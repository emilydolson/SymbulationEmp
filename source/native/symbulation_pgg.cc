#include "../pgg_mode/PGGWorld.h"
#include"../pgg_mode/PGGSymbiont.h"
#include"../pgg_mode/PGGHost.h"
#include "../pgg_mode/PGGWorldSetup.cc"
#include "../../Empirical/include/emp/config/ArgManager.hpp"
#include <iostream>
#include "../ConfigSetup.h"

// This is the main function for the NATIVE version of this project.

int symbulation_main(int argc, char * argv[])
{
  SymConfigBase config;

  bool success = config.Read("SymSettings.cfg");
  if(!success) {
    std::cout << "You didn't have a SymSettings.cfg, so one is being written, please try again" << std::endl;
    config.Write("SymSettings.cfg");
  }

  auto args = emp::cl::ArgManager(argc, argv);
  if (args.ProcessConfigOptions(config, std::cout, "SymSettings.cfg") == false) {
    std::cerr << "There was a problem in processing the options file." << std::endl;
    exit(1);
  }
  if (args.TestUnknown() == false) {
    std::cerr << "Leftover args no good." << std::endl;
    exit(1);
  }
  if (config.BURST_SIZE()%config.BURST_TIME() != 0 && config.BURST_SIZE() < 999999999) {
  	std::cerr << "BURST_SIZE must be an integer multiple of BURST_TIME." << std::endl;
  	exit(1);
  }

  config.Write(std::cout);
  emp::Random random(config.SEED());

  PGGWorld world(random, &config);


  int TIMING_REPEAT = config.DATA_INT();


  //Set up files
  //world.SetupPopulationFile().SetTimingRepeat(TIMING_REPEAT);

  std::string file_ending = "_SEED"+std::to_string(config.SEED())+".data";

  world.SetupPGGSymIntValFile(config.FILE_PATH()+"PGGSymVals"+config.FILE_NAME()+file_ending).SetTimingRepeat(TIMING_REPEAT);
  world.SetupHostIntValFile(config.FILE_PATH()+"HostVals"+config.FILE_NAME()+file_ending).SetTimingRepeat(TIMING_REPEAT);
  world.SetupSymIntValFile(config.FILE_PATH()+"SymVals"+config.FILE_NAME()+file_ending).SetTimingRepeat(TIMING_REPEAT);
  if(config.FREE_LIVING_SYMS() == 1){
    world.SetUpFreeLivingSymFile(config.FILE_PATH()+"FreeLivingSyms_"+config.FILE_NAME()+file_ending).SetTimingRepeat(TIMING_REPEAT);
  }

  worldSetup(&world, &config);
  
  world.RunExperiment();
  
  return 0;
}

/*
This definition guard prevents main from being defined twice during testing.
In testing, Catch will define a main function which will initiate tests
(including testing the symbulation_main function above).
*/
#ifndef CATCH_CONFIG_MAIN
int main(int argc, char * argv[]) {
  return symbulation_main(argc, argv);
}
#endif
