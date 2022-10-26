SHELL=/bin/sh

# Top level Makefile for WordNet 1.6 binaries
# Doesn't do much since platform specific version is called from
# top level installation Makefile

SUBDIRS=irix linux solaris sunos

clean::
	@for dir in $(SUBDIRS) ; \
	do \
	(cd $$dir; echo "Cleaning subdirectory $$dir"; $(MAKE) clean) ; \
	done

clean::
	@rm -f *~ "#"*
