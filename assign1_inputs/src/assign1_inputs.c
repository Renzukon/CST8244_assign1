/****************************************************************************************
 * Title: assign1_inputs.c
 *
 * Authors: Peter Nguyen and Jordan Hoskins
 * Date: 2018-10-16
 *
 * Purpose: assign1_inputs handles all cases of inputs from the user, or a text file. Prompts user to enter
 * 			enter an event type. Depending on the event type, it will prompt for additional information.
 * 			Afterwards, a struct with all the values that was prompted is sent off to the controller.
 *
 *****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <string.h>
#include <ctype.h>
#include "proj.h"

int main(int argc, char* argv[]) {
	if(argc >= 2){
	int  coid;
	pid_t serverpid = atoi(argv[1]);
	char state[5];
	currentState current;
	int personid = 0;
	int weight = 0;

	while(current.state != EXIT){
		printf("Enter the event type\n");
		printf("ls = left scan, rs = right scan, ws = weight scale, lo = left open,\nro = right open, lc = left closed, rc = right closed , gru = guard right unlock,\ngrl = guard right lock, gll=guard left lock,glu = guard left unlock\n");
		printf("or type exit to quit\n");

		scanf("%s",&state);

		if(strcmp(state,inMessage[1]) == 0){
			current.state = LEFT_SCAN;
			printf("Please enter your person ID\n");
			scanf("%d",&personid);
			current.personId = personid;
		}else if(strcmp(state,inMessage[2]) == 0){
			current.state = RIGHT_SCAN;
			printf("Please enter your person ID\n");
			scanf("%d",&personid);
			current.personId = personid;
		}else if(strcmp(state, inMessage[3]) == 0){
			current.state = LEFT_OPEN;
		}else if(strcmp(state, inMessage[4]) == 0){
			current.state = RIGHT_OPEN;
		}else if(strcmp(state, inMessage[5]) == 0){
			current.state = LEFT_CLOSE;
		}else if(strcmp(state, inMessage[6]) == 0){
			current.state = RIGHT_CLOSE;
		}else if(strcmp(state, inMessage[7]) == 0){
			current.state = GUARD_LU;
		}else if(strcmp(state, inMessage[8]) == 0){
			current.state = GUARD_LL;
		}else if(strcmp(state, inMessage[9]) == 0){
			current.state = GUARD_RU;
		}else if(strcmp(state, inMessage[10]) == 0){
			current.state = GUARD_RL;
		}else if(strcmp(state, inMessage[11]) == 0){
			current.state = WEIGHT;
			printf("Please enter your weight\n");
			scanf("%d",&weight);
			current.weight = weight;
		}else if(strcmp(state,inMessage[12]) == 0){
			current.state = EXIT;
		}

		coid = ConnectAttach (ND_LOCAL_NODE, serverpid, 1, _NTO_SIDE_CHANNEL, 0);
		if (coid == -1) {
		    fprintf (stderr, "Couldn't ConnectAttach\n");
		    perror (NULL);
		    exit (EXIT_FAILURE);
		}

   		if (MsgSend (coid, &current, sizeof(current), &current, sizeof (current)) == -1) {
   			fprintf (stderr, "Error during MsgSend\n");
   			perror (NULL);
   			exit (EXIT_FAILURE);
   		}
	}
	ConnectDetach(coid);
	return EXIT_SUCCESS;
	}else{
		printf("Not enough arguments supplied.");
	}
	return EXIT_SUCCESS;
}
