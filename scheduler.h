#ifndef scheduler_h_included
#define scheduler_h_included 1

/*!
 * \file scheduler.h
 *
 * \brief Contains the definition of scheduler
 *
 * \author Stewart L. Palmer
 */

#include <iostream>
#include "juggler_set.h"
#include "circuit_set.h"
#include "juggler_set_iterator.h"

/*!
 * \brief This class reads the input file, creates the circuits and jugglers,
 *        assigns the jugglers to their circuits, validates the assignments, and
 *        prints them out.
 */
class scheduler
{
public:

  /*!
   * \brief Standard constructor
   */
  explicit scheduler(
    const char  *file_name         /*!< Name of input file                  */
                          );


  /*!
   * \brief Assign all of the jugglers to their best fit circuits
   *
   * This runs in O(j*n + c), where j is the number of jugglers, n is the number of
   * preferences expressed by each juggler, and c is the number of circuits.
   *
   * First we try to assign each juggler to its first preferred circuit.  If the
   * juggler does not fit or if it has to evict a worse fitting juggler, there
   * remains a juggler yet to be assigned.  The function that does the assignment
   * calls itself recursively until the juggler has been assigned to a circuit or
   * has run out of preferred circuits.  If the juggler runs out of preferred
   * circuits, it is added to the set of orphaned jugglers.
   *
   * At the end of this one pass through the jugglers, all jugglers are assigned to
   * their best fit, with the possible exception of jugglers that did not fit in any
   * of their preferred circuits.
   *
   * If y orphaned jugglers exist, there are y open slots in the circuits.  At this
   * point we go through all the circuits.  We fill any open clot in a circuit with
   * the next orphaned juggler.  It matter not which jugglers are used to fill the
   * open slots.  It is still the case that none of these orphaned jugglers could be
   * moved to a circuit that they prefer more and be a better fit for any juggler in
   * that circuit.
   */
  void assign();


  /*!
   * \brief Show the final assignments
   */
  void show_assignments(
    std::ostream    &os           /*!< Output stream for results           */
                       );


  /*!
   * \brief Return the count of the number of circuits
   */
  unsigned int  circuit_count() const
  { return _circuits.size(); }


  /*!
   * \brief Return the count of the number of jugglers
   */
  unsigned int  juggler_count() const
  { return _jugglers.size(); }


  /*!
   * \brief Return the number of jugglers per circuit
   */
  unsigned int  jugglers_per_circuit() const
  { return (juggler_count() / circuit_count()); }


  /*!
   * \brief Return the number of orphaned jugglers
   */
  unsigned int orphan_juggler_count() const
  { return _orphan_jugglers.size(); }


  /*!
   * \brief Return a circuit by name
   *
   * \return A pointer to the circuit if it exists, otherwise zero
   */
  const circuit *get_circuit(
    const std::string    &circuit_name/*!< Name of circuit to return        */
                                      );



  /*!
   * \brief Add a juggler to the set of jugglers that have no circuits
   *
   * This is a juggler that is not a good fit for any of its preferred circuits
   */
  void add_orphaned_juggler(
    juggler    &jug)               /*!< Juggler to add                      */
  {
    _orphan_jugglers.add(jug);
  }


  /*!
   * \brief Validate the assignment of all the jugglers
   *
   * Ensure that all circuits are full and make sure that there is no juggler that
   * could be placed in a circuit that it prefers more and also be a better fit
   * for that circuit.
   *
   * \return Zero if no errors are found in the assignments, non-zero otherwise
   */
  int validate_assignments(
    std::ostream    &os            /*!< Stream for error reporting          */
                       );



  /*!
   *  \brief Stream object out to a stream
   *
   * \return The same stream as the input to allow for chained operators.
   */
  friend std::ostream &operator<<(
    std::ostream      &os,         /*!< The stream into which we stream     */
    const scheduler   &cn)         /*!< The object to be streamed           */
  {
    return cn.print_self(os);
  }

private:

  /*!
   * \brief The copy constructor is deliberately private and unimplemented.
   *
   * \param rhs the object from which we are to be constructed
   */
  scheduler(
    const scheduler   &rhs);

  /*!
   * \brief operator=() is deliberately private and unimplemented.
   *
   * \param rhs the object from which we are to be assigned
   *
   * \return reference to self to allow for chained operators
   */
  scheduler &operator=(
    const scheduler   &rhs);

  /*!
   * \brief This is the implementation function for operator<<()
   *
   * \return The same stream as the input to allow for chained operators.
   */
  std::ostream &print_self(
    std::ostream    &os)           /*!< The stream into which we stream     */
  const
  {
    os << "scheduler";

    return os;
  }


  /*!
   * \brief Try to assign each juggler to its most preferred circuit
   *
   * If the juggler is a good fit for the circuit it will be assigned to it.
   * If the circuit is full, this will cause the eviction of the juggler
   * with the lowest score.  If the jugler is not a good fit for the circuit,
   * it will not be assigned to it.  In either case, a juggler still needs
   * an assignment.  circuit::reassign_juggler is called recursively until
   * the juggler is either assigned to one of its preferred circuits or cannot
   * be assigned anywhere.  If it cannot be assigned anywhere it is placed in
   * the set of orphaned jugglers.
   *
   * This is the only loop through all the jugglers
   */
  void do_assignments();


  /*!
   * \brief Distribute orphaned jugglers to underfull circuits
   *
   * All of the possible assignments are done based on juggler preference.  But
   * it might not be possible to put a juggler into any of its preferred circuits.
   * Any juggler that could not be placed into any of its preferred circuits is in
   * the orphaned juggler set.  Here we go through the circuits.  As we encounter
   * an underfull circuit, we populate it from the orphaned juggler set.
   *
   * This is the only loop through the circuits.
   */
  void distribute_orphans();


  /*!
   * \brief Fetch and delete the next orphan from the set of orphaned jugglers
   */
  juggler *next_orphan()
  {
    juggler_set_iterator   jsi(_orphan_jugglers);
    juggler *j = jsi.next();
    if (j != 0)
      jsi.remove_current();

    return j;
  }


  //! The set of all jugglers ordered by juggler name
  juggler_set    _jugglers;

  //! The set of all circuits ordered by circuit name
  circuit_set    _circuits;

   /*!
    * \brief The set of all jugglers that have become orphans
    *
    * This set happens to be ordered by name but the ordering is irrelevant.
    */
  juggler_set    _orphan_jugglers;

  //! Name of input file
  const std::string  _file_name;

};

#endif                             /* scheduler_h_included                  */
