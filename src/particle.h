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
	float size;
	glm::vec2 currentPosition, direction;
	int steps;
	ofColor color;
	
	void update();
	void draw();
	
	particle(glm::vec2 start, glm::vec2 letterCenter, glm::vec2 wordCenter, int hue);
	
	~particle();
};

#endif /* particle_h */
