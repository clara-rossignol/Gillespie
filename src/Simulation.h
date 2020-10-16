#include "Random.h"
#include "System.h"
#include "Gene.h"

/*!
  The Simulation class is the main class in this program. It constructs the chemical \ref System according to user-specified parameters, and @ref run "runs" the simulation.

  Simulation results are printed to screen or file with the helper functions \ref header (prints a header a the top of data columns) and \ref print (prints the current state of the system as a set of columns under the header).

  A Simulation is made of a vector of \ref genes, which are pointers to \ref Gene objects. These genes are constructed with the function \ref add_genes and \ref add_gene.
Each new gene creates its corresponding set of chemical elements and chemical reactions in a \ref system (see \ref System).

  Time (\ref _time) advances from 0 until it reaches \ref _last. Two types of events are controlled by the \ref _time variable. The next chemical reaction will be performed at time \ref next_t which is a stochastic variable, and the \ref print function is called at every multiple of \ref delta_t. The state of the \ref system may change 0 or more times within each step of \ref delta_t time.
*/

class Simulation {
public:
/*! @name Initialization
  Simulation takes the command-line options and extracts the following parameters from them:
  * @param _last The total time until the end of the simulation
  * @param delta_t The time step for outputs
  * @param outfile The name of the output file (stdout if not specified)
  * @param seed The seed for the random number generator initialized in the constructor
  * @param config_file The (optional) name of a file to pass to \ref load_configuration
*/
///@{
    Simulation() : _time(0), delta_t(_DELTA_T_), next_t(0), _last(_END_TIME_) {};
    Simulation(int, char**);
    ~Simulation();
///@}
/*! @name Running the simulation
  The simulation is performed by calling \ref header once, then \ref run, which calls \ref print at \ref delta_t time intervals.
*/
///@{
    void run() {run(_last, delta_t);}
    void run(const double, const double);
    void header();
    void print();
///@}

/*! @name Configuration
  Configuration of the \ref system can be performed with an input file which contains the 6 rate parameters on one line for each gene in the system: 

     1:.2,.1,12,0.6,6,0.7

  Missing values are replaced by uniform(0,1) random numbers.
  Each line in the file results in a call to \ref add_gene. 

  If no configuration file is given, *n* (a Poisson random variable) genes with random rates (see \ref Gene) are generated with \ref add_genes.
*/
///@{
    void load_configuration(const std::string &infile);
    size_t add_genes(size_t n=0);
    size_t add_gene(const std::array<double, 6>&);
///@}
    const Gene* get_gene(const size_t n) {return genes[n];}
    size_t size() const {return genes.size();}
    size_t system_size() const {return system.size();}

private: 
    System system;
    std::ofstream outfile;
    double _time, delta_t, next_t, _last;
    std::vector<Gene*> genes;

};
