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
    * one represents mutualism. Zero is a neutral value.
    *
  */
  double interaction_val = 0;

  /**
    *
    * Purpose: Represents the resource points possessed by a symbiont.
    * This is what host's must collect to reproduce.
    *
  */
  double points = 0;

  /**
    *
    * Purpose: Represents if a symbiont is alive.
    * This is set to true when a symbiont is killed.
    *
  */
  bool dead = false;

  /**
    *
    * Purpose: Represents the chance (between 0 and 1) that
    * a free-living sym will infect a parallel host on process
    *
  */
  double infection_chance = 0.0;

  /**
    *
    * Purpose: Represents the number of updates the symbiont
    * has lived through; at birth is set to 0.
    *
  */
  int age = 0;

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
    * Purpose: Represents the symbiont's host.
    *
  */
  emp::Ptr<Organism> my_host = NULL;

  /**
    *
    * Purpose: Represents the configuration settings for a particular run.
    *
  */
  emp::Ptr<SymConfigBase> my_config = NULL;

  /**
    *
    * Purpose: Tracks the taxon of this organism.
    *
  */
  emp::Ptr<emp::Taxon<int>> my_taxon = NULL;

public:
  /**
   * The constructor for symbiont
   */
  Symbiont(emp::Ptr<emp::Random> _random, emp::Ptr<SymWorld> _world, emp::Ptr<SymConfigBase> _config, double _intval=0.0, double _points = 0.0) :  interaction_val(_intval), points(_points), random(_random), my_world(_world), my_config(_config) {
    infection_chance = my_config->SYM_INFECTION_CHANCE();
    if (infection_chance == -2) infection_chance = random->GetDouble(0,1); //randomized starting infection chance
    if (infection_chance > 1 || infection_chance < 0) throw "Invalid infection chance. Must be between 0 and 1"; //exception for invalid infection chance

    if ( _intval > 1 || _intval < -1) {
       throw "Invalid interaction value. Must be between -1 and 1";   // Exception for invalid interaction value
    };
  }


  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To force a copy constructor to be generated by the compiler.
   */
  Symbiont(const Symbiont &) = default;


  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To force a move constructor to be generated by the compiler
   */
  Symbiont(Symbiont &&) = default;


  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To tell the compiler to use its default generated variants of the constructor
   */
  Symbiont() = default;


  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To force a copy assignment operator to be generated by the compiler.
   */
  Symbiont & operator=(const Symbiont &) = default;


  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To force a move assignment operator to be generated by the compiler.
   */
  Symbiont & operator=(Symbiont &&) = default;

  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To destruct the symbiont and remove the symbiont from the systematic.
   */
  ~Symbiont() {
    if(my_config->PHYLOGENY() == 1) {my_world->GetSymSys()->RemoveOrg(my_taxon);}
  }

    /**
    * Input: None
    * 
    * Output: Name of class as string, Symbiont
    *
    * Purpose: To know which subclass the object is
    */
    std::string const GetName() {
      return  "Symbiont";
    }


  /**
   * Input: None
   *
   * Output: The double representing the symbiont's interaction value
   *
   * Purpose: To get a symbiont's interaction value.
   */
  double GetIntVal() const {return interaction_val;}


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
   * Input: None
   *
   * Output: The chance of a symbiont infecting a parallel
   * host during process
   *
   * Purpose: To determine a symbiont's infection chance
   */
  double GetInfectionChance() {return infection_chance;}


  /**
   * Input: None
   *
   * Output: The pointer to a symbiont's host
   *
   * Purpose: To retrieve a symbiont's host
   */
  emp::Ptr<Organism> GetHost() {return my_host;}


  /**
   * Input: None
   *
   * Output: The pointer to the symbiont's taxon
   *
   * Purpose: To retrieve the symbiont's taxon
   */
   emp::Ptr<emp::Taxon<int>> GetTaxon() {return my_taxon;}

   /**
    * Input: A pointer to the taxon that this organism should belong to.
    *
    * Output: None
    *
    * Purpose: To set the symbiont's taxon
    */
   void SetTaxon(emp::Ptr<emp::Taxon<int>> _in) {my_taxon = _in;}

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
   * Input: None
   *
   * Output: an int representing the current age of the Symbiont
   *
   * Purpose: To get the Symbiont's age.
   */
  int GetAge() {return age;}

  /**
   * Input: An int of what age the Symbiont should be set to
   *
   * Output: None
   *
   * Purpose: To set the Symbiont's age for testing purposes.
   */
  void SetAge(int _in) {age = _in;}

  /**
   * Input: The pointer to an organism that will be set as the symbinot's host
   *
   * Output: None
   *
   * Purpose: To set a symbiont's host
   */
  void SetHost(emp::Ptr<Organism> _in) {my_host = _in;}

  /**
   * Input: The double that will be the symbiont's infection chance
   *
   * Output: None
   *
   * Purpose: To set a symbiont's infection host and check that the proposed value is valid.
   */
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
  void UponInjection(){
    //does nothing for now, added for backwards compatibility from phage to symbiont
  }

  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: Increments age by one and kills it if too old.
   */
  void GrowOlder(){
    age = age + 1;
    if(age > my_config->SYM_AGE_MAX() && my_config->SYM_AGE_MAX() > 0){
      SetDead();
    }
  }


  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To mutate a symbiont's interaction value. The mutation value is chosen
   * from a normal distribution centered on 0 with the mutation size as the standard
   * deviation.
   */
  void Mutate(){
    double local_rate = my_config->MUTATION_RATE();
    double local_size = my_config->MUTATION_SIZE();

    if (random->GetDouble(0.0, 1.0) <= local_rate) {
      interaction_val += random->GetNormal(0.0, local_size);
      if(interaction_val < -1) interaction_val = -1;
      else if (interaction_val > 1) interaction_val = 1;

      //also modify infection chance, which is between 0 and 1
      if(my_config->FREE_LIVING_SYMS()){
        infection_chance += random->GetNormal(0.0, local_size);
        if (infection_chance < 0) infection_chance = 0;
        else if (infection_chance > 1) infection_chance = 1;
      }
    }
  }

  /**
   * Input: The double representing the resources to be distributed to the symbiont
   * and (optionally) the host from whom it comes; if no host is provided, the
   * symbiont's host variable is used.
   *
   * Output: The double representing the host's resources
   *
   * Purpose: To process and distribute resources.
   */
  double ProcessResources(double host_donation, emp::Ptr<Organism> host = nullptr){
    if(host == nullptr){
      host = my_host;
    }
    double sym_int_val = GetIntVal();
    double sym_portion = 0;
    double host_portion = 0;
    double synergy = my_config->SYNERGY();

    if (sym_int_val<0){
      double stolen = host->StealResources(sym_int_val);
      host_portion = 0;
      sym_portion = stolen + host_donation;
    }
    else if (sym_int_val >= 0){
      host_portion = host_donation * sym_int_val;
      sym_portion = host_donation - host_portion;
    }
    AddPoints(sym_portion);
    return host_portion * synergy;
  }


  /**
   * Input: None
   *
   * Output: The boolean representing if a symbiont
   * will seek out to infect a host.
   *
   * Purpose: To determine if a symbiont wants to
   * infect a host based upon its infection chance
   */
  bool WantsToInfect(){
    bool result = random->GetDouble(0.0, 1.0) < infection_chance;
    return result;
  }


  /**
   * Input: None
   *
   * Output: The boolean representing if a symbiont
   * will survive crossing over into the host world.
   *
   * Purpose: To determine if a symbiont will survive
   * crossing over into the host world based on infection risk.
   */
  bool InfectionFails(){
    //note: this can be returned true, and an infecting sym can then be killed by a host that is already infected.
    bool sym_dies = random->GetDouble(0.0, 1.0) < my_config->SYM_INFECTION_FAILURE_RATE();
    return sym_dies;
  }

  /**
   * Input: The double representing the resources given by the world.
   *
   * Output: None
   *
   * Purpose:  Free living symbionts specialized to interact with hosts
   * (extreme interaction value in either direction) lose some of the resources that they get from the world.
   */
  void LoseResources(double resources){
    double int_val = interaction_val;
    if(my_host.IsNull()) { // this method should only be called on free-living syms, but double check!

      if(int_val >= 0){
	      double spent = resources * int_val;
        this->AddPoints(resources - spent);
      }
      else {
        double attack = -1.0 * int_val * resources;
        this->AddPoints(resources - attack);
      }
    }
  }

  /**
   * Input: The size_t representing the location of the symbiont, and the size_t
   * representation of the symbiont's position in the host (default -1 if it doesn't have a host)
   *
   * Output: None
   *
   * Purpose: To process a symbiont, meaning to check for reproduction, distribute resources,
   * and to allow for movement
   */
   //size_t rank=-1
  void Process(emp::WorldPosition location) {
    //ID is where they are in the world, INDEX is where they are in the host's symbiont list (or 0 if they're free living)
    if (my_host.IsNull() && my_config->FREE_LIVING_SYMS()) { //free living symbiont
      double resources = my_world->PullResources(my_config->FREE_SYM_RES_DISTRIBUTE()); //receive resources from the world
      LoseResources(resources);
    }
    //Check if horizontal transmission can occur and do it
    HorizontalTransmission(location);
    //Age the organism
    GrowOlder();
    //Check if the organism should move and do it
    if (my_host.IsNull() && my_config->FREE_LIVING_SYMS() && !dead) {
      //if the symbiont should move, and hasn't been killed
      my_world->MoveFreeSym(location);
    }
  }

  /**
   * Input: None
   *
   * Output: The pointer to the newly created organism
   *
   * Purpose: To produce a new symbiont, identical to the original
   */
  emp::Ptr<Organism> MakeNew() {
    emp::Ptr<Symbiont> new_sym = emp::NewPtr<Symbiont>(random, my_world, my_config, GetIntVal());
    new_sym->SetInfectionChance(GetInfectionChance());
    return new_sym;
  }

  /**
   * Input: None
   *
   * Output: The pointer to the newly created organism
   *
   * Purpose: To produce a new symbiont; does not remove resources from the parent, assumes that is handled by calling function
   */
  emp::Ptr<Organism> Reproduce() {
    emp::Ptr<Organism> sym_baby = MakeNew();
    sym_baby->Mutate();

    if(my_config->PHYLOGENY() == 1){
      my_world->AddSymToSystematic(sym_baby, my_taxon);
      //baby's taxon will be set in AddSymToSystematic
    }
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
    if((my_world->WillTransmit()) && GetPoints() >= my_config->SYM_VERT_TRANS_RES()){ //if the world permits vertical tranmission and the sym has enough resources, transmit!
      emp::Ptr<Organism> sym_baby = Reproduce();
      points = points - my_config->SYM_VERT_TRANS_RES();
      host_baby->AddSymbiont(sym_baby);

      //vertical transmission data node
      emp::DataMonitor<int>& data_node_attempts_verttrans = my_world->GetVerticalTransmissionAttemptCount();
      data_node_attempts_verttrans.AddDatum(1);
    }
  }

  /**
   * Input: The location of the organism (and it's Host) as a size_t
   *
   * Output: None
   *
   * Purpose: To check and allow for horizontal transmission to occur
   */
  void HorizontalTransmission(emp::WorldPosition location) {
    if (my_config->HORIZ_TRANS()) { //non-lytic horizontal transmission enabled
      if(GetPoints() >= my_config->SYM_HORIZ_TRANS_RES()) {
        // symbiont reproduces independently (horizontal transmission) if it has enough resources
        //TODO: try just subtracting points to be consistent with vertical transmission
        //points = points - my_config->SYM_HORIZ_TRANS_RES();
        SetPoints(0);
        emp::Ptr<Organism> sym_baby = Reproduce();
        emp::WorldPosition new_pos = my_world->SymDoBirth(sym_baby, location);

        //horizontal transmission data nodes
        emp::DataMonitor<int>& data_node_attempts_horiztrans = my_world->GetHorizontalTransmissionAttemptCount();
        data_node_attempts_horiztrans.AddDatum(1);

        emp::DataMonitor<int>& data_node_successes_horiztrans = my_world->GetHorizontalTransmissionSuccessCount();
        if(new_pos.IsValid()){
          data_node_successes_horiztrans.AddDatum(1);
        }
      }
    }
  }
};
#endif
