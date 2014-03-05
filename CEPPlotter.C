/*
Program: CEP Plotter
Goal: Create histograms.
Project: CEP Analysis

How to Execute:

> root -l CEPPlotter.C

 */

#include <iostream>
#include <fstream>
#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"
#include "RooExtendPdf.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"

using namespace RooFit;

void CEPPlotter(){

  StyleNice();

  // Diffractive Variables
  MakePlotRatio("RJJ_no_multiple_pileup_step4_4","RJJ_multiple_pileup_0_step4_4","noauto","nowidth","",0,"ratio","all"); //always 0!
  //MakePlotRatio("RJJ_no_multiple_pileup_step4_3","RJJ_multiple_pileup_0_step4_3","noauto","nowidth","",4,"ratio","all"); //always 0!
  //MakePlotRatio("RJJ_no_multiple_pileup_step4_2","RJJ_multiple_pileup_0_step4_2","noauto","nowidth","",4,"noratio","all"); //always 0!
  //MakePlotRatio("RJJ_no_multiple_pileup_step4_2_CASTOR","RJJ_multiple_pileup_0_step4_2_CASTOR","noauto","nowidth","",4,"noratio","all");//always 0!
  //MakePlotRatio("deltaEtamaxminPF_no_multiple_pileup_step4_4","deltaEtamaxminPF_multiple_pileup_0_step4_4","noauto","width","dN/d#eta",2,"ratio","nall"); //always 0!
  //MakePlotRatio("deltaEtamaxminPF_no_multiple_pileup_step4_2","deltaEtamaxminPF_multiple_pileup_0_step4_2","noauto","nowidth","",4,"noratio","all"); //always 0!
  //MakePlotRatio("deltaEtamaxminPF_no_multiple_pileup_step4_2_CASTOR","deltaEtamaxminPF_multiple_pileup_0_step4_2_CASTOR","noauto","nowidth","",4,"noratio","all"); //always 0!
  //MakePlotRatio("xiPF_no_multiple_pileup_step4_2_CASTOR","xiPF_multiple_pileup_0_step4_2_CASTOR","noauto","nowidth","",4,"noratio","all"); //always 0!

  //Kinematics
  //MakePlotRatio("etaJet1_no_multiple_pileup_step3","etaJet1_multiple_pileup_0_step3","noauto","nowidth","",4,"ratio","all"); //always 0!
  //MakePlotRatio("etaJet1_no_multiple_pileup_step4_4","etaJet1_multiple_pileup_0_step4_4","noauto","nowidth","",4,"ratio","all"); //always 0!
  //MakePlotRatio("etaJet1_pileup_step4_2","etaJet1_multiple_pileup_0_step4_2","noauto","nowidth","",4,"ratio","all"); //always 0!
  //MakePlotRatio("etaJet1_no_multiple_pileup_step4_2_CASTOR","etaJet1_multiple_pileup_0_step4_2_CASTOR","noauto","nowidth","",4,"ratio","all"); //always 0!
  //MakePlotRatio("etaJet2_no_multiple_pileup_step4_4","etaJet2_multiple_pileup_0_step4_4","noauto","nowidth","",4,"ratio","all"); //always 0!
  //MakePlotRatio("etaJet2_pileup_step4_2","etaJet2_multiple_pileup_0_step4_2","noauto","nowidth","",4,"ratio","all"); //always 0!
  //MakePlotRatio("etaJet2_no_multiple_pileup_step4_2_CASTOR","etaJet2_multiple_pileup_0_step4_2_CASTOR","noauto","nowidth","",4,"ratio","all"); //always 0!
  //MakePlotRatio("pTJet1_no_multiple_pileup_step4_4","pTJet1_multiple_pileup_0_step4_4","noauto","nowidth","",4,"ratio","all"); //always 0!
  //MakePlotRatio("pTJet1_no_multiple_pileup_step4_4","pTJet1_no_multiple_pileup_step4_4","noauto","nowidth","",4,"noratio","all"); //always 0!
  //MakePlotRatio("pTJet1_pileup_step4_2","pTJet1_multiple_pileup_0_step4_2","noauto","nowidth","",4,"ratio","all"); //always 0!
  //MakePlotRatio("pTJet1_no_multiple_pileup_step4_2_CASTOR","pTJet1_multiple_pileup_0_step4_2_CASTOR","noauto","nowidth","",4,"ratio","all"); //always 0!
  //MakePlotRatio("pTJet2_no_multiple_pileup_step4_4","pTJet2_multiple_pileup_0_step4_4","noauto","nowidth","",4,"ratio","all"); //always 0!
  //MakePlotRatio("pTJet2_pileup_step4_2","pTJet2_multiple_pileup_0_step4_2","noauto","nowidth","",4,"ratio","all"); //always 0!
  //MakePlotRatio("pTJet2_no_multiple_pileup_step4_2_CASTOR","pTJet2_multiple_pileup_0_step4_2_CASTOR","noauto","nowidth","",4,"ratio","all"); //always 0!
  //MakePlotRatio("deltaPtJets_no_multiple_pileup_step4_4","deltaPtJets_multiple_pileup_0_step4_4","noauto","nowidth","",4,"ratio","all"); //always 0!
  //MakePlotRatio("deltaPtJets_pileup_step4_2","deltaPtJets_multiple_pileup_0_step4_2","noauto","nowidth","",4,"ratio","all"); //always 0!
  //MakePlotRatio("deltaPtJets_no_multiple_pileup_step4_2_CASTOR","deltaPtJets_multiple_pileup_0_step4_2_CASTOR","noauto","nowidth","",4,"ratio","all"); //always 0!
  //MakePlotRatio("deltaPhiJets_no_multiple_pileup_step4_4","deltaPhiJets_multiple_pileup_0_step4_4","noauto","nowidth","",4,"ratio","all"); //always 0!
  //MakePlotRatio("deltaPhiJets_pileup_step4_2","deltaPhiJets_multiple_pileup_0_step4_2","noauto","nowidth","",4,"ratio","all"); //always 0!
  //MakePlotRatio("deltaPhiJets_no_multiple_pileup_step4_2_CASTOR","deltaPhiJets_multiple_pileup_0_step4_2_CASTOR","noauto","nowidth","",4,"ratio","all"); //always 0!
  //MakePlotRatio("deltaEtaJets_no_multiple_pileup_step4_4","deltaEtaJets_multiple_pileup_0_step4_4","noauto","nowidth","",4,"ratio","all"); //always 0!
  //MakePlotRatio("deltaEtaJets_pileup_step4_2","deltaEtaJets_multiple_pileup_0_step4_2","noauto","nowidth","",4,"ratio","all"); //always 0!
  //MakePlotRatio("deltaEtaJets_no_multiple_pileup_step4_2_CASTOR","deltaEtaJets_multiple_pileup_0_step4_2_CASTOR","noauto","nowidth","",4,"ratio","all"); //always 0!

  // Options: GoldenCEP or AllJets
  //DGlobalFit("AllJets");

}

