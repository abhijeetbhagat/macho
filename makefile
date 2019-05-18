FLAGS = -std=c++11
CFLAGS = -fPIC -g
LDFLAGS = -shared

TARGET = macho.so
SOURCES = $(shell echo src/*.cpp) $(shell echo src/requests/*.cpp) $(shell echo src/transport/*.cpp) $(shell echo src/rtp/*.cpp) $(shell echo src/utils/*.cpp)

HEADERS = third_party/include/
REQUESTS_HEADERS = include/requests
TRANSPORT_HEADERS = include/transport
RTP_HEADERS = include/rtp
UTILS_HEADERS = include/utils

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

%.o : %.cpp
	g++ $(FLAGS) $(CFLAGS) -I$(HEADERS) -I$(REQUESTS_HEADERS) -I$(TRANSPORT_HEADERS) -I$(RTP_HEADERS) -I$(UTILS_HEADERS) -c $< -o $@

$(TARGET): $(OBJECTS)
	g++ $(FLAGS) $(CFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
