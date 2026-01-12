import face_recognition
import cv2
import os
from ament_index_python.packages import get_package_share_directory

def main():
    #获取图片绝对路径
    pkg_share = get_package_share_directory('demo_python_service')
    image_path = os.path.join(pkg_share, 'resource/default.jpg')
    print(f"图片真实路径：{image_path}")
    #使用cv2加载
    image = cv2.imread(image_path)

    face_locations = face_recognition.face_locations(image, number_of_times_to_upsample=1, model='hog')

    for top,right,bottom,left in face_locations:
        cv2.rectangle(image,(left,top),(right,bottom),(255,0,0),4)
    cv2.imshow('Face detect result',image)
    cv2.waitKey(0)