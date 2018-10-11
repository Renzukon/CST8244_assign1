#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <string.h>
#include <ctype.h>

int main(void) {
	printf("The display is running as process_id %d\n", getpid());
	return EXIT_SUCCESS;
}
