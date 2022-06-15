#include "TauStage2Trees.h"

#include "TTree.h"
#include "TChain.h"

#include <iostream>


/*****************************************************************/
void TauStage2Trees::linkMainVariables()
/*****************************************************************/
{
    // main tree: offline and truth variable
    m_mainTree->SetBranchStatus("RunNumber"         , true);
    m_mainTree->SetBranchStatus("EventNumber"       , true);
    m_mainTree->SetBranchStatus("lumi"       , true);
    m_mainTree->SetBranchStatus("tauTriggerBits"       , true);
    m_mainTree->SetBranchStatus("tauPt"       , true);
    m_mainTree->SetBranchStatus("tauEta"       , true);
    m_mainTree->SetBranchStatus("tauPhi"       , true);
    m_mainTree->SetBranchStatus("tauCharge"       , true);
    m_mainTree->SetBranchStatus("tauDecayMode"       , true);
    // m_mainTree->SetBranchStatus("muonPt"       , true);
    // m_mainTree->SetBranchStatus("muonEta"       , true);
    // m_mainTree->SetBranchStatus("muonPhi"       , true);
    m_mainTree->SetBranchStatus("hasTriggerMuonType"       , true);
    m_mainTree->SetBranchStatus("hasTriggerTauType"       , true);
    m_mainTree->SetBranchStatus("isMatched"       , true);
    m_mainTree->SetBranchStatus("isOS"       , true);
    m_mainTree->SetBranchStatus("foundJet"       , true);
    m_mainTree->SetBranchStatus("Nvtx"       , true);

    //Jets variables
    m_mainTree->SetBranchStatus("JetsNumber", true);
    m_mainTree->SetBranchStatus("jets_px", true);
    m_mainTree->SetBranchStatus("jets_py", true);
    m_mainTree->SetBranchStatus("jets_pz", true);
    m_mainTree->SetBranchStatus("jets_e", true);
    m_mainTree->SetBranchStatus("jets_rawPt", true);
    m_mainTree->SetBranchStatus("jets_area", true);
    m_mainTree->SetBranchStatus("jets_mT", true);
    m_mainTree->SetBranchStatus("jets_PUJetID", true);
    m_mainTree->SetBranchStatus("jets_PUJetIDupdated", true);
    m_mainTree->SetBranchStatus("jets_vtxPt", true);
    m_mainTree->SetBranchStatus("jets_vtxMass", true);
    m_mainTree->SetBranchStatus("jets_vtx3dL", true);
    m_mainTree->SetBranchStatus("jets_vtxNtrk", true);
    m_mainTree->SetBranchStatus("jets_vtx3deL", true);
    m_mainTree->SetBranchStatus("jets_leadTrackPt", true);
    m_mainTree->SetBranchStatus("jets_leptonPtRel", true);
    m_mainTree->SetBranchStatus("jets_leptonPt", true);
    m_mainTree->SetBranchStatus("jets_leptonDeltaR", true);
    m_mainTree->SetBranchStatus("jets_chEmEF", true);
    m_mainTree->SetBranchStatus("jets_chHEF", true);
    m_mainTree->SetBranchStatus("jets_nEmEF", true);
    m_mainTree->SetBranchStatus("jets_nHEF", true);
    m_mainTree->SetBranchStatus("jets_MUF", true);
    m_mainTree->SetBranchStatus("jets_neMult", true);
    m_mainTree->SetBranchStatus("jets_chMult", true);
    m_mainTree->SetBranchStatus("jets_jecUnc", true);
    //    m_mainTree->SetBranchStatus("jets_QGdiscr", true);
    m_mainTree->SetBranchStatus("jets_Flavour", true);
    m_mainTree->SetBranchStatus("jets_HadronFlavour", true);
    m_mainTree->SetBranchStatus("jets_genjetIndex", true);
    // m_mainTree->SetBranchStatus("bdiscr", true);
    // m_mainTree->SetBranchStatus("bdiscr2", true);
    // m_mainTree->SetBranchStatus("bdiscr3", true);
    // m_mainTree->SetBranchStatus("jetID", true);
    // m_mainTree->SetBranchStatus("jetrawf", true);

    m_mainTree->SetBranchStatus("PFMET_pt", true);
    m_mainTree->SetBranchStatus("PFMET_phi", true);
    m_mainTree->SetBranchStatus("PFMET_px", true);
    m_mainTree->SetBranchStatus("PFMET_py", true);
    m_mainTree->SetBranchStatus("PFMET_sumEt", true);
    m_mainTree->SetBranchStatus("CaloMET_pt", true);
    m_mainTree->SetBranchStatus("CaloMET_phi", true);
    m_mainTree->SetBranchStatus("CaloMET_px", true);
    m_mainTree->SetBranchStatus("CaloMET_py", true);
    m_mainTree->SetBranchStatus("CaloMET_sumEt", true);


    m_mainTree->SetBranchAddress("RunNumber"         , &m_run);
    m_mainTree->SetBranchAddress("EventNumber"       , &m_event);
    m_mainTree->SetBranchAddress("lumi"         , &m_lumi);
    m_mainTree->SetBranchAddress("tauPt"         , &m_tauPt);
    m_mainTree->SetBranchAddress("tauEta"         , &m_tauEta);
    m_mainTree->SetBranchAddress("tauPhi"         , &m_tauPhi);
    m_mainTree->SetBranchAddress("tauCharge"         , &m_tauCharge);
    m_mainTree->SetBranchAddress("tauDecayMode"         , &m_tauDecayMode);
    m_mainTree->SetBranchAddress("hasTriggerMuonType"         , &m_hasTriggerMuonType);
    m_mainTree->SetBranchAddress("hasTriggerTauType"         , &m_hasTriggerTauType);
    m_mainTree->SetBranchAddress("isMatched"         , &m_isMatched);
    m_mainTree->SetBranchAddress("isOS"         , &m_isOS);
    m_mainTree->SetBranchAddress("foundJet"         , &m_foundJet);
    // m_mainTree->SetBranchAddress("muonPt"         , &m_muonPt);
    // m_mainTree->SetBranchAddress("muonEta"         , &m_muonEta);
    // m_mainTree->SetBranchAddress("muonPhi"         , &m_muonPhi);
    m_mainTree->SetBranchAddress("Nvtx"         , &m_Nvtx);

    //Jets variables
    m_mainTree->SetBranchAddress("JetsNumber", &m_JetsNumber);
    m_mainTree->SetBranchAddress("jets_px", &m_jets_px);
    m_mainTree->SetBranchAddress("jets_py", &m_jets_py);
    m_mainTree->SetBranchAddress("jets_pz", &m_jets_pz);
    m_mainTree->SetBranchAddress("jets_e", &m_jets_e);
    m_mainTree->SetBranchAddress("jets_rawPt", &m_jets_rawPt);
    m_mainTree->SetBranchAddress("jets_area", &m_jets_area);
    m_mainTree->SetBranchAddress("jets_mT", &m_jets_mT);
    m_mainTree->SetBranchAddress("jets_PUJetID", &m_jets_PUJetID);
    m_mainTree->SetBranchAddress("jets_PUJetIDupdated", &m_jets_PUJetIDupdated);
    m_mainTree->SetBranchAddress("jets_vtxPt", &m_jets_vtxPt);
    m_mainTree->SetBranchAddress("jets_vtxMass", &m_jets_vtxMass);
    m_mainTree->SetBranchAddress("jets_vtx3dL", &m_jets_vtx3dL);
    m_mainTree->SetBranchAddress("jets_vtxNtrk", &m_jets_vtxNtrk);
    m_mainTree->SetBranchAddress("jets_vtx3deL", &m_jets_vtx3deL);
    m_mainTree->SetBranchAddress("jets_leadTrackPt", &m_jets_leadTrackPt);
    m_mainTree->SetBranchAddress("jets_leptonPtRel", &m_jets_leptonPtRel) ;
    m_mainTree->SetBranchAddress("jets_leptonPt", &m_jets_leptonPt);    
    m_mainTree->SetBranchAddress("jets_leptonDeltaR", &m_jets_leptonDeltaR);
    m_mainTree->SetBranchAddress("jets_chEmEF", &m_jets_chEmEF);
    m_mainTree->SetBranchAddress("jets_chHEF", &m_jets_chHEF);
    m_mainTree->SetBranchAddress("jets_nEmEF", &m_jets_nEmEF);
    m_mainTree->SetBranchAddress("jets_nHEF", &m_jets_nHEF);
    m_mainTree->SetBranchAddress("jets_MUF", &m_jets_MUF);
    m_mainTree->SetBranchAddress("jets_neMult", &m_jets_neMult);
    m_mainTree->SetBranchAddress("jets_chMult", &m_jets_chMult);
    m_mainTree->SetBranchAddress("jets_jecUnc", &m_jets_jecUnc);
    //    m_mainTree->SetBranchAddress("jets_QGdiscr", &m_jets_QGdiscr);
    m_mainTree->SetBranchAddress("jets_Flavour", &m_jets_Flavour);
    m_mainTree->SetBranchAddress("jets_HadronFlavour", &m_jets_HadronFlavour);
    m_mainTree->SetBranchAddress("jets_genjetIndex", &m_jets_genjetIndex);
    // m_mainTree->SetBranchAddress("jets_bdiscr", &m_bdiscr);
    // m_mainTree->SetBranchAddress("bdiscr2", &m_bdiscr2);
    // m_mainTree->SetBranchAddress("bdiscr3", &m_bdiscr3);
    // m_mainTree->SetBranchAddress("jetID", &m_jetID);
    // m_mainTree->SetBranchAddress("jetrawf", &m_jetrawf);

    m_mainTree->SetBranchAddress("PFMET_pt", &m_PFMET_pt);
    m_mainTree->SetBranchAddress("PFMET_phi", &m_PFMET_phi);
    m_mainTree->SetBranchAddress("PFMET_px", &m_PFMET_px);
    m_mainTree->SetBranchAddress("PFMET_py", &m_PFMET_py);
    m_mainTree->SetBranchAddress("PFMET_sumEt", &m_PFMET_sumEt);

    m_mainTree->SetBranchAddress("CaloMET_pt", &m_CaloMET_pt);
    m_mainTree->SetBranchAddress("CaloMET_phi", &m_CaloMET_phi);
    m_mainTree->SetBranchAddress("CaloMET_px", &m_CaloMET_px);
    m_mainTree->SetBranchAddress("CaloMET_py", &m_CaloMET_py);
    m_mainTree->SetBranchAddress("CaloMET_sumEt", &m_CaloMET_sumEt);

}

