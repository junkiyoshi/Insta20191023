#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {
	
	ofSeedRandom(39);

	this->mesh.clear();

	for (auto i = 0; i < 700; i++) {

		auto location = glm::vec3(
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.0005), 0, 1, -300, 300),
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.0005), 0, 1, -300, 300),
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.0005), 0, 1, -300, 300));

		location = glm::normalize(location) * 300;

		this->mesh.addVertex(location);
	}
	
	for (int i = 0; i < this->mesh.getVertices().size(); i++) {

		auto location = this->mesh.getVertices()[i];
		vector<int> near_index_list;
		for (int k = 0; k < this->mesh.getVertices().size(); k++) {

			auto other = this->mesh.getVertices()[k];
			auto distance = glm::distance(location, other);
			if (distance < 40) {

				near_index_list.push_back(k);
			}
		}

		if (near_index_list.size() >= 3) {

			for (int k = 0; k < near_index_list.size() - 2; k++) {

				this->mesh.addIndex(near_index_list[k]);
				this->mesh.addIndex(near_index_list[k + 1]);
				this->mesh.addIndex(near_index_list[k + 2]);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.25);
	ofRotateX(ofGetFrameNum() * 0.125);
	
	ofSetColor(255);
	for (auto& location : this->mesh.getVertices()) {

		ofDrawSphere(location, 2);
	}
	this->mesh.drawWireframe();

	ofSetColor(255, 64);
	this->mesh.drawFaces();
	
	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}