//
// C r e a t e   a   l i s t   f i l e   w i t h   a l l    *.r o o t   o b j e c t s
//
void RunAll(TString filename, TString logOpt, TString autonorma, TString type, TString th){

  std::ofstream outstring("ListOfHistograms.txt");

  gStyle->SetOptStat(0);
  TFile *f1= new TFile(filename);

  TList* tdf_obs = f1->GetListOfKeys();
  char *hName1 = new char [80];
  char *filesave = new char[80];

  TList *objlist = f1->GetListOfKeys();
  TIterator *itr = objlist->MakeIterator();
  TKey *key;

  TString *currentdir;
  TIter iter(tdf_obs);

  outstring << "" << std::endl;
  outstring << "<< List of Objects >>" << std::endl;
  outstring << " " << std::endl;

  while ((key = static_cast<TKey*>(iter.Next())) != 0) {

    TObject *obj = key->ReadObj();
    TH1F *h = (TH1F*)key->ReadObj();
    sprintf(filesave,"%s.png",h->GetName());

    outstring << obj->GetName() << std::endl;
    cout << "This object has name " << obj->GetName() << endl;

    if (obj->IsA()->InheritsFrom("TDirectory")) {
      TDirectory *d = static_cast<TDirectory*>(obj);
      cout << "Dir: " << d->GetPath() << endl;
    }

    if (h->GetEntries() != 0){ // Defense
      if(obj->IsA()->InheritsFrom("TH1")){
	hName1=h->GetName();
      }
    }

  }

  outstring.close();

}

//
// S t y l e
//

void TH1Draw(TH1F* h_1, TH1F* h_2, TH1F* h_3){

  h_1->SetLineColor(kBlack);
  h_1->SetMarkerStyle(20);
  h_1->SetMarkerSize(0.8);
  h_1->GetYaxis()->SetTitle("N Events");

  h_2->SetLineColor(kRed);
  h_2->SetLineWidth(2);
  h_2->SetFillColor(kRed-4);
  h_2->SetFillStyle(3020);
  h_2->GetYaxis()->SetTitle("N Events");

  h_3->SetLineColor(kBlue);
  h_3->SetLineWidth(2);
  h_3->SetFillColor(kBlue-4);
  h_3->SetFillStyle(3020);
  h_3->GetYaxis()->SetTitle("N Events");

}

void format_h(TH1F* h, int linecolor){
  h->SetLineWidth(3);
  h->SetLineColor(linecolor);
}

//
// M a k e   a   s i n g l e   p l o t   w i t h   F i t 
//

