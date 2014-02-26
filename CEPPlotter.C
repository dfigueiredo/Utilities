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
  //----------------------
  
  //MakePlotRatio("RJJ_no_multiple_pileup_step4_4","RJJ_multiple_pileup_0_step4_4","noauto","nowidth","","norebin","ratio","all"); //always 0!
  //MakePlotRatio("RJJ_no_multiple_pileup_step4_2","RJJ_multiple_pileup_0_step4_2","noauto","nowidth","","norebin","noratio","all"); //always 0!
  //MakePlotRatio("RJJ_no_multiple_pileup_step4_2_CASTOR","RJJ_multiple_pileup_0_step4_2_CASTOR","noauto","nowidth","","norebin","noratio","all");//always 0!
  //MakePlotRatio("deltaEtamaxminPF_no_multiple_pileup_step4_4","deltaEtamaxminPF_multiple_pileup_0_step4_4","noauto","nowidth","","norebin","ratio","all"); //always 0!
  //MakePlotRatio("deltaEtamaxminPF_no_multiple_pileup_step4_2","deltaEtamaxminPF_multiple_pileup_0_step4_2","noauto","nowidth","","norebin","noratio","all"); //always 0!
  //MakePlotRatio("deltaEtamaxminPF_no_multiple_pileup_step4_2_CASTOR","deltaEtamaxminPF_multiple_pileup_0_step4_2_CASTOR","noauto","nowidth","","norebin","noratio","all"); //always 0!
  //MakePlotRatio("xiPF_no_multiple_pileup_step4_2_CASTOR","xiPF_multiple_pileup_0_step4_2_CASTOR","noauto","nowidth","","norebin","noratio","all"); //always 0!

  //Kinematics
  //----------
  
  //MakePlotRatio("etaJet1_no_multiple_pileup_step3","etaJet1_multiple_pileup_0_step3","noauto","nowidth","","norebin","ratio","all"); //always 0!
  //MakePlotRatio("etaJet1_no_multiple_pileup_step4_4","etaJet1_multiple_pileup_0_step4_4","noauto","nowidth","","norebin","ratio","all"); //always 0!
  //MakePlotRatio("etaJet1_pileup_step4_2","etaJet1_multiple_pileup_0_step4_2","noauto","nowidth","","norebin","ratio","all"); //always 0!
  //MakePlotRatio("etaJet1_no_multiple_pileup_step4_2_CASTOR","etaJet1_multiple_pileup_0_step4_2_CASTOR","noauto","nowidth","","norebin","ratio","all"); //always 0!
  //MakePlotRatio("etaJet2_no_multiple_pileup_step4_4","etaJet2_multiple_pileup_0_step4_4","noauto","nowidth","","norebin","ratio","all"); //always 0!
  //MakePlotRatio("etaJet2_pileup_step4_2","etaJet2_multiple_pileup_0_step4_2","noauto","nowidth","","norebin","ratio","all"); //always 0!
  //MakePlotRatio("etaJet2_no_multiple_pileup_step4_2_CASTOR","etaJet2_multiple_pileup_0_step4_2_CASTOR","noauto","nowidth","","norebin","ratio","all"); //always 0!
  //MakePlotRatio("pTJet1_no_multiple_pileup_step4_4","pTJet1_multiple_pileup_0_step4_4","noauto","nowidth","","norebin","ratio","all"); //always 0!
  //MakePlotRatio("pTJet1_no_multiple_pileup_step4_4","pTJet1_no_multiple_pileup_step4_4","noauto","nowidth","","norebin","noratio","all"); //always 0!
  //MakePlotRatio("pTJet1_pileup_step4_2","pTJet1_multiple_pileup_0_step4_2","noauto","nowidth","","norebin","ratio","all"); //always 0!
  //MakePlotRatio("pTJet1_no_multiple_pileup_step4_2_CASTOR","pTJet1_multiple_pileup_0_step4_2_CASTOR","noauto","nowidth","","norebin","ratio","all"); //always 0!
  //MakePlotRatio("pTJet2_no_multiple_pileup_step4_4","pTJet2_multiple_pileup_0_step4_4","noauto","nowidth","","norebin","ratio","all"); //always 0!
  //MakePlotRatio("pTJet2_pileup_step4_2","pTJet2_multiple_pileup_0_step4_2","noauto","nowidth","","norebin","ratio","all"); //always 0!
  //MakePlotRatio("pTJet2_no_multiple_pileup_step4_2_CASTOR","pTJet2_multiple_pileup_0_step4_2_CASTOR","noauto","nowidth","","norebin","ratio","all"); //always 0!
  //MakePlotRatio("deltaPtJets_no_multiple_pileup_step4_4","deltaPtJets_multiple_pileup_0_step4_4","noauto","nowidth","","norebin","ratio","all"); //always 0!
  //MakePlotRatio("deltaPtJets_pileup_step4_2","deltaPtJets_multiple_pileup_0_step4_2","noauto","nowidth","","norebin","ratio","all"); //always 0!
  //MakePlotRatio("deltaPtJets_no_multiple_pileup_step4_2_CASTOR","deltaPtJets_multiple_pileup_0_step4_2_CASTOR","noauto","nowidth","","norebin","ratio","all"); //always 0!
  //MakePlotRatio("deltaPhiJets_no_multiple_pileup_step4_4","deltaPhiJets_multiple_pileup_0_step4_4","noauto","nowidth","","norebin","ratio","all"); //always 0!
  //MakePlotRatio("deltaPhiJets_pileup_step4_2","deltaPhiJets_multiple_pileup_0_step4_2","noauto","nowidth","","norebin","ratio","all"); //always 0!
  //MakePlotRatio("deltaPhiJets_no_multiple_pileup_step4_2_CASTOR","deltaPhiJets_multiple_pileup_0_step4_2_CASTOR","noauto","nowidth","","norebin","ratio","all"); //always 0!
  //MakePlotRatio("deltaEtaJets_no_multiple_pileup_step4_4","deltaEtaJets_multiple_pileup_0_step4_4","noauto","nowidth","","norebin","ratio","all"); //always 0!
  //MakePlotRatio("deltaEtaJets_pileup_step4_2","deltaEtaJets_multiple_pileup_0_step4_2","noauto","nowidth","","norebin","ratio","all"); //always 0!
  //MakePlotRatio("deltaEtaJets_no_multiple_pileup_step4_2_CASTOR","deltaEtaJets_multiple_pileup_0_step4_2_CASTOR","noauto","nowidth","","norebin","ratio","all"); //always 0!


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

