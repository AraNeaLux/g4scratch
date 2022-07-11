#ifndef __MyPhysicsList_h__
#define __MyPhysicsList_h__

#include "G4VModularPhysicsList.hh"
#include "G4PhysicsListHelper.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"

#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"
/*
#include "G4DecayPhysics.hh" 
#include "G4EmStandardPhysics.hh" 
#include "G4EmExtraPhysics.hh" 
#include "G4IonPhysics.hh" 
#include "G4StoppingPhysics.hh" 
#include "G4HadronElasticPhysics.hh" 
#include "G4NeutronTrackingCut.hh"
#include "G4HadronPhysicsFTFP_BERT.hh"
*/
#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option1.hh"
#include "G4EmStandardPhysics_option2.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4EmLowEPPhysics.hh"

#include "G4Decay.hh"
#include "G4DecayPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronElasticPhysicsXS.hh"
#include "G4HadronDElasticPhysics.hh"
#include "G4HadronHElasticPhysics.hh"
#include "G4HadronInelasticQBBC.hh"

#include "G4StepLimiterPhysics.hh"
#include "MyStepMax.h"
#include "G4ProcessManager.hh"

#include <cstdio>


class G4VPhysicsConstructor;

class MyPhysicsList: public G4VModularPhysicsList{

  public:
    MyPhysicsList() : G4VModularPhysicsList(){

      int ver = 1;
      this->SetVerboseLevel(ver);

      this->defaultCutValue = 0.7*CLHEP::mm;
/*
      this->RegisterPhysics( new G4EmStandardPhysics(ver));
      this->RegisterPhysics( new G4EmExtraPhysics(ver) );
      this->RegisterPhysics( new G4DecayPhysics(ver) );
      this->RegisterPhysics( new G4HadronElasticPhysics(ver) );
      this->RegisterPhysics( new G4HadronPhysicsFTFP_BERT(ver));
      this->RegisterPhysics( new G4StoppingPhysics(ver) );
      this->RegisterPhysics( new G4IonPhysics(ver));
      this->RegisterPhysics( new G4NeutronTrackingCut(ver));
*/



    }

    ~MyPhysicsList(){} 

    void ConstructParticle(){

      G4BosonConstructor  pBosonConstructor;
      pBosonConstructor.ConstructParticle();
   
      G4LeptonConstructor pLeptonConstructor;
      pLeptonConstructor.ConstructParticle();
   
      G4MesonConstructor pMesonConstructor;
      pMesonConstructor.ConstructParticle();
   
      G4BaryonConstructor pBaryonConstructor;
      pBaryonConstructor.ConstructParticle();
   
      G4IonConstructor pIonConstructor;
      pIonConstructor.ConstructParticle();
   
      G4ShortLivedConstructor pShortLivedConstructor;
      pShortLivedConstructor.ConstructParticle();
    }

 
    void ConstructProcess(){
      AddTransportation();

      //G4VPhysicsConstructor *EMPhysicsList = new G4EmStandardPhysics();
      //G4VPhysicsConstructor *EMPhysicsList = new G4EmStandardPhysics_option1();
      //G4VPhysicsConstructor *EMPhysicsList = new G4EmStandardPhysics_option2();
      //G4VPhysicsConstructor *EMPhysicsList = new G4EmStandardPhysics_option3();
      G4VPhysicsConstructor *EMPhysicsList = new G4EmStandardPhysics_option4();
      //G4VPhysicsConstructor *EMPhysicsList = new G4EmLivermorePhysics();
      //G4VPhysicsConstructor *EMPhysicsList = new G4EmPenelopePhysics();
      //G4VPhysicsConstructor *EMPhysicsList = new G4EmLowEPPhysics();



      EMPhysicsList->ConstructProcess();

      G4VPhysicsConstructor *DecayPhysicsList = new G4DecayPhysics();
      DecayPhysicsList->ConstructProcess();
      
      G4VPhysicsConstructor *HadronElasticPhysicsList = new G4HadronElasticPhysicsXS();
      HadronElasticPhysicsList->ConstructProcess();

      //G4StepLimiterPhysics* stepLimitPhys = new G4StepLimiterPhysics();
      //RegisterPhysics(stepLimitPhys);

      MyStepMax* stepMaxProcess = new MyStepMax();

      auto particleIterator=GetParticleIterator();
      particleIterator->reset();
      while ((*particleIterator)()){
        G4ParticleDefinition* particle = particleIterator->value();
        G4ProcessManager* pmanager = particle->GetProcessManager();
        //G4cout << particle->GetParticleName() << G4endl;
          
        if (stepMaxProcess->IsApplicable(*particle)){
          pmanager ->AddDiscreteProcess(stepMaxProcess);
          //stepMaxProcess->SetMaxStep();
          //G4cout << particle->GetParticleName() << G4endl;
        }
      }

    } 


    void SetCuts(){
      this->SetCutsWithDefault();
    };

};
#endif
