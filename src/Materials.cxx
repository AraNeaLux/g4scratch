
#include "Materials.h"

#include <G4Material.hh>
#include <G4NistManager.hh>

Materials *Materials::fMaterials = 0;


Materials::Materials() { 
  G4NistManager *nist = G4NistManager::Instance();

  fMaterialsMap["Al"] = nist->FindOrBuildMaterial("G4_Al");
  fMaterialsMap["Si"] = nist->FindOrBuildMaterial("G4_Si");
  fMaterialsMap["Ge"] = nist->FindOrBuildMaterial("G4_Ge");

  fMaterialsMap["Zr"] = nist->FindOrBuildMaterial("G4_Zr");
  fMaterialsMap["Ta"] = nist->FindOrBuildMaterial("G4_Ta");
  fMaterialsMap["Pb"] = nist->FindOrBuildMaterial("G4_Pb");

  
  fMaterialsMap["CH2"] = nist->FindOrBuildMaterial("G4_POLYETHYLENE");
  fMaterialsMap["air"] = nist->FindOrBuildMaterial("G4_AIR");
  fMaterialsMap["vac"] = nist->FindOrBuildMaterial("G4_Galactic");
  fMaterialsMap["vacuum"] = nist->FindOrBuildMaterial("G4_Galactic");

}

Materials *Materials::Instance() {
  if(!fMaterials)
    fMaterials = new Materials;
  return fMaterials;

}

Materials::~Materials() { }


G4Material *Materials::Get(std::string name) {
  G4Material *material = Instance()->GetMap()[name];
  if(!material) { 
    // do something smart
    // like search for the material in nist man and
    // put it in the map... (?) 
  }
  return material;

}



