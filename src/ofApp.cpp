/* additive synthesis with filters and oscillators  */

#include "ofApp.h"

void ofApp::setup(){
    
    ofSetFrameRate(60);
    
    // set sampling Rate
    sampleRate = 44100;
    
    // set buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method
    bufferSize = 512;

    // calling the calling the setup method in maximilian settings containing samplerate and buffer size
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    mySample.load(ofToDataPath("sound.wav"));
    
    ofBackground(0,0,0);

    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4);
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
   
    
    for (int i = 0; i < bufferSize; i++){
        
        // LFO
        LFO1out = LFO1.sinewave(5) * 2;
        LFO2out = LFO2.sinewave(0.1) * 1500;
    
        int myArray[10] = {100, 200, 300, 400, 500, 600, 500, 400, 300, 200};
        
        // clock device using phasor
        currentCount = myCounter.phasor(1, 1, 9);
        
        //--- oscillators ---//
        
        // worth playing around with high pass / band pass / band reject
        // square wave
        VCO1out = VCO1.square(2000 * currentCount);
        
        // LFO controlled oscillator --> vibrato
        VCO2out = VCO2.sawn(200 + LFO1out);
        
        // filters
        // low pass - portamento
        VCF1out = VCO1.square(VCF1.lopass(myArray[currentCount], 0.005));
        
        // low res - vibrato
        VCF2out = VCF2.lores(VCO2out, 2000 + LFO2out, 20);
        
        // amplitude control on raw oscillator and filter
        double VCO1amp = VCO1out * 0.05;
        double VCF1amp = VCF1out * 0.05;
        double VCF2amp = VCF2out * 0.05;
        double VCO2amp = VCO2out * 0.05;
        
        // mixer
        mix = VCO1amp + VCF1amp + VCF2amp + VCO2amp;
        
        output[i * nChannels] = mix;
        output[i * nChannels + 1] = mix;
        
    }
}
