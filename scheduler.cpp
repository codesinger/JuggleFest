
/*!
 * \file scheduler.cpp
 *
 * \brief Contains the implementation of scheduler
 *
 * \author Stewart L. Palmer
 */

#include <fstream>
#include "juggler_circuit.h"
#include "circuit_set_iterator.h"
#include "juggler_set_iterator.h"
#include "juggler_circuit_set_iterator.h"
#include "scheduler.h"

using namespace ::std;

/*                                                                          */
/****************************************************************************/
/*     C O N S T R U C T O R                                                */
/****************************************************************************/
/*                                                                          */
scheduler::scheduler(
  const char  *file_name)          /*!< Name of input file                  */
  :
  _file_name(file_name)
{
  {
    ifstream inp(file_name);
    char   line[4096];
    int line_no = 1;

    inp.getline(line, sizeof(line));
    while (inp.good())
    {
      const char type = toupper(line[0]);
      const string definition(line);
      if (type == 'C')
        {
          circuit *const c = new circuit(*this, definition);
          circuit &crs = *c;
          _circuits.add(crs);
        }
      else if (type == 'J')
        {
          juggler *const j = new juggler(*this, definition, _circuits);
          juggler &jug = *j;
          _jugglers.add(jug);
        }
      else
        {
          if (definition.size() != 0)
            {
              cout << __FILE__ << ":" << __LINE__ << ": " <<
                      "Do not understand line " << line_no << ": <" << definition << ">" << endl;
            }
        }
      inp.getline(line, sizeof(line));
      line_no++;
    }
    assert((juggler_count() % circuit_count()) == 0);
  }
}


/*                                                                          */
/****************************************************************************/
/*     A S S I G N                                                          */
/****************************************************************************/
/*                                                                          */
void scheduler::assign()
{
  do_assignments();
  if (orphan_juggler_count() != 0)
    distribute_orphans();
}


/*                                                                          */
/****************************************************************************/
/*     D O _ A S S I G N M E N T S                                          */
/****************************************************************************/
/*                                                                          */
void scheduler::do_assignments()
{
  juggler_set_iterator   jit(_jugglers);
  const juggler *j = jit.next();
  while (j != 0)
  {
    const juggler &jug = *j;
    jug.add_to_first_preferred_circuit();
    j = jit.next();
  }
}


/*                                                                          */
/****************************************************************************/
/*     D I S T R I B U T E _ O R P H A N S                                  */
/****************************************************************************/
/*                                                                          */
void scheduler::distribute_orphans()
{
  circuit_set_iterator   cit(_circuits);
  circuit *c = cit.next();
  while (c != 0)
  {
    circuit &circ = *c;
    while (circ.is_not_full())
    {
      juggler *j = next_orphan();
      assert(j != 0);
      juggler &jug = *j;
      const int new_preference = jug.highest_preference() + 1;
      const juggler_circuit *jcp = jug.add_circuit(circ, new_preference);
      assert(jcp != 0);
      const juggler_circuit &jc = *jcp;
      circ.assign_juggler(jc);
    }
    c = cit.next();
  }
}


/*                                                                          */
/****************************************************************************/
/*     G E T _ C I R C U I T                                                */
/****************************************************************************/
/*                                                                          */
const circuit *scheduler::get_circuit(
  const string    &circuit_name)
{
  circuit *c = 0;
  const int rc = _circuits.find(circuit_name, c);
  if (rc != 0)
    c = 0;

  return c;
}


/*                                                                          */
/****************************************************************************/
/*     S H O W _ A S S I G N M E N T S                                      */
/****************************************************************************/
/*                                                                          */
void scheduler::show_assignments(
  ostream    &os)
{
  circuit_set_iterator   cit(_circuits);
  circuit *c = cit.next();
  while (c != 0)
  {
    circuit &circ = *c;
    circ.show_assignments(os);
    os << "\n";
    c = cit.next();
  }
}


/*                                                                          */
/****************************************************************************/
/*     V A L I D A T E _ A S S I G N M E N T S                              */
/****************************************************************************/
/*                                                                          */
int scheduler::validate_assignments(
  ostream    &os)
{
  int rc = 0;

  {
    circuit_set_iterator   cit(_circuits);
    circuit *c = cit.next();
    while (c != 0)
    {
      circuit &circ = *c;
      const int lrc = circ.validate_assignments(os);
      if (lrc != 0)
        rc = 1;
      c = cit.next();
    }
  }

  {
    juggler_set_iterator   jit(_jugglers);
    juggler *j = jit.next();
    while (j != 0)
    {
      juggler &jug = *j;
      const int lrc = jug.validate_assignment(os);
      if (lrc != 0)
        rc = 1;
      j = jit.next();
    }
  }

  return rc;
}
