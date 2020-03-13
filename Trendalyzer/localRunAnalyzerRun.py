import sys
import FWCore.ParameterSet.Config as cms
from Configuration.StandardSequences.Eras import eras
import imp
import json

maskHO = False
maskHB = False
maskHF = False
maskHE = False
masks = []
skipevents = 0
maxevts = 10000


Runtypes = ["HBped1","HBped6","HBled1","HBled6","HEped1","HEped6","HEled1","HEled6","HBloled","HEloled","HFped","HFled","HOled","HOped","Multiloled","Multiped1","Multiled1","Meltiped6","Multiled6"]

runtype = sys.argv[2]
runnumber = int(sys.argv[3])
seqflag = int(sys.argv[4])

timerun = 0

## get masks, times etc
with open('Runs.json') as f:
    datart = json.load(f)

dataRT = datart.get("runs")

for datarun in dataRT:
    for line in datarun.keys():
        if (runnumber == int(line)):
            RUNTYPE = datarun[line].get("runtype")
            seq =  datarun[line].get("seq")
            timerun =  datarun[line].get("time")
            masks = datarun[line].get("masks")
for subd in masks:
    if (subd == "HO"):
         maskHO = True
    if (subd == "HB"):
        maskHB = True
    if (subd == "HF"):
        maskHF = True
    if (subd == "HE"):
        maskHE = True


OutfileName = "Runs/" + runtype + "/run" + str(runnumber) + ".root"
file = "file:/eos/cms/store/group/dpg_hcal/comm_hcal/USC/run" + str(runnumber) + "/USC_" + str(runnumber) + ".root"
Lmap = "Maps/LMAP_Nov12.txt"

if runtype not in Runtypes:
    sys.exit("Unknown runtype, see runtypes list")

ParametersModulePath = "python/" + runtype + "_cfi.py"

process = cms.Process('TEST',eras.Run3)

Params = imp.load_source('parameters', ParametersModulePath)

processHE =  (not maskHE) and Params.processHE
processHB = (not maskHB) and Params.processHB
processHO = (not maskHO) and Params.processHO
processHF = (not maskHF) and Params.processHF

if (Params.gsel==6):
     filegsel = "Trends/Trendalyzer/Maps/HcalQIEData_2019_v2.0_data_shunt" + str(6) + ".txt"
if (Params.gsel==1):
     filegsel = "Trends/Trendalyzer/Maps/HcalQIEData_2019_v2.0_data_shunt" + str(1) + ".txt"

process.load('Configuration.EventContent.EventContent_cff')

process.source = cms.Source("HcalTBSource",
    fileNames = cms.untracked.vstring(file),
    HcalSlowDataFED = cms.untracked.int32(14),
    firstLuminosityBlockForEachRun = cms.untracked.VLuminosityBlockID([])
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

if (seqflag == 1):
    skipevents = Params.skipevents
    maxevts = Params.maxevents
#    process.source.skipEvents = cms.untracked.uint32(Params.skipevents)

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.autoCond import autoCond
process.GlobalTag.globaltag = autoCond['phase1_2021_realistic']
process.load("CondCore.CondDB.CondDB_cfi")

process.load("Configuration.StandardSequences.GeometryDB_cff")

#process.load("EventFilter.HcalRawToDigi.HcalRawToDigi_cfi")
process.hcalDigis = cms.EDProducer("HcalRawToDigi",
        HcalFirstFED = cms.untracked.int32(1100)
)


process.hcalDigis.FilterDataQuality = cms.bool(False)
process.hcalDigis.firstSample = cms.int32(0)
process.hcalDigis.lastSample = cms.int32(7)
process.hcalDigis.lastSample.UnpackCalib = cms.untracked.bool(False)
process.hcalDigis.InputLabel = cms.InputTag("source")
process.hcalDigis.UnpackZDC = cms.untracked.bool(False)
#process.hcalDigis.ComplainEmptyData = cms.untracked.bool(True)
#process.hcalDigis.silent = cms.untracked.bool(False)

process.hcalDigis.FEDs = cms.untracked.vint32(1100, 1101, 1102, 1103, 1104, 1105, 1106, 1107, 1108, 1109, 1110, 1111, 1112, 1113, 1114, 1115, 1116, 1117, 1118, 1119, 1120, 1121, 1122, 1123, 1124, 1125, 1126, 1127, 1128, 1129, 1134, 1135)


process.digianalyzerT = cms.EDAnalyzer('Analyzer',
    skipevents = cms.untracked.int32(skipevents),
    maxevts =  cms.untracked.int32(maxevts),
    OutFileName = cms.untracked.string(OutfileName),
    historangeLHBHE = cms.untracked.double(Params.historangeLHBHE),
    historangeRHBHE = cms.untracked.double(Params.historangeRHBHE),
    numberofbinsHBHE = cms.untracked.int32(Params.numberofbinsHBHE),
    historangeLHO = cms.untracked.double(Params.historangeLHO),
    historangeRHO = cms.untracked.double(Params.historangeRHO),
    numberofbinsHO = cms.untracked.int32(Params.numberofbinsHO),
    historangeLHF = cms.untracked.double(Params.historangeLHO),
    historangeRHF = cms.untracked.double(Params.historangeRHO),
    numberofbinsHF = cms.untracked.int32(Params.numberofbinsHF),
    fitPeaks  = cms.untracked.bool(Params.fitPeaks),
    processHO = cms.untracked.bool(processHO),
    processHB = cms.untracked.bool(processHB),
    processHE = cms.untracked.bool(processHE),
    processHF = cms.untracked.bool(processHF),
    timeR = cms.untracked.int32(timerun),
    rnumber = cms.untracked.int32(runnumber),
    seq = cms.untracked.int32(seqflag),
    Lmapfile = cms.untracked.string(Lmap)
)

process.es_ascii2 = cms.ESSource("HcalTextCalibrations",
     input = cms.VPSet(
                            cms.PSet(
                                     object = cms.string('QIEData'),
                                     file = cms.FileInPath(filegsel)
                                     )
                   )
)
process.prefer=cms.ESPrefer('HcalTextCalibrations','es_ascii2')

process.es_ascii = cms.ESSource('HcalTextCalibrations',
        input = cms.VPSet(
               cms.PSet(
                object = cms.string('ElectronicsMap'),
                file = cms.FileInPath("Trends/Trendalyzer/Maps/HcalElectronicsMap_Run3_v1.0_data.txt")  # EMAP here!
               )
        )
)
process.es_prefer = cms.ESPrefer('HcalTextCalibrations', 'es_ascii')

process.dump = cms.EDAnalyzer("HcalDigiDump")

process.p = cms.Path(process.hcalDigis*process.digianalyzerT)
