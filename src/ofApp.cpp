#include "ofApp.h"
#include "particle.h"
#include "snippet.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);

	gui.setup("","", 20, 100);
	gui.add(fontSize.setup("font size", 100, 30, 300));
	//gui.add(floatSlider.setup("float slider", 30.0, 0.0, 300.0));
	
	gui.add(toggle.setup("toggle", false));
	//gui.add(button.setup("button"));
		//gui.add(intField.setup("int field", 100, 0, 100));
	//gui.add(floatField.setup("float field", 100.0, 0.0, 100.0));
	gui.add(textField.setup("text field", "text"));
	
	
	gui.add(vec3Slider.setup("text color", ofVec3f(100,1500,90), ofVec3f(0,0,0), ofVec3f(255,255,255)));
	
	message = "start";
}

//--------------------------------------------------------------
void ofApp::update(){
	for (int i=0; i<snippets.size();++i) {
		snippets[i].update();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(vec3Slider->x, vec3Slider->y, vec3Slider->z);
	//ofDrawCircle(ofGetWidth()/2, ofGetHeight() / 2, 128);
	//ofSetCircleResolution(fontSize);

	gui.draw();
	for (int i=0; i<snippets.size();++i) {
		snippets[i].draw();
	}
	
	ofSetColor(184,180,176);
	string outString = "-- Type snippet to add to screen --";
	outString += "\n" + message;
	outString += "\n------------------------------";
	ofDrawBitmapString(outString, 20, 40);
}

//--------------------------------------------------------------
void ofApp::exit(){
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
	if( key == OF_KEY_DEL || key == 8) {
		if( message.length() > 0 ) {
			message.pop_back();
		}
	} else if( key == OF_KEY_RETURN || key == 13 ) {
		message += "\n";
	} else if( key == OF_KEY_UP ) {
	} else if( key == OF_KEY_DOWN ) {
	} else if( key < 300 ) {
		unsigned char letter = (unsigned char)key;
		message += (letter);
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	snippet newSnippet(message, glm::vec2(x, y), vagRounded, fontSize, vec3Slider);
	snippets.push_back(newSnippet);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
