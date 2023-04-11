
#include "ExperimentConstruction.h"
#include "ExperimentalHall.h"
#include "Target.h"
#include "DetectorSi.h"

#include <G4GDMLParser.hh>

#include <fstream>
#include <cstdio>
 
ExperimentConstruction::ExperimentConstruction() { }


ExperimentConstruction::~ExperimentConstruction() { }

G4VPhysicalVolume *ExperimentConstruction::Construct() {
  
  fExpHall = new ExperimentalHall();
  fExpHall->Construct();
  
  Target *target = new Target(fExpHall->GetLogical());
  target->Construct();

  DetectorSi *detectorSi = new DetectorSi(fExpHall->GetLogical());
  detectorSi->Construct();

  return fExpHall->GetPhysical();
}

void ExperimentConstruction::writeGDML(std::string ofile) {
  G4GDMLParser parser;
  std::ifstream file(ofile);
  bool erase = file.good();
  file.close();
  if(erase) 
    std::remove(ofile.c_str());

  printf("here!\t0x%08x\n",(unsigned int*)GetHall());
  //std::cout << "here!\t" << ((unsigned long*)GetHall()->GetPhysical()) <<  std::endl;

  parser.Write(ofile,GetHall()->GetPhysical());

}

