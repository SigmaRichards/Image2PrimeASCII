#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <iostream>

#include <thread>
#include <future>
#include <vector>
#include <string>
#include <algorithm>
#include <random>

std::vector<int> get_next_numbers(int last_num,int size){
  std::vector<int> out;
  for(int a = 1; a<=size ; a++){     //starting from 1 so that last_num + 0 doesn't occur
    out.push_back(last_num + 2*a);
  }
  return out;
}

std::vector<std::vector<int>> splitvec(std::vector<int> vec,int n_threads,int n_samps){
  std::vector<std::vector<int>> out;
  int index = 0;
  for(int a = 0; a<n_threads;a++){
    std::vector<int> in;
    for(int b = 0; b<n_samps; b++){
      in.push_back(vec[index]);
      index++;
    }
    out.push_back(in);
  }
  return out;
}

int prime_func(const char* refc, std::vector<int> tests){
  //Initialize random state
  int seed = rand();
  gmp_randstate_t s;
  gmp_randinit_default(s);
  gmp_randseed_ui(s,seed);

  //Values to be created
  mpz_t p;//prime to test - if even will test p+1
  mpz_t pa;
  mpz_t tmp;//space for output values

  mpz_init(p);
  mpz_init(pa);
  mpz_init(tmp);

  //Initializing values
  int flag = mpz_set_str(p,refc, 10);
  int out = -1;
  for(int a = 0; a < tests.size(); a++){
    mpz_add_ui(pa,p,tests[a]);
    int isprime = mpz_probab_prime_p(pa,15);
    if(isprime>0){
      out = a;
      break;
    }
  }
  mpz_clear(p);
  mpz_clear(pa);
  mpz_clear(tmp);
  gmp_randclear(s);
  return out;
}

std::string do_prime_check(std::string start,int n_threads, int n_samps){
  auto rng = std::default_random_engine {};
  if(((start[start.length()-1] - '0')%2)==0){
    start[start.length()-1] = (start[start.length()-1] + 1);
  }
  const char* ref = start.c_str();
  int prime_index = -1;
  int thread_ind = -1;
  int last_num = -2;
  int num_tested = 0;
  std::vector<std::vector<int>> split_samps;

  std::cout<<"Test batch size: "<<n_samps*n_threads<<std::endl;
  std::vector<std::future<int>> futures;
  while(prime_index==-1){
    std::cout<<"\r";
    std::cout<<"Total tested: "<<num_tested<<std::flush;
    std::vector<int> samps = get_next_numbers(last_num,n_threads*n_samps);
    last_num = samps[n_threads*n_samps-1];
    std::shuffle(std::begin(samps), std::end(samps), rng);

    split_samps = splitvec(samps,n_threads,n_samps);
    for(int a = 0; a<n_threads; a++){
      futures.push_back(std::async(prime_func,ref, split_samps[a]));
    }
    for(int a = 0; a<n_threads; a++){
      int cv = futures[a].get();
      if(cv!=-1){
        prime_index = cv;
        thread_ind = a;
      }
    }
    for(int a = 0; a<n_threads; a++){
      futures.pop_back();
    }
    num_tested+=n_samps*n_threads;
  }
  std::cout<<std::endl;
  mpz_t p;
  mpz_init(p);
  mpz_set_str(p,ref, 10);
  mpz_add_ui(p,p,split_samps[thread_ind][prime_index]);
  char * out_cstar = mpz_get_str(NULL,10,p);
  std::string str_out = out_cstar;
  return str_out;
}

std::string is_prime(std::string ref){//deprecated
  const char* refc = ref.c_str();

  //Initialize random state
  int seed = rand();
  gmp_randstate_t s;
  gmp_randinit_default(s);
  gmp_randseed_ui(s,seed);

  //Values to be created
  mpz_t p;//prime to test - if even will test p+1
  mpz_t tmp;//space for output values

  mpz_init(p);
  mpz_init(tmp);

  //Initializing values
  int flag = mpz_set_str(p,refc, 10);

  int counter = 1;
  while(true){
    std::cout<<"Testing value: "<<counter<<'\r'<<std::flush;
    //prime test on p
    mpz_mod_ui(tmp,p,2);
    if(mpz_cmp_ui(tmp,0)>0){         //if odd
      int isprime = mpz_probab_prime_p(p,15);
      if(isprime>0){                   // if prime
        break;
      }else{
        mpz_add_ui(p,p,2);
        counter+=1;
      }
    }else{
      mpz_add_ui(p,p,1);
      counter+=1;
    }
  }
  std::cout<<std::endl;

  char * tmps = mpz_get_str(NULL,10,p);
  std::string str_out = tmps;

  mpz_clear(p);
  mpz_clear(tmp);

  return str_out;

}

std::string vec2str(std::vector<std::string> vv){
  std::string out;
  for(int i = 0;i<vv.size();i++){
    out+=vv[i];
  }
  return out;
}

std::vector<std::string> str2vec(std::string str,int len){
  std::vector<std::string> out;
  std::string tmp;
  for(int i = 0; i<str.length();i+=len){
    tmp = str.substr(i,len);
    out.push_back(tmp);
  }
  return out;
}

std::vector<std::string> prime_string(std::vector<std::string> vv){
  srand(time(NULL));

  std::string str = vec2str(vv);
  //std::string test = is_prime(str);
  std::string test = do_prime_check(str,12,10);
  std::vector<std::string> out = str2vec(test,vv[0].length());
  //bigint out_i = get_prime(c_bint,1,ndig);
  //std::vector<std::string> out = bi2str(out_i,vv[0].length());
  return out;
}
