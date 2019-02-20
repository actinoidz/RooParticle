#include "iostream"

#include "TROOT.h"
#include "TVectorT.h"
#include "TVectorD.h"

#include "particle.hpp"

#include <math.h>

using namespace std;

// particle::particle(){
// }

particle::particle(Double_t m0_,
                   // Double_t q_  = 1,
                   TVectorD x0_,
                   TVectorD v0_,
                   Bool_t   Invincible_,
                   Bool_t   Record_){
 m0 = m0_;
 // q  = q_;
 x  = x0_;
 v  = v0_;
 hF = TVectorD(3);
 Invincible = Invincible_;
 if(Record_){
   ppath = new path();
   Record = true;
 }else{
   Record = false;
 }
}

//copy constructor
particle::particle(const particle & p){
  name       = p.name;
  x          = p.x;
  v          = p.v;
  m0         = p.m0;
  Invincible = p.Invincible;
  Record     = p.Record;
  hold       = p.hold;
  hF         = p.hF;
  etime      = p.etime;

  q          = p.q;
}

void particle::holdForce(const TVectorD f){
  if(!hold){
    hold = true;
    hF.Zero();
    // std::cout<<"ZERO"<<endl;
    // hF.Print();
  }
  hF+=f;
}

void particle::releaseForce(const Double_t dt){
  applyForce(hF, dt);
  resetHold();
}

void particle::resetHold(){
  hold=false;
  hF.Zero();
}

void particle::applyForce(const TVectorD f, const Double_t dt){
  if(Invincible==true){
    if(Record==true){
      ppath->AddRecord(x,v, etime);
    }
    return;
  }
  Double_t m_ = GetM(false);
  TVectorD a = f * (1/m_);
  applyDX(
    a * (0.5) * pow(dt,2) + v * dt
  );
  applyDV(
    a * dt
  );
  etime += dt;
  if(Record==true){
    ppath->AddRecord(x,v, etime);}
}

Double_t particle::GetM(Bool_t restmass){
  if(restmass){
  return m0;
  }
  Double_t v_ = sqrt(v.Norm2Sqr());
  return ( 1/sqrt( 1-pow(v_,2) )) * m0;
}
