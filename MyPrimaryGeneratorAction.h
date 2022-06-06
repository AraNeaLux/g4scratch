#ifndef __MyPrimaryGeneratorAction_h__
#define __MyPrimaryGeneratorAction_h__

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4Proton.hh"

class MyPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction{
    public:

        void GeneratePrimaries(G4Event* anEvent){
            G4ParticleGun* myGun = new G4ParticleGun();

            myGun->SetParticleDefinition(G4Proton::ProtonDefinition());


            myGun->SetParticleEnergy(50.*keV);
            myGun->SetParticleMomentumDirection(G4ThreeVector(1.0,0,0));

            myGun->GeneratePrimaryVertex(anEvent);
        }

};
#endif
