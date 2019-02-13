####### *_* Linux Keylogger Sub-Project *_* ##########
######################################################

set(srcs KeyloggerLib.cpp)
add_library(keylog SHARED srcs)
#install (TARGETS keylog DESTINATION bin)

