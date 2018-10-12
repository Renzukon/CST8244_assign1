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
	   	if(res.responseCode == 1 || res.responseCode == 2){
		   	printf("%s %d\n",outMessage[res.responseCode],res.current.personId);
	   	}else if(res.responseCode == 11){
	   		printf("%s %d\n",outMessage[res.responseCode],res.current.weight);
	   	}else{
		   	printf("%s\n",outMessage[res.responseCode]);
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
