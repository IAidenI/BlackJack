# ================== Config commune ==================
CC         = g++
TARGET     = blackjack
SOURCEDIR  = sources
HEADERSDIR = headers

# compile faisait: g++ -std=c++17 blackjack.cpp sources/*.cpp -Iheaders -o blackjack
SOURCES := blackjack.cpp $(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS := $(SOURCES:.cpp=.o)
.INTERMEDIATE: $(OBJECTS)

CFLAGS  = -Wall -g -std=c++17 -I$(HEADERSDIR)
LDFLAGS =
LDLIBS  =

RM := rm -f

# ================== Règles ==================
.PHONY: all clean run

all: $(TARGET)
	@echo "Binary ready ! -> $(TARGET)"
	

$(TARGET): $(OBJECTS)
	@echo "Compiling and linking $(TARGET)..."
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

%.o: %.cpp $(HEADERSDIR)/*.hpp
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning object files..."
	-$(RM) $(OBJECTS)

run: $(TARGET)
	./$(TARGET)
