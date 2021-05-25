#include "ESP32_SPIFFS.h"

void listDir(fs::FS &file_system, const char *dirname, uint8_t levels) {
	Serial.printf("Listing directory : %s\r\n", dirname);
	File root = file_system.open(dirname, FILE_READ);

	if(!root) {
		Serial.println(" - failed to open directory");
		return;
	}

	if(!root.isDirectory()) {
		Serial.println("Not a directory");
		return;
	}

	File file = root.openNextFile();
	while(file) {
		if(file.isDirectory()) {
			Serial.print("	Dir : ");
			Serial.println(file.name());
			if(levels) {
				listDir(file_system, file.name(), levels - 1);
			}
		}
		else {
			Serial.print(" FILE : ");
			Serial.print(file.name());
			Serial.print("\tSize : ");
			Serial.println(file.size());
		}
		file = root.openNextFile();
	}
}

void readFile(fs::FS &file_system, const char *path) {
	Serial.printf("Reading File : %s\r\n", path);
	File file = file_system.open(path, FILE_READ);
	if(!file || file.isDirectory()) {
		Serial.println("File failed to open");
		return;
	}
	Serial.println(" - read from file : ");
	while(file.available()) Serial.write(file.read());
}

void writeFile(fs::FS &file_system, const char *path, const char *msg) {
	Serial.printf("Writing to file : %s\r\n", path);
	File file = file_system.open(path, FILE_WRITE);
	if(!file) {
		Serial.println(" - failed to open file for writing");
		return;
	}
	if(file.print(msg)) {
		Serial.println(" - file written");
	}
	else {
		Serial.println(" - file write failed");
	}
}

void appendFile(fs::FS &file_system, const char *path, const char *msg) {
	Serial.printf("Appending to file : %s\r\n", path);
	File file = file_system.open(path, FILE_APPEND);
	if(!file) {
		Serial.println(" - failed to open file for appending");
		return;
	}
	if(file.print(msg)) {
		Serial.println(" - message appended");
	}
	else {
		Serial.println(" - message append failed");
	}
}

void renameFile(fs::FS &file_system, const char *path1, const char *path2) {
	Serial.printf("Renaming file : %s to %s\r\n", path1, path2);
	if(file_system.rename(path1, path2)) {
		Serial.println("File renamed");
	}
	else {
		Serial.println("File renaming was unsuccessful");
	}
}

void deleteFile(fs::FS &file_system, const char *path) {
	Serial.printf("Deleting file : %s\r\n", path);
	if(file_system.remove(path)) {
		Serial.println(" - file deleted");
	}
	else {
		Serial.println(" - file deletion was unsuccessful");
	}
}

void testFileIO(fs::FS &file_system, const char *path) {
	Serial.printf("Testing file I/O with %s\r\n", path);
	static uint8_t buffer[BUFFER_SIZE];
	size_t length = 0, i;
	File file = file_system.open(path, FILE_WRITE);
	if(!file) {
		Serial.println(" - failed to open file for writing");
		return;
	}
	Serial.print(" - writing");
	uint32_t start = millis();
	for(i = 0; i < 2048; i++) {
		if((i & TEST_FILE_ADDRESS) == TEST_FILE_ADDRESS) {
			Serial.println(".");
		}
		file.write(buffer, BUFFER_SIZE);
	}
	Serial.println("");
	uint32_t end = millis() - start;
	Serial.printf(" - %u bytes written in %u ms\r\n", 2048 * BUFFER_SIZE, end);
	file.close();

	file = file_system.open(path, FILE_READ);
	i = 0;
	if(file && !file.isDirectory()) {
		length = file.size();
		size_t file_length = length;
		start = millis();
		Serial.print(" - reading");
		while(length) {
			size_t to_read = length;
			if(to_read > BUFFER_SIZE) {
				to_read = BUFFER_SIZE;
			}
			file.read(buffer, to_read);
			if((i++ & TEST_FILE_ADDRESS) == TEST_FILE_ADDRESS) {
				Serial.print(".");
			}
			length -= to_read;
		}
		Serial.println("");
		end = millis() - start;
		Serial.printf(" - %u bytes read in %u ms\r\n", file_length, end);
		file.close();
	}
	else {
		Serial.println(" - failed to open file for reading");
	}
}
