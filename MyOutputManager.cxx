#include "MyOutputManager.h"
#include <cstdio>
#include <TVector3.h>

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
  fTree->Branch("Process",      &fProcess);     
  fTree->Branch("ke",           &fke);           
  fTree->Branch("edep",         &fedep);           
  fTree->Branch("x",            &fx);            
  fTree->Branch("xdep",         &fxdep);            
  fTree->Branch("y",            &fy);            
  fTree->Branch("z",            &fz);            
  fTree->Branch("postpos",      &fpostpos);            

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
  fProcess      = -1;
  fke           = sqrt(-1); 
  fedep         = sqrt(-1); 
  fx            = sqrt(-1); 
  fxdep         = sqrt(-1); 
  fy            = sqrt(-1); 
  fz            = sqrt(-1); 

}

void MyOutputManager::fill(int eventID,
                           int trackID,
                           int stepNum,
                           int subStepNum,
                           std::string particleName,
                           int process,
                           double ke,
                           double edep,
                           double x,
                           double xdep,
                           double y,
                           double z,
                           TVector3 postpos){
  fEventID        = eventID;     
  fTrackID        = trackID;     
  fStepNum        = stepNum;      
  fSubStepNum     = subStepNum;   
  fParticleName   = particleName; 
  fProcess        = process;
  fke             = ke;           
  fedep           = edep;           
  fx              = x;            
  fxdep           = xdep;            
  fy              = y;            
  fz              = z;            
  fpostpos        = postpos;            

  fTree->Fill();

  clear();
}





