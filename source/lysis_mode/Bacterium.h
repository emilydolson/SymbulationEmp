#ifndef BACTERIUM_H
#define BACTERIUM_H
 
#include "../default_mode/Host.h"
#include "../SymWorld.h"
 
 
class Bacterium : public Host {
 
 
protected:
 
  /**
    * 
    * Purpose: Represents the host's genome. A double with a range from 0 to 1. 
    * The host's genome gets compared against the phage's incorporation value.
    * 
    * 
  */  
  double host_incorporation_val = 0;

  /**
    * 
    * Purpose: Represents whether the host's genome mutates or not. A boolean value. 0 for false, 1 for true.
    * The host's genome gets compared against the phage's incorporation value.
    * 
    * 
  */  
  bool mutate_host_inc_val = false;
 
public:
 
  /**
   * The constructor for the bacterium class
   */
  Bacterium(emp::Ptr<emp::Random> _random, emp::Ptr<SymWorld> _world, emp::Ptr<SymConfigBase> _config,
  double _intval =0.0, emp::vector<emp::Ptr<Organism>> _syms = {},
  emp::vector<emp::Ptr<Organism>> _repro_syms = {},
  std::set<int> _set = std::set<int>(),
  double _points = 0.0) : Host(_random, _world, _config, _intval,_syms, _repro_syms, _set, _points)  { 
    host_incorporation_val = my_config->HOST_INC_VAL();
    mutate_host_inc_val = my_config->MUTATE_INC_VAL();
    if(host_incorporation_val == -1){
      host_incorporation_val = random->GetDouble(0.0, 1.0);
    }
  }
 
  /**
   * Input: None
   * 
   * Output: None
   * 
   * Purpose: To force a copy constructor to be generated by the compiler.
   */
  Bacterium(const Bacterium &) = default;
 
 
  /**
   * Input: None
   * 
   * Output: None
   * 
   * Purpose: To force a move constructor to be generated by the compiler
   */  
  Bacterium(Bacterium &&) = default;
 
 
  /**
   * Input: None
   * 
   * Output: None
   * 
   * Purpose: To tell the compiler to use its default generated variants of the constructor 
   */
  Bacterium() = default;

  /**
   * Input: None
   * 
   * Output: The double representing a genome's value.
   * 
   * Purpose: To determine a genome's value.
   */
  double GetIncVal() {return host_incorporation_val;}
 
 
  /**
   * Input: The double to be set as the bacterium's genome value
   * 
   * Output: None
   * 
   * Purpose: To set a bacterium's genome value
   */
  void SetIncVal(double _in) {host_incorporation_val = _in;}

  /**
   * Input: None
   * 
   * Output: None
   * 
   * Purpose: To mutate a bacterium's genome. The mutation will be based on a value
   * chosen from a normal distribution centered at 0, with a standard deviation that
   * is equal to the mutation size. Bacterium mutation can be turned on or off.
   */
  void mutate() {
    Host::mutate();
    
    if(random->GetDouble(0.0, 1.0) <= my_config->MUTATION_RATE()){
      
      //mutate host genome if enabled      
      if(mutate_host_inc_val){
        host_incorporation_val += random->GetRandNormal(0.0, my_config->MUTATION_SIZE());
        
        if(host_incorporation_val < 0) host_incorporation_val = 0;
        
        else if(host_incorporation_val > 1) host_incorporation_val = 1;
      }
    }
  }

  double ProcessLysogenResources(double phage_inc_val){
    double incorporation_success = 1 - abs(GetIncVal() - phage_inc_val);
    double processed_resources = GetResInProcess() * incorporation_success * my_config->SYNERGY();
    SetResInProcess(0);
    return processed_resources;
  }


  
  /**
   * Input: The size_t value representing the location of the bacterium. 
   * 
   * Output: None
   * 
   * Purpose: To process the bacterium, meaning determining eligibility for reproduction, checking for vertical
   * transmission, removing dead syms, and processing alive syms. 
   */
  void Process(size_t location) {
    //Currently just wrapping to use the existing function
    double resources = my_world->PullResources();
    DistribResources(resources);
    // Check reproduction
    if (GetPoints() >= my_config->HOST_REPRO_RES() && repro_syms.size() == 0) {  // if host has more points than required for repro
        // will replicate & mutate a random offset from parent values
        // while resetting resource points for host and symbiont to zero
        emp::Ptr<Bacterium> host_baby = emp::NewPtr<Bacterium>(random, my_world, my_config, GetIntVal());
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
  }
   
};//Bacterium
#endif