#include "constants.h"
#include "Gene.h"
#include "Random.h"

Gene::Gene(System &sys) : _system(&sys), _ploidy(_PLOIDY_) {
    _RNG->uniform_double(rates, 0, 1);
    rates[0] *= _MAX_SWITCH_RATE_;
    rates[1] *= _MAX_SWITCH_RATE_;
    rates[2] *= _MAX_TX_RATE_;
    rates[4] *= _MAX_TL_RATE_;
    create_gene();
}

Gene::Gene(System &sys, std::array<double, 6> _r) 
    : _system(&sys), _ploidy(_PLOIDY_), rates(_r) {
    create_gene();
}

void Gene::create_gene() {
    elements = {_system->add_element(_ploidy), // gene off 
                _system->add_element(0),       // gene on
                _system->add_element(),        // RNA
                _system->add_element()};       // Protein
    _system->add_reaction({elements[0]}, {elements[0], elements[1]}, {-1, +1}, rates[0]);
    _system->add_reaction({elements[1]}, {elements[0], elements[1]}, {+1, -1}, rates[1]);
    _system->add_reaction({elements[1]}, {elements[2]}, {+1}, rates[2]);
    _system->add_reaction({elements[2]}, {elements[2]}, {-1}, rates[3]);
    _system->add_reaction({elements[2]}, {elements[3]}, {+1}, rates[4]);
    _system->add_reaction({elements[3]}, {elements[3]}, {-1}, rates[5]);
}
