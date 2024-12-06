import datetime
import time
import cv2
import serial
import pyrebase
import measure
from time import sleep
from threading import Timer

def get_object_color(image):
    # Format img
    hsv_frame = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

    # Get dimension image
    height, width, ret = image.shape
    cx = int(width/2)
    cy = int(height/2)

    # Get center pixel of object
    pixel_center = hsv_frame[cy, cx]
    hue_value = pixel_center[0]

    color = "Undefined"
    if hue_value < 10:
        color = "RED"
    if hue_value > 90 and hue_value < 130:
        color = "BLUE"
    if hue_value > 22 and hue_value < 45:
        color = "YELLOW"

    # Put text top-left img
    cv2.putText(image, color, (10, 70), 0, 1.5, (0, 0, 255), 2)

    # Put center circle 
    cv2.circle(image, (cx, cy), 5, (25, 25, 25), 3)

    return image, color

def connect_firebase():
    config = {
        "apiKey": "AIzaSyB7MBBveYBXPnWbHRPi9rPHEGfMYdwk2OE",
        "authDomain": "product-classification-f31bf.firebaseapp.com",
        "databaseURL": "https://product-classification-f31bf-default-rtdb.asia-southeast1.firebasedatabase.app",
        "projectId": "product-classification-f31bf",
        "storageBucket": "product-classification-f31bf.appspot.com",
        "messagingSenderId": "312000120740",
        "appId": "1:312000120740:web:d28f2968a899da11c82331",
    }
    firebase = pyrebase.initialize_app(config)
    return firebase.database()
    
def send_data_firebase(color, w, h):
    now = datetime.datetime.now()
    data = {"Width": w, "Height": h,
            "Date": now.strftime("%Y-%m-%d"+" "+"%H:%M:%S")}
    
    if (color == "RED"):
        db.child("Product Classification").child("Product Red").child(now.strftime("%Y-%m-%d"+" "+"%H:%M:%S")).set(data)
    if (color == "YELLOW"):
        db.child("Product Classification").child("Product Yellow").child(now.strftime("%Y-%m-%d"+" "+"%H:%M:%S")).set(data)
    if (color == "BLUE"):
        db.child("Product Classification").child("Product Blue").child(now.strftime("%Y-%m-%d"+" "+"%H:%M:%S")).set(data)

isRest = False
def resetTimeRestHandle():
    global isRest
    isRest = False

if __name__ == "__main__": 
    cap = cv2.VideoCapture(0)
    Arduino_Serial = serial.Serial('COM16', 9600, timeout=1)
    Arduino_Serial.flushInput()
    Arduino_Serial.readline()
    db = connect_firebase()

    while True:
        success, image = cap.read()

        if(isRest):
            continue

        image, edged = measure.read_and_preproces(image)
        # cv2.imshow("A", edged)
        # cv2.waitKey()

        image, arr_object = measure.find_object_in_pix(image, edged)
        print(arr_object)

        image, color = get_object_color(image)
        cv2.imshow("A", image)
        # cv2.waitKey()

        width = "Undefined" 
        height = "Undefined"
        # Get dimension of first object
        if(len(arr_object) > 0):
            width, height = arr_object[0].values()

        if(color!="Undefined" and width!="Undefined" and height!="Undefined"):
            isRest = True
            # Send data to Firebase+Arduino
            if (color == "RED"):
                Arduino_Serial.write('RED'.encode('utf-8'))
                send_data_firebase(color, width, height)
                resetTimeRest = Timer(5.0, resetTimeRestHandle)
                resetTimeRest.start()
                time.sleep(1)
            if (color == "YELLOW"):
                Arduino_Serial.write('YELLOW'.encode('utf-8'))
                send_data_firebase(color, width, height)
                resetTimeRest = Timer(5.0, resetTimeRestHandle)
                resetTimeRest.start()
                time.sleep(1)
            if (color == "BLUE"):
                Arduino_Serial.write('BLUE'.encode('utf-8'))
                send_data_firebase(color, width, height)
                resetTimeRest = Timer(5.0, resetTimeRestHandle)
                resetTimeRest.start()
                time.sleep(1)
        if cv2.waitKey(1) & 0xff == ord('q'):
            break
        time.sleep(0.25)

    cap.release()
    cv2.destroyAllWindows()
