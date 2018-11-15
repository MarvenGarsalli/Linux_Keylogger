######################### *_* Linux_Keylogger *_* ##############################
* Documentation author: Marwen Gharsalli
* Email               : marwen.garsalli@ensi-uma.tn
#######################################################################################
This project was created to help linux people be aware that they can be hacked. 
There is no doubt that linux is safer than windows but, security can never be assured 100% .
/!\ Email me to get the Library.

#        +-------------------------------------+
#        |  Hardware Platforms requirements    |
#        +-------------------------------------+
Linux OS (linux mint 17.3)
Xlib package
G++ 4.8 compiler

#        +-------------------------------------+
#        |        patches are welcome!         |
#        +-------------------------------------+
For Linux Platform:
*) Create a bash scrpit to transform this program to one of the linux runlevel services.

#        +-------------------------------------+
#        |        Deployment and Usage         |
#        +-------------------------------------+
1/ Build: g++ -o test key.cpp KeyloggerLib.cpp -lpthread -X11
3/ Run the project: sudo ./test
2/ Check for log file which has been created and it contains not only the pressed key but also the active windows of each pressed keys.

