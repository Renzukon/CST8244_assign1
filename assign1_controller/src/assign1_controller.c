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

currentState current;
int  coid;
response res;
StateFunc statefunc = initial_state;

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

	statefunc = (StateFunc)(*statefunc)();
	return statefunc;
}
/**********************************************************************
 *
 * 				1	void left_scan(void)
 *********************************************************************/
void *left_scan(){
	res.responseCode = 1;
	if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
		fprintf (stderr, "Error during MsgSend\n");
		perror (NULL);
		exit (EXIT_FAILURE);
	}
	statefunc = guard_LU;
	return statefunc;
}
/**********************************************************************
 *
 * 				2	void right_scan(void)
 *********************************************************************/
void *right_scan(){
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
 * 				3	void left_open(void)
 *********************************************************************/
void *left_open(){
	res.responseCode = 3;
		if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
			fprintf (stderr, "Error during MsgSend\n");
			perror (NULL);
			exit (EXIT_FAILURE);
		}
		statefunc = weight;
		return statefunc;
}
/**********************************************************************
 *
 * 				3	void right_open(void)
 *********************************************************************/
void *right_open(){
	res.responseCode = 4;
			if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
				fprintf (stderr, "Error during MsgSend\n");
				perror (NULL);
				exit (EXIT_FAILURE);
			}
			statefunc = right_close;
			return statefunc;
}
/**********************************************************************
 *
 * 				4	void left_close(void)
 *********************************************************************/
void *left_close(){
	res.responseCode = 5;
				if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
					fprintf (stderr, "Error during MsgSend\n");
					perror (NULL);
					exit (EXIT_FAILURE);
				}
				statefunc = guard_LL;
				return statefunc;
}
/**********************************************************************
 *
 * 				5	void right_close(void)
 *********************************************************************/
void *right_close(){
	res.responseCode = 6;
					if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
						fprintf (stderr, "Error during MsgSend\n");
						perror (NULL);
						exit (EXIT_FAILURE);
					}
					statefunc = guard_RL;
					return statefunc;
}
/**********************************************************************
 *
 * 				6	void guard_LU(void)
 *********************************************************************/
void *guard_LU(){
	res.responseCode = 7;
		if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
			fprintf (stderr, "Error during MsgSend\n");
			perror (NULL);
			exit (EXIT_FAILURE);
		}
		statefunc = left_open;
		return statefunc;
}
/**********************************************************************
 *
 * 				7	void guard_LL(void)
 *********************************************************************/
void *guard_LL(){
	res.responseCode = 8;
			if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
				fprintf (stderr, "Error during MsgSend\n");
				perror (NULL);
				exit (EXIT_FAILURE);
			}
			statefunc = guard_RU;
			return statefunc;
}
/**********************************************************************
 *
 * 				8	void guard_RU(void)
 *********************************************************************/
void *guard_RU(){
	res.responseCode = 9;
			if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
				fprintf (stderr, "Error during MsgSend\n");
				perror (NULL);
				exit (EXIT_FAILURE);
			}
			statefunc = right_open;
			return statefunc;
}
/**********************************************************************
 *
 * 				9	void guard_RL(void)
 *********************************************************************/
void *guard_RL(){
	res.responseCode = 10;
			if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
				fprintf (stderr, "Error during MsgSend\n");
				perror (NULL);
				exit (EXIT_FAILURE);
			}
			statefunc = exit_program;
			return statefunc;
}
/**********************************************************************
 *
 * 				10	void weight(void)
 *********************************************************************/
void *weight(){
	res.responseCode = 11;
	if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
		fprintf (stderr, "Error during MsgSend\n");
		perror (NULL);
		exit (EXIT_FAILURE);
	}
	statefunc = left_close;
	return statefunc;
}
/**********************************************************************
 *
 * 				11   void exit(void)
 *********************************************************************/
void *exit_program(){
	res.responseCode = 12;
		if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
			fprintf (stderr, "Error during MsgSend\n");
			perror (NULL);
			exit (EXIT_FAILURE);
		}
		exit(1);
		return 0;
}
