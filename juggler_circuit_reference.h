#ifndef juggler_circuit_reference_h_included
#define juggler_circuit_reference_h_included 1

/*!
 * \file juggler_circuit_reference.h
 *
 * \brief Contains the definition of juggler_circuit_reference
 *
 * \author Stewart L. Palmer
 */

#include <iostream>
#include "juggler_circuit.h"

class juggler_circuit_set;
class juggler_circuit_set_iterator;
class juggler_circuit_set_const_iterator;

/*!
 * \brief This is the item that is actually stored in each instance in juggler_circuit_set
 *
 * It is a reference to the associated juggler_circuit.  It delegates operator<() and
 * operatot<<() to the actual juggler_curcuit.  This means that instances of juggler_circuit
 * are never copied (the juggler_circuit copy constructor is private and unimplemented),
 * or destroyed.  Pointers to instances of juggler_circuit that are returned
 * by the iterator are the only copies ever made.  These pointers may safely be stored
 * and used later.
 */
class juggler_circuit_reference
{
public:


  /*!
   * \brief Operator <
   *
   * \param rhs Right hand side of comparison operator
   *
   * \return true if the key of the juggler_circuit referenced here is less than the key
   *         of the juggler circuit refereneced by the other juggler_circuit_reference.
   */
  bool operator<(
    const juggler_circuit_reference  &rhs)
  const
  {
    const juggler_circuit_reference &self = *this;
    const juggler_circuit &left  = self.jc_ref();
    const juggler_circuit &right =  rhs.jc_ref();
    const bool is_less = (left < right);

    return is_less;
  }

  /*!
   *  \brief Stream object out to a stream
   *
   * \return The same stream as the input to allow for chained operators.
   */
  friend std::ostream &operator<<(
    std::ostream                     &os,/*!< The stream into which we stream*/
    const juggler_circuit_reference  &cn)/*!< The object to be streamed     */
  {
    return cn.print_self(os);
  }

private:

  friend class juggler_circuit_set;
  friend class juggler_circuit_set_iterator;
  friend class juggler_circuit_set_const_iterator;

  /*!
   * \brief Standard constructor
   */
  explicit juggler_circuit_reference(
    const juggler_circuit   &jc)
  :
  _jc(jc)
  { }


  /*!
   * \brief The copy constructor is supplied by the compiler
   */


  /*!
   * \brief operator=() is deliberately private and unimplemented.
   *
   * \param rhs the object from which we are to be assigned
   *
   * \return reference to self to allow for chained operators
   */
  juggler_circuit_reference &operator=(
    const juggler_circuit_reference   &rhs);


  /*!
   * \brief Return a pointer to the associated juggler_circuit
   */
  const juggler_circuit *jc() const
  { return &_jc; }


  /*!
   * \brief Return a reference to the associated juggler_circuit
   */
  const juggler_circuit &jc_ref() const
  { return _jc; }

  /*!
   * \brief This is the implementation function for operator<<()
   *
   * \return The same stream as the input to allow for chained operators.
   */
  std::ostream &print_self(
    std::ostream    &os)           /*!< The stream into which we stream     */
  const
  {
    os << "Ref: " << _jc;

    return os;
  }

  //! Reference to the associated juggler_circuit
  const juggler_circuit   &_jc;

};

#endif                             /* juggler_circuit_reference_h_included  */
