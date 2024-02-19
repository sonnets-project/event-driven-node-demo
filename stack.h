/* This file represents the behaviours of a node we might want to code up. It's
 * a simple integer fix-size stack, with the methods below. There is only one
 * "global" stack, controlled by these methods.
 *
 * The point of this example is to demonstrate how comms might be integrated
 * into a node with some state - the behaviour of the node itself doesn't
 * really matter. */
void init(void);
int get_max(void);
int peek(void);
int pop(void);
void push(int);
