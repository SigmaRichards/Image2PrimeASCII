#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

#include "im2num.h"
#include "num2im.h"
#include "primetest.h"

int main(int argc, char** argv){
  int num_pixels = 0;
  if( (argc < 2)|(argc > 3))
    {
      std::cout<<"Usage: ./output image.jpg num_digits"<<std::endl;
      return -1;
    }
  if(argc==3){
    num_pixels = std::stoi(argv[2]);
  }

  std::cout<<"Converting to number..."<<std::flush;
  std::vector<std::string> vv = img2num(argv[1],num_pixels);
  std::cout<<"Done"<<std::endl;
  std::cout<<"Making number prime..."<<std::endl;
  std::vector<std::string> vp = prime_string(vv);
  std::cout<<"Done"<<std::endl;
  std::cout<<"Writing result as image..."<<std::flush;
  num2im(vp);
  std::cout<<"Done"<<std::endl;

  return 0;
}
