#ifndef circuit_h_included
#define circuit_h_included 1

/*!
 * \file circuit.h
 *
 * \brief Contains the definition of circuit
 *
 * \author Stewart L. Palmer
 */

#include <iostream>
#include <vector>
#include <assert.h>
#include "talent.h"
#include "juggler_set.h"
#include "juggler_circuit_set.h"
#include "juggler_circuit_set_iterator.h"
#include "juggler_circuit_set_const_iterator.h"


/*!
 * \brief Represents a circuit to which a juggler might be assigned
 */
class circuit : public talent
{
public:

  /*!
   * \brief Standard constructor
   *
   * \param sched      Reference to the scheduler
   * \param definition The string that defines the circuit.  This is the record
   *                   from the input file, which the circuit parses.
   */
  explicit circuit(
    scheduler          &sched,
    const std::string  &definition);


  /*!
   * \brief Return a count of jugglers assigned to this circuit
   */
  unsigned int assigned_count() const
  { return assigned().size(); }


  /*!
   * \brief Return the sum of all of the juggler IDs assigned to this circuit
   *
   * Used at the end of the program to get the sum of all jugglers assigned
   * to circuit 1790.
   *
   * \return The sum of all of the juggler IDs assigned to this circuit
   */
  int juggler_sum() const;


  /*!
   * \brief Return true if this circuit is full
   */
  bool is_full() const
  {
    assert( !(assigned_count() > jugglers_per_circuit()) );
    bool is_it_full = false;
    if (assigned_count() == jugglers_per_circuit())
      is_it_full = true;

    return is_it_full;
  }


  /*!
   * \brief Return true if this circuit is not full
   */
  bool is_not_full() const
  { return ( !is_full() ); }


  /*!
   * \brief Return the lowest score of any juggler assigned to this circuit
   *
   * The first juggler in the assigned set has the lowest score
   *
   * \return The lowest score of any juggler assigned to this circuit
   */
  int lowest_score() const
  {
    int low = INT_MIN;
    juggler_circuit_set_const_iterator  assigned_iterator(_assigned);
    const juggler_circuit *const j = assigned_iterator.first();
    if (j != 0)
      {
        const juggler_circuit &jc = *j;
        low = jc.score();
      }

    return low;
  }


  /*!
   * \brief Return and remove the assigned juggler with the lowest score
   *
   * The first juggler in the assigned set has the lowest score
   *
   * \return Pointer to the assigned juggler with the lowest score or zero if
   *         no jugglers are adssigned to the circuit
   */
  const juggler_circuit *remove_lowest_assigned_juggler()
  {
    juggler_circuit_set_iterator  assigned_iterator(_assigned);
    const juggler_circuit *j = assigned_iterator.first();
    if (j != 0)
      {
        assigned_iterator.remove_current();
      }

    return j;
  }


  /*!
   * \brief Assign a juggler to this circuit
   *
   * The circuit must not be full.  This is an unconditional assignment.
   */
  void assign_juggler(
    const juggler_circuit   &jc)   /*!< The juggler to assign               */
  {
    assert(is_not_full());
    assert(&jc.circ() == this);
    assigned().add(jc);
    jc.set_assignment();
  }


  /*!
   * \brief Try to find a home for a juggler
   *
   * This tries to assign the juggler to the circuit.  If the juggler does
   * not fit, then we still have a juggler to reassign.  If the juggler is
   * a better fit than all the others, we have to remove the lowest scoring
   * juggler.  In either case, we still have a juggler to assign.  Find the
   * next preference for the juggler.  If it has no next preference, add it
   * to the list of orphaned jugglers.  If it has a next preference, call
   * ourselves recursively to try to assign the juggler to the circuit of
   * next preference.  Continue until the juggler is assigned somewhere or
   * or finally added to the set of orphaned jugglers.  These are jugglers
   * that cannot fit in any of their preferred circuits.
   */
  void reassign_juggler(
    const juggler_circuit   &jc    /*!< juggler_circuit to reassign         */
                               );


  /*!
   * \brief Show all of the juggler assignments for this circuit
   */
  void show_assignments(
    std::ostream    &os)           /*!< The stream into which we stream     */
  const;


  /*!
   * \brief Validate the assignments to this circuit
   *
   * Circuit must have the required number of jugglers and they should all
   * be marked assigned to the circuit.
   *
   * \return Zero if no errors were found
   */
  int validate_assignments(
    std::ostream            &os    /*!< Stream for error reporting          */
                               );



  /*!
   *  \brief Stream object out to a stream
   *
   * \return The same stream as the input to allow for chained operators.
   */
  friend std::ostream &operator<<(
    std::ostream    &os,           /*!< The stream into which we stream     */
    const circuit   &cn)           /*!< The object to be streamed           */
  {
    return cn.print_self(os);
  }

private:

  /*!
   * \brief The copy constructor is deliberately private and unimplemented.
   *
   * \param rhs the object from which we are to be constructed
   */
  circuit(
    const circuit   &rhs);

  /*!
   * \brief operator=() is deliberately private and unimplemented.
   *
   * \param rhs the object from which we are to be assigned
   *
   * \return reference to self to allow for chained operators
   */
  circuit &operator=(
    const circuit   &rhs);

  /*!
   * \brief This is the implementation function for operator<<()
   *
   * \return The same stream as the input to allow for chained operators.
   */
  std::ostream &print_self(
    std::ostream    &os)           /*!< The stream into which we stream     */
  const;


  /*!
   * \brief Return a reference to the jugglers who are assigned to this circuit
   */
  juggler_circuit_set  &assigned()
  { return _assigned; }


  /*!
   * \brief Return a reference to the jugglers who are assigned to this circuit
   */
  const juggler_circuit_set  &assigned() const
  { return _assigned; }


  /*!
   * \brief Regular expression to scan a circuit string and extract the name of
   *        the circuit as well as its preferred talent (hand-eye coordination,
   *        endurance, and pizzazz)
   */
  const static std::string  _scan_exp;


   /*!
    * \brief The jugglers that have been assigned to this circuit
    */
  juggler_circuit_set       _assigned;


};

#endif                             /* circuit_h_included                    */
