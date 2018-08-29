#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxSerial.h"
#include "ofEvents.h"
#include "ofxOsc.h"
#include <chrono>

// struct SerialMessage{
//     std::string message;
//     std::string exception;
// };

class ofApp : public ofBaseApp{
public:
	void setup() override;
	void update() override;
	void draw() override;
	void exit() override;

	void keyPressed(int k) override;

	bool start_button_pressed;

	// PS3 EYE CAMERA
	const int cam_width = 600;
	const int cam_height = 480;
	ofVideoGrabber video_grabber;

	// OPENCV
	void run_coherent_line_drawing(const ofImage &in, ofImage &out, ofFbo &dots_fbo);

	ofImage input_image, output_image;
	ofFbo dots_fbo;
	// coherent line drawing parameters
	const int halfw = 6;
	const int smooth_passes = 1;
	const float sigma1 = 4.50; // degree of coherence
	const float sigma2 = 0.95905;
	const float tau = 0.98;
	const int black = -8;
	const int threshold = 164;
	vector<glm::vec2> dots;

	// SERIAL
	const int BAUD_RATE = 9600;
	void init_serial_devices(ofxIO::SLIPPacketSerialDevice &device1);
	void send_current_command(int i); // used to send commands to the paintball machine
	int current_command_index; // keeps track of the current command that we're sending
	const int SERIAL_INITIAL_DELAY_TIME = 1; // seconds

	int button_pressed_time;
	bool draw_dots;
	
	// cnc machine movement boundaries
	const int MACHINE_X_MAX_POS = 875;
	const int MACHINE_Y_MAX_POS = 700;

	ofxIO::SLIPPacketSerialDevice cnc_device;

	// ofxSerial events
	void onSerialBuffer(const ofxIO::SerialBufferEventArgs &args);
	void onSerialError(const ofxIO::SerialBufferErrorEventArgs &args);

	// STATS
	std::chrono::steady_clock::time_point start_time;

private:
	// OSC STUFF
	 // add our osc message to the osc bundle
	void append_message(ofxOscMessage &message, osc::OutboundPacketStream &p);
	 // send the osc bundle via serial
	void send_osc_bundle(ofxOscMessage &m, ofxIO::SLIPPacketSerialDevice &device, int buffer_size);
};
