#include "testApp.h"

void testApp::setUpKinects(){

    int i = 0;
    kinects[i].init(false, false);
	kinects[i].open(kserials[i]); // open by serial number
}

void testApp::setUpKinectClouds(){

    for(int i = 0; i<nK; i++){
        kinectClouds[i].init(i, &kinects[i]);
    }
}


void testApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);

    ofSetVerticalSync(true);

    gui.setup();
	gui.add(autorotation.set("auto rotation",false));

    kserials[0] = "A00364911617035A"; //, "x", "y"};
    kColors[0] = ofColor(255,0,0); kColors[1] = ofColor(0,255,0); kColors[2] = ofColor(255,255,0);
    kHeights[0] = kHeights[1] = kHeights[2] = 740;

    triangle_radius = 2100;

    ofBackground(0);
    ofEnableAlphaBlending();

    cam_distance = 3000;
    camera.setFarClip(10000);

    setUpKinects();
    setUpKinectClouds();
}

//--------------------------------------------------------------

void testApp::updateCamera(){

    float speed = 20.0;

    if (autorotation){
        cam_location = ofxVec3f(    sin(TWO_PI*ofGetElapsedTimef()/speed) * cam_distance,
                                    cos(TWO_PI*ofGetElapsedTimef()/speed) * cam_distance,
                                    1000); // z elevation
    }
    else{
        cam_location = ofxVec3f(    sin(4.0*PI*mouseX/ofGetWidth())*cos(1.0*PI*mouseY/ofGetHeight() - PI/2.0) * cam_distance,
                                    cos(4.0*PI*mouseX/ofGetWidth())*cos(1.0*PI*mouseY/ofGetHeight() - PI/2.0) * cam_distance,
                                    sin(1.0*PI*mouseY/ofGetHeight() - PI/2.0) * cam_distance); // z elevation
    }

    camera.resetTransform();
    camera.setPosition(cam_location);
    camera.lookAt(ofVec3f(0,0,1000), ofVec3f(0,0,1));
}

void testApp::updateKinects(){

    int i = 0;
    //for (int i=0; i<nK; i++){
        kinects[i].update();

        if(kinects[i].isFrameNew()){
            kinectClouds[i].meshCloud();
        }
    //}
}

void testApp::updateKinectClouds(){

    for(int i = 0; i<nK; i++){
        kinectClouds[i].update();
    }
}

void testApp::update(){

    updateCamera();

    updateKinects();

	updateKinectClouds();
}

//--------------------------------------------------------------

void testApp::drawKinectClouds(){

    for(int i = 0; i<nK; i++){
        ofSetColor(kColors[i]);
        kinectClouds[i].draw();
    }
}

void testApp::drawOrigin(){

    ofPushStyle();

    ofNoFill();

    ofDrawAxis(200);

    ofSetColor(ofColor(255, 255, 255));
    ofSetCircleResolution(6);
    ofCircle(0,0,250);

    /// TODO draw vertices according to corrected kinect position
    ofSetCircleResolution(3);
    ofCircle(0,0,2100);

    ofPopStyle();
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255);

    gui.draw();

    ofDrawBitmapString(ofToString(ofGetFrameRate()),2,10);
    ofDrawBitmapString(ofToString(ofGetElapsedTimef()),2,20);

	kinects[0].drawDepth(2,40,640/4,480/4);

    glEnable(GL_DEPTH_TEST);
	camera.begin();

        drawOrigin();

        glEnable(GL_DEPTH_TEST);
        drawKinectClouds();
        glDisable(GL_DEPTH_TEST);

    camera.end();
	glDisable(GL_DEPTH_TEST);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    switch (key){
        case 's':
            mesh.save(ofGetTimestampString()+".ply");
            break;
        case 'r':
            autorotation = !autorotation;
            break;

        case '+':
            cam_distance += 100;
            break;
        case '-':
            cam_distance -= 100;
            break;
    }

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}

//--------------------------------------------------------------

