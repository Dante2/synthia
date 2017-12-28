/* This is an example of how to integrate maximilain into openFrameworks,
 including using audio received for input and audio requested for output.
 
 
 You can copy and paste this and use it as a starting example.
 
 */

#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    
    // set sampling Rate
    sampleRate = 44100;
    
    // set buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method
    bufferSize = 512;

    // calling the calling the setup method in maximilian settings containing samplerate and buffer size
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    /* Anything that you would normally find/put in maximilian's setup() method needs to go here. For example, Sample loading.
     */
    
    // apply ADSR values accordingly
    ADSR.attack = 200;
    ADSR.decay = 200;
    ADSR.sustain = 50;
    ADSR.release = 3000;
    
    ampOut = 0.5;
    
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
   
    
    for (int i = 0; i < bufferSize; i++){
        
        // Stick your maximilian 'play()' code in here ! Declare your objects in testApp.h.
        
        // variable wave currently not being used
        
        // wave =
        
        ADSR.trigger = 1;
        
        ADSRout = ADSR.adsr(1., ADSR.trigger);
        
        VCO1out = VCO1.sinewave(2000);
        
        mix += VCO1out * ADSRout;

        output[i * nChannels] = mix * ampOut;
        output[i * nChannels + 1] = mix * ampOut;
        
    }
    
    
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
