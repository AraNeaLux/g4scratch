#ifndef __TARGET_H__
#define __TARGET_H__

class G4LogicalVolume;
class G4VPhysicalVolume;

class Target {
  public:
    Target(G4LogicalVolume *parent);
    ~Target();

    G4VPhysicalVolume *Construct();

  private:
    G4LogicalVolume *fParent;

};

#endif
