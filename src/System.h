#ifndef SYSTEM_H
#define SYSTEM_H

#include "Reaction.h"

/*!
  The System class holds all the chemical concentrations (\ref _quant) and the reactions (\ref _reactions) in the system. 

  A chemical reaction is an object of class \ref Reaction. 
  It is represented by an index in the vector \ref _reactions holding pointers to the actual objects.

  A chemical element is an index into the vector \ref _quant, it is an input to a set of reactions (indices) via the map \ref element2reactions.

*/

class System {
public:
    ~System();
/*! @name Initializing
  The system is built by adding elements and reactions.

  When a new element is added, the quantity can be specified or (by default) drawn from a uniform distribution.

  When a new reaction is added, its inputs, outputs, increments and rate coefficient must be specified.
  The increments are given in a vector and taken in the same order as the outputs.

  By adding a reaction, a \ref Reaction is constructed and pushed into \ref _reactions. The map \ref element2reactions is updated and a call to the \ref Reaction::update is made.
*/
///@{
    size_t add_element(const int q=-1);
    size_t add_reaction(const std::vector<size_t> ins, const std::vector<size_t> outs,
                        const std::vector<int> incrs, const double rate);
///@}
/*! @name System data
  The system \ref size is the number of chemical elements, the element's concentration (quantity) is available via the element's index, and similarly for the reaction rate coefficient.

 The \ref total_rate is the sum of all reaction rates in the system, via Reaction::rate.

 The \ref reaction_inputs returns the vector of all elements listed as inputs in a reaction, using Reaction::inputs.
*/
///@{
    size_t size() const {return _quant.size();}
    size_t quant(size_t index) const {return _quant[index];}
    double total_rate() const;
    double reaction_coefficient(size_t) const;
    std::vector<size_t> reaction_inputs(size_t) const;
///@}
/*! @name System update
  The system is updated by deciding which reaction will be performed (according to the random number nextr between 0 and \ref total_rate) and calls \ref Reaction::react on it. This in turns calls \ref increment on the reaction's outputs. After that, each of the reactions linked to these outputs are updated with \ref Reaction::update.
*/
///@{
    void step(double nextr);
    void increment(const size_t index, const int incr) {_quant[index] += incr;}
///@}

protected:
    std::vector<Reaction*> _reactions;
    std::vector<size_t> _quant;
    std::multimap<size_t, size_t> element2reactions;

};

#endif //SYSTEM_H
