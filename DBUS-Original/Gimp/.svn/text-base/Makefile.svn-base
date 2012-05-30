# File:
#   Makefile
# Summary:
#   A Makefile for Sam's experiments with GIMP

# +-------+---------------------------------------------------------------------
# | Notes |
# +-------+

# 1. I *think* that in order to query the PDB, one should be running as a
#    plugin (or otherwise within the GIMP framework).  

# 2. I *think* one has to use gimptool-2.0 to build GIMP plugins.  If you
#    need to set extra flags (e.g., for the compiler or linker, you can export
#    LDFLAGS or CFLAGS before calling gimptool.  See the Makefile.am in 
#    DrFu/src/plugins/gimp/ for more details.


# +----------+------------------------------------------------------------------
# | Settings |
# +----------+

UTILS=gimp-2.0

CFLAGS=-g -Wall $(shell pkg-config --cflags $(UTILS))

LDFLAGS=$(shell pkg-config --libs $(UTILS))


# +------------------+----------------------------------------------------------
# | Standard Targets |
# +------------------+

default: ginfo glist

install: ginfo-install glist-install

uninstall: ginfo-uninstall glist-uninstall

clean:
	rm -f *.o

dist-clean: clean
	rm -rf ginfo


# +-------------+---------------------------------------------------------------
# | Experiments |
# +-------------+

# Print out the cflags
.SILENT: cflags
cflags:
	echo CFLAGS=$(CFLAGS)


# Print out the ldflags
.SILENT: ldflags
ldflags:
	echo LDFLAGS=$(LDFLAGS)


# +--------------+--------------------------------------------------------------
# | Applications |
# +--------------+

ginfo: ginfo.o
	gimptool-2.0 --build ginfo.c

ginfo-install: ginfo
	gimptool-2.0 --install-admin-bin $<

ginfo-uninstall: gimptool-2.0 --uninstall-admin-bin ginfo

glist: glist.o
	gimptool-2.0 --build glist.c

glist-install: glist
	gimptool-2.0 --install-admin-bin $<

glist-uninstall: gimptool-2.0 --uninstall-admin-bin glist

