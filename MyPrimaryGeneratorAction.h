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

            // Particle Energy
            myGun->SetParticleEnergy(1.*MeV);
            // Particle at -10 cm?
            myGun->SetParticlePosition(G4ThreeVector(-10,0,0));
            // Particle going in +x direction
            myGun->SetParticleMomentumDirection(G4ThreeVector(1.0,0,0));

            myGun->GeneratePrimaryVertex(anEvent);
        }

};
#endif
