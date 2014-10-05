#ifndef type_pointer_set_iterator_h_included
#define type_pointer_set_iterator_h_included 1

/*!
 * \file type_pointer_set_iterator.h
 *
 * \brief Contains the definition of type_pointer_set_iterator
 *
 * \author Stewart L. Palmer
 */

#include <iostream>
#include <assert.h>
#include "type_pointer_set.h"

/*!
 * \brief An iterator over type_pointer_set
 */
template<typename K, typename T>
class type_pointer_set_iterator
{
public:

  /*!
   * \brief Standard constructor
   */
  explicit type_pointer_set_iterator<K, T>(
    type_pointer_set<K, T>   &tps)
  :
  _tps(tps),
  _it(_tps._tts_map.begin())
  { }


  /*!
   * \brief Fetch next pointer from the set
   *
   * \return The next pointer or zero if none remain
   */
  T next()
  {
    T n = 0;
    if (_it != _tps._tts_map.end())
      {
        const std::pair<K, T> &p = *_it;
        _last_it = _it;
        n = p.second;
        _last = n;
        _it++;
      }

    return n;
  }


  /*!
   * \brief Remove the last item we returned
   */
  void remove_current()
  {
    assert( !(_last == 0) );
    typename std::map<K, T>::iterator  iter = _last_it;
    _tps._tts_map.erase(iter);
  }



  /*!
   *  \brief Stream object out to a stream
   *
   * \return The same stream as the input to allow for chained operators.
   */
  friend std::ostream &operator<<(
    std::ostream                     &os,/*!< The stream into which we stream*/
    const type_pointer_set_iterator  &cn)/*!< The object to be streamed     */
  {
    return cn.print_self(os);
  }

private:

  /*!
   * \brief The copy constructor is deliberately private and unimplemented.
   *
   * \param rhs the object from which we are to be constructed
   */
  type_pointer_set_iterator(
    const type_pointer_set_iterator   &rhs);

  /*!
   * \brief operator=() is deliberately private and unimplemented.
   *
   * \param rhs the object from which we are to be assigned
   *
   * \return reference to self to allow for chained operators
   */
  type_pointer_set_iterator &operator=(
    const type_pointer_set_iterator   &rhs);

  /*!
   * \brief This is the implementation function for operator<<()
   *
   * \return The same stream as the input to allow for chained operators.
   */
  std::ostream &print_self(
    std::ostream    &os)           /*!< The stream into which we stream     */
  const
  {
    os << "type_pointer_set_iterator";

    return os;
  }

  //! The set over which we iterate
  type_pointer_set<K, T>              &_tps;

  //! The iterator we use to do it
  typename std::map<K, T>::iterator    _it;

  //! The last iterator position we returned
  typename std::map<K, T>::iterator    _last_it;

  //! The last item we returned
  T                                    _last;

};

#endif                             /* type_pointer_set_iterator_h_included  */
