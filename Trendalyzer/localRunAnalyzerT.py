import sys
import FWCore.ParameterSet.Config as cms
from Configuration.StandardSequences.Eras import eras
import imp


Runtypes = ["HBped1","HBped6","HBled1","HBled6","HEped1","HEped6","HEled1","HEled6","HBloled","HEloled","HFped","HFled","HOled","HOped","Multiloled","Multiped1","Multiled1","Meltiped6","Multiled6"]

runtype = sys.argv[2]
runnumber = sys.argv[3]
seqflag = int(sys.argv[4])

OutfileName = "Runs/" + runtype + "/run" + str(runnumber) + ".root"
file = "file:/eos/cms/store/group/dpg_hcal/comm_hcal/USC/run" + str(runnumber) + "/USC_" + str(runnumber) + ".root"

if runtype not in Runtypes:
    sys.exit("Unknown runtype, see runtypes list")

ParametersModulePath = "python/" + runtype + "_cfi.py"

process = cms.Process('TEST',eras.Run3)

Params = imp.load_source('parameters', ParametersModulePath)


if (Params.gsel==6):
     filegsel = "Trends/Trendalyzer/HcalQIEData_2019_v2.0_data_shunt" + str(6) + ".txt"
if (Params.gsel==1):
     filegsel = "Trends/Trendalyzer/HcalQIEData_2019_v2.0_data_shunt" + str(1) + ".txt"

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
    process.maxEvents = cms.untracked.PSet(
        input = cms.untracked.int32(Params.maxevents)
    )
#    process.source.skipEvents = cms.untracked.uint32(Params.skipevents)
#    process.source.firstEvent = cms.untracked.uint32(Params.skipevents)
    process.source.firstEvent = cms.untracked.uint32(15000)

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

# test HO FEDs only
#process.hcalDigis.FEDs = cms.untracked.vint32(1124, 1125, 1126, 1127, 1128, 1129, 1134, 1135)


process.digianalyzerT = cms.EDAnalyzer('Analyzer',
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
    processHO = cms.untracked.bool(Params.processHO),
    processHB = cms.untracked.bool(Params.processHB),
    processHE = cms.untracked.bool(Params.processHE),
    processHF = cms.untracked.bool(Params.processHF)
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
                file = cms.FileInPath("Trends/Trendalyzer/HcalElectronicsMap_Run3_v1.0_data.txt")  # EMAP here!
               )
        )
)
process.es_prefer = cms.ESPrefer('HcalTextCalibrations', 'es_ascii')

process.dump = cms.EDAnalyzer("HcalDigiDump")

process.p = cms.Path(process.hcalDigis*process.digianalyzerT)
