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
	if(argc >= 2){
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

<<<<<<< HEAD
			MsgReply (rcvid, EOK, &current, sizeof(current));
			if(statefunc == exit_program){
				ChannelDestroy(chid);
				exit(1);
			}
		}
=======
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
    	if(statefunc == exit_program){
	   	    ChannelDestroy(chid);
	   		exit(1);
    	}
    }
    ChannelDestroy(chid);
	return EXIT_SUCCESS;
	}else{
		printf("Not enough arguments supplied.");
	}
	return EXIT_SUCCESS;
}

void *initial_state(){
	if(current.state==LEFT_SCAN){
		statefunc = left_scan;
		current.direction = LEFT_SCAN;
	}else if(current.state == RIGHT_SCAN ){
		statefunc = right_scan;
		current.direction = RIGHT_SCAN;
	}else if(current.state == EXIT){
		statefunc = exit_program;
	}else{
		statefunc = initial_state;
		return statefunc;
	}
	statefunc = (StateFunc)(*statefunc)();
	return statefunc;
}
/**********************************************************************
 *
 * 				0	void left_scan(void) 0,6,2,4,7,8,3,5,9,11
 *********************************************************************/
void *left_scan(){
	if(current.state == EXIT){
		statefunc = exit_program;
	}else if(current.state != LEFT_SCAN){
		statefunc = left_scan;
	}else{
		res.responseCode = 1;
		res.current.personId = current.personId;
		if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
			fprintf (stderr, "Error during MsgSend\n");
			perror (NULL);
			exit (EXIT_FAILURE);
		}
		statefunc = guard_LU;
	}
	return statefunc;
}
/**********************************************************************
 *
 * 				0	void left_scan(void) 0,6,2,4,7,8,3,5,9,11
=======
 * 				2	void right_scan(void)
 *********************************************************************/
void *right_scan(){
	if(current.state == EXIT){
		statefunc = exit_program;
	}else if(current.state != RIGHT_SCAN){
		statefunc = right_scan;
	}else{
		res.responseCode = 2;
		res.current.personId = current.personId;
		if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
			fprintf (stderr, "Error during MsgSend\n");
			perror (NULL);
			exit (EXIT_FAILURE);
		}
		statefunc = guard_RU;
	}
		return statefunc;
}
/**********************************************************************
 *
 * 				2	void right_scan(void)
 * 				3	void left_open(void)
 *********************************************************************/
void *left_open(){
	if(current.state == EXIT){
		statefunc = exit_program;
	}else if(current.state != LEFT_OPEN){
		statefunc = left_open;
	}else{
	res.responseCode = 3;
		if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
			fprintf (stderr, "Error during MsgSend\n");
			perror (NULL);
			exit (EXIT_FAILURE);
		}
		if(current.direction == LEFT_SCAN){
			statefunc = weight;
		}else if(current.direction == RIGHT_SCAN){
			statefunc = left_close;
		}
	}
	return statefunc;
>>>>>>> refs/remotes/origin/Jordan
}
/**********************************************************************
 *
<<<<<<< HEAD
 * 				3	void left_open(void)
=======
 * 				3	void right_open(void)
>>>>>>> refs/remotes/origin/Jordan
 *********************************************************************/
<<<<<<< HEAD
void *left_open(){
	if(current.state != LEFT_OPEN){
		statefunc = left_open;
	}else if(current.state == EXIT){
		statefunc = exit_program;
	}else{
	res.responseCode = 3;
		if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
			fprintf (stderr, "Error during MsgSend\n");
			perror (NULL);
			exit (EXIT_FAILURE);
		}
		if(current.direction == LEFT_SCAN){
			statefunc = weight;
		}else if(current.direction == RIGHT_SCAN){
			statefunc = left_close;
		}
=======
void *right_open(){
	if(current.state == EXIT){
		statefunc = exit_program;
	}else if(current.state != RIGHT_OPEN){
		statefunc = right_open;
	}else{
	res.responseCode = 4;
			if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
				fprintf (stderr, "Error during MsgSend\n");
				perror (NULL);
				exit (EXIT_FAILURE);
			}
			if(current.direction == LEFT_SCAN){
				statefunc = right_close;
			}else if(current.direction == RIGHT_SCAN){
				statefunc = weight;
			}
>>>>>>> refs/remotes/origin/Jordan
	}
	return statefunc;
}
/**********************************************************************
 *
<<<<<<< HEAD
 * 				3	void right_open(void)
=======
 * 				4	void left_close(void)
>>>>>>> refs/remotes/origin/Jordan
 *********************************************************************/
