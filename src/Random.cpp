#include "Random.h"

RandomNumbers::RandomNumbers(unsigned long int s) 
:seed(s)
{
	if (seed == 0) {
		std::random_device rd;
		seed = rd();
	}
	rng.seed(seed);
}

double RandomNumbers::uniform_double(double lower, double upper) {
	std::uniform_real_distribution<> unif(lower, upper);
	return unif(rng);
}

int RandomNumbers::uniform_int(int lower, int upper)
{
	std::uniform_int_distribution<> unif(lower, upper);
	return unif(rng);
}

double RandomNumbers::normal(double mean, double sd)
{
	std::normal_distribution<> norm(mean, sd);
	return norm(rng);
}

double RandomNumbers::exponential(const double rate)
{
	std::exponential_distribution<> expo(rate);
	return expo(rng);
}

int RandomNumbers::poisson(double mean)
{
	std::poisson_distribution<> poiss(mean);
	return poiss(rng);
}
