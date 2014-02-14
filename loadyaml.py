import yaml

for d in yaml.load_all(open('izhikevich.yaml')):
    print d
