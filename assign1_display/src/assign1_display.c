#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "proj.h"

int main(int argc, char* argv[]) {
	currentState current;

	int     rcvid;
	int     chid;

    chid = ChannelCreate (0);
    if (chid == -1)
    {
    	perror("failed to create the channel.");
    	exit (EXIT_FAILURE);
    }

	printf("The display is running as process_id %d\n", getpid());
	printf("[status update : initial startup]\n");

	chid = ChannelCreate (0);
	if (chid == -1)
	{
	   	perror("failed to create the channel.");
	   	exit (EXIT_FAILURE);
	}
	while (1) {
	   	rcvid = MsgReceive (chid, &current, sizeof (current), NULL);
	   	printf("[status update : %s ]\n",current.outMessage);
	}
	MsgReply (rcvid, EOK, &current, sizeof(current));
	return EXIT_SUCCESS;
}
