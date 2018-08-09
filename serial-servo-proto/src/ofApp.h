#pragma once

#include "ofMain.h"
#include "ofxSerial.h"

struct SerialMessage {

    std::string message;
    std::string exception;
    int fade = 255;
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		
		void onSerialBuffer(const ofxIO::SerialBufferEventArgs& args);
    	void onSerialError(const ofxIO::SerialBufferErrorEventArgs& args);

		ofxIO::SLIPPacketSerialDevice device;
		std::vector<SerialMessage> serialMessages;

};