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

ControlFSM::ControlFSM(string keymapFile) : keymap(keymapFile){
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
	string eventName = "";
	char sym = 0;
	if (e.type == SDL_KEYDOWN) {
		sym = e.key.keysym.sym;
		eventName = keymap.getEventName(sym);
	}
	else if (e.type == SDL_KEYUP) {
		sym = e.key.keysym.sym;
		if (sym == SDLK_LCTRL || sym == SDLK_RCTRL){
			eventName = CTRL_UP_EVT;
		}
	 }
	if (eventName.length()){
		unique_ptr<ControlFSMEvent> event = make_unique<ControlFSMEvent>(eventName, sym);
		string stateEventHash = currentState->name + "#" + event->name;
		if (stateEventToAction.count(stateEventHash)){
			stateEventToAction[stateEventHash](*event);
		}
		currentState = nameToState[currentState->react(*event)];
	}
}
