#!/usr/bin/env python
import sys
import collections

class kludgeDict(collections.OrderedDict):
    def keySet(self):
        return self.keys()

def py2m(model, templatefile):
    import airspeed
    with open(templatefile) as f:
        templ = airspeed.Template(f.read())
    return templ.merge(model)


def eco2py(modelfile):
    import json
    with open(modelfile) as f:
        m = f.read()
    return json.JSONDecoder(object_pairs_hook=kludgeDict).decode(m)



if __name__ == "__main__": 

    try: 
        m = eco2py(sys.argv[1])
        print py2m(m, sys.argv[2])
        
    except: 
        print "USAGE:", sys.argv[0], "model_definition.json" "template.vm"
        sys.exit(1)
    











