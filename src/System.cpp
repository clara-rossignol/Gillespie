#include "constants.h"
#include "System.h"
#include "Random.h"

System::~System() {
    for (auto I : _reactions) 
        if (I) delete I;
}

size_t System::add_element(const int q) {
    size_t qq;
    if (q<0) qq = _RNG->uniform_int(0, _MAX_QUANT_);
    else     qq = (size_t)q;
    _quant.push_back(qq);
    return _quant.size()-1;
}

size_t System::add_reaction(const std::vector<size_t> ins, 
                            const std::vector<size_t> outs, 
                            const std::vector<int> incrs, 
                            const double rate) {
    Reaction *_reac = new Reaction(rate);
    size_t ridx(_reactions.size());
    _reactions.push_back(_reac);
    for (size_t n=0; n<ins.size(); n++) {
        _reac->input(ins[n]);
        element2reactions.insert({ins[n], ridx});
    }
    for (size_t n=0; n<incrs.size() && n<outs.size(); n++) 
        _reac->output(outs[n], incrs[n]);
    _reac->update(this);
    return ridx;
}

double System::total_rate() const {
	double tot(0.0);
	for(auto I : _reactions) {
		tot += I->rate();
	}
	return tot;
}

double System::reaction_coefficient(size_t id) const {
    if (id < _reactions.size()) return _reactions[id]->coeff();
    return -1;
}

std::vector<size_t> System::reaction_inputs(size_t id) const {
    std::vector<size_t> retvec;
    if (id < _reactions.size()) 
        retvec = _reactions[id]->inputs();
    return retvec;
}

void System::step(double nextr) {
    std::vector<size_t> modifs;
    for (auto I : _reactions) {
        nextr -= I->rate();
        if (nextr < 0) {
            modifs = I->react(this);
            break;
        }
    }
    std::set<size_t> visited;
    for (auto I : modifs) {
        auto bounds = element2reactions.equal_range(I);
        for (auto J=bounds.first; J!=bounds.second; J++)
            if (!visited.count(J->second)) {
                _reactions[J->second]->update(this);
                visited.insert(J->second);
            }
    }
}
