#!/usr/bin/env python
import sys
import json
import collections
import airspeed
from py2expr import adapt_python_expression as p2e

global LANG

def json2py(somfile):
    with open(somfile) as f:
        m = f.read()
    model = json.JSONDecoder(object_pairs_hook=javalikeHash).decode(m)
    return model

def merge_with_template(model, templfile):
    with open(sys.argv[2]) as f:
        templ = airspeed.Template(f.read())
    return templ.merge(model)

class javalikeHash(collections.OrderedDict):
    def __init__(self, *args):
        global LANG
        adapted_args = ([(el[0], p2e(el[1], LANG))\
                         if isinstance(el[1], basestring) and len(el[1]) > 1\
                         else el \
                         for el in args[0]],)
        super(javalikeHash, self).__init__(*adapted_args)

    def keySet(self):
        return self.keys()
    def size(self):
        return len(self)

if __name__ == '__main__': 
    if 4 != len(sys.argv):
        print "USAGE:", sys.argv[0], "model_definition.json template.vm language"
        sys.exit(1)
    global LANG
    LANG = sys.argv[3]
    m = json2py(sys.argv[1])
    print merge_with_template(m, sys.argv[2])










