import Image_Stitching
import cv2
import numpy as np


def detect_corners(reference_image):
    gray = cv2.cvtColor(reference_image, cv2.COLOR_BGR2GRAY)
    gray = np.float32(gray)
    dst = cv2.cornerHarris(gray, 2, 3, 0.04)

    #For every value in "dst" that is greater that 1% of the max value in "dst",
    # set the pixel at the equivalent coordinate in "reference_image" to red (╯‵□′)╯︵┻━┻
    reference_image[dst > 0.01 * dst.max()] = [0, 0, 255]
    return reference_image


def feature_match(image_to_align, reference_image, max_features, good_match_percent):

    img1 = cv2.cvtColor(image_to_align, cv2.COLOR_BGR2GRAY)
    img2 = cv2.cvtColor(reference_image, cv2.COLOR_BGR2GRAY)

    # Initiate SIFT detector
    sift = cv2.SIFT_create()

    # Find the keypoints and descriptors with SIFT
    kp1, des1 = sift.detectAndCompute(img1, None)
    kp2, des2 = sift.detectAndCompute(img2, None)

    FLANN_INDEX_KDTREE = 1
    index_params = dict(algorithm=FLANN_INDEX_KDTREE, trees=5)
    search_params = dict(checks=50)
    flann = cv2.FlannBasedMatcher(index_params, search_params)
    matches = flann.knnMatch(des1, des2, k=2)

    # Store all the good matches as per Lowe's ratio test.
    good = []
    for m, n in matches:
        if m.distance < good_match_percent * n.distance:
            good.append(m)


    if len(good) > max_features:
        # If enough good matches
        src_pts = np.float32([kp1[m.queryIdx].pt for m in good]).reshape(-1, 1, 2)
        dst_pts = np.float32([kp2[m.trainIdx].pt for m in good]).reshape(-1, 1, 2)

        M, mask = cv2.findHomography(src_pts, dst_pts, cv2.RANSAC, 5.0)
        matches_mask = mask.ravel().tolist()

        h, w = img1.shape
        pts = np.float32([[0, 0], [0, h - 1], [w - 1, h - 1], [w - 1, 0]]).reshape(-1, 1, 2)
        dst = cv2.perspectiveTransform(pts, M)

        img2 = cv2.polylines(img2, [np.int32(dst)], True, 255, 3, cv2.LINE_AA)

    else:
        # Not enough good matches. Results in no lines drawn
        print(f"Not enough matches are found - {len(good)}/{max_features}")
        matches_mask = None

    draw_params = dict(matchColor=(0, 255, 0),  # draw matches in green color
                       singlePointColor=None,
                       matchesMask=matches_mask,  # draw only inliers
                       flags=2)

    img3 = cv2.drawMatches(img1, kp1, img2, kp2, good, None, **draw_params)
    return img3


def main():
    max_features = 10
    good_match_percent = 0.7
    img1 = cv2.imread("ref_img/reference_img.png")
    img2 = cv2.imread("ref_img/align_this.jpg")

    detected = detect_corners(img1)
    cv2.imwrite("res_img/harris.png", detected)

    matched = feature_match(img2, img1, max_features, good_match_percent)
    cv2.imwrite("res_img/matched.jpg", matched)

    stitcher = Image_Stitching.Image_Stitching()
    aligned = stitcher.blending(img1, img2)
    cv2.imwrite("res_img/aligned.png", aligned)



if __name__ == '__main__':
    main()