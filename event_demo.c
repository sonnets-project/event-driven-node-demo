#include <stdio.h>

#include "event.h"

int main(void)
{
    struct Event event;
    unsigned char bytes[5];
    bytes[0] = '9';
    bytes[1] = '}';
    bytes[2] = '\0';
    bytes[3] = '\0';
    bytes[4] = '\0';  /* 057 125 000 000 000 */
    deserialise(&event, bytes);
    print_event(&event);
    printf("    (expected Instruction: 57, Payload: 125)\n");
    serialise(&event, bytes);
    printf("Byte string: '%s'\n    (expected '9}')\n", bytes);
    return 0;
}
