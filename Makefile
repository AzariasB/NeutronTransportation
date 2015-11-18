## -*- Makefile -*-
##
## User: boutina
## Time: 16 nov. 2015 09:43:31
## Makefile created by Oracle Solaris Studio.
##
## This file is generated automatically.
##


#### Compiler and tool definitions shared by all build targets #####
CC = gcc
BASICOPTS = -g -std=c11
CFLAGS = $(BASICOPTS)


# Define the target directories.
TARGETDIR_transportation=res


all: $(TARGETDIR_transportation)/transportation

## Target: *.c
OBJS_transportation =  \
	$(TARGETDIR_transportation)/main.o
SYSLIBS_transportation = -lm 
USERLIBS_transportation = $(SYSLIBS_transportation) 
DEPLIBS_transportation =  
LDLIBS_transportation = $(USERLIBS_transportation)


# Link or archive
$(TARGETDIR_transportation)/transportation: $(TARGETDIR_transportation) $(OBJS_transportation) $(DEPLIBS_transportation)
	$(LINK.c) $(CFLAGS_transportation) $(CPPFLAGS_transportation) -o $@ $(OBJS_transportation) $(LDLIBS_transportation)


# Compile source files into .o files
$(TARGETDIR_transportation)/main.o: $(TARGETDIR_transportation) main.c
	$(COMPILE.c) $(CFLAGS_transportation) $(CPPFLAGS_transportation) -o $@ main.c



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_transportation)/transportation \
		$(TARGETDIR_transportation)/main.o
	rm -f -r $(TARGETDIR_transportation)


# Create the target directory (if needed)
$(TARGETDIR_transportation):
	mkdir -p $(TARGETDIR_transportation)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-amd64-Linux

