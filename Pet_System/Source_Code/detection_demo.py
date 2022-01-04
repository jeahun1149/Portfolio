#================================================================
#
#   File name   : detection_demo.py
#   Author      : PyLessons
#   Created date: 2020-09-27
#   Website     : https://pylessons.com/
#   GitHub      : https://github.com/pythonlessons/TensorFlow-2.x-YOLOv3
#   Description : object detection image and video example
#
#================================================================
import pygame
import os

os.environ['CUDA_VISIBLE_DEVICES'] = '0'

pygame.init()
pygame.mixer.music.load("system_ready.wav")
pygame.mixer.music.play()

import cv2
import numpy as np
import tensorflow as tf
from yolov3.utils import detect_image, detect_realtime, detect_video, Load_Yolo_model, detect_video_realtime_mp
from yolov3.configs import *

os.system('python3 servo_set.py')


pygame.mixer.music.load("system_start.wav")
pygame.mixer.music.play()

yolo = Load_Yolo_model()
detect_realtime(yolo, '', input_size=YOLO_INPUT_SIZE, show=True, rectangle_colors=(255, 0, 0))
