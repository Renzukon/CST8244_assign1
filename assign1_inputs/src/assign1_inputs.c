#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <string.h>
#include <ctype.h>

#include "proj.h"

int main(int argc, char* argv[]) {
	int  coid;
	pid_t serverpid = atoi(argv[1]);
	char choice[5];
	currentState current;
	currentState response;
	int personid = 0;
	//int weight = 0;

	printf("Enter the event type\n");
	printf("ls = left scan, rs = right scan, ws = weight scale, lo = left open,\nro = right open, lc = left closed, rc = right closed , gru = guard right unlock,\ngrl = guard right lock, gll=guard left lock,glu = guard left unlock\n");
	printf("or type exit to quit\n");
	coid = ConnectAttach (ND_LOCAL_NODE, serverpid, 1, _NTO_SIDE_CHANNEL, 0);
	    if (coid == -1) {
	    	fprintf (stderr, "Couldn't ConnectAttach\n");
	    	perror (NULL);
	    	exit (EXIT_FAILURE);
	   	}
	while(response.state != EXIT){
		scanf("%s",&choice);
		if(strcmp(choice,"ls") == 0){
			current.choice = 0;
			printf("Please enter your person ID");
			scanf("%d",&personid);
			current.personId = personid;
		}else if(strcmp(choice,"rs") == 0){
			current.choice = 1;
		}else if(strcmp(choice,"ws") == 0){
			current.choice = 2;
		}else if(strcmp(choice,"lo") == 0){
			current.choice = 3;
		}else if(strcmp(choice,"ll") == 0){
			current.choice = 4;
		}else if(strcmp(choice,"ro") == 0){
			current.choice = 5;
		}else if(strcmp(choice,"rl") == 0){
			current.choice = 6;
		}else if(strcmp(choice,"gll") == 0){
			current.choice = 7;
		}else if(strcmp(choice,"glu") == 0){
			current.choice = 8;
		}else if(strcmp(choice,"grl") == 0){
			current.choice = 9;
		}else if(strcmp(choice,"gru") == 0){
			current.choice = 10;
		}else if(strcmp(choice,"exit") == 0){
			current.choice = 11;
		}
   		if (MsgSend (coid, &current, sizeof(current), &response, sizeof (response)) == -1) {
   			fprintf (stderr, "Error during MsgSend\n");
   			perror (NULL);
   			exit (EXIT_FAILURE);
   		}
	}
	printf("Bye bye LOSER");
	return EXIT_SUCCESS;
}
