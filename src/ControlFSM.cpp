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
	else if (evt.name == PICK_UP_EVT)
		return PICK_UP;
	else if (evt.name == DROP_EVT)
		return DROP;
	else
		return name;
}

string CtrlDownState::react(ControlFSMEvent& evt) {
	if (evt.name == CTRL_DOWN_EVT)
		return name;
	else
		return START_STATE;
}

bool ControlFSMEvent::isNumKey(){
	return (keycode >= '0' && keycode <= '9');
}

int ControlFSMEvent::getNum(){
	return keycode - '0';
}

string PickUpState::react(ControlFSMEvent& evt) {
	return START_STATE;
}

string DropState::react(ControlFSMEvent& evt) {
	return START_STATE;
}

ControlFSM::ControlFSM() {
	auto startState = make_shared<StartState>();
	nameToState.insert(make_pair(startState->name, startState));
	auto s = make_shared<CtrlDownState>();
	nameToState.insert(make_pair(s->name, s));
	auto p = make_shared<PickUpState>();
	nameToState.insert(make_pair(p->name, p));
	auto d = make_shared<DropState>();
	nameToState.insert(make_pair(d->name, d));
	currentState = startState;
}

void ControlFSM::registerAction(string stateName, string eventName, EventFunc action) {
	stateEventToAction.insert(make_pair(stateName + "#" + eventName, action));
}

void ControlFSM::processEvent(SDL_Event& e) {
	unique_ptr<ControlFSMEvent> event;
	if (e.type == SDL_KEYDOWN) {
		int sym = e.key.keysym.sym;
		switch (sym) {
		case SDLK_UP:
			event = make_unique<ControlFSMEvent>(MOVE_UP, sym);
			break;
		case SDLK_LEFT:
			event = make_unique<ControlFSMEvent>(MOVE_LEFT, sym);
			break;
		case SDLK_e:
			event = make_unique<ControlFSMEvent>(EXAMINE, sym);
			break;
		case SDLK_LCTRL:
		case SDLK_RCTRL:
			event = make_unique<ControlFSMEvent>(CTRL_DOWN_EVT, sym);
			break;
		case SDLK_s:
			event = make_unique<ControlFSMEvent>(SAVE, sym);
			break;
		case SDLK_p:
			event = make_unique<ControlFSMEvent>(PICK_UP_EVT, sym);
			break;
		case SDLK_d:
			event = make_unique<ControlFSMEvent>(DROP_EVT, sym);
			break;
		case SDLK_0:
		case SDLK_1:
		case SDLK_2:
			event = make_unique<ControlFSMEvent>(NUM_KEY_DOWN, sym);
			break;
		}
	}
	else if (e.type == SDL_KEYUP) {
		switch(e.key.keysym.sym) {
		case SDLK_LCTRL:
		case SDLK_RCTRL:
			event = make_unique<ControlFSMEvent>(CTRL_UP_EVT, e.key.keysym.sym);
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
