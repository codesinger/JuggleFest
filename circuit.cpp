
/*!
 * \file circuit.cpp
 *
 * \brief Contains the implementation of circuit
 *
 * \author Stewart L. Palmer
 */

#include <regex>
#include <assert.h>
#include "juggler_circuit_set_const_iterator.h"
#include "scheduler.h"
#include "circuit.h"

using namespace ::std;


// Regular expression to scan a circuit string and extract the name of the circuit as well as
// its preferred talent (hand-eye coordination, endurance, and pizzazz)
const string circuit::_scan_exp =
 "^C\\s+([a-zA-Z0-9]+)\\s+([a-zA-Z]+):([0-9]+)\\s+([a-zA-Z]+):([0-9]+)\\s+([a-zA-Z]+):([0-9]+)";
//        Name                      H:9                     E:9                     P:9
//        $1                       $2 $3                   $4 $5                   $6 $7


/*                                                                          */
/****************************************************************************/
/*     C O N S T R U C T O R                                                */
/****************************************************************************/
/*                                                                          */
circuit::circuit(
  scheduler          &sched,       /*!< Reference to the scheduler          */
  const string       &definition)  /*!< String that defines the circuit     */
  :
  talent(sched)
{
  smatch    matches;
  regex scan_rx(_scan_exp);

  const bool q = regex_search(definition, matches, scan_rx);
  assert(q);
  set_name(matches[1]);
  const int talent_rc = set_talents(matches, 2);
  assert(talent_rc == 0);
}


/*                                                                          */
/****************************************************************************/
/*     R E A S S I G N _ J U G G L E R                                      */
/****************************************************************************/
/*                                                                          */
void circuit::reassign_juggler(
  const juggler_circuit   &jc)     /*!< juggler_circuit to reassign         */
{
  const juggler_circuit *waiter = &jc;
  if ( is_not_full()  ||           /* If there is room for more or          */
       (jc.score() > lowest_score()) )/* This is a better fit than any      */
    {                              /* Will assign this juggler              */
      waiter = 0;                  /* This one will fit here                */
      if (is_full())               /* If no more room                       */
        {                          /* Will remove lowest assigned           */
          waiter = remove_lowest_assigned_juggler();
          const juggler_circuit &waiting = *waiter;
          waiting.clear_assignment();/* Mark no longer assigned             */
        }
      assign_juggler(jc);          /* Assign this one to ourself            */
    }
  if (waiter != 0)                 /* This one won't fit here               */
    {                              /* Put it elsewhere                      */
      const juggler_circuit &wjc = *waiter;
      juggler &jug = wjc.jug();     /* Get its next preferred circuit        */
      const juggler_circuit *const n = jug.get_next_preference(wjc.preference());
      if (n == 0)                  /* Has no more preferred circuits        */
        {                          /* Add it to the list of orphans         */
          sched().add_orphaned_juggler(jug);
        }
      else                         /* Try to add it to next preferred       */
        {                          /*  circuit                              */
          const juggler_circuit &next_jc = *n;
          circuit &next_circ = next_jc.circ();
          next_circ.reassign_juggler(next_jc);
        }
    }
}

/*                                                                          */
/****************************************************************************/
/*     J U G G L E R _ S U M                                                */
/****************************************************************************/
/*                                                                          */
int circuit::juggler_sum() const
{
  assert(is_full());
  int sum = 0;

  juggler_circuit_set_const_iterator  it(assigned());
  const juggler_circuit *j = it.next();
  while (j != 0)
  {
    const juggler_circuit &jc = *j;
    sum += jc.juggler_id();
    j = it.next();
  }

  return sum;
}


/*                                                                          */
/****************************************************************************/
/*     S H O W _ A S S I G N M E N T S                                      */
/****************************************************************************/
/*                                                                          */
void circuit::show_assignments(
  ostream    &os)                  /*!< The stream into which we stream     */
const
{
  os << name();
  int n = 0;
  juggler_circuit_set_const_iterator  assigned_iterator(assigned());
  const juggler_circuit *j = assigned_iterator.last();
  while(j != 0)
  {
    const juggler_circuit &jc = *j;
    if (n == 0)
      os << " ";
    else
      os << ", ";
    const juggler &jug = jc.jug();
    os << jug.name() << " ";
    jug.show_requests(os);
    n++;
    j = assigned_iterator.previous();
  }
}


/*                                                                          */
/****************************************************************************/
/*     V A L I D A T E _ A S S I G N M E N T                                */
/****************************************************************************/
/*                                                                          */
int circuit::validate_assignments(
  ostream            &os)          /*!< Stream for error reporting          */

{
  int rc = 0;

  if (assigned_count() != jugglers_per_circuit())
    {
      os << "Circuit " << name() << " is assigned " << assigned_count() <<
            " jugglers instead of the required " << jugglers_per_circuit() << endl;
      rc = 1;
    }

  juggler_circuit_set_const_iterator  asg(assigned());
  const juggler_circuit *j = asg.first();
  while (j != 0)
  {
    const juggler_circuit &jc = *j;
    const juggler &jug = jc.jug();
    const juggler_circuit &jca = jug.assignment();
    if (&jc != &jca)
      {
        os << "Juggler " << jug.name() << " is in the assigned list for circuit " <<
              name() << " but is marked assigned to circuit " << jca.circ().name() << endl;
        rc = 1;
      }
    j = asg.next();
  }

  return rc;
}


/*                                                                          */
/****************************************************************************/
/*     P R I N T _ S E L F                                                  */
/****************************************************************************/
/*                                                                          */
ostream &circuit::print_self(
  ostream    &os)                  /*!< The stream into which we stream     */
const
{
  os << "C:";
  talent::print_self(os);
  os << " " << assigned().size()  << " jugglers assigned:\n"  << assigned();

  return os;
}
