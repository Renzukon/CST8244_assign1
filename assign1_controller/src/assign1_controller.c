#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <string.h>
#include <ctype.h>
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

/**********************************************************************
 *
 * 					int main(void)
 *********************************************************************/
int main(void) {

	int rcvid;
	int chid;

	currentState current;
	currentState future;

	chid = ChannelCreate (0);
	if(chid ==-1){
		perror("failed to create channel");
		exit(EXIT_FAILURE);
	}

	printf("The controller is running as process_id %d\n", getpid());

	while(1){
		rcvid = MsgReceive(chid,&current,sizeof(current),NULL);

		printf("State: %d\n", current.state);
		printf("Input: %d\n", current.input);
		printf("Out Message: %d\n", current.outMessage);
		printf("PersonID: %d\n", current.personId);
		printf("Weight: %d\n", current.weight);
	}

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
