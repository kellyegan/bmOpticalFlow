#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
  video.loadMovie("westminster_st.mov");
  //video.loadMovie("fingers.mov");

  video.play();
  video.setPosition(0.11);
  video.setPaused(true);

  flow.setup(video.width, video.height);
  
  ofNoFill();
  ofSetColor(255);  
}

//--------------------------------------------------------------
void testApp::update(){
  video.idleMovie();
  if( video.isFrameNew() ) {
    flow.update(video.getPixels(), video.width, video.height, OF_IMAGE_COLOR);
  }
}

//--------------------------------------------------------------
void testApp::draw(){
  video.draw(0, 0);
  flow.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
  video.nextFrame();
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
