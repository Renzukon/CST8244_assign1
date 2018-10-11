#include <stdio.h>
#include <stdlib.h>

int main(void) {
	printf("The controller is running as process_id %d\n", getpid());
	return EXIT_SUCCESS;
}