void MakePlotRatio(TString name1, TString name2, TString AutoNorma, TString diff, TString ytitle, TString rebinopt, TString mode, TString SumHisto){

  TLegend* leg = new TLegend(0.7597956,0.822335,0.9931857,0.9949239,NULL,"brNDC");
  TString legdata, legpompyt, legexhume, legpomwig, legherwig, legboth;


  leg->SetFillColor(kWhite);

  TFile *data = TFile::Open("nonehisto_multijet_HLTExclDiJet30U_AND_HFPreSel_GoodVertex_triggerRefDijet50And30_68mb_24bin_pT60_60.root");
  TFile *data_up = TFile::Open("plushisto_multijet_HLTExclDiJet30U_AND_HFPreSel_GoodVertex_triggerRefDijet50And30_68mb_24bin_pT60_60.root");
  TFile *data_down = TFile::Open("minushisto_multijet_HLTExclDiJet30U_AND_HFPreSel_GoodVertex_triggerRefDijet50And30_68mb_24bin_pT60_60.root");
  TFile *data_trigger_eff = TFile::Open("nonehisto_multijet_HLTExclDiJet30U_AND_HFPreSel_GoodVertex_triggerRefDijet50And30_triggercorr_effcorr_68mb_24bin_pT60_60.root");
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
  TH1F* h_1_up = (TH1F*)data_up->Get(name1);
  TH1F* h_1_down = (TH1F*)data_down->Get(name1);

  h_1->Sumw2();
  h_1_trigger_eff->Sumw2();
  h_2->Sumw2();
  h_3->Sumw2();
  h_4->Sumw2();
  h_5->Sumw2();

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
      h_2->SetBinContent(i,0);
      h_2->SetBinError(i,0);
      h_3->SetBinContent(i,0);
      h_3->SetBinError(i,0);
      h_4->SetBinContent(i,0);
      h_4->SetBinError(i,0);
      h_5->SetBinContent(i,0);
      h_5->SetBinError(i,0);
    }
  }

  // Survival Probability 5%  
  h_2->Scale(0.05);
  h_4->Scale(0.05);

  if(diff == "width" || diff == "WIDTH"){
    double lumi = 0.04587;
    h_1->Scale(lumi,"width");
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

  TList *listAll = new TList;
  listAll->Add(h_2);
  listAll->Add(h_3);
  listAll->Add(h_4);
  listAll->Add(h_5);

  TH1F *MCtogether = (TH1F*)h_5->Clone("MCtogether");
  MCtogether->Reset();
  MCtogether->SetLineColor(kOrange);
  MCtogether->Merge(listAll);

  if(rebinopt == "rebin"){
    h_1->Rebin(4);
    h_2->Rebin(4);
    h_3->Rebin(4);
    h_4->Rebin(4);
    h_5->Rebin(4);
  }

  leg->AddEntry(h_1,legdata,"ep");
  leg->AddEntry(h_2,legpompyt,"LFP");
  leg->AddEntry(h_3,legexhume,"LFP");
  leg->AddEntry(h_4,legpomwig,"LFP");
  leg->AddEntry(h_5,legherwig,"LFP");

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
  format_h(dividend2,kBlue-4);
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

  int NBins = h_1_trigger_eff->GetNbinsX();
  const int n = NBins;

  double x[n];
  double y[n];
  double exl[n];
  double eyl[n];
  double exh[n];
  double eyh[n];

  for (int i=0; i<n; i++){
    if(h_1_trigger_eff->GetBinContent(i+1)>0){
      double BinWidth = h_1->GetXaxis()->GetBinWidth(i);
      x[i] = h_1->GetXaxis()->GetBinCenter(i+1);
      y[i] = h_1->GetBinContent(i+1);
      exl[i] = BinWidth/2;
      exh[i] = BinWidth/2;
      eyh[i] = fabs(h_1_up->GetBinContent(i+1)-h_1->GetBinContent(i+1));
      eyl[i] = fabs(h_1->GetBinContent(i+1)-h_1_down->GetBinContent(i+1));
    }else{
      x[i] = 0.;
      y[i] = 0.;
      exl[i] = 0.;
      exh[i] = 0.;
      eyh[i] = 0.;
      eyl[i] = 0.;
    }
  }

  gr = new TGraphAsymmErrors(NBins,x,y,exl,exh,eyl,eyh);
  gr->SetMarkerStyle(20);
  gr->GetYaxis()->SetTitle("N Events");
  gr->GetXaxis()->SetTitle(h_1->GetXaxis()->GetTitle());
  gr->SetFillColor(5);

  if (SumHisto=="all" || SumHisto == "ALL"){
    MCtogether->SetFillStyle(0);
    MCtogether->SetLineWidth(4);
    MCtogether->SetLineColor(32);
    leg->AddEntry(MCtogether,legboth,"LFP");
    if(rebinopt == "rebin"){
      MCtogether->Rebin(4);
    }
    MCtogether->Draw("Hist");
  }
  gr->Draw("APE2");
  h_5->Draw("HistSame");
  h_4->Draw("HistSame");
  h_3->Draw("HistSame");
  h_2->Draw("HistSame");
  h_1->Draw("psame");
  leg->Draw("HistSame");

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