/*****************************************************************/
void TauStage2Trees::linkSecondaryVariables()
/*****************************************************************/
{
    // Stage-2 secondary tree 
    m_secondaryTrees[0]->SetBranchStatus("RunNumber"         , true);
    m_secondaryTrees[0]->SetBranchStatus("EventNumber"       , true);
    m_secondaryTrees[0]->SetBranchStatus("l1tPt",  true);
    m_secondaryTrees[0]->SetBranchStatus("l1tEta", true);
    m_secondaryTrees[0]->SetBranchStatus("l1tPhi", true);
    m_secondaryTrees[0]->SetBranchStatus("l1tQual", true);
    m_secondaryTrees[0]->SetBranchStatus("l1tIso", true);
    m_secondaryTrees[0]->SetBranchStatus("l1tEmuPt",  true);
    m_secondaryTrees[0]->SetBranchStatus("l1tEmuEta", true);
    m_secondaryTrees[0]->SetBranchStatus("l1tEmuPhi", true);
    m_secondaryTrees[0]->SetBranchStatus("l1tEmuQual", true);
    m_secondaryTrees[0]->SetBranchStatus("l1tEmuIso", true);
    m_secondaryTrees[0]->SetBranchStatus("l1tEmuNTT", true);
    m_secondaryTrees[0]->SetBranchStatus("l1tEmuHasEM", true);
    m_secondaryTrees[0]->SetBranchStatus("l1tEmuIsMerged", true);
    m_secondaryTrees[0]->SetBranchStatus("l1tEmuTowerIEta", true);
    m_secondaryTrees[0]->SetBranchStatus("l1tEmuTowerIPhi", true);
    m_secondaryTrees[0]->SetBranchStatus("l1tEmuRawEt", true);
    m_secondaryTrees[0]->SetBranchStatus("l1tEmuIsoEt", true);

    m_secondaryTrees[0]->SetBranchStatus("genJet_pt", true);
    m_secondaryTrees[0]->SetBranchStatus("genJet_eta", true);
    m_secondaryTrees[0]->SetBranchStatus("genJet_phi", true);
    m_secondaryTrees[0]->SetBranchStatus("genJet_emEnergy", true);
    m_secondaryTrees[0]->SetBranchStatus("genJet_hadEnergy", true);
    m_secondaryTrees[0]->SetBranchStatus("genJet_invisibleEnergy", true);
    m_secondaryTrees[0]->SetBranchStatus("genJet_muonEnergy", true);
	
    m_secondaryTrees[0]->SetBranchStatus("genPart_id", true);
    m_secondaryTrees[0]->SetBranchStatus("genPart_stat", true);
    m_secondaryTrees[0]->SetBranchStatus("genPart_parent", true);
    m_secondaryTrees[0]->SetBranchStatus("genPart_pt", true);
    m_secondaryTrees[0]->SetBranchStatus("genPart_eta", true);
    m_secondaryTrees[0]->SetBranchStatus("genPart_phi", true);
    m_secondaryTrees[0]->SetBranchStatus("genPart_E", true);
    m_secondaryTrees[0]->SetBranchStatus("genPart_ch", true);
	
    m_secondaryTrees[0]->SetBranchStatus("nHCALTP", true);
    m_secondaryTrees[0]->SetBranchStatus("hcalTPieta", true);
    m_secondaryTrees[0]->SetBranchStatus("hcalTPiphi", true);
    m_secondaryTrees[0]->SetBranchStatus("hcalTPCaliphi", true);
    m_secondaryTrees[0]->SetBranchStatus("hcalTPet", true);
    m_secondaryTrees[0]->SetBranchStatus("hcalTPcompEt", true);
    m_secondaryTrees[0]->SetBranchStatus("hcalTPfineGrain", true);

    m_secondaryTrees[0]->SetBranchStatus("nECALTP", true);
    m_secondaryTrees[0]->SetBranchStatus("ecalTPieta", true);
    m_secondaryTrees[0]->SetBranchStatus("ecalTPiphi", true);
    m_secondaryTrees[0]->SetBranchStatus("ecalTPCaliphi", true);
    m_secondaryTrees[0]->SetBranchStatus("ecalTPet", true);
    m_secondaryTrees[0]->SetBranchStatus("ecalTPcompEt", true);
    m_secondaryTrees[0]->SetBranchStatus("ecalTPfineGrain", true);

    m_secondaryTrees[0]->SetBranchStatus("nTower", true);
    m_secondaryTrees[0]->SetBranchStatus("TT_ieta", true);
    m_secondaryTrees[0]->SetBranchStatus("TT_iphi", true);
    m_secondaryTrees[0]->SetBranchStatus("TT_iet", true);
    m_secondaryTrees[0]->SetBranchStatus("TT_iem", true);
    m_secondaryTrees[0]->SetBranchStatus("TT_ihad", true);
    m_secondaryTrees[0]->SetBranchStatus("TT_iratio", true);
    m_secondaryTrees[0]->SetBranchStatus("TT_iqual", true);
    m_secondaryTrees[0]->SetBranchStatus("TT_et", true);
    m_secondaryTrees[0]->SetBranchStatus("TT_eta", true);
    m_secondaryTrees[0]->SetBranchStatus("TT_phi", true);


    m_secondaryTrees[0]->SetBranchAddress("l1tPt", &m_l1tPt);
    m_secondaryTrees[0]->SetBranchAddress("l1tEta", &m_l1tEta);
    m_secondaryTrees[0]->SetBranchAddress("l1tPhi", &m_l1tPhi);
    m_secondaryTrees[0]->SetBranchAddress("l1tQual", &m_l1tQual);
    m_secondaryTrees[0]->SetBranchAddress("l1tIso", &m_l1tIso);
    m_secondaryTrees[0]->SetBranchAddress("l1tEmuPt",  &m_l1tEmuPt);
    m_secondaryTrees[0]->SetBranchAddress("l1tEmuEta", &m_l1tEmuEta);
    m_secondaryTrees[0]->SetBranchAddress("l1tEmuPhi", &m_l1tEmuPhi);
    m_secondaryTrees[0]->SetBranchAddress("l1tEmuQual", &m_l1tEmuQual);
    m_secondaryTrees[0]->SetBranchAddress("l1tEmuIso", &m_l1tEmuIso);
    m_secondaryTrees[0]->SetBranchAddress("l1tEmuNTT", &m_l1tEmuNTT);
    m_secondaryTrees[0]->SetBranchAddress("l1tEmuHasEM", &m_l1tEmuHasEM);
    m_secondaryTrees[0]->SetBranchAddress("l1tEmuIsMerged", &m_l1tEmuIsMerged);
    m_secondaryTrees[0]->SetBranchAddress("l1tEmuTowerIEta", &m_l1tEmuTowerIEta);
    m_secondaryTrees[0]->SetBranchAddress("l1tEmuTowerIPhi", &m_l1tEmuTowerIPhi);
    m_secondaryTrees[0]->SetBranchAddress("l1tEmuRawEt", &m_l1tEmuRawEt);
    m_secondaryTrees[0]->SetBranchAddress("l1tEmuIsoEt", &m_l1tEmuIsoEt);

    m_secondaryTrees[0]->SetBranchAddress("genJet_pt", &m_genJet_pt);
    m_secondaryTrees[0]->SetBranchAddress("genJet_eta", &m_genJet_eta);
    m_secondaryTrees[0]->SetBranchAddress("genJet_phi", &m_genJet_phi);
    m_secondaryTrees[0]->SetBranchAddress("genJet_emEnergy", &m_genJet_emEnergy);
    m_secondaryTrees[0]->SetBranchAddress("genJet_hadEnergy", &m_genJet_hadEnergy);
    m_secondaryTrees[0]->SetBranchAddress("genJet_invisibleEnergy", &m_genJet_invisibleEnergy);
    m_secondaryTrees[0]->SetBranchAddress("genJet_muonEnergy", &m_genJet_muonEnergy);
	
    m_secondaryTrees[0]->SetBranchAddress("genPart_id", &m_genPart_id);
    m_secondaryTrees[0]->SetBranchAddress("genPart_stat", &m_genPart_stat);
    m_secondaryTrees[0]->SetBranchAddress("genPart_parent", &m_genPart_parent);
    m_secondaryTrees[0]->SetBranchAddress("genPart_pt", &m_genPart_pt);
    m_secondaryTrees[0]->SetBranchAddress("genPart_eta", &m_genPart_eta);
    m_secondaryTrees[0]->SetBranchAddress("genPart_phi", &m_genPart_phi);
    m_secondaryTrees[0]->SetBranchAddress("genPart_E", &m_genPart_E);
    m_secondaryTrees[0]->SetBranchAddress("genPart_ch", &m_genPart_ch);
    
    m_secondaryTrees[0]->SetBranchAddress("nHCALTP", &m_nHCALTP);
    m_secondaryTrees[0]->SetBranchAddress("hcalTPieta", &m_hcalTPieta);
    m_secondaryTrees[0]->SetBranchAddress("hcalTPiphi", &m_hcalTPiphi);
    m_secondaryTrees[0]->SetBranchAddress("hcalTPCaliphi", &m_hcalTPCaliphi);
    m_secondaryTrees[0]->SetBranchAddress("hcalTPet", &m_hcalTPet);
    m_secondaryTrees[0]->SetBranchAddress("hcalTPcompEt", &m_hcalTPcompEt);
    m_secondaryTrees[0]->SetBranchAddress("hcalTPfineGrain", &m_hcalTPfineGrain);

    m_secondaryTrees[0]->SetBranchAddress("nECALTP", &m_nECALTP);
    m_secondaryTrees[0]->SetBranchAddress("ecalTPieta", &m_ecalTPieta);
    m_secondaryTrees[0]->SetBranchAddress("ecalTPiphi", &m_ecalTPiphi);
    m_secondaryTrees[0]->SetBranchAddress("ecalTPCaliphi", &m_ecalTPCaliphi);
    m_secondaryTrees[0]->SetBranchAddress("ecalTPet", &m_ecalTPet);
    m_secondaryTrees[0]->SetBranchAddress("ecalTPcompEt", &m_ecalTPcompEt);
    m_secondaryTrees[0]->SetBranchAddress("ecalTPfineGrain", &m_ecalTPfineGrain);

    m_secondaryTrees[0]->SetBranchAddress("nTower", &m_nTower);
    m_secondaryTrees[0]->SetBranchAddress("TT_ieta", &m_TT_ieta);
    m_secondaryTrees[0]->SetBranchAddress("TT_iphi", &m_TT_iphi);
    m_secondaryTrees[0]->SetBranchAddress("TT_iet", &m_TT_iet);
    m_secondaryTrees[0]->SetBranchAddress("TT_iem", &m_TT_iem);
    m_secondaryTrees[0]->SetBranchAddress("TT_ihad", &m_TT_ihad);
    m_secondaryTrees[0]->SetBranchAddress("TT_iratio", &m_TT_iratio);
    m_secondaryTrees[0]->SetBranchAddress("TT_iqual", &m_TT_iqual);
    m_secondaryTrees[0]->SetBranchAddress("TT_et", &m_TT_et);
    m_secondaryTrees[0]->SetBranchAddress("TT_eta", &m_TT_eta);
    m_secondaryTrees[0]->SetBranchAddress("TT_phi", &m_TT_phi);


    // Build event indices for secondary trees
    for(auto itr=m_secondaryTrees.begin(); itr!=m_secondaryTrees.end(); itr++)
    {
        (*itr)->BuildIndex("RunNumber", "EventNumber");
    }

}

