
#ifndef PROJ_H_
#define PROJ_H_

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

struct currentState {
	int choice;
	int missingchoice;
	int state;
	int input;
	int personId;
	int weight;
}typedef currentState;

struct response {
	char response[128];
}typedef response;

#endif
