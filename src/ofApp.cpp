#include "ofApp.h"
#include "particle.h"
#include "snippet.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);

	gui.setup("","", 20, 100);
	gui.add(fontSize.setup("font size", 100, 30, 300));
	gui.add(particleSize.setup("particle size", 2, 1, 5));
	gui.add(movementMode.setup("movement mode", 1, 0, 2));
	gui.add(movementHeader.setup("", "movement modes"));
	gui.add(movementZero.setup("0", "static"));
	gui.add(movementOne.setup("1", "pulsing"));
	gui.add(movementTwo.setup("2", "chain"));
	
	gui.add(rainbow.setup("RAINBOW!", false));
	gui.add(changingColor.setup("changing color", true));

	gui.add(clearHeader.setup("", "click to clear screen"));
	gui.add(clear.setup("clear"));
	
	message = "start";
}

//--------------------------------------------------------------
void ofApp::update(){
	if (clear) {
		for (int i=0; i<snippets.size();++i) {
			snippets[i].clear();
			snippets.clear();
		}
	}
	for (int i=0; i<snippets.size();++i) {
		snippets[i].update();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(184,180,176);
	string outString = "-- Type message then click on screen --";
	outString += "\n" + message;
	ofDrawBitmapString(outString, 20, 40);
	
	gui.draw();
	
	for (int i=0; i<snippets.size();++i) {
		snippets[i].draw();
	}

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
		
		// limits snippet length
		// TODO: add visual feedback
		if (message.size() >= 15) {
			return;
		}
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
	snippet newSnippet(message, glm::vec2(x, y), fontSize, particleSize, movementMode, rainbow, changingColor);
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
