#include "constants.h"
#include "Simulation.h"

Simulation::Simulation(int argc, char **argv) {
    try {
        TCLAP::CmdLine cmd(_PRGRM_TEXT_);
        TCLAP::ValueArg<double> maxt("t", "time", _TIME_TEXT_, false, _END_TIME_, "double");
        cmd.add(maxt);
        TCLAP::ValueArg<double> delt("d", "delta_t", _DELTAT_TEXT_, false, _DELTA_T_, "double");
        cmd.add(delt);
        TCLAP::ValueArg<std::string> ofile("o", "outptut", _OFILE_TEXT_, false, "", "string");
        cmd.add(ofile);
        TCLAP::ValueArg<std::string> cfile("c", "config", _CFILE_TEXT_, false, "", "string");
        cmd.add(cfile);
        TCLAP::ValueArg<long> seed("S", "seed", "Random seed", false, 0, "long");
        cmd.add(seed);
        cmd.parse(argc, argv);
        _RNG = new RandomNumbers(seed.getValue());
        std::string conf(cfile.getValue());
        if (!conf.empty()) load_configuration(conf);
        else               add_genes();
        _last = maxt.getValue();
        delta_t = delt.getValue();
        std::string outfname = ofile.getValue();
        if (outfname.length()) outfile.open(outfname, std::ios_base::out);
    } catch(TCLAP::ArgException &e) {
        throw(TCLAP_ERROR("Error: " + e.error() + " " + e.argId()));
    }
    header();
}

Simulation::~Simulation() {
    for (auto g : genes) if (g) delete g;
    if (outfile.is_open()) outfile.close();
    std::cout.flush();
}

//A FINIR 
void Simulation::load_configuration(const std::string &infile) {
    try {
		std::ifstream confstr(infile);
		std::string item, key, line;
		
		if(confstr.is_open()) {
			while(std::getline(confstr, line)) {
				line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
				if (line[0] == '#') continue;
				std::stringstream ss(line);
				std::getline(ss, key, ':');
				if (key.empty()) continue;
				
				}
				confstr.close();
		}
        } else throw(CFILE_ERROR("Could not open configuration file " + infile));
    } catch(std::ifstream::failure &e) {
        throw(CFILE_ERROR("Error with configuration file " + infile + ": " + e.what()));
    }
}

size_t Simulation::add_genes(size_t n) {
    if (n<1) n = _RNG->poisson(_AVG_NUMBER_);
    for (size_t m=0; m<n; m++)
        genes.push_back(new Gene(system));
    return genes.size()-1;    
}

size_t Simulation::add_gene(const std::array<double, 6> &r) {
    genes.push_back(new Gene(system, r));
    return genes.size()-1;
}

void Simulation::run(const double time, const double delta_t) {
    _time = 0;
    next_t = 0;
    print();
    for (next_t=delta_t; _time<time; ) {
        double total_rate = system.total_rate();
        if (total_rate <= 0) {
            std::cerr << "Rates vanished: " << total_rate << std::endl;
            return;
        }
        double 
            nextT = _RNG->exponential(total_rate),
            nextR = _RNG->uniform_double(0, total_rate);
        for (_time+=nextT; _time>next_t; next_t+=delta_t) print();
        system.step(nextR);
    }
}

void Simulation::header() {
    std::ostream *outstr = &std::cout;
    if (outfile.is_open()) outstr = &outfile;
    *outstr << "time";
    for (size_t n=1; n<=genes.size(); n++)
        *outstr << "\tD" << n << "\tR" << n << "\tP" << n;
    *outstr << std::endl;
}

void Simulation::print() {
    std::ostream *outstr = &std::cout;
    if (outfile.is_open()) outstr = &outfile;
    *outstr << next_t;
    for (auto g : genes) 
        *outstr << "\t" << g->state() 
                << "\t" << g->transcript() 
                << "\t" << g->protein();
    *outstr << std::endl;
}

