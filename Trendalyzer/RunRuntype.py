import subprocess
import sys
import socket
import optparse
import os
import re
import fnmatch
import json

runsHBped1 = [];
runsHBped6 = [];
runsHBled1 = [];
runsHBled6 = [];
runsHEped1 = [];
runsHEped6 = [];
runsHEled1 = [];
runsHEled6 = [];
runsHBloled = [];
runsHBloled = [];

def HB_ped1(data_,all):
    for line in data_:
        if line.get("HBHE_ped_Gsel0"):
            dataHBped1 = line.get("HBHE_ped_Gsel0")
            runsHBped1 = dataHBped1.get("runnumber")
            for line1 in runsHBped1:
# check whether
                if (os.path.isfile("Runs/HBped1/run"+str(line1)+".root") and not all):
                    continue
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerT.py","HBped1",str(line1),str(0)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
                print output
        if line.get("Multi_led-ped-Gsel-bv-sequence"):
            dataHBped1 = line.get("Multi_led-ped-Gsel-bv-sequence")
            runsHBped1 = dataHBped1.get("runnumber")
            for line1 in runsHBped1:
                if (os.path.isfile("Runs/HBped1/run"+str(line1)+".root") and not all):
                    continue
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerT.py","HBped1",str(line1),str(1)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
                print output

def HB_ped6(data_,all):
    for line in data_:
        if line.get("HBHE_ped"):
            dataHBped6 = line.get("HBHE_ped")
            runsHBped6 = dataHBped6.get("runnumber")
            for line1 in runsHBped6:
# check whether
                if (os.path.isfile("Runs/HBped6/run"+str(line1)+".root") and not all):
                    continue
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerT.py","HBped6",str(line1),str(0)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
                print output
        if line.get("Multi_led-ped-Gsel-bv-sequence"):
            dataHBped6 = line.get("Multi_led-ped-Gsel-bv-sequence")
            runsHBped6 = dataHBped6.get("runnumber")
            for line1 in runsHBped6:
                if (os.path.isfile("Runs/HEped1/run"+str(line1)+".root") and not all):
                    continue
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerT.py","HEped1",str(line1),str(1)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
                print output

def HE_ped1(data_,all):
    for line in data_:
        if line.get("HBHE_ped_Gsel0"):
            dataHEped1 = line.get("HBHE_ped_Gsel0")
            runsHEped1 = dataHEped1.get("runnumber")
            for line1 in runsHEped1:
# check whether
                if (os.path.isfile("Runs/HEped1/run"+"HEped1"+str(line1)+".root") and not all):
                    continue
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerT.py","HEped1",str(line1),str(0)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
                print output
        if line.get("Multi_led-ped-Gsel-bv-sequence"):
            dataHEped1 = line.get("Multi_led-ped-Gsel-bv-sequence")
            runsHEped1 = dataHEped1.get("runnumber")
            for line1 in runsHEped1:
                if (os.path.isfile("Runs/HEped1/run"+str(line1)+".root") and not all):
                    continue
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerT.py","HEped1",str(line1),str(1)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
                print output

def HE_ped6(data_,all):
    for line in data_:
        if line.get("HBHE_ped"):
            dataHEped1 = line.get("HBHE_ped")
            runsHEped1 = dataHEped1.get("runnumber")
            for line1 in runsHEped1:
# check whether
                if (os.path.isfile("Runs/HEped6/run"+str(line1)+".root") and not all):
                    continue
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerT.py","HEped6",str(line1),str(0)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
                print output
        if line.get("Multi_led-ped-Gsel-bv-sequence"):
            dataHEped1 = line.get("Multi_led-ped-Gsel-bv-sequence")
            runsHEped1 = dataHEped1.get("runnumber")
            for line1 in runsHEped1:
                if (os.path.isfile("Runs/HEped6/run"+str(line1)+".root") and not all):
                    continue
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerT.py","HEped6",str(line1),str(1)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
                print output

def HE_led1(data_,all):
    for line in data_:
        if line.get("HBHE_led_Gsel0"):
            dataHEled1 = line.get("HBHE_led_Gsel0")
            runsHEled1 = dataHEled1.get("runnumber")
            for line1 in runsHEled1:
