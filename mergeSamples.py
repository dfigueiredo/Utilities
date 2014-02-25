#!/usr/bin/env python
import os

print ''
print '@@@@@@@@@@@@@@@@@@'
print 'Merging Histograms'
print '@@@@@@@@@@@@@@@@@@'
print ''

#Merge Histograms

os.system("hadd histo_Muon_Reco.root histo_muon2010A_p1_HLT_Mu9_Reco.root histo_muon2010B_p2_HLT_Mu9_Reco.root histo_muon2010B_p3_HLT_Mu15_Reco.root")
os.system("hadd histo_Electron_Reco.root histo_EG2010A_Reco.root histo_Electron2010B_Reco.root")
os.system("hadd histo_Pompyt_muon_Reco.root histo_PompytMinus_muon_Reco.root histo_PompytPlus_muon_Reco.root")
os.system("hadd histo_Pompyt_electron_Reco.root histo_PompytMinus_electron_Reco.root histo_PompytPlus_electron_Reco.root")
os.system("hadd histo_Z_Reco.root histo_Muon_Reco.root histo_Electron_Reco.root")
os.system("hadd histo_DY_Reco.root histo_DyToEE_Reco.root histo_DyToMuMu_Reco.root")
os.system("hadd histo_PompytMinus_Reco.root histo_PompytMinus_electron_Reco.root histo_PompytMinus_muon_Reco.root")
os.system("hadd histo_PompytPlus_Reco.root histo_PompytPlus_electron_Reco.root histo_PompytPlus_muon_Reco.root")
os.system("hadd histo_Pompyt_Reco.root histo_PompytMinus_Reco.root histo_PompytPlus_Reco.root")

#Merge TTree All Z

os.system("hadd TTreeAllZ_histo_Muon_Reco.root TTreeAllZ_histo_muon2010A_p1_HLT_Mu9_Reco.root TTreeAllZ_histo_muon2010B_p2_HLT_Mu9_Reco.root TTreeAllZ_histo_muon2010B_p3_HLT_Mu15_Reco.root")
os.system("hadd TTreeAllZ_histo_Electron_Reco.root TTreeAllZ_histo_EG2010A_Reco.root TTreeAllZ_histo_Electron2010B_Reco.root")
os.system("hadd TTreeAllZ_histo_Pompyt_muon_Reco.root TTreeAllZ_histo_PompytMinus_muon_Reco.root TTreeAllZ_histo_PompytPlus_muon_Reco.root")
os.system("hadd TTreeAllZ_histo_Pompyt_electron_Reco.root TTreeAllZ_histo_PompytMinus_electron_Reco.root TTreeAllZ_histo_PompytPlus_electron_Reco.root")
os.system("hadd TTreeAllZ_histo_Z_Reco.root TTreeAllZ_histo_Muon_Reco.root TTreeAllZ_histo_Electron_Reco.root")
os.system("hadd TTreeAllZ_histo_DY_Reco.root TTreeAllZ_histo_DyToEE_Reco.root TTreeAllZ_histo_DyToMuMu_Reco.root")
os.system("hadd TTreeAllZ_histo_PompytMinus_Reco.root TTreeAllZ_histo_PompytMinus_electron_Reco.root TTreeAllZ_histo_PompytMinus_muon_Reco.root")
os.system("hadd TTreeAllZ_histo_PompytPlus_Reco.root TTreeAllZ_histo_PompytPlus_electron_Reco.root TTreeAllZ_histo_PompytPlus_muon_Reco.root")
os.system("hadd TTreeAllZ_histo_Pompyt_Reco.root TTreeAllZ_histo_PompytMinus_Reco.root TTreeAllZ_histo_PompytPlus_Reco.root")

#Merge TTree CASTOR

