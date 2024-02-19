#include "stack.h"

#define STACK_MAX 10

struct
{
    int head;  /* Top value of stack is at stack + head, and head=-1 indicates
                  an empty stack. */
    int data[STACK_MAX];
} stack;

void init(void){stack.head = -1;}

int get_max(void){return STACK_MAX;}  /* Needed because we undef later. */

int peek(void)
{
    if (stack.head < 0) return 0;  /* Yuck */
    else return stack.data[stack.head];
}

int pop(void)
{
    int out = peek();
    if (stack.head >= 0) stack.head--;
    return out;
}

void push(int v)
{
    if (stack.head + 1 < STACK_MAX) stack.head++;  /* Eugh */
    stack.data[stack.head] = v;
}

#undef STACK_MAX
