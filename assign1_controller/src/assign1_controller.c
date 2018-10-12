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

void *left_scan();
void *right_scan();
void *left_open();
void *right_open();
void *left_close();
void *right_close();
void *guard_LU();
void *guard_LL();
void *guard_RU();
void *guard_RL();
void *weight();
void *exit_program();

currentState current;
int  coid;
response res;
int main(int argc, char* argv[]) {

	pid_t serverpid = atoi(argv[1]);
	int  rcvid;
	int  chid;

    chid = ChannelCreate (0);
    if (chid == -1)
    {
    	perror("failed to create the channel.");
    	exit (EXIT_FAILURE);
    }
	printf("The controller is running as process_id %d\n", getpid());
	coid = ConnectAttach (ND_LOCAL_NODE, serverpid, 1, _NTO_SIDE_CHANNEL, 0);
	if (coid == -1) {
		fprintf (stderr, "Couldn't ConnectAttach\n");
		perror (NULL);
		exit(EXIT_FAILURE);
	}
    while (1) {
    	rcvid = MsgReceive (chid, &current, sizeof (current), NULL);
    	switch(current.choice){
    		case 0:
        		left_scan();
    			break;
    		case 1:
    			right_scan();
    			break;
    		case 2:
    			left_open();
    			break;
    		case 3:
    			right_open();
    			break;
    		case 4:
    			left_close();
    			break;
    		case 5:
    			right_close();
    			break;
    		case 6:
    			guard_LU();
    			break;
    		case 7:
    			guard_LL();
    			break;
    		case 8:
    			guard_RU();
    			break;
    		case 9:
    			guard_RL();
    			break;
    		case 10:
    			weight();
    			break;
    		case 11:
    			exit_program();
    			printf("Exiting Controller");
    			exit(1);
    			break;
    		default:
    			break;
    	}
    	MsgReply (rcvid, EOK, &current, sizeof(current));
    }

    ChannelDestroy(chid);
	return EXIT_SUCCESS;
}
/**********************************************************************
 *
 * 				0	void left_scan(void) 0,6,2,4,7,8,3,5,9,11
 *********************************************************************/
void *left_scan(){
	current.state=LEFT_SCAN;
	res.responseCode = 1;
	if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
		fprintf (stderr, "Error during MsgSend\n");
		perror (NULL);
		exit (EXIT_FAILURE);
	}
	return guard_LU();
}
/**********************************************************************
 *
 * 				1	void right_scan(void) 1,8,3,5,9,6,2,4,7,11
 *********************************************************************/
void *right_scan(){
	current.state=RIGHT_SCAN;
		res.responseCode = 2;
		if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
			fprintf (stderr, "Error during MsgSend\n");
			perror (NULL);
			exit (EXIT_FAILURE);
		}
	return guard_RU();
}
/**********************************************************************
 *
 * 				2	void left_open(void)
 *********************************************************************/
void *left_open(){
	current.state=LEFT_OPEN;
	res.responseCode = 3;
	strcpy(res.response,"Left door open");
		if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
			fprintf (stderr, "Error during MsgSend\n");
			perror (NULL);
			exit (EXIT_FAILURE);
		}
	return left_close();
}
/**********************************************************************
 *
 * 				3	void right_open(void)
 *********************************************************************/
void *right_open(){
	current.state=RIGHT_OPEN;
	res.responseCode = 4;
		strcpy(res.response,"right door open");
			if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
				fprintf (stderr, "Error during MsgSend\n");
				perror (NULL);
				exit (EXIT_FAILURE);
			}
	return right_close();
}
/**********************************************************************
 *
 * 				4	void left_close(void)
 *********************************************************************/
void *left_close(){
	current.state=LEFT_CLOSE;
	res.responseCode = 5;
			strcpy(res.response,"left door close");
				if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
					fprintf (stderr, "Error during MsgSend\n");
					perror (NULL);
					exit (EXIT_FAILURE);
				}
	return guard_LL();
}
/**********************************************************************
 *
 * 				5	void right_close(void)
 *********************************************************************/
void *right_close(){
	current.state=RIGHT_CLOSE;
	res.responseCode = 6;
				strcpy(res.response,"right door close");
					if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
						fprintf (stderr, "Error during MsgSend\n");
						perror (NULL);
						exit (EXIT_FAILURE);
					}
	return guard_RL();
}
/**********************************************************************
 *
 * 				6	void guard_LU(void)
 *********************************************************************/
void *guard_LU(){

	current.state=GUARD_LU;
	res.responseCode = 7;
		strcpy(res.response,"Guard Left unlock");
		if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
			fprintf (stderr, "Error during MsgSend\n");
			perror (NULL);
			exit (EXIT_FAILURE);
		}
	return left_open();
}
/**********************************************************************
 *
 * 				7	void guard_LL(void)
 *********************************************************************/
void *guard_LL(){
	current.state=GUARD_LL;
	res.responseCode = 8;
			strcpy(res.response,"Guard Left lock");
			if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
				fprintf (stderr, "Error during MsgSend\n");
				perror (NULL);
				exit (EXIT_FAILURE);
			}
	return 0;
}
/**********************************************************************
 *
 * 				8	void guard_RU(void)
 *********************************************************************/
void *guard_RU(){
	current.state=GUARD_RU;
	res.responseCode = 9;
			strcpy(res.response,"Guard right unlock");
			if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
				fprintf (stderr, "Error during MsgSend\n");
				perror (NULL);
				exit (EXIT_FAILURE);
			}
	return right_open();
}
/**********************************************************************
 *
 * 				9	void guard_RL(void)
 *********************************************************************/
void *guard_RL(){
	current.state=GUARD_RL;
	res.responseCode = 10;
			strcpy(res.response,"Guard right lock");
			if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
				fprintf (stderr, "Error during MsgSend\n");
				perror (NULL);
				exit (EXIT_FAILURE);
			}
	return 0;
}
/**********************************************************************
 *
 * 				10	void weight(void)
 *********************************************************************/
void *weight(){
	current.state=WEIGHT;
	res.responseCode = 11;
	if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
		fprintf (stderr, "Error during MsgSend\n");
		perror (NULL);
		exit (EXIT_FAILURE);
	}
	return 0;
}
/**********************************************************************
 *
 * 				11   void exit(void)
 *********************************************************************/
void *exit_program(){
	current.state = EXIT;
	res.responseCode = 12;
		if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
			fprintf (stderr, "Error during MsgSend\n");
			perror (NULL);
			exit (EXIT_FAILURE);
		}
	return 0;
}
