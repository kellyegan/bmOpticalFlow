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
  blockSize = cvSize(5, 5);
  shiftSize = cvSize(1, 1);
  maxRange = cvSize(5, 5);
  
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

void ofxOpticalFlowBM :: setup( int width, int height ) {
  scalSize = cvSize(width, height);
  fullSize = cvSize(width, height);
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
  
  //colrImgSml.setFromPixels( pixels, width, height );
  //greyImgSml.setFromColorImage( colrImgSml );
  
  
  cvCalcOpticalFlowBM( greyImgPrv.getCvImage(), //Previous image (CvArr *)
                       greyImgSml.getCvImage(), //Current image (CvArr *)
                       blockSize,    //Block size (CvSize)
                       shiftSize,    //Shift size (CvSize)
                       maxRange,     //Max range (CvSize)
                       0,            //Use previous velocity as starting point if not zero (int)
                       opFlowVelX,   //X Velocity (CvArr) 
                       opFlowVelY    //Y Velocity (CvArr) 
  );
  
  //greyImgPrv = greyImgSml;
}
