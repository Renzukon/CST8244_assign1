/*
 * proj.h
 *
 *  An example H file that you can use as a model for defining enums for the inputs, outputs, and state names.
 *  This approach will make your code more readable :)
 */

#ifndef PROJ_H_
#define PROJ_H_

#define NUM_STATES 12
typedef enum {
	LEFT_SCAN = 0,
	RIGHT_SCAN = 1,
	LEFT_OPEN = 2,
	RIGHT_OPEN = 3,
	LEFT_CLOSE = 4,
	RIGHT_CLOSE = 5,
	GUARD_LU = 6,
	GUARD_LL = 7,
	GUARD_RU = 8,
	GUARD_RL = 9,
	WEIGHT = 10,
	EXIT = 11
} State;


#define NUM_OUTPUTS 13

struct currentState {
	int choice;
	int missingchoice;
	int state;
	int input;
	char outMessage[128];
	int personId;
	int weight;
}typedef currentState;
#endif /* PROJ_H_ */