void MakePlotRatio(TString name1, TString name2, TString AutoNorma, TString diff, TString ytitle, double rebinopt, TString mode, TString SumHisto){

  TLegend* leg = new TLegend(0.7597956,0.822335,0.9931857,0.9949239,NULL,"brNDC");
  TString legdata, legpompyt, legexhume, legpomwig, legherwig, legboth;


  leg->SetFillColor(kWhite);

  TFile *data = TFile::Open("nonehisto_multijet_HLTExclDiJet30U_AND_HFPreSel_GoodVertex_triggerRefDijet50And30_68mb_24bin_pT60_60.root");
  TFile *data_up_jets = TFile::Open("plus_jets_histo_multijet_HLTExclDiJet30U_AND_HFPreSel_GoodVertex_triggerRefDijet50And30_68mb_24bin_pT60_60.root");
  TFile *data_down_jets = TFile::Open("minus_jets_histo_multijet_HLTExclDiJet30U_AND_HFPreSel_GoodVertex_triggerRefDijet50And30_68mb_24bin_pT60_60.root");
  TFile *data_up_pf = TFile::Open("plus_pf_histo_multijet_HLTExclDiJet30U_AND_HFPreSel_GoodVertex_triggerRefDijet50And30_68mb_24bin_pT60_60.root");
  TFile *data_down_pf = TFile::Open("minus_pf_histo_multijet_HLTExclDiJet30U_AND_HFPreSel_GoodVertex_triggerRefDijet50And30_68mb_24bin_pT60_60.root");
  TFile *data_up_trigger = TFile::Open("plus_trigger_histo_multijet_HLTExclDiJet30U_AND_HFPreSel_GoodVertex_triggerRefDijet50And30_68mb_24bin_pT60_60.root");
  TFile *data_down_trigger = TFile::Open("minus_trigger_histo_multijet_HLTExclDiJet30U_AND_HFPreSel_GoodVertex_triggerRefDijet50And30_68mb_24bin_pT60_60.root");
  TFile *data_trigger_eff = TFile::Open("nonehisto_multijet_HLTExclDiJet30U_AND_HFPreSel_GoodVertex_triggerRefDijet50And30_triggercorr_effcorr_68mb_24bin_pT60_60.root");
  TFile *data_trigger = TFile::Open("nonehisto_multijet_HLTExclDiJet30U_AND_HFPreSel_GoodVertex_triggerRefDijet50And30_triggercorr_68mb_24bin_pT60_60.root");

  TFile *exhume = TFile::Open("histo_exhume.root");
  TFile *pompyt = TFile::Open("histo_pompyt.root");
  TFile *pomwig = TFile::Open("histo_pomwig.root"); 
  TFile *herwigpu0 = TFile::Open("histo_herwigpu_pT60_60_pu0.root");
  legdata = "2010 data";
  legpompyt = "POMPYT * 5%";
  legexhume = "ExHuMe * 5%";
  legpomwig = "Pomwig* 5%";
  legherwig = "Herwig++ PU[0]";
  legboth = "All models";

  TH1F* h_1 = (TH1F*)data->Get(name1);
  TH1F* h_2 = (TH1F*)pompyt->Get(name1);
  TH1F* h_3 = (TH1F*)exhume->Get(name1);
  TH1F* h_4 = (TH1F*)pomwig->Get(name1);
  TH1F* h_5 = (TH1F*)herwigpu0->Get(name2);
  TH1F* h_1_trigger_eff = (TH1F*)data_trigger_eff->Get(name1);
  TH1F* h_1_trigger = (TH1F*)data_trigger->Get(name1);
  TH1F* h_1_up_jets = (TH1F*)data_up_jets->Get(name1);
  TH1F* h_1_down_jets = (TH1F*)data_down_jets->Get(name1);
  TH1F* h_1_up_pf = (TH1F*)data_up_pf->Get(name1);
  TH1F* h_1_down_pf = (TH1F*)data_down_pf->Get(name1);
  TH1F* h_1_up_trigger = (TH1F*)data_up_trigger->Get(name1);
  TH1F* h_1_down_trigger = (TH1F*)data_down_trigger->Get(name1);

  if(rebinopt > 0){
    h_1->Rebin(rebinopt);
    h_1_trigger_eff->Rebin(rebinopt);
    h_1_up_jets->Rebin(rebinopt);
    h_1_up_pf->Rebin(rebinopt);
    h_1_down_jets->Rebin(rebinopt);
    h_1_down_pf->Rebin(rebinopt);
    h_1_up_trigger->Rebin(rebinopt);
    h_1_down_trigger->Rebin(rebinopt);
       h_1_trigger->Rebin(rebinopt);
    h_2->Rebin(rebinopt);
    h_3->Rebin(rebinopt);
    h_4->Rebin(rebinopt);
    h_5->Rebin(rebinopt);
  }

  if(diff == "width" || diff == "WIDTH"){
    double lumi = 0.04587; // 1/21.82, luminosity^{-1} here.
    h_1->Scale(lumi,"width");
    h_1_trigger_eff->Scale(lumi,"width");
    h_1_up_jets->Scale(lumi,"width");
    h_1_up_pf->Scale(lumi,"width");
    h_1_down_jets->Scale(lumi,"width");
    h_1_down_pf->Scale(lumi,"width");
    h_1_up_trigger->Scale(lumi,"width");
    h_1_down_trigger->Scale(lumi,"width");
    h_1_trigger->Scale(lumi,"width");
    h_2->Scale(lumi,"width");
    h_3->Scale(lumi,"width");
    h_4->Scale(lumi,"width");
    h_5->Scale(lumi,"width");
    h_1->GetYaxis()->SetTitle(ytitle);
    h_2->GetYaxis()->SetTitle(ytitle);
    h_3->GetYaxis()->SetTitle(ytitle);
    h_4->GetYaxis()->SetTitle(ytitle);
    h_5->GetYaxis()->SetTitle(ytitle);
  }else{
    h_1->GetYaxis()->SetTitle("N Events");
    h_2->GetYaxis()->SetTitle("N Events");
    h_3->GetYaxis()->SetTitle("N Events");
    h_4->GetYaxis()->SetTitle("N Events");
    h_5->GetYaxis()->SetTitle("N Events");
  }


  h_1->Sumw2();
  h_1_up_jets->Sumw2();
  h_1_up_pf->Sumw2();
  h_1_down_jets->Sumw2();
  h_1_down_pf->Sumw2();
  h_1_down_trigger->Sumw2();
  h_1_up_trigger->Sumw2();
  h_1_trigger_eff->Sumw2();
  h_1_trigger->Sumw2();
  h_2->Sumw2();
  h_3->Sumw2();
  h_4->Sumw2();
  h_5->Sumw2();

  double factornon = h_1->Integral()/h_1_trigger_eff->Integral();

  for (int i=1; i<= h_1_trigger_eff->GetNbinsX(); i++){
    double scaleFactor;

    if(h_1_trigger_eff->GetBinContent(i) > 0.){
      scaleFactor = h_1->GetBinContent(i)/h_1_trigger_eff->GetBinContent(i);
      h_2->SetBinContent(i,h_2->GetBinContent(i)*scaleFactor);
      h_2->SetBinError(i,h_2->GetBinError(i)*scaleFactor);
      h_3->SetBinContent(i,h_3->GetBinContent(i)*scaleFactor);
      h_3->SetBinError(i,h_3->GetBinError(i)*scaleFactor);
      h_4->SetBinContent(i,h_4->GetBinContent(i)*scaleFactor);
      h_4->SetBinError(i,h_4->GetBinError(i)*scaleFactor);
      h_5->SetBinContent(i,h_5->GetBinContent(i)*scaleFactor);
      h_5->SetBinError(i,h_5->GetBinError(i)*scaleFactor);
    }else{
      h_2->SetBinContent(i,h_2->GetBinContent(i)*factornon);
      h_2->SetBinError(i,h_2->GetBinError(i)*factornon);
      h_3->SetBinContent(i,h_3->GetBinContent(i)*factornon);
      h_3->SetBinError(i,h_3->GetBinError(i)*factornon);
      h_4->SetBinContent(i,h_4->GetBinContent(i*factornon));
      h_4->SetBinError(i,h_4->GetBinError(i)*factornon);
      h_5->SetBinContent(i,h_5->GetBinError(i)*factornon);
      h_5->SetBinError(i,h_5->GetBinError(i)*factornon);
    }
  }

  // Survival Probability 5%  
  h_2->Scale(0.05);
  h_4->Scale(0.05);

  TList *listAll = new TList;
  listAll->Add(h_2);
  listAll->Add(h_3);
  listAll->Add(h_4);
  listAll->Add(h_5);

  TH1F *MCtogether = (TH1F*)h_5->Clone("MCtogether");
  MCtogether->Reset();
  MCtogether->SetLineColor(kOrange);
  MCtogether->Merge(listAll);

  leg->AddEntry(h_2,legpompyt,"LF");
  leg->AddEntry(h_3,legexhume,"LF");
  leg->AddEntry(h_4,legpomwig,"LF");
  leg->AddEntry(h_5,legherwig,"LF");

  h_1->SetLineColor(kBlack);
  h_1->SetMarkerStyle(20);
  h_1->SetMarkerSize(1.2);

  h_2->SetLineColor(kOrange);
  h_2->SetLineWidth(4);

  h_3->SetLineColor(kGreen);
  h_3->SetLineWidth(4);

  h_4->SetLineColor(kBlue);
  h_4->SetLineWidth(4);

  h_5->SetLineColor(kRed);
  h_5->SetLineWidth(4);


  TH1F* dividend=new TH1F(*h_1);
  dividend->Divide(h_5);

  TH1F* dividend2=new TH1F(*h_1);
  dividend2->Divide(h_3);

  format_h(dividend,kRed-4);
  format_h(dividend2,kGreen-4);
  gStyle->SetOptStat(0);

  if (mode == "ratio"){
    TCanvas* RatioCanvas= new TCanvas();
    RatioCanvas->Divide(1,2);
    RatioCanvas->cd(1);
    RatioCanvas->GetPad(1)->SetRightMargin(.01);
  }
  else{
    TCanvas* RatioCanvas= new TCanvas();
    RatioCanvas->cd();
  }

  vector<int> elementBin;

  for (int i=0; i<h_1->GetNbinsX(); i++){
    if(h_1_trigger_eff->GetBinContent(i+1)>0){
      elementBin.push_back(i+1);
    }

  }

  int NBins = elementBin.size();
  const int n = NBins;

  float x[n];
  float y[n];
  float exl[n];
  float eyl[n];
  float exh[n];
  float eyh[n];

  for (std::vector<std::string>::size_type j=0; j<elementBin.size(); j++){

    int i = elementBin.at(j);

    float BinWidth = h_1->GetXaxis()->GetBinWidth(i);

    float deltauppf2 = pow(h_1_up_pf->GetBinContent(i)-h_1->GetBinContent(i),2);
    float deltadownpf2 = pow(h_1_down_pf->GetBinContent(i)-h_1->GetBinContent(i),2);
    float deltaupjets2 = pow(h_1_up_jets->GetBinContent(i)-h_1->GetBinContent(i),2);
    float deltadownjets2 = pow(h_1_down_jets->GetBinContent(i)-h_1->GetBinContent(i),2);
    float deltauptrigger2 = pow(h_1_up_trigger->GetBinContent(i)-h_1_trigger->GetBinContent(i),2);
    float deltadowntrigger2 = pow(h_1_down_trigger->GetBinContent(i)-h_1_trigger->GetBinContent(i),2);
    float statistics2 = pow(h_1->GetBinError(i),2);

    x[j] = h_1->GetXaxis()->GetBinCenter(i);
    y[j] = h_1->GetBinContent(i);
    exl[j] = BinWidth/2;
    exh[j] = BinWidth/2;
    eyh[j] = TMath::Sqrt(deltaupjets2+deltauppf2+statistics2+deltauptrigger2);
    eyl[j] = TMath::Sqrt(deltadownjets2+deltadownpf2+statistics2+deltadowntrigger2);

  }

  gr = new TGraphAsymmErrors(n,x,y,exl,exh,eyl,eyh);
  gr->SetMarkerStyle(20);
  gr->GetYaxis()->SetTitle("N Events");
  gr->GetXaxis()->SetTitle(h_1->GetXaxis()->GetTitle());
  gr->SetFillStyle(3001);
  gr->SetLineWidth(0);
  gr->SetFillColor(kOrange+1);

  h_5->Draw("HISTO");
  h_4->Draw("SAMEHISTO");
  h_3->Draw("SAMEHISTO");
  h_2->Draw("SAMEHISTO");  
  if (SumHisto=="all" || SumHisto == "ALL"){
    MCtogether->SetFillStyle(0);
    MCtogether->SetLineWidth(4);
    MCtogether->SetLineColor(32);
    leg->AddEntry(MCtogether,legboth,"LF");
    if(rebinopt == "rebin"){
      MCtogether->Rebin(4);
    }
    MCtogether->Draw("SAMEHISTO");
  }

  leg->AddEntry(gr,legdata,"P");
  leg->AddEntry(gr,"Systematics","F");
  gr->Draw("P E2");
  leg->Draw("SAME");


  if(mode=="ratio"){
    RatioCanvas->cd(2);
    dividend->GetYaxis()->SetRangeUser(0,2.49);
    RatioCanvas->GetPad(2)->SetGridy();
    RatioCanvas->GetPad(2)->SetRightMargin(.01);
    dividend->GetYaxis()->SetTitle("data/mc");
    dividend->Draw();
    dividend2->Draw("same");
  }

  DFitExtended(h_1,h_5,h_4,h_2,h_3,h_1->GetXaxis()->GetXmin(),h_1->GetXaxis()->GetXmax());

  cout << "\n S U M M A R Y\n " << endl;
  cout << "# events Data: " << h_1->GetEntries() << endl;
  cout << "# events HERWIG PU(0), QCD: " << h_5->GetEntries() << endl;
  cout << "# events Pomwig, DPE: " << h_4->GetEntries() << endl;
  cout << "# events Pompyt, SD: " << h_2->GetEntries() << endl;
  cout << "# events ExHuMe, CEP: " << h_3->GetEntries() << endl;
  cout << "" << endl;

}


