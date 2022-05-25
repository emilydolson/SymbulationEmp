#ifndef PHAGE_H
#define PHAGE_H

#include "../default_mode/Symbiont.h"
#include "LysisWorld.h"

class Phage: public Symbiont {
protected:

  /**
    * Purpose: Represents the time until lysis will be triggered.
    *
  */
  double burst_timer = 0;

  /**
    *
    * Purpose: Represents if lysogeny is on.
    *
  */
  bool lysogeny = false;

  /**
    *
    * Purpose: Represents the compatibility of the prophage to it's placement within the host's genome.
    *
  */
  double incorporation_val = 0.0;

  /**
    *
    * Purpose: Represents the chance of lysis
    *
  */
  double chance_of_lysis = 1;

  /**
    *
    * Purpose: Represents the chance of a prophage inducing to the lytic process
    *
  */
  double induction_chance = 1;

  /**
    *
    * Purpose: Represents the world that the phage are living in.
    *
  */
  emp::Ptr<LysisWorld> my_world = NULL;


public:
  /**
   * The constructor for phage
   */
  Phage(emp::Ptr<emp::Random> _random, emp::Ptr<LysisWorld> _world, emp::Ptr<SymConfigBase> _config, double _intval=0.0, double _points = 0.0) : Symbiont(_random, _world, _config, _intval, _points) {
    chance_of_lysis = my_config->LYSIS_CHANCE();
    induction_chance = my_config->CHANCE_OF_INDUCTION();
    incorporation_val = my_config->PHAGE_INC_VAL();
    if(chance_of_lysis == -1){
      chance_of_lysis = random->GetDouble(0.0, 1.0);
    }
    if(induction_chance == -1){
      induction_chance = random->GetDouble(0.0, 1.0);
    }
    if(incorporation_val == -1){
      incorporation_val = random->GetDouble(0.0, 1.0);
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
  Phage(const Phage &) = default;


  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To force a move constructor to be generated by the compiler
   */
  Phage(Phage &&) = default;


  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To tell the compiler to use its default generated variants of the constructor
   */
  Phage() = default;


  /**Input: None
   *
   * Output: The double representing the phage's burst timer.
   *
   * Purpose: To get a phage's burst timer.
   */
  double GetBurstTimer() {return burst_timer;}


  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To increment a phage's burst timer.
   */
  void IncBurstTimer() {burst_timer += random->GetRandNormal(1.0, 1.0);}


  /**
   * Input: The double to be set as the phage's burst timer
   *
   * Output: None
   *
   * Purpose: To set a phage's burst timer.
   */
  void SetBurstTimer(double _in) {burst_timer = _in;}


  /**
   * Input: None
   *
   * Output: The double representing a phage's change of lysis.
   *
   * Purpose: To determine a phage's chance of lysis.
   */
  double GetLysisChance() {return chance_of_lysis;}


  /**
   * Input: The double to be set as the phage's chance of lysis.
   *
   * Output: None
   *
   * Purpose: To set a phage's chance of lysis
   */
  void SetLysisChance(double _in) {chance_of_lysis = _in;}

   /**
   * Input: None
   *
   * Output: The double representing a phage's incorporation value.
   *
   * Purpose: To determine a phage's incorporation value.
   */
  double GetIncVal() {return incorporation_val;}


  /**
   * Input: The double to be set as the phage's incorporation value.
   *
   * Output: None
   *
   * Purpose: To set a phage's incorporation value.
   */
  void SetIncVal(double _in) {incorporation_val = _in;}

  /**
   * Input: None
   *
   * Output: The double representing a prophage's chance of induction.
   *
   * Purpose: To determine a lysogenic phage's chance of inducing
   */
  double GetInductionChance() {return induction_chance;}

  /**
   * Input: The double to be set as the phage's chance of induction
   *
   * Output:None
   *
   * Purpose: To set a phage's chance of inducing
   */
  void SetInductionChance(double _in) {induction_chance = _in;}

  /**
   * Input: None
   *
   * Output: The bool representing if a phage will do lysogeny.
   *
   * Purpose: To determine if a phage is capable of lysogeny
   */
  bool GetLysogeny() {return lysogeny;}


  /**
   * Input: None
   *
   * Output: The bool representing if an organism is a phage, always true.
   *
   * Purpose: To determine if an organism is a phage.
   */
  bool IsPhage() {return true;}


  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To determine if a phage will choose lysis or lysogeny. If a phage chooses
   * to be lytic, their interaction value will be -1 to represent them being antagonistic.
   * If a phage chooses to be lysogenic, their interaction value will be 0 to represent
   * them being neutral.
   */
  void UponInjection() {
    double rand_chance = random->GetDouble(0.0, 1.0);
    if (rand_chance <= chance_of_lysis){
      lysogeny = false;
    } else {
      lysogeny = true;
    }
  }


  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To mutate a phage's chance of lysis. The mutation will be based on a
   * value chosen from a normal distribution centered at 0, with a standard
   * deviation that is equal to the mutation size. Phage mutation can be
   * on or off.
   */
  void Mutate() {
    Symbiont::Mutate();
    double local_rate = my_config->MUTATION_RATE();
    double local_size = my_config->MUTATION_SIZE();
    if (random->GetDouble(0.0, 1.0) <= local_rate) {
      //mutate chance of lysis/lysogeny, if enabled
      if(my_config->MUTATE_LYSIS_CHANCE()){
        chance_of_lysis += random->GetRandNormal(0.0, local_size);
        if(chance_of_lysis < 0) chance_of_lysis = 0;
        else if (chance_of_lysis > 1) chance_of_lysis = 1;
      }
      if(my_config->MUTATE_INDUCTION_CHANCE()){
        induction_chance += random->GetRandNormal(0.0, local_size);
        if(induction_chance < 0) induction_chance = 0;
        else if (induction_chance > 1) induction_chance = 1;
      }
      if(my_config->MUTATE_INC_VAL()){
        incorporation_val += random->GetRandNormal(0.0, local_size);
        if(incorporation_val < 0) incorporation_val = 0;
        else if (incorporation_val > 1) incorporation_val = 1;
      }
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
    emp::Ptr<Phage> sym_baby = emp::NewPtr<Phage>(random, my_world, my_config, GetIntVal());
    // pass down parent's genome
    sym_baby->SetIncVal(GetIncVal());
    sym_baby->SetLysisChance(GetLysisChance());
    sym_baby->SetInductionChance(GetInductionChance());
    sym_baby->SetInfectionChance(GetInfectionChance());
    return sym_baby;
  }

  /**
   * Input: location of the phage attempting to horizontally transmit
   *
   * Output: None
   *
   * Purpose: To burst host and release offspring
   */
  void LysisBurst(emp::WorldPosition location){
    emp::vector<emp::Ptr<Organism>>& repro_syms = my_host->GetReproSymbionts();
    //Record the burst size and count
    emp::DataMonitor<double>& data_node_burst_size = my_world->GetBurstSizeDataNode();
    data_node_burst_size.AddDatum(repro_syms.size());
    emp::DataMonitor<int>& data_node_burst_count = my_world->GetBurstCountDataNode();
    data_node_burst_count.AddDatum(1);

    for(size_t r=0; r<repro_syms.size(); r++) {
      my_world->SymDoBirth(repro_syms[r], location);
    }
    my_host->ClearReproSyms();
    my_host->SetDead();
    return;
  }

  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To allow lytic phage to produce offspring and increment the burst timer
   */
  void LysisStep(){
    IncBurstTimer();
    if(my_config->SYM_LYSIS_RES() == 0) {
      std::cout << "Lysis with a sym_lysis_res of 0 leads to an \
      infinite loop, please change" << std::endl;
      std::exit(1);
    }
    while(GetPoints() >= my_config->SYM_LYSIS_RES()) {
      emp::Ptr<Organism> sym_baby = Reproduce();
      my_host->AddReproSym(sym_baby);
      SetPoints(GetPoints() - my_config->SYM_LYSIS_RES());
    }
  }

  /**
   * Input: A pointer to the baby host to have symbionts added.
   *
   * Output: None
   *
   * Purpose: To allow for vertical transmission to occur. lysogenic
   * phage have 100% chance of vertical transmission, lytic phage have
   * 0% chance
   */
  void VerticalTransmission(emp::Ptr<Organism> host_baby){
    //lysogenic phage have 100% chance of vertical transmission, lytic phage have 0% chance
    if(lysogeny){
      emp::Ptr<Organism> phage_baby = Reproduce();
      host_baby->AddSymbiont(phage_baby);
    }
  }


  /**
   * Input: The double representing the resources to be distributed to the phage
   * and (optionally) the host from whom it comes; if no host is provided, the
   * phage's host variable is used.
   *
   * Output: The double representing the resources that are left over from what
   * was distributed to the phage.
   *
   * Purpose: To allow a phage to steal or use donated resources from their host.
   */
  double ProcessResources(double host_donation, emp::Ptr<Organism> host = nullptr){
    if(host == nullptr){
      host = my_host;
    }
    if(lysogeny){
      if(my_config->BENEFIT_TO_HOST()){
        return host->ProcessLysogenResources(incorporation_val);
      } else{
        return 0;
      }
    }
    else{
      return Symbiont::ProcessResources(host_donation, host); //lytic phage do steal resources
    }
  }

  /**
   * Input: The worldposition representing the location of the phage being processed.
   *
   * Output: None
   *
   * Purpose: To process a phage, meaning check for reproduction, check for lysis, and move the phage.
   */
  void Process(emp::WorldPosition location) {
    if(my_config->LYSIS() && !GetHost().IsNull()) { //lysis enabled and phage is in a host
      if(!lysogeny){ //phage has chosen lysis
        if(GetBurstTimer() >= my_config->BURST_TIME() ) { //time to lyse!
          LysisBurst(location);
        }
        else { //not time to lyse
          LysisStep();
        }
      }
      else if(lysogeny){ //phage has chosen lysogeny
        double rand_chance = random->GetDouble(0.0, 1.0);
        if (rand_chance <= induction_chance){//phage has chosen to induce and turn lytic
          lysogeny = false;
        }
        else if(random->GetDouble(0.0, 1.0) <= my_config->PROPHAGE_LOSS_RATE()){ //check if the phage's host should become susceptible again
          SetDead();
        }
      }
    }

    else if (GetHost().IsNull() && my_config->FREE_LIVING_SYMS()) { //phage is free living
      my_world->MoveFreeSym(location);
    }
  }
};
#endif
