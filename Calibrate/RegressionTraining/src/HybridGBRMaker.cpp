/**
 *  @file  HybridGBRMaker.cpp
 *  @brief  
 *
 *
 *  @author  Jean-Baptiste Sauvan <sauvan@llr.in2p3.fr>
 *
 *  @date    11/28/2012
 *
 *  @internal
 *     Created :  11/28/2012
 * Last update :  11/28/2012 10:15:12 PM
 *          by :  JB Sauvan
 *
 * =====================================================================================
 */



#include "HybridGBRMaker.h"
#include "Utilities.h"
#include "GBRTrainer.h"
#include "GBRForest.h"
#include "GBRApply.h"

#include <TFile.h>
#include <TChain.h>
#include <TCut.h>
#include <TKey.h>
#include "TString.h"

#include "RooArgList.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooConstVar.h"
#include "RooWorkspace.h"
#include "HiggsAnalysis/GBRLikelihood/interface/RooHybridBDTAutoPdf.h"
#include "HiggsAnalysis/GBRLikelihood/interface/RooDoubleCBFast.h"
#include "HiggsAnalysis/GBRLikelihood/interface/HybridGBRForestFlex.h"
#include "CondFormats/EgammaObjects/interface/GBRForestD.h"

#include <iostream>
#include <sstream>
#include <time.h>


using namespace std;
using namespace RooFit;



/*****************************************************************/
HybridGBRMaker::HybridGBRMaker():
    m_name("regression"),
    m_fileOutName(""),
    m_target(""),
    m_targetComb(""),
    m_weight(""),
    m_doCombine(true),
    //m_trainerEBVar(NULL),
    //m_trainerEE(NULL),
    //m_trainerEEVar(NULL),
    m_trainerComb(NULL),
    m_forestEBmean(NULL),
    m_forestEEmean(NULL),
    m_forestEBwidth(NULL),
    m_forestEEwidth(NULL),
    m_ntrees(10000)
/*****************************************************************/
{
}

/*****************************************************************/
HybridGBRMaker::~HybridGBRMaker()
/*****************************************************************/
{

}


/*****************************************************************/
void HybridGBRMaker::close()
/*****************************************************************/
{
    vector<TFile*>::iterator it = m_filesIn.begin();
    vector<TFile*>::iterator itE = m_filesIn.end();
    for(;it!=itE;++it)
    {
        if(*it)
        {
            (*it)->Close();
            delete *it;
         }
    }
    m_filesIn.clear();
    //for(unsigned int i=0;i<m_trees.size();i++)
    //{
    //    //TTree* tree = m_trees[i];
    //    //if(tree) 
    //    //{
    //    //    tree->Delete();
    //    //    tree = NULL;
    //    //}
    //}
    //m_trees.clear();
    //if(m_trainerEB) 
    //{
        //delete m_trainerEB;
        //m_trainerEB = NULL;
    //}
    //if(m_trainerEE) 
    //{
        //delete m_trainerEE;
        //m_trainerEE = NULL;
    //}
    if(m_trainerComb) 
    {
        delete m_trainerComb;
        m_trainerComb = NULL;
    }

}


/*****************************************************************/
bool HybridGBRMaker::init(const string& name,
                           const string& fileNames,
                           const string& treeName,
                           const string& outputDirectory,
                           bool doCombine)
