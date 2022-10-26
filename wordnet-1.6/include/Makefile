SHELL=/bin/sh

# Makefile for WordNet 1.6 source code header files

WN_ROOT = /usr/local/wordnet1.6
WN_INSTALLDIR = $(WN_ROOT)/include

WN_FILES = license.h setutil.h wn.h wnconsts.h wnglobal.h wnhelp.h wnrtl.h wntypes.h

all: $(WN_FILES)

install: $(WN_FILES)
	@if [ ! -d $(WN_INSTALLDIR) ] ; then \
		echo "Making directory $(WN_INSTALLDIR)" ; \
		mkdir -p $(WN_INSTALLDIR) ; \
		chmod 755 $(WN_INSTALLDIR) ; \
	fi ; 
	@echo "Installing include files in $(WN_INSTALLDIR)"
	@for file in $(WN_FILES) ; \
	 do \
		filename=$(WN_INSTALLDIR)/$$file ; \
		if [ -f $$filename ] ; then \
			echo "Cannot install $$filename: file exists" ; \
		else \
			echo "Installing $$filename" ; \
			cp -p $$file $$filename ; \
		fi ; \
	 done ;
	@echo "Done installing include files in $(WN_INSTALLDIR)"

uninstall:
	@echo "Uninstalling include files from $(WN_INSTALLDIR)"
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
	@echo "Done uninstalling include files from $(WN_INSTALLDIR)"

clean:
	@rm -f *~ "#"*
