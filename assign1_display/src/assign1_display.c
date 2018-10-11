#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <string.h>
#include <ctype.h>

#include "proj.h"

int main(int argc, char* argv[]) {
	printf("The display is running as process_id %d\n", getpid());
	return EXIT_SUCCESS;
}
