#ifndef __MyOutputManager_h__
#define __MyOutputManager_h__

#include <TTree.h>
#include <TFile.h>

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
              int subStepNum,
              std::string particleName,
              int process,
              double ke,
              double edep,
              double x,
              double xdep,
              double y,
              double z);

  private:
    MyOutputManager();
    static MyOutputManager* fptr;
    TFile *foutput;
    TTree *fTree;

  private:
    int fEventID;
    int fTrackID;
    int fStepNum;
    int fSubStepNum;
    std::string fParticleName;
    int fProcess;
    double fke;
    double fedep;
    double fx;
    double fxdep;
    double fy;
    double fz;

};




#endif
