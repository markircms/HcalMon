import FWCore.ParameterSet.Config as cms
from Configuration.StandardSequences.Eras import eras

process = cms.Process('TEST',eras.Run3)

#process.load('Configuration/StandardSequences/RawToDigi_cff')

process.load('Configuration.EventContent.EventContent_cff')

process.source = cms.Source("HcalTBSource",
    fileNames = cms.untracked.vstring(
#        "file:USC_333273.root"
#       "file:/eos/cms/store/group/dpg_hcal/comm_hcal/USC/run333159/USC_333159.root" #from eos directly
#        "file:/eos/cms/store/group/dpg_hcal/comm_hcal/USC/run333128/USC_333128.root"
#         "file:/eos/cms/store/group/dpg_hcal/comm_hcal/USC/run332730/USC_332730.root"
#          "file:/eos/cms/store/group/dpg_hcal/comm_hcal/USC/run333273/USC_333273.root"
# 	      "file:/eos/cms/store/group/dpg_hcal/comm_hcal/USC/run332799/USC_332799.root"
 	      "file:/eos/cms/store/group/dpg_hcal/comm_hcal/USC/run333405/USC_333405.root"
    ),
    HcalSlowDataFED = cms.untracked.int32(14),
    firstLuminosityBlockForEachRun = cms.untracked.VLuminosityBlockID([])
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)


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
process.hcalDigis.lastSample.UnpackCalib = cms.untracked.bool(True)
process.hcalDigis.InputLabel = cms.InputTag("source")
process.hcalDigis.UnpackZDC = cms.untracked.bool(False)
#process.hcalDigis.ComplainEmptyData = cms.untracked.bool(True)
#process.hcalDigis.silent = cms.untracked.bool(False)

process.hcalDigis.FEDs = cms.untracked.vint32(1100, 1101, 1102, 1103, 1104, 1105, 1106, 1107, 1108, 1109, 1110, 1111, 1112, 1113, 1114, 1115, 1116, 1117, 1118, 1119, 1120, 1121, 1122, 1123, 1124, 1125, 1126, 1127, 1128, 1129, 1134, 1135)

# test HO FEDs only
#process.hcalDigis.FEDs = cms.untracked.vint32(1124, 1125, 1126, 1127, 1128, 1129, 1134, 1135)


process.digianalyzer = cms.EDAnalyzer('Analyzer',
    OutFileName = cms.untracked.string('output.root'),
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
                                     file = cms.FileInPath('Trends/Trendalyzer/HcalQIEData_2019_v2.0_data_shunt1.txt')
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

process.p = cms.Path(process.hcalDigis*process.digianalyzer)