/*****************************************************************/
{
    cout<<"INFO: init semi-parametric GBR regression "<<name<<"\n";
    m_name = name;
    m_doCombine = doCombine;

    // create GBR trainer
    m_trainerComb = new GBRTrainer();

    // fill GBRtrainer with TTrees
    m_tree = new TChain(treeName.c_str());
    vector<string> vectorFileNames;
    tokenize(fileNames, vectorFileNames, ":");
    vector<string>::iterator it = vectorFileNames.begin();
    vector<string>::iterator itE = vectorFileNames.end();
    for(;it!=itE;++it)
    {
        TFile* fileIn = TFile::Open(it->c_str());
        if(!fileIn || !fileIn->IsOpen())
        {
            cout<<"FATAL: HybridGBRMaker::init(): Cannot open input file "<<*it<<"\n";
            return false;
        }
        //fileIn->Close();
        m_filesIn.push_back(fileIn);
        TTree* tree = (TTree*)fileIn->Get(treeName.c_str());
        if(!tree)
        {
            cout<<"FATAL: HybridGBRMaker::init(): Cannot find regression tree "<<treeName<<" in "<<*it<<"\n";
            return false;
        }
        m_trainerComb->AddTree(tree);
        m_tree->Add(it->c_str());
        m_trees.push_back(tree);
    }
    
    // open output file 
    stringstream outFileName;
    outFileName << outputDirectory << "/" << name << "_results.root";
    m_fileOutName = outFileName.str();
    TFile* fileOut = TFile::Open(m_fileOutName.c_str(), "RECREATE");
    if(!fileOut || !fileOut->IsOpen())
    {
        cout<<"FATAL: HybridGBRMaker::init(): Cannot open output file "<<outFileName.str()<<"\n";
        return false;
    }
    fileOut->Close();


    return true;
}



/*****************************************************************/
void HybridGBRMaker::addVariableEB(const string& name)
/*****************************************************************/
{
    m_variablesEB.push_back(name);
}

/*****************************************************************/
void HybridGBRMaker::addVariableEE(const string& name)
/*****************************************************************/
{
    m_variablesEE.push_back(name);
}

/*****************************************************************/
void HybridGBRMaker::addVariableComb(const string& name)
/*****************************************************************/
{
    if(!m_trainerComb)
    {
        cout<<"ERROR: HybridGBRMaker::addVariable(): Cannot add variable: trainer doesn't exist\n";
        return;
    }
    m_variablesComb.push_back(name);
    m_trainerComb->AddInputVar(name);
}


/*****************************************************************/
void HybridGBRMaker::addTarget(const string& target, const string& targetComb)
/*****************************************************************/
{
    m_target = target;
    if(!m_trainerComb)
    {
        cout<<"ERROR: HybridGBRMaker::addVariable(): Cannot add variable: trainer doesn't exist\n";
        return;
    }
    m_targetComb = targetComb;
    m_trainerComb->SetTargetVar(m_targetComb);
}


/*****************************************************************/
void HybridGBRMaker::prepareTraining(const string& cutBase, const string& cutComb, const string& cutEB, const string& cutEE, const string& options)
/*****************************************************************/
{
    cout<<"HybridGBRMaker::prepareTraining()\n";
}

/*****************************************************************/
void HybridGBRMaker::run(const string& cutBase, const string& cutComb, const string& cutEB, const string& cutEE, const string& options)
/*****************************************************************/
{
    cout<<"INFO: Prepare and run training for "<<m_name<<"\n";
    runEB(cutBase, cutEB, options);
    runEE(cutBase, cutEE, options);
    if(m_doCombine) runComb(cutComb, options);
}


