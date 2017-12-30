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
    

    
    // maxiClock object wasn't working but I solved it
    maxiClock myClock;
    
    // set up oscillators. Hardcoding number at VCO3 --> bad?
    maxiOsc VCO1, VCO2, VCO3[6], myCounter, LFO1, LFO2;
    
    // for use with myCounter
    int currentCount, voice;
    
    // for use with ADSR trigger if statement in clock
    double pitch[6];
    
    // control sound output from oscillators. Hardcoding number at VCO3out --> bad?
    double VCO1out, VCO2out, VCO3out[6], LFO1out, LFO2out;
    
    // envs
    maxiEnv ADSR[6];
    
    // env output
    double ADSRout[6];
    
    // filter
    maxiFilter VCF1, VCF2;
    
    // control out put from filter
    double VCF1out, VCF2out;
    
    // oscillator 3 mixed with env
    double VCO3env[6];
    
    // amplitude control oscillator 3
    double VCO3amp[6];
    
    // volume control
    double ampOut;
    
    // mix it all together
    double mix;
    
    double wave;
		
    maxiSample mySample;
};
