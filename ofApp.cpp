#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetLineWidth(2);
	ofEnableDepthTest();
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);

	this->font.loadFont("fonts/msgothic.ttc", 40, true, true, true);
	this->word = "TWIST ";
}

//--------------------------------------------------------------
void ofApp::update() {


}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5 + glm::vec2(0, 20));

	ofSeedRandom(39);
	int word_index = 0;
	for (int x = -500; x <= 450; x += 50) {

		for (int y = -400; y <= 450; y += 50) {

			auto location = glm::vec3(x, y, 100);
			int word_index = (word_index + 1) % this->word.size();

			ofPath chara_path = this->font.getCharacterAsPoints(this->word[word_index], true, false);
			vector<ofPolyline> outline = chara_path.getOutline();
			
			ofFill();
			ofSetColor(0);
			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				ofNextContour(true);

				outline[outline_index] = outline[outline_index].getResampledByCount(100);
				auto vertices = outline[outline_index].getVertices();
				for (auto& vertex : vertices) {

					auto rotate_deg = ofMap(ofNoise(location.x, (location.y + vertex.y) * 0.005 + ofGetFrameNum() * 0.01), 0, 1, -180, 180);
					auto rotation = glm::rotate(glm::mat4(), rotate_deg * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
					auto v = location + glm::vec4(vertex + glm::vec2(-20 , 0), 0) * rotation;

					ofVertex(v);
				}
			}
			ofEndShape(true);

			ofNoFill();
			ofSetColor(255);
			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				ofNextContour(true);

				outline[outline_index] = outline[outline_index].getResampledByCount(100);
				auto vertices = outline[outline_index].getVertices();
				for (auto& vertex : vertices) {

					auto rotate_deg = ofMap(ofNoise(location.x, (location.y + vertex.y) * 0.005 + ofGetFrameNum() * 0.01), 0, 1, -180, 180);
					auto rotation = glm::rotate(glm::mat4(), rotate_deg * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
					auto v = location + glm::vec4(vertex + glm::vec2(-20 , 0), 0) * rotation;

					ofVertex(v);
				}
			}
			ofEndShape(true);
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}