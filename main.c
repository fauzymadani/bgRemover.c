#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace cv;

void removeBackground(const char *inputImage, const char *outputImage) {
  // read file
  Mat img = imread(inputImage);
  if (img.empty()) {
    printf("Gagal membaca gambar: %s\n", inputImage);
    return;
  }

  // Convert to HSV
  Mat hsvImg;
  cvtColor(img, hsvImg, COLOR_BGR2HSV);

  // creating mask for bg color
  Mat mask;
  inRange(hsvImg, Scalar(30, 0, 0), Scalar(180, 255, 255),
          mask); // HSV teshold examp,le

  // flip mask
  bitwise_not(mask, mask);

  Mat result;
  img.copyTo(result, mask);

  // set output
  imwrite(outputImage, result);
  printf("completed. saving image to: %s\n", outputImage);
}

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Usage: %s <input_image> <output_image>\n", argv[0]);
    return -1;
  }

  removeBackground(argv[1], argv[2]);
  return 0;
}
