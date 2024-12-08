#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace cv;

void removeBackgroundWithGreenscreen(const char *inputImage,
                                     const char *outputImage) {
  // Baca gambar
  Mat img = imread(inputImage);
  if (img.empty()) {
    printf("Gagal membaca gambar: %s\n", inputImage);
    return;
  }

  // Konversi ke HSV
  Mat hsvImg;
  cvtColor(img, hsvImg, COLOR_BGR2HSV);

  // Buat mask untuk warna hijau (greenscreen)
  Mat mask;
  inRange(hsvImg, Scalar(35, 50, 50), Scalar(85, 255, 255), mask);

  // Perbaiki mask dengan operasi morfologi (dilate dan erode)
  Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
  morphologyEx(mask, mask, MORPH_CLOSE, kernel); // Mengisi area kecil
  morphologyEx(mask, mask, MORPH_OPEN, kernel);  // Menghilangkan noise kecil

  // Balik mask (objek utama menjadi putih, background hitam)
  bitwise_not(mask, mask);

  // Terapkan mask ke gambar asli
  Mat result;
  img.copyTo(result, mask);

  // Simpan hasil
  imwrite(outputImage, result);
  printf("Background dihapus dengan greenscreen. Gambar disimpan ke: %s\n",
         outputImage);
}

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Usage: %s <input_image> <output_image>\n", argv[0]);
    return -1;
  }

  removeBackgroundWithGreenscreen(argv[1], argv[2]);
  return 0;
}

