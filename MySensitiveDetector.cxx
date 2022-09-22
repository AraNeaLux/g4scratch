#include "MySensitiveDetector.h"
#include "MyHit.h"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"


MySensitiveDetector::MySensitiveDetector(const G4String& name,
                                         const G4String& hitsCollectionName)
  : G4VSensitiveDetector(name), fHitsCollection(NULL){
  collectionName.insert(hitsCollectionName);
}


MySensitiveDetector::~MySensitiveDetector(){

}


void MySensitiveDetector::Initialize(G4HCofThisEvent* hce){

  fHitsCollection = new MyTrackerHitsCollection(SensitiveDetectorName, collectionName[0]);

  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection(hcID, fHitsCollection);

}


G4bool MySensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory*){
  //G4cout << "Processing hits ...." << G4endl; 

  MyHit* hit = new MyHit();

  hit->SetPos(aStep->GetPostStepPoint()->GetPosition());

  fHitsCollection->insert(hit);

  hit->Print();

  return true;
}


void MySensitiveDetector::EndOfEvent(G4HCofThisEvent*){

}
