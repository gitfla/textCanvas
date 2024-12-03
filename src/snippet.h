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
	
	glm::vec2 startPosition;
	glm::vec3 color;
	vector<particle> particles;
	
	void update();
	void draw();
	
	snippet(string text, glm::vec2, ofTrueTypeFont vagRounded, int fontSize, glm::vec3);
	
	~snippet();
};

#endif /* snippet_h */
