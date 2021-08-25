#ifndef PHAGE_H
#define PHAGE_H

#include "Symbiont.h"
#include "SymWorld.h"

class Phage: public Symbiont {
protected:

  /**
    *
    * Purpose: Represents the time until lysis will be triggered.
    *
  */
  double burst_timer = 0;

  /**
    *
    * Purpose: Represents if lysis is permitted.
    *
  */
  bool lysis_enabled = true;

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
    * Purpose: Represents whether the compatibility of the prophage to it's placement within the host's genome, mutates or not.
    *
  */
  bool mutate_incorporation_val = false;

  /**
    *
    * Purpose: Represents how long a lysis burst takes to occur.
    *
  */
  double burst_time = 60;

  /**
    *
    * Purpose: Represents resources required for symbiont to create offspring
    *
  */
  double sym_lysis_res = 15;

  /**
    *
    * Purpose: Represents the chance of lysis
    *
  */
  double chance_of_lysis = 1;

  /**
    *
    * Purpose: Represents if lysis mutation is permitted
    *
  */
  bool mutate_chance_of_lysis = false;

  /**
    *
    * Purpose: Represents if induction rate mutation is permitted
    *
  */
  bool mutate_chance_of_induction = false;


  /**
    *
    * Purpose: Represents the chance of a prophage inducing to the lytic process
    *
  */
  double induction_chance = 1;


public:
  /**
   * The constructor for phage
   */
  Phage(emp::Ptr<emp::Random> _random, emp::Ptr<SymWorld> _world, emp::Ptr<SymConfigBase> _config, double _intval=0.0, double _points = 0.0) : Symbiont(_random, _world, _config, _intval, _points) {
    burst_time = my_config->BURST_TIME();
    sym_lysis_res = my_config->SYM_LYSIS_RES();
    lysis_enabled = my_config->LYSIS();
    mutate_chance_of_induction = my_config->MUTATE_INDUCTION_CHANCE();
    mutate_chance_of_lysis = my_config->MUTATE_LYSIS_CHANCE();
    chance_of_lysis = my_config->LYSIS_CHANCE();
    induction_chance = my_config->CHANCE_OF_INDUCTION();
    incorporation_val = my_config->PHAGE_INC_VAL();
    mutate_incorporation_val = my_config->MUTATE_INC_VAL();
    if(chance_of_lysis == -1){
      chance_of_lysis = random->GetDouble(0.0, 1.0);
    }
    if(induction_chance == -1){
      induction_chance = random->GetDouble(0.0, 1.0);
    }
    if(incorporation_val == -1){
      incorporation_val = random->GetDouble(0.0, 1.0);
    }
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
  void uponInjection() {
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
  void mutate() {
   Symbiont::mutate();
    if (random->GetDouble(0.0, 1.0) <= mut_rate) {
      //mutate chance of lysis/lysogeny, if enabled
      if(mutate_chance_of_lysis){
        chance_of_lysis += random->GetRandNormal(0.0, mut_size);
        if(chance_of_lysis < 0) chance_of_lysis = 0;
        else if (chance_of_lysis > 1) chance_of_lysis = 1;
      }
      if(mutate_chance_of_induction){
        induction_chance += random->GetRandNormal(0.0, mut_size);
        if(induction_chance < 0) induction_chance = 0;
        else if (induction_chance > 1) induction_chance = 1;
      }
      if(mutate_incorporation_val){
        incorporation_val += random->GetRandNormal(0.0, mut_size);
        if(incorporation_val < 0) incorporation_val = 0;
        else if (incorporation_val > 1) incorporation_val = 1;
      }
    }
  }


  /**
   * Input: None
   *
   * Output: The pointer to the new phage that has been produced.
   *
   * Purpose: To reproduce phage. The newly generated phage will have
   * 0 points, a burst timer equal to 0, and have a mutated genome
   * from their parent organism.
   */
  emp::Ptr<Organism> reproduce() {
    emp::Ptr<Phage> sym_baby = emp::NewPtr<Phage>(*this); //constructor that takes parent values
    sym_baby->SetPoints(0);
    sym_baby->SetBurstTimer(0);
    sym_baby->mutate();
    return sym_baby;
  }

  /**
   * Input: location of the phage attempting to horizontally transmit
   *
   * Output: None
   *
   * Purpose: To burst host and release offspring
   */
  void LysisBurst(size_t location){
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
    if(sym_lysis_res == 0) {
      std::cout << "Lysis with a sym_lysis_res of 0 leads to an \
      infinite loop, please change" << std::endl;
      std::exit(1);
    }
    while(GetPoints() >= sym_lysis_res) {
      emp::Ptr<Organism> sym_baby = reproduce();
      my_host->AddReproSym(sym_baby);
      SetPoints(GetPoints() - sym_lysis_res);
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
      emp::Ptr<Organism> phage_baby = reproduce();
      host_baby->AddSymbiont(phage_baby);
    }
  }

  /**
   * Input: The double representing the resources that will be given to a phage.
   *
   * Output: The double representing the resources that are left over from what
   * was distributed to the phage.
   *
   * Purpose: To allow a phage to steal or use donated resources from their host.
   */
  double ProcessResources(double hostDonation){
    return ProcessResources(hostDonation, my_host);
  }

  /**
   * Input: The double representing the resources that will be given to a phage and the host with who the phage interacts.
   *
   * Output: The double representing the resources that are left over from what
   * was distributed to the phage.
   *
   * Purpose: To allow a phage to steal or use donated resources from their host.
   */
  double ProcessResources(double hostDonation, emp::Ptr<Organism> host){
    if(lysogeny){
      if(my_config->BENEFIT_TO_HOST()){
        return my_host->ProcessLysogenResources(incorporation_val);
      } else{
        return 0;
      }
    }
    else{
      return Symbiont::ProcessResources(hostDonation, host); //lytic phage do steal resources
    }
  }

  /**
   * Input: The size_t representing the location of the phage being processed.
   *
   * Output: None
   *
   * Purpose: To process a phage, meaning check for reproduction, check for lysis, and move the phage.
   */
  void Process(size_t location) {
    if(lysis_enabled && !GetHost().IsNull()) { //lysis enabled and phage is in a host
      if(!lysogeny){ //phage has chosen lysis
        if(GetBurstTimer() >= burst_time ) { //time to lyse!
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
      my_world->FreeSymLocationHandler(location);
    }
  }
};
#endif
