/* This is an example of how to integrate maximilain into openFrameworks,
 including using audio received for input and audio requested for output.
 
 
 You can copy and paste this and use it as a starting example.
 
 */

#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    
    // maxiClock
    myClock.setTicksPerBeat(2);
    myClock.setTempo(60);
    
    // set sampling Rate
    sampleRate = 44100;
    
    // set buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method
    bufferSize = 512;

    // calling the calling the setup method in maximilian settings containing samplerate and buffer size
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
 for (int i = 0; i < 6; i++) {
    
    // apply ADSR values accordingly
    ADSR[i].setAttack(20);
    ADSR[i].setDecay(100);
    ADSR[i].setSustain(0.25);
    ADSR[i].setRelease(1000);
     
 }
    
    mySample.load(ofToDataPath("sound.wav"));
    
    ofBackground(0,0,0);

    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4); /* this has to happen at the end of setup - it switches on the DAC */

}

//--------------------------------------------------------------
void ofApp::update(){
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    /* You can use any of the data from audio received and audiorequested to draw stuff here.
     
     */
    
    
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
   
    /* currently set up with two different types of clock --> maxiClock and phasor
     but currently just using maxiClock */
    
    for (int i = 0; i < bufferSize; i++){
        
        // set mix to 0 to begin with
        mix = 0;
        
        // maxiClock functionality
        myClock.ticker();
        if (myClock.tick) {
            // freq += 2;
            // std::cout << myClock.tick;
            
            // retrigger the voices once we reach the 6th and final voice
            if (voice == 6) {
                voice = 0;
        }
            
        // trigger the envelope from the start
        ADSR[voice].trigger = 1;
        // ADSR.trigger = 1;
        pitch[voice] = voice+1;
        voice ++;
            
        }
    
        /* our ADSR ENVs are iterated through and passed through to the ADSR output
         where the adsr functionality passes it a constant signal of 1 to generate the transient and triggered */
        ADSRout[i] = ADSR[i].adsr(1., ADSR[i].trigger);
        //std::cout << " adsr out = " << ADSRout;
    
        // LFO
        LFO1out = LFO1.sinewave(5) * 2;
        LFO2out = LFO2.sinewave(0.1) * 1500;
 
        // sequencing with phasor and an array of freq values
        
        int myArray[10] = {100, 200, 300, 400, 500, 600, 500, 400, 300, 200};
        currentCount = myCounter.phasor(1, 1, 9);

        // this if else statement couples with the phasor in currentCount to trigger the ADSR
//        if (currentCount == 1) ADSR.trigger = 1;
//
//        else ADSR.trigger = 0;
        
        //--- oscillators ---//
        
        // worth playing around with high pass / band pass / band reject
        VCO1out = VCO1.square(2000) * currentCount;
        
        // LFO controlled oscillator --> vibrato
        VCO2out = VCO2.sawn(200 + LFO1out);
        
        // using env to control pitch of oscillator --> good for drums with currentCount phasor as clock
        VCO3out[i] = VCO3[i].sawn(currentCount * 100 * ADSRout[i] * 10);
        
        // filters
        // low pass - portamento
        VCF1out = VCO1.square(VCF1.lopass(myArray[currentCount], 0.005));
        
        // low res - vibrato
        VCF2out = VCF2.lores(VCO2out, 2000 + LFO2out, 20);
        
        // apply envs
        // double VCF2env = VCF2out * ADSRout;
        VCO3env[i] = VCO3out[i] * ADSRout[i] / 6;
        
        
        // amplitude control on raw oscillator and filter
        double VCO1amp = VCO1out * 0.0;
        double VCF1amp = VCF1out * 0.0;
        // double VCF2amp = VCF2env * 0.0;
        double VCO2amp = VCO2out * 0.0;
        VCO3amp[i] = VCO3env[i] * 0.025;
        
        // mixer
        // mix = VCO1amp + VCF1amp + VCF2amp + VCO2amp + VCO3amp;
        
        mix += VCO3amp[i];
        
        // if you dont set env to 'off' its constantly 'on'
        ADSR[i].trigger = 0;
        output[i * nChannels] = mix;
        output[i * nChannels + 1] = mix;
        
    }
    // std::cout << " adsr out = " << ADSRout;
    
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    for(int i = 0; i < bufferSize; i++){
        /* you can also grab the data out of the arrays*/
        
    }
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
