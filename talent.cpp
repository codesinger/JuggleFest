
/*!
 * \file talent.cpp
 *
 * \brief Contains the implementation of talent
 *
 * \author Stewart L. Palmer
 */

#include <regex>
#include <stdlib.h>
#include "assert.h"
#include "scheduler.h"
#include "talent.h"

using namespace ::std;

/*                                                                          */
/****************************************************************************/
/*     S E T _ T A L E N T                                                  */
/****************************************************************************/
/*                                                                          */
int talent::set_talents(
  const smatch       &talents,     /*!< match_results of talents            */
  const unsigned int  start)       /*!< Starting index within match_results */
{
  assert( !((start + 3*2-1) > talents.size()) );
  int rc = 0;
  bool missing_hand      = true;
  bool missing_endurance = true;
  bool missing_pizzazz   = true;
  for (unsigned int i = start; i < (start+3*2); i += 2)
  {
    const string name = talents[i];
    const string quantifier_string = talents[i+1];
    const int quantifier = atoi(quantifier_string.c_str());
    const char type = toupper(name.c_str()[0]);
    switch(type)
    {
      case 'H':
        _hand = quantifier;
        missing_hand = false;
        break;
      case 'E':
        _endurance = quantifier;
        missing_endurance = false;
        break;
      case 'P':
        _pizzazz = quantifier;
        missing_pizzazz = false;
        break;
      default:
        rc = 1;
    }
  }
  if (missing_hand || missing_endurance || missing_pizzazz)
    rc = 1;

  return rc;
}


/*                                                                          */
/****************************************************************************/
/*     S E T _ N A M E                                                      */
/****************************************************************************/
/*                                                                          */
void talent::set_name(
  const string    &the_name)
{
  _name = the_name;
  const char *const nm = name().c_str();
  assert( (nm[0] == 'J') || (nm[0] == 'C') );
  const int d = atoi(&nm[1]);
  set_id(d);
}


/*                                                                          */
/****************************************************************************/
/*     J U G G L E R S _ P E R _ C I R C U I T                              */
/****************************************************************************/
/*                                                                          */
unsigned int talent::jugglers_per_circuit() const
{ return sched().jugglers_per_circuit(); }


/*                                                                          */
/****************************************************************************/
/*     P R I N T _ S E L F                                                  */
/****************************************************************************/
/*                                                                          */
ostream &talent::print_self(
  ostream    &os)                  /*!< The stream into which we stream     */
const
{
  os << name() << " - H:" << hand() << " E:" << endurance() << " P:" << pizzazz();

  return os;
}

