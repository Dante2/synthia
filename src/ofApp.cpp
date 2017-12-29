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
    
    ampOut = 0.005;
    
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
        
        // clock device using phasor and square wave
        
        int myArray[10] = {100, 200, 300, 400, 500, 600, 500, 400, 300, 200};
        currentCount = myCounter.phasor(1, 1, 9);
        
        // oscillator1 
        VCO1out = VCO1.square(myArray[currentCount]);
        
        // filter
        VCFout = VCF.lopass(VCO1out, 0.005);
    
        
        output[i * nChannels] = VCFout * ampOut;
        output[i * nChannels + 1] = VCFout * ampOut;
        
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
