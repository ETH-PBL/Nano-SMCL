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

        for i in [17]:

            seq = i

            dataDir = "/home/nickybones/Code/ros2_ws/src/smcl/data/S{}/".format(seq) 
            quantDir = "/home/nickybones/Code/ros2_ws/src/smcl/quantization/sequences/"
            imgDir = dataDir + "images/"
            predDir = dataDir + "preds/"
            arr = os.listdir(imgDir)
            arr = sorted(arr, key=lambda x: int(os.path.splitext(x)[0]))

            img_paths = [f for f in arr if ".png" in f]

            results = []

            sem_str = "float detection_input[][62] = {"

            for im_path in img_paths:

                img = cv2.imread(imgDir + im_path)
                img = cv2.resize(img, (width,height))
                debug_img = copy.deepcopy(img)

                image_id = int(im_path.split('.')[0].replace("Out", ""))

                pred_path = (predDir + im_path).replace(".png", ".txt")
                isExist = os.path.exists(pred_path)
                if isExist:
                    pred = pd.read_csv(pred_path, header=None).to_numpy()
                    output_img, real_boxes = self.postprocess(img, pred)
                    im_id = float(im_path.replace(".png", "")) * 10
                    cv2.imwrite(quantDir + "results/Q{}.png".format(int(im_id)), output_img)

                    num_boxes  = len(real_boxes)
                    if num_boxes > 10:
                        num_boxes = 10
                    if num_boxes > 0:
                        sem_str += "{ "
                        sem_str += "{}, ".format(10 * float(image_id))
                        sem_str += "{}, ".format(num_boxes)

                        for i in range(num_boxes):
                            box = real_boxes[i]

                            sem_str += "{}, {}, {}, {}, {}, {}, ".format(int(box[5]), int(box[0]), int(box[1]), int(box[2] + box[0]), int(box[3] + box[1]), box[4])

                        for j in range(num_boxes, 10):
                            sem_str += "{}, {}, {}, {}, {}, {}, ".format(0.0 , 0.0 , 0.0 ,  0.0, 0.0,  0.0)

                        sem_str = sem_str[:-2]
                        sem_str += " }, \n"

            sem_str = sem_str[:-3]
            sem_str += "};"

            f = open(dataDir + "sem_q.h", "w")
            n = f.write(sem_str)
            f.close()








            


if __name__ == '__main__':

    parser = argparse.ArgumentParser()
    parser.add_argument('--conf-thres', type=float, default=0.2, help='Confidence threshold')
    parser.add_argument('--iou-thres', type=float, default=0.5, help='NMS IoU threshold')
    parser.add_argument('--model', type=str, default="/home/nickybones/Code/ros2_ws/src/smcl/pbl300ep256sz_coco/weights/best.pt", help='dataset path')
    parser.add_argument('--data', type=str, default="/home/nickybones/Code/ultralytics/ultralytics/cfg/datasets/pbl.yaml", help='model path')

    args = parser.parse_args()
    qeval = QuantizedEvaluation(args.model, args.data, args.conf_thres, args.iou_thres)
    qeval.main()


