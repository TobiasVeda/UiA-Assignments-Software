import cv2


def print_image_information(img):
    print(f"height: {img.shape[0]}")
    print(f"width: {img.shape[1]}")
    print(f"channels: {img.shape[2]}")
    print(f"size: {img.size}")
    print(f"data type: {img.dtype}")


def video_capture():
    cam = cv2.VideoCapture(0)

    frame_width = int(cam.get(cv2.CAP_PROP_FRAME_WIDTH))
    frame_height = int(cam.get(cv2.CAP_PROP_FRAME_HEIGHT))
    fps = cam.get(cv2.CAP_PROP_FPS)

    with open("solutions/camera_outputs.txt", "w") as file:
        file.write(f"width: {frame_width}\n")
        file.write(f"height: {frame_height}\n")
        file.write(f"fps: {fps}\n")

    fourcc = cv2.VideoWriter_fourcc(*"mp4v")
    out = cv2.VideoWriter("output.mp4", fourcc, 20.0, (frame_width, frame_height))

    while True:
        ret, frame = cam.read()
        out.write(frame)
        cv2.imshow("Camera", frame)

        if cv2.waitKey(1) == ord('q'):
            break

    cam.release()
    out.release()
    cv2.destroyAllWindows()


def main():
    img = cv2.imread("lena-1.png", -1)
    print_image_information(img)
    video_capture()


if __name__ == "__main__":
    main()

