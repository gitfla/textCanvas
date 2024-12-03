//
//  snippet.cpp
//  textCanvas
//
//  Created by F F on 01/12/2024.
//

#include "snippet.h"

snippet::snippet(string text, glm::vec2 start, ofTrueTypeFont vagRounded, int fontSize, glm::vec3 color) {
	startPosition = start;
	fontSize = fontSize;
	
	vagRounded.load("vag.ttf", fontSize, false, false, true, 0);

	// get the string as paths
	bool vflip = true; // OF flips y coordinate in the default perspective,
	// should be false if using a camera for example
	bool filled = false; // or false for contours
	vector < ofPath > paths = vagRounded.getStringAsPoints(text, vflip, filled);
	
	cout << "paths: " << paths.size() << endl;
	ofPushMatrix();
	ofTranslate(startPosition[0],startPosition[1]);
	
	float min_x = std::numeric_limits<float>::min();
	float min_y = min_x;
	float max_x = -min_x;
	float max_y = -min_x;
	
	for (int i = 0; i < paths.size(); i++){
		vector <ofPolyline> polylines = paths[i].getOutline();
		
		for (int j = 0; j < polylines.size(); j++){
			for (int k = 0; k < polylines[j].size(); k+=1){
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
	float center_word_x = (min_x + max_x) /2;
	float center_word_y = (min_y + max_y) / 2;
	
	
	for (int i = 0; i < paths.size(); i++){
		
		// for every character break it out to polylines
		
		vector <ofPolyline> polylines = paths[i].getOutline();
		cout << "polylines size: " << polylines.size() << endl;
		
		// for every polyline, draw every fifth point
		
		for (int j = 0; j < polylines.size(); j++){
			
			float sum_x = 0;
			float sum_y = 0;
			for (int k = 0; k < polylines[j].size(); k+=1){
				sum_x += polylines[j][k][0];
				sum_y += polylines[j][k][1];
			}
			float center_x = sum_x / polylines[j].size();
			float center_y = sum_y / polylines[j].size();
			for (int k = 0; k < polylines[j].size(); k+=5){         // draw every "fifth" point
				//cout << "polylines[j][k]: " <<  polylines[j][k] << endl;
				//ofDrawCircle( polylines[j][k], 2);
				
				float percent = float(k)/polylines[j].size();
				
				ofPoint point = polylines[j].getPointAtPercent(percent);
				glm::vec3 polyline = polylines[j][k];
				
				
				float mappedHue = 200 * float(point[0] - min_x) / (max_x - min_x);
				particle newParticle(
					glm::vec2(point[0], point[1]),
					glm::vec2(center_x, center_y),
					glm::vec2(center_word_x, center_word_y),
					mappedHue);
				particles.push_back(newParticle);
				//cout << "pushing back new particle" << endl;
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

snippet::~snippet() {
}
