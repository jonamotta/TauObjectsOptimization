/**
 *  @file  TauStage2Trees.h
 *  @brief  
 *
 *
 *  @author  Jean-Baptiste Sauvan <sauvan@llr.in2p3.fr>
 *
 *  @date    07/16/2014
 *
 *  @internal
 *     Created :  07/16/2014
 * Last update :  15/06/2022 20:51:05 PM
 *          by :  O Davignon
 *
 * =====================================================================================
 */


#ifndef TAUSTAGE2TREES_H
#define TAUSTAGE2TREES_H

#include "ITrees.h"

class TauStage2Trees:public ITrees
{
    public:
        TauStage2Trees():ITrees(){};
        ~TauStage2Trees(){};

        void linkMainVariables();
        void linkSecondaryVariables();
        void linkOutputVariables();
        void resetVariables();

    protected:
        // offline and truth variables
        int m_lumi;
	
	//Taus variables
	std::vector<float>* m_tauPt;
        std::vector<float>* m_tauEta;
        std::vector<float>* m_tauPhi;
	std::vector<int>*   m_tauCharge;
	std::vector<int>*   m_tauDecayMode;

        bool m_hasTriggerMuonType;
        bool m_hasTriggerTauType;
	std::vector<bool>* m_isMatched;
        bool m_isOS;
        int m_foundJet;
        /* float m_muonPt; */
        /* float m_muonEta; */
        /* float m_muonPhi; */
        int m_Nvtx;

	//Jets variables
	int m_JetsNumber;
	std::vector<float>* m_jets_px;
	std::vector<float>* m_jets_py;
	std::vector<float>* m_jets_pz;
	std::vector<float>* m_jets_e;
	std::vector<float>* m_jets_rawPt;
	std::vector<float>* m_jets_area;
	std::vector<float>* m_jets_mT;
	std::vector<float>* m_jets_PUJetID;
	std::vector<float>* m_jets_PUJetIDupdated;
	std::vector<float>* m_jets_vtxPt;
	std::vector<float>* m_jets_vtxMass;
	std::vector<float>* m_jets_vtx3dL;
	std::vector<float>* m_jets_vtxNtrk;
	std::vector<float>* m_jets_vtx3deL;
	std::vector<float>* m_jets_leadTrackPt;
	std::vector<float>* m_jets_leptonPtRel; 
	std::vector<float>* m_jets_leptonPt;    
	std::vector<float>* m_jets_leptonDeltaR;
	std::vector<float>* m_jets_chEmEF;
	std::vector<float>* m_jets_chHEF;
	std::vector<float>* m_jets_nEmEF;
	std::vector<float>* m_jets_nHEF;
	std::vector<float>* m_jets_MUF;
	std::vector<int>*   m_jets_neMult;
	std::vector<int>*   m_jets_chMult;
	std::vector<float>* m_jets_jecUnc;
	//std::vector<float>* m_jets_QGdiscr;
	std::vector<int>* m_jets_Flavour; // parton flavour
	std::vector<int>* m_jets_HadronFlavour; // hadron flavour
	std::vector<int>* m_jets_genjetIndex;
	/* std::vector<float>* m_bdiscr; */
	/* std::vector<float>* m_bdiscr2; */
	/* std::vector<float>* m_bdiscr3; */
	/* std::vector<int>* m_jetID; //1=loose, 2=tight, 3=tightlepveto */
	/* std::vector<float>* m_jetrawf; */

	double m_PFMET_pt;
	double m_PFMET_phi;
	double m_PFMET_px;
	double m_PFMET_py;
	double m_PFMET_sumEt;

	double m_CaloMET_pt;
	double m_CaloMET_phi;
	double m_CaloMET_px;
	double m_CaloMET_py;
	double m_CaloMET_sumEt;
	
        std::vector<int>* m_l1tQual;
        std::vector<float>* m_l1tPt;
        std::vector<float>* m_l1tEta;
        std::vector<float>* m_l1tPhi;
        std::vector<int>* m_l1tIso;
        std::vector<int>* m_l1tEmuQual;
        std::vector<float>* m_l1tEmuPt;
        std::vector<float>* m_l1tEmuEta;
        std::vector<float>* m_l1tEmuPhi;
        std::vector<int>* m_l1tEmuIso;
        std::vector<int>* m_l1tEmuNTT;
        std::vector<int>* m_l1tEmuHasEM;
        std::vector<int>* m_l1tEmuIsMerged;
        std::vector<int>* m_l1tEmuTowerIEta;
        std::vector<int>* m_l1tEmuTowerIPhi;
        std::vector<int>* m_l1tEmuRawEt;
        std::vector<int>* m_l1tEmuIsoEt;
	
	std::vector<float>* m_genJet_pt;
	std::vector<float>* m_genJet_eta;
	std::vector<float>* m_genJet_phi;
	std::vector<float>* m_genJet_emEnergy;
	std::vector<float>* m_genJet_hadEnergy;
	std::vector<float>* m_genJet_invisibleEnergy;
	std::vector<float>* m_genJet_muonEnergy;
	
	std::vector<int>* m_genPart_id;
	std::vector<int>* m_genPart_stat;
	std::vector<int>* m_genPart_parent;
	std::vector<float>* m_genPart_pt;
	std::vector<float>* m_genPart_eta;
	std::vector<float>* m_genPart_phi;
	std::vector<float>* m_genPart_E;
	std::vector<int>* m_genPart_ch;
	
	short m_nHCALTP;
	std::vector<short>* m_hcalTPieta;
	std::vector<short>* m_hcalTPiphi;
	std::vector<short>* m_hcalTPCaliphi;
	std::vector<float>* m_hcalTPet;
	std::vector<short>* m_hcalTPcompEt;
	std::vector<short>* m_hcalTPfineGrain;

	short m_nECALTP;
	std::vector<short>* m_ecalTPieta;
	std::vector<short>* m_ecalTPiphi;
	std::vector<short>* m_ecalTPCaliphi;
	std::vector<float>* m_ecalTPet;
	std::vector<short>* m_ecalTPcompEt;
	std::vector<short>* m_ecalTPfineGrain;

	short m_nTower;
	std::vector<short>* m_TT_ieta;
	std::vector<short>* m_TT_iphi;
	std::vector<short>* m_TT_iet;
	std::vector<short>* m_TT_iem;
	std::vector<short>* m_TT_ihad;
	std::vector<short>* m_TT_iratio;
	std::vector<short>* m_TT_iqual;
	std::vector<float>* m_TT_et;
	std::vector<float>* m_TT_eta;
	std::vector<float>* m_TT_phi;

};


#endif
