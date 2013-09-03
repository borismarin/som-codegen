#!/usr/bin/env python
import sys
import json
import collections
import airspeed
from py2expr import adapt_python_expression as p2e

def json2py(somfile, lang):
    with open(somfile) as f:
        m = f.read()
        model = MyDecoder(language = lang).decode(m)
    return model

def merge_with_template(model, templfile):
    with open(sys.argv[2]) as f:
        templ = airspeed.Template(f.read())
    return templ.merge(model)

class MyDecoder(json.JSONDecoder):


    def __init__(self, language):
        json.JSONDecoder.__init__(self, object_hook=self.dict_to_object)
        self.language = language
        
    def dict_to_object(self, d):
        dd = self.javalikeHash()
        for k, v in d.iteritems():
            #those are not supposed to contain math
            if isinstance(v, basestring) and k not in ['comment', 'name', 'direction']:
                dd[k] = p2e(v, self.language)
            elif isinstance(v, list):
                dd[k] = self.javalikeList(v)
            else:
                dd[k] = v
        return dd        

    class javalikeList(list):
        def size(self):
            return len(self)

    class javalikeHash(collections.OrderedDict):
        def keySet(self):
            return self.keys()
        def size(self):
            return len(self)



if __name__ == '__main__': 
    if 4 != len(sys.argv):
        print "USAGE:", sys.argv[0], "model_definition.json template.vm language"
        sys.exit(1)
    m = json2py(sys.argv[1], sys.argv[3])
    print merge_with_template(m, sys.argv[2])