//
// F i t:   L i k e l i h o o h   E x t e n d e d   F i t 
//

void DFitExtended(TH1 *Dat, TH1 *BkgQCD, TH1 *BkgPomwig, TH1 *BkgPompyt, TH1 *SigExhume, double x_min, double x_max){

  // S e t u p   c o m p o n e n t   p d f s 
  // ---------------------------------------

  // Declare observable x
  RooRealVar x(Dat->GetXaxis()->GetTitle(), Dat->GetXaxis()->GetTitle(), x_min, x_max); 

  // Get PDFs
  RooDataHist data_in("data_in","data_in",x,Dat);
  RooDataHist bkg_in_QCD("bkg_in_QCD","bkg_in_QCD",x,BkgQCD) ;
  RooDataHist bkg_in_pomwig("bkg_in_pomwig","bkg_in_pomwig",x,BkgPomwig);
  RooDataHist bkg_in_pompyt("bkg_in_pompyt","bkg_in_pompyt",x,BkgPompyt);
  RooDataHist sig_in_exhume("sig_in_exhume","sig_in_exhme",x,SigExhume) ;

  RooHistPdf data("PDFdata_in", "PDFdata_in", x, data_in) ;
  RooHistPdf sig_exhume("PDFsig_in_exhume", "PDFsig_in_exhume", x, sig_in_exhume) ;
  RooHistPdf bkg_QCD("PDFbkg_in_QCD", "PDFbkg_in_QCD", x, bkg_in_QCD) ;
  RooHistPdf bkg_pomwig("PDFbkg_in_pomwig", "PDFbkg_in_pomwig", x, bkg_in_pomwig) ;
  RooHistPdf bkg_pompyt("PDFbkg_in_pompyt", "PDFbkg_in_pompyt", x, bkg_in_pompyt) ;

  /////////////////////
  // M E T H O D   1 //
  /////////////////////


  // C o n s t r u c t   e x t e n d e d   c o m p o s i t e   m o d e l 
  // -------------------------------------------------------------------

  // Sum the composite signal and background into an extended pdf.
  RooRealVar nsig_exhume("nsig_exhume","number of signal events",1,0,100000);
  RooRealVar nbkg_qcd("nbkg_qcd","number of QCD background events",1,0,100000);
  RooRealVar nbkg_pomwig("nbkg_pomwig","number of Pomwig background events",1,0,100000);
  RooRealVar nbkg_pompyt("nbkg_pompyt","number of Pompyt background events",1,0,100000);

  RooAddPdf  model("model","(g1+g2+g3+g4)+a",RooArgList(bkg_QCD,bkg_pomwig, bkg_pompyt,sig_exhume),RooArgList(nbkg_qcd,nbkg_pomwig,nbkg_pompyt,nsig_exhume));

  // S a m p l e ,   f i t   a n d   p l o t   e x t e n d e d   m o d e l 
  // ---------------------------------------------------------------------

  // Generate a data sample of expected number events in x from model
  // = model.expectedEvents() = nsig+nbkg
  //RooDataSet *data = model.generate(x) ;

  // Fit model to data, extended ML term automatically included
  model.fitTo(data_in,Extended(kTRUE)) ; 

  // Plot data and PDF overlaid, use expected number of events for p.d.f projection normalization
  // rather than observed number of events (==data->numEntries())
  RooPlot* xframe = x.frame(Title("extended ML fit example")) ;
  data_in.plotOn(xframe,RooFit::Name("Data")) ;
  model.plotOn(xframe,Normalization(1.0,RooAbsReal::RelativeExpected)) ;

  // Overlay the background component of model with a dashed line
  model.plotOn(xframe,Components(RooArgSet(bkg_QCD,bkg_pomwig, bkg_pompyt)),Name("background"),LineStyle(kDashed),LineColor(kRed),Normalization(1.0,RooAbsReal::RelativeExpected)) ;

  // Overlay the background+sig2 components of model with a dotted line
  model.plotOn(xframe,Components(RooArgSet(bkg_QCD,bkg_pomwig, bkg_pompyt,sig_exhume)),LineStyle(kDotted),Name("background+signal"),Normalization(1.0,RooAbsReal::RelativeExpected)) ;

  // Print structure of composite p.d.f.
  //model.Print("t") ;

  /////////////////////
  // M E T H O D   2 //
  /////////////////////

  // C o n s t r u c t   e x t e n d e d   c o m p o n e n t s   f i r s t
  // ---------------------------------------------------------------------

  // Associated nsig/nbkg as expected number of events with sig/bkg
  RooExtendPdf esig("esig","esig",sig_exhume,nsig_exhume) ;
  RooExtendPdf ebkgqcd("ebkgqcd","ebkgqcd",bkg_QCD,nbkg_qcd) ;
  RooExtendPdf ebkgpomwig("ebkgpomwig","ebkgpomwig",bkg_pomwig,nbkg_pomwig) ;
  RooExtendPdf ebkgpompyt("ebkgpompyt","ebkgpompyt",bkg_pompyt,nbkg_pompyt) ;

  // S u m   e x t e n d e d   c o m p o n e n t s   w i t h o u t   c o e f s 
  // -------------------------------------------------------------------------

  // Construct sum of two extended p.d.f. (no coefficients required)
  RooAddPdf  model2("model2","(g1+g2+g3+g4)+a",RooArgList(ebkgqcd,ebkgpomwig,ebkgpompyt,esig)) ;

  RooFitResult* r = model2.fitTo(data_in,RooFit::Save()) ;
  r->Print("esig");
  r->Print("ebkgqcd");
  r->Print("ebkgpomwig");
  r->Print("ebkgpompyt");
  r->Print("v") ;

  // Fit chi2
  //Double_t chi2 = xframe->chiSquare("model", "data", 3);

  //model2.paramOn(xframe);

  // Draw the frame on the canvas
  new TCanvas("composite","composite",600,600) ;
  gPad->SetLeftMargin(0.15) ; xframe->GetYaxis()->SetTitleOffset(1.4) ; xframe->Draw() ;

  TLegend *legend = new TLegend(0.7,0.7,0.9,0.9);
  legend->SetTextFont(72);
  legend->SetTextSize(0.05);
  legend->AddEntry("Data","Data","P ");
  legend->AddEntry("background+signal","background+signal","L ");
  legend->AddEntry("background","background","L ");
  legend->Draw();

}


