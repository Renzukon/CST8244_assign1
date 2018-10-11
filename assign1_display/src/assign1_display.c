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
	response res;

	int     rcvid;
	int     chid;

	printf("The display is running as process_id %d\n", getpid());
	printf("[status update : initial startup]\n");

	chid = ChannelCreate (0);
	if (chid == -1)
	{
	   	perror("failed to create the channel.");
	   	exit (EXIT_FAILURE);
	}
	while (1) {
	   	rcvid = MsgReceive (chid, &res, sizeof (res), NULL);
	   	printf("[status update : %s ]\n",res.response);
	   	MsgReply (rcvid, EOK, &res, sizeof(res));
	}

	return EXIT_SUCCESS;
}
