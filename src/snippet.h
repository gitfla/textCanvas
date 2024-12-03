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

// represents how the particles in the snippet move
enum movementMode {
	STATIC = 0,
	PULSING = 1,
	CHAIN = 2
};

class snippet {
public:
	int fontSize;
	movementMode mode;
	glm::vec2 startPosition;
	vector<particle> particles;
	ofTrueTypeFont 	vagRounded;
	
	void update();
	void draw();
	void clear();
	
	snippet(string text, glm::vec2, int fontSize, int particleSize, movementMode movementMode, bool rainbow, bool changingColor);
	~snippet();
};

#endif /* snippet_h */
