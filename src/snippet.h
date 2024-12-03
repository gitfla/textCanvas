//
//  particle.h
//  textCanvas
//
//  Created by F F on 28/11/2024.
//
#include "ofMain.h"
#include "particle.h"

#ifndef snippet_h
#define snippet_h

class snippet {
public:
	int fontSize;
	bool pulse;
	
	glm::vec2 startPosition;
	glm::vec3 color;
	vector<particle> particles;
	ofTrueTypeFont 	vagRounded;
	
	void update();
	void draw();
	void clear();
	
	snippet(string text, glm::vec2, int fontSize, int particleSize, int movementMode, bool rainbow, bool changingColor);
	~snippet();
};

#endif /* snippet_h */
