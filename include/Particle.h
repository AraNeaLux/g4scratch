#ifndef __PARTICLE_H__
#define __PARTICLE_H__

class Particle {

  public:
    Particle()  { }
    ~Particle() { }

  private:
    int fA;
    int fZ;

    double fEx  //= 0.*CLHEP::MeV;
    double fTau //= 0.*CLHEP::ps;
    double fKE  //= 100*MeV;
    

};


class Projectile : public Particle {
  public:
    Projectile()  { }
    ~Projectile() { }

  private:
    

};


class Recoil : public Particle {
  public:
    Projectile()  { }
    ~Projectile() { }

  private:
    

};

#endif
