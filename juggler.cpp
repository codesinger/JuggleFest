
/*!
 * \file juggler.cpp
 *
 * \brief Contains the implementation of juggler
 *
 * \author Stewart L. Palmer
 */

#include <regex>
#include <sstream>
#include <assert.h>
#include "juggler_circuit.h"
#include "circuit_set.h"
#include "juggler.h"

using namespace ::std;


// Regular expression to scan a juggler string and extract the name of the juggler, its talent
// (hand-eye coordination, endurance, and pizzazz), and comma separated string of preferred circuits.
const string juggler::_scan_exp =
 "^J\\s+([a-zA-Z0-9]+)\\s+([a-zA-Z]+):([0-9]+)\\s+([a-zA-Z]+):([0-9]+)\\s+([a-zA-Z]+):([0-9]+)\\s+([a-zA-Z0-9,]+)*";
//        Name                      H:9                     E:9                     P:9           string of
//                                                                                                preferred circuits
//        $1                       $2 $3                   $4 $5                   $6 $7          $8



/*                                                                          */
/****************************************************************************/
/*     C O N S T R U C T O R                                                */
/****************************************************************************/
/*                                                                          */
juggler::juggler(
  scheduler           &sched,      /*!< Reference to the scheduler          */
  const string        &definition, /*!< String that defines the juggler     */
  circuit_set         &circuits)   /*!< The set of all circuits             */
  :
  talent(sched),
  _assignment(0)
{
  smatch    matches;
  regex scan_rx(_scan_exp);
  // Used to detect a juggler with duplicate circuit preferences
  circuit_set   local_circuits;

  const bool q = regex_search(definition, matches, scan_rx);
  assert(q);
  set_name(matches[1]);
  const int talent_rc = set_talents(matches, 2);
  assert(talent_rc == 0);

  const string circuits_list = matches[8];
  istringstream is(circuits_list);
  string   single_circuit;
  int preference = 0;
  while(getline(is, single_circuit, ','))
  {
    circuit  *c = 0;
    const int lrc = circuits.find(single_circuit, c);
    assert(lrc == 0);
    circuit &circ = *c;
    local_circuits.add(circ);      /* Check for duplicates in pref list     */
    add_circuit(circ, preference);
    preference++;
  }
}


/*                                                                          */
/****************************************************************************/
/*     A D D _ C I R C U I T                                                */
/****************************************************************************/
/*                                                                          */
const juggler_circuit *juggler::add_circuit(
  circuit     &circ,               /*!< The circuit to add                  */
  const int    preference)         /*!< The preference for this circuit     */
{
  juggler &self = *this;
  const int score = self.dot(circ);
  const juggler_circuit  *j = new juggler_circuit(self, circ, score, preference);
  const juggler_circuit  &jc = *j;
  self.add_request(jc);

  return j;
}


/*                                                                          */
/****************************************************************************/
/*     A D D _ R E Q U E S T                                                */
/****************************************************************************/
/*                                                                          */
void juggler::add_request(
  const juggler_circuit   &jc)     /*!< juggler_circuit to add              */
{
  _requested.push_back(&jc);
}


/*                                                                          */
/****************************************************************************/
/*     A D D _ T O _ F I R S T _ P R E F E R R E D _ C I R C U I T          */
/****************************************************************************/
/*                                                                          */
void juggler::add_to_first_preferred_circuit() const
{
  const juggler_circuit *j = _requested[0];
  const juggler_circuit &jc = *j;
  circuit &circ = jc.circ();
  circ.reassign_juggler(jc);
}


/*                                                                          */
/****************************************************************************/
/*     S H O W _ R E Q U E S T S                                            */
/****************************************************************************/
/*                                                                          */
void juggler::show_requests(
  ostream     &os)                 /*!< Output stream for requests          */
const
{
  for (unsigned int i = 0; i < _requested.size(); i++)
    {
      const juggler_circuit *j = _requested[i];
      const juggler_circuit &jc = *j;
      if (i != 0)
        os << " ";
      os << jc.circuit_name() << ":" << jc.score();
    }
}


/*                                                                          */
/****************************************************************************/
/*     V A L I D A T E _ A S S I G N M E N T                                */
/****************************************************************************/
/*                                                                          */
int juggler::validate_assignment(
  ostream     &os)
{
  int rc = 0;
  if ( !is_assigned() )
    {
      os << "Juggler " << name() << " is not assigned!" << endl;
      return 1;
    }
  const juggler_circuit &assigned = assignment();
  const circuit  &assigned_circuit = assigned.circ();
  for (unsigned int i = 0; i < _requested.size(); i++)
    {
      const juggler_circuit *j = _requested[i];
      const juggler_circuit &jc = *j;
      const circuit &this_circuit = jc.circ();
      if (&assigned == &jc)
        {
          break;
        }

      if (jc.score() > this_circuit.lowest_score())
        {
          os << name() << " is assigned to " << assigned_circuit.name() <<
            " (Pref " << assigned.preference() << ", Score " << assigned.score() <<
            ", Low = " << assigned_circuit.lowest_score() <<
            ").  Better fit in " << this_circuit.name() << " (Pref " <<
            jc.preference() << ", Score " << jc.score() << ", Low = " << this_circuit.lowest_score() <<
            ")." << endl;
          rc = 1;
        }
    }

  return rc;
}


/*                                                                          */
/****************************************************************************/
/*     P R I N T _ S E L F                                                  */
/****************************************************************************/
/*                                                                          */
ostream &juggler::print_self(
  ostream    &os)                  /*!< The stream into which we stream     */
const
{
  os << "J:";
  talent::print_self(os);
  os << ": ";
  if ( !is_assigned() )
    os << "Not assigned to a circuit.";
  else
    os << "Assigned to circuit " << assignment().circuit_name();
  os << "\n";

  return os;
}
