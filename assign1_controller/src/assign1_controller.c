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

int left_scan(void);
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

currentState current;
int  coid;
int main(int argc, char* argv[]) {

	int chid;
	int rcvid;

	printf("The controller is running as process_id %d\n", getpid());



    chid = ChannelCreate (0);
    if (chid == -1)
    {
    	perror("failed to create the channel.");
    	exit (EXIT_FAILURE);
    }

    while (1) {
    	rcvid = MsgReceive (chid, &current, sizeof (current), NULL);
    	switch(current.choice){
    		case 0:
    			left_scan();
    			break;
    		case 11:
    			exit_program();
    			break;
    		default:
    			break;
    	}

    	MsgReply(rcvid,EOK,&current,sizeof(current));
    }
	printf("%d\n",current.state);
	ChannelDestroy(chid);
	return EXIT_SUCCESS;
}
/**********************************************************************
 *
 * 					void left_scan(void)
 *********************************************************************/
int left_scan(){
	current.state=LEFT_SCAN;
	strcpy(current.outMessage,"Left Scan");
	printf("I AM HERE: %s", current.outMessage);

	/*if (MsgSend (coid, &current, sizeof(current), &current, sizeof (current)) == -1) {
		fprintf (stderr, "Error during MsgSend\n");
		perror (NULL);
		exit (EXIT_FAILURE);
	}*/
	return 0;
}
/**********************************************************************
 *
 * 					void right_scan(void)
 *********************************************************************/
void right_scan(void){
	current.state = RIGHT_SCAN;
	strcpy(current.outMessage, "RIGHT SCAN");
	printf("STATUS: %s", current.outMessage);
}
/**********************************************************************
 *
 * 					void left_open(void)
 *********************************************************************/
void left_open(void){
	current.state = LEFT_OPEN;
	strcpy(current.outMessage, "LEFT OPEN");
}
/**********************************************************************
 *
 * 					void right_open(void)
 *********************************************************************/
void right_open(void){
	current.state = RIGHT_OPEN;
	strcpy(current.outMessage, "RIGHT OPEN");
}
/**********************************************************************
 *
 * 					void left_close(void)
 *********************************************************************/
void left_close(void){
	current.state = LEFT_CLOSE;
	strcpy(current.outMessage, "LEFT CLOSE");
}
/**********************************************************************
 *
 * 					void right_close(void)
 *********************************************************************/
void right_close(void){
	current.state = RIGHT_CLOSE;
	strcpy(current.outMessage, "RIGHT CLOSE");
}
/**********************************************************************
 *
 * 					void guard_LU(void)
 *********************************************************************/
void guard_LU(void){
	current.state = GUARD_LU;
	strcpy(current.outMessage, "GUARD LEFT UNLOCK");
}
/**********************************************************************
 *
 * 					void guard_LL(void)
 *********************************************************************/
void guard_LL(void){
	current.state = GUARD_LL;
	strcpy(current.outMessage, "GUARD LEFT LOCK");
}
/**********************************************************************
 *
 * 					void guard_RU(void)
 *********************************************************************/
void guard_RU(void){
	current.state = GUARD_RU;
	strcpy(current.outMessage, "GUARD RIGHT UNLOCK");
}
/**********************************************************************
 *
 * 					void guard_RL(void)
 *********************************************************************/
void guard_RL(void){
	current.state = GUARD_RL;
	strcpy(current.outMessage, "GUARD RIGHT LOCK");
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
current.state = EXIT;
}
