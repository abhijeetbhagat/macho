FLAGS = -std=c++11
CFLAGS = -fPIC -g
LDFLAGS = -shared

TARGET = macho.so
SOURCES = $(shell echo src/*.cpp) $(shell echo src/requests/*.cpp) $(shell echo src/transport/*.cpp) $(shell echo src/rtp/*.cpp) $(shell echo src/utils/*.cpp) $(shell echo src/filters/*.cpp) $(shell echo src/sinks/*.cpp)

HEADERS = third_party/include/
REQUESTS_HEADERS = include/requests
TRANSPORT_HEADERS = include/transport
RTP_HEADERS = include/rtp
UTILS_HEADERS = include/utils
FILTERS_HEADERS = include/filters
SINKS_HEADERS = include/sinks
LCIRCINUS_DIR = libcircinus/
CIRCINUS_PUB_HEADERS = libcircinus/include/

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

%.o : %.cpp
	g++ $(FLAGS) $(CFLAGS) -I$(HEADERS) -I$(REQUESTS_HEADERS) -I$(TRANSPORT_HEADERS) -I$(RTP_HEADERS) -I$(UTILS_HEADERS) -I$(FILTERS_HEADERS) -I$(SINKS_HEADERS) -I$(CIRCINUS_PUB_HEADERS) -c $< -o $@

$(TARGET): $(OBJECTS)
	g++ $(FLAGS) $(CFLAGS) $(OBJECTS) -L$(LCIRCINUS_DIR) -lcircinus -o $(TARGET) $(LDFLAGS)
