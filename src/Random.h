#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <vector>
#include <algorithm>

/*!
  This is a random number class based on standard c++-11 generators.
*/

class RandomNumbers {
    
public:
/*! @name Initializing
  The generator \ref rng is a Mersenne twister *mt19937* engine. 
  A seed *s>0* can be provided, by default it is seeded with a *random_device*.
*/
///@{
    RandomNumbers(unsigned long int s=0);
///@}
/*! @name Distributions
  These functions either return a single number 
  or fill a given container with random numbers according to the specified distribution. 
  The additional parameters are the standard parameters of these distributions.
*/
///@{
    double uniform_double(double lower=0, double upper=1);
    template<class T> void uniform_double(T&, double lower=0, double upper=1);
    int uniform_int(int lower=0, int upper=100);
    template<class T> void uniform_int(T&, int lower=0, int upper=100);
    double normal(double mean=0, double sd=1);
    template<class T> void normal(T&, double mean=0, double sd=1);
    double exponential(const double rate=1);
    template<class T> void exponential(T&, const double rate=1);
    int poisson(double mean=1);
    template<class T> void poisson(T&, double mean=1);
///@}

private:
    std::mt19937 rng;
    long int seed;

};

template<class T> void RandomNumbers::uniform_double(T &res, double lower, double upper) {
    std::uniform_real_distribution<> unif(lower, upper);
    for (auto I=res.begin(); I!=res.end(); I++) *I = unif(rng);
}

template<class T> void RandomNumbers::normal(T &res, double mean, double sd) {
    std::normal_distribution<> norm(mean, sd);
    for (auto I=res.begin(); I!=res.end(); I++) *I = norm(rng);
}

template<class T> void RandomNumbers::uniform_int(T &res, int lower, int upper) {
	std::uniform_int_distribution<> unif(lower, upper);
	for (auto I=res.begin(); I!=res.end(); I++) *I = unif(rng);
}

template<class T> void RandomNumbers::exponential(T &res, const double rate) {
	std::exponential_distribution<> expo(rate);
	for (auto I=res.begin(); I!=res.end(); I++) *I = expo(rng);
}

template<class T> void RandomNumbers::poisson(T &res, double mean) {
	std::poisson_distribution<> poiss(mean);
	for (auto I=res.begin(); I!=res.end(); I++) *I = poiss(rng);
}

extern RandomNumbers *_RNG;

#endif //RANDOM_H
