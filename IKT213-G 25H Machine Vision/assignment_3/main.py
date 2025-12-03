import cv2
import numpy as np
from cv2 import GaussianBlur, matchTemplate


def sobel_edge_detection(image):
    blur = GaussianBlur(image, ksize=(3,3), sigmaX=0)
    sobel = cv2.Sobel(src=blur, ddepth=cv2.CV_64F, dx=1, dy=1, ksize=1)
    cv2.imwrite("solution/sobel.png", sobel)

def canny_edge_detection(image, threshold_1, threshold_2):
    blur = GaussianBlur(image, ksize=(3, 3), sigmaX=0)
    canny = cv2.Canny(blur, threshold_1, threshold_2)
    cv2.imwrite("solution/canny.png", canny)

def template_matching(image, template):

    img = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    template = cv2.cvtColor(template, cv2.COLOR_BGR2GRAY)
    height, width = template.shape
    threshold = 0.9

    res = cv2.matchTemplate(img, template, cv2.TM_CCOEFF_NORMED)
    loc = np.where(res >= threshold)

    for i in zip(*loc[::-1]):
        top_left = i
        bottom_right = (i[0] + width, i[1] + height)
        cv2.rectangle(image, top_left, bottom_right, (0, 0, 255), 1)

    cv2.imwrite(f"solution/match.png", image)

def resize(image, scale_factor:int, up_or_down:str):
    width, height, color = image.shape

    if up_or_down == "up":
        result = cv2.pyrUp(src=image, dstsize=(scale_factor * height, scale_factor * width))
    elif up_or_down == "down":
        result = cv2.pyrDown(src=image, dstsize=(scale_factor // height, scale_factor // width))
    else:
        print("invalid \"up_or_down\"")
        return
    cv2.imwrite(f"solution/scale_{up_or_down}.png", result)

def main():
    lambo = cv2.imread("img/lambo.png")
    shapes = cv2.imread("img/shapes-1.png")
    template = cv2.imread("img/shapes_template.jpg")
    sobel_edge_detection(lambo)
    canny_edge_detection(lambo, 50, 50)
    template_matching(shapes, template)
    resize(lambo, 2, "up")
    resize(lambo, 2, "down")


if __name__ == "__main__":
    main()