#ifndef BACTERIUM_H
#define BACTERIUM_H

#include "../default_mode/Host.h"
#include "LysisWorld.h"


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
    * Purpose: Represents the world that the hosts are living in.
    *
  */
  emp::Ptr<LysisWorld> my_world = NULL;

public:

  /**
   * The constructor for the bacterium class
   */
  Bacterium(emp::Ptr<emp::Random> _random, emp::Ptr<LysisWorld> _world, emp::Ptr<SymConfigBase> _config,
  double _intval =0.0, emp::vector<emp::Ptr<Organism>> _syms = {},
  emp::vector<emp::Ptr<Organism>> _repro_syms = {},
  std::set<int> _set = std::set<int>(),
  double _points = 0.0) : Host(_random, _world, _config, _intval,_syms, _repro_syms, _set, _points)  {
    host_incorporation_val = my_config->HOST_INC_VAL();
    if(host_incorporation_val == -1){
      host_incorporation_val = random->GetDouble(0.0, 1.0);
    }
    my_world = _world;
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
   * Input: None.
   *
   * Output: A new bacterium with same properties as this bacterium.
   *
   * Purpose: To avoid creating an organism via constructor in other methods.
   */
  emp::Ptr<Organism> makeNew(){
    emp::Ptr<Bacterium> host_baby = emp::NewPtr<Bacterium>(random, my_world, my_config, GetIntVal());
    host_baby->SetPoints(0);
    host_baby->SetAge(0);
    host_baby->SetIncVal(GetIncVal());
    return host_baby;
  }

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
      if(my_config->MUTATE_INC_VAL()){
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

};//Bacterium
#endif
