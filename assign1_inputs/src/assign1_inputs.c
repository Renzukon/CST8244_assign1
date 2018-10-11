#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <string.h>
#include <ctype.h>

#include "proj.h"

int main(void) {
	char choice[5];
	currentState current;
	State state;
	int personid = 0;
	int weight = 0;

	printf("Enter the event type\n");
	printf("ls = left scan, rs = right scan, ws = weight scale, lo = left open,\nro = right open, lc = left closed, rc = right closed , gru = guard right unlock,\ngrl = guard right lock, gll=guard left lock,glu = guard left unlock\n");
	printf("or type exit to quit\n");
	while(current.state != EXIT){
		scanf("%s",&choice);
		if(strcmp(choice,"ls") == 0){
			state = LEFT_SCAN;
			current.state = state;
			printf("Please enter person id\n");
			scanf("%d",personid);
			current.personId = personid;
		}else if(strcmp(choice,"rs") == 0){
			state = RIGHT_SCAN;
			current.state = state;
			printf("Please enter person id\n");
			scanf("%d",personid);
			current.personId = personid;
		}else if(strcmp(choice,"ws") == 0){
			state = WEIGHT;
			current.state = state;
			printf("Please enter weight\n");
			scanf("%d",weight);
			current.personId = weight;
		}else if(strcmp(choice,"exit") == 0){
			state = EXIT;
			current.state = state;
		}
	}
	printf("Bye bye LOSER");
	return EXIT_SUCCESS;
}
