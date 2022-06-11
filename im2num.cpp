#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <math.h>

std::vector<std::vector<int>> quantizeImg(std::vector<std::vector<float>> img,int levels){
  std::vector<std::vector<int>> out;
  for(int a=0; a< img.size();a++){
    std::vector<int> in;
    for(int b=0; b<img[a].size();b++){
      int v = (int)(levels*img[a][b]);
      if(v==levels)v=levels-1;
      in.push_back(v);
    }
    out.push_back(in);
  }
  return out;
}
std::vector<std::string> stringImg(std::vector<std::vector<int>> img,std::string ref){
  std::vector<std::string> out;
  for(int a=0; a< img.size();a++){
    std::string in;
    for(int b=0; b<img[a].size();b++){
      char v = ref[img[a][b]];
      in+=v;
    }
    out.push_back(in);
  }
  return out;
}

int get_height_target(int num_digits,float aspect){
  float tmp1 = 5*num_digits;
  float tmp2 = 7*aspect;
  float tmp3 = tmp1/tmp2;
  float tmp4 = std::sqrt(tmp3);
  int out = (int)tmp4;
  return out;
}


std::vector<std::string> img2num(char* path,int num_digits)
{
    cv::Mat mat;
    mat = cv::imread( path,cv::IMREAD_GRAYSCALE);

    //cv::imshow("Display window", mat);
    //int k = cv::waitKey(0);
    int TARGET_NUMBER_LENGTH = (mat.cols*mat.rows)/35;
    if(num_digits!=0){
      TARGET_NUMBER_LENGTH = num_digits;
    }

    float ASPECT_RATIO = (float)mat.cols/mat.rows;
    int HEIGHT_TARGET = get_height_target(TARGET_NUMBER_LENGTH,ASPECT_RATIO);
    int WIDTH_TARGET = (int) TARGET_NUMBER_LENGTH/HEIGHT_TARGET;

    int NUM_LEVELS = 10;
    std::string REF = "1172299408";

    cv::Mat img_eq;
    cv::equalizeHist(mat,img_eq);

    cv::Mat img_rs;
    cv::resize(img_eq, img_rs, cv::Size(WIDTH_TARGET,HEIGHT_TARGET), cv::INTER_LINEAR);

    std::vector<uchar> array;
    if (mat.isContinuous()) {
      // array.assign(mat.datastart, mat.dataend); // <- has problems for sub-matrix like mat = big_mat.row(i)
      array.assign(img_rs.data, img_rs.data + img_rs.total()*img_rs.channels());
    } else {
      for (int i = 0; i < img_rs.rows; ++i) {
        array.insert(array.end(), img_rs.ptr<uchar>(i), img_rs.ptr<uchar>(i)+img_rs.cols*img_rs.channels());
      }
    }
    std::vector<std::vector<float>> out;
    for(int i = 0;i< HEIGHT_TARGET;i++){
      std::vector<float> in;
      for(int j = 0; j < WIDTH_TARGET ; j++){
        int v = (int)array[i*WIDTH_TARGET+j];
        float f = (float)v/255;
        in.push_back(f);
      }
      out.push_back(in);
    }

    std::vector<std::vector<int>> img_q = quantizeImg(out,10);
    std::vector<std::string> img_s = stringImg(img_q,REF);
    return img_s;
}
