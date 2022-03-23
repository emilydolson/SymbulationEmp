#ifndef PGGHOST_H
#define PGGHOST_H

// #include "../../Empirical/include/emp/math/Random.hpp"
// #include "../../Empirical/include/emp/tools/string_utils.hpp"
// #include <set>
// #include <iomanip> // setprecision
// #include <sstream> // stringstream
#include "../default_mode/Host.h"
#include "PggWorld.h"


class PggHost: public Host {
protected:

  /**
    *
    * Purpose:#
    *
  */
  double sourcepool = 0;

  /**
    *
    * Purpose: Represents the world that the pgg hosts are living in.
    *
  */
  emp::Ptr<PggWorld> my_world = NULL;

public:
  PggHost(emp::Ptr<emp::Random> _random, emp::Ptr<PggWorld> _world, emp::Ptr<SymConfigBase> _config,
  double _intval =0.0, emp::vector<emp::Ptr<Organism>> _syms = {},
  emp::vector<emp::Ptr<Organism>> _repro_syms = {},
  std::set<int> _set = std::set<int>(),
  double _points = 0.0) : Host(_random, _world, _config, _intval,_syms, _repro_syms, _set, _points) {my_world = _world;}


  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To force a copy constructor to be generated by the compiler.
   */
  PggHost(const PggHost &) = default;


  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To force a move constructor to be generated by the compiler
   */
  PggHost(PggHost &&) = default;


  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To tell the compiler to use its default generated variants of the constructor
   */
  PggHost() = default;


  /**
   * Input: None
   *
   * Output: #
   *
   * Purpose:
   */
  double GetPool() {return sourcepool;}


  /**
   * Input: #
   *
   * Output: None
   *
   * Purpose:
   */
  void SetPool(double _in) {sourcepool= _in;}


  /**
   * Input: #
   *
   * Output: None
   *
   * Purpose:
   */
  void AddPool(double _in) {sourcepool += _in;}


  /**
   * Input: #
   *
   * Output: None
   *
   * Purpose:
   */
  void DistribResources(double resources) {
    Host::DistribResources(resources);

    for(size_t i=0; i < syms.size(); i++){
      double hostPool = syms[i]->ProcessPool();
      this->AddPool(hostPool);
    }
    if(syms.size()>0){this->DistribPool();}
  } //end DistribResources


  /**
   * Input: None
   *
   * Output: #
   *
   * Purpose:
   */
  void DistribPool(){
    //to do: marginal return
    int num_sym = syms.size();
    double bonus = my_config->PGG_SYNERGY();
    double sym_piece = (double) sourcepool / num_sym;
    for(size_t i=0; i < syms.size(); i++){
        syms[i]->AddPoints(sym_piece*bonus);
    }
    this->SetPool(0);
  }

  /**
   * Input: None.
   *
   * Output: A new pgghost with same properties as this pgghost.
   *
   * Purpose: To avoid creating an organism via constructor in other methods.
   */
  emp::Ptr<Organism> makeNew(){
    emp::Ptr<PggHost> host_baby = emp::NewPtr<PggHost>(random, my_world, my_config, GetIntVal());
    return host_baby;
  }

};//Host

#endif
