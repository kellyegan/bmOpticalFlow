/*
 *  ofxOpticalFlowBM.h
 *  bmOpticalFlow
 *
 *  Created by Kelly Egan on 4/15/12.
 *
 */

#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

class ofxOpticalFlowBM {
  public:
    ofxOpticalFlowBM();
    ~ofxOpticalFlowBM();
  
    void reset		();
    void destroy	();
  
    void setup		( int width, int height );
    void update		( ofImage& source );
  
};