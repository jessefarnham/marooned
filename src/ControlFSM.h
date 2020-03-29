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

using namespace std;

const string START_STATE = "START";
const string CTRL_DOWN = "CTRL_DOWN";

const string MOVE_UP = "MOVE_UP";
const string MOVE_LEFT = "MOVE_LEFT";
const string EXAMINE = "EXAMINE";
const string SAVE = "SAVE";
const string CTRL_DOWN_EVT = "CTRL_DOWN_EVT";
const string CTRL_UP_EVT = "CTRL_UP_EVT";
const string NUM_KEY_DOWN = "NUM_KEY_DOWN";


class ControlFSMEvent {
public:
	ControlFSMEvent(string name) : name(name) {};
	virtual ~ControlFSMEvent() {};
	const string name;
};

class NumKeyDownEvent : public ControlFSMEvent {
public:
	NumKeyDownEvent(char keycode) : ControlFSMEvent(NUM_KEY_DOWN), num(keycode - '0') {};
	const int num;
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

typedef function<void(ControlFSMEvent&)> EventFunc;

class ControlFSM {
public:
	ControlFSM();
	void registerAction(string stateName, string eventName, EventFunc action);
	void processEvent(SDL_Event& e);
private:
	shared_ptr<ControlFSMState> currentState;
	unordered_map<string, shared_ptr<ControlFSMState>> nameToState;
	unordered_map<string, EventFunc> stateEventToAction;
};

#endif /* CONTROLFSM_H_ */