/*****************************************************************/
void TauStage2Trees::linkOutputVariables()
/*****************************************************************/
{

  m_lumi=0;
  m_tauPt=0;
  m_tauEta=0;
  m_tauPhi=0;
  m_tauCharge=0;
  m_tauDecayMode=0;
  m_hasTriggerMuonType=0;
  m_hasTriggerTauType=0;
  m_isMatched=0;
  m_isOS=0;
  m_foundJet=0;
  // m_muonPt=0;
  // m_muonEta=0;
  // m_muonPhi=0;
  m_Nvtx=0;



  m_l1tQual=0;
  m_l1tPt=0;
  m_l1tEta=0;
  m_l1tPhi=0;
  m_l1tIso=0;
  m_l1tEmuQual=0;
  m_l1tEmuPt=0;
  m_l1tEmuEta=0;
  m_l1tEmuPhi=0;
  m_l1tEmuIso=0;
  m_l1tEmuNTT=0;
  m_l1tEmuHasEM=0;
  m_l1tEmuIsMerged=0;
  m_l1tEmuTowerIEta=0;
  m_l1tEmuTowerIPhi=0;
  m_l1tEmuRawEt=0;
  m_l1tEmuIsoEt=0;

  //Jets variables
  m_JetsNumber=0;
  m_jets_px=0;
  m_jets_py=0;
  m_jets_pz=0;
  m_jets_e=0;
  m_jets_rawPt=0;
  m_jets_area=0;
  m_jets_mT=0;
  m_jets_PUJetID=0;
  m_jets_PUJetIDupdated=0;
  m_jets_vtxPt=0;
  m_jets_vtxMass=0;
  m_jets_vtx3dL=0;
  m_jets_vtxNtrk=0;
  m_jets_vtx3deL=0;
  m_jets_leadTrackPt=0;
  m_jets_leptonPtRel=0; 
  m_jets_leptonPt=0;    
  m_jets_leptonDeltaR=0;
  m_jets_chEmEF=0;
  m_jets_chHEF=0;
  m_jets_nEmEF=0;
  m_jets_nHEF=0;
  m_jets_MUF=0;
  m_jets_neMult=0;
  m_jets_chMult=0;
  m_jets_jecUnc=0;
  //  m_jets_QGdiscr=0;
  m_jets_Flavour=0; // parton flavour
  m_jets_HadronFlavour=0; // hadron flavour
  m_jets_genjetIndex=0;
  // m_bdiscr=0;
  // m_bdiscr2=0;
  // m_bdiscr3=0;
  // m_jetID=0; //1=loose, 2=tight, 3=tightlepveto
  // m_jetrawf=0;

  m_PFMET_pt=0;
  m_PFMET_phi=0;
  m_PFMET_px=0;
  m_PFMET_py=0;
  m_PFMET_sumEt=0;

  m_CaloMET_pt=0;
  m_CaloMET_phi=0;
  m_CaloMET_px=0;
  m_CaloMET_py=0;
  m_CaloMET_sumEt=0;

	
  m_genJet_pt=0;
  m_genJet_eta=0;
  m_genJet_phi=0;
  m_genJet_emEnergy=0;
  m_genJet_hadEnergy=0;
  m_genJet_invisibleEnergy=0;
  m_genJet_muonEnergy=0;
	
  m_genPart_id=0;
  m_genPart_stat=0;
  m_genPart_parent=0;
  m_genPart_pt=0;
  m_genPart_eta=0;
  m_genPart_phi=0;
  m_genPart_E=0;
  m_genPart_ch=0;
	
  m_nHCALTP=0;
  m_hcalTPieta=0;
  m_hcalTPiphi=0;
  m_hcalTPCaliphi=0;
  m_hcalTPet=0;
  m_hcalTPcompEt=0;
  m_hcalTPfineGrain=0;

  m_nECALTP=0;
  m_ecalTPieta=0;
  m_ecalTPiphi=0;
  m_ecalTPCaliphi=0;
  m_ecalTPet=0;
  m_ecalTPcompEt=0;
  m_ecalTPfineGrain=0;

  m_nTower=0;
  m_TT_ieta=0;
  m_TT_iphi=0;
  m_TT_iet=0;
  m_TT_iem=0;
  m_TT_ihad=0;
  m_TT_iratio=0;
  m_TT_iqual=0;
  m_TT_et=0;
  m_TT_eta=0;
  m_TT_phi=0;

  // m_l1tQual->clear();
  // m_l1tPt->clear();
  // m_l1tEta->clear();
  // m_l1tPhi->clear();
  // m_l1tIso->clear();
  // m_l1tEmuQual->clear();
  // m_l1tEmuPt->clear();
  // m_l1tEmuEta->clear();
  // m_l1tEmuPhi->clear();
  // m_l1tEmuIso->clear();
  // m_l1tEmuNTT->clear();
  // m_l1tEmuHasEM->clear();
  // m_l1tEmuIsMerged->clear();
  // m_l1tEmuTowerIEta->clear();
  // m_l1tEmuTowerIPhi->clear();
  // m_l1tEmuRawEt->clear();
  // m_l1tEmuIsoEt->clear();

  // Output tree
  m_outputTree->Branch("RunNumber",  &m_run,        "RunNumber/I");
  m_outputTree->Branch("EventNumber", &m_event,     "EventNumber/l");

  m_outputTree->Branch("lumi"         , &m_lumi);
  m_outputTree->Branch("tauPt"         , &m_tauPt);
  m_outputTree->Branch("tauEta"         , &m_tauEta);
  m_outputTree->Branch("tauPhi"         , &m_tauPhi);
  m_outputTree->Branch("tauCharge"         , &m_tauCharge);
  m_outputTree->Branch("tauDecayMode"         , &m_tauDecayMode);
  m_outputTree->Branch("hasTriggerMuonType"         , &m_hasTriggerMuonType);
  m_outputTree->Branch("hasTriggerTauType"         , &m_hasTriggerTauType);
  m_outputTree->Branch("isMatched"         , &m_isMatched);
  m_outputTree->Branch("isOS"         , &m_isOS);
  m_outputTree->Branch("foundJet"         , &m_foundJet);
  // m_outputTree->Branch("muonPt"         , &m_muonPt);
  // m_outputTree->Branch("muonEta"         , &m_muonEta);
  // m_outputTree->Branch("muonPhi"         , &m_muonPhi);
  m_outputTree->Branch("Nvtx"         , &m_Nvtx);
  m_outputTree->Branch("l1tPt", &m_l1tPt);
  m_outputTree->Branch("l1tEta", &m_l1tEta);
  m_outputTree->Branch("l1tPhi", &m_l1tPhi);
  m_outputTree->Branch("l1tQual", &m_l1tQual);
  m_outputTree->Branch("l1tIso", &m_l1tIso);
  m_outputTree->Branch("l1tEmuPt",  &m_l1tEmuPt);
  m_outputTree->Branch("l1tEmuEta", &m_l1tEmuEta);
  m_outputTree->Branch("l1tEmuPhi", &m_l1tEmuPhi);
  m_outputTree->Branch("l1tEmuQual", &m_l1tEmuQual);
  m_outputTree->Branch("l1tEmuIso", &m_l1tEmuIso);
  m_outputTree->Branch("l1tEmuNTT", &m_l1tEmuNTT);
  m_outputTree->Branch("l1tEmuHasEM", &m_l1tEmuHasEM);
  m_outputTree->Branch("l1tEmuIsMerged", &m_l1tEmuIsMerged);
  m_outputTree->Branch("l1tEmuTowerIEta", &m_l1tEmuTowerIEta);
  m_outputTree->Branch("l1tEmuTowerIPhi", &m_l1tEmuTowerIPhi);
  m_outputTree->Branch("l1tEmuRawEt", &m_l1tEmuRawEt);
  m_outputTree->Branch("l1tEmuIsoEt", &m_l1tEmuIsoEt);

  //Jets variables
  m_outputTree->Branch("JetsNumber", &m_JetsNumber);
  m_outputTree->Branch("jets_px", &m_jets_px);
  m_outputTree->Branch("jets_py", &m_jets_py);
  m_outputTree->Branch("jets_pz", &m_jets_pz);
  m_outputTree->Branch("jets_e", &m_jets_e);
  m_outputTree->Branch("jets_rawPt", &m_jets_rawPt);
  m_outputTree->Branch("jets_area", &m_jets_area);
  m_outputTree->Branch("jets_mT", &m_jets_mT);
  m_outputTree->Branch("jets_PUJetID", &m_jets_PUJetID);
  m_outputTree->Branch("jets_PUJetIDupdated", &m_jets_PUJetIDupdated);
  m_outputTree->Branch("jets_vtxPt", &m_jets_vtxPt);
  m_outputTree->Branch("jets_vtxMass", &m_jets_vtxMass);
  m_outputTree->Branch("jets_vtx3dL", &m_jets_vtx3dL);
  m_outputTree->Branch("jets_vtxNtrk", &m_jets_vtxNtrk);
  m_outputTree->Branch("jets_vtx3deL", &m_jets_vtx3deL);
  m_outputTree->Branch("jets_leadTrackPt", &m_jets_leadTrackPt);
  m_outputTree->Branch("jets_leptonPtRel", &m_jets_leptonPtRel) ;
  m_outputTree->Branch("jets_leptonPt", &m_jets_leptonPt);    
  m_outputTree->Branch("jets_leptonDeltaR", &m_jets_leptonDeltaR);
  m_outputTree->Branch("jets_chEmEF", &m_jets_chEmEF);
  m_outputTree->Branch("jets_chHEF", &m_jets_chHEF);
  m_outputTree->Branch("jets_nEmEF", &m_jets_nEmEF);
  m_outputTree->Branch("jets_nHEF", &m_jets_nHEF);
  m_outputTree->Branch("jets_MUF", &m_jets_MUF);
  m_outputTree->Branch("jets_neMult", &m_jets_neMult);
  m_outputTree->Branch("jets_chMult", &m_jets_chMult);
  m_outputTree->Branch("jets_jecUnc", &m_jets_jecUnc);
  //  m_outputTree->Branch("jets_QGdiscr", &m_jets_QGdiscr);
  m_outputTree->Branch("jets_Flavour", &m_jets_Flavour);
  m_outputTree->Branch("jets_HadronFlavour", &m_jets_HadronFlavour);
  m_outputTree->Branch("jets_genjetIndex", &m_jets_genjetIndex);
  // m_outputTree->Branch("bdiscr", &m_bdiscr);
  // m_outputTree->Branch("bdiscr2", &m_bdiscr2);
  // m_outputTree->Branch("bdiscr3", &m_bdiscr3);
  // m_outputTree->Branch("jetID", &m_jetID);
  // m_outputTree->Branch("jetrawf", &m_jetrawf);

  m_outputTree->Branch("PFMET_pt", &m_PFMET_pt);
  m_outputTree->Branch("PFMET_phi", &m_PFMET_phi);
  m_outputTree->Branch("PFMET_px", &m_PFMET_px);
  m_outputTree->Branch("PFMET_py", &m_PFMET_py);
  m_outputTree->Branch("PFMET_sumEt", &m_PFMET_sumEt);

  m_outputTree->Branch("CaloMET_pt", &m_CaloMET_pt);
  m_outputTree->Branch("CaloMET_phi", &m_CaloMET_phi);
  m_outputTree->Branch("CaloMET_px", &m_CaloMET_px);
  m_outputTree->Branch("CaloMET_py", &m_CaloMET_py);
  m_outputTree->Branch("CaloMET_sumEt", &m_CaloMET_sumEt);


  m_outputTree->Branch("genJet_pt", &m_genJet_pt);
  m_outputTree->Branch("genJet_eta", &m_genJet_eta);
  m_outputTree->Branch("genJet_phi", &m_genJet_phi);
  m_outputTree->Branch("genJet_emEnergy", &m_genJet_emEnergy);
  m_outputTree->Branch("genJet_hadEnergy", &m_genJet_hadEnergy);
  m_outputTree->Branch("genJet_invisibleEnergy", &m_genJet_invisibleEnergy);
  m_outputTree->Branch("genJet_muonEnergy", &m_genJet_muonEnergy);
	
  m_outputTree->Branch("genPart_id", &m_genPart_id);
  m_outputTree->Branch("genPart_stat", &m_genPart_stat);
  m_outputTree->Branch("genPart_parent", &m_genPart_parent);
  m_outputTree->Branch("genPart_pt", &m_genPart_pt);
  m_outputTree->Branch("genPart_eta", &m_genPart_eta);
  m_outputTree->Branch("genPart_phi", &m_genPart_phi);
  m_outputTree->Branch("genPart_E", &m_genPart_E);
  m_outputTree->Branch("genPart_ch", &m_genPart_ch);
	
  m_outputTree->Branch("nHCALTP", &m_nHCALTP);
  m_outputTree->Branch("hcalTPieta", &m_hcalTPieta);
  m_outputTree->Branch("hcalTPiphi", &m_hcalTPiphi);
  m_outputTree->Branch("hcalTPCaliphi", &m_hcalTPCaliphi);
  m_outputTree->Branch("hcalTPet", &m_hcalTPet);
  m_outputTree->Branch("hcalTPcompEt", &m_hcalTPcompEt);
  m_outputTree->Branch("hcalTPfineGrain", &m_hcalTPfineGrain);

  m_outputTree->Branch("nECALTP", &m_nECALTP);
  m_outputTree->Branch("ecalTPieta", &m_ecalTPieta);
  m_outputTree->Branch("ecalTPiphi", &m_ecalTPiphi);
  m_outputTree->Branch("ecalTPCaliphi", &m_ecalTPCaliphi);
  m_outputTree->Branch("ecalTPet", &m_ecalTPet);
  m_outputTree->Branch("ecalTPcompEt", &m_ecalTPcompEt);
  m_outputTree->Branch("ecalTPfineGrain", &m_ecalTPfineGrain);

  m_outputTree->Branch("nTower", &m_nTower);
  m_outputTree->Branch("TT_ieta", &m_TT_ieta);
  m_outputTree->Branch("TT_iphi", &m_TT_iphi);
  m_outputTree->Branch("TT_iet", &m_TT_iet);
  m_outputTree->Branch("TT_iem", &m_TT_iem);
  m_outputTree->Branch("TT_ihad", &m_TT_ihad);
  m_outputTree->Branch("TT_iratio", &m_TT_iratio);
  m_outputTree->Branch("TT_iqual", &m_TT_iqual);
  m_outputTree->Branch("TT_et", &m_TT_et);
  m_outputTree->Branch("TT_eta", &m_TT_eta);
  m_outputTree->Branch("TT_phi", &m_TT_phi);

}