/*****************************************************************/
void HybridGBRMaker::runEB(const string& cutBase, const string& cutEB, const string& options)
/*****************************************************************/
{

    //create RooRealVars for each input variable
    RooArgList varsEB;
    for (unsigned int ivar=0; ivar<m_variablesEB.size(); ++ivar)
    {
        RooRealVar* var = new RooRealVar(TString::Format("var_%i",ivar), m_variablesEB.at(ivar).c_str(), 0.);
        varsEB.addOwned(*var);
    }

    //make list of input variable RooRealVars
    RooArgList condvarsEB(varsEB);

    //create RooRealVar for target
    RooRealVar* targetvar  = new RooRealVar("targetvar", m_target.c_str(), 1.);
    //RooRealVar targetvar ("targetvar", m_target.c_str(), 1.);

    //add target to full list
    varsEB.addOwned(*targetvar);

    // retrieve event weight
    // loop over options
    vector<string> optionTokens;
    tokenize(options, optionTokens, ":");
    for(const auto& token : optionTokens)
    {
        vector<string> tagAndValue;
        tokenize(token, tagAndValue, "=");
        string tag = tagAndValue[0];
        string value = tagAndValue[1];
        if(tag=="EventWeight")
        {
            m_weight = value;
            cout<<"INFO: EventWeight = "<<value<<"\n";
        }
    }

    //RooRealVar for event weight 
    TCut weight(m_weight.c_str());
    RooRealVar weightvarEB("weightvar","",1.);

    // Define event cuts
    m_cutEB = cutEB;
    TCut cutCentral(cutBase.c_str());
    //TCut cutCombination(cutComb.c_str());
    TCut cutBarrel(cutEB.c_str());
    cout<<"INFO: Cuts for EB training = '"<<string(cutCentral && cutBarrel)<<"'\n";
    //cout<<"INFO: Cuts for combination training    = '"<<string(cutCombination)<<"'\n";
    // weight * cuts
    weightvarEB.SetTitle( (cutCentral && cutBarrel)*weight );



    //create RooDataSet from TChain
    RooDataSet *hdataEB = RooTreeConvert::CreateDataSet("hdataEB", m_tree, varsEB, weightvarEB);   

    //RooRealVars corresponding to regressed parameters (sigma, mean, left tail parameter, right tail parameter)
    RooRealVar sigwidthtvarEB("sigwidthtvarEB","",0.01);
    sigwidthtvarEB.setConstant(false);

    RooRealVar sigmeantvarEB("sigmeantvarEB","",1.);
    sigmeantvarEB.setConstant(false); 

    RooRealVar signvarEB("signvarEB","",3.);
    signvarEB.setConstant(false);       

    RooRealVar sign2varEB("sign2varEB","",3.);
    sign2varEB.setConstant(false);     

    //define non-parametric functions for each regressed parameter
    RooGBRFunctionFlex *sigwidthtfuncEB = new RooGBRFunctionFlex("sigwidthtfuncEB","");
    RooGBRFunctionFlex *sigmeantfuncEB = new RooGBRFunctionFlex("sigmeantfuncEB","");
    RooGBRFunctionFlex *signfuncEB = new RooGBRFunctionFlex("signfuncEB","");
    RooGBRFunctionFlex *sign2funcEB = new RooGBRFunctionFlex("sign2funcEB","");
    //RooGBRFunctionFlex sigwidthtfuncEB("sigwidthtfuncEB","");
    //RooGBRFunctionFlex sigmeantfuncEB("sigmeantfuncEB","");
    //RooGBRFunctionFlex signfuncEB("signfuncEB","");
    //RooGBRFunctionFlex sign2funcEB("sign2funcEB","");

    //define mapping of input variables to non-parametric functions (in this case trivial since all 4 functions depend on the same inputs, but this is not a requirement)
    RooGBRTargetFlex *sigwidthtEB = new RooGBRTargetFlex("sigwidthtEB","",*sigwidthtfuncEB,sigwidthtvarEB,condvarsEB);  
    RooGBRTargetFlex *sigmeantEB = new RooGBRTargetFlex("sigmeantEB","",*sigmeantfuncEB,sigmeantvarEB,condvarsEB);  
    RooGBRTargetFlex *signtEB = new RooGBRTargetFlex("signtEB","",*signfuncEB,signvarEB,condvarsEB);  
    RooGBRTargetFlex *sign2tEB = new RooGBRTargetFlex("sign2tEB","",*sign2funcEB,sign2varEB,condvarsEB);  
    //RooGBRTargetFlex sigwidthtEB("sigwidthtEB","",sigwidthtfuncEB,sigwidthtvarEB,condvarsEB);  
    //RooGBRTargetFlex sigmeantEB("sigmeantEB","",sigmeantfuncEB,sigmeantvarEB,condvarsEB);  
    //RooGBRTargetFlex signtEB("signtEB","",signfuncEB,signvarEB,condvarsEB);  
    //RooGBRTargetFlex sign2tEB("sign2tEB","",sign2funcEB,sign2varEB,condvarsEB);

    //define list of mapped functions to regress
    RooArgList tgtsEB;
    tgtsEB.add(*sigwidthtEB);
    tgtsEB.add(*sigmeantEB);
    tgtsEB.add(*signtEB);
    tgtsEB.add(*sign2tEB);  

    //define transformations corresponding to parameter bounds for non-parametric outputs  
    RooRealConstraint sigwidthlimEB("sigwidthlimEB","",*sigwidthtEB,0.0002,0.5);
    RooRealConstraint sigmeanlimEB("sigmeanlimEB","",*sigmeantEB,0.2,2.0);
    RooRealConstraint signlimEB("signlimEB","",*signtEB,1.01,5000.); 
    RooRealConstraint sign2limEB("sign2limEB","",*sign2tEB,1.01,5000.); 

    //define pdf, which depends on transformed outputs (and is intended to be treated as a conditional pdf over the
    //regression inputs in this case)
    //The actual pdf below is a double crystal ball, with crossover points alpha_1 and alpha_2 set constant, but all other
    //parameters regressed
    RooDoubleCBFast sigpdfEB("sigpdfEB","",*targetvar,sigmeanlimEB,sigwidthlimEB,RooConst(2.),signlimEB,RooConst(1.),sign2limEB);

    //dummy variable
    RooConstVar etermconst("etermconst","",0.);  

    //dummy variable
    RooRealVar r("r","",1.);
    r.setConstant();

    //define list of pdfs
    std::vector<RooAbsReal*> vpdfEB;
    vpdfEB.push_back(&sigpdfEB);  

    //define list of training datasets
    std::vector<RooAbsData*> vdataEB;
    vdataEB.push_back(hdataEB);

    RooHybridBDTAutoPdf trainerEB("bdtpdfdiffEB","",tgtsEB,etermconst,r,vdataEB,vpdfEB);


    // set cut for training events
    //m_trainerComb->SetTrainingCut(string(cutCombination)); 
    // loop over options
    for(const auto& token : optionTokens)
    {
        vector<string> tagAndValue;
        tokenize(token, tagAndValue, "=");
        if(tagAndValue.size()!=2)
        {
            cout<<"ERROR: HybridGBRMaker::prepareTraining(): option "<<token<<" cannot be processed. Should be of the form tag=value.\n";
            continue;
        }
        string tag = tagAndValue[0];
        string value = tagAndValue[1];
        if(tag=="MinEvents")
        {
            double minEvents = 0;
            fromString(minEvents, value);
            std::vector<double> vMinEvents;
            vMinEvents.push_back(minEvents);
            trainerEB.SetMinWeights(vMinEvents);
            //m_trainerComb->SetMinEvents(minEvents);
            cout<<"INFO: MinEvents = "<<minEvents<<"\n";
        }
        else if(tag=="Shrinkage")
        {
            float shrink = 0.;
            fromString(shrink, value);
            trainerEB.SetShrinkage(shrink);
            //m_trainerComb->SetShrinkage(shrink);
            cout<<"INFO: Shrinkage = "<<shrink<<"\n";
        }
        else if(tag=="MinSignificance")
        {
            float sig = 0.;
            fromString(sig, value);
            trainerEB.SetMinCutSignificance(sig);
            //m_trainerComb->SetMinCutSignificance(sig);
            cout<<"INFO: MinSignificance = "<<sig<<"\n";
        }
        else if(tag=="TransitionQuantile")
        {
            float trans = 0.;
            fromString(trans, value);
            trainerEB.SetTransitionQuantile(trans);
            //m_trainerComb->SetTransitionQuantile(trans);
            cout<<"INFO: TransitionQuantile = "<<trans<<"\n";
        }
        else if(tag=="RandomSeed")
        {
        }
        else if(tag=="NTrees")
        {
            int ntrees= 0;
            fromString(ntrees, value);
            m_ntrees = ntrees;
            cout<<"INFO: NTrees = "<<ntrees<<"\n";
        }
        else if(tag=="EventWeight")
        {
            // already filled, but do it again
            m_weight = value;
        }
        else
        {
            cout<<"ERROR: HybridGBRMaker::prepareTraining(): Unknown option "<<tag<<"\n";
            cout<<"ERROR: Possibilities are: MinEvents, Shrinkage, MinSignificance, TransitionQuantile, NTrees, EventWeight\n";
        }
    }


    // run
    cout<<"INFO: train BDT for EB central value estimation\n";
    trainerEB.TrainForest(m_ntrees);
    // save workspace
    RooWorkspace weregEB("wereg_eb");
    weregEB.import(sigpdfEB);

    // Write input variable names
    TFile* fileOut = TFile::Open(m_fileOutName.c_str(), "UPDATE");
    //if(m_doCombine)
    //m_fileOut->WriteObject(&m_variablesComb, "varlistComb");
    m_forestEBmean = new GBRForestD(*sigmeantEB->Forest());
    m_forestEBwidth = new GBRForestD(*sigwidthtEB->Forest());
    fileOut->WriteObject(m_forestEBmean,"EBCorrection");
    fileOut->WriteObject(m_forestEBwidth,"EBUncertainty");

    fileOut->WriteObject(&m_variablesEB, "varlistEB");
    fileOut->Close();

    // write workspace
    weregEB.writeToFile(m_fileOutName.c_str(), false);    


    //if(m_doCombine)
    //{
        //cout<<"INFO: train BDT for combination\n";
        //forestComb = m_trainerComb->TrainForest(m_ntrees);
        //delete m_trainerComb;
        //m_trainerComb = NULL;
    //}

    // write GBRForest in output file
    //if(forestEB)
    //m_fileOut->WriteObject(forestEB, "EBCorrection");
    //else
    //cout<<"WARNING: HybridGBRMaker::run(): NULL EB forest\n";
    //if(forestEE)
    //m_fileOut->WriteObject(forestEE, "EECorrection");
    //else
    //cout<<"WARNING: HybridGBRMaker::run(): NULL EE forest\n";
    //if(m_doCombine)
    //{
    //if(forestComb)
    //m_fileOut->WriteObject(forestComb, "CombinationWeight");
    //else
    //cout<<"WARNING: HybridGBRMaker::run(): NULL comb forest\n";
    //}

    // save list of input variables


    //hdataEB->Delete();

}

