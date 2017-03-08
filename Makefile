#
# Makefile for DNS server (query support only)
#
# $Author: Cristina Camacho Romaguera $
# $Date: 2006/09/11 19:00:00 $
#
#


HOME_DIR=.

# Compiling in debug version
DEBUG_CFLAGS=-g -Wall -Wextra
COMPILE_MSG="Compiling debug version: "

CFLAGS=$(DEBUG_CFLAGS) -DLINUX  -D_X11

CPP=g++ -c -std=c++11
LINK= g++ -shared -Wl,-export-dynamic
LINKEXE=g++
MKLIB=ar -r

#All
ALL_PATH_INCLUDE=
ALL_PATH_LIB=
ALL_LIB=-lc -lm -lpthread -ldl -lstdc++

#Rules to compile
%.o: %.cpp
	@echo $(COMPILE_MSG) $<
	@$(CPP) $(CFLAGS) $(ALL_PATH_INCLUDE) $< -o $@

ALL_OBJS=log.o dnsDb.o rr.o answer.o header.o question.o message.o dns.o dnsd.o

EXE_NAME=dnsd
all: $(EXE_NAME)

#rules to build executable
$(EXE_NAME): $(ALL_OBJS)
	@echo "-Building exe: "$(EXE_NAME)
	@$(LINKEXE) $(ALL_OBJS) $(ALL_PATH_LIB) $(ALL_LIB) -o  $(EXE_NAME)

#rule to clean objects files
clean:
	@echo "Removing object files"
	@rm -f $(ALL_OBJS)
	@rm -f $(EXE_NAME)
	@rm -f *~
