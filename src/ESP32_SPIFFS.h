#ifndef _ESP32_SPIFFS_H_
#define _ESP32_SPIFFS_H_

#include <FS.h>
#include <SPIFFS.h>

#define FORMAT_SPIFFS_IF_FAILED true
#define BUFFER_SIZE				512
#define TEST_FILE_ADDRESS		0x001F

void listDir(fs::FS &, const char *, uint8_t);
void readFile(fs::FS &, const char *);
void writeFile(fs::FS &, const char *, const char *);
void appendFile(fs::FS &, const char *, const char *);
void renameFile(fs::FS &, const char *, const char *);
void deleteFile(fs::FS &, const char *);
void testFileIO(fs::FS &, const char *);

#endif // _ESP32_SPIFFS_H_
