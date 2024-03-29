#include "event.h"

#include <stdio.h>

int payload_to_int(const unsigned char* payload){return *(int*)payload;}

void print_event(const struct Event* event)
{
    printf("Instruction: %d, Payload: %d\n",
           event->instruction, payload_to_int(event->payload));
}

void serialise(const struct Event* event, unsigned char* const bytes)
{
    /* Deliberately hardcoded to emphasise the point */
    bytes[0] = event->instruction;
    bytes[1] = event->payload[0];
    bytes[2] = event->payload[1];
    bytes[3] = event->payload[2];
    bytes[4] = event->payload[3];
}

void deserialise(struct Event* const event, const unsigned char* bytes)
{
    /* Deliberately hardcoded to emphasise the point */
    event->instruction = bytes[0];
    event->payload[0] = bytes[1];
    event->payload[1] = bytes[2];
    event->payload[2] = bytes[3];
    event->payload[3] = bytes[4];
}
