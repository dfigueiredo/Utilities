/*

   >> P R O G R A M   D I F F R A C T I V E   P L O T T E R
   --------------------------------------------------------
GOAL: Create histograms
PROJECT: Diffractive Z/W boson analysis


>> H O W   T O   E X E C U T E :
--------------------------------
> root -l DiffractiveBosonPlotter.C


>> A N A L Y S I S   C U T S
----------------------------

FOR W:

"step2" --> single vertex
"step3" --> pt lepton && pt met
"step4" --> no cosmic (only for muons)
"step5" --> isolation and barrel cuts (only for electrons)
"step6" --> only one lepton (muon or electron)
"step7" --> transvese mass cut

FOR Z:

"step2" --> single vertex
"step3" --> pt leptons
"step4" --> at least two leptons
"step5" --> charge invariance
"step6" --> dilepton mass
"step7" --> isolation
"step8" --> barrel cuts (only for electrons)

COMMON CUTS:

"without_cuts" --> No cuts
"with_trigger" --> Trigger
"NGapCMS" --> HF Minus gap or etamax/min gap
"PGapCMS" --> HF Plus gap or etamax/min gap
"NGapCMSAndCASTOR" --> HF Minus gap and CASTOR gap
"PGapCMSAndCastorActivity" --> HF Plus gap & CASTOR active
"NGapCMSAndWKinP" --> HF Minus gap & W going to CMS Plus
"PGapCMSAndWKinN" --> HF Plus gap & W going to CMS Minus
"NGapCMSAndCASTORAndWKinP" --> HF Minus gap & CASTOR gap & W going to CMS Plus
"PGapCMSAndCastorActivityAndWKinN" --> HF Plus gap & CASTOR active & W going to CMS Minus
"NGapCASTOR" --> CASTOR gap
"NGapCASTORAndWKinP" --> CASTOR gap & W going to CMS Plus
"PGapCMSAndCASTOR" --> HF Plus gap & CASTOR gap
"PGapCMSAndCASTORAndWKinP" --> HF Plus gap & CASTOR gap and W going to CMS Plus

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
#include <vector>

using namespace RooFit;

TString legres, leggen, cmstitle, correction;
std::string mc_file, mc_file_electron;
std::string titleY;
double xmin, xmax;
int rebin;

void DiffractiveFitConstant(){

  // Files
  mc_file = "histo_all_signal.root";
  //mc_file = "histo_WtoMuNu_Reco_pu_P2.root";
  //mc_file_electron = "histo_PomwigMinus_electron_Reco_P2.root";

  bool translate = false;

  if(translate){
    legres = "Monte Carlo";
    titleY = "Eventos";
    cmstitle = "CMS Preliminar";
    correction ="";
  }else{
    legres = "Monte Carlo";
    titleY = "Events";
    cmstitle = "CMS Preliminary";
    correction ="";
  }

  // X axis range. If xmin == xmax, no changes.
  xmin = -5.;
  xmax = 5.;

  // Rebin. If rebin <= 0, no changes.
  rebin = 0;
  
  //MyResolution("Generator/ratioXiMinus_single_zeropileup");
  //MyResolution("Generator/ratioXiMinus_single_NGapCASTOR");
  MyResolution("Generator/ratioXiMinusMore_single_zeropileup");
    
}

// C M S   O F F I C I A L   S T Y L E
//------------------------------------

void loadFiles(TString hname1){

  //gStyle->SetOptFit(0);
  gStyle->SetOptStat(111);
  gStyle->SetOptTitle(0);

  TFile *l_file  = TFile::Open(mc_file.c_str());
  //TFile *l_electron  = TFile::Open(mc_file_electron.c_str());

  TH1F* h_resolution = (TH1F*)l_file->Get(hname1);
  //TH1F* h_res_electron = (TH1F*)l_electron->Get(hname1);

  TList *listres = new TList;
  listres->Add(h_resolution);
  //listres->Add(h_res_electron);

  TH1F *res = (TH1F*)h_resolution->Clone("res");
  res->Reset();
  res->Merge(listres);

}

void MyResolution(TString hname1){

  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  loadFiles(hname1);

  float canv_X =  10;
  float canv_Y =  10;
  float canv_W =  700;
  float canv_H =  1000;

  TCanvas *c = new TCanvas("c", "canvas",canv_X,canv_Y,canv_W,canv_H);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetFrameBorderMode(0);
  c->SetFrameFillStyle(0);
  c->Draw();

  res->SetDirectory(0);
  //res->SetStats(0);

  TLegend* leg = new TLegend(0.7597956,0.822335,0.9931857,0.9949239,NULL,"brNDC");

  leg->SetFillColor(kWhite);
  leg->SetLineColor(kWhite);

  if(xmin != xmax) res->GetXaxis()->SetRangeUser(xmin,xmax);
  res->GetXaxis()->SetNdivisions(506);
  res->GetXaxis()->SetLabelFont(42);
  res->GetXaxis()->SetTickLength(0.025);
  res->GetXaxis()->SetTitleFont(42);
  res->GetYaxis()->SetTitle(titleY.c_str());
  res->GetYaxis()->SetNdivisions(506);
  res->GetYaxis()->SetLabelFont(42);
  res->GetYaxis()->SetLabelOffset(0.011);
  res->GetXaxis()->SetLabelSize(0.03);
  res->GetXaxis()->SetTitleSize(0.04);
  res->GetYaxis()->SetLabelSize(0.03);
  res->GetYaxis()->SetTitleSize(0.04);
  res->GetYaxis()->SetTickLength(0.025);
  res->GetXaxis()->SetTitleOffset(1.2);
  res->GetYaxis()->SetTitleOffset(1.2);
  res->GetYaxis()->SetTitleFont(42);
  res->SetLineColor(kBlack);
  res->SetMarkerStyle(4);
  res->SetLineWidth(2.);
  res->SetMinimum(0);
  if(rebin>0) res->Rebin(rebin);
  res->Sumw2();

  leg->AddEntry(res,legres,"P");

  c->cd();

  TLatex *   tex = new TLatex(0.94,0.9346049,correction);
  tex->SetNDC();
  tex->SetTextAlign(31);
  tex->SetTextFont(42);
  tex->SetTextSize(0.05);
  tex->SetLineWidth(2);
  tex->Draw();

  res->Draw("E1");
  leg->Draw();

  c->cd();

  c->cd();
  c->Modified();
  c->cd();
  c->SetSelected(c);

}



