#ifndef juggler_set_iterator_h_included
#define juggler_set_iterator_h_included 1

/*!
 * \file juggler_set_iterator.h
 *
 * \brief Contains the definition of juggler_set_iterator
 *
 * \author Stewart L. Palmer
 */

#include <iostream>
#include "type_pointer_set_iterator.h"
#include "juggler_set.h"

/*!
 * \brief An iterator over juggler_set
 */
class juggler_set_iterator : public type_pointer_set_iterator<std::string, juggler *>
{
public:

  /*!
   * \brief Standard constructor
   */
  explicit juggler_set_iterator(
    juggler_set     &cs)
  :
  type_pointer_set_iterator<std::string, juggler *>(cs)
  { }

  /*!
   *  \brief Stream object out to a stream
   *
   * \return The same stream as the input to allow for chained operators.
   */
  friend std::ostream &operator<<(
    std::ostream                &os,/*!< The stream into which we stream    */
    const juggler_set_iterator  &cn)/*!< The object to be streamed          */
  {
    return cn.print_self(os);
  }

private:

  /*!
   * \brief The copy constructor is deliberately private and unimplemented.
   *
   * \param rhs the object from which we are to be constructed
   */
  juggler_set_iterator(
    const juggler_set_iterator   &rhs);

  /*!
   * \brief operator=() is deliberately private and unimplemented.
   *
   * \param rhs the object from which we are to be assigned
   *
   * \return reference to self to allow for chained operators
   */
  juggler_set_iterator &operator=(
    const juggler_set_iterator   &rhs);

  /*!
   * \brief This is the implementation function for operator<<()
   *
   * \return The same stream as the input to allow for chained operators.
   */
  std::ostream &print_self(
    std::ostream    &os)           /*!< The stream into which we stream     */
  const
  {
    os << "juggler_set_iterator";

    return os;
  }

};

#endif                             /* juggler_set_iterator_h_included       */