# check whether
                if (os.path.isfile("Runs/HEled1/run"+str(line1)+".root") and not all):
                    continue
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerT.py","HEled1",str(line1),str(0)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
                print output
        if line.get("Multi_led-ped-Gsel-bv-sequence"):
            dataHEled1 = line.get("Multi_led-ped-Gsel-bv-sequence")
            runsHEled1 = dataHEled1.get("runnumber")
            for line1 in runsHEled1:
                if (os.path.isfile("Runs/HEled1/run"+str(line1)+".root") and not all):
                    continue
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerT.py","HEled1",str(line1),str(1)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
                print output

def HE_led6(data_,all):
    for line in data_:
        if line.get("HBHE_led"):
            dataHEled6 = line.get("HBHE_led")
            runsHEled6 = dataHEled6.get("runnumber")
            for line1 in runsHEled6:
# check whether
                if (os.path.isfile("Runs/HEled6/run"+str(line1)+".root") and not all):
                    continue
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerT.py","HEled6",str(line1),str(0)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
                print output
        if line.get("Multi_led-ped-Gsel-bv-sequence"):
            dataHEled6 = line.get("Multi_led-ped-Gsel-bv-sequence")
            runsHEled6 = dataHEled6.get("runnumber")
            for line1 in runsHEled6:
                if (os.path.isfile("Runs/HEled6/run"+str(line1)+".root") and not all):
                    continue
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerT.py","HEled6",str(line1),str(1)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
                print output

def HB_led1(data_,all):
    for line in data_:
        if line.get("HBHE_led_Gsel0"):
            dataHBled1 = line.get("HBHE_led_Gsel0")
            runsHBled1 = dataHBled1.get("runnumber")
            for line1 in runsHBled1:
                if (os.path.isfile("Runs/HBled1/run"+str(line1)+".root") and not all):
                    continue
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerT.py","HBled1",str(line1),str(0)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
                print output
        if line.get("Multi_led-ped-Gsel-bv-sequence"):
            dataHBled1 = line.get("Multi_led-ped-Gsel-bv-sequence")
            runsHBled1 = dataHBled1.get("runnumber")
            for line1 in runsHBled1:
                if (os.path.isfile("Runs/HBled1/run"+str(line1)+".root") and not all):
                    continue
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerT.py","HBled1",str(line1),str(1)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
                print output

def HB_led6(data_,all):
    for line in data_:
        if line.get("HBHE_led"):
            dataHBled6 = line.get("HBHE_led")
            runsHBled6 = dataHBled6.get("runnumber")
            for line1 in runsHBled6:
                if (os.path.isfile("Runs/HBled6/run"+str(line1)+".root") and not all):
                    continue
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerT.py","HBled6",str(line1),str(0)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
                print output
        if line.get("Multi_led-ped-Gsel-bv-sequence"):
            dataHBled6 = line.get("Multi_led-ped-Gsel-bv-sequence")
            runsHBled6 = dataHBled6.get("runnumber")
            for line1 in runsHBled6:
                if (os.path.isfile("Runs/HBled6/run"+str(line1)+".root") and not all):
                    continue
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerT.py","HBled6",str(line1),str(1)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
                print output
def HE_loled(data_,all):
    for line in data_:
        if line.get("HBHE_led-low-intensity-Gsel0"):
            dataHEloled = line.get("HBHE_led-low-intensity-Gsel0")
            runsHEloled = dataHEloled.get("runnumber")
            for line1 in runsHEloled:
                if (os.path.isfile("Runs/HEloled/run"+str(line1)+".root") and not all):
                    continue
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerT.py","HEloled",str(line1),str(0)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
                print output
        if line.get("Multi_led-ped-Gsel-bv-sequence"):
            dataHEloled = line.get("Multi_led-ped-Gsel-bv-sequence")
            runsHEloled = dataHEloled.get("runnumber")
            for line1 in runsHEloled:
                if (os.path.isfile("Runs/HEloled/run"+str(line1)+".root") and not all):
                    continue
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerT.py","HEloled",str(line1),str(1)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
                print output

