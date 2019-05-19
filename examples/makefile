
FLAGS = -std=c++11 -pthread
CFLAGS = -fPIC -g
LDIR = ../
DEP = ../macho.so

TARGET = rtsp_test
SOURCES = rtsp-test.cpp
HEADERS = ../third_party/include/
REQUESTS_HEADERS = ../include/requests
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

%.o : %.cpp
	g++ $(FLAGS) $(CFLAGS) -I$(HEADERS) -I$(REQUESTS_HEADERS) -c $< -o $@

$(TARGET): $(OBJECTS)
	g++ $(FLAGS) $(CFLAGS) $(OBJECTS) -L$(LDIR) -o $(TARGET) $(DEP)