// L I K E L I H O O D   E X T E N D E D   G L O B A L   F I T

void DGlobalFit(TString type){

  bool debug = false;

  if(type == "AllJets"){
    TFile *data  = TFile::Open("TTreeAllJets_nonehisto_multijet_HLTExclDiJet30U_AND_HFPreSel_GoodVertex_triggerRefDijet50And30_68mb_24bin_pT60_60.root");
    TFile *exhume = TFile::Open("TTreeAllJets_histo_exhume.root");
    TFile *pompyt = TFile::Open("TTreeAllJets_histo_pompyt.root");
    TFile *pomwig = TFile::Open("TTreeAllJets_histo_pomwig.root"); 
    TFile *herwig = TFile::Open("TTreeAllJets_histo_herwigpu_pT60_60.root");
  }else if(type == "GoldenCEP"){
    TFile *data  = TFile::Open("TTreeGoldenCEP_nonehisto_multijet_HLTExclDiJet30U_AND_HFPreSel_GoodVertex_triggerRefDijet50And30_68mb_24bin_pT60_60.root");
    TFile *exhume = TFile::Open("TTreeGoldenCEP_histo_exhume.root");
    TFile *pompyt = TFile::Open("TTreeGoldenCEP_histo_pompyt.root");
    TFile *pomwig = TFile::Open("TTreeGoldenCEP_histo_pomwig.root"); 
    TFile *herwig = TFile::Open("TTreeGoldenCEP_histo_herwigpu_pT60_60.root");
  }else{
    std::cout << "Please, put correct option." << std::endl;
    exit(0);
  }

  TTree *datain = (TTree*)data->Get("Events");
  TTree *herwigin = (TTree*)herwig->Get("Events");
  TTree *pompytin = (TTree*)pompyt->Get("Events");
  TTree *exhumein = (TTree*)exhume->Get("Events");
  TTree *pomwigin = (TTree*)pomwig->Get("Events");

  RooRealVar Rjj("Rjj","Rjj",0,1); //100
  RooRealVar nTracks("nTracks","nTracks",0,100);
  RooRealVar DeltaEtaPF("DeltaEtaPF","DeltaEtaPF",0,10);
  RooRealVar XiPlus("XiPlus","XiPlus",0,0.2);
  RooRealVar XiMinus("XiMinus","XiMinus",0,0.2); 

  RooDataSet DataSet("data","data",datain,RooArgSet(Rjj,nTracks,DeltaEtaPF,XiPlus,XiMinus));
  RooDataSet herwigSet("herwig","herwig",herwigin,RooArgSet(Rjj,nTracks,DeltaEtaPF,XiPlus,XiMinus));
  RooDataSet pompytSet("pompyt","pompyt",pompytin,RooArgSet(Rjj,nTracks,DeltaEtaPF,XiPlus,XiMinus));
  RooDataSet exhumeSet("exhume","exhume",exhumein,RooArgSet(Rjj,nTracks,DeltaEtaPF,XiPlus,XiMinus));
  RooDataSet pomwigSet("pomwig","pomwig",pomwigin,RooArgSet(Rjj,nTracks,DeltaEtaPF,XiPlus,XiMinus));

  if (debug){
    DataSet.Print();
    herwigSet.Print();
    pompytSet.Print();
    exhumeSet.Print();
    pomwigSet.Print();
  }

  //   H E R W I G
  RooDataHist herwigHistoRjj("herwigHistoRjj","herwigHistoRjj", Rjj, herwigSet);
  RooHistPdf herwigPDFRjj("herwigPDFRjj", "herwigPDFRjj", Rjj, herwigHistoRjj) ;

  RooDataHist herwigHistonTracks("herwigHistonTracks","herwigHistonTracks", nTracks, herwigSet);
  RooHistPdf herwigPDFnTracks("herwigPDFnTracks", "herwigPDFnTracks", nTracks, herwigHistonTracks) ;

  RooDataHist herwigHistoDeltaEtaPF("herwigHistoDeltaEtaPF","herwigHistoDeltaEtaPF", DeltaEtaPF, herwigSet);
  RooHistPdf herwigPDFDeltaEtaPF("herwigPDFDeltaEtaPF", "herwigPDFDeltaEtaPF", DeltaEtaPF, herwigHistoDeltaEtaPF) ;

  RooDataHist herwigHistoXiPlus("herwigHistoXiPlus","herwigHistoXiPlus", XiPlus, herwigSet);
  RooHistPdf herwigPDFXiPlus("herwigPDFXiPlus", "herwigPDFXiPlus", XiPlus, herwigHistoXiPlus) ;

  RooDataHist herwigHistoXiMinus("herwigHistoXiMinus","herwigHistoXiMinus", XiMinus, herwigSet);
  RooHistPdf herwigPDFXiMinus("herwigPDFXiMinus", "herwigPDFXiMinus", XiMinus, herwigHistoXiMinus) ;


  //   P O M P Y T
  RooDataHist pompytHistoRjj("pompytHistoRjj","pompytHistoRjj", Rjj, pompytSet);
  RooHistPdf pompytPDFRjj("pompytPDFRjj", "pompytPDFRjj", Rjj, pompytHistoRjj) ;

  RooDataHist pompytHistonTracks("pompytHistonTracks","pompytHistonTracks", nTracks, pompytSet);
  RooHistPdf pompytPDFnTracks("pompytPDFnTracks", "pompytPDFnTracks", nTracks, pompytHistonTracks) ;

  RooDataHist pompytHistoDeltaEtaPF("pompytHistoDeltaEtaPF","pompytHistoDeltaEtaPF", DeltaEtaPF, pompytSet);
  RooHistPdf pompytPDFDeltaEtaPF("pompytPDFDeltaEtaPF", "pompytPDFDeltaEtaPF", DeltaEtaPF, pompytHistoDeltaEtaPF) ;

  RooDataHist pompytHistoXiPlus("pompytHistoXiPlus","pompytHistoXiPlus", XiPlus, pompytSet);
  RooHistPdf pompytPDFXiPlus("pompytPDFXiPlus", "pompytPDFXiPlus", XiPlus, pompytHistoXiPlus) ;

  RooDataHist pompytHistoXiMinus("pompytHistoXiMinus","pompytHistoXiMinus", XiMinus, pompytSet);
  RooHistPdf pompytPDFXiMinus("pompytPDFXiMinus", "pompytPDFXiMinus", XiMinus, pompytHistoXiMinus) ;


  //   E X H U M E
  RooDataHist exhumeHistoRjj("exhumeHistoRjj","exhumeHistoRjj", Rjj, exhumeSet);
  RooHistPdf exhumePDFRjj("exhumePDFRjj", "exhumePDFRjj", Rjj, exhumeHistoRjj) ;

  RooDataHist exhumeHistonTracks("exhumeHistonTracks","exhumeHistonTracks", nTracks, exhumeSet);
  RooHistPdf exhumePDFnTracks("exhumePDFnTracks", "exhumePDFnTracks", nTracks, exhumeHistonTracks) ;

  RooDataHist exhumeHistoDeltaEtaPF("exhumeHistoDeltaEtaPF","exhumeHistoDeltaEtaPF", DeltaEtaPF, exhumeSet);
  RooHistPdf exhumePDFDeltaEtaPF("exhumePDFDeltaEtaPF", "exhumePDFDeltaEtaPF", DeltaEtaPF, exhumeHistoDeltaEtaPF) ;

  RooDataHist exhumeHistoXiPlus("exhumeHistoXiPlus","exhumeHistoXiPlus", XiPlus, exhumeSet);
  RooHistPdf exhumePDFXiPlus("exhumePDFXiPlus", "exhumePDFXiPlus", XiPlus, exhumeHistoXiPlus) ;

  RooDataHist exhumeHistoXiMinus("exhumeHistoXiMinus","exhumeHistoXiMinus", XiMinus, exhumeSet);
  RooHistPdf exhumePDFXiMinus("exhumePDFXiMinus", "exhumePDFXiMinus", XiMinus, exhumeHistoXiMinus) ;


  //   P O M W I G
  RooDataHist pomwigHistoRjj("pomwigHistoRjj","pomwigHistoRjj", Rjj, pomwigSet);
  RooHistPdf pomwigPDFRjj("pomwigPDFRjj", "pomwigPDFRjj", Rjj, pomwigHistoRjj) ;

  RooDataHist pomwigHistonTracks("pomwigHistonTracks","pomwigHistonTracks", nTracks, pomwigSet);
  RooHistPdf pomwigPDFnTracks("pomwigPDFnTracks", "pomwigPDFnTracks", nTracks, pomwigHistonTracks) ;

  RooDataHist pomwigHistoDeltaEtaPF("pomwigHistoDeltaEtaPF","pomwigHistoDeltaEtaPF", DeltaEtaPF, pomwigSet);
  RooHistPdf pomwigPDFDeltaEtaPF("pomwigPDFDeltaEtaPF", "pomwigPDFDeltaEtaPF", DeltaEtaPF, pomwigHistoDeltaEtaPF) ;

  RooDataHist pomwigHistoXiPlus("pomwigHistoXiPlus","pomwigHistoXiPlus", XiPlus, pomwigSet);
  RooHistPdf pomwigPDFXiPlus("pomwigPDFXiPlus", "pomwigPDFXiPlus", XiPlus, pomwigHistoXiPlus) ;

  RooDataHist pomwigHistoXiMinus("pomwigHistoXiMinus","pomwigHistoXiMinus", XiMinus, pomwigSet);
  RooHistPdf pomwigPDFXiMinus("pomwigPDFXiMinus", "pomwigPDFXiMinus", XiMinus, pomwigHistoXiMinus) ;


  //   F R E E   P A R A M E T E R S 
  RooRealVar nherwig("nherwig","number of herwig",5000,0,5000); 
  RooRealVar nexhume("nexhume","number of exhume",2000,0,2000); 
  RooRealVar npompyt("npompyt","number of pompyt",100,0,100); 
  RooRealVar npomwig("npomwig","number of pomwig",1000,0,1000); 


  //   M U L T I P L Y I N G   P D F S
  RooProdPdf modelHerwig("modelherwig","modelherwig",RooArgSet(herwigPDFRjj,herwigPDFnTracks,herwigPDFDeltaEtaPF,herwigPDFXiPlus,herwigPDFXiMinus));
  RooProdPdf modelPompyt("modelPompyt","modelPompyt",RooArgSet(pompytPDFRjj,pompytPDFnTracks,pompytPDFDeltaEtaPF,pompytPDFXiPlus,pompytPDFXiMinus));
  RooProdPdf modelExhume("modelExhume","modelExhume",RooArgSet(exhumePDFRjj,exhumePDFnTracks,exhumePDFDeltaEtaPF,exhumePDFXiPlus,exhumePDFXiMinus));
  RooProdPdf modelPomwig("modelPomwig","modelPomwig",RooArgSet(pomwigPDFRjj,pomwigPDFnTracks,pomwigPDFDeltaEtaPF,pomwigPDFXiPlus,pomwigPDFXiMinus));

  //   C R E A T I N G   M O D E L
  RooAddPdf  model("model","(g1+g2+g3+g4)+a",RooArgList(modelHerwig,modelPompyt,modelPomwig,modelExhume),RooArgList(nherwig,npompyt,npomwig,nexhume)) ;
  model.fitTo(DataSet,Extended(kTRUE)) ;


  //   P L O T T I N G   E A C H   D I M E N S I O N

  // Plot Rjj
  RooPlot* xframeRjj = Rjj.frame(Title("extended ML fit example")) ;
  DataSet.plotOn(xframeRjj,RooFit::Name("Data")) ;
  //model.plotOn(xframeRjj,Normalization(1.0,RooAbsReal::RelativeExpected),LineColor(kOrange)) ;
  model.plotOn(xframeRjj,Components(RooArgSet(herwigPDFRjj,pompytPDFRjj,pomwigPDFRjj)),Name("Background"),LineStyle(kDashed),LineColor(kRed),Normalization(1.0,RooAbsReal::RelativeExpected)) ;
  model.plotOn(xframeRjj,Components(RooArgSet(exhumePDFRjj,herwigPDFRjj,pompytPDFRjj,pomwigPDFRjj)),LineColor(kBlue),Name("Signal+Background"),Normalization(1.0,RooAbsReal::RelativeExpected)) ;
  model.Print("t") ;

  // Plot nTracks
  RooPlot* xframenTracks = nTracks.frame(Title("extended ML fit example")) ;
  DataSet.plotOn(xframenTracks,RooFit::Name("Data")) ;
  //model.plotOn(xframenTracks,Normalization(1.0,RooAbsReal::RelativeExpected),LineColor(kOrange)) ;
  model.plotOn(xframenTracks,Components(RooArgSet(herwigPDFnTracks,pompytPDFnTracks,pomwigPDFnTracks)),Name("Background"),LineStyle(kDashed),LineColor(kRed),Normalization(1.0,RooAbsReal::RelativeExpected)) ;
  model.plotOn(xframenTracks,Components(RooArgSet(exhumePDFnTracks,herwigPDFnTracks,pompytPDFnTracks,pomwigPDFnTracks)),LineColor(kBlue),Name("Signal+Background"),Normalization(1.0,RooAbsReal::RelativeExpected)) ;
  model.Print("t") ;

  // Plot Tracks
  RooPlot* xframeDeltaEtaPF = DeltaEtaPF.frame(Title("extended ML fit example")) ;
  DataSet.plotOn(xframeDeltaEtaPF,RooFit::Name("Data")) ;
  //model.plotOn(xframeDeltaEtaPF,Normalization(1.0,RooAbsReal::RelativeExpected),LineColor(kOrange)) ;
  model.plotOn(xframeDeltaEtaPF,Components(RooArgSet(herwigPDFDeltaEtaPF,pompytPDFDeltaEtaPF,pomwigPDFDeltaEtaPF)),Name("Background"),LineStyle(kDashed),LineColor(kRed),Normalization(1.0,RooAbsReal::RelativeExpected)) ;
  model.plotOn(xframeDeltaEtaPF,Components(RooArgSet(exhumePDFDeltaEtaPF,herwigPDFDeltaEtaPF,pompytPDFDeltaEtaPF,pomwigPDFDeltaEtaPF)),LineColor(kBlue),Name("Signal+Background"),Normalization(1.0,RooAbsReal::RelativeExpected)) ;
  model.Print("t") ;

  // Plot XiPlus
  RooPlot* xframeXiPlus = XiPlus.frame(Title("extended ML fit example")) ;
  DataSet.plotOn(xframeXiPlus,RooFit::Name("Data"));
  //model.plotOn(xframeXiPlus,Normalization(1.0,RooAbsReal::RelativeExpected),LineColor(kOrange)) ;
  model.plotOn(xframeXiPlus,Components(RooArgSet(herwigPDFXiPlus,pompytPDFXiPlus,pomwigPDFXiPlus)),Name("Background"),LineStyle(kDashed),LineColor(kRed),Normalization(1.0,RooAbsReal::RelativeExpected)) ;
  model.plotOn(xframeXiPlus,Components(RooArgSet(exhumePDFXiPlus,herwigPDFXiPlus,pompytPDFXiPlus,pomwigPDFXiPlus)),LineColor(kBlue),Name("Signal+Background"),Normalization(1.0,RooAbsReal::RelativeExpected)) ;
  model.Print("t") ;

  // Plot XiMinus
  RooPlot* xframeXiMinus = XiMinus.frame(Title("extended ML fit example")) ;
  DataSet.plotOn(xframeXiMinus,RooFit::Name("Data"));
  //model.plotOn(xframeXiMinus,Normalization(1.0,RooAbsReal::RelativeExpected),LineColor(kOrange)) ;
  model.plotOn(xframeXiMinus,Components(RooArgSet(herwigPDFXiMinus,pompytPDFXiMinus,pomwigPDFXiMinus)),Name("Background"),LineStyle(kDashed),LineColor(kRed),Normalization(1.0,RooAbsReal::RelativeExpected)) ;
  model.plotOn(xframeXiMinus,Components(RooArgSet(exhumePDFXiMinus,herwigPDFXiMinus,pompytPDFXiMinus,pomwigPDFXiMinus)),LineColor(kBlue),Name("Signal+Background"),Normalization(1.0,RooAbsReal::RelativeExpected)) ;
  model.Print("t") ;


  /////////////////////
  // M E T H O D   2 //
  /////////////////////

  // C o n s t r u c t   e x t e n d e d   c o m p o n e n t s   f i r s t
  // ---------------------------------------------------------------------

  // Associated nexhume/nherwig as expected number of events with sig/bkg
  RooExtendPdf eexhume("eexhume","extended signal p.d.f",modelExhume,nexhume) ;
  RooExtendPdf eherwig("eherwig","extended background p.d.f",modelHerwig,nherwig) ;
  RooExtendPdf epompyt("epompyt","extended background p.d.f",modelPompyt,npompyt) ;
  RooExtendPdf epomwig("epomwig","extended background p.d.f",modelPomwig,npomwig) ;

  // S u m   e x t e n d e d   c o m p o n e n t s   w i t h o u t   c o e f s
  // -------------------------------------------------------------------------

  // Construct sum of two extended p.d.f. (no coefficients required)
  RooAddPdf  model2("model2","(g1+g2+g3+g4)+a",RooArgList(eherwig,epompyt,epomwig,eexhume)) ;

  RooFitResult* r = model2.fitTo(DataSet,RooFit::Save()) ;
  r->Print("eexhume");
  r->Print("eherwig");
  r->Print("epompyt");
  r->Print("epomwig");
  r->Print("v") ;

  // Print parameters in the plot
  /*
     model2.paramOn(xframeRjj);
     model2.paramOn(xframenTracks);
     model2.paramOn(xframeDeltaEtaPF);
     model2.paramOn(xframeXiPlus);
     model2.paramOn(xframeXiMinus);
   */

  TCanvas *c1 = new TCanvas("c1","multipads1",900,700);
  c1->Divide(2,2);

  TCanvas *c2 = new TCanvas("c2","multipads2",900,700);

  gPad->SetLeftMargin(0.15);
  c1->cd(1);
  xframenTracks->GetYaxis()->SetTitleOffset(1.4) ; xframenTracks->Draw() ;
  c1->cd(2);
  xframeDeltaEtaPF->GetYaxis()->SetTitleOffset(1.4) ; xframeDeltaEtaPF->Draw() ;
  c1->cd(3);
  xframeXiPlus->GetYaxis()->SetTitleOffset(1.4) ;  xframeXiPlus->Draw() ;
  c1->cd(4);
  xframeXiMinus->GetYaxis()->SetTitleOffset(1.4) ;  xframeXiMinus->Draw() ;

  c2->cd();
  xframeRjj->GetYaxis()->SetTitleOffset(
      1.4) ; xframeRjj->Draw() ;
  c2->cd();

  c1->cd(1);
  TLegend *legend = new TLegend(0.7,0.7,0.9,0.9);
  legend->SetTextFont(72);
  legend->SetTextSize(0.05);
  legend->AddEntry("Data","Data","P ");
  legend->AddEntry("Background","Background","L");
  legend->AddEntry("Signal+Background","Signal+Background","L");
  legend->Draw();
  c2->cd();
  legend->Draw();

}


// C O S M E T I C S

void StyleNice(){

  //gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  gStyle->SetPadLeftMargin(0.2);
  gStyle->SetPadBottomMargin(0.2);
  gStyle->SetLegendBorderSize(0);

  gStyle->SetMarkerStyle(20);
  gStyle->SetMarkerSize(1.);

  gStyle->SetTitleSize(0.0845,"X");
  gStyle->SetTitleSize(0.0845,"Y");

  gStyle->SetLabelSize(0.06,"X");
  gStyle->SetLabelSize(0.06,"Y");

  gStyle->SetLabelOffset(0.01,"Y");
  gStyle->SetLabelOffset(0.01,"X");

  gStyle->SetTitleOffset(0.8,"Y");
  gStyle->SetTitleOffset(1.06,"X");

  gStyle->SetLineWidth(3);
  gStyle->SetHistLineWidth(2);

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetTickLength(0.01,"Y");
  gStyle->SetTickLength(0.02,"X");

  gROOT->ForceStyle();

}
