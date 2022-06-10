#include "MyOutputManager.h"
#include <cstdio>

MyOutputManager* MyOutputManager::fptr = 0;

MyOutputManager* MyOutputManager::Get(){
  if(fptr == 0){
    fptr = new MyOutputManager();
  }
  return fptr;
}

MyOutputManager::MyOutputManager() {
  printf("%s\n",__PRETTY_FUNCTION__);
}


MyOutputManager::~MyOutputManager() {
  printf("%s\n",__PRETTY_FUNCTION__);
}



void MyOutputManager::setupTree(const char* fname){
//  foutput = new TFile("output.root","recreate");
//  fTree = new TTree("t1","My Awesome Tree!");
}

void MyOutputManager::closeTree(){
//  foutput->Write();
//  foutput->Close();

}
