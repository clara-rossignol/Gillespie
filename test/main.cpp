#include <gtest/gtest.h>
#include "constants.h"
#include "Random.h"
#include "Simulation.h"
#include "System.h"

RandomNumbers *_RNG = new RandomNumbers(23948710923);

TEST(Random, distributions) {
    double mean = 0;
    double input_mean(1.35), input_sd(2.8);
    std::vector<double> res;
    res.resize(10000);
    double delta = input_sd*sqrt(3.0);
    double lower = input_mean-delta, upper = input_mean+delta;
    _RNG->uniform_double(res, lower, upper);
    for (auto I : res) {
        EXPECT_GE(I, lower);
        EXPECT_LT(I, upper);
        mean += I*1e-4;
    }
    EXPECT_NEAR(input_mean, mean, 3e-2*input_sd);
    _RNG->normal(res, input_mean, input_sd);
    mean = 0;
    for (auto I : res) mean += I*1e-4;
    EXPECT_NEAR(input_mean, mean, 2e-2*input_sd);
    _RNG->poisson(res, input_mean);
    mean = 0;
    for (auto I : res) mean += I*1e-4;
    EXPECT_NEAR(input_mean, mean, 2e-2*input_mean);
}

TEST(Simulation, readconfig) {
    Simulation sim;
    sim.load_configuration("../test/gene_config.txt");
    EXPECT_DOUBLE_EQ(8., sim.get_gene(1)->translate_rate());
    EXPECT_DOUBLE_EQ(.6, sim.get_gene(0)->tdegrade_rate());
}

TEST(Simulation, addgenes) {
    Simulation sim;
    size_t ng(4);
    sim.add_genes(ng);
    EXPECT_EQ(ng, sim.size());
    EXPECT_EQ(4*ng, sim.system_size());
}

TEST(System, initRun) {
    System sys;
    size_t e0 = sys.add_element(1),
        e1 = sys.add_element(2),
        e2 = sys.add_element(0);
    EXPECT_EQ(3, sys.size());
    EXPECT_EQ(2, sys.quant(1));
    sys.add_reaction({e0, e1}, {e2}, {1}, 2.0);
    sys.add_reaction({e0}, {e1}, {-1}, 0.5);
    EXPECT_DOUBLE_EQ(.5, sys.reaction_coefficient(1));
    EXPECT_DOUBLE_EQ(4.5, sys.total_rate());
    auto ins = sys.reaction_inputs(0);
    EXPECT_EQ(2, ins.size());
    EXPECT_EQ(0, ins[0]);
    EXPECT_EQ(1, ins[1]);
    sys.step(1.);
    EXPECT_EQ(1, sys.quant(2));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

