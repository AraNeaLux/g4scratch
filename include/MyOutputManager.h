#ifndef __MyOutputManager_h__
#define __MyOutputManager_h__

#include <TTree.h>
#include <TFile.h>
#include <TVector3.h>

class MyOutputManager{

  public: 
    static MyOutputManager* Get();

    ~MyOutputManager();
    void setupTree(const char *fname="output.root");
    void closeTree();
    void clear();
    void fill(int eventID,
              int trackID,
              int stepNum,
              int volume,
              std::string particleName,
              int process,
              double ke,
              double edep,
              double stepLen,
              double x,
              double zdep,
              double y,
              double z,
              TVector3 postpos);

  private:
    MyOutputManager();
    static MyOutputManager* fptr;
    TFile *foutput;
    TTree *fTree;

  private:
    int fEventID;
    int fTrackID;
    int fStepNum;
    int fVolume;
    std::string fParticleName;
    int fProcess;
    double fke;
    double fedep;
    double fStepLen;
    double fx;
    double fzdep;
    double fy;
    double fz;
    TVector3 fpostpos;

};




#endif
