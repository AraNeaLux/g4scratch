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
              int volume,
              double ke,
              double x,
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
    int fVolume;
    double fke;
    double fx;
    double fy;
    double fz;

};




#endif
