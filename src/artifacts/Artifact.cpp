/*
 * Artifact.cpp
 *
 *  Created on: Mar 25, 2020
 *      Author: jesse
 */

#include "Artifact.h"

Artifact::Artifact() {
	// TODO Auto-generated constructor stub

}

std::string Artifact::getTextureName(){
	return "artifact";
}

bool Artifact::getStandable(){
	return true;
}

int Artifact::getDrawPriority(){
	return 1; //artifacts always draw with higher priority than terrain
}

std::string Artifact::getDescription(){
	return "A mysterious artifact from an unknown alien race.";
}

Artifact::~Artifact() {
	// TODO Auto-generated destructor stub
}

std::unique_ptr<Artifact> toArtifact(std::unique_ptr<GameItem> gi){
	Artifact* tmpArtifact = dynamic_cast<Artifact*>(gi.get());
	std::unique_ptr<Artifact> uniqueArtifact;
	if(tmpArtifact != nullptr)
	{
	    gi.release();
	    uniqueArtifact.reset(tmpArtifact);
	}
	return uniqueArtifact;
}


