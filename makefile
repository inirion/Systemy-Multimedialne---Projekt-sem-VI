#Makefile tested on Debian linux
#Needed library sfml (libsfml-dev)  OpenCV (libopencv-dev) (Video4Linux) libv4l-dev
ARG ?= -g
PH ?= on

ifeq ($(MAKECMDGOALS),clean)
PH := off
endif
ifeq ($(MAKECMDGOALS),cleanall)
PH := off
endif
ifeq ($(MAKECMDGOALS),help)
PH := off
endif


ifeq ($(PH),on)
BEFORESCRIPT := $(shell ./precompiled.sh)
else
BEFORESCRIPT := No precompiled headers
endif

CC := g++
CFLAGS := -c -std=c++11 -Wall -Wextra $(shell pkg-config --cflags opencv) $(ARG) 
LDFLAGS := -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network $(shell pkg-config --libs opencv)  -lv4l2  $(ARG)

SOURCES := base64/base64.cpp
SOURCES += Object2d.cpp DynamicObject2d.cpp HaveName.cpp HavePressed.cpp HaveHover.cpp HaveEnabled.cpp HaveVisible.cpp HaveFocus.cpp ButtonView.cpp Pressable.cpp
SOURCES += TextInput.cpp MenuButton.cpp TrackBar.cpp
SOURCES += MenuMain.cpp MenuOptionsFirst.cpp MenuOptionsSecond.cpp MenuDefaultsAsk.cpp MenuPaint.cpp MenuHockey.cpp MenuHockeyMulti.cpp MenuHockeyConnectServer.cpp MenuHockeyCreateServer.cpp MenuHockeyWin.cpp MenuHockeyCreateSideBySide.cpp MenuHockeyLobby.cpp
SOURCES += Hockey.cpp Puck.cpp Paddle.cpp AIController.cpp LanControllerServer.cpp LanControllerClient.cpp Gate.cpp
SOURCES += Conf.cpp ConfDetector.cpp ConfCapture.cpp ConfigurationManager.cpp
SOURCES += Broadcaster.cpp Server.cpp Client.cpp

SOURCES += main.cpp Program.cpp CameraPointer.cpp MousePointer.cpp UniPointer.cpp 

OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE := airhockey


all: printbeforescript $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

printbeforescript:
$(info $(BEFORESCRIPT))

help:
	@echo "make help - show this help"
	@echo "make PH=off - compile without precompiled headers generation"
	@echo "make ARG=-O3 - compile release, default is debug ARG = -g"
	@echo "make clean - clean *.o files"
	@echo "make cleanall - clean all cache files"

clean:
	rm -f *.o
	
cleanall: clean
	rm -f *.gch
	rm -f *.md5