/*****************************************************************/
void HybridGBRMaker::runEE(const string& cutBase, const string& cutEE, const string& options)
/*****************************************************************/
{
    //create RooRealVars for each input variable
    RooArgList varsEE;
    for (unsigned int ivar=0; ivar<m_variablesEE.size(); ++ivar)
    {
        RooRealVar* var = new RooRealVar(TString::Format("var_%i",ivar), m_variablesEE.at(ivar).c_str(), 0.);
        varsEE.addOwned(*var);
    }

    //make list of input variable RooRealVars
    RooArgList condvarsEE(varsEE);

    //create RooRealVar for target
    RooRealVar* targetvar  = new RooRealVar("targetvar", m_target.c_str(), 1.);
    //RooRealVar targetvar ("targetvar", m_target.c_str(), 1.);

    //add target to full list
    varsEE.addOwned(*targetvar);

    // retrieve event weight
    // loop over options
    vector<string> optionTokens;
    tokenize(options, optionTokens, ":");
    for(const auto& token : optionTokens)
    {
        vector<string> tagAndValue;
        tokenize(token, tagAndValue, "=");
        string tag = tagAndValue[0];
        string value = tagAndValue[1];
        if(tag=="EventWeight")
        {
            m_weight = value;
            cout<<"INFO: EventWeight = "<<value<<"\n";
        }
    }

    //RooRealVar for event weight 
    TCut weight(m_weight.c_str());
    RooRealVar weightvarEE("weightvar","",1.);

    // Define event cuts
    m_cutEE = cutEE;
    TCut cutCentral(cutBase.c_str());
    TCut cutEndcap(cutEE.c_str());
    cout<<"INFO: Cuts for EE training = '"<<string(cutCentral && cutEndcap)<<"'\n";
    // weight * cuts
    weightvarEE.SetTitle( (cutCentral && cutEndcap)*weight );


    //create RooDataSet from TChain
    RooDataSet *hdataEE = RooTreeConvert::CreateDataSet("hdataEE", m_tree, varsEE, weightvarEE);   

    //RooRealVars corresponding to regressed parameters (sigma, mean, left tail parameter, right tail parameter)
    RooRealVar sigwidthtvarEE("sigwidthtvarEE","",0.01);
    sigwidthtvarEE.setConstant(false);

    RooRealVar sigmeantvarEE("sigmeantvarEE","",1.);
    sigmeantvarEE.setConstant(false); 

    RooRealVar signvarEE("signvarEE","",3.);
    signvarEE.setConstant(false);       

    RooRealVar sign2varEE("sign2varEE","",3.);
    sign2varEE.setConstant(false);     

    //define non-parametric functions for each regressed parameter
    RooGBRFunctionFlex *sigwidthtfuncEE = new RooGBRFunctionFlex("sigwidthtfuncEE","");
    RooGBRFunctionFlex *sigmeantfuncEE = new RooGBRFunctionFlex("sigmeantfuncEE","");
    RooGBRFunctionFlex *signfuncEE = new RooGBRFunctionFlex("signfuncEE","");
    RooGBRFunctionFlex *sign2funcEE = new RooGBRFunctionFlex("sign2funcEE","");
    //RooGBRFunctionFlex sigwidthtfuncEB("sigwidthtfuncEB","");
    //RooGBRFunctionFlex sigmeantfuncEB("sigmeantfuncEB","");
    //RooGBRFunctionFlex signfuncEB("signfuncEB","");
    //RooGBRFunctionFlex sign2funcEB("sign2funcEB","");

    //define mapping of input variables to non-parametric functions (in this case trivial since all 4 functions depend on the same inputs, but this is not a requirement)
    RooGBRTargetFlex *sigwidthtEE = new RooGBRTargetFlex("sigwidthtEE","",*sigwidthtfuncEE,sigwidthtvarEE,condvarsEE);  
    RooGBRTargetFlex *sigmeantEE = new RooGBRTargetFlex("sigmeantEE","",*sigmeantfuncEE,sigmeantvarEE,condvarsEE);  
    RooGBRTargetFlex *signtEE = new RooGBRTargetFlex("signtEE","",*signfuncEE,signvarEE,condvarsEE);  
    RooGBRTargetFlex *sign2tEE = new RooGBRTargetFlex("sign2tEE","",*sign2funcEE,sign2varEE,condvarsEE);  
    //RooGBRTargetFlex sigwidthtEB("sigwidthtEB","",sigwidthtfuncEB,sigwidthtvarEB,condvarsEB);  
    //RooGBRTargetFlex sigmeantEB("sigmeantEB","",sigmeantfuncEB,sigmeantvarEB,condvarsEB);  
    //RooGBRTargetFlex signtEB("signtEB","",signfuncEB,signvarEB,condvarsEB);  
    //RooGBRTargetFlex sign2tEB("sign2tEB","",sign2funcEB,sign2varEB,condvarsEB);

    //define list of mapped functions to regress
    RooArgList tgtsEE;
    tgtsEE.add(*sigwidthtEE);
    tgtsEE.add(*sigmeantEE);
    tgtsEE.add(*signtEE);
    tgtsEE.add(*sign2tEE);  

    //define transformations corresponding to parameter bounds for non-parametric outputs  
    RooRealConstraint sigwidthlimEE("sigwidthlimEE","",*sigwidthtEE,0.0002,0.5);
    RooRealConstraint sigmeanlimEE("sigmeanlimEE","",*sigmeantEE,0.2,2.0);
    RooRealConstraint signlimEE("signlimEE","",*signtEE,1.01,5000.); 
    RooRealConstraint sign2limEE("sign2limEE","",*sign2tEE,1.01,5000.); 

    //define pdf, which depends on transformed outputs (and is intended to be treated as a conditional pdf over the
    //regression inputs in this case)
    //The actual pdf below is a double crystal ball, with crossover points alpha_1 and alpha_2 set constant, but all other
    //parameters regressed
    RooDoubleCBFast sigpdfEE("sigpdfEE","",*targetvar,sigmeanlimEE,sigwidthlimEE,RooConst(2.),signlimEE,RooConst(1.),sign2limEE);

    //dummy variable
    RooConstVar etermconst("etermconst","",0.);  

    //dummy variable
    RooRealVar r("r","",1.);
    r.setConstant();

    //define list of pdfs
    std::vector<RooAbsReal*> vpdfEE;
    vpdfEE.push_back(&sigpdfEE);  

    //define list of training datasets
    std::vector<RooAbsData*> vdataEE;
    vdataEE.push_back(hdataEE);

    RooHybridBDTAutoPdf trainerEE("bdtpdfdiffEE","",tgtsEE,etermconst,r,vdataEE,vpdfEE);


    // set cut for training events
    //m_trainerComb->SetTrainingCut(string(cutCombination)); 
    // loop over options
    for(const auto& token : optionTokens)
    {
        vector<string> tagAndValue;
        tokenize(token, tagAndValue, "=");
        if(tagAndValue.size()!=2)
        {
            cout<<"ERROR: HybridGBRMaker::prepareTraining(): option "<<token<<" cannot be processed. Should be of the form tag=value.\n";
            continue;
        }
        string tag = tagAndValue[0];
        string value = tagAndValue[1];
        if(tag=="MinEvents")
        {
            double minEvents = 0;
            fromString(minEvents, value);
            std::vector<double> vMinEvents;
            vMinEvents.push_back(minEvents);
            trainerEE.SetMinWeights(vMinEvents);
            cout<<"INFO: MinEvents = "<<minEvents<<"\n";
        }
        else if(tag=="Shrinkage")
        {
            float shrink = 0.;
            fromString(shrink, value);
            trainerEE.SetShrinkage(shrink);
            cout<<"INFO: Shrinkage = "<<shrink<<"\n";
        }
        else if(tag=="MinSignificance")
        {
            float sig = 0.;
            fromString(sig, value);
            trainerEE.SetMinCutSignificance(sig);
            cout<<"INFO: MinSignificance = "<<sig<<"\n";
        }
        else if(tag=="TransitionQuantile")
        {
            float trans = 0.;
            fromString(trans, value);
            trainerEE.SetTransitionQuantile(trans);
            cout<<"INFO: TransitionQuantile = "<<trans<<"\n";
        }
        else if(tag=="NTrees")
        {
            int ntrees= 0;
            fromString(ntrees, value);
            m_ntrees = ntrees;
            cout<<"INFO: NTrees = "<<ntrees<<"\n";
        }
        else if(tag=="RandomSeed")
        {
        }
        else if(tag=="EventWeight")
        {
            // already filled, but do it again
            m_weight = value;
        }
        else
        {
            cout<<"ERROR: HybridGBRMaker::prepareTraining(): Unknown option "<<tag<<"\n";
            cout<<"ERROR: Possibilities are: MinEvents, Shrinkage, MinSignificance, TransitionQuantile, NTrees, EventWeight\n";
        }
    }


    // run
    cout<<"INFO: train BDT for EE central value estimation\n";
    trainerEE.TrainForest(m_ntrees);
    // save workspace
    RooWorkspace weregEE("wereg_ee");
    weregEE.import(sigpdfEE);


    TFile* fileOut = TFile::Open(m_fileOutName.c_str(), "UPDATE");
    m_forestEEmean = new GBRForestD(*sigmeantEE->Forest());
    m_forestEEwidth = new GBRForestD(*sigwidthtEE->Forest());
    fileOut->WriteObject(m_forestEEmean,"EECorrection");
    fileOut->WriteObject(m_forestEEwidth,"EEUncertainty");
    fileOut->WriteObject(&m_variablesEE, "varlistEE");
    fileOut->Close();

    weregEE.writeToFile(m_fileOutName.c_str(), false);    

}

