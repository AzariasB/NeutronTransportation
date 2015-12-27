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
BASICOPTS = -std=c11

# Define the target directories.
TARGETDIR_transportation=res


all: $(TARGETDIR_transportation)/transportation

## Target: *.c
OBJS_transportation =  \
	$(TARGETDIR_transportation)/window_manager.o \
	$(TARGETDIR_transportation)/calc_transportation.o \
	$(TARGETDIR_transportation)/main.o
SYSLIBS_transportation = -lm
USERLIBS_transportation = $(SYSLIBS_transportation)
GTKFLAGS=`pkg-config --libs --cflags gtk+-3.0`
CFLAGS = $(BASICOPTS)


# Link or archive
$(TARGETDIR_transportation)/transportation: $(TARGETDIR_transportation) $(OBJS_transportation)
	$(LINK.c) $(CFLAGS_transportation) -o $@ $(OBJS_transportation) $(USERLIBS_transportation) $(GTKFLAGS)


# Compile source files into .o files
$(TARGETDIR_transportation)/window_manager.o: $(TARGETDIR_transportation) window_manager.c
	$(COMPILE.c) $(CFLAGS_transportation)  -o $@ window_manager.c $(GTKFLAGS)

$(TARGETDIR_transportation)/calc_transportation.o: $(TARGETDIR_transportation) calc_transportation.c
	$(COMPILE.c) $(CFLAGS_transportation) -o $@ calc_transportation.c $(GTKFLAGS)


$(TARGETDIR_transportation)/main.o: $(TARGETDIR_transportation) main.c
	$(COMPILE.c) $(CFLAGS_transportation) -o $@ main.c $(GTKFLAGS)



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_transportation)/transportation \
		$(TARGETDIR_transportation)/main.o \
		$(TARGETDIR_transportation)/calc_transportation.o \
		$(TARGETDIR_transportation)/window_manager.o
	rm -f -r $(TARGETDIR_transportation)


# Create the target directory (if needed)
$(TARGETDIR_transportation):
	mkdir -p $(TARGETDIR_transportation)
