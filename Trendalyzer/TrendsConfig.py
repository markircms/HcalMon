import sys
import FWCore.ParameterSet.Config as cms

RType = "Multiloled"
runs = [333158,333174,333357,333405,333464]
LmapPath = "Maps/LMAP_Nov12.txt"
RType = sys.argv[2]

process = cms.Process('TEST')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.source = cms.Source("EmptySource")


#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#from Configuration.AlCa.autoCond import autoCond
#process.GlobalTag.globaltag = autoCond['phase1_2021_realistic']
#process.load("CondCore.CondDB.CondDB_cfi")

process.TrendsAnalyzer = cms.OutputModule('Trendalyzer',
    Runsvector = cms.untracked.vint32(runs),
    Lmapinput = cms.untracked.string(LmapPath),
    Runtype = cms.untracked.string(RType)
)

process.p = cms.EndPath(process.TrendsAnalyzer)
