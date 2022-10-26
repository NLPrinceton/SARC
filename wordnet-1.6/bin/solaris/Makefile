SHELL=/bin/sh

# Makefile for WordNet 1.6 binaries

WN_ROOT = /usr/local/wordnet1.6
WN_INSTALLDIR = $(WN_ROOT)/bin

WN_FILES = wn wnb wishwn

all: $(WN_FILES)

install: $(WN_FILES)
	@echo "Installing binary files in $(WN_INSTALLDIR)"
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
		fi ; \
	 done ;
	@echo "Done installing binary files in $(WN_INSTALLDIR)"

uninstall:
	@echo "Uninstalling binary files from $(WN_INSTALLDIR)"
	@ for file in $(WN_FILES) ; \
	 do \
		filename=$(WN_INSTALLDIR)/$$file ; \
		if [ ! -f $$filename ] ; then \
			echo "Cannot uninstall $$filename: not present" ; \
		else \
			echo "Uninstalling $$filename" ; \
			rm -f $$filename ; \
		fi ; \
	 done ;
	@echo "Done uninstalling binary files from $(WN_INSTALLDIR)"

clean:
	@rm -f *~ "#"*
