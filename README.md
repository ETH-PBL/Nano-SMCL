# Fully Onboard Low-Power Localization with Semantic Sensor Fusion on a Nano-UAV using Floor Plans
This repository contains the implementation of the following publication - Arxiv link coming soon!
```bibtex
@article{zimmerman2024icra,
  title = {{Fully Onboard Low-Power Localization with Semantic Sensor Fusion on a Nano-UAV using Floor Plans}},
  author  = {Zimmerman, Nicky and Müller, Hanna and Magno, Michele and Benini, Luca},
  journal = {{arXiv preprint:XXXX.XXXXX}},
  year    = {2023}
}
```

## Abstract
Nano-sized unmanned aerial vehicles (UAVs) are well-fit for indoor applications and for close proximity to humans. To enable autonomy, the nano-UAV must be able to self-localize in its operating environment. This is a particularly-challenging task due to the limited sensing and compute resources on board. This work presents an online and onboard approach for localization in floor plans annotated with semantic information. Unlike sensor-based maps, floor plans are readily-available, and do not increase the cost and time of deployment. To overcome the difficulty of localizing in sparse maps, the proposed approach fuses geometric information from miniaturized time-of-flight sensors and semantic cues. The semantic information is extracted from images by deploying a state-of-the-art object detection model on a high-performance multi-core microcontroller onboard the drone, consuming only 2.5mJ per frame and executing in 38ms. In our evaluation, we globally localize in a real-world office environment, achieving 90\% success rate. 

<p align="center">
<img src="resources/motivation.png" width="384"/>
</p>

## Results
Our live demos for semantic localization on the Bitcraze Crazyflie 2.1 can seen in the following video:
[![](http://img.youtube.com/vi/03l6LVqv4VA/0.jpg)](https://www.youtube.com/watch?v=03l6LVqv4VA "SMCL")

## Installation 
Working on it right now!!!
