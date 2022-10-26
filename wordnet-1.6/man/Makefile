SHELL=/bin/sh

# Makefile for WordNet 1.6 manual pages

WN_ROOT = /usr/local/man
WN_INSTALLDIR = $(WN_ROOT)/man

WN_FILES =
MAN1_INSTALLDIR = $(WN_INSTALLDIR)/man1
MAN3_INSTALLDIR = $(WN_INSTALLDIR)/man3
MAN5_INSTALLDIR = $(WN_INSTALLDIR)/man5
MAN7_INSTALLDIR = $(WN_INSTALLDIR)/man7
MAN1_FILES = wn.1 wnb.1 wnintro.1
MAN3_FILES = binsrch.3 morph.3 wnintro.3 wnsearch.3 wnutil.3
MAN5_FILES = cntlist.5 glossidx.5 lexnames.5 senseidx.5 taglist.5 wndb.5 wninput.5 wnintro.5
MAN7_FILES = morphy.7 uniqbeg.7 wngloss.7 wngroups.7 wnintro.7 wnlicens.7 wnpkgs.7 wnstats.7

all install install-man:
	@for dir in $(MAN1_INSTALLDIR) $(MAN3_INSTALLDIR) $(MAN5_INSTALLDIR) $(MAN7_INSTALLDIR) ; \
	  do \
		if [ ! -d $$dir ] ; then \
			echo "Making directory $$dir" ; \
			mkdir -p $$dir ; \
			chmod 755 $$dir ; \
		fi ; \
	  done ;
	@echo "Installing man pages in $(WN_INSTALLDIR)"
	@$(MAKE) -k WN_INSTALLDIR='$(MAN1_INSTALLDIR)' WN_FILES='$(MAN1_FILES)' doinstall
	@$(MAKE) -k WN_INSTALLDIR='$(MAN3_INSTALLDIR)' WN_FILES='$(MAN3_FILES)' doinstall
	@$(MAKE) -k WN_INSTALLDIR='$(MAN5_INSTALLDIR)' WN_FILES='$(MAN5_FILES)' doinstall
	@$(MAKE) -k WN_INSTALLDIR='$(MAN7_INSTALLDIR)' WN_FILES='$(MAN7_FILES)' doinstall
	@echo "Done installing man pages in $(WN_INSTALLDIR)"

doinstall:
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

uninstall:
	@echo "Uninstalling man pages from $(WN_INSTALLDIR)"
	@$(MAKE) -k WN_INSTALLDIR='$(MAN1_INSTALLDIR)' WN_FILES='$(MAN1_FILES)' douninstall
	@$(MAKE) -k WN_INSTALLDIR='$(MAN3_INSTALLDIR)' WN_FILES='$(MAN3_FILES)' douninstall
	@$(MAKE) -k WN_INSTALLDIR='$(MAN5_INSTALLDIR)' WN_FILES='$(MAN5_FILES)' douninstall
	@$(MAKE) -k WN_INSTALLDIR='$(MAN7_INSTALLDIR)' WN_FILES='$(MAN7_FILES)' douninstall
	@echo "Done uninstalling man pages from $(WN_INSTALLDIR)"

douninstall:
	@for file in $(WN_FILES) ; \
	 do \
		filename=$(WN_INSTALLDIR)/$$file ; \
		if [ ! -f $$filename ] ; then \
			echo "Cannot uninstall $$filename: file not present" ; \
		else \
			echo "Uninstalling $$filename" ; \
			rm -f $$filename ; \
		fi ; \
	 done ;

clean:
	@rm -f *~ "#"*

psfiles: 
	@for file in $(WN_FILES) ; \
	 do \
		tbl $$file | ptroff -man -t >ps/$${file}ps ; \
	 done ;

catfiles: 
	@for file in $(WN_FILES) ; \
	 do \
		tbl $$file | nroff -man >cat/$${file}lp ; \
	 done ;

