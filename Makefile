CC = icc
CXX = icpc
CFLAGS = -O3 -xHost -ipo -qopenmp -g -Wl,--as-needed
CXXFLAGS = $(CFLAGS) -std=c++11

TARGET = transmissivity
HDRS = $(wildcard *.h)
SOURCES = $(wildcard *.cc)
OBJS := $(patsubst %.cc,%.o,$(SOURCES))

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

clean:
	rm -f $(OBJS)
	rm -f $(TARGET)
