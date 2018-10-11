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
	   	if(res.state == 1){
	   		printf("[status update : %s Person Id : %d ]\n",res.response,res.personId);
	   	}else if(res.state == 2){
	   		printf("[status update : %s Weight : %d ]\n",res.response,res.weight);
	   	}else if(res.state == 0){
		   	printf("[status update : %s ]\n",res.response);
	   	}
	   	if(res.state == -1){
	   		printf("Exiting Display");
	   		exit(1);
	   	}
	   	MsgReply (rcvid, EOK, &res, sizeof(res));
	}

	return EXIT_SUCCESS;
}
