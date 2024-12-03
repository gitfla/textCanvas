//
//  particle.h
//  textCanvas
//
//  Created by F F on 28/11/2024.
//
#include "ofMain.h"

#ifndef particle_h
#define particle_h

class particle {
public:
	// isRoundtrip refers to whether particle should also make the reverse path to initial position
	// changingColor refers to whether hue of particle should keep updating
	bool isRoundtrip, changingColor;
	
	// radius of particle's circle
	float size;
	glm::vec2 startPosition, currentPosition, endPosition, direction;
	
	// stepsInCycle refers to how many iterations before particle reaches endPosition
	int stepsInCycle, currentStep;
	ofColor color;
	
	void update();
	void draw();
	void clear();
	
	particle(glm::vec2 start, glm::vec2 end, int steps, bool roundtrip, int size, ofColor c, bool changingColor);
	
	~particle();
};

#endif /* particle_h */
