PROGRAM=minestorm

# Add your objs to generate in OBJS var
OBJS=src/myMaths.o src/game.o src/player.o src/mines.o src/main.o 

CC?=gcc
TARGET?=$(shell $(CC) -dumpmachine)

CFLAGS=-O0 -g -Wall -Wextra -Wno-unused-parameter
CPPFLAGS=-Iinclude -Ithird_party/include -MMD
LDFLAGS=-Lthird_party/libs-$(TARGET)
LDLIBS=-lraylib

ifeq ($(TARGET),x86_64-linux-gnu)
LDLIBS+=-ldl -lpthread -lm
else ifeq ($(TARGET),x86_64-pc-cygwin)
LDLIBS+=-lgdi32
endif

DEPS=$(OBJS:.o=.d)

.PHONY: all clean

all: $(PROGRAM)

-include $(DEPS)

%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

build.tar.gz: $(PROGRAM) $(wildcard assets/*)
	tar czf build.tar.gz $(PROGRAM) assets

TestColisionAABB: tests/TestColision_AABB.c
	gcc $(CFLAGS) -Iinclude -Ithird_party/include $(LDFLAGS) tests/TestColision_AABB.c $(LDLIBS) -o $@

TestPolygonDrawing: tests/polygonDrawing.c
	gcc $(CFLAGS) -Iinclude -Ithird_party/include $(LDFLAGS) tests/polygonDrawing.c src/myMaths.c $(LDLIBS) -o $@

TestColisionSAT: tests/TestColision_SAT.c
	gcc $(CFLAGS) -Iinclude -Ithird_party/include $(LDFLAGS) tests/TestColision_SAT.c $(LDLIBS) -o $@

clean:
	rm -f $(OBJS) $(DEPS) build.tar.gz $(PROGRAM) TestColisionAABB TestPolygonDrawing TestColisionSAT TestColisionAABB.exe TestPolygonDrawing.exe TestColisionSAT.exe