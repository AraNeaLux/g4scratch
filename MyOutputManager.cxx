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
  foutput = new TFile("output.root","recreate");
  fTree = new TTree("t1","My Awesome Tree!");

  fTree->Branch("EventID",      &fEventID);     
  fTree->Branch("TrackID",      &fTrackID);     
  fTree->Branch("StepNum",      &fStepNum);     
  fTree->Branch("SubStepNum",   &fSubStepNum);  
  fTree->Branch("ParticleName", &fParticleName); 
  fTree->Branch("ke",           &fke);           
  fTree->Branch("x",            &fx);            
  fTree->Branch("y",            &fy);            
  fTree->Branch("z",            &fz);            

}

void MyOutputManager::closeTree(){
  foutput->Write();
  foutput->Close();

}

void MyOutputManager::clear(){
  fEventID      = -1;
  fTrackID      = -1;
  fStepNum      = -1;
  fSubStepNum   = -1; 
  fParticleName = ""; 
  fke           = sqrt(-1); 
  fx            = sqrt(-1); 
  fy            = sqrt(-1); 
  fz            = sqrt(-1); 

}

void MyOutputManager::fill(int eventID,
                           int trackID,
                           int stepNum,
                           int subStepNum,
                           std::string particleName,
                           double ke,
                           double x,
                           double y,
                           double z){
  fEventID        = eventID;     
  fTrackID        = trackID;     
  fStepNum        = stepNum;      
  fSubStepNum     = subStepNum;   
  fParticleName   = particleName; 
  fke             = ke;           
  fx              = x;            
  fy              = y;            
  fz              = z;            

  fTree->Fill();

  clear();
}





