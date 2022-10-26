SHELL=/bin/sh

# Makefile for both source and binary distribution of WordNet 1.6

# The WordNet Unix release is provided as a binary installation for 
# the following platforms.
#
#	SPARCstation running SunOS Release 4.1.3
#	SPARCstation running Solaris 2.5.2
#	Silicon Graphics Mips processor running Irix 5.3
#	PC 486 processor running Linux kernel 2.0.27
#
# If you are using one of these systems, you should select the the
# appropriate PLATFORM below, and use the 'make BinWorld' command to
# install WordNet from the pre-compiled binaries.

# Platform for binary installation.  If you are using one of the 
# following systems you do not have to compile the search code.

PLATFORM = sunos
#PLATFORM = solaris
#PLATFORM = irix
#PLATFORM = linux

# The WordNet system must be installed in a directory hierarchy.
# WN_ROOT is the root of the WordNet installation hierarchy.
# The default is /usr/local/wordnet1.6.  

# The installation process will create the following subdirectories:

#	bin	WordNet executable programs
#
# 	dict	WordNet database files (the WNSEARCHDIR environment
#		variable must be set by the user if the database
#		is NOT installed in /usr/local/wordnet1.6/dict)
#
#	lib	library of WordNet search code functions (libwn.a)
#
#	include	header files for use with library functions
#
#	man	WordNet manual pages (WordNet Reference Manual)

# Default installation paths

WN_ROOT = /usr/local/wordnet1.6

# By default, precompiled WordNet binaries are installed in 
# $WN_ROOT/bin.  You may specify another location, such as /usr/local/bin.
# By installing the binaries in /usr/local/bin, you probably do not have to
# change your PATH environment variable.

WN_BINDIR = $(WN_ROOT)/bin

# By default, the WordNet database files are installed in $WN_ROOT/dict.
# You may specify another location.  If the database is not installed in
# the default location, you MUST set the environment variable 
# WNSEARCHDIR, or the WordNet browser will not be able to run.

WN_DICTDIR = $(WN_ROOT)/dict

# By default, installing the database files is done by copying them
# from the "dict" subdirectory into WN_DICTDIR.  To save space, you
# can set INSTALLCMD to 'mv', which will move the files instead of
# copying them.  This is slightly dangerous since you won't have a
# copy of the database files in the release directory.  If you set
# INSTALLCMD to 'mv', you must set INSTALLFLAGS to nothing.

INSTALLCMD = cp
INSTALLFLAGS = -p
#INSTALLCMD = mv
#INSTALLFLAGS = 

# By default, the WordNet library is installed in $WN_ROOT/lib, and
# the WordNet header files are installed in $WN_ROOT/include.  These
# used when developing new applications that access the WordNet
# database files.

WN_LIBDIR = $(WN_ROOT)/lib
WN_INCDIR = $(WN_ROOT)/include

# By default, manual pages are installed $WN_ROOT/man. You may 
# specify another location, such as /usr/local/man.  By installing the 
# manual pages in /usr/local/man, you probably do not have to change 
# your MANPATH environment variable.

WN_MANDIR = $(WN_ROOT)/man

###### Platform specific stuff (for compiling from source only) ######

# To build WordNet you must use an ANSI C compiler. 'gcc' is freely
# and readily available.  It's what we used to make the precompiled
# binaries.

CC = gcc

# By default, WordNet is built using static linking whenever possible.  
# "-static" is the correct flag for 'gcc'.  Solaris doesn't seem to be
# able to build it statically because libX11 calls dynamic functions.

# Use this for SunOS and Linux
LOCAL_LDFLAGS = -static

# Use this for Solaris
#LOCAL_LDFLAGS = -R/usr/openwin/lib:/usr/lib:/usr/local/lib

# Use this for IRIX
#LOCAL_LDFLAGS = 

# "UNIX" must be defined for things to compile...

LOCAL_CFLAGS = -O -DUNIX

# The WordNet browser uses the Tcl/Tk libraries (libtcl7.6, libtk4.2).  
# If you already have these versions installed on your system, then
# you can just set the paths below as necessary for your installation.
# If you do not have Tcl/Tk installed, or do not have the correct
# versions, see the file "README.tcktk" for information about 
# downloading and installing Tcl7.6 and Tk4.2 on your system.

TCL_INCDIR = /usr/local/include
TCL_LIBDIR = /usr/local/lib
TK_INCDIR = /usr/local/include
TK_LIBDIR = /usr/local/lib
X11_INCDIR = /usr/openwin/include
X11_LIBDIR = /usr/openwin/lib

