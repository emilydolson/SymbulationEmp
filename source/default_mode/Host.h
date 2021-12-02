#ifndef HOST_H
#define HOST_H
 
#include "../../../Empirical/include/emp/math/Random.hpp"
#include "../../../Empirical/include/emp/tools/string_utils.hpp"
#include <set>
#include <iomanip> // setprecision
#include <sstream> // stringstream
#include "../Organism.h"
#include "../SymWorld.h"


class Host: public Organism {


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
    * Purpose: Represents the number of updates the host
    * has lived through; at birth is set to 0.
    *
  */
  int age = 0;

  /**
    *
    * Purpose: Represents the set of symbionts belonging to a host.
    * This can be set with SetSymbionts(), and symbionts can be
    * added with AddSymbiont(). This can be cleared with ClearSyms()
    *
  */
  emp::vector<emp::Ptr<Organism>> syms = {};

  /**
    *
    * Purpose: Represents the set of repro symbionts belonging to a host.
    * Symbionts can be added with AddReproSymb(). This can be cleared with ClearSyms()
    *
  */
  emp::vector<emp::Ptr<Organism>> repro_syms = {};

  /**
    *
    * Purpose: Represents the resource type available to hosts.
    * This is currently not implemented fully.
    *
  */
  std::set<int> res_types = {};

  /**
    *
    * Purpose: Represents the resource points possessed by a host.
    * This is what hosts must collect to reproduce.
    *
  */
  double points = 0;

  /**
    *
    * Purpose: Represents the resources that could be in the process of
    * being stolen.
    *
  */
  double res_in_process = 0;

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
    * Purpose: Represents the configuration settings for a particular run.
    *
  */
  emp::Ptr<SymConfigBase> my_config = NULL;

  /**
    *
    * Purpose: Represents if a host is alive. This is set to true when a host is killed.
    *
  */
  bool dead = false;

public:

  /**
   * The constructor for the host class
   */
  Host(emp::Ptr<emp::Random> _random, emp::Ptr<SymWorld> _world, emp::Ptr<SymConfigBase> _config,
  double _intval =0.0, emp::vector<emp::Ptr<Organism>> _syms = {},
  emp::vector<emp::Ptr<Organism>> _repro_syms = {},
  std::set<int> _set = std::set<int>(),
  double _points = 0.0) : interaction_val(_intval), syms(_syms), repro_syms(_repro_syms),
  res_types(_set), points(_points), random(_random), my_world(_world), my_config(_config) {
    if ( _intval > 1 || _intval < -1) {
       throw "Invalid interaction value. Must be between -1 and 1";  // Exception for invalid interaction value
     };
   }

  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To delete the memory used by a host's symbionts when the host is deleted.
   */
  ~Host(){
    for(size_t i=0; i<syms.size(); i++){
      syms[i].Delete();
    }
    for(size_t j=0; j<repro_syms.size(); j++){
      repro_syms[j].Delete();
    }
  }


  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To force a copy constructor to be generated by the compiler.
   */
  Host(const Host &) = default;


  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To force a move constructor to be generated by the compiler
   */
  Host(Host &&) = default;


  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To tell the compiler to use its default generated variants of the constructor
   */
  Host() = default;


  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To force a copy assignment operator to be generated by the compiler.
   */
  Host & operator=(const Host &) = default;


  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To force a move assignment operator to be generated by the compiler.
   */
  Host & operator=(Host &&) = default;


  /**
   * Input: An object of host to be compared to the current host.
   *
   * Output: To boolean representing if thing1 == &thing2
   *
   * Purpose: To override the bool operator == to return (thing1 == &thing2)
   */
  bool operator==(const Host &other) const { return (this == &other);}


  /**
   * Input: An object of host, and the address of the thing it is being
   * compared to.
   *
   * Output: To boolean representing if *thing1 == thing2
   *
   * Purpose: To override the bool operator != to return !(*thing1 == thing2)
   */
  bool operator!=(const Host &other) const {return !(*this == other);}


/**
  * Input: None
  *
  * Output: The double representing host's interaction value
  *
  * Purpose: To get the double representing host's interaction value
  */
  double GetIntVal() const { return interaction_val;}


/**
  * Input: None
  *
  * Output: A vector of pointers to the organisms that are the host's syms.
  *
  * Purpose: To get the vector containing pointers to the host's symbionts.
  */
  emp::vector<emp::Ptr<Organism>>& GetSymbionts() {return syms;}


/**
 * Input: None
 *
 * Output: A vector of pointers to the organisms that are the host's repro syms.
 *
 * Purpose: To get the vector containing pointers to the host's repro syms.
 */
  emp::vector<emp::Ptr<Organism>>& GetReproSymbionts() {return repro_syms;}


