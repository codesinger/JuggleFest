#ifndef talent_h_included
#define talent_h_included 1

/*!
 * \file talent.h
 *
 * \brief Contains the definition of talent
 *
 * \author Stewart L. Palmer
 */

#include <iostream>
#include <regex>

class scheduler;


/*!
 * \brief Holds the values for hand-eye coordination, endurance, and pizzazz
 *
 * It is the parent class for juggler and circuit, both of which share these attributes
 */
class talent
{
public:

  /*!
   * \brief Standard constructor
   *
   * \param sched Reference to the scheduler.  This is used to get certain
   *              global information such as the number of jugglers per circuit.
   *              It is also used to place an orphaned juggler into the set
   *              of orphaned jugglers.
   */
  explicit talent(
    scheduler  &sched)
  :
  _sched(sched),
  _id(-1),
  _hand(-1),
  _endurance(-1),
  _pizzazz(-1)
  { }


  /*!
   * \brief Return a reference to the scheduler
   */
  scheduler &sched()
  { return _sched; }


  /*!
   * \brief Return a reference to the scheduler
   */
  const scheduler &sched() const
  { return _sched; }


  /*!
   * \brief Return the ID of this instance
   */
  int id() const
  { return _id; }



  /*!
   * \brief Return a reference to the name
   */
  const std::string  &name() const
  { return _name; }


  /*!
   * \brief Return the value for hand-eye coordination
   */
  int hand() const
  { return _hand; }


  /*!
   * \brief Return the value for endurance
   */
  int endurance() const
  { return _endurance; }


  /*!
   * \brief Return the value for pizzazz
   */
  int pizzazz() const
  { return _pizzazz; }


  /*!
   * \brief Return the dot product of two instances of talent
   */
  int dot(
    const talent   &rhs)
  const
  {
    const talent &self = *this;
    const int product = self.hand()      * rhs.hand()      +
                        self.endurance() * rhs.endurance() +
                        self.pizzazz()   * rhs.pizzazz();

    return product;
  }


  /*!
   * \brief Return the number of jugglers per circuit
   */
  unsigned int jugglers_per_circuit() const;


  /*!
   *  \brief Stream object out to a stream
   *
   * \return The same stream as the input to allow for chained operators.
   */
  friend std::ostream &operator<<(
    std::ostream   &os,            /*!< The stream into which we stream     */
    const talent   &cn)            /*!< The object to be streamed           */
  {
    return cn.print_self(os);
  }

protected:


  /*!
   * \brief Set the name of this item
   *
   * \param name The name to set
   *
   * Since the names of all jugglers and circuits are a letter followed
   * by a number, the number is used to set the unique ID as well.
   */
  void set_name(
    const std::string   &name);


  /*!
   * \brief Set the talents from the result of a regular expression scan
   *        done by a child class
   *
   * Input is a match_results iterator and a starting index within the iterator
   *
   * \return non-zero if a talent (H, E, or P) is missing or not recognized
   */
  int set_talents(
    const std::smatch  &talents,   /*!< match_results of talents            */
    const unsigned int  start      /*!< Starting index within match_results */
                             );


  /*!
   * \brief This is the implementation function for operator<<()
   *
   * \return The same stream as the input to allow for chained operators.
   */
  virtual std::ostream &print_self(
    std::ostream    &os)           /*!< The stream into which we stream     */
  const;

private:

  /*!
   * \brief The copy constructor is deliberately private and unimplemented.
   *
   * \param rhs the object from which we are to be constructed
   */
  talent(
    const talent   &rhs);

  /*!
   * \brief operator=() is deliberately private and unimplemented.
   *
   * \param rhs the object from which we are to be assigned
   *
   * \return reference to self to allow for chained operators
   */
  talent &operator=(
    const talent   &rhs);


  /*!
   * \brief Set the value of the ID
   */
  void set_id(
    const int    id)
  { _id = id; }


  //! Reference to the scheduler
  scheduler         &_sched;

   /*!
    * \brief The unique ID of this instance.
    *
    * Useful for placing an item
    * into a set, using the ID as the last part of they key, which
    * guarantees key uniqueness.
    *
    * This ID is derived from the object name since they all follow the
    * pattern of either Cxxxx for circuits or Jxxxx for jugglers.
    */
  int                _id;

  //! Value for hand-eye coordination
  int                _hand;

  //! Value for endurance
  int                _endurance;

  //! Value for pizzazz
  int                _pizzazz;

  //! The name of the entity with these talents
  std::string        _name;

};

#endif                             /* talent_h_included                     */
