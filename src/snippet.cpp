//
//  snippet.cpp
//  textCanvas
//
//  Created by F F on 01/12/2024.
//

#include "snippet.h"

// returns the minimum and maximum X and Y positions of the text displayed
// uses this return format because we use the min and max X to play with colors later on
vector<glm::vec2> getXYRanges(vector<ofPath> paths) {
	float minX = std::numeric_limits<float>::min();
	float minY = minX;
	float maxX = -minX;
	float maxY = -minX;
	
	for (int i = 0; i < paths.size(); i++){
		vector <ofPolyline> polylines = paths[i].getOutline();
		
		for (int j = 0; j < polylines.size(); j++){
			for (int k = 0; k < polylines[j].size(); k++) {
				if (polylines[j][k][0] > maxX) {
					maxX = polylines[j][k][0];
				}
				if (polylines[j][k][0] < minX) {
					minX = polylines[j][k][0];
				}
				if (polylines[j][k][1] > maxY) {
					maxY = polylines[j][k][1];
				}
				if (polylines[j][k][1] < minY) {
					minY = polylines[j][k][1];
				}
			}
		}
	}
	return {glm::vec2(minX, maxX), glm::vec2(minY, maxY)};
}

// TODO: break each movement mode into different snippet class implementations
snippet::snippet(string text, glm::vec2 start, int fontSize, int particleSize, movementMode movementMode, bool rainbow, bool changingColor) {
	mode = movementMode;
	startPosition = start;
	fontSize = fontSize;
	vagRounded.load("vag.ttf", fontSize, false, false, true, 0);
	
	// set random color for the whole snippet
	ofColor c;
	c.set(ofRandom(255), ofRandom(255), ofRandom(255), 200);

	// get snippet as paths
	bool vflip = true; // OF flips y coordinate in the default perspective,
	// should be false if using a camera for example
	bool filled = false; // or false for contours
	vector<ofPath> paths = vagRounded.getStringAsPoints(text, vflip, filled);
	
	// translate coordinates to screen
	ofPushMatrix();
	ofTranslate(startPosition[0],startPosition[1]);
	
	vector<glm::vec2> ranges = getXYRanges(paths);
	float centerX = (ranges[0][0] + ranges[0][1])/2;
	float centerY = (ranges[1][0] + ranges[1][1])/2;
	glm::vec2 center = glm::vec2(centerX, centerY);
	
	for (int i = 0; i < paths.size(); i++){
		// for every character break it out to polylines
		// however, the polylines skip straight lines in characters, creating gaps
		// therefore, we need to resample the points in accordance to percentage
		// ensuring that the particles outline entire character
		vector <ofPolyline> polylines = paths[i].getOutline();
		cout << "polylines size: " << polylines.size() << endl;
		
		for (int j = 0; j < polylines.size(); j++){
			// gets last point (at 100%) as the previous point for the first iteration,
			// then update normally in each iteration
			// TODO: deal with off-by-one
			ofPoint previousPoint = polylines[j].getPointAtPercent(1);
			
			for (int k = 0; k < polylines[j].size(); k+=5) {         // draw every "fifth" point
				float percent = float(k)/polylines[j].size();
				ofPoint point = polylines[j].getPointAtPercent(percent);
				
				float endX, endY;
				switch(movementMode) {
					case STATIC:
						// particle's end point is the same as starting point, no movement
						endX = point[0];
						endY = point[1];
						break;
					case PULSING:
						// particle's end point is based on starting point and center of snippet, so it can grow the char
						// (originally took into account center of each character, but it cancelled itself out in math)
						endX = point[0] + (point[0] - center[0]);
						endY = point[1] + (point[1] - center[1]);
						break;
					case CHAIN:
						// particle's end point is the point before itself in the path
						endX = previousPoint[0];
						endY = previousPoint[1];
				}
	
				// if rainbow is selected, particle's hue depends on X value of particle
				if (rainbow) {
					float mappedHue = 200 * float(point[0] - ranges[0][0]) / (ranges[0][1] - ranges[0][0]);
					c.setHsb(mappedHue, 255, 255, 200);
				}
				
				// create particle
				particle newParticle(
									 glm::vec2(point[0], point[1]),
									 glm::vec2(endX, endY),
									 200,
									 movementMode == 1,
									 particleSize,
									 c,
									 changingColor);
				particles.push_back(newParticle);
				previousPoint = point;
			}
		}
	}
	ofPopMatrix();
}

void snippet::update() {
	for (int i=0; i<particles.size();++i) {
		particles[i].update();
	}
}

void snippet::draw() {
	ofPushMatrix();
	ofTranslate(startPosition[0], startPosition[1]);
	for (int i=0; i<particles.size();++i) {
		particles[i].draw();
	}
	ofPopMatrix();
}

void snippet::clear() {
	for (int i=0; i<particles.size();++i) {
		particles[i].clear();
	}
}

snippet::~snippet() {
}
