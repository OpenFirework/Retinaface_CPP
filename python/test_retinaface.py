import retinacarton
import cv2

model_path="/home/sky/Projects/Retinaface_CPP-master/models"
detector=retinacarton.PyRetinaFaceCarton()
detector.Initial(model_path)
img=cv.imread("/home/sky/Projects/Retinaface_CPP-master/test_cartons/onepiece.jpg")
res=detcor.DetectFace(img, img.shape[1], img.shape[0])
print(res)  
       
