import sys
import os
import re
import fnmatch
import json

with open('runtypes.json') as f:
    datart1 = json.load(f)

dict = {}
datart = datart1.get("runtypes")
for line in datart:
    for line1 in line.keys():
#        print line[line1]
        vectRN = line[line1].get("runnumber")
        evnum = line[line1].get("eventnumber")
        masks = line[line1].get("masks")
        for line2 in vectRN:
            dict2 = {}
            dict2["runtype"] = line1
            dict2["eventnumber"] = evnum
            dict2["masks"] = masks
            dict[line2] = dict2

with open('result.json', 'w') as fp:
    json.dump(dict, fp,indent=2)
]
