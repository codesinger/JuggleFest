/*!
 * \file juggler_circuit_set.cpp
 *
 * \brief Contains the implementation of juggler_circuit_set
 *
 * \author Stewart L. Palmer
 */

#include "juggler_circuit_set_iterator.h"

using namespace ::std;


/*                                                                          */
/****************************************************************************/
/*     P R I N T _ S E L F                                                  */
/****************************************************************************/
/*                                                                          */
ostream &juggler_circuit_set::print_self(
  ostream    &os)           /*!< The stream into which we stream            */
const
{
  juggler_circuit_set_iterator  it(*this);
  const juggler_circuit *j= it.last();
  while (j != 0)
  {
    const juggler_circuit &jc = *j;
    os << jc << "\n";
    j = it.previous();
  }

  return os;
}

