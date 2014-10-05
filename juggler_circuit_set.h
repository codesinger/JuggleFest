#ifndef juggler_circuit_set_h_included
#define juggler_circuit_set_h_included 1

/*!
 * \file juggler_circuit_set.h
 *
 * \brief Contains the definition of juggler_circuit_set
 *
 * \author Stewart L. Palmer
 */

#include <iostream>
#include <set>
#include <assert.h>
#include "juggler_circuit_reference.h"

class juggler_circuit_set_iterator;
class juggler_circuit_set_const_iterator;


/*!
 * \brief An ordered set of unique juggler_circuit
 *
 * This is implemented as std::set but the implementation details are not exposed
 * to callers of this class.
 */
class juggler_circuit_set
{
public:

  /*!
   * \brief Standard constructor
   */
  explicit juggler_circuit_set()
  { }


  /*!
   * \brief Add a juggler_circuit to the set
   */
  void add(
    const juggler_circuit  &jc)    /*!< juggler_circuit to add              */
  {
    const juggler_circuit_reference  jcr(jc);
    _jcs_set.insert(jcr);
  }


  /*!
   * \brief Return the number of elements in the set
   */
  unsigned int size() const
  { return _jcs_set.size(); }


  /*!
   * \brief Delete a juggler_curcuit by value
   */
  void remove(
    const juggler_circuit  &jc)    /*!< juggler_circuit to delete           */
  {
    assert(size() > 0);            /* Can't delete from empty set           */
    const juggler_circuit_reference  jcr(jc);
    const unsigned int delete_count = _jcs_set.erase(jcr);
    if (delete_count != 1)         /* Could not find item to delete         */
      {
        std::cerr << __FILE__ << ":" << __LINE__ << ": " << "delete_count = " << delete_count << "\n" <<
        "To remove: " << jc << "\n{" << *this << "}" << std::endl;
      }
    assert(delete_count == 1);
  }


  /*!
   *  \brief Stream object out to a stream
   *
   * \return The same stream as the input to allow for chained operators.
   */
  friend std::ostream &operator<<(
    std::ostream        &os,       /*!< The stream into which we stream     */
    const juggler_circuit_set   &cn)       /*!< The object to be streamed           */
  {
    return cn.print_self(os);
  }

private:

  friend class juggler_circuit_set_iterator;
  friend class juggler_circuit_set_const_iterator;


  /*!
   * \brief The copy constructor is deliberately private and unimplemented.
   *
   * \param rhs the object from which we are to be constructed
   */
  juggler_circuit_set(
    const juggler_circuit_set   &rhs);

  /*!
   * \brief operator=() is deliberately private and unimplemented.
   *
   * \param rhs the object from which we are to be assigned
   *
   * \return reference to self to allow for chained operators
   */
  juggler_circuit_set &operator=(
    const juggler_circuit_set   &rhs);

  /*!
   * \brief This is the implementation function for operator<<()
   *
   * \return The same stream as the input to allow for chained operators.
   */
  std::ostream &print_self(
    std::ostream    &os)           /*!< The stream into which we stream     */
  const
  {
    std::set<juggler_circuit_reference>::const_iterator  it;
    it = _jcs_set.end();
    while (it != _jcs_set.begin())
    {
      --it;
      const juggler_circuit_reference &jcr = *it;
      os << jcr << "\n";
    }

    return os;
  }

  //! The set that is used to implement this set
  std::set<juggler_circuit_reference>  _jcs_set;

};

#endif                             /* juggler_circuit_set_h_included        */
