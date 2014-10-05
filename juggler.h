#ifndef juggler_h_included
#define juggler_h_included 1

/*!
 * \file juggler.h
 *
 * \brief Contains the definition of juggler
 *
 * \author Stewart L. Palmer
 */

#include <iostream>
#include <vector>
#include <assert.h>
#include "talent.h"

class circuit;
class circuit_set;
class juggler_assignment;
class juggler_circuit;
class juggler_circuit_set;


/*!
 * \brief Represents a juggler instance
 */
class juggler : public talent
{
public:

  /*!
   * \brief Standard constructor
   *
   * The constructor finds each circuit in the juggler preference list and
   * constructs a juggler_circuit instance for each one.  The juggler_circuit
   * instance points to both the juggler object and the circuit object and holds
   * the score and preference for that combination of juggler and circuit.
   *
   * \param sched      Reference to the scheduler
   * \param definition String that defines the juggler.  This is the input
   *                   record read from the file, which the constructor parses.
   * \param circuits   The set of all circuits
   */
  explicit juggler(
    scheduler          &sched,
    const std::string  &definition,
    circuit_set        &circuits);



  /*!
   * \brief Return a reference to the current juggler assignment
   *
   * An assignment is represented by an instance of juggler_circuit, which points
   * to the both the juggler and the circuit and contains the score and preference.
   *
   * \return A reference to the current juggler assignment
   */
  const juggler_circuit &assignment()
  {
    assert(_assignment != 0);

    return *_assignment;
  }


  /*!
   * \brief Return a reference to the current juggler assignment
   *
   * An assignment is represented by an instance of juggler_circuit, which points
   * to the both the juggler and the circuit and contains the score and preference.
   *
   * \return A reference to the current juggler assignment
   */
  const juggler_circuit &assignment() const
  {
    assert(_assignment != 0);

    return *_assignment;
  }


  /*!
   * \brief Return true if the juggler is currently assigned to a circuit
   */
  bool is_assigned() const
  {
    return (_assignment != 0);
  }


  /*!
   * \brief Add this juggler to its first preferred circuit
   *
   * If it does not fit in its first preferred circuit, all other preferences
   * will be tried until the juggler is assigned to a circuit or is finally
   * added to the set of orphaned jugglers that cannot fit in any of their
   * preferred circuits.
   */
  void add_to_first_preferred_circuit() const;


  /*!
   * \brief Show all circuits, and their scores, that this juggler prefers
   */
  void show_requests(
    std::ostream     &os)          /*!< Output stream for requests          */
  const;


  /*!
   * \brief Set the assignment for the juggler
   */
  void set_assignment(
    const juggler_circuit  &assignment)/*!< Assignment record               */
  {
    _assignment = &assignment;
  }


  /*!
   * \brief Clear the assigned state of the juggler
   */
  void clear_assignment()
  { _assignment = 0; }


  /*!
   * \brief Return the highest preference for this juggler
   */
  int highest_preference() const
  {
    int high = _requested.size();

    return high;
  }


  /*!
   * \brief Get the next preference for this juggler
   *
   * \param current_preference The current preference value for the juggler
   *
   * \return A pointer to the juggler_circuit that represents the next lowest
   *         preference of the juggler or zero if the current preference is
   *         already the lowest and there are no more.
   *
   */
  const juggler_circuit *get_next_preference(
    const unsigned int    current_preference)
  const
  {
    const juggler_circuit *j = 0;
    const unsigned int next_preference = current_preference + 1;
    if (_requested.size() > next_preference)
      j = _requested[next_preference];

    return j;
  }


  /*!
   * \brief Validate the juggler assignment
   *
   * Compare the juggler assignment against the problem statement to make sure
   * that it is not a better fit in any circuit that it prefers more than the
   * circuit to which it is assigned.
   *
   * \return zero if the assignment is correct, non-zero if a problem was detected
   */
  int validate_assignment(
    std::ostream     &os           /*!< Output stream for error messages    */
                        );


  /*!
   *  \brief Stream object out to a stream
   *
   * \return The same stream as the input to allow for chained operators.
   */
  friend std::ostream &operator<<(
    std::ostream    &os,           /*!< The stream into which we stream     */
    const juggler   &cn)           /*!< The object to be streamed           */
  {
    return cn.print_self(os);
  }

private:

  friend class scheduler;


  /*!
   * \brief The copy constructor is deliberately private and unimplemented.
   *
   * \param rhs the object from which we are to be constructed
   */
  juggler(
    const juggler   &rhs);

  /*!
   * \brief operator=() is deliberately private and unimplemented.
   *
   * \param rhs the object from which we are to be assigned
   *
   * \return reference to self to allow for chained operators
   */
  juggler &operator=(
    const juggler   &rhs);


  /*!
   * \brief This is the implementation function for operator<<()
   *
   * \return The same stream as the input to allow for chained operators.
   */
  std::ostream &print_self(
    std::ostream    &os)           /*!< The stream into which we stream     */
  const;


  /*!
   * \brief Create a new juggler_circuit to describe the relationship of the
   *        juggler to the circuit and add it to our set of preferred circuits
   *
   * \return A pointer to the newly created juggler_circuit
   */
  const juggler_circuit *add_circuit(
    circuit     &circ,             /*!< The circuit to add                  */
    const int    preference        /*!< The preference for this circuit     */
                           );


  /*!
   * \brief Add a circuit preference for this juggler
   *
   * This records the juggler's preference for the circuit as well as the fit.
   * The request is recorded by an instance of juggler_circuit.
   */
  void add_request(
    const juggler_circuit   &jc    /*!< juggler_circuit to add              */
                               );


  /*!
   * \brief Regular expression to scan a juggler string and extract the name of
   *        the juggler, its talent (hand-eye coordination, endurance, and pizzazz),
   *        and comma separated string of preferred circuits.
   */
  const static std::string               _scan_exp;

   /*!
    * \brief Pointer to the juggler's assignment record
    */
  const juggler_circuit                 *_assignment;


   /*!
    * \brief The circuits for which this juggler has expressed a preference
    *
    * Stored in order of preference
    */
  std::vector<const juggler_circuit *>   _requested;


};

#endif                             /* juggler_h_included                    */
