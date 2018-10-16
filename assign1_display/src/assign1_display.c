/****************************************************************************************
 * Title: assign1_display.c
 *
 * Authors: Peter Nguyen and Jordan Hoskins
 * Date: 2018-10-16
 *
 * Purpose: assign1_display is responsible solely for all output messages. Receives a struct with
 * 			an int variable as well as another structure for values to be displayed. The int value
 * 			determines which message will be output, and depending on certain cases, additional
 * 			information is displayed as well.
 *
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
