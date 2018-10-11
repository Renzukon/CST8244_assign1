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

currentState current;

int main(int argc, char* argv[]) {
	int     rcvid;
	int     chid;


	printf("The controller is running as process_id %d\n", getpid());

    chid = ChannelCreate (0);
    if (chid == -1)
    {
    	perror("failed to create the channel.");
    	exit (EXIT_FAILURE);
    }
    while (1) {
    	rcvid = MsgReceive (chid, &current, sizeof (current), NULL);
    	switch(current.state){
    		case 0:
    			left_scan();
    			break;
    		default:
    			break;
    	}
    }
	MsgReply (rcvid, EOK, &current, sizeof(current));
	printf("%d\n",current.state);
	return EXIT_SUCCESS;
}
/**********************************************************************
 *
 * 					void left_scan(void)
 *********************************************************************/
void left_scan(void){



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
