#ifndef doxygen_h_included
#define doxygen_h_included 1

/*!
 * \file doxygen.h
 *
 * \brief Contains documentation about the program
 *
 * \author Stewart L. Palmer
 */



/*!
 *  \mainpage Solution for Yodle jugglers and circuits
 *
 * \section pstmt Problem statement (copied from Yodle web site)
 *
 * Many developers here at Yodle are avid jugglers. To celebrate their prowess we
 * are organizing a Yodle Open JuggleFest, but we need your help planning it. There
 * will be thousands of participants split into teams. Each team will attempt to
 * complete a juggling circuit consisting of several tricks. Each circuit
 * emphasizes different aspects of juggling, requiring hand to eye coordination
 * (H), endurance (E) and pizzazz (P) in various amounts for successful
 * completion. Each juggler has these abilities in various amounts as well. How
 * good a match they are for a circuit is determined by the dot product of the
 * juggler’s and the circuit’s H, E, and P values. The higher the result, the
 * better the match.
 *
 * Each participant will be on exactly one team and there will be a distinct
 * circuit for each team to attempt. Each participant will rank in order of
 * preference their top X circuits. Since we would like the audiences to enjoy the
 * performances as much as possible, when assigning jugglers to circuits we also
 * want to consider how well their skills match up to the circuit. In fact we want
 * to match jugglers to circuits such that no juggler could switch to a circuit
 * that they prefer more than the one they are assigned to and be a better fit for
 * that circuit than one of the other jugglers assigned to it.
 *
 * To help us create the juggler/circuit assignments write a program in a language
 * of your choice that takes as input a file of circuits and jugglers and outputs a
 * file of circuits and juggler assignments. The number of jugglers assigned to a
 * circuit should be the number of jugglers divided by the number of
 * circuits. Assume that the number of circuits and jugglers will be such that each
 * circuit will have the same number of jugglers with no remainder.
 *
 * Input file
 *
 * One line per circuit or juggler. All circuits will come before any
 * jugglers. Circuit lines start with a C and juggler lines start with a J. Names
 * of circuits and jugglers will never have spaces. A skill and the rating for that
 * skill are separated by a colon. Circuit lines have the circuit names followed by
 * skills. Juggler lines have the juggler names followed by skills, followed by
 * circuits in order of preference, separated by commas. Example:
 *
 \verbatim
 C C0 H:7 E:7 P:10
 C C1 H:2 E:1 P:1
 C C2 H:7 E:6 P:4

 J J0 H:3 E:9 P:2 C2,C0,C1
 J J1 H:4 E:3 P:7 C0,C2,C1
 J J2 H:4 E:0 P:10 C0,C2,C1
 J J3 H:10 E:3 P:8 C2,C0,C1
 J J4 H:6 E:10 P:1 C0,C2,C1
 J J5 H:6 E:7 P:7 C0,C2,C1
 J J6 H:8 E:6 P:9 C2,C1,C0
 J J7 H:7 E:1 P:5 C2,C1,C0
 J J8 H:8 E:2 P:3 C1,C0,C2
 J J9 H:10 E:2 P:1 C1,C2,C0
 J J10 H:6 E:4 P:5 C0,C2,C1
 J J11 H:8 E:4 P:7 C0,C1,C2
 \endverbatim
 *
 * Output file
 *
 * One line per circuit assignment. Each line should contain the circuit name
 * followed by the juggler name, followed by that juggler’s circuits in order of
 * preference and the match score for that circuit. The line should include all
 * jugglers matched to the circuit. The example below is a valid assignment for the
 * input file above.
 *
 \verbatim
 C2 J6 C2:128 C1:31 C0:188, J3 C2:120 C0:171 C1:31, J10 C0:120 C2:86 C1:21, J0 C2:83 C0:104 C1:17
 C1 J9 C1:23 C2:86 C0:94, J8 C1:21 C0:100 C2:80, J7 C2:75 C1:20 C0:106, J1 C0:119 C2:74 C1:18
 C0 J5 C0:161 C2:112 C1:26, J11 C0:154 C1:27 C2:108, J2 C0:128 C2:68 C1:18, J4 C0:122 C2:106 C1:23
 \endverbatim
 *
 * Run your program on this input file which contains 2000 circuits and 12000
 * jugglers. Send us both your code and the output file to the following e-mail
 * address: the sum of the names of the jugglers (taking off the leading letter J)
 * that are assigned to circuit C1970 \@yodle.com. So for example if the jugglers
 * assigned to circuit C1970 were J1,J2,J3,J4,J5 and J6 you would send your
 * solution to 21\@yodle.com
 *
 * \section psoln Problem solution
 *
 * This program does the scheduling of the jugglers into circuits with one pass
 * through the jugglers and one conditional pass through the circuits if there exist
 * any jugglers that cannot be placed into any of their preferred circuits.  The
 * time required for the scheduling is O(j*n + c), where j is the number of
 * jugglers, n is the number of preferences expressed by each juggler, and c is the
 * number of circuits.  But the parsing of the input records and the conversion from
 * strings to numbers completely dominates the time required for the juggler
 * assignments.
 *
 * First we try to assign each juggler to its first preferred circuit.  This is done
 * by calling juggler::add_to_first_preferred_circuit().  This finds the first
 * preferred circuit for the juggler and calls circuit::reassign_juggler() on the
 * circuit of first preference.
 *
 * If the juggler does not fit or if it has to evict a worse fitting juggler, there
 * remains a juggler yet to be assigned.  reassign_juggler() calls itself
 * recursively until the juggler has been assigned to a best fitting circuit or has
 * run out of preferred circuits.  If the juggler runs out of preferred circuits, it
 * is added to the set of orphaned jugglers that do not fit in any of their
 * preferred circuits.
 *
 * At the end of this one pass through the jugglers, all jugglers are assigned to
 * their best fit, with the possible exception of jugglers that did not fit in any
 * of their preferred circuits.
 *
 * If y orphaned jugglers exist, there are y open slots in the circuits.  At this
 * point we go through all the circuits.  We fill any open slot in a circuit with
 * the next orphaned juggler.  It matters not which jugglers are used to fill the
 * open slots.  It is still the case that none of these orphaned jugglers could be
 * moved to a circuit that they prefer more and be a better fit than any juggler in
 * that circuit.  If that were true they would already have been assigned there.
 *
 * In order to be certain that all of the assignments have been done correctly, we
 * make one more pass through the jugglers and circuits to validate that the
 * assignments form a correct solution to the problem.
 *
 * Although there are a number of classes here to parse the input, create, and
 * manipulate the required objects, the top level path to do the basic assignments
 * consists of only 51 lines of code.  If there are any orphaned jugglers at the end
 * of the initial assignment, the top level path to distribute the orphaned jugglers
 * into the underfull circuits is only another 29 lines of code.  At its heart, this
 * is a simple and easy to maintain program.
 *
 */

#endif                             /* doxygen_h_included                  */

