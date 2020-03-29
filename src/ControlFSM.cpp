/*
 * ControlFSM.cpp
 *
 *  Created on: Mar 29, 2020
 *      Author: jesse
 */

#include "ControlFSM.h"

ControlFSMState::~ControlFSMState(){

}

string ControlFSMState::react(ControlFSMEvent &) {
	return name;
}

string StartState::react(ControlFSMEvent & evt) {
	if (evt.name == CTRL_DOWN_EVT)
		return CTRL_DOWN;
	else
		return name;
}

string CtrlDownState::react(ControlFSMEvent& evt) {
	if (evt.name == CTRL_DOWN_EVT)
		return name;
	else
		return START_STATE;
}


ControlFSM::ControlFSM() {
	auto startState = make_shared<StartState>();
	nameToState.insert(make_pair(startState->name, startState));
	auto s = make_shared<CtrlDownState>();
	nameToState.insert(make_pair(s->name, s));
	currentState = startState;
}

void ControlFSM::registerAction(string stateName, string eventName, EventFunc action) {
	stateEventToAction.insert(make_pair(stateName + "#" + eventName, action));
}

void ControlFSM::processEvent(SDL_Event& e) {
	unique_ptr<ControlFSMEvent> event;
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
		case SDLK_UP:
			event = make_unique<ControlFSMEvent>(MOVE_UP);
			break;
		case SDLK_LEFT:
			event = make_unique<ControlFSMEvent>(MOVE_LEFT);
			break;
		case SDLK_e:
			event = make_unique<ControlFSMEvent>(EXAMINE);
			break;
		case SDLK_LCTRL:
		case SDLK_RCTRL:
			event = make_unique<ControlFSMEvent>(CTRL_DOWN_EVT);
			break;
		case SDLK_s:
			event = make_unique<ControlFSMEvent>(SAVE);
			break;
		}
	}
	else if (e.type == SDL_KEYUP) {
		switch(e.key.keysym.sym) {
		case SDLK_LCTRL:
		case SDLK_RCTRL:
			event = make_unique<ControlFSMEvent>(CTRL_UP_EVT);
			break;
		}
	 }
	if (event){
		if (stateEventToAction.count(currentState->name + "#" + event->name)){
			stateEventToAction[currentState->name + "#" + event->name](*event);
		}
		currentState = nameToState[currentState->react(*event)];
	}
}
