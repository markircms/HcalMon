import subprocess
import sys
import socket
import optparse
import os
import re
import fnmatch
import json

Runtypes = ["HBped1","HBped6","HBled1","HBled6","HEped1","HEped6","HEled1","HEled6","HBloled","HEloled","HFped","HFled","HOled","HOped","Multiloled","Multiped1","Multiled1","Meltiped6","Multiled6"]


parser = optparse.OptionParser()
parser.add_option('-r', dest="Runtype", default=None, help="Runtype to process")
parser.add_option('--all', dest="all", action="store_true", default=False, help="Reanalyze all runs")
parser.add_option('--evr', dest="evr", action="store_true", default=False, help="Analyze all runtypes")
parser.add_option('--run', dest="run", type=int,  default =None, help="Run number to process if you want to analyze one run")
options, args = parser.parse_args()

if ((options.Runtype not in Runtypes) and (options.Runtype != None)):
    sys.exit("Unknown runtype, see runtypes list")

with open('Runs.json') as f:
    datart = json.load(f)

dataRT = datart.get("runs")

for datarun in dataRT:
 for line in datarun.keys():
    runtype = datarun[line].get("runtype")
    seq =  datarun[line].get("seq")
    time =  datarun[line].get("time")
    if (options.evr == True):
        if (runtype == "HBHE_ped_Gsel0"):
            if (options.all == True or not os.path.isfile("Runs/HBped1/run"+str(line)+".root")):
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HBped1",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
            else:
                continue
            if (options.all == True or not os.path.isfile("Runs/HEped1/run"+str(line)+".root")):
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HEped1",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
            else:
                continue
        if (runtype == "HBHE_ped"):
            if (options.all == True or not os.path.isfile("Runs/HBped6/run"+str(line)+".root")):
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HBped6",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
            else:
                continue
            if (options.all == True or not os.path.isfile("Runs/HEped6/run"+str(line)+".root")):
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HEped6",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
            else:
                continue
        if (runtype == "HBHE_led_Gsel0"):
            if (options.all == True or not os.path.isfile("Runs/HBled1/run"+str(line)+".root")):
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HBled1",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
            else:
                continue
            if (options.all == True or not os.path.isfile("Runs/HEled1/run"+str(line)+".root")):
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HEled1",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
            else:
                continue
        if (runtype == "HBHE_led"):
            if (options.all == True or not os.path.isfile("Runs/HBled6/run"+str(line)+".root")):
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HBled6",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
            else:
                continue
            if (options.all == True or not os.path.isfile("Runs/HEled6/run"+str(line)+".root")):
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HEled6",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
            else:
                continue
        if (runtype == "HBHE_led-low-intensity-Gsel0"):
            if (options.all == True or not os.path.isfile("Runs/HBloled/run"+str(line)+".root")):
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HBloled",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
            else:
                continue
            if (options.all == True or not os.path.isfile("Runs/HEloled/run"+str(line)+".root")):
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HEloled",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
            else:
                continue
        if (runtype == "Multi_led-ped-Gsel-bv-sequence"):
            if (options.all == True or not os.path.isfile("Runs/HBloled/run"+str(line)+".root")):
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HBloled",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
            else:
                continue
            if (options.all == True or not os.path.isfile("Runs/HEloled/run"+str(line)+".root")):
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HEloled",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
            else:
                continue
            if (options.all == True or not os.path.isfile("Runs/HBled6/run"+str(line)+".root")):
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HBled6",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
            else:
                continue
            if (options.all == True or not os.path.isfile("Runs/HEled6/run"+str(line)+".root")):
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HEled6",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
            else:
                continue
            if (options.all == True or not os.path.isfile("Runs/HBled1/run"+str(line)+".root")):
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HBled1",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
            else:
                continue
            if (options.all == True or not os.path.isfile("Runs/HEled1/run"+str(line)+".root")):
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HEled1",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
            else:
                continue
            if (options.all == True or not os.path.isfile("Runs/HBped1/run"+str(line)+".root")):
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HBped1",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
            else:
                continue
            if (options.all == True or not os.path.isfile("Runs/HEped1/run"+str(line)+".root")):
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HEped1",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
            else:
                continue
            if (options.all == True or not os.path.isfile("Runs/Multiped1/run"+str(line)+".root")):
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","Multiped1",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
            else:
                continue
            if (options.all == True or not os.path.isfile("Runs/Multiled1/run"+str(line)+".root")):
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","Multiled1",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
            else:
                continue
            if (options.all == True or not os.path.isfile("Runs/Multiped6/run"+str(line)+".root")):
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","Multiped6",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
            else:
                continue
            if (options.all == True or not os.path.isfile("Runs/Multiled6/run"+str(line)+".root")):
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","Multiled6",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
            else:
                continue
            if (options.all == True or not os.path.isfile("Runs/Multiloled/run"+str(line)+".root")):
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","Multiloled6",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
            else:
                continue
    else:
        if (options.Runtype == "HBped1"):
            if (runtype == "HBHE_ped_Gsel0"):
                if (options.all == True or not os.path.isfile("Runs/HBped1/run"+str(line)+".root")):
                    p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HBped1",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    output = p.communicate(b'\n')[1]
                else:
                    continue
            if (runtype == "Multi_led-ped-Gsel-bv-sequence"):
                if (options.all == True or not os.path.isfile("Runs/HBped1/run"+str(line)+".root")):
                    p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HBped1",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    output = p.communicate(b'\n')[1]
                else:
                    continue
        if (options.Runtype == "HBped6"):
            if (runtype == "HBHE_ped"):
                if (options.all == True or not os.path.isfile("Runs/HBped6/run"+str(line)+".root")):
                    p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HBped6",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    output = p.communicate(b'\n')[1]
                else:
                    continue
            if (runtype == "Multi_led-ped-Gsel-bv-sequence"):
                if (options.all == True or not os.path.isfile("Runs/HBped6/run"+str(line)+".root")):
                    p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HBped6",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    output = p.communicate(b'\n')[1]
                else:
                    continue
        if (options.Runtype == "HBled1"):
            if (runtype == "HBHE_led_Gsel0"):
                if (options.all == True or not os.path.isfile("Runs/HBled1/run"+str(line)+".root")):
                    p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HBled1",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    output = p.communicate(b'\n')[1]
                else:
                    continue
            if (runtype == "Multi_led-ped-Gsel-bv-sequence"):
                if (options.all == True or not os.path.isfile("Runs/HBled1/run"+str(line)+".root")):
                    p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HBled1",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    output = p.communicate(b'\n')[1]
                else:
                    continue
        if (options.Runtype == "HBled6"):
            if (runtype == "HBHE_led"):
                if (options.all == True or not os.path.isfile("Runs/HBled6/run"+str(line)+".root")):
                    p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HBled6",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    output = p.communicate(b'\n')[1]
                else:
                    continue
            if (runtype == "Multi_led-ped-Gsel-bv-sequence"):
                if (options.all == True or not os.path.isfile("Runs/HBled6/run"+str(line)+".root")):
                    p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HBled6",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    output = p.communicate(b'\n')[1]
                else:
                    continue
        if (options.Runtype == "HEped1"):
            if (runtype == "HBHE_ped_Gsel0"):
                if (options.all == True or not os.path.isfile("Runs/HEped1/run"+str(line)+".root")):
                    p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HEped1",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    output = p.communicate(b'\n')[1]
                else:
                    continue
            if (runtype == "Multi_led-ped-Gsel-bv-sequence"):
                if (options.all == True or not os.path.isfile("Runs/HEped1/run"+str(line)+".root")):
                    p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HEped1",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    output = p.communicate(b'\n')[1]
                else:
                    continue
        if (options.Runtype == "HEped6"):
            if (runtype == "HBHE_ped"):
                if (options.all == True or not os.path.isfile("Runs/HEped6/run"+str(line)+".root")):
                    p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HEped6",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    output = p.communicate(b'\n')[1]
                else:
                    continue
            if (runtype == "Multi_led-ped-Gsel-bv-sequence"):
                if (options.all == True or not os.path.isfile("Runs/HEped6/run"+str(line)+".root")):
                    p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HEped6",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    output = p.communicate(b'\n')[1]
                else:
                    continue
        if (options.Runtype == "HEled1"):
            if (runtype == "HBHE_led_Gsel0"):
                if (options.all == True or not os.path.isfile("Runs/HEled1/run"+str(line)+".root")):
                    p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HEled1",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    output = p.communicate(b'\n')[1]
                else:
                    continue
            if (runtype == "Multi_led-ped-Gsel-bv-sequence"):
                if (options.all == True or not os.path.isfile("Runs/HEled1/run"+str(line)+".root")):
                    p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HEled1",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    output = p.communicate(b'\n')[1]
                else:
                    continue
        if (options.Runtype == "HEled6"):
            if (runtype == "HBHE_led"):
                if (options.all == True or not os.path.isfile("Runs/HEled6/run"+str(line)+".root")):
                    p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HEled6",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    output = p.communicate(b'\n')[1]
                else:
                    continue
            if (runtype == "Multi_led-ped-Gsel-bv-sequence"):
                if (options.all == True or not os.path.isfile("Runs/HEled6/run"+str(line)+".root")):
                    p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HEled6",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    output = p.communicate(b'\n')[1]
                else:
                    continue
        if (options.Runtype == "HBloled"):
            if (runtype == "HBHE_led-low-intensity-Gsel0"):
                if (options.all == True or not os.path.isfile("Runs/HBloled/run"+str(line)+".root")):
                    p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HBloled",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    output = p.communicate(b'\n')[1]
                else:
                    continue
            if (runtype == "Multi_led-ped-Gsel-bv-sequence"):
                if (options.all == True or not os.path.isfile("Runs/HBloled/run"+str(line)+".root")):
                    p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HBloled",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    output = p.communicate(b'\n')[1]
                else:
                    continue
        if (options.Runtype == "HEloled"):
            if (runtype == "HBHE_led-low-intensity-Gsel0"):
                if (options.all == True or not os.path.isfile("Runs/HEloled/run"+str(line)+".root")):
                    p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HEloled",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    output = p.communicate(b'\n')[1]
                else:
                    continue
            if (runtype == "Multi_led-ped-Gsel-bv-sequence"):
                if (options.all == True or not os.path.isfile("Runs/HEloled/run"+str(line)+".root")):
                    p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","HEloled",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    output = p.communicate(b'\n')[1]
                else:
                    continue
        if (options.Runtype == "Multiled1"):
            if (runtype == "Multi_led-ped-Gsel-bv-sequence"):
                if (options.all == True or not os.path.isfile("Runs/Multiled1/run"+str(line)+".root")):
#                    p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","Multiled1",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
#                    output = p.communicate(b'\n')[1]
                    p = subprocess.call(["cmsRun", "localRunAnalyzerRun.py","Multiled1",str(line),str(seq)])
                else:
                    continue
        if (options.Runtype == "Multiled6"):
            if (runtype == "Multi_led-ped-Gsel-bv-sequence"):
                if (options.all == True or not os.path.isfile("Runs/Multiled6/run"+str(line)+".root")):
                    p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","Multiled6",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    output = p.communicate(b'\n')[1]
                else:
                    continue
        if (options.Runtype == "Multiloled"):
            if (runtype == "Multi_led-ped-Gsel-bv-sequence"):
                if (options.all == True or not os.path.isfile("Runs/Multiloled/run"+str(line)+".root")):
#                    p = subprocess.Popen(["cmsRun", "localRunAnalyzerRun.py","Multiloled",str(line),str(seq)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
#                    output = p.communicate(b'\n')[1]
                    p = subprocess.call(["cmsRun", "localRunAnalyzerRun.py","Multiloled",str(line),str(seq)])
                else:
                    continue
