# File:
#   Makefile
# Summary:
#   A Makefile for some example D-Bus files.

# +---------+-------------------------------------------------------------------
# | Globals |
# +---------+

# The utilities that these programs use.  These should be the names that
# pkg-config expects.
UTILS=glib-2.0 gio-unix-2.0 

# The applications we build
APPS=example2 example5 sam0


# +----------+------------------------------------------------------------------
# | Settings |
# +----------+

#-lmcheck
CFLAGS=-g -Wall -lmcheck -DDEBUG -DOBSERVE $(shell pkg-config --cflags $(UTILS))

LDFLAGS=$(shell pkg-config --libs $(UTILS))


# +------------------+----------------------------------------------------------
# | Standard Targets |
# +------------------+

default: $(APPS)

clean:
	rm -f *.o 

distclean: clean
	rm -rf $(APPS) 


# +--------------+--------------------------------------------------------------
# | Applications |
# +--------------+
