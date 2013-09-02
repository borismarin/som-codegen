#!/usr/bin/env python
import sys
import json
import collections
import airspeed
from py2expr import adapt_python_expression as p2e


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
        #adapted_args = [(el[0], p2e(el[1], 'C')) for el in args[0]]
        #adapted_args = ([(el[0], el[1]) for el in args[0]],)
        print [p2e(el[1], 'C') for el in args[0] if isinstance(el[1], basestring)]
        import ipdb; ipdb.set_trace()
    #print args, '\n', adapted_args, '\n\n\n'
        #super(javalikeHash, self).__init__(*adapted_args)
        super(javalikeHash, self).__init__(*args)

    def keySet(self):
        return self.keys()
    def size(self):
        return len(self)

if __name__ == '__main__': 
    if 4 != len(sys.argv):
        print "USAGE:", sys.argv[0], "model_definition.json template.vm language"
        sys.exit(1)
    m = json2py(sys.argv[1])
    # for (k, v) in m.iteritems():
    #     m[k] = p2e(v, sys.argv[3])
    print merge_with_template(m, sys.argv[2])










