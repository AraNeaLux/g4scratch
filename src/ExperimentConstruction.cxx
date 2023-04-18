
#include "ExperimentConstruction.h"
#include "ExperimentalHall.h"
#include "Target.h"
#include "VacChamber.h"
#include "DetectorSi.h"
#include "DetectorGe.h"
#include "MySensitiveDetector.h"

#include <G4GDMLParser.hh>
#include <G4SDManager.hh>

#include <fstream>
#include <cstdio>
 
ExperimentConstruction::ExperimentConstruction() { }


ExperimentConstruction::~ExperimentConstruction() { }

G4VPhysicalVolume *ExperimentConstruction::Construct() {
  
  fExpHall = new ExperimentalHall();
  fExpHall->Construct();
  
  Target *target = new Target(fExpHall->GetLogical());
  target->Construct();

  //VacChamber *vacChamber = new VacChamber(fExpHall->GetLogical());
  //vacChamber->Construct();

  DetectorSi *detectorSi = new DetectorSi(fExpHall->GetLogical(),10,45);
  detectorSi->Construct();

  detectorSi = new DetectorSi(fExpHall->GetLogical(),10,-45);
  detectorSi->Construct();

  DetectorGe *detectorGe = new DetectorGe(fExpHall->GetLogical(),20,135);
  detectorGe->Construct();

  detectorGe = new DetectorGe(fExpHall->GetLogical(),20,-135);
  detectorGe->Construct();

  detectorGe = new DetectorGe(fExpHall->GetLogical(),20,45);
  detectorGe->Construct();

  detectorGe = new DetectorGe(fExpHall->GetLogical(),20,-45);
  detectorGe->Construct();

  return fExpHall->GetPhysical();
}

void ExperimentConstruction::ConstructSDandField() {

  G4SDManager *SDman = G4SDManager::GetSDMpointer();

  G4String SDname = "detectorSi_l";
  G4String HCname = "HCnameSi";
  MySensitiveDetector* SDSi = new MySensitiveDetector(SDname,HCname);
  SDman->GetSDMpointer()->AddNewDetector(SDSi);
  SetSensitiveDetector(SDname,SDSi,true);

  G4cout << "Added detectorSi SD" << G4endl;

  SDname = "detectorGe_l";
  HCname = "HCnameGe";
  MySensitiveDetector* SDGe = new MySensitiveDetector(SDname,HCname);
  SDman->GetSDMpointer()->AddNewDetector(SDGe);
  SetSensitiveDetector(SDname,SDGe,true);

  G4cout << "Added detectorGe SD" << G4endl;
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

