#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

void update_outim(std::vector<int *> arr,int target){
  switch (target) {
    case 0:
      *arr[0]=255;
      *arr[1]=255;
      *arr[2]=255;
      *arr[3]=255;
      *arr[4]=255;
      *arr[5]=255;
      *arr[7]=255;
      *arr[8]=255;
      *arr[9]=255;
      *arr[10]=255;
      *arr[11]=255;
      *arr[12]=255;
      break;
    case 1:
      *arr[2]=255;
      *arr[4]=255;
      *arr[7]=255;
      *arr[9]=255;
      *arr[12]=255;
      break;
    case 2:
      *arr[0]=255;
      *arr[1]=255;
      *arr[2]=255;
      *arr[4]=255;
      *arr[5]=255;
      *arr[6]=255;
      *arr[7]=255;
      *arr[8]=255;
      *arr[10]=255;
      *arr[11]=255;
      *arr[12]=255;
      break;
    case 3:
      *arr[0]=255;
      *arr[1]=255;
      *arr[2]=255;
      *arr[4]=255;
      *arr[5]=255;
      *arr[6]=255;
      *arr[7]=255;
      *arr[9]=255;
      *arr[10]=255;
      *arr[11]=255;
      *arr[12]=255;
      break;
    case 4:
      *arr[0]=255;
      *arr[2]=255;
      *arr[3]=255;
      *arr[4]=255;
      *arr[5]=255;
      *arr[6]=255;
      *arr[7]=255;
      *arr[9]=255;
      *arr[12]=255;
      break;
    case 5:
      *arr[0]=255;
      *arr[1]=255;
      *arr[2]=255;
      *arr[3]=255;
      *arr[5]=255;
      *arr[6]=255;
      *arr[7]=255;
      *arr[9]=255;
      *arr[10]=255;
      *arr[11]=255;
      *arr[12]=255;
      break;
    case 6:
      *arr[0]=255;
      *arr[3]=255;
      *arr[5]=255;
      *arr[6]=255;
      *arr[7]=255;
      *arr[8]=255;
      *arr[9]=255;
      *arr[10]=255;
      *arr[11]=255;
      *arr[12]=255;
      break;
    case 7:
      *arr[0]=255;
      *arr[1]=255;
      *arr[2]=255;
      *arr[4]=255;
      *arr[7]=255;
      *arr[9]=255;
      *arr[12]=255;
      break;
    case 8:
      *arr[0]=255;
      *arr[1]=255;
      *arr[2]=255;
      *arr[3]=255;
      *arr[4]=255;
      *arr[5]=255;
      *arr[6]=255;
      *arr[7]=255;
      *arr[8]=255;
      *arr[9]=255;
      *arr[10]=255;
      *arr[11]=255;
      *arr[12]=255;
      break;
    case 9:
      *arr[0]=255;
      *arr[1]=255;
      *arr[2]=255;
      *arr[3]=255;
      *arr[4]=255;
      *arr[5]=255;
      *arr[6]=255;
      *arr[7]=255;
      *arr[9]=255;
      *arr[12]=255;
      break;

  }
}

std::vector<uchar> convert_vector(std::vector<std::vector<int>> img_i){
  std::vector<uchar> out;
  for(int i = 0; i < img_i.size(); i++){
    for(int j = 0; j < img_i[i].size(); j++){
      out.push_back((uchar)(img_i[i][j]));
    }
  }
  return out;
}

void num2im(std::vector<std::string> img_s){
  int R = img_s.size()*7;
  int C = img_s[0].size()*5;
  std::vector<std::vector<int>> v(R, std::vector<int>(C));

  for(int i = 0; i < img_s.size(); i++){
    std::string cstr = img_s[i];
    for(int j = 0; j < img_s[i].size(); j++){
      char c_s = cstr[j];
      int c_i = c_s-'0';
      int ip = i*7+1;
      int jp = j*5+1;

      std::vector<int *> arr;
      arr.insert(arr.end(),{&v[ip][jp],&v[ip][jp+1],&v[ip][jp+2]});
      arr.insert(arr.end(),{&v[ip+1][jp],&v[ip+1][jp+2]});
      arr.insert(arr.end(),{&v[ip+2][jp],&v[ip+2][jp+1],&v[ip+2][jp+2]});
      arr.insert(arr.end(),{&v[ip+3][jp],&v[ip+3][jp+2]});
      arr.insert(arr.end(),{&v[ip+4][jp],&v[ip+4][jp+1],&v[ip+4][jp+2]});

      update_outim(arr,c_i);
    }
  }

  std::vector<uchar> img_u = convert_vector(v);

  cv::Mat img_o(v.size(),v[0].size(),0,img_u.data());

  cv::imwrite("out.png",img_o);
  return;
}