  /**
   * Input: None
   *
   * Output: The set of ints representing a host's res type.
   *
   * Purpose: To get the set of ints representing the host's res type.
   */
  std::set<int> GetResTypes() const { return res_types;}


  /**
   * Input: None
   *
   * Output: The double representing a host's points.
   *
   * Purpose: To get the host's points.
   */
  double GetPoints() { return points;}


  /**
   * Input: None
   *
   * Output: The double representing res_in_process
   *
   * Purpose: To get the value of res_in_process
   */
  double GetResInProcess() { return res_in_process;}

  /**
   * Input: None
   *
   * Output: The bool representing if an organism is a host.
   *
   * Purpose: To determine if an organism is a host.
  */
 bool IsHost() { return true; }


  /**
   * Input: A double representing the host's new interaction value.
   *
   * Output: None
   *
   * Purpose: To set a host's interaction value.
   */
  void SetIntVal(double _in) {
    if ( _in > 1 || _in < -1) {
       throw "Invalid interaction value. Must be between -1 and 1";  // Exception for invalid interaction value
     }
     else {
       interaction_val = _in;
     }
  }


  /**
   * Input: A vector of pointers to organisms that will become a host's symbionts.
   *
   * Output: None
   *
   * Purpose: To set a host's symbionts to the input vector of organisms.
   */
  void SetSymbionts(emp::vector<emp::Ptr<Organism>> _in) {
    ClearSyms();
    for(size_t i = 0; i < _in.size(); i++){
      AddSymbiont(_in[i]);
    }
  }


  /**
   * Input: A set of ints representing a host's resource type.
   *
   * Output: None
   *
   * Purpose: To set a host's resource types to the input.
   */
  void SetResTypes(std::set<int> _in) {res_types = _in;}


  /**
   * Input: A double representing a host's new point value.
   *
   * Output: None
   *
   * Purpose: To set a host's points.
   */
  void SetPoints(double _in) {points = _in;}


  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To clear a host's symbionts.
   */
  void ClearSyms() {syms.resize(0);}


  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To clear a host's repro symbionts.
   */
  void ClearReproSyms() {repro_syms.resize(0);}


  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To kill a host.
   */
  void SetDead() { dead = true;}


  /**
   * Input: The double to be set as res_in_process
   *
   * Output: None
   *
   * Purpose: To set the value of res_in_process
   */
  void SetResInProcess(double _in) { res_in_process = _in;}

  /**
   * Input: None
   *
   * Output: boolean
   *
   * Purpose: To determine if a host is dead.
   */
  bool GetDead() {return dead;}

  /**
   * Input: None
   *
   * Output: an int representing the current age of the Host
   *
   * Purpose: To get the Host's age.
   */
  int GetAge() {return age;}

  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: Increments age by one and kills it if too old.
   */
  void growOlder(){
    age = age + 1;
    if(age > my_config->HOST_AGE_MAX() && my_config->HOST_AGE_MAX() > 0){
      SetDead();
    }
  }

  /**
   * Input: The interaction value of the symbiont that
   * is eligible to steal resources from the host.
   *
   * Output: The double representing the amount of resources
   * that are actually stolen from the host.
   *
   * Purpose: To determine if a host's symbiont is eligible to
   * steal resources from the host.
   */
  double StealResources(double _intval){
    double hostIntVal = GetIntVal();
    double res_in_process = GetResInProcess();
    //calculate how many resources another organism can steal from this host
    if (hostIntVal>0){ //cooperative hosts shouldn't be over punished by StealResources
      hostIntVal = 0;
    }
    if (_intval < hostIntVal){
      //organism trying to steal can overcome host's defense
      double stolen = (hostIntVal - _intval) * res_in_process;
      double remainingResources = res_in_process - stolen;
      SetResInProcess(remainingResources);
      return stolen;
    } else {
      //defense cannot be overcome, no resources are stolen
      return 0;
    }
  }


