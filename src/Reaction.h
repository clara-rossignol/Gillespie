#ifndef REACTION_H
#define REACTION_H

class System;

/*!
  The Reaction class implements Gillespie's notion of a chemical reaction. It is defined by 
<ul>
  <li>a reaction rate coefficient</li>
  <li>a set of inputs (elements from the system that enter the reaction)</li>
  <li>a set of output elements and their increments (by how much each element's concentration changes when the reaction is performed)</li>
</ul>
*/

class Reaction {
public:
/*! @name Reaction data
  Constructor only takes the reaction rate coefficient as parameter.

  Inputs are a set of element indices.

  Outputs are pairs (element index, increment).
*/
///@{
    Reaction(double _c=1) : _coeff(_c) {}
    void input(const size_t idx) {_input.push_back(idx);}
    std::vector<size_t> inputs() const {return _input;}
    void output(const size_t idx, const int incr) {_output.insert({idx, incr});}
///@}
/*! @name Reaction updates
  When the reaction is performed, each output is incremented according to the \ref _output table, and the indices of theses outputs are returned.

  When the inputs have changed, the reaction rate must be updated with the update() function.
*/
///@{
    const std::vector<size_t> react(System*);
    void update(const System*);
///@}
/*! @name Reaction rates
  The current reaction rate is the product of the raction rate coefficient and the concentrations of all inputs.
*/
///@{
    double rate() const {return _rate;}
    void coeff(const double _c) {_coeff = _c;}
    double coeff() const {return _coeff;}
///@}

protected:
    std::vector<size_t> _input;
    std::map<size_t, int> _output;
    double _coeff, _rate;

};

#endif //REACTION_H
