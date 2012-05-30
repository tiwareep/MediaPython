#File:
#  Makefile
#Summary
#   A Makefile for the MediaPython '11 project

# +-------+----------------------------------------------------------------------------
# | Notes |
# +-------+

#The purpose of this Makefile is to automate the wrapping of several Gimp procedures made
# available through DBUS in python. The target file wrappers_all.py should be a file containing
# all wrappers(duh) in python, and the target generate creates a file which retrieves all current
#Gimp methods on the DBUS server IF it is running.

# +------------------+----------------------------------------------------------
# | Standard Targets |
# +------------------+

all: wrappers_all.py generate


wrappers_all.py : wrappers_intro.py wrappers_context.py wrappers_image.py wrappers_selection.py wrappers_paint.py wrappers_position.py wrappers_turtle.py wrappers_rgb.py
	cat $^ > $@

generate: generate_from_xml_run.py
	python generate_from_xml_run.py