/*****************************************************************/
void HybridGBRMaker::runComb(const string& cutComb, const string& options)
/*****************************************************************/
{
    TCut cutCombination(cutComb.c_str());
    cout<<"INFO: Cuts for combination training    = '"<<string(cutCombination)<<"'\n";
    // set cut for training events
    m_trainerComb->SetTrainingCut(string(cutCombination)); 
    // loop over options
    vector<string> optionTokens;
    tokenize(options, optionTokens, ":");
    for(const auto& token : optionTokens)
    {
        vector<string> tagAndValue;
        tokenize(token, tagAndValue, "=");
        if(tagAndValue.size()!=2)
        {
            cout<<"ERROR: GBRMaker::prepareTraining(): option "<<token<<" cannot be processed. Should be of the form tag=value.\n";
            continue;
        }
        string tag = tagAndValue[0];
        string value = tagAndValue[1];
        if(tag=="MinEvents")
        {
            int minEvents = 0;
            fromString(minEvents, value);
            m_trainerComb->SetMinEvents(minEvents);
            cout<<"INFO: MinEvents = "<<minEvents<<"\n";
        }
        else if(tag=="Shrinkage")
        {
            float shrink = 0.;
            fromString(shrink, value);
            m_trainerComb->SetShrinkage(shrink);
            cout<<"INFO: Shrinkage = "<<shrink<<"\n";
        }
        else if(tag=="MinSignificance")
        {
            float sig = 0.;
            fromString(sig, value);
            m_trainerComb->SetMinCutSignificance(sig);
            cout<<"INFO: MinSignificance = "<<sig<<"\n";
        }
        else if(tag=="TransitionQuantile")
        {
            float trans = 0.;
            fromString(trans, value);
            m_trainerComb->SetTransitionQuantile(trans);
            cout<<"INFO: TransitionQuantile = "<<trans<<"\n";
        }
        else if(tag=="NTrees")
        {
            // already filled
            cout<<"INFO: NTrees = "<<m_ntrees<<"\n";
        }
        else if(tag=="RandomSeed")
        {
            m_trainerComb->SetRandomSeed(value);
            cout<<"INFO: RandomSeed = "<<value<<"\n";
        }
        else if(tag=="EventWeight")
        {
            m_trainerComb->SetEventWeight(value);
            cout<<"INFO: EventWeight = "<<value<<"\n";
        }
        else
        {
            cout<<"ERROR: HybridGBRMaker::runComb(): Unknown option "<<tag<<"\n";
            cout<<"ERROR: Possibilities are: MinEvents, Shrinkage, MinSignificance, TransitionQuantile, RandomSeed, EventWeight, NTrees\n";
        }
    }


    // add BDT response and errors to the tree
    cout<<"INFO: filling BDT response in tree\n";
    GBRApply gbrApply;
    for(unsigned int t=0; t<m_trees.size(); t++)
        gbrApply.ApplyAsFriendTransform(m_trees[t], m_forestEBmean, m_forestEEmean,
                m_variablesEB, m_variablesEE,
                m_cutEB, m_cutEE,
                "BDTresponse",
                0.2, 2.);

    // add BDT error response to the tree
    cout<<"INFO: filling BDT error in tree\n";
    for(unsigned int t=0; t<m_trees.size(); t++)
        gbrApply.ApplyAsFriendTransform(m_trees[t], m_forestEBwidth, m_forestEEwidth,
                m_variablesEB, m_variablesEE,
                m_cutEB, m_cutEE,
                "BDTerror",
                0.0002, 0.5);


    // run training for combination
    const GBRForest* forestComb = NULL;
    cout<<"INFO: train BDT for combination\n";
    forestComb = m_trainerComb->TrainForest(m_ntrees);
    delete m_trainerComb;
    m_trainerComb = NULL;

    // write GBRForest in output file
    TFile* fileOut = TFile::Open(m_fileOutName.c_str(), "UPDATE");
    if(forestComb)
        fileOut->WriteObject(forestComb, "CombinationWeight");
    else
        cout<<"WARNING: HybridGBRMaker::runComb(): NULL comb forest\n";

    fileOut->WriteObject(&m_variablesComb, "varlistComb");
    fileOut->Close();

}



