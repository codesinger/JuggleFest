#ifndef circuit_set_const_iterator_h_included
#define circuit_set_const_iterator_h_included 1

/*!
 * \file circuit_set_const_iterator.h
 *
 * \brief Contains the definition of circuit_set_const_iterator
 *
 * \author Stewart L. Palmer
 */

#include <iostream>
#include "type_pointer_set_iterator.h"
#include "circuit_set.h"

/*!
 * \brief A const iterator over circuit_set
 */
class circuit_set_const_iterator : public type_pointer_set_iterator<std::string, const circuit *>
{
public:

  /*!
   * \brief Standard constructor
   */
  explicit circuit_set_const_iterator(
    const circuit_set     &cs)
  :
  type_pointer_set_iterator<std::string, const circuit *>(cs)
  { }

  /*!
   *  \brief Stream object out to a stream
   *
   * \return The same stream as the input to allow for chained operators.
   */
  friend std::ostream &operator<<(
    std::ostream                &os,/*!< The stream into which we stream    */
    const circuit_set_const_iterator  &cn)/*!< The object to be streamed          */
  {
    return cn.print_self(os);
  }

private:

  /*!
   * \brief The copy constructor is deliberately private and unimplemented.
   *
   * \param rhs the object from which we are to be constructed
   */
  circuit_set_const_iterator(
    const circuit_set_const_iterator   &rhs);

  /*!
   * \brief operator=() is deliberately private and unimplemented.
   *
   * \param rhs the object from which we are to be assigned
   *
   * \return reference to self to allow for chained operators
   */
  circuit_set_const_iterator &operator=(
    const circuit_set_const_iterator   &rhs);

  /*!
   * \brief This is the implementation function for operator<<()
   *
   * \return The same stream as the input to allow for chained operators.
   */
  std::ostream &print_self(
    std::ostream    &os)           /*!< The stream into which we stream     */
  const
  {
    os << "circuit_set_const_iterator";

    return os;
  }

};

#endif                             /* circuit_set_const_iterator_h_included */
