FLAGS = -std=c++11
CFLAGS = -fPIC -g
LDFLAGS = -shared

TARGET = macho.so
SOURCES = $(shell echo src/*.cpp)
#HEADERS = $(shell echo include/*.h third_party/include/spdlog/*.h third_party/include/)
HEADERS = third_party/include/
REQUESTS_HEADERS = include/requests
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

%.o : %.cpp
	g++ $(FLAGS) $(CFLAGS) -I$(HEADERS) -I$(REQUESTS_HEADERS) -c $< -o $@

$(TARGET): $(OBJECTS)
	g++ $(FLAGS) $(CFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
