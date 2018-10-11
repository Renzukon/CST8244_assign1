#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "proj.h"

//function prototypes

void left_scan(void);
void right_scan(void);
void left_open(void);
void right_open(void);
void left_close(void);
void right_close(void);
void guard_LU(void);
void guard_LL(void);
void guard_RU(void);
void guard_RL(void);
void weight(void);
void exit_program(void);

response res;

int main(int argc, char* argv[]) {

	//pid_t serverpid = atoi(argv[1]);
	int  rcvid;
	int  chid;
	currentState current;

	//int  coid;

    chid = ChannelCreate (0);
    if (chid == -1)
    {
    	perror("failed to create the channel.");
    	exit (EXIT_FAILURE);
    }
	printf("The controller is running as process_id %d\n", getpid());
	/*coid = ConnectAttach (ND_LOCAL_NODE, serverpid, 1, _NTO_SIDE_CHANNEL, 0);
	if (coid == -1) {
		fprintf (stderr, "Couldn't ConnectAttach\n");
		perror (NULL);
		exit(EXIT_FAILURE);
	}*/
    while (1) {
    	rcvid = MsgReceive (chid, &current, sizeof (current), NULL);
    	switch(current.choice){
    		case 0:
    			left_scan();
    			/*if (MsgSend (coid, &future, sizeof(future), &current, sizeof (current)) == -1) {
    				fprintf (stderr, "Error during MsgSend\n");
    				perror (NULL);
    				exit (EXIT_FAILURE);
    			}*/
    			printf("I'm out\n");
    			break;
    		default:
    			break;
    	}
    	MsgReply (rcvid, EOK, &res, sizeof(res));
    }

    ChannelDestroy(chid);
	return EXIT_SUCCESS;
}
/**********************************************************************
 *
 * 					void left_scan(void)
 *********************************************************************/
void left_scan(void){
	printf("I am here\n");
	//current.state=LEFT_SCAN;
	strcpy(res.response,"Left Scan");
}
/**********************************************************************
 *
 * 					void right_scan(void)
 *********************************************************************/
void right_scan(void){

}
/**********************************************************************
 *
 * 					void left_open(void)
 *********************************************************************/
void left_open(void){

}
/**********************************************************************
 *
 * 					void right_open(void)
 *********************************************************************/
void right_open(void){

}
/**********************************************************************
 *
 * 					void left_close(void)
 *********************************************************************/
void left_close(void){

}
/**********************************************************************
 *
 * 					void right_close(void)
 *********************************************************************/
void right_close(void){

}
/**********************************************************************
 *
 * 					void guard_LU(void)
 *********************************************************************/
void guard_LU(void){

}
/**********************************************************************
 *
 * 					void guard_LL(void)
 *********************************************************************/
void guard_LL(void){

}
/**********************************************************************
 *
 * 					void guard_RU(void)
 *********************************************************************/
void guard_RU(void){

}
/**********************************************************************
 *
 * 					void guard_RL(void)
 *********************************************************************/
void guard_RL(void){

}
/**********************************************************************
 *
 * 					void weight(void)
 *********************************************************************/
void weight(void){

}
/**********************************************************************
 *
 * 					void exit(void)
 *********************************************************************/
void exit_program(void){

}