os.system("hadd TTreeCASTOR_histo_Muon_Reco.root TTreeCASTOR_histo_muon2010A_p1_HLT_Mu9_Reco.root TTreeCASTOR_histo_muon2010B_p2_HLT_Mu9_Reco.root TTreeCASTOR_histo_muon2010B_p3_HLT_Mu15_Reco.root")
os.system("hadd TTreeCASTOR_histo_Electron_Reco.root TTreeCASTOR_histo_EG2010A_Reco.root TTreeCASTOR_histo_Electron2010B_Reco.root")
os.system("hadd TTreeCASTOR_histo_Pompyt_muon_Reco.root TTreeCASTOR_histo_PompytMinus_muon_Reco.root TTreeCASTOR_histo_PompytPlus_muon_Reco.root")
os.system("hadd TTreeCASTOR_histo_Pompyt_electron_Reco.root TTreeCASTOR_histo_PompytMinus_electron_Reco.root TTreeCASTOR_histo_PompytPlus_electron_Reco.root")
os.system("hadd TTreeCASTOR_histo_Z_Reco.root TTreeCASTOR_histo_Muon_Reco.root TTreeCASTOR_histo_Electron_Reco.root")
os.system("hadd TTreeCASTOR_histo_DY_Reco.root TTreeCASTOR_histo_DyToEE_Reco.root TTreeCASTOR_histo_DyToMuMu_Reco.root")
os.system("hadd TTreeCASTOR_histo_PompytMinus_Reco.root TTreeCASTOR_histo_PompytMinus_electron_Reco.root TTreeCASTOR_histo_PompytMinus_muon_Reco.root")
os.system("hadd TTreeCASTOR_histo_PompytPlus_Reco.root TTreeCASTOR_histo_PompytPlus_electron_Reco.root TTreeCASTOR_histo_PompytPlus_muon_Reco.root")
os.system("hadd TTreeCASTOR_histo_Pompyt_Reco.root TTreeCASTOR_histo_PompytMinus_Reco.root TTreeCASTOR_histo_PompytPlus_Reco.root")

#Merge Z Signal

os.system("hadd TTreeGoldenDiffZ_histo_Muon_Reco.root TTreeGoldenDiffZ_histo_muon2010A_p1_HLT_Mu9_Reco.root TTreeGoldenDiffZ_histo_muon2010B_p2_HLT_Mu9_Reco.root TTreeGoldenDiffZ_histo_muon2010B_p3_HLT_Mu15_Reco.root")
os.system("hadd TTreeGoldenDiffZ_histo_Electron_Reco.root TTreeGoldenDiffZ_histo_EG2010A_Reco.root TTreeGoldenDiffZ_histo_Electron2010B_Reco.root")
os.system("hadd TTreeGoldenDiffZ_histo_Pompyt_muon_Reco.root TTreeGoldenDiffZ_histo_PompytMinus_muon_Reco.root TTreeGoldenDiffZ_histo_PompytPlus_muon_Reco.root")
os.system("hadd TTreeGoldenDiffZ_histo_Pompyt_electron_Reco.root TTreeGoldenDiffZ_histo_PompytMinus_electron_Reco.root TTreeGoldenDiffZ_histo_PompytPlus_electron_Reco.root")
os.system("hadd TTreeGoldenDiffZ_histo_Z_Reco.root TTreeGoldenDiffZ_histo_Muon_Reco.root TTreeGoldenDiffZ_histo_Electron_Reco.root")
os.system("hadd TTreeGoldenDiffZ_histo_DY_Reco.root TTreeGoldenDiffZ_histo_DyToEE_Reco.root TTreeGoldenDiffZ_histo_DyToMuMu_Reco.root")
os.system("hadd TTreeGoldenDiffZ_histo_PompytMinus_Reco.root TTreeGoldenDiffZ_histo_PompytMinus_electron_Reco.root TTreeGoldenDiffZ_histo_PompytMinus_muon_Reco.root")
os.system("hadd TTreeGoldenDiffZ_histo_PompytPlus_Reco.root TTreeGoldenDiffZ_histo_PompytPlus_electron_Reco.root TTreeGoldenDiffZ_histo_PompytPlus_muon_Reco.root")
os.system("hadd TTreeGoldenDiffZ_histo_Pompyt_Reco.root TTreeGoldenDiffZ_histo_PompytMinus_Reco.root TTreeGoldenDiffZ_histo_PompytPlus_Reco.root")