  /**
   * Input: The double representing the number of points to be incremented onto a host's points.
   *
   * Output: None
   *
   * Purpose: To increment a host's points by the input value.
   */
  void AddPoints(double _in) {points += _in;}


  /**
   * Input: The pointer to the organism that is to be added to the host's symbionts.
   *
   * Output: None
   *
   * Purpose: To add a symbionts to a host's symbionts
   */
  void AddSymbiont(emp::Ptr<Organism> _in) {
    if((int)syms.size() < my_config->SYM_LIMIT() && SymAllowedIn()){
      syms.push_back(_in);
      _in->SetHost(this);
      _in->uponInjection();
    } else {
      _in.Delete();
    }
  }


  /**
   * Input: None
   *
   * Output: A bool representing if a symbiont will be allowed to enter a host.
   *
   * Purpose: To determine if a symbiont will be allowed into a host. If phage exclusion is off, this function will
   * always return true. If phage exclusion is on, then there is a 1/2^n chance of a new phage being allowed in,
   * where n is the number of existing phage.
   */
  bool SymAllowedIn(){
    bool do_phage_exclusion = my_config->PHAGE_EXCLUDE();
    if(!do_phage_exclusion){
     return true;
    }
    else{
     int num_syms = syms.size();
     //essentially imitaties a 1/ 2^n chance, with n = number of symbionts
     int enter_chance = random->GetUInt((int) pow(2.0, num_syms));
     if(enter_chance == 0) { return true; }
     return false;
    }
  }


  /**
   * Input: A pointer to the organism to be added to the host's symbionts.
   *
   * Output: None
   *
   * Purpose: To add a repro sym to the host's symbionts.
   */
  void AddReproSym(emp::Ptr<Organism> _in) {repro_syms.push_back(_in);}


  /**
   * Input: None
   *
   * Output: A bool representing if a host has any symbionts.
   *
   * Purpose: To determine if a host has any symbionts, though they might be corpses that haven't been removed yet.
   */
  bool HasSym() {
    return syms.size() != 0;
  }


  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To mutate a host's interaction value. This is called on newly generated
   * hosts to allow for evolution to occur.
   */
  void mutate(){
    double mutation_size = my_config->HOST_MUTATION_SIZE();
    if (mutation_size == -1) mutation_size = my_config->MUTATION_SIZE();
    double mutation_rate = my_config->HOST_MUTATION_RATE();
    if (mutation_rate == -1) mutation_rate = my_config->MUTATION_RATE();

    if(random->GetDouble(0.0, 1.0) <= mutation_rate){
      interaction_val += random->GetRandNormal(0.0, mutation_size);
      if(interaction_val < -1) interaction_val = -1;
      else if (interaction_val > 1) interaction_val = 1;
    }
  }


  /**
   * Input: The double representing the number of resources to be distributed to the host and its symbionts and the position of the host in the world.
   *
   * Output: None
   *
   * Purpose: To distribute resources to a host and its symbionts. In the event that the host has no symbionts,
   * the host gets all resources not allocated to defense or given to absent partner. Otherwise, the resource
   * is split into equal chunks for each symbiont
   */
  void DistribResources(double resources) {
    double hostIntVal = interaction_val; //using private variable because we can
    //do ectosymbiosis if the config setting is on, there is a parallel sym

    //In the event that the host has no symbionts, the host gets all resources not allocated to defense or
    // given to absent partner.
    if(syms.empty()) {
      if(hostIntVal >= 0){
        double spent = resources * hostIntVal;
        this->AddPoints(resources - spent);
      }
      else {
        double hostDefense = -1.0 * hostIntVal * resources;
        this->AddPoints(resources - hostDefense);
      }
      return; //This concludes resource distribution for a host without symbionts
    }

    size_t num_sym = syms.size();
    double sym_piece = (double) resources / num_sym;

    for(size_t i=0; i < syms.size(); i++){
      DistribResToSym(syms[i], sym_piece);
    }
  } //end DistribResources

