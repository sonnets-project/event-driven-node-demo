/* Now we have defined what an event is, and the behaviour of a node (our stack
 * example), we are ready to create an application node by incorporating a
 * driver.
 *
 * A driver accepts incoming events, and executes functions depending on what
 * it receives.
 *
 * In terms of data, a driver is a glorified map between the instruction field
 * of an event, and the functions that it executes. The driver doesn't define
 * any node logic - the driver simply "drives" the behaviour of the node.
 *
 * Since we're in C, and our instruction field is defined by a character
 * (i.e. a byte), we initialise an array of size "byte", and use that to store
 * function pointers to execute. This is our glorified map. In C++ you would
 * consider a std::map, in Python a dictionary, in Lua a table, and so on.
 *
 * Note that the payload of our event structure is a 4-length array of
 * characters also.
 */

#include "event.h"
#define DRIVER_MAP_SIZE 256  /* i.e. sizeof(char) */

/* Consumes an event, invokes some node logic, and returns the value to the
 * caller. */
int consume(int*, struct Event*);

/* Registers a function into the map. */
void reg(unsigned, int (*cb)(unsigned char*));
