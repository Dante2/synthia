#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
        void audioOut(float * output, int bufferSize, int nChannels);
    
    // buffer size
    int bufferSize;
    
    // sample rate
    int sampleRate;

    // set up oscillators
    maxiOsc VCO1, VCO2, myCounter, LFO1, LFO2;
    
    // for use with myCounter
    int currentCount;
    
    // control sound output from oscillators
    double VCO1out, VCO2out, LFO1out, LFO2out;
    
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
