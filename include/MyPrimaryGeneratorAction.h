#ifndef __MyPrimaryGeneratorAction_h__
#define __MyPrimaryGeneratorAction_h__

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4Proton.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

class MyPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction{
    public:

        MyPrimaryGeneratorAction(double energy = 500):G4VUserPrimaryGeneratorAction(){
            fEnergy=energy;

        }
        virtual ~MyPrimaryGeneratorAction(){}

        double fEnergy;

        void GeneratePrimaries(G4Event* anEvent){
            G4ParticleGun* myGun = new G4ParticleGun();

            //myGun->SetParticleDefinition(G4Proton::ProtonDefinition());
            G4ParticleDefinition* particle
              = G4ParticleTable::GetParticleTable()->FindParticle("proton");
            myGun->SetParticleDefinition(particle);

            // Particle Energy
            myGun->SetParticleEnergy(fEnergy*keV);
            // Particle at -10 cm?
            myGun->SetParticlePosition(G4ThreeVector(0.*cm,0.*cm,-9.*cm));
            // Particle going in +x direction
            myGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));

/*
            // random gamma camera
            G4double cosTheta = 2*G4UniformRand() - 1., 
                     phi = 2*CLHEP::pi*G4UniformRand();
            G4double sinTheta = std::sqrt(1. - cosTheta*cosTheta);
            G4double ux = sinTheta*std::cos(phi),
                     uy = sinTheta*std::sin(phi),
                     uz = cosTheta;

            myGun->SetParticleMomentumDirection(G4ThreeVector(ux,uy,uz));

            // Particle Energy
            myGun->SetParticleEnergy(.5*MeV);
*/
            myGun->GeneratePrimaryVertex(anEvent);
        }

};
#endif
