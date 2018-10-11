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
	State state;
	//int personid = 0;
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
	while(current.state != EXIT){
		scanf("%s",&choice);
		if(strcmp(choice,"ls") == 0){
			state = LEFT_SCAN;
			current.state = state;
		}else if(strcmp(choice,"rs") == 0){
			state = RIGHT_SCAN;
			current.state = state;
		}else if(strcmp(choice,"ws") == 0){
			state = WEIGHT;
			current.state = state;
		}else if(strcmp(choice,"lo") == 0){
			state = LEFT_OPEN;
			current.state = state;
		}else if(strcmp(choice,"ll") == 0){
			state = LEFT_CLOSE;
			current.state = state;
		}else if(strcmp(choice,"ro") == 0){
			state = RIGHT_OPEN;
			current.state = state;
		}else if(strcmp(choice,"rl") == 0){
			state = RIGHT_CLOSE;
			current.state = state;
		}else if(strcmp(choice,"gll") == 0){
			state = GUARD_LL;
			current.state = state;
		}else if(strcmp(choice,"glu") == 0){
			state = GUARD_LU;
			current.state = state;
		}else if(strcmp(choice,"grl") == 0){
			state = GUARD_RL;
			current.state = state;
		}else if(strcmp(choice,"gru") == 0){
			state = GUARD_RU;
			current.state = state;
		}else if(strcmp(choice,"exit") == 0){
			state = EXIT;
			current.state = state;
		}
   		if (MsgSend (coid, &current, sizeof(current), &response, sizeof (response)) == -1) {
   			fprintf (stderr, "Error during MsgSend\n");
   			perror (NULL);
   			exit (EXIT_FAILURE);
   		}

>>>>>>> refs/heads/Peter
	}
	printf("Bye bye LOSER");
	return EXIT_SUCCESS;
}
