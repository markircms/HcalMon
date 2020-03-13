import subprocess
import sys
import socket
import optparse
import os
import re
import fnmatch
import json
from RunRuntype import *

Runtypes = ["HBped1","HBped6","HBled1","HBled6","HEped1","HEped6","HEled1","HEled6","HBloled","HEloled","HFped","HFled","HOled","HOped","Multiloled","Multiped1","Multiled1","Meltiped6","Multiled6"]


parser = optparse.OptionParser()
parser.add_option('-r', dest="Runtype", default=None, help="Runtype to process")
parser.add_option('--all', dest="all", default=False, help="Reanalyze all runs")
parser.add_option('--run', dest="run", type=int,  default =None, help="Run number to process if you want to analyze one run")
options, args = parser.parse_args()


if options.Runtype not in Runtypes:
    sys.exit("Unknown runtype, see runtypes list")

with open('runtypes.json') as f:
    datart = json.load(f)

dataRT = datart.get("runtypes")

if (options.Runtype == "HBped1"):
    HB_ped1(dataRT,options.all)
if (options.Runtype == "HBped6"):
    HB_ped6(dataRT,options.all)
if (options.Runtype == "HEped1"):
    HE_ped1(dataRT,options.all)
if (options.Runtype == "HBped6"):
    HE_ped6(dataRT,options.all)
if (options.Runtype == "HBled1"):
    HB_led1(dataRT,options.all)
if (options.Runtype == "HBled6"):
    HB_led6(dataRT,options.all)
if (options.Runtype == "HEled1"):
    HE_led1(dataRT,options.all)
if (options.Runtype == "HEled6"):
    HE_led6(dataRT,options.all)
if (options.Runtype == "HEloled"):
    HE_loled(dataRT,options.all)
if (options.Runtype == "HBloled"):
    HB_loled(dataRT,options.all)
if (options.Runtype == "Multiloled"):
    Multi_loled(dataRT,options.all)
if (options.Runtype == "Multiled1"):
    Multi_led1(dataRT,options.all)
if (options.Runtype == "Multiped1"):
    Multi_ped1(dataRT,options.all)
if (options.Runtype == "Multiled6"):
    Multi_led6(dataRT,options.all)
if (options.Runtype == "Multiped6"):
    Multi_ped6(dataRT,options.all)
