#

from CRABClient.UserUtilities import config
config = config()
config.General.transferOutputs = True
# config.General.requestName = 'openHLT_20181031_V59_Hydjet_Quenched_Drum5Ev8_PbPbMinBias_5020GeV_1030'
config.General.requestName = 'openHLT_20181104_V65calojet_Hydjet_Quenched_Drum5Ev8_PbPbMinBias_5020GeV_1030_v5'
config.General.workArea = 'crab_projects'
# config.JobType.psetName = 'expHLT_103X_ImportV34L1_cfg_DUMP.py'
# config.JobType.psetName = 'expHLT_103X_V34changevar_cfg_DUMP.py'
# config.JobType.psetName = 'expHLT_103X_V3trkfil_cfg_DUMP.py'
# config.JobType.psetName = 'expHLT_103X_ImportV42L1_cfg_DUMP.py'
# config.JobType.psetName = 'expHLT_103X_ImportV46L1_cfg_DUMP.py'
# config.JobType.psetName = 'expHLT_103X_ImportV51rmtrk_cfg_DUMP.py'
config.JobType.psetName = 'expHLT_103X_ImportV65_cfg_DUMP.py'
# config.JobType.psetName = 'expHLT_103X_ImportV59L1_cfg_DUMP.py'
config.JobType.pluginName = 'Analysis'
config.JobType.maxMemoryMB = 4000
# config.JobType.inputFiles = ['rssLimit']
config.JobType.pyCfgParams = ['noprint']
config.JobType.outputFiles = ['openHLT.root']
# config.JobType.numCores = 4
config.JobType.allowUndistributedCMSSW = True

# config.Data.useParent = True
config.Data.userInputFiles = open('filelist_HINPbPbSpring18GS_103X_upgrade2018_realistic_HI_v7_DIGI_L1_DIGI2RAW_HLT_PU.txt').readlines()
# config.Data.inputDataset = '/Hydjet_Quenched_Drum5Ev8_PbPbMinBias_5020GeV_2018/HINPbPbSpring18DR-NoPU_100X_upgrade2018_realistic_v10_ext1-v1/GEN-SIM-RAW'
# config.Data.inputDataset = '/Hydjet_Quenched_Drum5Ev8_PbPbMinBias_5020GeV_2018/mnguyen-crab_Hydjet_Quenched_Drum5Ev8_PbPbMinBias_5020GeV_DIGI2RAW_103X_upgrade2018_realistic_HI_v4-58f9b704d41182ecb4a63ead877b2936/USER'
# config.Data.inputDataset = '/Hydjet_Quenched_Drum5Ev8_PbPbMinBias_5020GeV_2018/katatar-HINPbPbSpring18GS_103X_upgrade2018_realistic_HI_v7_DIGI_L1_DIGI2RAW_HLT_PU-1c389861083a146d75ac332e7b4016f6/USER'
config.Data.inputDBS = 'phys03'
config.Data.totalUnits = -1
config.Data.unitsPerJob = 1
config.Data.splitting = "FileBased"
# config.Data.splitting = 'EventAwareLumiBased'
# config.Data.splitting = 'LumiBased'
# config.Data.runRange = '304906-304906'
# config.Data.lumiMask = 'json_skiponefile.txt'
# config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/HI/Cert_304899-304907_5TeV_PromptReco_XeXe_Collisions17_JSON.txt'
# config.Data.allowNonValidInputDataset = True
config.Data.outputPrimaryDataset = "Hydjet_Quenched_Drum5Ev8_PbPbMinBias_5020GeV_2018"

config.Site.storageSite = 'T2_US_MIT'
# config.Site.storageSite = 'T2_CH_CERN'
# config.Data.outLFNDirBase = '/store/group/phys_heavyions/wangj/HltHFPPRef2017'
config.Site.whitelist = ['T2_US_MIT']
config.Site.blacklist = ['T2_US_Nebraska','T2_US_UCSD','T2_US_Wisconsin','T2_FR_GRIF_IRFU','T3_US_UCR','T3_US_Rutgers','T3_BG_UNI_SOFIA','T3_IT_Perugia']
# config.Site.ignoreGlobalBlacklist = True
config.section_("Debug")
config.Debug.extraJDL = ['+CMS_ALLOW_OVERFLOW=False']
