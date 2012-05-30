# File:
#   Makefile
# Summary:
#   A Makefile for Sam's experiments with D-Bus

# +-------+---------------------------------------------------------------------
# | Notes |
# +-------+

# We use dbus (duh), dbus-glib, glib, and gtk.  (gtk provides the event loop
# that keeps everything running).  gtk seems to require cairo pango and atk.
# I ended up rewriting the definitions of CFLAGS to use pkg-config, but left
# the old versions around to help novices understand.


# +---------+-------------------------------------------------------------------
# | Globals |
# +---------+

# The utilities that these programs use.  These should be the names that
# pkg-config expects.
UTILS=dbus-glib-1 gtk+-2.0 gimp-2.0

# The applications we build
APPS=counter-service counter-service-0 counter-factory dbe

# The plugins we build
PLUGINS=gimpbus

# The libraries we build
LIBRARIES=libglimdbus.a libgimpbus.a


# +----------+------------------------------------------------------------------
# | Settings |
# +----------+

OLD_CFLAGS=-g -Wall -I/usr/include/dbus-1.0 -I/usr/lib/dbus-1.0/include -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/gtk-2.0 -I/usr/lib/gtk-2.0/include -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/atk-1.0

CFLAGS=-g -Wall -DDEBUG $(shell pkg-config --cflags $(UTILS))

OLD_LDFLAGS=-L/usr/lib -ldbus-1 -ldbus-glib-1 -lglib-2.0  -lgtk-x11-2.0

LDFLAGS=$(shell pkg-config --libs $(UTILS))


# +------------------+----------------------------------------------------------
# | Standard Targets |
# +------------------+

default: gimpbus

clean:
	rm -f *.o 

distclean: clean
	rm -rf $(APPS) $(PLUGINS) $(LIBRARIES) *glue.h *server.h *temp.h *client.h

plugins: gimpbus

install: gimpbus-install

uninstall: gimpbus-uninstall


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

dbe: dbe.o glim-dbe.o glim-dbus.o
	$(LINK.o) -o $@ $^

counter-service-0: counter-service-0.o glim-counter.o
	$(LINK.o) -o $@ $^

counter-service: counter-service.o glim-counter.o glim-dbus.o
	$(LINK.o) -o $@ $^

counter-factory: counter-factory.o glim-counter-factory.o glim-counter.o glim-dbus.o
	$(LINK.o) -o $@ $^


# +-----------+-----------------------------------------------------------------
# | Libraries |
# +-----------+

libglimdbus.a: glim-dbus.o
	ar -r $@ $^
	ranlib $@

libgimpbus.a: glim-gimpbus.o
	ar -r $@ $^
	ranlib $@


# +--------------+--------------------------------------------------------------
# | Gimp Plugins |
# +--------------+

gimpbus: gimpbus.c libglimdbus.a libgimpbus.a
	export CFLAGS="$(CFLAGS)"; \
	export LDFLAGS="$(LDFLAGS) -L. -lglimdbus -lgimpbus"; \
	gimptool-2.0 --build gimpbus.c

gimpbus-install: gimpbus
	gimptool-2.0 --install-admin-bin $<

gimpbus-uninstall:
	gimptool-2.0 --uninstall-admin-bin gimpbus


# +------------+----------------------------------------------------------------
# | D-Bus Glue |
# +------------+

glim-counter-glue.h: glim-counter.xml 
	dbus-binding-tool --mode=glib-server --prefix=glim_counter $< > $@

glim-counter-factory-glue.h: glim-counter-factory.xml 
	dbus-binding-tool --mode=glib-server --prefix=glim_counter_factory $< > $@

glim-gimpbus-server.h: glim-gimpbus.xml
	dbus-binding-tool --mode=glib-server --prefix=glim_gimpbus $< > $@

glim-gimpbus-client.h: glim-gimpbus-tmp.h
	sed -e 's/edu_grinnell_glimmer/glim/g' < $< > $@

glim-gimpbus-tmp.h: glim-gimpbus.xml
	dbus-binding-tool --prefix=glim_gimpbus --mode=glib-client $< > $@

glim-dbe-server.h: glim-dbe.xml
	dbus-binding-tool --mode=glib-server --prefix=glim_dbe $< > $@


# +---------+-------------------------------------------------------------------
# | Headers |
# +---------+

# Dependencies
glim-counter.o: glim-counter.h glim-counter-glue.h
counter-service.o: glim-counter.h glim-dbus.h
counter-service-0.o: glim-counter.h 

glim-counter-factory.o: glim-counter-factory.h glim-counter-factory-glue.h glim-counter.h
counter-factory.o: glim-counter-factory.h glim-dbus.h

glim-gimpbus.o: glim-gimpbus-server.h

glim-dbe.o: glim-dbe-server.h

glim-gimpbus.o: glim-debug.h
glim-dbus.o: glim-debug.h
