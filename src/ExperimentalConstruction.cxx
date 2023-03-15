
#include "ExperimentConstruction.h"
#include "ExperimentalHall.h"

ExperimentConstruction::ExperimentConstruction() { }


ExperimentConstruction::~ExperimentConstruction() { }

G4VPhysicalVolume *ExperimentConstruction::Construct() {
  
  ExperimentalHall *expHall = new ExperimentalHall();
  expHall->Construct();

  return expHall->GetPhysical();
}

void ExperimentConstruction::writeGDML() { }

