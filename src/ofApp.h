#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    // Audio output and input methods
    
        void audioOut(float * output, int bufferSize, int nChannels);
        void audioIn(float * input, int bufferSize, int nChannels);
    
    
    // stick you maximilian declarations below
    
    // set up oscillators
    maxiOsc mySine1;
    
    // control sound output from oscillators
    double VCO1out;
    
    // envs
    maxiEnv ADSR;
    
    // filter
    maxiFilter VCF;
    
    // control out put from filter
    double VCFout;
    
    // buffer size
    int	bufferSize;
    
    // sample rate
    int	sampleRate;
    
    double wave;
		
    maxiSample mySample;
};