# Libraries needed for SunOS
WNB_LIBS = -ltk42 -ltcl76 -lX11 -lm

# Libraries needed Irix (note the different nomenclature for the
# Tcl/Tk libraries)
#WNB_LIBS = -ltk4.2 -ltcl7.6 -lX11 -lm

# Libraries needed for Solaris and Linux
#WNB_LIBS = -ltk4.2 -ltcl7.6 -lX11 -lm -ldl -lsocket -lnsl

###### Finally, the "make" targets ######

all:
	@echo 'First edit Makefile and set "$$PLATFORM" for your computer system'
	@echo "Then specify target: BinWorld, SrcWorld, CleanWorld"

# Target to install WordNet from pre-compiled binaries.  Specify
# $(PLATFORM) above.

BinWorld: wnbin wndict wninclude wnlib wnman
	@echo "Done installing WordNet 1.6 for $(PLATFORM)..."

# Target to compile and install WordNet from source code

SrcWorld: clean wnsrc wndict wnman
	@echo "Done creating and installing WordNet 1.6.."

# After the database is installed and everything has been tested,
# use this target to clean up from the make and delete the uninstalled 
# version of the database. 

CleanWorld: clean cleandbfiles
	echo "Done cleaning up and removing source database files"

# You should not need to use any of the followin targets unless
# something goes wrong.

wnbin:
	@echo "Installing WordNet 1.6 binaries in $(WN_BINDIR)..."
	(cd bin/$(PLATFORM); $(MAKE) -k WN_INSTALLDIR='$(WN_BINDIR)' install)

wndict:
	@echo "Installing WordNet 1.6 database in $(WN_DICTDIR)..."
	(cd dict; $(MAKE) -k WN_INSTALLDIR='$(WN_DICTDIR)' INSTALLCMD='$(INSTALLCMD)' INSTALLFLAGS='$(INSTALLFLAGS)' install)

wninclude:
	@echo "Installing WordNet 1.6 header files in $(WN_INCDIR)..."
	(cd include; $(MAKE) -k WN_INSTALLDIR='$(WN_INCDIR)' install)

wnlib:
	@echo "Installing WordNet 1.6 library in $(WN_LIBDIR)..."
	(cd lib/$(PLATFORM); $(MAKE) -k WN_INSTALLDIR='$(WN_LIBDIR)' install)
	(cd lib/wnres; $(MAKE) -k WN_INSTALLDIR='$(WN_LIBDIR)/wnres' install)

wnman:
	@echo "Installing WordNet 1.6 documentation in $(WN_MANDIR)..."
	(cd man; $(MAKE) -k WN_INSTALLDIR='$(WN_MANDIR)' install)

wnsrc:
	(cd src; $(MAKE) -k CC='$(CC)' WN_ROOT='$(WN_ROOT)' TCL_INCDIR='$(TCL_INCDIR)' TK_INCDIR='$(TK_INCDIR)' TCL_LIBDIR='$(TCL_LIBDIR)' TK_LIBDIR='$(TK_LIBDIR)' X11_INCDIR='$(X11_INCDIR)' X11_LIBDIR='$(X11_LIBDIR)' WNB_LIBS='$(WNB_LIBS)' LOCAL_CFLAGS='$(LOCAL_CFLAGS)' LOCAL_LDFLAGS='$(LOCAL_LDFLAGS)' WN_BINDIR='$(WN_BINDIR)' WN_LIBDIR='$(WN_LIBDIR)' WN_INCDIR='$(WN_INCDIR)' all install)

CLEANDIRS = bin dict include lib man

clean::
	@rm -f *~ "#"*

clean::
	@for i in $(CLEANDIRS) src ; \
	  do \
		(cd $$i ; echo "Cleaning directory $$i..." ; $(MAKE) clean) ; \
	  done

distclean: clean
	(cd src ; echo "Cleaning directory src..." ; make clean) 

cleandbfiles:
	(cd dict ; $(MAKE) cleandbfiles)

INSTDIRS = bin/$(PLATFORM) dict include lib/$(PLATFORM) lib/wnres man

uninstall:
	@for dir in $(INSTDIRS) ; \
	 do \
		( cd $$dir ; echo "Uninstalling subdirectory $$dir..." ; $(MAKE) WN_ROOT='$(WN_ROOT)' uninstall ) \
	 done
