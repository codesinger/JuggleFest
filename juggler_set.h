#ifndef juggler_set_h_included
#define juggler_set_h_included 1

/*!
 * \file juggler_set.h
 *
 * \brief Contains the definition of juggler_set
 *
 * \author Stewart L. Palmer
 */

#include <iostream>
#include <map>
#include <assert.h>
#include "juggler.h"
#include "type_pointer_set.h"


/*!
 * \brief A set of juggler ordered by juggler name
 *
 * This is implemented as a std::map but none of those details are exposed
 * outside the class.
 */
class juggler_set : public type_pointer_set<std::string, juggler *>
{
public:

  /*!
   * \brief Standard constructor
   */
  explicit juggler_set()
  { }


  /*!
   * \brief Add a juggler to the set
   *
   * Assert failure if the new juggler is already in the set
   */
  void add(
    juggler             &jug)      /*!< Juggler to add                      */
  {
    juggler  *j = &jug;
    type_pointer_set<std::string, juggler *>::add(jug.name(), j);
  }


  /*!
   *  \brief Stream object out to a stream
   *
   * \return The same stream as the input to allow for chained operators.
   */
  friend std::ostream &operator<<(
    std::ostream        &os,       /*!< The stream into which we stream     */
    const juggler_set   &cn)       /*!< The object to be streamed           */
  {
    return cn.print_self(os);
  }

private:

  /*!
   * \brief The copy constructor is deliberately private and unimplemented.
   *
   * \param rhs the object from which we are to be constructed
   */
  juggler_set(
    const juggler_set   &rhs);

  /*!
   * \brief operator=() is deliberately private and unimplemented.
   *
   * \param rhs the object from which we are to be assigned
   *
   * \return reference to self to allow for chained operators
   */
  juggler_set &operator=(
    const juggler_set   &rhs);

  /*!
   * \brief This is the implementation function for operator<<()
   *
   * \return The same stream as the input to allow for chained operators.
   */
  std::ostream &print_self(
    std::ostream    &os)           /*!< The stream into which we stream     */
  const
  {
    type_pointer_set<std::string, juggler *>::print_self(os);

    return os;
  }


};

#endif                             /* juggler_set_h_included                */
