import cv2
import numpy as np

def padding(image, border_width):
    reflect = cv2.copyMakeBorder(image, border_width, border_width, border_width, border_width, cv2.BORDER_REFLECT)
    cv2.imwrite("solution/reflectedLena.png", reflect)

def crop(image, x_0, y_0, x_1, y_1):
    cropped = image[y_0:y_1, x_0:x_1]
    cv2.imwrite("solution/croppedLena.png", cropped)

def resize(image, width, height):
    resized = cv2.resize(image, (width, height))
    cv2.imwrite("solution/resizedLena.png", resized)

def copy(image, emptyPictureArray):
    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            for k in range (image.shape[2]):
                emptyPictureArray[i][j][k] = image[i][j][k]
    cv2.imwrite("solution/copiedLena.png", emptyPictureArray)

def grayscale(image):
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    cv2.imwrite("solution/grayLena.png", gray)

def hsv(image):
    hsvImg = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
    cv2.imwrite("solution/hsvLena.png", hsvImg)

def hue_shifted(image, emptyPictureArray, hue):
    # doesn't specify if the shifted image should be
    # copied to "emptyPictureArray"
    image = cv2.add(image, hue) # "add" caps at 255
    cv2.imwrite("solution/shiftedLena.png", image)

def smoothing(image):
    blur = cv2.blur(image, (15,15), cv2.BORDER_DEFAULT)
    cv2.imwrite("solution/smoothedLena.png", blur)

def rotation(image, rotation_angle):
    if rotation_angle == 90:
        rotated = cv2.rotate(image, cv2.ROTATE_90_CLOCKWISE)
        cv2.imwrite("solution/rotated90Lena.png", rotated)
    elif rotation_angle == 180:
        rotated = cv2.rotate(image, cv2.ROTATE_180)
        cv2.imwrite("solution/rotated180Lena.png", rotated)
    elif rotation_angle == 270:
        rotated = cv2.rotate(image, cv2.ROTATE_90_COUNTERCLOCKWISE)
        cv2.imwrite("solution/rotated270Lena.png", rotated)
    else:
        print("invalid rotation angle")


def main():
    image = cv2.imread("lena-2.png")
    height = image.shape[0]
    width = image.shape[1]
    emptyPictureArray = np.zeros((height, width, 3), dtype=np.uint8)

    padding(image, 100)
    crop(image, 80, 80, (width - 130), (height - 130))
    resize(image, 200, 200)
    copy(image, emptyPictureArray)
    grayscale(image)
    hsv(image)
    hue_shifted(image, emptyPictureArray, 50)
    smoothing(image)
    rotation(image, 90)
    rotation(image, 180)
    rotation(image, 270)


if __name__ == '__main__':
    main()