/*
 * ControlFSM.h
 *
 *  Created on: Mar 29, 2020
 *      Author: jesse
 */

#ifndef CONTROLFSM_H_
#define CONTROLFSM_H_

#include <string>
#include <memory>
#include <unordered_map>
#include <SDL2/SDL.h>
#include <functional>
#include "KeyMap.h"

using namespace std;

const string START_STATE = "START";
const string CTRL_DOWN = "CTRL_DOWN";
const string PICK_UP = "PICK_UP";
const string DROP = "DROP";

const string MOVE_UP = "MOVE_UP";
const string MOVE_LEFT = "MOVE_LEFT";
const string MOVE_RIGHT = "MOVE_RIGHT";
const string MOVE_DOWN = "MOVE_DOWN";
const string EXAMINE = "EXAMINE";
const string SAVE = "SAVE";
const string LOAD = "LOAD";
const string CTRL_DOWN_EVT = "CTRL_DOWN_EVT";
const string CTRL_UP_EVT = "CTRL_UP_EVT";
const string PICK_UP_EVT = "PICK_UP_EVT";
const string DROP_EVT = "DROP_EVT";
const string NUM_KEY_DOWN = "NUM_KEY_DOWN";
const string SHOW_INVENTORY = "SHOW_INVENTORY";


class ControlFSMEvent {
public:
	ControlFSMEvent(string name, int keycode) : name(name), keycode(keycode) {};
	virtual ~ControlFSMEvent() {};
	const string name;
	bool isNumKey();
	int getNum();
	const int keycode;
};

class ControlFSMState {
public:
	ControlFSMState(string name) : name(name) {};
	virtual ~ControlFSMState();
	virtual string react(ControlFSMEvent&);
	const string name;
};

class StartState : public ControlFSMState {
public:
	StartState() : ControlFSMState(START_STATE) {};
	string react(ControlFSMEvent&);
};

class CtrlDownState : public ControlFSMState {
public:
	CtrlDownState() : ControlFSMState(CTRL_DOWN) {};
	string react(ControlFSMEvent&);
};

class PickUpState : public ControlFSMState {
public:
	PickUpState() : ControlFSMState(PICK_UP) {};
	string react(ControlFSMEvent&);
};

class DropState : public ControlFSMState {
public:
	DropState() : ControlFSMState(DROP) {};
	string react(ControlFSMEvent&);
};

typedef function<void(ControlFSMEvent&)> EventFunc;

class ControlFSM {
public:
	ControlFSM(string keymapFile);
	void registerAction(string stateName, string eventName, EventFunc action);
	void processEvent(SDL_Event& e);
private:
	shared_ptr<ControlFSMState> currentState;
	unordered_map<string, shared_ptr<ControlFSMState>> nameToState;
	unordered_map<string, EventFunc> stateEventToAction;
	KeyMap keymap;
};

#endif /* CONTROLFSM_H_ */
