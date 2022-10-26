SHELL=/bin/sh

# Makefile for WordNet 1.6 command line interface "wn"

WN_ROOT = /usr/local/wordnet1.6
WN_INSTALLDIR = $(WN_ROOT)/bin

CC = gcc
LOCAL_CFLAGS = -O -DUNIX
CFLAGS = -I../include $(LOCAL_CFLAGS)
LOCAL_LDFLAGS = -static
LDFLAGS= -L../lib $(LOCAL_LDFLAGS)
LIBS = -lwn

WN_FILES = wn
SRC = wn.c
OBJ = wn.o

all: $(WN_FILES)

install: $(WN_FILES)
	@if [ ! -d $(WN_INSTALLDIR) ] ; then \
		echo "Making directory $(WN_INSTALLDIR)" ; \
		mkdir -p $(WN_INSTALLDIR) ; \
		chmod 755 $(WN_INSTALLDIR) ; \
	fi ; 
	@for file in $(WN_FILES) ; \
	 do \
		filename=$(WN_INSTALLDIR)/$$file ; \
		if [ -f $$filename ] ; then \
			echo "Cannot install $$filename: file exists" ; \
		else \
			echo "Installing $$filename" ; \
			cp -p $$file $$filename ; \
			chmod 555 $$filename ; \
		fi ; \
	 done ;
	@echo "Done installing command line interface in $(WN_INSTALLDIR)"

uninstall:
	@for file in $(WN_FILES) ; \
	 do \
		filename=$(WN_INSTALLDIR)/$$file ; \
		if [ ! -f $$filename ] ; then \
			echo "Cannot uninstall $$filename: not present" ; \
		else \
			echo "Uninstalling $$filename" ; \
			rm -f $$filename ; \
		fi ; \
	 done ;
	@echo "Done uninstalling command line interface from $(WN_INSTALLDIR)"


$(WN_FILES): $(OBJ)
	$(CC) -o $(WN_FILES) $(LDFLAGS) $(OBJ) $(LIBS)

clean:
	@rm -f $(OBJ) $(WN_FILES) core *~ "#"*

distclean: uninstall clean
