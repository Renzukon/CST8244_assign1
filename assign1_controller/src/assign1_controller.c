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
	int     rcvid;
	int     chid;
	currentState current;

	printf("The controller is running as process_id %d\n", getpid());

    chid = ChannelCreate (0);
    if (chid == -1)
    {
    	perror("failed to create the channel.");
    	exit (EXIT_FAILURE);
    }
    while (1) {
    	rcvid = MsgReceive (chid, &current, sizeof (current), NULL);
    	switch(current.state){
    		case 0:
    			current.outMessage = 0;
    			break;
    	}
    }
	MsgReply (rcvid, EOK, &current, sizeof(current));
	printf("%d\n",current.state);
	return EXIT_SUCCESS;
}
