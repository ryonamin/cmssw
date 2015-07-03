// -*- C++ -*-
//
// Package:    DQM/HLTObjectMonitor
// Class:      HLTObjectMonitor
//
/**\class HLTObjectMonitor HLTObjectMonitor.cc DQM/HLTEvF/plugins/HLTObjectMonitor.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Charles Nicholas Mueller
//         Created:  Sun, 22 Mar 2015 22:29:00 GMT
//
//


// system include files
#include <memory>
#include <sys/time.h>
#include <cstdlib>

// user include files
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/HLTReco/interface/TriggerTypeDefs.h"
#include "DataFormats/Scalers/interface/LumiScalers.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

//for collections
#include "HLTrigger/JetMET/interface/AlphaT.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/METReco/interface/MET.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"
#include "DataFormats/BTauReco/interface/JetTag.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidateFwd.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/CaloJet.h"


#include "DQMServices/Core/interface/DQMStore.h"
#include "DQMServices/Core/interface/MonitorElement.h"
#include "DQMServices/Core/interface/DQMEDAnalyzer.h"

#include "TMath.h"
#include "TStyle.h"
#include "TLorentzVector.h"

#include <unordered_map>
//
// class declaration
//

//using namespace edm;
using namespace trigger;
using std::vector;
using std::string;
using std::unordered_map;

class HLTObjectMonitor : public DQMEDAnalyzer {
   public:
      explicit HLTObjectMonitor(const edm::ParameterSet&);
      ~HLTObjectMonitor();

  //      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void bookHistograms(DQMStore::IBooker &i, edm::Run const&, edm::EventSetup const&) override;
      void dqmBeginRun(edm::Run const&, edm::EventSetup const&) override;

      void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

  double dxyFinder(double, double, edm::Handle<reco::RecoChargedCandidateCollection>, edm::Handle<reco::BeamSpot>);
  double get_wall_time(void);
      // ----------member data ---------------------------

  bool debugPrint;

  HLTConfigProvider hltConfig_;

  string topDirectoryName;
  string mainShifterFolder;
  string backupFolder;

  unordered_map<string, unsigned int> lookupIndex;
  unordered_map<string, string> lookupFilter;
  vector<string> quickCollectionPaths;

  //set Token(-s)
  edm::EDGetTokenT<edm::TriggerResults> triggerResultsToken_;
  edm::EDGetTokenT<trigger::TriggerEvent> aodTriggerToken_;
  edm::EDGetTokenT<LumiScalersCollection> lumiScalersToken_;
  edm::EDGetTokenT<reco::BeamSpot> beamSpotToken_;
  edm::EDGetTokenT<reco::RecoChargedCandidateCollection> chargedCandToken_;
  edm::EDGetTokenT<reco::JetTagCollection> csvCaloTagsToken_;
  edm::EDGetTokenT<reco::JetTagCollection> csvPfTagsToken_;
  edm::EDGetTokenT<vector<reco::CaloJet>> csvCaloJetsToken_;
  edm::EDGetTokenT<vector<reco::PFJet>> csvPfJetsToken_;



  //declare params
  edm::ParameterSet rsq_TH1;
  edm::ParameterSet mr_TH1;
  edm::ParameterSet alphaT_TH1;
  edm::ParameterSet photonPt_TH1;
  edm::ParameterSet photonEta_TH1;
  edm::ParameterSet photonPhi_TH1;
  edm::ParameterSet muonPt_TH1;
  edm::ParameterSet muonEta_TH1;
  edm::ParameterSet muonPhi_TH1;
  edm::ParameterSet l2muonPt_TH1;
  edm::ParameterSet l2muonEta_TH1;
  edm::ParameterSet l2muonPhi_TH1;
  edm::ParameterSet l2NoBPTXmuonPt_TH1;
  edm::ParameterSet l2NoBPTXmuonEta_TH1;
  edm::ParameterSet l2NoBPTXmuonPhi_TH1;
  edm::ParameterSet electronPt_TH1;
  edm::ParameterSet electronEta_TH1;
  edm::ParameterSet electronPhi_TH1;
  edm::ParameterSet jetPt_TH1;
  edm::ParameterSet jetAK8Pt_TH1;
  edm::ParameterSet jetAK8Mass_TH1;
  edm::ParameterSet tauPt_TH1;
  edm::ParameterSet diMuonLowMass_TH1;
  edm::ParameterSet caloMetPt_TH1;
  edm::ParameterSet caloMetPhi_TH1;
  edm::ParameterSet pfMetPt_TH1;
  edm::ParameterSet pfMetPhi_TH1;
  edm::ParameterSet caloHtPt_TH1;
  edm::ParameterSet pfHtPt_TH1;
  edm::ParameterSet bJetPhi_TH1;
  edm::ParameterSet bJetEta_TH1;
  edm::ParameterSet bJetCSVCalo_TH1;
  edm::ParameterSet bJetCSVPF_TH1;
  edm::ParameterSet diMuonMass_TH1;
  edm::ParameterSet diElecMass_TH1;
  edm::ParameterSet muonDxy_TH1;

  string processName_;

  //setup path names
  string razor_pathName;
  string alphaT_pathName;
  string photonPlots_pathName;
  string muonPlots_pathName;
  string l2muonPlots_pathName;
  string l2NoBPTXmuonPlots_pathName;
  string electronPlots_pathName;
  string jetPt_pathName;
  string tauPt_pathName;
  string diMuonLowMass_pathName;
  string caloMetPlots_pathName;
  string pfMetPlots_pathName;
  string caloHtPt_pathName;
  string pfHtPt_pathName;
  string bJetPlots_pathName;
  string bJetPlots_pathNameOR;
  string bJetPlots_pathNameCalo;
  string bJetPlots_pathNamePF;
  string jetAK8Plots_pathName;
  string diMuonMass_pathName;
  string diMuonMass_pathNameOR;
  string diElecMass_pathName;
  string muonDxyPlots_pathName;

  //declare all MEs
  MonitorElement * rsq_;
  MonitorElement * mr_;
  MonitorElement * alphaT_;
  MonitorElement * photonPt_;
  MonitorElement * photonEta_;
  MonitorElement * photonPhi_;
  MonitorElement * muonPt_;
  MonitorElement * muonEta_;
  MonitorElement * muonPhi_;
  MonitorElement * l2muonPt_;
  MonitorElement * l2muonEta_;
  MonitorElement * l2muonPhi_;
  MonitorElement * l2NoBPTXmuonPt_;
  MonitorElement * l2NoBPTXmuonEta_;
  MonitorElement * l2NoBPTXmuonPhi_;
  MonitorElement * electronPt_;
  MonitorElement * electronEta_;
  MonitorElement * electronPhi_;
  MonitorElement * jetPt_;
  MonitorElement * jetAK8Pt_;
  MonitorElement * jetAK8Mass_;
  MonitorElement * tauPt_;
  MonitorElement * diMuonLowMass_;
  MonitorElement * caloMetPt_;
  MonitorElement * caloMetPhi_;
  MonitorElement * pfMetPt_;
  MonitorElement * pfMetPhi_;
  MonitorElement * caloHtPt_;
  MonitorElement * pfHtPt_;
  MonitorElement * bJetPhi_;
  MonitorElement * bJetEta_;
  MonitorElement * bJetCSVCalo_;
  MonitorElement * bJetCSVPF_;
  MonitorElement * diMuonMass_;
  MonitorElement * diElecMass_;
  MonitorElement * muonDxy_;

  MonitorElement * wallTimePerEvent_;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
HLTObjectMonitor::HLTObjectMonitor(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
  debugPrint = false;

  topDirectoryName = "HLT/ObjectMonitor";
  mainShifterFolder = topDirectoryName+"/MainShifter";
  backupFolder = topDirectoryName+"/Backup";


  //parse params
  processName_ = iConfig.getParameter<string>("processName");

  rsq_TH1 = iConfig.getParameter<edm::ParameterSet> ("rsq");
  mr_TH1 = iConfig.getParameter<edm::ParameterSet> ("mr");
  alphaT_TH1 = iConfig.getParameter<edm::ParameterSet> ("alphaT");
  photonPt_TH1 = iConfig.getParameter<edm::ParameterSet>("photonPt");
  photonEta_TH1 = iConfig.getParameter<edm::ParameterSet>("photonEta");
  photonPhi_TH1 = iConfig.getParameter<edm::ParameterSet>("photonPhi");
  muonPt_TH1 = iConfig.getParameter<edm::ParameterSet>("muonPt");
  muonEta_TH1 = iConfig.getParameter<edm::ParameterSet>("muonEta");
  muonPhi_TH1 = iConfig.getParameter<edm::ParameterSet>("muonPhi");
  l2muonPt_TH1 = iConfig.getParameter<edm::ParameterSet>("l2muonPt");
  l2muonEta_TH1 = iConfig.getParameter<edm::ParameterSet>("l2muonEta");
  l2muonPhi_TH1 = iConfig.getParameter<edm::ParameterSet>("l2muonPhi");
  l2NoBPTXmuonPt_TH1 = iConfig.getParameter<edm::ParameterSet>("l2NoBPTXmuonPt");
  l2NoBPTXmuonEta_TH1 = iConfig.getParameter<edm::ParameterSet>("l2NoBPTXmuonEta");
  l2NoBPTXmuonPhi_TH1 = iConfig.getParameter<edm::ParameterSet>("l2NoBPTXmuonPhi");
  electronPt_TH1 = iConfig.getParameter<edm::ParameterSet>("electronPt");
  electronEta_TH1 = iConfig.getParameter<edm::ParameterSet>("electronEta");
  electronPhi_TH1 = iConfig.getParameter<edm::ParameterSet>("electronPhi");
  jetPt_TH1 = iConfig.getParameter<edm::ParameterSet>("jetPt");
  jetAK8Pt_TH1 = iConfig.getParameter<edm::ParameterSet>("jetAK8Pt");
  jetAK8Mass_TH1 = iConfig.getParameter<edm::ParameterSet>("jetAK8Mass");
  tauPt_TH1 = iConfig.getParameter<edm::ParameterSet>("tauPt");
  diMuonLowMass_TH1 = iConfig.getParameter<edm::ParameterSet>("diMuonLowMass");
  caloMetPt_TH1 = iConfig.getParameter<edm::ParameterSet>("caloMetPt");
  caloMetPhi_TH1 = iConfig.getParameter<edm::ParameterSet>("caloMetPhi");
  pfMetPt_TH1 = iConfig.getParameter<edm::ParameterSet>("pfMetPt");
  pfMetPhi_TH1 = iConfig.getParameter<edm::ParameterSet>("pfMetPhi");
  caloHtPt_TH1 = iConfig.getParameter<edm::ParameterSet>("caloHtPt");
  pfHtPt_TH1 = iConfig.getParameter<edm::ParameterSet>("pfHtPt");
  bJetPhi_TH1 = iConfig.getParameter<edm::ParameterSet>("bJetPhi");
  bJetEta_TH1 = iConfig.getParameter<edm::ParameterSet>("bJetEta");
  bJetCSVCalo_TH1 = iConfig.getParameter<edm::ParameterSet>("bJetCSVCalo");
  bJetCSVPF_TH1 = iConfig.getParameter<edm::ParameterSet>("bJetCSVPF");
  diMuonMass_TH1 = iConfig.getParameter<edm::ParameterSet>("diMuonMass");
  diElecMass_TH1 = iConfig.getParameter<edm::ParameterSet>("diElecMass");
  muonDxy_TH1 = iConfig.getParameter<edm::ParameterSet>("muonDxy");

  //set Token(s)
  //will need to change 'TEST' to 'HLT' or something else before implementation
  triggerResultsToken_ = consumes<edm::TriggerResults>(edm::InputTag("TriggerResults","", processName_));
  aodTriggerToken_ = consumes<trigger::TriggerEvent>(edm::InputTag("hltTriggerSummaryAOD", "", processName_));
  lumiScalersToken_ = consumes<LumiScalersCollection>(edm::InputTag("hltScalersRawToDigi","",""));
  beamSpotToken_ = consumes<reco::BeamSpot>(edm::InputTag("hltOnlineBeamSpot","",processName_));
  chargedCandToken_ = consumes<vector<reco::RecoChargedCandidate>>(edm::InputTag("hltL3NoFiltersNoVtxMuonCandidates","",processName_));
  csvCaloTagsToken_ = consumes<reco::JetTagCollection>(edm::InputTag("hltCombinedSecondaryVertexBJetTagsCalo","",processName_));
  csvPfTagsToken_ = consumes<reco::JetTagCollection>(edm::InputTag("hltCombinedSecondaryVertexBJetTagsPF","",processName_));
  csvCaloJetsToken_ = consumes<vector<reco::CaloJet>>(edm::InputTag("hltSelector8CentralJetsL1FastJet","",processName_));
  csvPfJetsToken_ = consumes<vector<reco::PFJet>>(edm::InputTag("hltPFJetForBtag","",processName_));


}


HLTObjectMonitor::~HLTObjectMonitor()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
HLTObjectMonitor::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  double start = get_wall_time();

  using namespace edm;

   if (debugPrint) std::cout << "Inside analyze(). " << std::endl;

   // access trigger results
   edm::Handle<edm::TriggerResults> triggerResults;
   iEvent.getByToken(triggerResultsToken_, triggerResults);
   if (!triggerResults.isValid()) return;

   edm::Handle<trigger::TriggerEvent> aodTriggerEvent;
   iEvent.getByToken(aodTriggerToken_, aodTriggerEvent);
   if (!aodTriggerEvent.isValid()) return;

   for (string & pathName : quickCollectionPaths) //loop over paths
     {
       if (triggerResults->accept(lookupIndex[pathName]) && hltConfig_.saveTags(lookupFilter[pathName]))
	 {

	   const TriggerObjectCollection objects = aodTriggerEvent->getObjects();
	   edm::InputTag moduleFilter(lookupFilter[pathName],"",processName_);
	   unsigned int moduleFilterIndex = aodTriggerEvent->filterIndex(moduleFilter);

	   if (moduleFilterIndex+1 > aodTriggerEvent->sizeFilters()) return;
	   const Keys &keys = aodTriggerEvent->filterKeys( moduleFilterIndex );

	   ////////////////////////////////
	   ///
	   /// single-object plots
	   ///
	   ////////////////////////////////

	   //PFHT pt
	   if (pathName == pfHtPt_pathName)
	     {
	       for (const auto & key : keys) pfHtPt_->Fill(objects[key].pt());
	     }

	   //jet pt
	   else if (pathName == jetPt_pathName)
	     {
	       for (const auto & key : keys) jetPt_->Fill(objects[key].pt());
	     }

	   //photon pt + eta + phi (all use same path)
	   else if (pathName == photonPlots_pathName)
	     {
	       for (const auto & key : keys)
		 {
		   photonPt_->Fill(objects[key].pt());
		   photonEta_->Fill(objects[key].eta());
		   photonPhi_->Fill(objects[key].phi());
		 }
	     }

	   //electron pt + eta + phi (all use same path)
	   else if (pathName == electronPlots_pathName)
	     {
	       for (const auto & key : keys)
		 {
		   electronPt_->Fill(objects[key].pt());
		   electronEta_->Fill(objects[key].eta());
		   electronPhi_->Fill(objects[key].phi());
		 }
	     }

	   //muon pt + eta + phi (all use same path)
	   else if (pathName == muonPlots_pathName)
	     {
	       for (const auto & key : keys)
		 {
		   muonPt_->Fill(objects[key].pt());
		   muonEta_->Fill(objects[key].eta());
		   muonPhi_->Fill(objects[key].phi());
		 }
	     }

	   //l2muon pt
	   else if (pathName == l2muonPlots_pathName)
	     {
	       for (const auto & key : keys)
		 {
		   l2muonPt_->Fill(objects[key].pt());
		   l2muonEta_->Fill(objects[key].eta());
		   l2muonPhi_->Fill(objects[key].phi());
		 }
	     }

	   //l2NoBPTXmuon pt
	   else if (pathName == l2NoBPTXmuonPlots_pathName)
	     {
	       for (const auto & key : keys)
		 {
		   l2NoBPTXmuonPt_->Fill(objects[key].pt());
		   l2NoBPTXmuonEta_->Fill(objects[key].eta());
		   l2NoBPTXmuonPhi_->Fill(objects[key].phi());
		 }
	     }

	   //Razor
	   else if (pathName == razor_pathName)
	     {
	       double onlineMR = 0, onlineRsq = 0;
	       for (const auto & key : keys)
		 {
		   if(objects[key].id() == 0){ //the MET object containing MR and Rsq will show up with ID = 0
		     onlineMR = objects[key].px(); //razor variables stored in dummy reco::MET objects
		     onlineRsq = objects[key].py();
		   }
		   mr_->Fill(onlineMR);
		   rsq_->Fill(onlineRsq);
		 }
	     }

	   //alphaT
	   else if (pathName == alphaT_pathName)
	     {
	       std::vector<ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double>>> alphaT_jets;
	       for (const auto & key : keys)
		 {
		   ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double>> JetLVec(objects[key].pt(),objects[key].eta(),objects[key].phi(),objects[key].mass());
		   alphaT_jets.push_back(JetLVec);
		 }

	       float alphaT = AlphaT(alphaT_jets,false).value();
	       alphaT_->Fill(alphaT);
	     }

	   //tau pt
	   else if (pathName == tauPt_pathName)
	     {
	       for (const auto & key : keys) tauPt_->Fill(objects[key].pt());
	     }

	   //caloMET pt+phi (same path)
	   else if (pathName == caloMetPlots_pathName)
	     {
	       for (const auto & key : keys)
		 {
		   caloMetPt_->Fill(objects[key].pt());
		   caloMetPhi_->Fill(objects[key].phi());
		 }
	     }

	   //caloHT pt
	   else if (pathName == caloHtPt_pathName)
	     {
	       for (const auto & key : keys) caloHtPt_->Fill(objects[key].pt());
	     }

	   //jetAK8 pt + mass
	   else if (pathName == jetAK8Plots_pathName)
	     {
	       for (const auto & key : keys)
		 {
		   jetAK8Pt_->Fill(objects[key].pt());
		   jetAK8Mass_->Fill(objects[key].mass());
		 }
	     }

	   //PFMET pt + phi
	   else if (pathName == pfMetPlots_pathName)
	     {
	       for (const auto & key : keys)
		 {
		   pfMetPt_->Fill(objects[key].pt());
		   pfMetPhi_->Fill(objects[key].phi());
		 }
	     }

	   // bjet eta + phi
	   //else if (pathName == bJetPlots_pathName || pathName == bJetPlots_pathNameOR)
	   else if (pathName == bJetPlots_pathNameCalo || pathName == bJetPlots_pathNamePF)
	     {
	       for (const auto & key : keys)
		 {
		   bJetEta_->Fill(objects[key].eta());
		   bJetPhi_->Fill(objects[key].phi());
		 }
	     }

	   //b-tagging CSV information
	   if (pathName == bJetPlots_pathNamePF)
	     {
	       edm::Handle<reco::JetTagCollection> csvPfTags;
	       iEvent.getByToken(csvPfTagsToken_, csvPfTags);
	       edm::Handle<vector<reco::PFJet>> csvPfJets;
	       iEvent.getByToken(csvPfJetsToken_, csvPfJets);

	       if (csvPfTags.isValid() && csvPfJets.isValid())
		 {
		   for (auto iter = csvPfTags->begin(); iter != csvPfTags->end(); iter++) bJetCSVPF_->Fill(iter->second);
		 }
	     }
	   if (pathName == bJetPlots_pathNameCalo)
	     {
	       edm::Handle<reco::JetTagCollection> csvCaloTags;
	       iEvent.getByToken(csvCaloTagsToken_, csvCaloTags);
	       edm::Handle<vector<reco::CaloJet>> csvCaloJets;
	       iEvent.getByToken(csvCaloJetsToken_, csvCaloJets);


	       if (csvCaloTags.isValid() && csvCaloJets.isValid())
		 {
		   for (auto iter = csvCaloTags->begin(); iter != csvCaloTags->end(); iter++) bJetCSVCalo_->Fill(iter->second);
		 }
	     }

	   //muon dxy(use an unique path)
	   else if (pathName == muonDxyPlots_pathName)
	     {
	       edm::Handle<vector<reco::RecoChargedCandidate>> recoChargedCands;
	       iEvent.getByToken(chargedCandToken_, recoChargedCands);
	       edm::Handle<reco::BeamSpot> recoBeamSpot;
	       iEvent.getByToken(beamSpotToken_, recoBeamSpot);
	       double muon_dxy;

	       if (recoChargedCands.isValid() && recoBeamSpot.isValid())
		 {
		   for (const auto & key : keys)
		     {
		       muon_dxy = dxyFinder(objects[key].eta(), objects[key].phi(), recoChargedCands, recoBeamSpot);
		       if (muon_dxy != -99.) muonDxy_->Fill(muon_dxy);
		     }
		 }
	     }

	   // ////////////////////////////////
	   // ///
	   // /// double-object plots
	   // ///
	   // ////////////////////////////////

	   //double muon low mass
	   else if (pathName == diMuonLowMass_pathName)
	     {
	       const double mu_mass(.105658);
	       unsigned int kCnt0 = 0;
	       for (const auto & key0: keys)
		 {
		   unsigned int kCnt1 = 0;
		   for (const auto & key1: keys)
		     {
		       if (key0 != key1 && kCnt1 > kCnt0) // avoid filling hists with same objs && avoid double counting separate objs
			 {
			   if (abs(objects[key0].id()) == 13 && (objects[key0].id()+objects[key1].id()==0))  // check muon id and dimuon charge
			     {
			       TLorentzVector mu1, mu2, dimu;
			       mu1.SetPtEtaPhiM(objects[key0].pt(), objects[key0].eta(), objects[key0].phi(), mu_mass);
			       mu2.SetPtEtaPhiM(objects[key1].pt(), objects[key1].eta(), objects[key1].phi(), mu_mass);
			       dimu = mu1+mu2;
			       diMuonLowMass_->Fill(dimu.M());
			     }
			 }
		       kCnt1 +=1;
		     }
		   kCnt0 +=1;
		 }
	     } //end double object plot

	   else if (pathName == diMuonMass_pathName || pathName == diMuonMass_pathNameOR)
	     {
	       const double mu_mass(.105658);
	       unsigned int kCnt0 = 0;
	       for (const auto & key0: keys)
		 {
		   unsigned int kCnt1 = 0;
		   for (const auto & key1: keys)
		     {
		       if (key0 != key1 && kCnt1 > kCnt0) // avoid filling hists with same objs && avoid double counting separate objs
			 {
			   if (abs(objects[key0].id()) == 13 && (objects[key0].id()+objects[key1].id()==0))  // check muon id and dimuon charge
			     {
			       TLorentzVector mu1, mu2, dimu;
			       mu1.SetPtEtaPhiM(objects[key0].pt(), objects[key0].eta(), objects[key0].phi(), mu_mass);
			       mu2.SetPtEtaPhiM(objects[key1].pt(), objects[key1].eta(), objects[key1].phi(), mu_mass);
			       dimu = mu1+mu2;
			       diMuonMass_->Fill(dimu.M());
			     }
			 }
		       kCnt1 +=1;
		     }
		   kCnt0 +=1;
		 }
	     }

	   else if (pathName == diElecMass_pathName)
	     {
	       unsigned int kCnt0 = 0;
	       for (const auto & key0: keys)
		 {
		   unsigned int kCnt1 = 0;
		   for (const auto & key1: keys)
		     {
		       if (key0 != key1 && kCnt1 > kCnt0) // avoid filling hists with same objs && avoid double counting separate objs
			 {
			   //                   if (abs(objects[key0].id()) == 11 && (objects[key0].id()+objects[key1].id()==0))  // id is not filled for electrons
			   //                     {
			   TLorentzVector el1, el2, diEl;
			   el1.SetPtEtaPhiM(objects[key0].pt(), objects[key0].eta(), objects[key0].phi(), 0);
			   el2.SetPtEtaPhiM(objects[key1].pt(), objects[key1].eta(), objects[key1].phi(), 0);
			   diEl = el1+el2;
			   diElecMass_->Fill(diEl.M());
			   //                     }
			 }
		       kCnt1 +=1;
		     }
		   kCnt0 +=1;
		 }
	     } //end double object plot
	 }
     }

   //   sleep(1); //sleep for 1s, used to calibrate timing
   double end = get_wall_time();
   double wallTime = end - start;
   wallTimePerEvent_->Fill(wallTime);
}

// ------------ method called when starting to processes a run  ------------
void
HLTObjectMonitor::dqmBeginRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
  if (debugPrint) std::cout << "Calling beginRun. " << std::endl;
  bool changed = true;
  if (hltConfig_.init(iRun, iSetup, processName_, changed))
    {
      if (debugPrint) std::cout << "Extracting HLTconfig. " << std::endl;
    }

  string pathName_noVersion;
  vector<string> triggerPaths = hltConfig_.triggerNames();
  for (const auto & pathName : triggerPaths)
    {
      pathName_noVersion = hltConfig_.removeVersion(pathName);
      if (lookupIndex.find(pathName_noVersion) == lookupIndex.end())
	{
	  lookupIndex[pathName_noVersion] = hltConfig_.triggerIndex(pathName);
	}
    }

  // setup string names
  razor_pathName = rsq_TH1.getParameter<string>("pathName");
  alphaT_pathName = alphaT_TH1.getParameter<string>("pathName");
  photonPlots_pathName = photonPt_TH1.getParameter<string>("pathName");
  muonPlots_pathName = muonPt_TH1.getParameter<string>("pathName");
  l2muonPlots_pathName = l2muonPt_TH1.getParameter<string>("pathName");
  l2NoBPTXmuonPlots_pathName = l2NoBPTXmuonPt_TH1.getParameter<string>("pathName");
  electronPlots_pathName = electronPt_TH1.getParameter<string>("pathName");
  jetPt_pathName = jetPt_TH1.getParameter<string>("pathName");
  jetAK8Plots_pathName = jetAK8Pt_TH1.getParameter<string>("pathName");
  tauPt_pathName = tauPt_TH1.getParameter<string>("pathName");
  diMuonLowMass_pathName = diMuonLowMass_TH1.getParameter<string>("pathName");
  caloMetPlots_pathName = caloMetPt_TH1.getParameter<string>("pathName");
  pfMetPlots_pathName = pfMetPt_TH1.getParameter<string>("pathName");
  caloHtPt_pathName = caloHtPt_TH1.getParameter<string>("pathName");
  pfHtPt_pathName = pfHtPt_TH1.getParameter<string>("pathName");
  bJetPlots_pathName = bJetPhi_TH1.getParameter<string>("pathName");
  bJetPlots_pathNameOR = bJetPhi_TH1.getParameter<string>("pathName_OR");
  bJetPlots_pathNameCalo = bJetCSVCalo_TH1.getParameter<string>("pathName");
  bJetPlots_pathNamePF = bJetCSVPF_TH1.getParameter<string>("pathName");
  diMuonMass_pathName = diMuonMass_TH1.getParameter<string>("pathName");
  diMuonMass_pathNameOR = diMuonMass_TH1.getParameter<string>("pathName_OR");
  diElecMass_pathName = diElecMass_TH1.getParameter<string>("pathName");
  muonDxyPlots_pathName = muonDxy_TH1.getParameter<string>("pathName");

  //link all paths and filters needed
  if (lookupIndex.count(razor_pathName) > 0)
    {
      quickCollectionPaths.push_back(razor_pathName);
      lookupFilter[razor_pathName] = rsq_TH1.getParameter<string>("moduleName");
    }
  if (lookupIndex.count(photonPlots_pathName) > 0)
    {
      quickCollectionPaths.push_back(photonPlots_pathName);
      lookupFilter[photonPlots_pathName] = photonPt_TH1.getParameter<string>("moduleName");
    }
  if (lookupIndex.count(muonPlots_pathName) > 0)
    {
      quickCollectionPaths.push_back(muonPlots_pathName);
      lookupFilter[muonPlots_pathName] = muonPt_TH1.getParameter<string>("moduleName");
    }
  if (lookupIndex.count(l2muonPlots_pathName) > 0)
    {
      quickCollectionPaths.push_back(l2muonPlots_pathName);
      lookupFilter[l2muonPlots_pathName] = l2muonPt_TH1.getParameter<string>("moduleName");
    }
  if (lookupIndex.count(l2NoBPTXmuonPlots_pathName) > 0)
    {
      quickCollectionPaths.push_back(l2NoBPTXmuonPlots_pathName);
      lookupFilter[l2NoBPTXmuonPlots_pathName] = l2NoBPTXmuonPt_TH1.getParameter<string>("moduleName");
    }
  if (lookupIndex.count(electronPlots_pathName) > 0)
    {
      quickCollectionPaths.push_back(electronPlots_pathName);
      lookupFilter[electronPlots_pathName] = electronPt_TH1.getParameter<string>("moduleName");
    }
  if (lookupIndex.count(diMuonLowMass_pathName) > 0)
    {
      quickCollectionPaths.push_back(diMuonLowMass_pathName);
      lookupFilter[diMuonLowMass_pathName] = diMuonLowMass_TH1.getParameter<string>("moduleName");
    }
  if (lookupIndex.count(alphaT_pathName) > 0)
    {
      quickCollectionPaths.push_back(alphaT_TH1.getParameter<string> ("pathName"));
      lookupFilter[alphaT_pathName] = alphaT_TH1.getParameter<string> ("moduleName");
    }
  if (lookupIndex.count(jetPt_pathName) > 0)
    {
      quickCollectionPaths.push_back(jetPt_pathName);
      lookupFilter[jetPt_pathName] = jetPt_TH1.getParameter<string>("moduleName");
    }
  if (lookupIndex.count(jetAK8Plots_pathName) > 0)
    {
      quickCollectionPaths.push_back(jetAK8Plots_pathName);
      lookupFilter[jetAK8Plots_pathName] = jetAK8Pt_TH1.getParameter<string>("moduleName");
    }
  if (lookupIndex.count(caloMetPlots_pathName) >0)
    {
      quickCollectionPaths.push_back(caloMetPlots_pathName);
      lookupFilter[caloMetPlots_pathName] = caloMetPt_TH1.getParameter<string>("moduleName");
    }
  if (lookupIndex.count(pfHtPt_pathName) > 0)
    {
      quickCollectionPaths.push_back(pfHtPt_pathName);
      lookupFilter[pfHtPt_pathName] = pfHtPt_TH1.getParameter<string>("moduleName");
    }
  if (lookupIndex.count(tauPt_pathName) > 0)
    {
      quickCollectionPaths.push_back(tauPt_pathName);
      lookupFilter[tauPt_pathName] = tauPt_TH1.getParameter<string>("moduleName");
    }
  if (lookupIndex.count(pfMetPlots_pathName) >0)
    {
      quickCollectionPaths.push_back(pfMetPlots_pathName);
      lookupFilter[pfMetPlots_pathName] = pfMetPt_TH1.getParameter<string>("moduleName");
    }
  if (lookupIndex.count(caloHtPt_pathName) >0)
    {
      quickCollectionPaths.push_back(caloHtPt_pathName);
      lookupFilter[caloHtPt_pathName] = caloHtPt_TH1.getParameter<string>("moduleName");
    }
  if (lookupIndex.count(bJetPlots_pathName) >0)
    {
      quickCollectionPaths.push_back(bJetPlots_pathName);
      lookupFilter[bJetPlots_pathName] = bJetPhi_TH1.getParameter<string>("moduleName");
    }
  if (lookupIndex.count(bJetPlots_pathNameOR) >0)
    {
      quickCollectionPaths.push_back(bJetPlots_pathNameOR);
      lookupFilter[bJetPlots_pathNameOR] = bJetEta_TH1.getParameter<string>("moduleName_OR");
    }
  if (lookupIndex.count(bJetPlots_pathNameCalo) >0)
    {
      quickCollectionPaths.push_back(bJetPlots_pathNameCalo);
      lookupFilter[bJetPlots_pathNameCalo] = bJetCSVCalo_TH1.getParameter<string>("moduleName");
    }
  if (lookupIndex.count(bJetPlots_pathNamePF) >0)
    {
      quickCollectionPaths.push_back(bJetPlots_pathNamePF);
      lookupFilter[bJetPlots_pathNamePF] = bJetCSVPF_TH1.getParameter<string>("moduleName");
    }
  if (lookupIndex.count(diMuonMass_pathName) >0)
    {
      quickCollectionPaths.push_back(diMuonMass_pathName);
      lookupFilter[diMuonMass_pathName] = diMuonMass_TH1.getParameter<string>("moduleName");
    }
  if (lookupIndex.count(diMuonMass_pathNameOR) >0)
    {
      quickCollectionPaths.push_back(diMuonMass_pathNameOR);
      lookupFilter[diMuonMass_pathNameOR] = diMuonMass_TH1.getParameter<string>("moduleName_OR");
    }
  if (lookupIndex.count(diElecMass_pathName) >0)
    {
      quickCollectionPaths.push_back(diElecMass_pathName);
      lookupFilter[diElecMass_pathName] = diElecMass_TH1.getParameter<string>("moduleName");
    }
  if (lookupIndex.count(muonDxyPlots_pathName) > 0)
    {
      quickCollectionPaths.push_back(muonDxyPlots_pathName);
      lookupFilter[muonDxyPlots_pathName] = muonDxy_TH1.getParameter<string>("moduleName");
    }


}

// ------------ method called when ending the processing of a run  ------------

void
HLTObjectMonitor::endRun(edm::Run const&, edm::EventSetup const&)
{
  if (debugPrint) std::cout << "Calling endRun. " << std::endl;
}

void HLTObjectMonitor::bookHistograms(DQMStore::IBooker & ibooker, edm::Run const& iRun, edm::EventSetup const& iSetup)
{

  ////////////////////////////////
  ///
  /// Main shifter workspace plots
  ///
  ////////////////////////////////
  ibooker.setCurrentFolder(mainShifterFolder);

  //wall time
  wallTimePerEvent_ = ibooker.book1D("wallTime","wall time per event",1000,0,0.01);
  wallTimePerEvent_->setAxisTitle("wall time per event [seconds]");

  //photon pt
  if (lookupIndex.count(photonPlots_pathName) > 0)
    {
      photonPt_ = ibooker.book1D("Photon_pT",photonPlots_pathName.c_str(),photonPt_TH1.getParameter<int>("NbinsX"),photonPt_TH1.getParameter<int>("Xmin"),photonPt_TH1.getParameter<int>("Xmax"));
      photonPt_->setAxisTitle("photon p_{T} [GeV]");
    }
  //muon pt
  if (lookupIndex.count(muonPlots_pathName) > 0)
    {
      muonPt_ = ibooker.book1D("Muon_pT",muonPlots_pathName.c_str(),muonPt_TH1.getParameter<int>("NbinsX"),muonPt_TH1.getParameter<int>("Xmin"),muonPt_TH1.getParameter<int>("Xmax"));
      muonPt_->setAxisTitle("muon p_{T} [GeV]");
    }
  //l2 muon pt
  if (lookupIndex.count(l2muonPlots_pathName) > 0)
    {
      l2muonPt_ = ibooker.book1D("L2Muon_pT",l2muonPlots_pathName.c_str(),l2muonPt_TH1.getParameter<int>("NbinsX"),l2muonPt_TH1.getParameter<int>("Xmin"),l2muonPt_TH1.getParameter<int>("Xmax"));
      l2muonPt_->setAxisTitle("L2 muon p_{T} [GeV]");
    }
  //l2 NoBPTX muon pt
  if (lookupIndex.count(l2NoBPTXmuonPlots_pathName) > 0)
    {
      l2NoBPTXmuonPt_ = ibooker.book1D("L2NoBPTXMuon_pT",l2NoBPTXmuonPlots_pathName.c_str(),l2NoBPTXmuonPt_TH1.getParameter<int>("NbinsX"),l2NoBPTXmuonPt_TH1.getParameter<int>("Xmin"),l2NoBPTXmuonPt_TH1.getParameter<int>("Xmax"));
      l2NoBPTXmuonPt_->setAxisTitle("L2 No BPTX muon p_{T} [GeV]");
    }
  //electron pt
  if (lookupIndex.count(electronPlots_pathName) > 0)
    {
      electronPt_ = ibooker.book1D("Electron_pT",electronPlots_pathName.c_str(),electronPt_TH1.getParameter<int>("NbinsX"),electronPt_TH1.getParameter<int>("Xmin"),electronPt_TH1.getParameter<int>("Xmax"));
      electronPt_->setAxisTitle("electron p_{T} [GeV]");
    }
  //jet pt
  if (lookupIndex.count(jetPt_pathName) > 0)
    {
      jetPt_ = ibooker.book1D("Jet_pT",jetPt_pathName.c_str(),jetPt_TH1.getParameter<int>("NbinsX"),jetPt_TH1.getParameter<int>("Xmin"),jetPt_TH1.getParameter<int>("Xmax"));
      jetPt_->setAxisTitle("jet p_{T} [GeV]");
    }
  //jetAK8 pt + mass
  if (lookupIndex.count(jetAK8Plots_pathName) > 0)
    {
      //ak8 jet pt
      jetAK8Pt_ = ibooker.book1D("JetAK8_pT",jetAK8Plots_pathName.c_str(),jetAK8Pt_TH1.getParameter<int>("NbinsX"),jetAK8Pt_TH1.getParameter<int>("Xmin"),jetAK8Pt_TH1.getParameter<int>("Xmax"));
      jetAK8Pt_->setAxisTitle("AK8 jet p_{T} [GeV]");
      //ak8 jet mass
      jetAK8Mass_ = ibooker.book1D("JetAK8_mass",jetAK8Plots_pathName.c_str(),jetAK8Mass_TH1.getParameter<int>("NbinsX"),jetAK8Mass_TH1.getParameter<int>("Xmin"),jetAK8Mass_TH1.getParameter<int>("Xmax"));
      jetAK8Mass_->setAxisTitle("AK8 jet mass [GeV]");
    }
  //tau pt
  if (lookupIndex.count(tauPt_pathName) > 0)
    {
      tauPt_ = ibooker.book1D("Tau_pT",tauPt_pathName.c_str(),tauPt_TH1.getParameter<int>("NbinsX"),tauPt_TH1.getParameter<int>("Xmin"),tauPt_TH1.getParameter<int>("Xmax"));
      tauPt_->setAxisTitle("tau p_{T} [GeV]");
    }
  //dimuon low mass
  if (lookupIndex.count(diMuonLowMass_pathName) > 0)
    {
      diMuonLowMass_ = ibooker.book1D("Dimuon_LowMass",diMuonLowMass_pathName.c_str(),diMuonLowMass_TH1.getParameter<int>("NbinsX"),diMuonLowMass_TH1.getParameter<double>("Xmin"),diMuonLowMass_TH1.getParameter<double>("Xmax"));
      diMuonLowMass_->setAxisTitle("di-muon low mass [GeV]");
    }
  //alphaT
  if (lookupIndex.count(alphaT_pathName) > 0)
    {
      alphaT_ = ibooker.book1D("alphaT",alphaT_pathName.c_str(),alphaT_TH1.getParameter<int>("NbinsX"),alphaT_TH1.getParameter<int>("Xmin"),alphaT_TH1.getParameter<int>("Xmax"));
      alphaT_->setAxisTitle("Alpha_{T}");
    }
  //caloMET pt
  if (lookupIndex.count(caloMetPlots_pathName) >0)
    {
      caloMetPt_ = ibooker.book1D("CaloMET_pT",caloMetPlots_pathName.c_str(),caloMetPt_TH1.getParameter<int>("NbinsX"),caloMetPt_TH1.getParameter<int>("Xmin"),caloMetPt_TH1.getParameter<int>("Xmax"));
      caloMetPt_->setAxisTitle("calo MET p_{T} [GeV]");
    }
  //caloHT pt
  if (lookupIndex.count(caloHtPt_pathName) >0)
    {
      caloHtPt_ = ibooker.book1D("CaloHT_pT",caloHtPt_pathName.c_str(),caloHtPt_TH1.getParameter<int>("NbinsX"),caloHtPt_TH1.getParameter<int>("Xmin"),caloHtPt_TH1.getParameter<int>("Xmax"));
      caloHtPt_->setAxisTitle("calo HT p_{T} [GeV]");
    }
  //PFHT pt
  if (lookupIndex.count(pfHtPt_pathName) > 0)
    {
      pfHtPt_ = ibooker.book1D("PFHT_pT",pfHtPt_pathName.c_str(),pfHtPt_TH1.getParameter<int>("NbinsX"),pfHtPt_TH1.getParameter<int>("Xmin"),pfHtPt_TH1.getParameter<int>("Xmax"));
      pfHtPt_->setAxisTitle("PF HT p_{T} [GeV]");
    }
  //PFMET pt
  if (lookupIndex.count(pfMetPlots_pathName) >0)
    {
      pfMetPt_ = ibooker.book1D("PFMET_pT",pfMetPlots_pathName.c_str(),pfMetPt_TH1.getParameter<int>("NbinsX"),pfMetPt_TH1.getParameter<int>("Xmin"),pfMetPt_TH1.getParameter<int>("Xmax"));
      pfMetPt_->setAxisTitle("PF MET p_{T} [GeV]");
    }
  //dimuon mass
  if (lookupIndex.count(diMuonMass_pathName) >0 || lookupIndex.count(diMuonMass_pathNameOR) >0)
    {
      std::string title_paths_diMuonMass = diMuonMass_pathName + " + " + diMuonMass_pathNameOR;
      diMuonMass_ = ibooker.book1D("diMuon_Mass",title_paths_diMuonMass.c_str(),diMuonMass_TH1.getParameter<int>("NbinsX"),diMuonMass_TH1.getParameter<int>("Xmin"),diMuonMass_TH1.getParameter<int>("Xmax"));
      diMuonMass_->setAxisTitle("dimuon mass [GeV]");
    }
  //razor
  if (lookupIndex.count(razor_pathName) > 0)
    {
      rsq_ = ibooker.book1D("rsq",razor_pathName.c_str(), rsq_TH1.getParameter<int>("NbinsX"), rsq_TH1.getParameter<int>("Xmin"), rsq_TH1.getParameter<int>("Xmax"));
      rsq_->setAxisTitle("R^{2}");

      mr_ = ibooker.book1D("mr",razor_pathName.c_str(), mr_TH1.getParameter<int>("NbinsX"), mr_TH1.getParameter<int>("Xmin"), mr_TH1.getParameter<int>("Xmax"));
      mr_->setAxisTitle("M_{R} [GeV]");
    }
  //dielectron mass
  if (lookupIndex.count(diElecMass_pathName) >0)
    {
      diElecMass_ = ibooker.book1D("diElec_Mass",diElecMass_pathName.c_str(),diElecMass_TH1.getParameter<int>("NbinsX"),diElecMass_TH1.getParameter<int>("Xmin"),diElecMass_TH1.getParameter<int>("Xmax"));
      diElecMass_->setAxisTitle("dielectron mass [GeV]");
    }
  // muon dxy
  if (lookupIndex.count(muonDxyPlots_pathName) > 0)
    {
      muonDxy_ = ibooker.book1D("Muon_dxy",muonDxyPlots_pathName.c_str(),muonDxy_TH1.getParameter<int>("NbinsX"),muonDxy_TH1.getParameter<int>("Xmin"),muonDxy_TH1.getParameter<int>("Xmax"));
      muonDxy_->setAxisTitle("muon d_{xy} [mm]");
    }
  //CSV
  if (lookupIndex.count(bJetPlots_pathNameCalo) >0)
    {
      bJetCSVCalo_ = ibooker.book1D("bJetCSVCalo",bJetPlots_pathNameCalo.c_str(),bJetCSVCalo_TH1.getParameter<int>("NbinsX"),bJetCSVCalo_TH1.getParameter<int>("Xmin"),bJetCSVCalo_TH1.getParameter<int>("Xmax"));
      bJetCSVCalo_->setAxisTitle("calo b-jet CSV");
    }
  if (lookupIndex.count(bJetPlots_pathNamePF) >0)
    {
      bJetCSVPF_ = ibooker.book1D("bJetCSVPF",bJetPlots_pathNamePF.c_str(),bJetCSVPF_TH1.getParameter<int>("NbinsX"),bJetCSVPF_TH1.getParameter<int>("Xmin"),bJetCSVPF_TH1.getParameter<int>("Xmax"));
      bJetCSVPF_->setAxisTitle("PF b-jet CSV");
    }

  ////////////////////////////////
  ///
  // Backup workspace plots
  ///
  ////////////////////////////////
  ibooker.setCurrentFolder(backupFolder);

  if (lookupIndex.count(photonPlots_pathName) > 0)
    {
      //photon eta
      photonEta_ = ibooker.book1D("Photon_eta",photonPlots_pathName.c_str(),photonEta_TH1.getParameter<int>("NbinsX"),photonEta_TH1.getParameter<int>("Xmin"),photonEta_TH1.getParameter<int>("Xmax"));
      photonEta_->setAxisTitle("photon eta");
      //photon phi
      photonPhi_ = ibooker.book1D("Photon_phi",photonPlots_pathName.c_str(),photonPhi_TH1.getParameter<int>("NbinsX"),photonPhi_TH1.getParameter<double>("Xmin"),photonPhi_TH1.getParameter<double>("Xmax"));
      photonPhi_->setAxisTitle("photon phi");
    }
  if (lookupIndex.count(muonPlots_pathName) > 0)
    {
      //muon eta
      muonEta_ = ibooker.book1D("Muon_eta",muonPlots_pathName.c_str(),muonEta_TH1.getParameter<int>("NbinsX"),muonEta_TH1.getParameter<int>("Xmin"),muonEta_TH1.getParameter<int>("Xmax"));
      muonEta_->setAxisTitle("muon eta");
      //muon phi
      muonPhi_ = ibooker.book1D("Muon_phi",muonPlots_pathName.c_str(),muonPhi_TH1.getParameter<int>("NbinsX"),muonPhi_TH1.getParameter<double>("Xmin"),muonPhi_TH1.getParameter<double>("Xmax"));
      muonPhi_->setAxisTitle("muon phi");
    }
  if (lookupIndex.count(l2muonPlots_pathName) > 0)
    {
      //l2 muon eta
      l2muonEta_ = ibooker.book1D("L2Muon_eta",l2muonPlots_pathName.c_str(),l2muonEta_TH1.getParameter<int>("NbinsX"),l2muonEta_TH1.getParameter<int>("Xmin"),l2muonEta_TH1.getParameter<int>("Xmax"));
      l2muonEta_->setAxisTitle("L2muon eta");
      //l2 muon phi
      l2muonPhi_ = ibooker.book1D("L2Muon_phi",l2muonPlots_pathName.c_str(),l2muonPhi_TH1.getParameter<int>("NbinsX"),l2muonPhi_TH1.getParameter<double>("Xmin"),l2muonPhi_TH1.getParameter<double>("Xmax"));
      l2muonPhi_->setAxisTitle("L2muon phi");
    }
  if (lookupIndex.count(l2NoBPTXmuonPlots_pathName) > 0)
    {
      //l2NoBPTXmuon eta
      l2NoBPTXmuonEta_ = ibooker.book1D("L2NoBPTXMuon_eta",l2NoBPTXmuonPlots_pathName.c_str(),l2NoBPTXmuonEta_TH1.getParameter<int>("NbinsX"),l2NoBPTXmuonEta_TH1.getParameter<int>("Xmin"),l2NoBPTXmuonEta_TH1.getParameter<int>("Xmax"));
      l2NoBPTXmuonEta_->setAxisTitle("L2NoBPTXmuon eta");
      //l2NoBPTXmuon phi
      l2NoBPTXmuonPhi_ = ibooker.book1D("L2NoBPTXMuon_phi",l2NoBPTXmuonPlots_pathName.c_str(),l2NoBPTXmuonPhi_TH1.getParameter<int>("NbinsX"),l2NoBPTXmuonPhi_TH1.getParameter<double>("Xmin"),l2NoBPTXmuonPhi_TH1.getParameter<double>("Xmax"));
      l2NoBPTXmuonPhi_->setAxisTitle("L2NoBPTXmuon phi");
    }
  if (lookupIndex.count(electronPlots_pathName) > 0)
    {
      //electron eta
      electronEta_ = ibooker.book1D("Electron_eta",electronPlots_pathName.c_str(),electronEta_TH1.getParameter<int>("NbinsX"),electronEta_TH1.getParameter<int>("Xmin"),electronEta_TH1.getParameter<int>("Xmax"));
      electronEta_->setAxisTitle("electron eta");
      //electron phi
      electronPhi_ = ibooker.book1D("Electron_phi",electronPlots_pathName.c_str(),electronPhi_TH1.getParameter<int>("NbinsX"),electronPhi_TH1.getParameter<double>("Xmin"),electronPhi_TH1.getParameter<double>("Xmax"));
      electronPhi_->setAxisTitle("electron phi");
    }
  if (lookupIndex.count(caloMetPlots_pathName) >0)
    {
      //caloMET phi
      caloMetPhi_ = ibooker.book1D("CaloMET_phi",caloMetPlots_pathName.c_str(),caloMetPhi_TH1.getParameter<int>("NbinsX"),caloMetPhi_TH1.getParameter<double>("Xmin"),caloMetPhi_TH1.getParameter<double>("Xmax"));
      caloMetPhi_->setAxisTitle("calo MET phi");
    }
  if (lookupIndex.count(pfMetPlots_pathName) >0)
    {
      //PFMET phi
      pfMetPhi_ = ibooker.book1D("PFMET_phi",pfMetPlots_pathName.c_str(),pfMetPhi_TH1.getParameter<int>("NbinsX"),pfMetPhi_TH1.getParameter<double>("Xmin"),pfMetPhi_TH1.getParameter<double>("Xmax"));
      pfMetPhi_->setAxisTitle("PF MET phi");
    }
  if (lookupIndex.count(bJetPlots_pathNameCalo) >0 || lookupIndex.count(bJetPlots_pathNamePF) >0)
    //  if (lookupIndex.count(bJetPlots_pathName) >0 || lookupIndex.count(bJetPlots_pathNameOR) >0)
    {
      std::string bJet_pathsTitle = bJetPlots_pathNameCalo + " + " + bJetPlots_pathNamePF;
      //bJet phi
      bJetPhi_ = ibooker.book1D("bJet_phi",bJet_pathsTitle.c_str(),bJetPhi_TH1.getParameter<int>("NbinsX"),bJetPhi_TH1.getParameter<double>("Xmin"),bJetPhi_TH1.getParameter<double>("Xmax"));
      bJetPhi_->setAxisTitle("b-jet phi");
      //bJet eta
      bJetEta_ = ibooker.book1D("bJet_eta",bJet_pathsTitle.c_str(),bJetEta_TH1.getParameter<int>("NbinsX"),bJetEta_TH1.getParameter<int>("Xmin"),bJetEta_TH1.getParameter<int>("Xmax"));
      bJetEta_->setAxisTitle("b-jet eta");
    }
}

double HLTObjectMonitor::dxyFinder(double eta, double phi, edm::Handle<reco::RecoChargedCandidateCollection> recoChargedCands, edm::Handle<reco::BeamSpot> recoBeamSpot)
{
  double dxy = -99.;
  for (reco::RecoChargedCandidateCollection::const_iterator l3Muon = recoChargedCands->begin(); l3Muon != recoChargedCands->end(); l3Muon++)
    {
      if (deltaR(eta,phi,l3Muon->eta(),l3Muon->phi()) < 0.1)
        {
          dxy = (-(l3Muon->vx()-recoBeamSpot->x0()) * l3Muon->py() + (l3Muon->vy()-recoBeamSpot->y0()) * l3Muon->px())/l3Muon->pt();
          break;
        }
    }
  return dxy;
}

double HLTObjectMonitor::get_wall_time()
{
  struct timeval time;
  if (gettimeofday(&time,NULL)) return 0;
  return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

// ------------ method called when starting to processes a luminosity block  ------------
/*
void
HLTObjectMonitor::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
HLTObjectMonitor::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
// void
// HLTObjectMonitor::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
//   //The following says we do not know what parameters are allowed so do no validation
//   // Please change this to state exactly what you do use, even if it is no parameters
//   edm::ParameterSetDescription desc;
//   desc.setUnknown();
//   descriptions.addDefault(desc);
// }

//define this as a plug-in
DEFINE_FWK_MODULE(HLTObjectMonitor);