def HB_loled(data_,all):
#    dataHBped1 = data_.get("HBHE_ped_Gsel0")
    for line in data_:
        if line.get("HBHE_led-low-intensity-Gsel0"):
            dataHBloled = line.get("HBHE_led-low-intensity-Gsel0")
            runsHBloled = dataHBloled.get("runnumber")
            for line1 in runsHBloled:
# check whether file is in folder
                if (os.path.isfile("Runs/HBloled/run"+str(line1)+".root") and not all):
                    continue
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerT.py","HBloled",str(line1),str(0)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
                print output
        if line.get("Multi_led-ped-Gsel-bv-sequence"):
            dataHBloled = line.get("Multi_led-ped-Gsel-bv-sequence")
            runsHBloled = dataHBloled.get("runnumber")
            for line1 in runsHBloled:
                if (os.path.isfile("Runs/HBloled/run"+str(line1)+".root") and not all):
                    continue
                p = subprocess.Popen(["cmsRun", "localRunAnalyzerT.py","HBloled",str(line1),str(1)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output = p.communicate(b'\n')[1]
                print output
def Multi_loled(data_,all):
        for line in data_:
            if line.get("Multi_led-ped-Gsel-bv-sequence"):
                dataMultiloled = line.get("Multi_led-ped-Gsel-bv-sequence")
                runsMultiloled = dataMultiloled.get("runnumber")
                for line1 in runsMultiloled1:
                    if (os.path.isfile("Runs/Multiloled/run"+str(line1)+".root") and not all):
                        continue
                    p = subprocess.Popen(["cmsRun", "localRunAnalyzerT.py","Multiloled",str(line1),str(1)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    output = p.communicate(b'\n')[1]
                    print output
def Multi_ped1(data_,all):
        for line in data_:
            if line.get("Multi_led-ped-Gsel-bv-sequence"):
                dataMultiped1 = line.get("Multi_led-ped-Gsel-bv-sequence")
                runsMultiped1 = dataMultiped1.get("runnumber")
                for line1 in runsMultiped1:
                    if (os.path.isfile("Runs/Multiped1/run"+str(line1)+".root") and not all):
                        continue
                    p = subprocess.Popen(["cmsRun", "localRunAnalyzerT.py","Multiped1",str(line1),str(1)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    output = p.communicate(b'\n')[1]
                    print output
def Multi_led1(data_,all):
        for line in data_:
            if line.get("Multi_led-ped-Gsel-bv-sequence"):
                dataMultiled1 = line.get("Multi_led-ped-Gsel-bv-sequence")
                runsMultiled1 = dataMultiled1.get("runnumber")
                for line1 in runsMultiled1:
                    if (os.path.isfile("Runs/Multiled1/run"+str(line1)+".root") and not all):
                        continue
                    p = subprocess.Popen(["cmsRun", "localRunAnalyzerT.py","Multiled1",str(line1),str(1)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    output = p.communicate(b'\n')[1]
                    print output
#                    subprocess.check_call(["cmsRun", "localRunAnalyzerT.py","Multiled1",str(line1),str(1)])
def Multi_ped6(data_,all):
        for line in data_:
            if line.get("Multi_led-ped-Gsel-bv-sequence"):
                dataMultiped6 = line.get("Multi_led-ped-Gsel-bv-sequence")
                runsMultiped6 = dataMultiped6.get("runnumber")
                for line1 in runsMultiped6:
                    if (os.path.isfile("Runs/Multiped6/run"+str(line1)+".root") and not all):
                        continue
                    p = subprocess.Popen(["cmsRun", "localRunAnalyzerT.py","Multiped6",str(line1),str(1)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    output = p.communicate(b'\n')[1]
                    print output
def Multi_led6(data_,all):
        for line in data_:
            if line.get("Multi_led-ped-Gsel-bv-sequence"):
                dataMultiled6 = line.get("Multi_led-ped-Gsel-bv-sequence")
                runsMultiled6 = dataMultiled6.get("runnumber")
                for line1 in runsMultiled6:
                    if (os.path.isfile("Runs/Multiled6/run"+str(line1)+".root") and not all):
                        continue
                    p = subprocess.Popen(["cmsRun", "localRunAnalyzerT.py","Multiled6",str(line1),str(1)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    output = p.communicate(b'\n')[1]
                    print output
