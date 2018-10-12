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
void *initial_state();
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

typedef void *(*StateFunc)();
StateFunc statefunc = initial_state;
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

    	statefunc = (StateFunc)(*statefunc)();
    	MsgReply (rcvid, EOK, &current, sizeof(current));
    }

    ChannelDestroy(chid);
	return EXIT_SUCCESS;
}

void *initial_state(){
	if(current.state==LEFT_SCAN)
		statefunc = left_scan;
		current.direction = LEFT_SCAN;
	if(current.state ==2)
		statefunc = right_scan;
		current.direction = RIGHT_SCAN;
	return statefunc;
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
	return statefunc;
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
		return statefunc;
}
/**********************************************************************
 *
 * 				2	void left_open(void)
 *********************************************************************/
void *left_open(){
	current.state=LEFT_OPEN;
	res.responseCode = 3;
		if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
			fprintf (stderr, "Error during MsgSend\n");
			perror (NULL);
			exit (EXIT_FAILURE);
		}
		return statefunc;
}
/**********************************************************************
 *
 * 				3	void right_open(void)
 *********************************************************************/
void *right_open(){
	current.state=RIGHT_OPEN;
	res.responseCode = 4;
			if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
				fprintf (stderr, "Error during MsgSend\n");
				perror (NULL);
				exit (EXIT_FAILURE);
			}
			return statefunc;
}
/**********************************************************************
 *
 * 				4	void left_close(void)
 *********************************************************************/
void *left_close(){
	current.state=LEFT_CLOSE;
	res.responseCode = 5;
				if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
					fprintf (stderr, "Error during MsgSend\n");
					perror (NULL);
					exit (EXIT_FAILURE);
				}
				return statefunc;
}
/**********************************************************************
 *
 * 				5	void right_close(void)
 *********************************************************************/
void *right_close(){
	current.state=RIGHT_CLOSE;
	res.responseCode = 6;
					if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
						fprintf (stderr, "Error during MsgSend\n");
						perror (NULL);
						exit (EXIT_FAILURE);
					}
					return statefunc;
}
/**********************************************************************
 *
 * 				6	void guard_LU(void)
 *********************************************************************/
void *guard_LU(){

	current.state=GUARD_LU;
	res.responseCode = 7;
		if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
			fprintf (stderr, "Error during MsgSend\n");
			perror (NULL);
			exit (EXIT_FAILURE);
		}
		return statefunc;
}
/**********************************************************************
 *
 * 				7	void guard_LL(void)
 *********************************************************************/
void *guard_LL(){
	current.state=GUARD_LL;
	res.responseCode = 8;
			if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
				fprintf (stderr, "Error during MsgSend\n");
				perror (NULL);
				exit (EXIT_FAILURE);
			}
			return statefunc;
}
/**********************************************************************
 *
 * 				8	void guard_RU(void)
 *********************************************************************/
void *guard_RU(){
	current.state=GUARD_RU;
	res.responseCode = 9;
			if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
				fprintf (stderr, "Error during MsgSend\n");
				perror (NULL);
				exit (EXIT_FAILURE);
			}
			return statefunc;
}
/**********************************************************************
 *
 * 				9	void guard_RL(void)
 *********************************************************************/
void *guard_RL(){
	current.state=GUARD_RL;
	res.responseCode = 10;
			if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
				fprintf (stderr, "Error during MsgSend\n");
				perror (NULL);
				exit (EXIT_FAILURE);
			}
			return statefunc;
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
	return statefunc;
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
		return statefunc;
}
