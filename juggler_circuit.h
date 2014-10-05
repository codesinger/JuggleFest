#ifndef juggler_circuit_h_included
#define juggler_circuit_h_included 1

/*!
 * \file juggler_circuit.h
 *
 * \brief Contains the definition of juggler_circuit
 *
 * \author Stewart L. Palmer
 */

#include <iostream>
#include "juggler.h"

class juggler_circuit_reference;

/*!
 * \brief Describe the relationship of a juggler to a circuit
 *
 * Records score of juggler as well as juggler preference.  Juggler preference is 0
 * if this circuit is the juggler's first preference, 1 if second preference, etc.
 */
class juggler_circuit
{
public:

  /*!
   * \brief Standard constructor
   */
  explicit juggler_circuit(
    juggler  &jug,                 /*!< The juggler                         */
    circuit  &circ,                /*!< The circuit                         */
    int       score,               /*!< Score of juggler for this circuit   */
    int       preference)          /*!< Juggler preference for this circuit */
  :
  _jug(jug),
  _circ(circ),
  _score(score),
  _preference(preference)
  { }


  /*!
   * \brief Return a reference to the juggler
   */
  juggler &jug() const
  { return _jug; }


  /*!
   * \brief Return the name of the juggler
   */
  const std::string  &juggler_name() const
  { return jug().name(); }


  /*!
   * \brief Return the ID of the juggler
   */
  int juggler_id() const
  { return jug().id(); }


  /*!
   * \brief Return a reference to the circuit
   */
  circuit &circ() const
  { return _circ; }


  /*!
   * \brief Return the name of the circuit
   */
  const std::string  &circuit_name() const;


  /*!
   * \brief Return the score
   */
  int score() const
  { return _score; }


  /*!
   * \brief Return the preference
   */
  int preference() const
  { return _preference; }


  /*!
   * \brief Return the lowest score of any juggler assigned to this circuit
   */
  int lowest_score() const;


  /*!
   * \brief Set the assigned state of the juggler
   *
   * This is a const function with respect to juggler_circuit because it does not
   * modify juggler_circuit.  It modifies the juggler to which juggler_circuit
   * refers.
   */
  void set_assignment() const
  { jug().set_assignment(*this); }


  /*!
   * \brief Clear the assigned state of the juggler
   *
   * This is a const function with respect to juggler_circuit because it does not
   * modify juggler_circuit.  It modifies the juggler to which juggler_circuit
   * refers.
   */
  void clear_assignment() const
  { jug().clear_assignment(); }


  /*!
   * \brief Operator <
   *
   * This is used to define the ordering in a juggler_circuit_set.  A juggler_circuit
   * has a three part key:
   *
   * <ol>
   * <li> The score (dot prodoct) of the juggler and the circuit,
   * <li> The preference of the juggler for the circuit.  Lower number represents
   *      higher preference, and
   * <li> The unique ID of the juggler.
   * </ol>
   *
   * This guarantees uniqueness of every key, which allows a juggler_circuit to be
   * deleted by value.
   *
   * \return true if the key of this juggler_circuit is less than the key of the
   *         other juggler_circuit
   */
  bool operator<(
    const juggler_circuit   &rhs)  /*!< Right hand side of comparison operator*/
  const
  {
    bool is_less = false;
    const juggler_circuit  &self = *this;
    if (self.score() < rhs.score())
      is_less = true;
    else if (self.score() == rhs.score())
      {
        if (self.preference() < rhs.preference())
          is_less = true;
        else if (self.preference() == rhs.preference())
          {
            if (self.jug().id() < rhs.jug().id())
              is_less = true;
          }
      }

    return is_less;
  }


  /*!
   *  \brief Stream object out to a stream
   *
   * \return The same stream as the input to allow for chained operators.
   */
  friend std::ostream &operator<<(
    std::ostream            &os,   /*!< The stream into which we stream     */
    const juggler_circuit   &cn)   /*!< The object to be streamed           */
  {
    return cn.print_self(os);
  }

private:

  friend class juggler_circuit_reference;

  /*!
   * \brief The copy constructor is deliberately private and unimplemented.
   *
   * \param rhs the object from which we are to be constructed
   */
  juggler_circuit(
    const juggler_circuit   &rhs);


  /*!
   * \brief operator=() is deliberately private and unimplemented.
   *
   * \param rhs the object from which we are to be assigned
   *
   * \return reference to self to allow for chained operators
   */
  juggler_circuit &operator=(
    const juggler_circuit   &rhs);


  /*!
   * \brief This is the implementation function for operator<<()
   *
   * \return The same stream as the input to allow for chained operators.
   */
  std::ostream &print_self(
    std::ostream    &os)           /*!< The stream into which we stream     */
  const
  {
    os << "score = " << score() << ", preference = " << preference() << ": " <<
          jug() << "\n";

    return os;
  }


  //! Reference to the juggler itself
  juggler        &_jug;

  //! Reference to the associated circuit
  circuit        &_circ;

  //! Score of the juggler for this circuit
  const int       _score;

  //! Preference of the juggler for this circuit
  const int       _preference;

};

#endif                             /* juggler_circuit_h_included            */
