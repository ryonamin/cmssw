#!/usr/bin/env python

import sys, os
from SUSYBSMAnalysis.Zprime2muAnalysis.PATTools import switchHLTProcessName, AODOnly
from tuple_common import cms, process, crab_cfg

AODOnly(process)
#switchHLTProcessName(process, 'REDIGI311X')

#process.source.fileNames = ['/store/mc/Summer12_DR53X/DYToMuMu_M-20_CT10_TuneZ2star_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7A-v1/0000/FE93A307-F2E2-E111-BC0D-E41F131815FC.root']
process.source.fileNames = [
       '/store/mc/GEM2019Upg14DR/ZprimeSSMToMuMu_M-2500_TuneZ2star_14TeV-pythia6/AODSIM/final_phase1_PU50bx25_DES19_62_V8-v1/00000/0A0109BF-1C20-E411-A51B-00248C0BE01E.root',
       '/store/mc/GEM2019Upg14DR/ZprimeSSMToMuMu_M-2500_TuneZ2star_14TeV-pythia6/AODSIM/final_phase1_PU50bx25_DES19_62_V8-v1/00000/14741E04-2720-E411-B9B7-003048FFD76E.root',
       '/store/mc/GEM2019Upg14DR/ZprimeSSMToMuMu_M-2500_TuneZ2star_14TeV-pythia6/AODSIM/final_phase1_PU50bx25_DES19_62_V8-v1/00000/1C41007F-4020-E411-ADB3-0025905A611E.root',
       '/store/mc/GEM2019Upg14DR/ZprimeSSMToMuMu_M-2500_TuneZ2star_14TeV-pythia6/AODSIM/final_phase1_PU50bx25_DES19_62_V8-v1/00000/32F3D285-1220-E411-A49F-003048FFCBA8.root',
       '/store/mc/GEM2019Upg14DR/ZprimeSSMToMuMu_M-2500_TuneZ2star_14TeV-pythia6/AODSIM/final_phase1_PU50bx25_DES19_62_V8-v1/00000/4055F084-0D20-E411-B574-0025905A60A0.root',
       '/store/mc/GEM2019Upg14DR/ZprimeSSMToMuMu_M-2500_TuneZ2star_14TeV-pythia6/AODSIM/final_phase1_PU50bx25_DES19_62_V8-v1/00000/46B0DD5D-2220-E411-ADC7-0025905964A2.root',
       '/store/mc/GEM2019Upg14DR/ZprimeSSMToMuMu_M-2500_TuneZ2star_14TeV-pythia6/AODSIM/final_phase1_PU50bx25_DES19_62_V8-v1/00000/66B41556-2D20-E411-830C-002618943973.root',
       '/store/mc/GEM2019Upg14DR/ZprimeSSMToMuMu_M-2500_TuneZ2star_14TeV-pythia6/AODSIM/final_phase1_PU50bx25_DES19_62_V8-v1/00000/766690C5-FE1F-E411-B0BD-0025905B85F6.root',
       '/store/mc/GEM2019Upg14DR/ZprimeSSMToMuMu_M-2500_TuneZ2star_14TeV-pythia6/AODSIM/final_phase1_PU50bx25_DES19_62_V8-v1/00000/864169AE-1F20-E411-8472-0026189438E2.root',
       '/store/mc/GEM2019Upg14DR/ZprimeSSMToMuMu_M-2500_TuneZ2star_14TeV-pythia6/AODSIM/final_phase1_PU50bx25_DES19_62_V8-v1/00000/8C5077A9-1020-E411-BF94-002618943947.root',
       '/store/mc/GEM2019Upg14DR/ZprimeSSMToMuMu_M-2500_TuneZ2star_14TeV-pythia6/AODSIM/final_phase1_PU50bx25_DES19_62_V8-v1/00000/92797F63-2321-E411-8AC4-0025905B861C.root',
       '/store/mc/GEM2019Upg14DR/ZprimeSSMToMuMu_M-2500_TuneZ2star_14TeV-pythia6/AODSIM/final_phase1_PU50bx25_DES19_62_V8-v1/00000/940781F8-3D21-E411-9BDF-0025905A608A.root',
       '/store/mc/GEM2019Upg14DR/ZprimeSSMToMuMu_M-2500_TuneZ2star_14TeV-pythia6/AODSIM/final_phase1_PU50bx25_DES19_62_V8-v1/00000/9A0E50D9-9520-E411-8A2E-0025905A48D6.root',
       '/store/mc/GEM2019Upg14DR/ZprimeSSMToMuMu_M-2500_TuneZ2star_14TeV-pythia6/AODSIM/final_phase1_PU50bx25_DES19_62_V8-v1/00000/9CA55FD3-0C20-E411-8B75-0026189438C4.root',
       '/store/mc/GEM2019Upg14DR/ZprimeSSMToMuMu_M-2500_TuneZ2star_14TeV-pythia6/AODSIM/final_phase1_PU50bx25_DES19_62_V8-v1/00000/9E942055-0B20-E411-B5F7-00261894387E.root',
       '/store/mc/GEM2019Upg14DR/ZprimeSSMToMuMu_M-2500_TuneZ2star_14TeV-pythia6/AODSIM/final_phase1_PU50bx25_DES19_62_V8-v1/00000/A0211809-B220-E411-A40A-0025905A6136.root',
       '/store/mc/GEM2019Upg14DR/ZprimeSSMToMuMu_M-2500_TuneZ2star_14TeV-pythia6/AODSIM/final_phase1_PU50bx25_DES19_62_V8-v1/00000/BC438FCE-8C20-E411-899F-003048FFD796.root',
       '/store/mc/GEM2019Upg14DR/ZprimeSSMToMuMu_M-2500_TuneZ2star_14TeV-pythia6/AODSIM/final_phase1_PU50bx25_DES19_62_V8-v1/00000/C2149735-3D20-E411-9F2B-002618943919.root',
       '/store/mc/GEM2019Upg14DR/ZprimeSSMToMuMu_M-2500_TuneZ2star_14TeV-pythia6/AODSIM/final_phase1_PU50bx25_DES19_62_V8-v1/00000/C61A9CDC-FF1F-E411-8275-0025905A60B4.root',
       '/store/mc/GEM2019Upg14DR/ZprimeSSMToMuMu_M-2500_TuneZ2star_14TeV-pythia6/AODSIM/final_phase1_PU50bx25_DES19_62_V8-v1/00000/D4B5F441-2F20-E411-8547-0025905A60A0.root',
       '/store/mc/GEM2019Upg14DR/ZprimeSSMToMuMu_M-2500_TuneZ2star_14TeV-pythia6/AODSIM/final_phase1_PU50bx25_DES19_62_V8-v1/00000/FCAB96F9-3D21-E411-A121-0025905A48EC.root',
       '/store/mc/GEM2019Upg14DR/ZprimeSSMToMuMu_M-2500_TuneZ2star_14TeV-pythia6/AODSIM/final_phase1_PU50bx25_DES19_62_V8-v1/00000/FEF43AC3-1C20-E411-A0B5-0025905A60CE.root'
                           ]
process.maxEvents.input = 10
#process.GlobalTag.globaltag = 'START53_V11::All'
process.GlobalTag.globaltag = 'DES19_62_V8::All'

if __name__ == '__main__' and hasattr(sys, 'argv') and 'submit' in sys.argv:
    job_control = '''
total_number_of_events = -1
events_per_job = 150000
'''

    just_testing = 'testing' in sys.argv
    create_only = 'create_only' in sys.argv

    from SUSYBSMAnalysis.Zprime2muAnalysis.MCSamples import samples
    for sample in samples:
        print sample.name

        new_py = open('tuple_mc.py').read()
        new_py += '\nswitchHLTProcessName(process, "%(hlt_process_name)s")\n' % sample.__dict__

        sample.pset = 'crab/psets/tuple_mc_crab_%(name)s.py' % sample.__dict__
        open(sample.pset,'wt').write(new_py)

        sample.job_control = job_control % sample.__dict__
        open('crab.cfg', 'wt').write(crab_cfg % sample.__dict__)
        if not just_testing:
            if create_only:
                os.system('crab -create')
            else:
                os.system('crab -create -submit all')
            os.system('rm crab.cfg')
