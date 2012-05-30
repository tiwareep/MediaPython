import xml.sax.handler

class GetMethodHandler(xml.sax.handler.ContentHandler):
    def __init__(self):
        self.inArg = 0
        self.mapping = {}

    def startElement(self, current, attributes):
        if current == "method":
            self.buffer = ""
            self.method = attributes["name"]
        elif current == "arg":
            self.inArg = 1
    
#right now this just prints newlines but somehow we can make it print parameters if we want.
    #def characters(self, data):
       # if self.inArg:
            #self.buffer += data
 
    def endElement(self, current):
        if current == "arg" or current == "method":
            self.inArg = 0
            self.mapping[self.method] = self.buffer
