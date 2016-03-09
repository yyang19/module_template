#the compiler
CC=gcc
CXX=g++

#compiler flags
CFLAGS = -g -Wall

# define library paths in addition to /usr/lib
# if I wanted to include libraries not in /usr/lib I'd specify their path using -Lpath, something like:
# LFLAGS = -L/home/newhall/lib  -L../lib
LFLAGS =

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
#   LIBS = -lmylib -lm
LIBS = -lm

#c source files
SRCS = skelton.c module.c
OBJS = $(SRCS:.c=.o)

# define the executable file 
MAIN = myprog

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean

all: $(MAIN)

$(MAIN): $(OBJS) 
	 $(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)

.c.o:
	 $(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	 $(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	 makedepend $(INCLUDES) $^