<<<<<<< HEAD
void *right_open(){
	if(current.state != RIGHT_OPEN){
		statefunc = right_open;
	}else if(current.state == EXIT){
		statefunc = exit_program;
	}else{
	res.responseCode = 4;
			if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
				fprintf (stderr, "Error during MsgSend\n");
				perror (NULL);
				exit (EXIT_FAILURE);
			}
			if(current.direction == LEFT_SCAN){
				statefunc = right_close;
			}else if(current.direction == RIGHT_SCAN){
				statefunc = weight;
			}
=======
void *left_close(){
	if(current.state == EXIT){
		statefunc = exit_program;
	}else if(current.state != LEFT_CLOSE){
		statefunc = left_close;
	}else{
		res.responseCode = 5;
		if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
			fprintf (stderr, "Error during MsgSend\n");
			perror (NULL);
			exit (EXIT_FAILURE);
		}
		statefunc = guard_LL;
>>>>>>> refs/remotes/origin/Jordan
	}
	return statefunc;
}
/**********************************************************************
 *
<<<<<<< HEAD
 * 				4	void left_close(void)
=======
 * 				5	void right_close(void)
>>>>>>> refs/remotes/origin/Jordan
 *********************************************************************/
<<<<<<< HEAD
void *left_close(){
	if(current.state != LEFT_CLOSE){
		statefunc = left_close;
	}else if(current.state == EXIT){
		statefunc = exit_program;
	}else{
		res.responseCode = 5;
		if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
			fprintf (stderr, "Error during MsgSend\n");
			perror (NULL);
			exit (EXIT_FAILURE);
		}
		statefunc = guard_LL;
=======
void *right_close(){
	if(current.state == EXIT){
		statefunc = exit_program;
	}else if(current.state != RIGHT_CLOSE){
		statefunc = right_close;
	}else{
		res.responseCode = 6;
		if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
			fprintf (stderr, "Error during MsgSend\n");
			perror (NULL);
			exit (EXIT_FAILURE);
		}
		statefunc = guard_RL;
>>>>>>> refs/remotes/origin/Jordan
	}
	return statefunc;
}
/**********************************************************************
 *
<<<<<<< HEAD
 * 				5	void right_close(void)
=======
 * 				6	void guard_LU(void)
>>>>>>> refs/remotes/origin/Jordan
 *********************************************************************/
<<<<<<< HEAD
void *right_close(){
	if(current.state != RIGHT_CLOSE){
		statefunc = right_close;
	}else if(current.state == EXIT){
		statefunc = exit_program;
	}else{
		res.responseCode = 6;
		if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
			fprintf (stderr, "Error during MsgSend\n");
			perror (NULL);
			exit (EXIT_FAILURE);
		}
		statefunc = guard_RL;
=======
void *guard_LU(){
	if(current.state == EXIT){
		statefunc = exit_program;
	}else if(current.state != GUARD_LU){
		statefunc = guard_LU;
	}else{
		res.responseCode = 7;
		if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
			fprintf (stderr, "Error during MsgSend\n");
			perror (NULL);
			exit (EXIT_FAILURE);
		}
		statefunc = left_open;
>>>>>>> refs/remotes/origin/Jordan
	}
	return statefunc;
}
/**********************************************************************
 *
<<<<<<< HEAD
 * 				6	void guard_LU(void)
=======
 * 				7	void guard_LL(void)
>>>>>>> refs/remotes/origin/Jordan
 *********************************************************************/
<<<<<<< HEAD
void *guard_LU(){
	if(current.state != GUARD_LU){
		statefunc = guard_LU;
	}else if(current.state == EXIT){
		statefunc = exit_program;
	}else{
		res.responseCode = 7;
		if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
			fprintf (stderr, "Error during MsgSend\n");
			perror (NULL);
			exit (EXIT_FAILURE);
		}
		statefunc = left_open;
=======
void *guard_LL(){
	if(current.state == EXIT){
		statefunc = exit_program;
	}else if(current.state != GUARD_LL){
		statefunc = guard_LL;
	}else{
		res.responseCode = 8;
		if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
			fprintf (stderr, "Error during MsgSend\n");
			perror (NULL);
			exit (EXIT_FAILURE);
		}
		if(current.direction == LEFT_SCAN){
			statefunc = guard_RU;
		}else if(current.direction == RIGHT_SCAN){
			statefunc = exit_program;
		}
>>>>>>> refs/remotes/origin/Jordan
	}
	return statefunc;
}
/**********************************************************************
 *
<<<<<<< HEAD
 * 				7	void guard_LL(void)
=======
 * 				8	void guard_RU(void)
>>>>>>> refs/remotes/origin/Jordan
 *********************************************************************/
