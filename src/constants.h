#include <tclap/CmdLine.h>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>


/*!
  A base class for errors thrown in this program.
  Each error type has a specific exit code.
  Error messages will be passed by the exception caller.
*/
class SimulError : public std::runtime_error {
public:
    SimulError(const char *c, int v=0) : std::runtime_error(c), code(v) {}
    SimulError(const std::string &s, int v=0) : std::runtime_error(s), code(v) {}
    int value() const {return code;}
protected:
    const int code;
};

#define _SIMULERR_(_N, _id) class _N : public SimulError { \
    public: _N(const char *c) : SimulError(c,_id) {} \
            _N(const std::string &s) : SimulError(s,_id) {} };


/// *Specific error codes*
_SIMULERR_(TCLAP_ERROR, 10)
_SIMULERR_(CFILE_ERROR, 20)
_SIMULERR_(OUTPUT_ERROR, 30)

#undef _SIMULERR_

/// * default parameter values *
#define _PLOIDY_ 2
#define _AVG_NUMBER_ 10.
#define _MAX_QUANT_ 100
#define _MAX_TX_RATE_ 100.
#define _MAX_TL_RATE_ 50.
#define _MAX_SWITCH_RATE_ 10.
#define _DELTA_T_ .5
#define _END_TIME_ 10

/// * text messages *
#define _PRGRM_TEXT_ "Gene Simulation with the Gillespie Algorithm"
#define _NUMBER_TEXT_ "Number of genes in simulation"
#define _TIME_TEXT_ "Simulation end time"
#define _DELTAT_TEXT_ "Time interval for outputs"
#define _OFILE_TEXT_ "Output file name"
#define _CFILE_TEXT_ "Configuration file name"
