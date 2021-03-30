#ifndef SYMBIONT_H
#define SYMBIONT_H

#include "../../Empirical/include/emp/math/Random.hpp"
#include "../../Empirical/include/emp/tools/string_utils.hpp"
#include "SymWorld.h"
#include <set>
#include <iomanip> // setprecision
#include <sstream> // stringstream


class Symbiont: public Organism {
protected:  
  double interaction_val;
  double points;
  double sym_h_res = 100;
  bool h_trans = true;
  double mut_size = 0.002;
  double ht_mut_size = 0.002;
  double mut_rate = 0.1;
  emp::Ptr<emp::Random> random;
  emp::Ptr<SymWorld> my_world;
  emp::Ptr<Organism> my_host = new Organism(); //need to clean up this memory still

public:

  Symbiont(emp::Ptr<emp::Random> _random, emp::Ptr<SymWorld> _world, double _intval=0.0,
   double _points = 0.0, double _h_res = 100.0, bool _h_trans = true, 
   double _mut_size = 0.002) : interaction_val(_intval), points(_points), 
   random(_random), my_world(_world), sym_h_res(_h_res), h_trans(_h_trans), 
   mut_size(_mut_size) {
     if ( _intval > 1 || _intval < -1) {
       throw "Invalid _intval. Must be between -1 and 1";   // NEW
     };
  }
  Symbiont(const Symbiont &) = default;
  Symbiont(Symbiont &&) = default;


  Symbiont & operator=(const Symbiont &) = default;
  Symbiont & operator=(Symbiont &&) = default;

  double GetIntVal() const {return interaction_val;}
  double GetPoints() {return points;}
  //  std::set<int> GetResTypes() const {return res_types;}



  void SetIntVal(double _in) { 
    if ( _in > 1 || _in < -1) {
       throw "Invalid _in. Must be between -1 and 1";   // NEW
     }
     else {
        interaction_val = _in;
     }
       
  }
  
  void SetPoints(double _in) { points = _in;}
  void AddPoints(double _in) { points += _in;}
  void SetHost(emp::Ptr<Organism> _in) {my_host = _in;}
  //void SetResTypes(std::set<int> _in) {res_types = _in;}

  bool WillMutate() {
    bool result = random->GetDouble(0.0, 1.0) <= mut_rate;
    return result;

  }

  //TODO: change everything to camel case
  void mutate(){
    interaction_val += random->GetRandNormal(0.0, mut_size);
    if(interaction_val < -1) interaction_val = -1;
    else if (interaction_val > 1) interaction_val = 1;
  }

  void HorizMutate(){
    interaction_val += random->GetRandNormal(0.0, ht_mut_size);
    if(interaction_val < -1) interaction_val = -1;
    else if (interaction_val > 1) interaction_val = 1;
  }

  void process(size_t location) {
    bool will_mutate = WillMutate();
    if (h_trans) { //non-lytic horizontal transmission enabled
      if(GetPoints() >= sym_h_res) {
        // symbiont reproduces independently (horizontal transmission) if it has >= 100 resources (by default)
        // new symbiont in this host with mutated value
        SetPoints(0); //TODO: test just subtracting points instead of setting to 0
        emp::Ptr<Symbiont> sym_baby = new Symbiont(*this);
        sym_baby->SetPoints(0);
        if (will_mutate) {
          sym_baby->HorizMutate();
          HorizMutate();
        }
        
        my_world->SymDoBirth(sym_baby, location);

      }
    }
  }

  emp::Ptr<Organism> reproduce() {
    emp::Ptr<Symbiont> sym_baby = new Symbiont(*this); //constructor that takes parent values                                             
    sym_baby->SetPoints(0);
    sym_baby->mutate();
    mutate(); //mutate parent symbiont
    return sym_baby;
  }
  


};

std::string PrintSym(emp::Ptr<Symbiont>  org){
  if (org->GetPoints() < 0) return "-";
  double out_val = org->GetIntVal();  
  
  // this prints the symbiont with two decimal places for easier reading
  std::stringstream temp;
  temp << std::fixed << std::setprecision(2) << out_val;
  std::string formattedstring = temp.str();
  return formattedstring;
  
  // return emp::to_string(out_val);  // creates a string without specifying format
}//Symbiont
#endif