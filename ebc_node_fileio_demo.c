/* This is an example that builds on ebc_node_demo to control a stack by
 * reading events from a file, and writing some data to an output file.
 *
 * To reiterate, in a fully-fledged event-driven system, you would have some
 * network transport passing events around. In this example, an 'event' is a
 * modification to an input file.
 *
 * Note: uses inotify, so Linux (>=2.6.13) only.
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/inotify.h>
#include <unistd.h>

#include "driver.h"
#include "ebc_node_callbacks.h"
#include "stack.h"

/* Note the callback functions defined in ebc_node_callbacks.c to assist with
   this example. Now we hook it all up. */
int main(int const argc, char const* const* const argv)
{
    struct Event event;
    int out;
    FILE *eventFl;
    unsigned char eventBuf[sizeof(struct Event)];
    int inotifyfd;
    int inotifywd;
    char inotifyBuf[sizeof(struct inotify_event)]; /* One inotify event */
    struct inotify_event *inotifyEvent;
    ssize_t readrc;
    char *watchPath;
    FILE *watchFl;

    /* Read first argument for name of file to watch, and store. Make sure it
     * exists before we start getting serious. */
    if (argc < 2)
    {
        fprintf(stderr, "Give me a path to watch for events!\n");
        return 1;
    }
    if (!(watchPath = calloc(strlen(argv[1]) + 1, sizeof(char))) && argv[1])
    {
        perror("calloc");
        return 1;
    }
    else strcpy(watchPath, argv[1]);
    if (!(watchFl = fopen(watchPath, "r")))
    {
        perror("fopen");
        return 1;
    }
    if (fclose(watchFl))
    {
        perror("fclose");
        return 1;
    }

    /* Register callback functions into our driver's map, each with a different
     * instruction id. */
    reg(0, initialise_cb);
    reg(1, get_max_cb);
    reg(2, peek_cb);
    reg(3, pop_cb);
    reg(4, push_cb);

    /* Set up inotify */
    if ((inotifyfd = inotify_init()) < 0)
    {
        perror("inotify_init");
        return 1;
    }
    if ((inotifywd = inotify_add_watch(inotifyfd, watchPath,
                                       IN_MODIFY)) < 0)
    {
        perror("inotify_add_watch");
        return 1;
    }

    /* Here we enter our blocking read loop. We only pass 'read' when our file
       is modified. */
    do
    {
        if ((readrc = read(inotifyfd, inotifyBuf,
                           sizeof(struct inotify_event))) < 0)
        {
            perror("read");
            return 1;
        }
        printf("Change detected.\n");
        inotifyEvent = (struct inotify_event*) inotifyBuf;
        if (inotifyEvent->wd == inotifywd)
        {
            /* Read file for five bytes */
            if (!(eventFl = fopen(watchPath, "r")))
            {
                perror("fopen");
                return 1;
            }
            if (fread(eventBuf, sizeof(char),
                      sizeof(struct Event) / sizeof(char), eventFl) < 5)
            {
                /* Too short, or error? */
                if (feof(eventFl))
                {
                    printf("Event too short!\n");  /* Try again... */
                    continue;
                }
                else
                {
                    perror("fread");
                    return 1;
                }
            }
            if (fclose(eventFl))
            {
                perror("fclose");
                return 1;
            }

            /* Define the event object from bytes in the file */
            deserialise(&event, eventBuf);

            /* Consume said event */
            if (consume(&out, &event))
            {
                /* We received an invalid instruction! */
                printf("Invalid instruction!\n");
                continue;
            }
        }
    } while (1);
    return 0;
}
