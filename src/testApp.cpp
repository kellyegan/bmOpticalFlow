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
    videoPixels = video.getPixels();
  }
}

//--------------------------------------------------------------
void testApp::draw(){
  ofPoint currentVel;
  
  // video.draw(0, 0);
  for(int y = 0; y < video.height; y++) {
    for (int x = 0; x < video.width; x++) {
      currentVel = flow.getVel(x, y);
      ofSetColor(videoPixels[((video.width * y) + x) * 3], 
                 videoPixels[((video.width * y) + x) * 3 + 1], 
                 videoPixels[((video.width * y) + x) * 3 + 2]);
      ofLine(x, y, x + currentVel.x, y + currentVel.y);
    }
  }
  ofSetColor(255, 255, 255);
  flow.draw(0, 0);
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
