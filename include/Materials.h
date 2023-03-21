#ifndef __MATERIALS_H__
#define __MATERIALS_H__

#include<map>
#include<string>


class G4Material;

class Materials {
  private:
    static Materials *fMaterials; 
    Materials();

  public:
    static Materials *Instance(); 
    ~Materials();

    static G4Material *Get(std::string name);
    std::map<std::string,G4Material*> GetMap() const { return fMaterialsMap; } 

  private:

    std::map<std::string,G4Material*> fMaterialsMap;      
    
};


#endif

