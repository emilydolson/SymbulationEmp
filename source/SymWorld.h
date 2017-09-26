#include "evo/World.h"
#include "tools/Random.h"
#include <set>
#include "SymOrg.h"


class SymWorld {
 private:
  emp::Random random;
  emp::evo::GridWorld<Host> world;

 public:
  SymWorld() {
  	const int dimX = 10;
  	const int dimY = 10;
  	const int popSize = (dimX * dimY) / 2;  // number of organisms - anything less than full population results in segmentation fault at replication
    world.ConfigPop(dimX,dimY);
    world.Insert( Host(0.5, Symbiont(), std::set<int>(), 0.0), popSize);  
    world.Print(PrintOrg);
  }
  
  void PrintIt() {
     world.Print(PrintOrg);
  }
  
  double newIntVal(double _in = 0.5) {
        // get random deviation from original interaction values of host and symbiont
        // not sure how large the standard deviation value should be  
  	 	double offset = random.GetRandNormal(0.0, 0.002);  // using sd from dissertation
  	 	
  	 	double newVal = _in + offset;  
  	 	
  	 	 if (newVal > 1 ) {
  	 	      newVal = 1.0;
  	 	   } else if (newVal < 0) {
  	 	      newVal = 0.0;
  	 	   }
  	 	   
  	 	 return newVal;

}
  
  void Update(size_t new_resources=10) {
  	 // divvy up and distribute resources to host and symbiont in each cell --- NEW FUNCTION!!
  	 for (size_t i = 0; i < world.GetSize(); i++) {
  	   if (world.IsOccupied(i) == false) continue;  // no organism at that cell
  	   
  	   // initial disbursement to host and symbiont
  	   size_t sym_portion = world[i].GetIntVal() * new_resources;
//  	   std::cout << "Symbiont gets: " << sym_portion;
  	   size_t host_portion = new_resources - sym_portion;
//  	   std::cout << " and host keeps: " << host_portion << std::endl;
  	   
  	   world[i].AddPoints(host_portion);
	   world[i].GiveSymPoints(sym_portion);
  	   
  	   // symbiont trades value back to host based on its interaction value
  	   world[i].GetBackPoints(sym_portion);
  	   
  	   }

  	 /* test print of resource values
  	 std::cout << std::endl;
 	 std::cout << "Resource values of hosts" << std::endl;
  	 for (size_t i = 0; i < world.GetSize(); i++) {
  	 	if (world.IsOccupied(i) == false) {
 	 	    std::cout << " - "; // no resources to print
  	 	}
  	 	else {
  	 	   double checkPoints;
  	 	   checkPoints = world[i].GetPoints();
  	 //		std::cout << " " << checkPoints << " ";
  	    }
  	   
	}  
	*/	
	
	/*test print of sym resource values
	std::cout << std::endl;
    std::cout << "Resource values of symbionts" << std::endl;
  	 for (size_t i = 0; i < world.GetSize(); i++) {
  	 	if (world.IsOccupied(i) == false) {
  	 	   std::cout << " - "; // no resources to print
  	 	}
  	 	else {
  	 	   double checkPoints;
  	 	   checkPoints = world[i].GetSymbiont().GetPoints();
        	std::cout << " " << checkPoints << " ";
  	    }
  	   
	} 
      std::cout << std::endl;  */
  	 
  	 // host reproduces if it can
  	 // assuming 100% vertical transmission rate right now
  	 for (size_t i = 0; i < world.GetSize(); i++) {
  	 	if (world.IsOccupied(i) == false) continue;  // nothing to replicate!
  	 	
  	 	if (world[i].GetPoints() >= 100 ) {  // host replication
  	// 	   std::cout << "Testing replication at: " << i << std::endl;
  	 	   // will replicate & mutate a random offset from parent values
  	 	   // while resetting resource points for host and symbiont to zero
 
  	 	//   std::cout << "Testing host offset of: " << host_offset << std::endl;
  	 	//   std::cout << "Testing sym offset of: " << sym_offset << std::endl;
  	 	   double newHostIntVal = newIntVal(world[i].GetIntVal());
  	 	   double newSymIntVal = newIntVal(world[i].GetSymbiont().GetIntVal());

  	 	   world[i] = Host(newHostIntVal, Symbiont(), std::set<int>(), 0.0); // Possibly safer to use InsertAt()???
  	 	   world[i].SetSymIntVal(newSymIntVal);  
  	 	
  	 	// pick a new world[i] to get a new Host & symbiont with 
  	 	// random deviation from original interaction values of host and symbiont 
  	 	
  	 	// this should work, but it doesn't seem to ever include the end index for the world  
 // 	 int newLoc = random.GetInt(0, world.GetSize() - 1);
 		 int newLoc = random.GetInt(0, world.GetSize());  // try this but guard against going past end
 		// std::cout << "New location: " << newLoc << std::endl;
 		 if (newLoc == world.GetSize()) {
 		 	newLoc = world.GetSize() - 1;
 		 	std::cout << "Tried to go out of bounds." << std::endl;
 		 }
 		 	
 		  // std::cout << "New Location: " << newLoc << std::endl;
 		   newHostIntVal = newIntVal(world[i].GetIntVal());
  	 	   newSymIntVal = newIntVal(world[i].GetSymbiont().GetIntVal());
  	 	   world.InsertAt(Host(newHostIntVal, Symbiont(), std::set<int>(), 0.0), newLoc);
  	 	   world[newLoc].SetSymIntVal(newSymIntVal);
  	 	   
  	 	}
  	 	else if (world[i].GetSymbiont().GetPoints() >= 100) {
  	 	 // symbiont reproduces independently if it has >= 100 resources
  	 	 // new symbiont in this host with mutated value
  	 	 double newSymIntVal = newIntVal(world[i].GetSymbiont().GetIntVal());
  	 	 world[i].SetSymIntVal(newSymIntVal);
  	 	 world[i].ResetSymPoints();
  	 	 
  	 	 // pick new host to infect, if one exists at the new location and does NOT already have a symbiont
  	 	 int newLoc = random.GetInt(0, world.GetSize());  // try this but guard against going past end
 		 if (newLoc == world.GetSize()) {
 		 	newLoc = world.GetSize() - 1;
 		 	std::cout << "Tried to go out of bounds." << std::endl;
 		 }
 		 
 		 if (world.IsOccupied(newLoc) == true) {
 		   std::cout << "Symbiont tried to replicate on its own from " << i << " to " << newLoc;
 		   if (world[newLoc].HasSym()) {
 		   	  std::cout << " and failed because host already has a symbiont." << std::endl;
 		   } else {
 		     newSymIntVal = newIntVal(world[i].GetSymbiont().GetIntVal());
 		     world[newLoc].SetSymIntVal(newSymIntVal);
 		     world[newLoc].ResetSymPoints();
 		   }
  	 	 } else {
  	 	 	std::cout << "Symbiont tried to replicate on its own but failed to find a host at " << newLoc << std::endl;
  	 	 }
  	 	 
 }
  	 	
  	 	
  	 }
  	 
  	 
  }
  

};

