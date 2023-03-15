#ifndef __EXPERIMENTCONSTUCTION_H__
#define __EXPERIMENTCONSTUCTION_H__

#include <G4UserDetectorConstruction.hh>

class G4PhysicalVolume;

class ExperimentConstruction : public G4UserDetectorConstrution {
  public:
    ExperimentConstuction();  
    ~ExperimentConstuction();  

    virtual G4PhysicalVolume *Constuct();

    void writeGDML();


  private:
    


};


#endif
