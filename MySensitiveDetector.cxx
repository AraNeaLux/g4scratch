#include "MySensitiveDetector.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"


MySensitiveDetector::MySensitiveDetector(const G4String& name)
  : G4VSensitiveDetector(name){

}


MySensitiveDetector::~MySensitiveDetector(){

}


void MySensitiveDetector::Initialize(G4HCofThisEvent*){

}


G4bool MySensitiveDetector::ProcessHits(G4Step*, G4TouchableHistory*){
  G4cout << "Processing hits ...." << G4endl; 
  return true;
}


void MySensitiveDetector::EndOfEvent(G4HCofThisEvent*){

}
