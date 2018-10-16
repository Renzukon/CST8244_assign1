/****************************************************************************************
 * Title: assign1_controller.c
 *
 * Authors: Peter Nguyen and Jordan Hoskins
 * Date: 2018-10-16
 *
 * Purpose: The controller will turn the state machine for assignment1.
 * 			inputs are input by the user to determine the current state and next state.
 * 			All states will loop until the correct state in the FSM has been input by
 * 			the user.
 *****************************************************************************************/
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
	   	switch(res.responseCode){
	   		case LEFT_SCAN:
	   		case RIGHT_SCAN:
	   			printf("%s %d\n",outMessage[res.responseCode],res.current.personId);
	   			break;
	   		case WEIGHT:
	   			printf("%s %d\n",outMessage[res.responseCode],res.current.weight);
	   			break;
	   		default:
	   			printf("%s\n",outMessage[res.responseCode]);
	   			break;
	   	}
	   	MsgReply (rcvid, EOK, &res, sizeof(res));
	   	if(res.responseCode == 12){
	   		printf("Exiting Display\n");
	   	    ChannelDestroy(chid);
	   		exit(1);
	   	}
	}

	return EXIT_SUCCESS;
}
