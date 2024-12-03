//
//  snippet.cpp
//  textCanvas
//
//  Created by F F on 01/12/2024.
//

#include "snippet.h"

// returns the minimum and maximum X and Y positions of the text displayed in paths
// uses this return format because we use the min and max X for the rainbow case.
vector<glm::vec2> getXYRanges(vector<ofPath> paths) {
	float min_x = std::numeric_limits<float>::min();
	float min_y = min_x;
	float max_x = -min_x;
	float max_y = -min_x;
	
	for (int i = 0; i < paths.size(); i++){
		vector <ofPolyline> polylines = paths[i].getOutline();
		
		for (int j = 0; j < polylines.size(); j++){
			for (int k = 0; k < polylines[j].size(); k+=1) {
				if (polylines[j][k][0] > max_x) {
					max_x = polylines[j][k][0];
				}
				if (polylines[j][k][0] < min_x) {
					min_x = polylines[j][k][0];
				}
				if (polylines[j][k][1] > max_y) {
					max_y = polylines[j][k][1];
				}
				if (polylines[j][k][1] < min_y) {
					min_y = polylines[j][k][1];
				}
			}
		}
	}
	return {glm::vec2(min_x, max_x), glm::vec2(min_y, max_y)};
}

// TODO: break each movement mode into different snippet class implementations
snippet::snippet(string text, glm::vec2 start, int fontSize, int particleSize, int movementMode, bool rainbow, bool changingColor) {
	startPosition = start;
	fontSize = fontSize;
	vagRounded.load("vag.ttf", fontSize, false, false, true, 0);
	
	// sets random color for the whole snippet
	ofColor c;
	c.set(ofRandom(255), ofRandom(255), ofRandom(255), 200);

	// get the string as paths
	bool vflip = true; // OF flips y coordinate in the default perspective,
	// should be false if using a camera for example
	bool filled = false; // or false for contours
	vector<ofPath> paths = vagRounded.getStringAsPoints(text, vflip, filled);
	
	ofPushMatrix();
	ofTranslate(startPosition[0],startPosition[1]);
	
	vector<glm::vec2> ranges = getXYRanges(paths);
	glm::vec2 center = glm::vec2((ranges[0][0] + ranges[0][1])/2, (ranges[1][0] + ranges[1][1])/2);
	
	for (int i = 0; i < paths.size(); i++){
		// for every character break it out to polylines
		vector <ofPolyline> polylines = paths[i].getOutline();
		cout << "polylines size: " << polylines.size() << endl;
		
		for (int j = 0; j < polylines.size(); j++){
			// tries to get last point (at 100%) as the previous point for the first one
			// TODO: deal with off-by-one
			ofPoint previousPoint = polylines[j].getPointAtPercent(1);

			
			for (int k = 0; k < polylines[j].size(); k+=5){         // draw every "fifth" point
				float percent = float(k)/polylines[j].size();
				ofPoint point = polylines[j].getPointAtPercent(percent);
				
				// movementMode == 0 , static
				float end_x = point[0];
				float end_y = point[1];
				
				if (movementMode == 1) { // pulsing
					end_x = point[0] + (point[0] - center[0]);
					end_y = point[1] + (point[1] - center[1]);
				}
				
				if (movementMode == 2) { // chain
					end_x = previousPoint[0];
					end_y = previousPoint[1];
				}
	
				// if rainbow is selected, hue depends on X value of particle
				if (rainbow) {
					float mappedHue = 200 * float(point[0] - ranges[0][0]) / (ranges[0][1] - ranges[0][0]);
					c.setHsb(mappedHue, 255, 255, 200);
				}
				particle newParticle(
									 glm::vec2(point[0], point[1]),
									 glm::vec2(end_x, end_y),
									 200,
									 movementMode == 1,
									 particleSize,
									 c,
									 changingColor);
				particles.push_back(newParticle);
				
				if (movementMode == 2) {
					previousPoint = point;
				}
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
