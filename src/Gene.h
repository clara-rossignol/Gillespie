#include "System.h"

/*!
  The Gene class is an interface to create standard chemical reactions for gene transcription.
  A Gene is made of 4 quantities (gene_off, gene_on, RNA, Protein) and 
  6 reactions (activation, inactivation, transcription, rna degradation, translation, protein degradation).

  To comply with standard Gillepsie reaction systems, gene activity is represented by 2 elements
  (on / off) which are always complementary to each other: gene_on+gene_off=ploidy (number of copies of the gene).
*/

class Gene {
public:
/*! @name Initializing
  A Gene is part of a bigger system and needs a reference to it. 
  It can be initialized with the 6 reaction rates, otherwise these rates are picked from a uniform distribution.
*/
///@{
    Gene(System&);
    Gene(System&, std::array<double, 6>);
///@}
/*! @name Gene data
  State is the number of active copies (among 'ploidy' copies), transcript the number of RNAs present in the system, and protein the number of proteins.
*/
///@{
    short  state() const {return _system->quant(elements[1]);}
    short  inactive() const {return _system->quant(elements[0]);}
    size_t transcript() const {return _system->quant(elements[2]);}
    size_t protein() const {return _system->quant(elements[3]);}
    short ploidy() const {return _ploidy;}
    void ploidy(const short _p) {_ploidy = _p;}
///@}
/*! @name System indices
  Indices of the (on) state, transcript, protein elements in the overall system.
*/
///@{
    size_t state_id() const {return elements[1];}
    size_t transcript_id() const {return elements[2];}
    size_t protein_id() const {return elements[3];}
///@}
/*! @name Reaction rates
  Access to the 6 reaction rates for this gene.
*/
///@{
    double on_rate() const {return rates[0];}
    double off_rate() const {return rates[1];}
    double transcript_rate() const {return rates[2];}
    double tdegrade_rate() const {return rates[3];}
    double translate_rate() const {return rates[4];}
    double pdegrade_rate() const {return rates[5];}
///@}

protected:
    System *_system;
    short _ploidy;
    std::array<size_t, 4> elements;
    std::array<double, 6> rates;

private:
    void create_gene();
};
