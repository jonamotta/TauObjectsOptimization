#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <iostream>
#include <TLorentzVector.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TPaveText.h>
#include <TStyle.h>
#include <TROOT.h>
#include <sstream>
#include <TBranchElement.h>
#include <fstream>
#include <TGraphAsymmErrors.h>
#include <stdio.h>
#include <math.h>

using namespace std;

// input is a MERGED root file and output is a MATCHED root file

void MakeTreeForCalibration(TString InputFileName, TString OutputFileName)

{
  // TChain data("Ntuplizer_noTagAndProbe_TagAndProbe");
  TChain data("Ntuplizer_TagAndProbe");

  data.Add(InputFileName.Data());

  Int_t           RunNumber = 0;
  ULong64_t       EventNumber = 0;
  Int_t           lumi = 0;
  Float_t         tauPt = 0;
  Float_t         tauEta = 0;
  Float_t         tauPhi = 0;
  Int_t           tauCharge = 0;
  Int_t           tauDecayMode = 0;
  Bool_t          hasTriggerMuonType = 0;
  Bool_t          hasTriggerTauType = 0;
  Bool_t          isMatched = 0;
  Bool_t          isOS = 0;
  Int_t           foundJet = 0;
  Int_t           Nvtx = 0;
  vector<float>   *l1tPt = 0;
  vector<float>   *l1tEta = 0;
  vector<float>   *l1tPhi = 0;
  vector<int>     *l1tQual = 0;
  vector<int>     *l1tIso = 0;
  vector<float>   *l1tEmuPt = 0 ;
  vector<float>   *l1tEmuEta = 0 ;
  vector<float>   *l1tEmuPhi = 0 ;
  vector<int>     *l1tEmuQual = 0 ;
  vector<int>     *l1tEmuIso = 0 ;
  vector<int>     *l1tEmuNTT = 0 ;
  vector<int>     *l1tEmuHasEM = 0 ;
  vector<int>     *l1tEmuIsMerged = 0 ;
  vector<int>     *l1tEmuTowerIEta = 0 ;
  vector<int>     *l1tEmuTowerIPhi = 0 ;
  vector<int>     *l1tEmuRawEt = 0 ;
  vector<int>     *l1tEmuIsoEt = 0 ;

  TBranch        *b_RunNumber;   //!
  TBranch        *b_EventNumber;   //!
  TBranch        *b_lumi;   //!
  TBranch        *b_tauPt;   //!
  TBranch        *b_tauEta;   //!
  TBranch        *b_tauPhi;   //!
  TBranch        *b_tauCharge;   //!
  TBranch        *b_tauDecayMode;   //!
  TBranch        *b_hasTriggerMuonType;   //!
  TBranch        *b_hasTriggerTauType;   //!
  TBranch        *b_isMatched;   //!
  TBranch        *b_isOS;   //!
  TBranch        *b_foundJet;   //!
  TBranch        *b_Nvtx;   //!
  TBranch        *b_l1tPt;   //!
  TBranch        *b_l1tEta;   //!
  TBranch        *b_l1tPhi;   //!
  TBranch        *b_l1tQual;   //!
  TBranch        *b_l1tIso;   //!
  TBranch        *b_l1tEmuPt;   //!
  TBranch        *b_l1tEmuEta;   //!
  TBranch        *b_l1tEmuPhi;   //!
  TBranch        *b_l1tEmuQual;   //!
  TBranch        *b_l1tEmuIso;   //!
  TBranch        *b_l1tEmuNTT;   //!
  TBranch        *b_l1tEmuHasEM;   //!
  TBranch        *b_l1tEmuIsMerged;   //!
  TBranch        *b_l1tEmuTowerIEta;   //!
  TBranch        *b_l1tEmuTowerIPhi;   //!
  TBranch        *b_l1tEmuRawEt;   //!
  TBranch        *b_l1tEmuIsoEt;   //!

  data.SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
  data.SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
  data.SetBranchAddress("lumi", &lumi, &b_lumi);
  data.SetBranchAddress("tauPt", &tauPt, &b_tauPt);
  data.SetBranchAddress("tauEta", &tauEta, &b_tauEta);
  data.SetBranchAddress("tauPhi", &tauPhi, &b_tauPhi);
  data.SetBranchAddress("tauCharge", &tauCharge, &b_tauCharge);
  data.SetBranchAddress("tauDecayMode", &tauDecayMode, &b_tauDecayMode);
  data.SetBranchAddress("hasTriggerMuonType", &hasTriggerMuonType, &b_hasTriggerMuonType);
  data.SetBranchAddress("hasTriggerTauType", &hasTriggerTauType, &b_hasTriggerTauType);
  data.SetBranchAddress("isMatched", &isMatched, &b_isMatched);
  data.SetBranchAddress("isOS", &isOS, &b_isOS);
  data.SetBranchAddress("foundJet", &foundJet, &b_foundJet);
  data.SetBranchAddress("Nvtx", &Nvtx, &b_Nvtx);
  data.SetBranchAddress("l1tPt", &l1tPt, &b_l1tPt);
  data.SetBranchAddress("l1tEta", &l1tEta, &b_l1tEta);
  data.SetBranchAddress("l1tPhi", &l1tPhi, &b_l1tPhi);
  data.SetBranchAddress("l1tQual", &l1tQual, &b_l1tQual);
  data.SetBranchAddress("l1tIso", &l1tIso, &b_l1tIso);
  data.SetBranchAddress("l1tEmuPt", &l1tEmuPt, &b_l1tEmuPt);
  data.SetBranchAddress("l1tEmuEta", &l1tEmuEta, &b_l1tEmuEta);
  data.SetBranchAddress("l1tEmuPhi", &l1tEmuPhi, &b_l1tEmuPhi);
  data.SetBranchAddress("l1tEmuQual", &l1tEmuQual, &b_l1tEmuQual);
  data.SetBranchAddress("l1tEmuIso", &l1tEmuIso, &b_l1tEmuIso);
  data.SetBranchAddress("l1tEmuNTT", &l1tEmuNTT, &b_l1tEmuNTT);
  data.SetBranchAddress("l1tEmuHasEM", &l1tEmuHasEM, &b_l1tEmuHasEM);
  data.SetBranchAddress("l1tEmuIsMerged", &l1tEmuIsMerged, &b_l1tEmuIsMerged);
  data.SetBranchAddress("l1tEmuTowerIEta", &l1tEmuTowerIEta, &b_l1tEmuTowerIEta);
  data.SetBranchAddress("l1tEmuTowerIPhi", &l1tEmuTowerIPhi, &b_l1tEmuTowerIPhi);
  data.SetBranchAddress("l1tEmuRawEt", &l1tEmuRawEt, &b_l1tEmuRawEt);
  data.SetBranchAddress("l1tEmuIsoEt", &l1tEmuIsoEt, &b_l1tEmuIsoEt);

  ULong64_t       out_indexevents = 0;
  Int_t           out_runNumber = 0;
  Int_t           out_lumi = 0;
  unsigned long out_tauTriggerBits = 0;
  float out_tauPt = 0;
  float out_tauEta = 0;
  float out_tauPhi = 0;
  int   out_tauCharge = 0;
  int   out_tauDecayMode = 0;
  float out_hltPt = 0;
  float out_hltEta = 0;
  float out_hltPhi = 0;
  int out_l1tQual = 0;
  float out_l1tPt = 0;
  float out_l1tEta = 0;
  float out_l1tPhi = 0;
  int out_l1tIso = 0;
  int out_l1tEmuQual = 0;
  float out_l1tEmuPt = 0;
  float out_l1tEmuEta = 0;
  float out_l1tEmuPhi = 0;
  int out_l1tEmuIso = 0;
  int out_l1tEmuNTT = 0;
  int out_l1tEmuHasEM = 0;
  int out_l1tEmuIsMerged = 0;
  int out_l1tEmuTowerIEta = 0;
  int out_l1tEmuTowerIPhi = 0;
  int out_l1tEmuRawEt = 0;
  int out_l1tEmuIsoEt = 0;
  Bool_t out_hasTriggerMuonType = 0;
  Bool_t out_hasTriggerTauType = 0;
  Bool_t out_isMatched = 0;
  Bool_t out_isOS = 0;
  int out_foundJet = 0;
  int out_Nvtx = 0;
  float out_Target = 0;


  TFile f(OutputFileName.Data(),"RECREATE");
  TTree outTree("outTreeForCalibration","outTreeForCalibration");  
  
  outTree.Branch("EventNumber",&out_indexevents,"EventNumber/l");
  outTree.Branch("RunNumber",&out_runNumber,"RunNumber/I");
  outTree.Branch("Lumi",&out_lumi,"lumi/I");
  outTree.Branch("OfflineTau_pt",  &out_tauPt,  "OfflineTau_pt/F");
  outTree.Branch("OfflineTau_eta", &out_tauEta, "OfflineTau_eta/F");
  outTree.Branch("OfflineTau_phi", &out_tauPhi, "OfflineTau_phi/F");
  outTree.Branch("OfflineTau_decayMode",  &out_tauDecayMode,  "OfflineTau_decayMode/I");
  outTree.Branch("L1Tau_pt",  &out_l1tEmuPt,  "L1Tau_pt/F");
  outTree.Branch("L1Tau_eta", &out_l1tEmuEta, "L1Tau_eta/F");
  outTree.Branch("L1Tau_phi", &out_l1tEmuPhi, "L1Tau_phi/F");
  outTree.Branch("L1Tau_nTT", &out_l1tEmuNTT, "L1Tau_nTT/I");
  outTree.Branch("L1Tau_hasEM", &out_l1tEmuHasEM, "L1Tau_hasEM/I");
  outTree.Branch("L1Tau_isMerged", &out_l1tEmuIsMerged, "L1Tau_isMerged/I");
  outTree.Branch("L1Tau_IEta", &out_l1tEmuTowerIEta, "L1Tau_IEta/I");
  outTree.Branch("L1Tau_RawIEt", &out_l1tEmuRawEt, "L1Tau_RawIEt/I");
  outTree.Branch("L1Tau_Iso", &out_l1tEmuIsoEt, "L1Tau_Iso/I");
  outTree.Branch("OfflineTau_isMatched", &out_isMatched, "OfflineTau_isMatched/O");//needs to be filled
  outTree.Branch("Target", &out_Target, "Target/F");
  outTree.Branch("L1Tau_Qual", &out_l1tEmuQual, "L1Tau_Qual/I");
  outTree.Branch("L1Tau_IsoFlag", &out_l1tEmuIso, "L1Tau_IsoFlag/I");
  outTree.Branch("Nvtx", &out_Nvtx, "Nvtx/I");

  for(UInt_t i = 0 ; i < data.GetEntries() ; ++i)
    {
      data.GetEntry(i);
      // cout<<"Entry #"<<i<<endl;
      if(i%10000==0) cout<<"Entry #"<<i<<endl;

      float highestL1TauPt = 0.;
      if(fabs(tauEta)>2.2) continue;
      UInt_t iMatchedL1Tau = 0;
      out_isMatched = false;
      
      for(UInt_t iL1Tau = 0 ; iL1Tau < l1tEmuPt->size() ; ++iL1Tau)
        {
          if(l1tEmuRawEt->at(iL1Tau)/2.<10.) continue;
          // if(l1tEmuRawEt->at(iL1Tau)/2.<10.) continue;
          if(fabs(l1tEmuEta->at(iL1Tau))>2.1) continue;

          TLorentzVector L1Tau;
    // L1Tau.SetPtEtaPhiM(l1tPt->at(iL1Tau),l1tEta->at(iL1Tau),l1tPhi->at(iL1Tau),0.);
          L1Tau.SetPtEtaPhiM(l1tEmuPt->at(iL1Tau),l1tEmuEta->at(iL1Tau),l1tEmuPhi->at(iL1Tau),0.);

          // cout<<"l1tEmuRawEt.at(iL1Tau)/2. = "<<l1tEmuRawEt->at(iL1Tau)/2.<<endl;
          // cout<<"l1tEmuEta.at(iL1Tau) = "<<l1tEmuEta->at(iL1Tau)<<endl;
          // cout<<"l1tEmuPhi.at(iL1Tau) = "<<l1tEmuPhi->at(iL1Tau)<<endl;

          TLorentzVector OfflineTau;
          OfflineTau.SetPtEtaPhiM(tauPt,tauEta,tauPhi,0.);

          //matching with offline
          if(L1Tau.DeltaR(OfflineTau)<0.5 && L1Tau.Pt()>highestL1TauPt)
            {
              highestL1TauPt = L1Tau.Pt();
              out_isMatched = true;
              iMatchedL1Tau = iL1Tau;
            }
        }

      if(out_isMatched)
      {
        out_indexevents = EventNumber;
        out_runNumber = RunNumber;
        out_lumi = lumi;
        out_tauPt = tauPt;
        out_tauEta = tauEta;
        out_tauPhi = tauPhi;
        out_tauCharge = tauCharge;
        out_tauDecayMode = tauDecayMode;

        out_l1tQual = l1tEmuQual->at(iMatchedL1Tau);
        out_l1tPt = l1tEmuPt->at(iMatchedL1Tau);
        out_l1tEta = l1tEmuEta->at(iMatchedL1Tau);
        out_l1tPhi = l1tEmuPhi->at(iMatchedL1Tau);
        // out_l1tIso = l1tEmuIso->at(iMatchedL1Tau);
        out_l1tEmuIso = l1tEmuIso->at(iMatchedL1Tau);
        // out_l1tQual = l1tQual->at(iMatchedL1Tau);
        // out_l1tPt = l1tPt->at(iMatchedL1Tau);
        // out_l1tEta = l1tEta->at(iMatchedL1Tau);
        // out_l1tPhi = l1tPhi->at(iMatchedL1Tau);
        // out_l1tIso = l1tIso->at(iMatchedL1Tau);

        out_l1tEmuQual = l1tEmuQual->at(iMatchedL1Tau);
        out_l1tEmuPt = l1tEmuPt->at(iMatchedL1Tau);
        out_l1tEmuEta = l1tEmuEta->at(iMatchedL1Tau);
        out_l1tEmuPhi = l1tEmuPhi->at(iMatchedL1Tau);
        // out_l1tEmuIso = l1tEmuIso->at(iMatchedL1Tau);
        out_l1tEmuNTT = l1tEmuNTT->at(iMatchedL1Tau);
        out_l1tEmuHasEM = l1tEmuHasEM->at(iMatchedL1Tau);
        out_l1tEmuIsMerged = l1tEmuIsMerged->at(iMatchedL1Tau);
        out_l1tEmuTowerIEta = l1tEmuTowerIEta->at(iMatchedL1Tau);
        out_l1tEmuTowerIPhi = l1tEmuTowerIPhi->at(iMatchedL1Tau);
        out_l1tEmuRawEt = l1tEmuRawEt->at(iMatchedL1Tau);
        out_l1tEmuIsoEt = l1tEmuIsoEt->at(iMatchedL1Tau);

        //out_Target = tauPt/(l1tPt->at(iMatchedL1Tau));
        out_Target = tauPt/(l1tEmuRawEt->at(iMatchedL1Tau)/2.);

        out_Nvtx = Nvtx;

        outTree.Fill();

      }
    }


  outTree.Write();
}
