
FLAGS = -std=c++11 -pthread
CFLAGS = -fPIC -g
LMACHO_DIR = ../
LCIRCINUS_DIR = ../libcircinus/
DEP = ../macho.so ../libcircinus/libcircinus.so

TARGET = rtsp_test
SOURCES = rtsp-test.cpp
HEADERS = ../third_party/include/
REQUESTS_HEADERS = ../include/requests
CIRCINUS_PUB_HEADERS = ../libcircinus/include/
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

%.o : %.cpp
	g++ $(FLAGS) $(CFLAGS) -I$(HEADERS) -I$(REQUESTS_HEADERS) -I$(CIRCINUS_PUB_HEADERS) -c $< -o $@

$(TARGET): $(OBJECTS)
	g++ $(FLAGS) $(CFLAGS) -L$(LCIRCINUS_DIR) $(OBJECTS) -lcircinus -o $(TARGET) $(DEP)
