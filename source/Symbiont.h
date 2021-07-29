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
  /**
    * 
    * Purpose: Represents the interaction value between the host and symbiont. 
    * A negative interaction value represent antagonism, while a positive
    * one represents mutalism. Zero is a neutral value. 
    * 
  */  
  double interaction_val = 0;

  /**
    * 
    * Purpose: Represents the resource points possesed by a symbiont.
    * This is what host's must collect to reproduce. 
    * 
  */     
  double points = 0;

  /**
    * 
    * Purpose: Represents tbe points threshold for horizontal 
    * transmission to occur. 
    * 
  */      
  double sym_h_res = 100;

  /**
    * 
    * Purpose: Represents if horizontal transmission is allowed
    * to occur. 
    * 
  */      
  bool h_trans = true;

  /**
    * 
    * Purpose: Represents tbe standard deviation of the values
    * chosen as mutations of a symbiont's interaction value. 
    * 
  */      
  double mut_size = 0.002;

  /**
    * 
    * Purpose: Represents tbe standard deviation of the values
    * chosen as mutations of a symbiont's interaction value when
    * horizontal transmission is occuring. . 
    * 
  */    
  double ht_mut_size = 0.002;

  /**
    * 
    * Purpose: Represents tbe probability (0-1) of mutation occuring. 
    * 
  */      
  double mut_rate = 0;

  /**
    * 
    * Purpose: Represents tbe probability (0-1) of mutation occuring
    * during horizontal transmission. 
    * 
  */       
  double ht_mut_rate = 0;

  /**
    * 
    * Purpose: Represents if a symbiont is alive. 
    * This is set to false when a symbiont is killed. 
    * 
  */      
  bool dead = false;
  double infection_chance = 0.0;

  /**
    * 
    * Purpose: Represents an instance of random.
    * 
  */     
  emp::Ptr<emp::Random> random = NULL;

  /**
    * 
    * Purpose: Represents the world that the hosts are living in.
    * 
  */     
  emp::Ptr<SymWorld> my_world = NULL;

  /**
    * 
    * Purpose: Represents tbe symbiont's host. 
    * 
  */      
  emp::Ptr<Organism> my_host = NULL;

  /**
    * 
    * Purpose: Represents the configuration settings for a practicular run.
    * 
  */     
  emp::Ptr<SymConfigBase> my_config = NULL;

