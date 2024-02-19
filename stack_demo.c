#include <stdio.h>

#include "stack.h"

int main(void)
{
	int i;
	int max;

	/* By way of demonstration. */
	init();
	push(4);
	push(5);
	push(6);
	printf("%d ", peek());  /* 6 */
	for (i = 0; i<4; i++) printf("%d ", pop());  /* 6 5 4 0 */
	/* Stack is now empty. */
	printf("\n    (expected 6 6 5 4 0)\n");

	/* And now we break it forcefully. */
	max = get_max();
	for (i = 0; i < max + 5; i++) push(i);
	for (i = 0; i < max; i++) printf("%d ", pop());
	/* Stack is now empty */
	printf("\n    (expected 14 8 7 6 5 4 3 2 1 0)\n");
	return 0;
}
