#ifndef juggler_circuit_set_const_iterator_h_included
#define juggler_circuit_set_const_iterator_h_included 1

/*!
 * \file juggler_circuit_set_const_iterator.h
 *
 * \brief Contains the definition of juggler_circuit_set_const_iterator
 *
 * \author Stewart L. Palmer
 */

#include <iostream>
#include <assert.h>
#include "juggler_circuit_set.h"

/*!
 * \brief A const iterator over juggler_circuit_set
 */
class juggler_circuit_set_const_iterator
{
public:

  /*!
   * \brief Standard constructor
   */
  explicit juggler_circuit_set_const_iterator(
    const juggler_circuit_set    &jcs)/*!< Set over which we iterate        */
  :
  _jcs(jcs),
  _it(_jcs._jcs_set.begin()),
  _last(0)
  { }


  /*!
   * \brief Fetch first juggler_circuit
   */
  const juggler_circuit *first()
  {
    _it = _jcs._jcs_set.begin();
    const juggler_circuit *const jc = next();

    return jc;
  }


  /*!
   * \brief Fetch last juggler_circuit
   */
  const juggler_circuit *last()
  {
    /* Note that STL iterator.begin() returns a forward iterator positioned ON the first */
    /* element of the list.  STL iterator.end() returns a forward iterator positioned    */
    /* AFTER the last element of the list.                                               */
    _it = _jcs._jcs_set.end();
    const juggler_circuit *const jc = previous();

    return jc;
  }


  /*!
   * \brief Fetch next juggler_circuit
   *
   * \return The address of the next instance or zero if none remain
   */
  const juggler_circuit *next()
  {
    const juggler_circuit            *jc = 0;
    _last = jc;
    if (_it != _jcs._jcs_set.end())
      {
        const juggler_circuit_reference &jcr = *_it;
        jc = jcr.jc();
        _last = jc;
        _last_it = _it;
        assert( !(_last == 0) );
        _it++;
      }

    return jc;
  }


  /*!
   * \brief Fetch previous juggler_circuit
   */
  const juggler_circuit *previous()
  {
    const juggler_circuit  *jc = 0;
    if (_it != _jcs._jcs_set.begin())
      {
        --_it;
        const juggler_circuit_reference &jcr = *_it;
        jc = jcr.jc();
        _last = jc;
        _last_it = _it;
        assert( !(_last == 0) );
      }

    return jc;
  }


  /*!
   *  \brief Stream object out to a stream
   *
   * \return The same stream as the input to allow for chained operators.
   */
  friend std::ostream &operator<<(
    std::ostream                        &os,/*!< The stream into which we stream*/
    const juggler_circuit_set_const_iterator  &cn)/*!< The object to be streamed  */
  {
    return cn.print_self(os);
  }

private:

  /*!
   * \brief The copy constructor is deliberately private and unimplemented.
   *
   * \param rhs the object from which we are to be constructed
   */
  juggler_circuit_set_const_iterator(
    const juggler_circuit_set_const_iterator   &rhs);

  /*!
   * \brief operator=() is deliberately private and unimplemented.
   *
   * \param rhs the object from which we are to be assigned
   *
   * \return reference to self to allow for chained operators
   */
  juggler_circuit_set_const_iterator &operator=(
    const juggler_circuit_set_const_iterator   &rhs);

  /*!
   * \brief This is the implementation function for operator<<()
   *
   * \return The same stream as the input to allow for chained operators.
   */
  std::ostream &print_self(
    std::ostream    &os)           /*!< The stream into which we stream     */
  const
  {
    os << "juggler_circuit_set_const_iterator";

    return os;
  }

  //! The set over which we iterate
  const juggler_circuit_set                     &_jcs;

  //! The iterator we use to do it
  std::set<juggler_circuit_reference>::iterator  _it;

  //! The last iterator position used
  std::set<juggler_circuit_reference>::iterator  _last_it;

  //! The last juggler_circuit returned by this iterator
  const juggler_circuit                         *_last;

};

#endif                             /* juggler_circuit_set_const_iterator_h_included*/