public:
  /** 
   * The constructor for symbiont
   */
  Symbiont(emp::Ptr<emp::Random> _random, emp::Ptr<SymWorld> _world, emp::Ptr<SymConfigBase> _config, double _intval=0.0, double _points = 0.0) :  interaction_val(_intval), points(_points), random(_random), my_world(_world), my_config(_config) {
    sym_h_res = my_config->SYM_HORIZ_TRANS_RES();
    h_trans = my_config->HORIZ_TRANS();
    mut_rate = my_config->MUTATION_RATE();
    infection_chance = my_config->SYM_INFECTION_CHANCE();
    if(my_config->HORIZ_MUTATION_RATE() < 0){
      ht_mut_rate = mut_rate;
    } else {
      ht_mut_rate = my_config->HORIZ_MUTATION_RATE();
    }
    mut_size = my_config->MUTATION_SIZE();
    if(my_config->HORIZ_MUTATION_SIZE() < 0) {
      ht_mut_size = mut_size;
    } else {
      ht_mut_size = my_config->HORIZ_MUTATION_SIZE();
    }
    if ( _intval > 1 || _intval < -1) {
       throw "Invalid interaction value. Must be between -1 and 1";   // Exception for invalid interaction value
    };
  }


  /**
   * Input:
   * 
   * Output:
   * 
   * Purpose:
   */
  Symbiont(const Symbiont &) = default;


  /**
   * Input:
   * 
   * Output:
   * 
   * Purpose:
   */  
  Symbiont(Symbiont &&) = default;


  /**
   * Input:
   * 
   * Output:
   * 
   * Purpose:
   */
  Symbiont() = default;


  /**
   * Input:
   * 
   * Output:
   * 
   * Purpose:
   */
  Symbiont & operator=(const Symbiont &) = default;


  /**
   * Input:
   * 
   * Output:
   * 
   * Purpose:
   */
  Symbiont & operator=(Symbiont &&) = default;


  /**
   * Input: None
   * 
   * Output: The double representing the symbiont's interaction value
   * 
   * Purpose: To get a symbiont's interaction value.
   */
  double GetIntVal() const {
    return interaction_val;}


  /**
   * Input: None
   * 
   * Output: The double representing the symbiont's points
   * 
   * Purpose: To get a symbiont's points.
   */
  double GetPoints() {return points;}


  /**
   * Input: None
   * 
   * Output: The bool representing if a symbiont is a phage
   * 
   * Purpose: To determine if a symbiont is a phage
   */
  bool IsPhage() {return false;}


  /**
   * Input: None
   * 
   * Output: The bool representing if a symbiont is a host
   * 
   * Purpose: To determine if a symbiont is a host
   */ 
  bool IsHost() {return false;}


 /**
   * Input: 
   * 
   * Output: 
   * 
   * Purpose: 
   */ 
  double GetInfectionChance() {return infection_chance;}


  /**
   * Input: None
   * 
   * Output: The pointer to a symbiont's host
   * 
   * Purpose: To retrive a symbiont's host
   */
  emp::Ptr<Organism> GetHost() {return my_host;}


  //  std::set<int> GetResTypes() const {return res_types;}


  /** 
   * Input: None
   * 
   * Output: None
   * 
   * Purpose: To set a symbiont to dead
   */
  void SetDead() { dead = true; }


  /**
   * Input: None
   * 
   * Output: The bool representing if a symbiont is dead
   * 
   * Purpose: To determine if a symbiont is dead
   */
  bool GetDead() { return dead; }


  /**
   * Input: The double representing the new interaction value of a symbiont 
   * 
   * Output: None
   * 
   * Purpose: To set a symbiont's interaction value
   */
  void SetIntVal(double _in) {
    if ( _in > 1 || _in < -1) {
       throw "Invalid interaction value. Must be between -1 and 1";   // Exception for invalid interaction value
     }
     else {
        interaction_val = _in;
     }
  }


  /**
   * Input: The double representing the points to be set as a symbinot's points
   * 
   * Output: None
   * 
   * Purpose: To set a symbiont's points
   */
  void SetPoints(double _in) {points = _in;}


  /**
   * Input: The double representing the points to be added to a symbinot's points
   * 
   * Output: None
   * 
   * Purpose: To increment a symbiont's points
   */
  void AddPoints(double _in) { points += _in;}


  /**
   * Input: The pointer to an organism that will be set as the symbinot's host
   * 
   * Output: None
   * 
   * Purpose: To set a symbiont's host
   */
  void SetHost(emp::Ptr<Organism> _in) {my_host = _in;}
  void SetInfectionChance(double _in) {
    if(_in > 1 || _in < 0) throw "Invalid infection chance. Must be between 0 and 1 (inclusive)";
    else infection_chance = _in;
  }

  //void SetResTypes(std::set<int> _in) {res_types = _in;}


  /**
   * Input: None
   * 
   * Output: None
   * 
   * Purpose: Does nothing for now, added for backwards compatibility from phage to symbiont
   */
  void uponInjection(){
    //does nothing for now, added for backwards compatibility from phage to symbiont
  }


  /**
   * Input: None
   * 
   * Output: None
   * 
   * Purpose: To mutate an symbiont's interaction value. The mutation value is choosen 
   * from a normal distribution centered on 0 with the mutation size as the standard
   * deviation. 
   */
  void mutate(){
    //TODO: change everything to camel case
    // double pre_value = interaction_val;
    if (random->GetDouble(0.0, 1.0) <= mut_rate) {
      interaction_val += random->GetRandNormal(0.0, mut_size);
      if(interaction_val < -1) interaction_val = -1;
      else if (interaction_val > 1) interaction_val = 1;

      //also modify infection chance, which is between 0 and 1
      if(my_config->FREE_LIVING_SYMS()){
        infection_chance += random->GetRandNormal(0.0, mut_size);
        if (infection_chance < 0) infection_chance = 0;
        else if (infection_chance > 1) infection_chance = 1;
      }
    }
    //if((pre_value*interaction_val) < 0) {
    //  std::cout << "switched2!" << std::endl;
    //}
  }


  /**
   * Input: None
   * 
   * Output: None
   * 
   * Purpose: To mutate an symbiont's interaction value based upon the horizontal mutation size. 
   * This is a function to be called during horizontal transmission.
   */
  void HorizMutate(){
    // double pre_value = interaction_val;
    if (random->GetDouble(0.0, 1.0) <= ht_mut_rate) {
      interaction_val += random->GetRandNormal(0.0, ht_mut_size);
      if(interaction_val < -1) interaction_val = -1;
      else if (interaction_val > 1) interaction_val = 1;

      if(my_config->FREE_LIVING_SYMS()){
        infection_chance += random->GetRandNormal(0.0, ht_mut_size);
        if (infection_chance < 0) infection_chance = 0;
        else if (infection_chance > 1) infection_chance = 1;
      }
    }
  }


