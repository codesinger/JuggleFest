#ifndef type_pointer_set_h_included
#define type_pointer_set_h_included 1

/*!
 * \file type_pointer_set.h
 *
 * \brief Contains the definition of type_pointer_set
 *
 * \author Stewart L. Palmer
 */

#include <iostream>
#include <assert.h>
#include <map>

template<typename K, typename T>
class type_pointer_set_iterator;


/*!
 * \brief A template class that is a set of {key, pointer to item}
 */
template<typename K, typename T>
class type_pointer_set
{
public:

  /*!
   * \brief Standard constructor
   */
  explicit type_pointer_set()
  { }


  /*!
   * \brief Find the item for a given name
   *
   * \return non-zero if the item is not found
   */
  int find(
    const K             &name,     /*!< Name key                            */
    T                   &item)     /*!< Reference to pointer to item        */
  {
    int rc = 1;
    typename std::map<K, T>::iterator it = _tts_map.find(name);
    if (it != _tts_map.end())
      {
        rc = 0;
        const std::pair<K, T> &p = *it;
        item = p.second;
      }

    return rc;
  }


  /*!
   * \brief Add an item to the set
   *
   * Assert failure if the name already exists in the set
   */
  void add(
    const K             &name,     /*!< Name of item to add                 */
    T                   &item)     /*!< Pointer to the item to add          */
  {
    T  found_item;
    const int find_rc = find(name, found_item);
    assert(find_rc != 0);
    _tts_map.insert(std::pair<K, T>(name, item));
  }


  /*!
   * \brief Return the number of items in the set
   */
  unsigned int size() const
  { return _tts_map.size(); }


  /*!
   *  \brief Stream object out to a stream
   *
   * \return The same stream as the input to allow for chained operators.
   */
  friend std::ostream &operator<<(
    std::ostream          &os,     /*!< The stream into which we stream     */
    const type_pointer_set   &cn)     /*!< The object to be streamed           */
  {
    return cn.print_self(os);
  }

protected:

  /*!
   * \brief This is the implementation function for operator<<()
   *
   * \return The same stream as the input to allow for chained operators.
   */
  std::ostream &print_self(
    std::ostream    &os)           /*!< The stream into which we stream     */
  const
  {
    typename std::map<K, T>::const_iterator it;
    for (it = _tts_map.begin(); it != _tts_map.end(); ++it)
    {
      const std::pair<K, T> &p = *it;
      const T m = p.second;
      os << *m << "\n";
    }

    return os;
  }

private:

  friend class type_pointer_set_iterator<K, T>;


  /*!
   * \brief The copy constructor is deliberately private and unimplemented.
   *
   * \param rhs the object from which we are to be constructed
   */
  type_pointer_set(
    const type_pointer_set   &rhs);

  /*!
   * \brief operator=() is deliberately private and unimplemented.
   *
   * \param rhs the object from which we are to be assigned
   *
   * \return reference to self to allow for chained operators
   */
  type_pointer_set &operator=(
    const type_pointer_set   &rhs);

  //! The map used to implement this set
  std::map<K, T>   _tts_map;
};

#endif                             /* type_pointer_set_h_included           */
