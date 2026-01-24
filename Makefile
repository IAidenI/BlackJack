# ================== Choix de l'app ==================
# Usage:
#   make                 -> build blackjackCLI
#   make APP=blackjackUI -> build blackjackUI
APP ?= blackjackCLI

CC         = g++
SOURCEDIR  = sources
HEADERSDIR = headers
THIRDPARTY = third_party/bcrypt
BCRYPT_INC = -I$(THIRDPARTY)/include -I$(THIRDPARTY)/src

# ================== Sources communes ==================
COMMON_SOURCES := $(wildcard $(SOURCEDIR)/**/*.cpp) \
                  $(wildcard $(SOURCEDIR)/*.cpp) \
                  $(wildcard $(THIRDPARTY)/src/*.cpp)

# ================== Sources par app ==================
APP_SOURCE := $(APP).cpp
SOURCES    := $(APP_SOURCE) $(COMMON_SOURCES)

OBJECTS := $(SOURCES:.cpp=.o)
.INTERMEDIATE: $(OBJECTS)

CFLAGS  = -Wall -g -std=c++17 -I$(HEADERSDIR) $(BCRYPT_INC)

# ================== Raylib uniquement pour l'UI ==================
RAYLIB_CFLAGS :=
RAYLIB_LIBS   :=

ifeq ($(APP),blackjackUI)
  RAYLIB_CFLAGS := $(shell pkg-config --cflags raylib 2>/dev/null)
  RAYLIB_LIBS   := $(shell pkg-config --libs raylib 2>/dev/null)
  # Fallback si pkg-config n'est pas dispo/renvoie vide
  ifeq ($(strip $(RAYLIB_LIBS)),)
    RAYLIB_LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
  endif
endif

CFLAGS += $(RAYLIB_CFLAGS)
LDLIBS  = $(RAYLIB_LIBS)

RM := rm -f

# ================== Règles ==================
.PHONY: all clean run

all: $(APP)
	@echo "Binary ready ! -> $(APP)"

$(APP): $(OBJECTS)
	@echo "Compiling and linking $(APP)..."
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cpp $(HEADERSDIR)/*.hpp
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning object files..."
	-$(RM) $(OBJECTS) blackjackCLI blackjackUI

run: all
	./$(APP)
