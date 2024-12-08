#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace cv;

void removeBackgroundWithGreenscreen(const char *inputImage,
                                     const char *outputImage) {
  // read image
  Mat img = imread(inputImage);
  if (img.empty()) {
    printf("Could not read image: %s\n", inputImage);
    return;
  }

  // convert to HSV
  Mat hsvImg;
  cvtColor(img, hsvImg, COLOR_BGR2HSV);

  // masking for green color
  Mat mask;
  inRange(hsvImg, Scalar(35, 50, 50), Scalar(85, 255, 255), mask);

  Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
  morphologyEx(mask, mask, MORPH_CLOSE, kernel); // fill space
  morphologyEx(mask, mask, MORPH_OPEN, kernel);  // remove noise

  bitwise_not(mask, mask);

  // implement mask to the image
  Mat result;
  img.copyTo(result, mask);

  // save result
  imwrite(outputImage, result);
  printf("completed. save changes to: %s\n", outputImage);
}

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Usage: %s <input_image> <output_image>\n", argv[0]);
    return -1;
  }

  removeBackgroundWithGreenscreen(argv[1], argv[2]);
  return 0;
}
