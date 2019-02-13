######################### *_* Linux_Keylogger *_* ##############################
* Documentation author: Marwen Gharsalli
* Email               : marwen.garsalli@ensi-uma.tn
#######################################################################################
This project was created to help linux people to be aware that they can be hacked. 
There is no doubt that linux is more secure than windows but, security can never be assured 100% .
/!\ Email me to get the Library. This project is for educational purpose, I am not responsible for malicious purpose.

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
An example build session targeting the build platform could look like this:

```
$ git clone https://github.com/MarvenGarsalli/Linux_Keylogger
$ cd Linux_Keylogger
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./test

```
=> This will create a .system file which contains pressed buttons per window name
