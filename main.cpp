#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <unistd.h>

#include "im2num.h"
#include "num2im.h"
#include "primetest.h"

int main(int argc, char** argv){
  int num_pixels = 0;
  int num_skip = 0;
  int num_threads = 4;
  int num_samps = 10;
  char* path;

  int c = 0;

  while ((c = getopt (argc, argv, "n:s:t:g:")) != -1){
    switch (c)
    {
    case 'n':
      num_pixels = std::atoi(optarg);
      break;
    case 's':
      num_skip = std::atoi(optarg);
      break;
    case 't':
      num_threads = std::atoi(optarg);
      break;
    case 'g':
      num_samps = std::atoi(optarg);
      break;
    case '?':
      if((optopt == 'n')|(optopt == 's')){
        fprintf (stderr, "Option -%c requires an argument.\n", optopt);
      }
      else if (isprint (optopt)){
        fprintf (stderr, "Unknown option `-%c'.\n", optopt);
      }
      else{
        fprintf (stderr,"Unknown option character `\\x%x'.\n",optopt);
      }
      return 1;
    default:
      abort();
    }
  }
  if(argc-optind != 1){
    fprintf (stderr,"Expected 1 non-optional argument, got %d.\n",argc-optind);
    return 1;
  }
  path = argv[optind];


  std::cout<<"Converting to number..."<<std::flush;
  std::vector<std::string> vv = img2num(path,num_pixels);
  std::cout<<"Done"<<std::endl;
  std::cout<<"Making number prime..."<<std::endl;
  std::vector<std::string> vp = prime_string(vv,num_skip,num_threads,num_samps);
  std::cout<<"Done"<<std::endl;
  std::cout<<"Writing result as image..."<<std::flush;
  num2im(vp);
  std::cout<<"Done"<<std::endl;
  return 0;
}
