
#include "Materials.h"

Materials *Materials::fMaterials = 0;

Materials::Materials() { }

Materials *Materials::Get() {
  if(!fMaterials)
    fMaterials = new Materials;
  return fMaterials;

}

Materials::~Materials() { }
