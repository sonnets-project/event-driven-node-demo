/* Define callback (cb) functions to be registered into our function map.
 *
 * All of these callback functions return an integer. In a more purpose-built
 * system, you may want to return a void* and allocate memory for the caller to
 * clean up. I'm not going to do that because I want to keep this example as
 * simple as possible - all of our node functions either return an integer or
 * nothing.
 *
 * I'm putting some print statements in here to make it easier to follow the
 * flow of execution. */

#include <stdio.h>

#include "event.h"
#include "stack.h"

/* Initialises the stack. Payload and return value are ignored. */
int initialise_cb(const unsigned char* payload)
{
    (void)payload;  /* Unused */
    printf("cb: initialising stack\n");
    init();
    return 0;
}

/* Functions that return something do so as an integer. */
int get_max_cb(const unsigned char* payload)
{
    int max;
    (void)payload;  /* Unused */
    printf("cb: getting maximum - it is ");
    max = get_max();
    printf("'%d'.\n", max);
    return max;
}

int peek_cb(const unsigned char* payload)
{
    int out;
    (void)payload;  /* Unused */
    printf("cb: peeking - the value is ");
    out = peek();
    printf("'%d'.\n", out);
    return out;
}

int pop_cb(const unsigned char* payload)
{
    int out;
    (void)payload;  /* Unused */
    printf("cb: popping - the value is ");
    out = pop();
    printf("'%d'.\n", out);
    return out;
}

/* Push requires an input value, so we need to define some relationship between
 * the unsigned char* payload, and the integer to go on the stack. Thankfully,
 * this is defined in payload_to_int in event.c for convenience! */
int push_cb(const unsigned char* payload)
{
    int input = payload_to_int(payload);
    printf("cb: pushing value '%d'.\n", input);
    push(input);
    return 0;
}
