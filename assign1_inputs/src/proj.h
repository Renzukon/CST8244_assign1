#ifndef PROJ_H_
#define PROJ_H_

typedef enum {
	INITIAL = 0,
	LEFT_SCAN = 1,
	RIGHT_SCAN = 2,
	LEFT_OPEN = 3,
	RIGHT_OPEN = 4,
	LEFT_CLOSE = 5,
	RIGHT_CLOSE = 6,
	GUARD_LU = 7,
	GUARD_LL = 8,
	GUARD_RU = 9,
	GUARD_RL = 10,
	WEIGHT = 11,
	EXIT = 12
} State;

#define NUM_INPUTS 13

const char *inMessage[NUM_INPUTS] = {
		"",
		"ls",
		"rs",
		"lo",
		"ro",
		"lc",
		"rc",
		"glu",
		"gll",
		"gru",
		"grl",
		"ws",
		"exit"
};

#define NUM_OUTPUTS 13	// where n equals the number of output messages from the FSM.

const char *outMessage[NUM_OUTPUTS] = {
	"",
	"Left Scan",
	"Right Scan",
	"Left Open",
	"Right Open",
	"Left Close",
	"Right Close",
	"Guard Left Unlock",
	"Guard Left Lock",
	"Guard Right Unlock",
	"Guard Right Lock",
	"Weighing ",
	"Exiting"
};

struct currentState {

	int state;
	int direction;
	int personId;
	int weight;
}typedef currentState;

struct response {
	currentState current;
	int responseCode;
}typedef response;

#endif
