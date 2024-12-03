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
	bool isRoundtrip, changingColor;
	float size;
	glm::vec2 startPosition, currentPosition, endPosition, direction;
	int stepsInCycle, currentStep;
	ofColor color;
	
	void update();
	void draw();
	void clear();
	
	particle(glm::vec2 start, glm::vec2 end, int steps, bool roundtrip, int size, ofColor c, bool changingColor);
	
	~particle();
};

#endif /* particle_h */
