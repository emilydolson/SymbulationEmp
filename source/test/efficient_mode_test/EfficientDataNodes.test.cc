#include "../../efficient_mode/EfficientHost.h"
#include "../../efficient_mode/EfficientSymbiont.h"
#include "../../efficient_mode/EfficientWorld.h"

TEST_CASE("GetEfficiencyDataNode", "[efficient]"){
  GIVEN("a world"){
    emp::Random random(17);
    SymConfigBase config;
    int int_val = 0;
    double points = 10;
    EfficientWorld w(random);
    w.Resize(4);
    w.SetFreeLivingSyms(1);
    config.SYM_LIMIT(3);

    emp::DataMonitor<double>& sym_efficiency_node = w.GetEfficiencyDataNode();
    REQUIRE(std::isnan(sym_efficiency_node.GetMean()));

    WHEN("efficient symbionts are added to the world"){
      size_t num_syms = 6;
      double efficiencies[6] = {0, 0.3, 0.45, 0.6, 0.77, 1.0};
      double expected_av = 0.52;

      Host *h = new EfficientHost(&random, &w, &config, int_val);
      w.AddOrgAt(h, 0);

      for(size_t i = 0; i < (num_syms/2); i++){
        w.AddOrgAt(new EfficientSymbiont(&random, &w, &config, int_val, points, efficiencies[i]), emp::WorldPosition(0, i));
        h->AddSymbiont(new EfficientSymbiont(&random, &w, &config, int_val, points, efficiencies[i+3]));
      }

      w.Update();
      THEN("their efficiency is tracked by a data node"){
        REQUIRE(sym_efficiency_node.GetMean() < (expected_av + 0.0001));
        REQUIRE(sym_efficiency_node.GetMean() > (expected_av - 0.0001));
      }
    }
  }
}