/*****************************************************************/
void TauStage2Trees::resetVariables()
/*****************************************************************/
{
  ITrees::resetVariables();

  m_lumi=0;
  m_tauPt->clear();
  m_tauEta->clear();
  m_tauPhi->clear();
  m_tauCharge->clear();
  m_tauDecayMode->clear();
  m_hasTriggerMuonType=0;
  m_hasTriggerTauType=0;
  m_isMatched->clear();
  m_isOS=0;
  m_foundJet=0;
  // m_muonPt=0;
  // m_muonEta=0;
  // m_muonPhi=0;
  m_Nvtx=0;

  //Jets variables
  m_JetsNumber=0;
  m_jets_px->clear();
  m_jets_py->clear();
  m_jets_pz->clear();
  m_jets_e->clear();
  m_jets_rawPt->clear();
  m_jets_area->clear();
  m_jets_mT->clear();
  m_jets_PUJetID->clear();
  m_jets_PUJetIDupdated->clear();
  m_jets_vtxPt->clear();
  m_jets_vtxMass->clear();
  m_jets_vtx3dL->clear();
  m_jets_vtxNtrk->clear();
  m_jets_vtx3deL->clear();
  m_jets_leadTrackPt->clear();
  m_jets_leptonPtRel->clear(); 
  m_jets_leptonPt->clear();    
  m_jets_leptonDeltaR->clear();
  m_jets_chEmEF->clear();
  m_jets_chHEF->clear();
  m_jets_nEmEF->clear();
  m_jets_nHEF->clear();
  m_jets_MUF->clear();
  m_jets_neMult->clear();
  m_jets_chMult->clear();
  m_jets_jecUnc->clear();
  //  m_jets_QGdiscr->clear();
  m_jets_Flavour->clear(); // parton flavour
  m_jets_HadronFlavour->clear(); // hadron flavour
  m_jets_genjetIndex->clear();
  // m_bdiscr->clear();
  // m_bdiscr2->clear();
  // m_bdiscr3->clear();
  // m_jetID->clear(); //1=loose, 2=tight, 3=tightlepveto
  // m_jetrawf->clear();

  m_PFMET_pt=0;
  m_PFMET_phi=0;
  m_PFMET_px=0;
  m_PFMET_py=0;
  m_PFMET_sumEt=0;

  m_CaloMET_pt=0;
  m_CaloMET_phi=0;
  m_CaloMET_px=0;
  m_CaloMET_py=0;
  m_CaloMET_sumEt=0;

  m_l1tQual->clear();
  m_l1tPt->clear();
  m_l1tEta->clear();
  m_l1tPhi->clear();
  m_l1tIso->clear();
  m_l1tEmuQual->clear();
  m_l1tEmuPt->clear();
  m_l1tEmuEta->clear();
  m_l1tEmuPhi->clear();
  m_l1tEmuIso->clear();
  m_l1tEmuNTT->clear();
  m_l1tEmuHasEM->clear();
  m_l1tEmuIsMerged->clear();
  m_l1tEmuTowerIEta->clear();
  m_l1tEmuTowerIPhi->clear();
  m_l1tEmuRawEt->clear();
  m_l1tEmuIsoEt->clear();

  m_genJet_pt->clear();
  m_genJet_eta->clear();
  m_genJet_phi->clear();
  m_genJet_emEnergy->clear();
  m_genJet_hadEnergy->clear();
  m_genJet_invisibleEnergy->clear();
  m_genJet_muonEnergy->clear();
	
  m_genPart_id->clear();
  m_genPart_stat->clear();
  m_genPart_parent->clear();
  m_genPart_pt->clear();
  m_genPart_eta->clear();
  m_genPart_phi->clear();
  m_genPart_E->clear();
  m_genPart_ch->clear();
	
  m_nHCALTP=0;
  m_hcalTPieta->clear();
  m_hcalTPiphi->clear();
  m_hcalTPCaliphi->clear();
  m_hcalTPet->clear();
  m_hcalTPcompEt->clear();
  m_hcalTPfineGrain->clear();

  m_nECALTP=0;
  m_ecalTPieta->clear();
  m_ecalTPiphi->clear();
  m_ecalTPCaliphi->clear();
  m_ecalTPet->clear();
  m_ecalTPcompEt->clear();
  m_ecalTPfineGrain->clear();

  m_nTower=0;
  m_TT_ieta->clear();
  m_TT_iphi->clear();
  m_TT_iet->clear();
  m_TT_iem->clear();
  m_TT_ihad->clear();
  m_TT_iratio->clear();
  m_TT_iqual->clear();
  m_TT_et->clear();
  m_TT_eta->clear();
  m_TT_phi->clear();


}
