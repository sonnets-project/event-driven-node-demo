/* This is an example that uses an event-driver to control a stack. Note that
 * the driver.c and driver.h source files know nothing about stacks - the
 * event-driving logic is divorced from the application it is supporting.
 *
 * In a fully-fledged event-driven system, you would have some network
 * transport passing events around. In this example, I'm simply going to create
 * a bunch of events in the entry point (main) to consume.
 */

#include <stdio.h>

#include "driver.h"
#include "ebc_node_callbacks.h"

#define TOTAL_INPUT_CHARS 45  /* Always cleanly divisible by 5 */

/* Note the callback functions defined in ebc_node_callbacks.c to assist with
   this example. Now we hook it all up. */
int main(void)
{
    int i;
    int out;
    int rc;
    struct Event event;

    /* Define events from serialised character arrays, because why not */
    unsigned char content[TOTAL_INPUT_CHARS] =
    {
        0x00, 0x00, 0x00, 0x00, 0x00, /* instruction = 0, payload = 0 */
        0x01, 0x00, 0x00, 0x00, 0x00, /* instruction = 1, payload = 0 */
        0x04, 0x7d, 0x00, 0x00, 0x00, /* instruction = 4, payload = 125 */
        0x04, 0x01, 0xff, 0x00, 0x00, /* instruction = 4, payload = 65281 (0xff01) */
        0x03, 0x00, 0x00, 0x00, 0x00, /* instruction = 3, payload = 0 */
        0x02, 0x00, 0x00, 0x00, 0x00, /* instruction = 2, payload = 0 */
        0x03, 0x00, 0x00, 0x00, 0x00, /* instruction = 3, payload = 0 */
        0x03, 0x00, 0x00, 0x00, 0x00, /* instruction = 3, payload = 0 */
        0x10, 0x00, 0x00, 0x00, 0x00  /* instruction = 16, payload = 0  (invalid!) */
    };
    /* This will, in sequence:
     *  - initialise the stack
     *  - get the maximum size of the stack
     *  - push value 125
     *  - push value 65281
     *  - pop, retrieving 65281
     *  - peek, seeing 125
     *  - pop, retrieving 125
     *  - pop (on an empty stack), retrieving 0
     *  - error out, because there is no instruction 16.
     */
    printf("Find this comment in 'driver_demo.c' for what one would expect "
           "to happen!\n");

    /* Register callback functions into our driver's map, each with a different
     * instruction id. */
    reg(0, initialise_cb);
    reg(1, get_max_cb);
    reg(2, peek_cb);
    reg(3, pop_cb);
    reg(4, push_cb);

    /* Run events until we run out of bytes to process. */
    for (i = 0; i < TOTAL_INPUT_CHARS; i = i + 5)
    {
        /* Define the event object from the incoming bytes */
        deserialise(&event, &content[i]);

        /* I must consume... consume everything! */
        rc = consume(&out, &event);
        if (rc != 0)
        {
            /* We received an invalid instruction! */
            printf("Exiting.\n");
            return 1;
        }
    }

    return 0;
}

#undef TOTAL_INPUT_CHARS
