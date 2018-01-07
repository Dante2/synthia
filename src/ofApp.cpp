/* manipulated samples with spin back */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    
//    myClock.setTicksPerBeat(1);
//    myClock.setTempo(60);
    
    sampleRate = 44100;
    
    bufferSize = 512;

    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    beats.load("/Users/jools/Documents/Uni/yr2/Perception_and_Multimedia/Term2/Audio/Labs/Week18/song1.wav");
    beats2.load("/Users/jools/Documents/Uni/yr2/Perception_and_Multimedia/Term2/Audio/Labs/Week18/song1.wav");
    
    ofBackground(0,0,0);
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4);
    
    ampOut = 0.5;
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    for (int i = 0; i < bufferSize; i++){
        
        currentCount = myPhasor.phasor(0.25, 1, 9);
        
        myOtherPhasorOut = myOtherPhasor.phasor(1) * beats.length;
        
        if (currentCount == 1){
            beats.trigger();
        }
        
        if (currentCount == 8){
            // spin back using phasor
            VCO1out = VCO1.phasor(-2) * 2;
            sample1 = beats.play(VCO1out, 0, beats.length);
            // lower the volume of spin back a bit
            ampOut = 0.25;
        } else {
            sample1 = beats.play(0.025, 0, beats.length);
            // sample1 = beats.play(0.025, 0, myOtherPhasorOut);
        }
        
//        myClock.ticker();
//        if (myClock.tick){
//            beats.trigger();
//        }
        
        // -1 to 1 twice a second. Multiplying the sinewave by a positive or negative number has really interesting effect.
        // VCO1out = VCO1.sinewave(-2) * 10;
        
        //--- samples ---//
        
        // sample1 = beats.play(VCO1out);
        
//        // play at given frequency from start pos to end pos
//        sample1 = beats.play(0.25, beats.length / 2, beats.length);
//
//        // playing backwards
//        sample2 = beats2.play(-0.5, 0, beats.length) * 0.6;
        
        // sample1 = beats.playOnce(0.5);
        
        
        
        //output[0]=beats.play();//just play the file. Looping is default for all play functions.
        // output[0]=beats.play(0.68);//play the file with a speed setting. 1. is normal speed.
        //output[0]=beats.play(0.5,0,44100);//linear interpolationplay with a frequency input, start point and end point. Useful for syncing.
        //output[0]=beats.play4(0.5,0,44100);//cubic interpolation play with a frequency input, start point and end point. Useful for syncing.
        
        // output[i * nChannels] = sample1 + sample2;
        output[i * nChannels] = sample1 * ampOut;
        output[i * nChannels + 1] = sample1 * ampOut;
        
    }
}