/**
   * Input: The double representing the resources to be distributed to the symbionts
   * 
   * Output: The double representing the host's resources
   * 
   * Purpose: To process and distribute resources.
   */
  double ProcessResources(double hostDonation){
    double sym_int_val = GetIntVal();
    double sym_portion = 0;
    double host_portion = 0;
    double synergy = my_config->SYNERGY();

    if (sym_int_val<0){
      double stolen = my_host->StealResources(sym_int_val);
      host_portion = 0;
      sym_portion = stolen + hostDonation;
    }
    else if (sym_int_val >= 0){
      host_portion = hostDonation * sym_int_val;
      sym_portion = hostDonation - host_portion;
    }
    AddPoints(sym_portion);
    return host_portion * synergy;
  }


  /**
   * Input:
   * 
   * Output:
   * 
   * Purpose:
   */
  bool WantsToInfect(){
    bool result = random->GetDouble(0.0, 1.0) < infection_chance;
    return result;
  }


  /**
   * Input: The size_t representing the location of the symbiont. 
   * 
   * Output: None
   * 
   * Purpose: To process a symbiont, meaning to check for reproduction, distribute resources, 
   * and to allow for movement 
   */
  void Process(size_t location) {
    if (my_host.IsNull() && my_config->FREE_LIVING_SYMS()) { //free living symbiont
      double resources = my_world->PullResources();
      AddPoints(resources);
    }

    if (h_trans) { //non-lytic horizontal transmission enabled
      if(GetPoints() >= sym_h_res) {
        // symbiont reproduces independently (horizontal transmission) if it has enough resources
        // new symbiont in this host with mutated value
        SetPoints(0); //TODO: test just subtracting points instead of setting to 0
        emp::Ptr<Symbiont> sym_baby = emp::NewPtr<Symbiont>(*this);
        sym_baby->SetPoints(0);
        sym_baby->HorizMutate();
        //HorizMutate();
        my_world->SymDoBirth(sym_baby, location);
      }
    }
    if (my_host.IsNull() && my_config->FREE_LIVING_SYMS()) {
      my_world->MoveFreeSym(location);
    }
  }


  /**
   * Input: None
   * 
   * Output: The pointer to the newly created organism
   * 
   * Purpose: To produce a new symbiont
   */
  emp::Ptr<Organism> reproduce() {
    emp::Ptr<Symbiont> sym_baby = emp::NewPtr<Symbiont>(*this); //constructor that takes parent values
    sym_baby->SetPoints(0);
    sym_baby->mutate();
    //mutate(); //mutate parent symbiont
    return sym_baby;
  }

  /**
   * Input: The pointer to the organism that is the new host baby
   * 
   * Output: None
   * 
   * Purpose: To allow for vertical transmission to occur 
   */
  void VerticalTransmission(emp::Ptr<Organism> host_baby) {
    if(my_world->WillTransmit()){
      emp::Ptr<Organism> sym_baby = reproduce();
      host_baby->AddSymbiont(sym_baby);
    }
  }
}; 
#endif