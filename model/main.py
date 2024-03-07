import argparse

import cv2
import numpy as np
import onnxruntime as ort
import torch
import os
import pandas as pd
import json 
import copy 

from ultralytics.utils import ROOT, yaml_load
from ultralytics.utils.checks import check_requirements, check_yaml
from ultralytics import YOLO


class QuantizedEvaluation:

    def __init__(self, model, data, confidence_thres, iou_thres):
        
        self.model = YOLO(model)
        self.confidence_thres = confidence_thres
        self.iou_thres = iou_thres
        self.classes = yaml_load(check_yaml(data))['names']
        self.color_palette = np.random.uniform(0, 255, size=(len(self.classes), 3))

    def draw_detections(self, img, box, score, class_id):
        

        x1, y1, w, h = box
        color = self.color_palette[class_id]
        cv2.rectangle(img, (int(x1), int(y1)), (int(x1 + w), int(y1 + h)), color, 2)
        label = f'{self.classes[class_id]}: {score:.2f}'
        (label_width, label_height), _ = cv2.getTextSize(label, cv2.FONT_HERSHEY_SIMPLEX, 0.5, 1)

        label_x = x1
        label_y = y1 - 10 if y1 - 10 > label_height else y1 + 10

        cv2.rectangle(img, (label_x, label_y - label_height), (label_x + label_width, label_y + label_height), color,
                      cv2.FILLED)

        cv2.putText(img, label, (label_x, label_y), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 0), 1, cv2.LINE_AA)


    def postprocess(self, input_image, output):
        
        #outputs = np.transpose(np.squeeze(output[0]))
        outputs = output

        rows = outputs.shape[0]
        boxes = []
        scores = []
        class_ids = []

        img_height, img_width = input_image.shape[:2]


        x_factor = img_width / self.input_width
        y_factor = img_height / self.input_height

        # Iterate over each row in the outputs array
        for i in range(rows):
            # Extract the class scores from the current row
            classes_scores = outputs[i][4:]

            # Find the maximum score among the class scores
            max_score = np.amax(classes_scores)

            # If the maximum score is above the confidence threshold
            if max_score >= self.confidence_thres:
                # Get the class ID with the highest score
                class_id = np.argmax(classes_scores)

                # Extract the bounding box coordinates from the current row
                x, y, w, h = outputs[i][0], outputs[i][1], outputs[i][2], outputs[i][3]
                #print(x, y, w, h)

                # Calculate the scaled coordinates of the bounding box
                left = int((x - w / 2) * x_factor)
                top = int((y - h / 2) * y_factor)
                width = int(w * x_factor)
                height = int(h * y_factor)

                # Add the class ID, score, and box coordinates to the respective lists
                class_ids.append(class_id)
                scores.append(max_score)
                boxes.append([left, top, width, height])

        # Apply non-maximum suppression to filter out overlapping bounding boxes
        indices = cv2.dnn.NMSBoxes(boxes, scores, self.confidence_thres, self.iou_thres)

        real_boxes = []

        # Iterate over the selected indices after non-maximum suppression
        for i in indices:
            # Get the box, score, and class ID corresponding to the index
            box = boxes[i]
            score = scores[i]
            class_id = class_ids[i]
            if box[0] < 0:
                box[0] = 0
            if box[1] < 0:
                box[1] = 0
            real_boxes.append(np.array([box[0], box[1], box[2], box[3], score, class_id]))
            # Draw the detection on the input image
            self.draw_detections(input_image, box, score, class_id)

        
        return input_image, real_boxes




    def main(self):

        
        self.input_width = 256
        self.input_height = 256

        width = 256
        height  = 192
        loadFromFile = True

        Qtype = "HANNA"

        daddyDir = "testset/" 
        imgDir = daddyDir + "images/"
        predDir = daddyDir + "preds_{}/".format(Qtype)
        labelDir = daddyDir + "labels/"
        arr = os.listdir(imgDir)
        img_paths = [f for f in arr if ".png" in f]

        results = []

        for im_path in img_paths:

            img = cv2.imread(imgDir + im_path)
            img = cv2.resize(img, (width,height))
            debug_img = copy.deepcopy(img)

            image_id = int(im_path.split('.')[0].replace("Out", ""))
            if loadFromFile:

                pred_path = (predDir + im_path).replace(".png", ".txt")
                isExist = os.path.exists(pred_path)
                if isExist:
                    pred = pd.read_csv(pred_path, header=None).to_numpy()
                    output_img, real_boxes = self.postprocess(img, pred)

                    for box in real_boxes:

                        result = {
                        "image_id": image_id,
                        "category_id": int(box[5]),
                        "bbox": [int(box[0]), int(box[1]), int(box[2]), int(box[3])],
                        "score": box[4],
                        }
                        results.append(result)

                    cv2.imwrite(daddyDir + "results/" + im_path.replace(".png", "") + "Q.png", output_img)



            else:
                preds = self.model.predict(source=img) 
                output_img = copy.deepcopy(img)
                for pred in preds:

                    for i in range(len(pred.boxes)):

                        c = pred.boxes[i].cls.cpu().numpy()[0]
                        box = pred.boxes[i].xyxy.cpu().numpy().flatten().tolist()
                        conf = pred.boxes[i].conf.cpu().numpy()[0]

                        result = {
                        "image_id": image_id,
                        "category_id": int(c),
                        "bbox": [int(box[0]), int(box[1]), int(box[2] - box[0]), int(box[3] - box[1])],
                        "score": float(conf),
                        }
                        results.append(result)

                        self.draw_detections(output_img, [int(box[0]), int(box[1]), int(box[2] - box[0]), int(box[3] - box[1])], conf, int(c))

                cv2.imwrite(daddyDir + "results/" + im_path.replace(".png", "") + "FP.png", output_img)




            label_path = (labelDir + im_path).replace(".png", ".txt")
            print(label_path)
            with open(os.path.join(labelDir, f'{im_path.split(".")[0]}.txt')) as f:
                annotations = f.readlines()
        
            for ann in annotations:
                x, y, w, h = map(float, ann.strip().split()[1:])
                if x < 0:
                    x = 0
                if y < 0:
                    y = 0
                c = int(ann.strip().split()[0])
                x_min, y_min = int((x - w / 2) * width), int((y - h / 2) * height)
                x_max, y_max = int((x + w / 2) * width), int((y + h / 2) * height)
                self.draw_detections(debug_img, [x_min, y_min, x_max - x_min, y_max - y_min], 1.0, c)

            cv2.imwrite(daddyDir + "results/" + im_path.replace(".png", "") + "GT.png", debug_img)
                # ann_dict = {
                # "image_id": int(im_path.split('.')[0].replace("Out", "")),
                # "category_id": c,
                # "bbox": [x_min, y_min, x_max - x_min, y_max - y_min],
                # "score": 1.0,
                # }
                # results.append(ann_dict)


        print(results)
        if loadFromFile:
            with open(os.path.join('/home/nickybones/Code/ros2_ws/src/smcl/quantization/', 'Q_{}_predictions_testset.json'.format(Qtype)), 'w') as f:
                json.dump(results, f, indent=4)
        else:
             with open(os.path.join('/home/nickybones/Code/ros2_ws/src/smcl/quantization/', 'FP_predictions_testset.json'), 'w') as f:
                json.dump(results, f, indent=4)

                


if __name__ == '__main__':

    parser = argparse.ArgumentParser()
    parser.add_argument('--conf-thres', type=float, default=0.2, help='Confidence threshold')
    parser.add_argument('--iou-thres', type=float, default=0.5, help='NMS IoU threshold')
    parser.add_argument('--model', type=str, default="/home/nickybones/Code/ros2_ws/src/smcl/pbl300ep256sz_coco/weights/best.pt", help='dataset path')
    parser.add_argument('--data', type=str, default="/home/nickybones/Code/ultralytics/ultralytics/cfg/datasets/pbl.yaml", help='model path')

    args = parser.parse_args()
    qeval = QuantizedEvaluation(args.model, args.data, args.conf_thres, args.iou_thres)
    qeval.main()


