
AR := ar
AS := as
LD := ld
RANLIB := ranlib

ifeq ($(CC), clang)
USEGCC = 0
USECLANG = 1
else
USEGCC = 1
USECLANG = 0
endif

ifeq ($(OS), Darwin)
DARWINVER = $(shell uname -r | cut -b 1-2)
OSXVER = $(shell sw_vers -productVersion | cut -b 1-4)
ifeq ($(DARWINVER), 10)
USEGCC = 1
USECLANG = 0
else
USEGCC = 0
USECLANG = 1
endif
endif

ifeq ($(USEGCC),1)
CC = gcc
CXX = g++
JCFLAGS = -std=gnu99 -pipe $(fPIC) -fno-strict-aliasing -D_FILE_OFFSET_BITS=64
JCXXFLAGS = -pipe $(fPIC) -fno-rtti
DEBUGFLAGS = -ggdb3 -DDEBUG
SHIPFLAGS = -O3 -DNDEBUG -falign-functions
ifneq ($(ARCH), ppc64)
  SHIPFLAGS += -momit-leaf-frame-pointer
endif
endif

ifeq ($(USECLANG),1)
CC = clang
CXX = clang++
CFLAGS = -pipe $(fPIC) -fno-strict-aliasing -D_FILE_OFFSET_BITS=64
CXXFLAGS = -pipe $(fPIC) -fno-rtti
DEBUGFLAGS = -g -DDEBUG
SHIPFLAGS = -O3 -DNDEBUG
ifeq ($(OS), Darwin)
CC += -mmacosx-version-min=10.6
CXX += -mmacosx-version-min=10.6
CFLAGS += -D_LARGEFILE_SOURCE -D_DARWIN_USE_64_BIT_INODE=1
endif
endif


SRCS = hashing.c timefuncs.c dblprint.c ptrhash.c operators.c \
	utf8.c htable.c bitvector.c \
	int2str.c arraylist.c

OBJS = $(SRCS:%.c=%.o)
DOBJS = $(SRCS:%.c=%.do)

ifneq ($(MAKECMDGOALS),debug)
XOBJS = $(OBJS)
else
XOBJS = $(DOBJS)
endif

FLAGS = -Wall -Wno-strict-aliasing $(CFLAGS) $(HFILEDIRS:%=-I%) -fvisibility=hidden

DEBUGFLAGS += $(FLAGS)
SHIPFLAGS += $(FLAGS)

default: release

HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CPPFLAGS) $(SHIPFLAGS) -c $< -o $@
%.do: %.c $(HEADERS)
	$(CC) $(CPPFLAGS) $(DEBUGFLAGS) -c $< -o $@

release debug: libsupport.a

libsupport.a: $(XOBJS)
	rm -rf $@
	ar -rcs $@ $^

clean:
	rm -f *.o
	rm -f *.do
	rm -f *.a
	rm -f *~ *#
	rm -f core*
	rm -f libsupport.a
