
/*!
 * \file juggler_circuit.cpp
 *
 * \brief Contains the implementation of juggler_circuit
 *
 * \author Stewart L. Palmer
 */

#include "circuit.h"
#include "juggler_circuit.h"

using namespace ::std;


/*                                                                          */
/****************************************************************************/
/*     C I R C U I T _ N A M E                                              */
/****************************************************************************/
/*                                                                          */
const string  &juggler_circuit::circuit_name() const
{ return circ().name(); }


/*                                                                          */
/****************************************************************************/
/*     L O W E S T _ S C O R E                                              */
/****************************************************************************/
/*                                                                          */
int juggler_circuit::lowest_score() const
{
  const int low = circ().lowest_score();

  return low;
}
