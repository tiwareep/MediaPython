#A MediaPython implementation of a handy XML parser that reads takes all available GIMP methods
#on the DBUS server and generates a file that retrieves them using python. Also provides a handy
#list of all available methods in a seperate file.

#---------------------------------------------------------------------------------------------
#Import useful python libraries for XML parsing  

import xml.sax
import generate_from_xml
import pprint
import string

#---------------------------------------------------------------------------------------------
#Prepares some parsing variables

parser = xml.sax.make_parser(  )
handler = generate_from_xml.GetMethodHandler(  )
parser.setContentHandler(handler)
parser.parse("../DBUS/glim-gimpbus.xml")
#pprint.pprint(handler.mapping)
winner = handler.mapping

#-----------------------------------------------------------------------------------------------
#Create file with list of methods
filename = "func_list_from_xml.py"
file = open(filename, 'w+')
for line in winner:
    file.write(line)
    file.write("\n")
file.close()

arr = []
input = open("func_list_from_xml.py", 'r')
for line in input.readlines():
    arr.append(line)
arr2 = map(string.strip, arr)

#-----------------------------------------------------------------------------------------------
# Create file to retrieve methods from DBUS in python
gen_file = "get_dbus_methods_python.py"
file = open(gen_file, 'w+')
file.write("#! /usr/bin/env python\n\n#THIS IS A GENERATED FILE. DO NOT EDIT.\n\nimport dbus\nbus = dbus.SessionBus()\ngimpbus = bus.get_object('edu.grinnell.glimmer.gimpbus', '/edu/grinnell/glimmer/gimpbus')\n\n")
file.write("ADD=0\nSUBTRACT=1\nREPLACE=2\nINTERSECT=3\n\n")
for line in arr2:
    file.write(line)
    file.write(" = gimpbus.get_dbus_method('")
    file.write(line)
    file.write("', 'edu.grinnell.glimmer.gimpbus')\n\n")


