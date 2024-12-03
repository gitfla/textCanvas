//
//  particle.cpp
//  textCanvas
//
//  Created by F F on 28/11/2024.
//

#include "particle.h"

particle::particle(glm::vec2 start, glm::vec2 letterCenter, glm::vec2 wordCenter, int hue) {
	steps = 0;
	currentPosition = start;
	float dir_x;
	float dir_y;
	float dist_x = letterCenter[0] - wordCenter[0];
	float dist_y = letterCenter[1] - wordCenter[1];
	dir_x = (start[0] - letterCenter[0])/500 + dist_x/500;
	dir_y = (start[1] - letterCenter[1])/500 + dist_y/500;

	direction = glm::vec2(dir_x, dir_y);
	size = 2;
	color.setHsb(hue, 255, 255, 200);
}


void particle::update() {
	currentPosition += direction;
	steps++;
	if (steps > 200) {
		direction = -direction;
		steps = 0;
	}
	color.setHue(color.getHue()+1);
}

void particle::draw() {
	ofSetColor(color);
	ofDrawCircle(currentPosition[0], currentPosition[1], size);
}

particle::~particle() {	
}
