/* An event is nothing more than a series of bits (well, bytes really). We
 * overlay some structure onto that series of bits for context.
 *
 * If we wanted to turn our stack example into an event-driven node, we might
 * consider it to have:
 * - one input that holds a "request" for the stack (i.e. peek, pop, and push
 *   with a value.
 * - one output, to which popped and peeked values go.
 *
 * ...though there are many ways to slice this. We'll roll with that node
 * example here. To do this, we'll need to define what our events look like. I
 * am arbitrarily going to choose to use the first byte as an "instruction"
 * field, and four more bytes to hold a "payload" (either incoming or
 * outgoing).
 *
 * There's nothing sacred about this - you could vary this however you
 * like. You could even have variable-length payload if you want to.
 *
 * I am also making the brazen assumption that an int is 4-bytes here, and that
 * you know about the endianness of your machine. Mine is LSB-first by byte,
 * MSB-first by bit. YMMV.
 */

#include <stdio.h>

struct Event
{
    unsigned char instruction;
    unsigned char payload[4];
};

int payload_to_int(const unsigned char*);
void print_event(const struct Event*);
void serialise(const struct Event*, unsigned char* const);
void deserialise(struct Event* const, const unsigned char*);
