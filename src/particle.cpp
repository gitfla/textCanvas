//
//  particle.cpp
//  textCanvas
//
//  Created by F F on 28/11/2024.
//

#include "particle.h"

particle::particle(glm::vec2 start, glm::vec2 end, int steps, bool roundtrip, int s, ofColor c, bool cColor) {
	isRoundtrip = roundtrip;
	currentPosition = start;
	startPosition = start;
	endPosition = end;
	stepsInCycle = steps;
	currentStep = 0;
	size = s;
	color = c;
	changingColor = cColor;
}

void particle::update() {
	// calculate current direction
	float dir_x = float(endPosition[0] - startPosition[0])/stepsInCycle;
	float dir_y = float(endPosition[1] - startPosition[1])/stepsInCycle;
	
	// if it's supposed to make the reverse path, check if halfway and go in opposite direction
	if (isRoundtrip && (currentStep > (stepsInCycle/2))) {
		dir_x = -1 * dir_x;
		dir_y = -1 * dir_y;
	}
	direction = glm::vec2(dir_x, dir_y);
	
	// update current state
	currentPosition += direction;
	currentStep++;
	if (changingColor) {
		color.setHue(color.getHue()+1);
	}
	
	if (currentStep <= stepsInCycle) {
		return;
	}
	
	// end of cycle, restart state appropriately
	currentStep = 0;
	currentPosition = startPosition;
}

void particle::draw() {
	ofSetColor(color);
	ofDrawCircle(currentPosition[0], currentPosition[1], size);
}

void particle::clear() {
}

particle::~particle() {	
}
