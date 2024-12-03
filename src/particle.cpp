//
//  particle.cpp
//  textCanvas
//
//  Created by F F on 28/11/2024.
//

#include "particle.h"

particle::particle(glm::vec2 start, glm::vec2 letterCenter, glm::vec2 wordCenter, int hue) {
	currentStep = 0;
	stepsInCycle = 200;
	currentPosition = start;
	startPosition = start;
	float dir_x;
	float dir_y;
	float dist_x = letterCenter[0] - wordCenter[0];
	float dist_y = letterCenter[1] - wordCenter[1];
	dir_x = (start[0] - letterCenter[0])/400 + dist_x/400;
	dir_y = (start[1] - letterCenter[1])/400 + dist_y/400;

	direction = glm::vec2(dir_x, dir_y);
	size = 2;
	color.setHsb(hue, 255, 255, 200);
}


particle::particle(glm::vec2 start, glm::vec2 end, int steps, int hue, bool roundtrip) {
	currentPosition = start;
	startPosition = start;
	endPosition = end;
	stepsInCycle = steps;
	currentStep = 0;
	roundtrip = roundtrip;
	size = 2;
	color.setHsb(hue, 255, 255, 200);
}


void particle::update() {
	color.setHue(color.getHue()+1);
 
	float dir_x = float(endPosition[0] - startPosition[0])/stepsInCycle;
	float dir_y = float(endPosition[1] - startPosition[1])/stepsInCycle;
	direction = glm::vec2(dir_x, dir_y);
	
	currentPosition += direction;
	currentStep++;
	
	if (currentStep <= stepsInCycle) {
		return;
	}
	
	// end of cycle, restart appropriately
	currentStep = 0;
	
	if (roundtrip) {
		direction = -direction;
	} else {
		currentPosition = startPosition;
	}
}

void particle::draw() {
	ofSetColor(color);
	ofDrawCircle(currentPosition[0], currentPosition[1], size);
}

particle::~particle() {	
}