  /**
   * Input: The total resources recieved by the host and its location in the world.
   *
   * Output: The resources remaining after the host maybe does ectosymbiosis.
   *
   * Purpose: To handle ectosymbiosis.
   */
  double HandleEctosymbiosis(double resources, size_t location){
    double leftover_resources = resources;
    if(GetDoEctosymbiosis(location)){
      double sym_piece = leftover_resources / (syms.size() + 1); //if there are no endo syms, the ecto sym will handle all the resources
      DistribResToSym(my_world->GetSymAt(location), sym_piece);
      leftover_resources = leftover_resources - sym_piece; //leave the leftover resources to be split by other syms
    }
    return leftover_resources;
  }

  /**
   * Input: The location of this host in the world.
   *
   * Output: A bool value representing whether this host should interact with a parallel sym
   *
   * Purpose: To determine whether a host should interact with a parallel sym
   */
  bool GetDoEctosymbiosis(size_t location){
    //a host is immune to ectosymbiosis if immunity is on and it has a sym.
    bool is_immune = my_config->ECTOSYMBIOTIC_IMMUNITY() && HasSym();
    bool valid_sym = my_world->GetSymAt(location) != nullptr && !my_world->GetSymAt(location)->GetDead();
    return my_config->ECTOSYMBIOSIS() && (valid_sym == true) && (is_immune == false);
  }

  /**
   * Input: The sym to whom resources are distributed and the resources it might recieve.
   *
   * Output: None
   *
   * Purpose: To distribute resources between sym and host depending on their interaction values.
   */
  void DistribResToSym(emp::Ptr<Organism> sym, double sym_piece){
    double hostIntVal = interaction_val;
    double hostDonation = 0;
    if(hostIntVal < 0){
      double hostDefense = hostIntVal * sym_piece * -1.0;
      hostDonation = 0;
      SetResInProcess(sym_piece - hostDefense);
    }
    else if(hostIntVal >= 0){
      hostDonation = hostIntVal * sym_piece;
      SetResInProcess(sym_piece - hostDonation);
    }

    double sym_return = sym->ProcessResources(hostDonation, this);
    this->AddPoints(sym_return + GetResInProcess());
    SetResInProcess(0);
  }


  /**
   * Input: The size_t value representing the location of the host.
   *
   * Output: None
   *
   * Purpose: To process the host, meaning determining eligibility for reproduction, checking for vertical
   * transmission, removing dead syms, and processing alive syms.
   */
  void Process(size_t location) {
    //Currently just wrapping to use the existing function
    double desired_resources = my_config->RES_DISTRIBUTE();
    double world_resources = my_world->PullResources(desired_resources); //recieve resources from the world
    double resources = HandleEctosymbiosis(world_resources, location);
    if(resources > 0) DistribResources(resources); //if there are enough resources left, distribute them.

    // Check reproduction
    if (GetPoints() >= my_config->HOST_REPRO_RES() && repro_syms.size() == 0) {  // if host has more points than required for repro
        // will replicate & mutate a random offset from parent values
        // while resetting resource points for host and symbiont to zero
        emp::Ptr<Host> host_baby = emp::NewPtr<Host>(random, my_world, my_config, GetIntVal());
        host_baby->mutate();
        //mutate(); //parent mutates and loses current resources, ie new organism but same symbiont
        SetPoints(0);

        //Now check if symbionts get to vertically transmit
        for(size_t j = 0; j< (GetSymbionts()).size(); j++){
          emp::Ptr<Organism> parent = GetSymbionts()[j];
          parent->VerticalTransmission(host_baby);
        }

        //Will need to change this to AddOrgAt and write my own position grabber
        //when I want ecto-symbionts
        my_world->DoBirth(host_baby, location); //Automatically deals with grid
      }
    if (GetDead()){
        return; //If host is dead, return
      }
    if (HasSym()) { //let each sym do whatever they need to do
        emp::vector<emp::Ptr<Organism>>& syms = GetSymbionts();
        for(size_t j = 0; j < syms.size(); j++){
          emp::Ptr<Organism> curSym = syms[j];
          if (GetDead()){
            return; //If previous symbiont killed host, we're done
          }
          if(!curSym->GetDead()){
            curSym->Process(location);
          }
          if(curSym->GetDead()){
            syms.erase(syms.begin() + j); //if the symbiont dies during their process, remove from syms list
            curSym.Delete();
          }
        } //for each sym in syms
      } //if org has syms
    growOlder();
  }
};//Host
#endif