<<<<<<< HEAD
void *guard_LL(){
	if(current.state != GUARD_LL){
		statefunc = guard_LL;
	}else if(current.state == EXIT){
		statefunc = exit_program;
	}else{
		res.responseCode = 8;
		if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
			fprintf (stderr, "Error during MsgSend\n");
			perror (NULL);
			exit (EXIT_FAILURE);
		}
		if(current.direction == LEFT_SCAN){
			statefunc = guard_RU;
		}else if(current.direction == RIGHT_SCAN){
			statefunc = exit_program;
		}
=======
void *guard_RU(){
	if(current.state == EXIT){
		statefunc = exit_program;
	}else if(current.state != GUARD_RU){
		statefunc = guard_RU;
	}else{
		res.responseCode = 9;
		if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
			fprintf (stderr, "Error during MsgSend\n");
			perror (NULL);
			exit (EXIT_FAILURE);
		}
		statefunc = right_open;
>>>>>>> refs/remotes/origin/Jordan
	}
	return statefunc;
}
/**********************************************************************
 *
<<<<<<< HEAD
 * 				8	void guard_RU(void)
=======
 * 				9	void guard_RL(void)
>>>>>>> refs/remotes/origin/Jordan
 *********************************************************************/
<<<<<<< HEAD
void *guard_RU(){
	if(current.state != GUARD_RU){
		statefunc = guard_RU;
	}else if(current.state == EXIT){
		statefunc = exit_program;
	}else{
		res.responseCode = 9;
		if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
			fprintf (stderr, "Error during MsgSend\n");
			perror (NULL);
			exit (EXIT_FAILURE);
		}
		statefunc = right_open;
=======
void *guard_RL(){
	if(current.state == EXIT){
		statefunc = exit_program;
	}else if(current.state != GUARD_RL){
		statefunc = guard_RL;
	}else{
		res.responseCode = 10;
		if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
			fprintf (stderr, "Error during MsgSend\n");
			perror (NULL);
			exit (EXIT_FAILURE);
		}
		if(current.direction == LEFT_SCAN){
			statefunc = exit_program;
		}else if(current.direction == RIGHT_SCAN){
			statefunc = guard_LU;
		}
>>>>>>> refs/remotes/origin/Jordan
	}
	return statefunc;
}
/**********************************************************************
 *
<<<<<<< HEAD
 * 				9	void guard_RL(void)
=======
 * 				10	void weight(void)
>>>>>>> refs/remotes/origin/Jordan
 *********************************************************************/
<<<<<<< HEAD
void *guard_RL(){
	if(current.state != GUARD_RL){
		statefunc = guard_RL;
	}else if(current.state == EXIT){
		statefunc = exit_program;
	}else{
		res.responseCode = 10;
		if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
			fprintf (stderr, "Error during MsgSend\n");
			perror (NULL);
			exit (EXIT_FAILURE);
		}
		if(current.direction == LEFT_SCAN){
			statefunc = exit_program;
		}else if(current.direction == RIGHT_SCAN){
			statefunc = guard_LU;
		}
	}
	return statefunc;
}
/**********************************************************************
 *
 * 				10	void weight(void)
 *********************************************************************/
void *weight(){
	if(current.state != WEIGHT){
		statefunc = weight;
	}else if(current.state == EXIT){
		statefunc = exit_program;
=======
void *weight(){
	if(current.state == EXIT){
		statefunc = exit_program;
	}else if(current.state != WEIGHT){
		statefunc = weight;
>>>>>>> refs/remotes/origin/Jordan
	}else{
		res.responseCode = 11;
		res.current.weight = current.weight;
		if (MsgSend (coid, &res, sizeof(res), &res, sizeof (res)) == -1) {
			fprintf (stderr, "Error during MsgSend\n");
			perror (NULL);
			exit (EXIT_FAILURE);
		}
		if(current.direction == LEFT_SCAN){
			statefunc = left_close;
		}else if(current.direction == RIGHT_SCAN){
			statefunc = right_close;
		}
	}
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
		//exit(1);
		return exit_program;
}
