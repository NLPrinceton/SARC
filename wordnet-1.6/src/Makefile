SHELL=/bin/sh

# Top level Makefile for WordNet 1.6 library and interface code

WN_ROOT = /usr/local/wordnet1.6
WN_BINDIR = $(WN_ROOT)/bin
WN_INCDIR = $(WN_ROOT)/include
WN_LIBDIR = $(WN_ROOT)/lib

TCL_INCDIR = /usr/local/include
TCL_LIBDIR = /usr/local/lib
TK_INCDIR = /usr/local/include
TK_LIBDIR = /usr/local/lib
X11_INCDIR = /usr/openwin/include
X11_LIBDIR = /usr/openwin/lib
WNB_LIBS = -ltk4.2 -ltcl7.6 -lX11 -lm

CC = gcc
LOCAL_CFLAGS = -O -DUNIX
LOCAL_LDFLAGS = -static

LIBS = -lwn

LIBDIR = lib
APPDIRS = wn wnb
MISCDIRS = include
SUBDIRS = $(LIBDIR) $(APPDIRS) $(MISCDIRS)

all: compile

compile: 
	@( cd $(LIBDIR) ; echo "Making $(LIBDIR)" ; $(MAKE) -k CC='$(CC)' LOCAL_CFLAGS='$(LOCAL_CFLAGS)' all )
	@echo "Done compiling library"
	@for dir in $(APPDIRS) ; \
	 do \
		echo "Compiling $$dir..." ; \
		if [ $$dir = "wnb" ] ; then \
			(cd $$dir ; \
			$(MAKE) -k CC='$(CC)' LOCAL_CFLAGS='$(LOCAL_CFLAGS) -I$(TCL_INCDIR) -I$(TK_INCDIR) -I$(X11_INCDIR)' LOCAL_LDFLAGS='$(LOCAL_LDFLAGS) -L$(TCL_LIBDIR) -L$(TK_LIBDIR) -L$(X11_LIBDIR)' LIBS='$(WNB_LIBS) $(LIBS)' WN_INSTALLDIR='$(WN_BINDIR)' all )  \
		else \
			(cd $$dir ; \
			$(MAKE) -k CC='$(CC)' LOCAL_CFLAGS='$(LOCAL_CFLAGS)' LOCAL_LDFLAGS='$(LOCAL_LDFLAGS)' LIBS='$(LIBS)' WN_INSTALLDIR='$(WN_BINDIR)' all ) ; \
		fi ; \
	 done ;
	@echo "Done compiling interfaces"

install:
	@for dir in $(APPDIRS) ; \
	 do \
		( cd $$dir ; echo "Installing $$dir...";  $(MAKE) WN_INSTALLDIR='$(WN_BINDIR)' install ) ; \
	 done
	@echo "Done installing interfaces"
	@( cd lib ; echo "Installing library.."; $(MAKE) WN_INSTALLDIR='$(WN_LIBDIR)' install )
	@( cd include ; echo "Installing include.."; $(MAKE) WN_INSTALLDIR='$(WN_INCDIR)' install)

uninstall:
	@for dir in $(APPDIRS) ; \
	 do \
		( cd $$dir; echo "Uninstalling $$dir..." ; $(MAKE) WN_INSTALLDIR='$(WN_BINDIR)' uninstall ) \
	 done
	@( cd lib ; echo "Uninstalling lib..." ; $(MAKE) WN_INSTALLDIR='$(WN_LIBDIR)' uninstall )
	@( cd include ; echo "Uninstalling include..." ; $(MAKE) WN_INSTALLDIR='$(WN_INCDIR)' uninstall )

clean::
	@for dir in $(SUBDIRS) ; \
	 do \
		( cd $$dir; echo "Cleaning subdirectory $$dir" ; $(MAKE) clean ) \
	 done ;

clean::
	@rm -f *~ "#"*

distclean:: clean uninstall
