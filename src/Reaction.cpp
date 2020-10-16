#include "constants.h"
#include "Reaction.h"
#include "System.h"

const std::vector<size_t> Reaction::react(System *_sys) {
    std::vector<size_t> modifs;
    for (auto I : _output) {
        _sys->increment(I.first, I.second);
        modifs.push_back(I.first);
    }
    return modifs;
}

void Reaction::update(const System *_sys) {
    _rate = _coeff;
    for (auto I : _input) _rate *= (double)_sys->quant(I);
}
