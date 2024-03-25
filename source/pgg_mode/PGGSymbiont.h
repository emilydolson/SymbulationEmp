#ifndef PGGSYM_H
#define PGGSYM_H

#include "../default_mode/Symbiont.h"
#include "PGGWorld.h"

class PGGSymbiont: public Symbiont {
protected:

  /**
    *
    * Purpose: the donation value for this symbiont.
    *
  */
  double PGG_donate = 0;

  /**
    *
    * Purpose: Represents the world that the pgg symbionts are living in.
    *
  */
  emp::Ptr<PGGWorld> my_world = NULL;

public:
  PGGSymbiont(emp::Ptr<emp::Random> _random, emp::Ptr<PGGWorld> _world, emp::Ptr<SymConfigBase> _config, double _intval=0.0, double _donation = 0.0, double _points = 0.0 ) : Symbiont(_random, _world, _config, _intval, _points),PGG_donate(_donation)
  {my_world = _world;}


  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To force a copy constructor to be generated by the compiler.
   */
  PGGSymbiont(const PGGSymbiont &) = default;


  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To force a move constructor to be generated by the compiler
   */
  PGGSymbiont(PGGSymbiont &&) = default;


  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To tell the compiler to use its default generated variants of the constructor
   */
  PGGSymbiont() = default;


  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To force a copy assignment operator to be generated by the compiler.
   */
  PGGSymbiont & operator=(const PGGSymbiont &) = default;


  /**
  * Input: None
  *
  * Output: None
  *
  * Purpose: To force a move assignment operator to be generated by the compiler.
  */
  PGGSymbiont & operator=(PGGSymbiont &&) = default;

  /**
  * Input: None
  * 
  * Output: Name of class as string, PGGSymbiont
  *
  * Purpose: To know which subclass the object is
  */
  std::string const GetName() {
    return  "PGGSymbiont";
  }

  /**
   * Input: None
   *
   * Output: The donation value for the symbiont.
   *
   * Purpose: To get a symbiont's donation value.
   */
  double GetDonation() {return PGG_donate;}


  /**
   * Input: The double to be set as the symbiont's donation value.
   *
   * Output: None
   *
   * Purpose: To set the symbiont's donation value.
   */
  void SetDonation(double _in) {PGG_donate = _in;}


  /**
   * Input: None
   *
   * Output: None
   *
   * Purpose: To mutate a PGGSymbiont's donation value. The mutation will be based on a
   * value chosen from a normal distribution centered at 0, with a standard
   * deviation that is equal to the mutation size.
   */
  void Mutate(){
    Symbiont::Mutate();
    if (random->GetDouble(0.0, 1.0) <= my_config->MUTATION_RATE()) {
      PGG_donate += random->GetNormal(0.0, my_config->MUTATION_SIZE());
      if(PGG_donate < 0) PGG_donate = 0;
      else if (PGG_donate > 1) PGG_donate = 1;
    }
  }


  /**
   * Input: None
   *
   * Output: The double representation of resources to be given to the host.
   *
   * Purpose: Deteremines the resources that the symbiont is contributing
   * to the host's resource pool, and decriments them from the symbiont's own
   * own resource collection.
   */
  double ProcessPool(){
    double symdonation = GetDonation();
    double symPortion = GetPoints();
    double hostreturn = symdonation*symPortion;
    SetPoints(symPortion-hostreturn);
    return hostreturn;
  }

  /**
   * Input: None
   *
   * Output: The pointer to the newly created organism
   *
   * Purpose: To produce a new PGGSymbiont, identical to the original
   */
  emp::Ptr<Organism> MakeNew() {
    emp::Ptr<PGGSymbiont> sym_baby = emp::NewPtr<PGGSymbiont>(random, my_world, my_config, GetIntVal());
    sym_baby->SetInfectionChance(GetInfectionChance());
    sym_baby->SetDonation(GetDonation());
    return sym_baby;
  }

  /**
   * Input: The PGG symbiont to be printed
   *
   * Output: A formatted string representation of the input symbiont, including its
   * interaction value and donation value.
   *
   * Purpose: To print the symbiont for testing purposes.
   */
  std::string PrintSym(emp::Ptr<PGGSymbiont> org){
    if (org->GetPoints() < 0) return "-";
    double out_val = org->GetIntVal();
    double donate_val = org->GetDonation();
    // this prints the symbiont with two decimal places for easier reading
    std::stringstream temp;
    temp << std::fixed << std::setprecision(2) << "Interaction value: " << out_val << " Donation value: " << donate_val;
    std::string formattedstring = temp.str();
    return formattedstring;
  }
};//PGGSymbiont
#endif
