//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file electromagnetic/TestEm1/include/StepMax.hh
/// \brief Definition of the StepMax class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef __MyStepMax_h__
#define __MyStepMax_h__

#include "globals.hh"
#include "G4VDiscreteProcess.hh"
#include "G4ParticleDefinition.hh"
#include "G4Step.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class MyStepMax : public G4VDiscreteProcess
{
  public:

    G4double fMaxChargedStep;

    MyStepMax(const G4String& processName = "UserMaxStep")
    :G4VDiscreteProcess(processName),fMaxChargedStep(DBL_MAX){};

    ~MyStepMax(){};

    virtual G4bool IsApplicable(const G4ParticleDefinition& particle){
      return (particle.GetPDGCharge() != 0. && !particle.IsShortLived());
    };

    void SetMaxStep(G4double step = 0.05){
      fMaxChargedStep = step;
    };

    G4double GetMaxStep() {return fMaxChargedStep;};

    virtual G4double PostStepGetPhysicalInteractionLength(const G4Track& track,
                                               G4double previousStepSize,
                                               G4ForceCondition* condition){
      *condition = NotForced;
      return fMaxChargedStep;
    };

    virtual G4VParticleChange* PostStepDoIt(const G4Track& aTrack, const G4Step&){
      // do nothing
      aParticleChange.Initialize(aTrack);
      return &aParticleChange;
    };

    virtual G4double GetMeanFreePath(const G4Track&,G4double,G4ForceCondition*)
    {return DBL_MAX;};    

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

