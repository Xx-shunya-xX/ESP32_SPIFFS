#include "ESP32_SPIFFS.h"

void setup() {
	Serial.begin(115200);
	if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
		Serial.println("Connection to SPIFFS failed");
		return;
	}
	listDir(SPIFFS, "/", 0);
	writeFile(SPIFFS, "/hello.txt", "Hello ");
	appendFile(SPIFFS, "/hello.txt", ", World!\r\n");
	renameFile(SPIFFS, "/hello.txt", "/foo.txt");
	readFile(SPIFFS, "/foo.txt");
	deleteFile(SPIFFS, "/foo.txt");
	testFileIO(SPIFFS, "/test.txt");
	deleteFile(SPIFFS, "/test.txt");
	Serial.println("Test Complete");
}

void loop() {
}
