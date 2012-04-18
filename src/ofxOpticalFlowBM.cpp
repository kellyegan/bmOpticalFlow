/*
 *  ofxOpticalFlowBM.cpp
 *  bmOpticalFlow
 *
 *  Created by Kelly Egan on 4/15/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxOpticalFlowBM.h"


ofxOpticalFlowBM :: ofxOpticalFlowBM() {
  blockSize = cvSize(20, 20);    //Size of block to compare
  shiftSize = cvSize(10, 10);    //Increment to look for pixels
  maxRange = cvSize(10, 10);     //Pixels around block to look... search area = (blockSize + 2 * maxRange)
  
  initialized = false;
}

ofxOpticalFlowBM :: ~ofxOpticalFlowBM() {
	destroy();
}

void ofxOpticalFlowBM :: reset() {
  colrImgLrg.set( 0 );
  colrImgSml.set( 0 );
  greyImgLrg.set( 0 );
  greyImgSml.set( 0 );
  greyImgPrv.set( 0 );
  
  cvSetZero( opFlowVelX );
  cvSetZero( opFlowVelY );
}

void ofxOpticalFlowBM :: destroy() {
  colrImgLrg.clear();
	colrImgSml.clear();
	greyImgLrg.clear();
	greyImgSml.clear();
	greyImgPrv.clear();
	
	cvReleaseImage( &opFlowVelX );
	cvReleaseImage( &opFlowVelY );
}

void ofxOpticalFlowBM :: setup( int w, int h ) {
  scalSize = cvSize(w, h);
  fullSize = cvSize(w, h);
  flowSize = cvSize(floor( (scalSize.width - blockSize.width) / shiftSize.width),
                    floor( (scalSize.height - blockSize.height) / shiftSize.height )
  );

  
  if( initialized )
		destroy();
	
	colrImgLrg.allocate( fullSize.width, fullSize.height );
	colrImgSml.allocate( scalSize.width, scalSize.height );
	greyImgLrg.allocate( fullSize.width, fullSize.height );
	greyImgSml.allocate( scalSize.width, scalSize.height );
	greyImgPrv.allocate( scalSize.width, scalSize.height );
	
	opFlowVelX = cvCreateImage( flowSize, IPL_DEPTH_32F, 1 );
	opFlowVelY = cvCreateImage( flowSize, IPL_DEPTH_32F, 1 );
	
	reset();
	
	initialized = true;
}

void ofxOpticalFlowBM :: update( unsigned char* pixels, int width, int height, int imageType ) {
  
  colrImgSml.setFromPixels( pixels, width, height );
  greyImgSml.setFromColorImage( colrImgSml );
  
  
  cvCalcOpticalFlowBM( greyImgPrv.getCvImage(), //Previous image (CvArr *)
                       greyImgSml.getCvImage(), //Current image (CvArr *)
                       blockSize,    //Block size (CvSize)
                       shiftSize,    //Shift size (CvSize)
                       maxRange,     //Max range (CvSize)
                       0,            //Use previous velocity as starting point if not zero (int)
                       opFlowVelX,   //X Velocity (CvArr) 
                       opFlowVelY    //Y Velocity (CvArr) 
  );
  
  greyImgPrv = greyImgSml;
}

ofPoint ofxOpticalFlowBM :: getVel( int x, int y) {
  ofPoint p;
  p.x = cvGetReal2D(opFlowVelX, y, x);   //NOTE: y then x ... annoying
  p.y = cvGetReal2D(opFlowVelY, y, x);   //NOTE: y then x ... annoying
  return p;
}

void ofxOpticalFlowBM :: draw() {
  for( int y = 0; y < flowSize.height; y++) {
    for (int x = 0; x < flowSize.width; x++) {
      ofPoint vel = getVel(x, y);
      //ofLine(x, y, x + vel.x, y + vel.y);
      ofLine(x * shiftSize.width, y * shiftSize.height, x * shiftSize.width + vel.x, y * shiftSize.height + vel.y);
    }
  }
}
