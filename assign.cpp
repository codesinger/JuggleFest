/*!
 * \file assign.cpp
 *
 * \brief Main program for juggler assignment
 *
 * \author Stewart L. Palmer
 */

#include <iostream>
#include "scheduler.h"

using namespace ::std;

int main()
{
  // Read and parse the input file, creating all of the jugglers and circuits
  scheduler sched("input.txt");

  cerr << "circuit count = "          << sched.circuit_count() <<
          ", juggler count = "        << sched.juggler_count() <<
          ", jugglers per circuit = " << sched.jugglers_per_circuit() << endl;

  // Assign all the jugglers to their best fit circuits
  sched.assign();
  cerr << "All jugglers assigned." << endl;

  // Compare the assignments to the original problem statement
  const int arc = sched.validate_assignments(cerr);
  if (arc == 0)
    cerr << "Assignments validated." << endl;

  // Write out the completed assignments
  sched.show_assignments(cout);

  // Get the sum of all jugglers assigned to circuit C1970
  int csum = -1;
  const circuit *const c = sched.get_circuit("C1970");
  if (c == 0)
    cout << "Circuit C1970 does not exist." << endl;
  else
    {
      const circuit &circ = *c;
      csum = circ.juggler_sum();
      cerr << "Juggler sum for C1970 is " << csum << endl;
    }

  // This constitutes a regression test
  assert(csum == 28762);

  return 0;
}
