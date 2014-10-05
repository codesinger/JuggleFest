#ifndef circuit_set_h_included
#define circuit_set_h_included 1

/*!
 * \file circuit_set.h
 *
 * \brief Contains the definition of circuit_set
 *
 * \author Stewart L. Palmer
 */

#include <iostream>
#include "circuit.h"
#include "type_pointer_set.h"

/*!
 * \brief A set of unique circuits ordered by name
 *
 * This is implemented as a std::map but none of those details are exposed
 * outside the class.
 */
class circuit_set : public type_pointer_set<std::string, circuit *>
{
public:

  /*!
   * \brief Standard constructor
   */
  explicit circuit_set()
  { }


  /*!
   * \brief Add a circuit to the set
   *
   * Assert failure if the new circuit is already in the set
   */
  void add(
    circuit             &circ)      /*!< Circuit to add                       */
  {
    circuit  *c = &circ;
    type_pointer_set<std::string, circuit *>::add(circ.name(), c);
  }


  /*!
   *  \brief Stream object out to a stream
   *
   * \return The same stream as the input to allow for chained operators.
   */
  friend std::ostream &operator<<(
    std::ostream        &os,       /*!< The stream into which we stream     */
    const circuit_set   &cn)       /*!< The object to be streamed           */
  {
    return cn.print_self(os);
  }

private:

  /*!
   * \brief The copy constructor is deliberately private and unimplemented.
   *
   * \param rhs the object from which we are to be constructed
   */
  circuit_set(
    const circuit_set   &rhs);

  /*!
   * \brief operator=() is deliberately private and unimplemented.
   *
   * \param rhs the object from which we are to be assigned
   *
   * \return reference to self to allow for chained operators
   */
  circuit_set &operator=(
    const circuit_set   &rhs);

  /*!
   * \brief This is the implementation function for operator<<()
   *
   * \return The same stream as the input to allow for chained operators.
   */
  std::ostream &print_self(
    std::ostream    &os)           /*!< The stream into which we stream     */
  const
  {
    type_pointer_set<std::string, circuit *>::print_self(os);

    return os;
  }

};

#endif                             /* circuit_set_h_included                */
