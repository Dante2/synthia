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
    
    // buffer size
    int bufferSize;
    
    // sample rate
    int sampleRate;
    

    
    // maxiClock object doesn't seem to exist in the OF version of Maxim :[
    // maxiClock myClock;
    // instead we'll create a counter with phasor
    
    // set up oscillators
    maxiOsc VCO1, VCO2, myCounter, LFO1;
    
    // for use with myCounter
    int currentCount;
    
    // control sound output from oscillators
    double VCO1out, LFO1out;
    
    // envs
    maxiEnv ADSR;
    
    // env output
    double ADSRout;
    
    // filter
    maxiFilter VCF1, VCF2;
    
    // control out put from filter
    double VCF1out, VCF2out;
    
    // volume control
    double ampOut;
    
    // mix it all together
    double mix;
    
    double wave;
		
    maxiSample mySample;
};
