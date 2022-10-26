SHELL=/bin/sh

# Makefile for WordNet 1.6 Browser

WN_ROOT = /usr/local/wordnet1.6
WN_INSTALLDIR = $(WN_ROOT)/bin

TCL_INCDIR = /usr/local/include
TCL_LIBDIR = /usr/local/lib
TK_INCDIR = /usr/local/include
TK_LIBDIR = /usr/local/lib
X11_INCDIR = /usr/X11/include
X11_LIBDIR = /usr/X11/lib
WNB_LIBS = -ltk4.2 -ltcl7.6 -lX11 -lm

CC = gcc
LOCAL_CFLAGS = -O -DUNIX -I$(TCL_INCDIR) -I$(TK_INCDIR) -I$(X11_INCDIR)
CFLAGS = -I../include $(LOCAL_CFLAGS)
LOCAL_LDFLAGS = -static -L$(TCL_LIBDIR) -L$(TK_LIBDIR) -L$(X11_LIBDIR)
LDFLAGS= -L../lib $(LOCAL_LDFLAGS)
LIBS = -lwn

WN_FILES = wishwn wnb
SRC = stubs.c tkAppInit.c
OBJ = stubs.o tkAppInit.o

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
	@echo "Done installing WordNet browser interface in $(WN_INSTALLDIR)"

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

wishwn: $(OBJ)
	$(CC) -o wishwn $(LDFLAGS) $(OBJ) $(LIBS)

wnb:

clean:
	@rm -f $(OBJ) wishwn core *~ "#"*

distclean: uninstall clean
