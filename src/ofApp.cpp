#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    
    myClock.setTicksPerBeat(2);
    myClock.setTempo(60);
    
    sampleRate = 44100;
    
    bufferSize = 512;

    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
 for (int i = 0; i < 6; i++) {
    
    // apply ADSR values accordingly
    ADSR[i].setAttack(200);
    ADSR[i].setDecay(200);
    ADSR[i].setSustain(50);
    ADSR[i].setRelease(3000);
 }
    
    mySample.load(ofToDataPath("sound.wav"));
    ofBackground(0,0,0);
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4);
    ampOut = 0.025;
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    for (int i = 0; i < bufferSize; i++){
        
        mix = 0;
        
        myClock.ticker();
        if (myClock.tick) {
            if (voice == 6) {
                voice = 0;
        }

        ADSR[voice].trigger = 1;
        pitch[voice] = voice + 1;
        voice ++;
        }
            
//        // sequencing with phasor and an array of freq values
//
//        int myArray[10] = {100, 200, 300, 400, 500, 600, 500, 400, 300, 200};
//        currentCount = myCounter.phasor(1, 1, 9);
        
        //--- oscillators ---//
        
        for (int i = 0; i < 6; i++) {
            
            ADSRout[i] = ADSR[i].adsr(1., ADSR[i].trigger);
            LFO3out[i] = LFO3[i].sinebuf(0.2);
            VCO3out[i] = VCO3[i].pulse(55 * pitch[i], 0.6);
            VCO4out[i] = VCO4[i].pulse((110 * pitch[i]) + LFO3out[i], 0.2);
            VCF3out[i] = VCF3[i].lores((VCO3out[i] + VCO4out[i]) * 0.5, 250 + ((pitch[i] + LFO3out[i]) * 1000), 10);
            
            mix += VCF3out[i] * ADSRout[i] / 6;
        
        }

        for (int i=0; i < 6; i++) {
        ADSR[i].trigger = 0;
        }
        
        output[i * nChannels] = mix * ampOut;
        output[i * nChannels + 1] = mix * ampOut;
        
    }
}
