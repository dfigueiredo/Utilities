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

TString legreco, leggen, cmstitle, correction;
std::string mc_file_muon, mc_file_electron;
std::string titleY;
double xmin, xmax;
int rebin;

void DiffractiveCorrelation(){

  // Files
  mc_file_muon = "histo_PomwigMinus_muonP2_Reco.root";
  //mc_file_muon = "histo_WtoMuNu_Reco_pu_P2.root";
  //mc_file_electron = "histo_PomwigMinus_electron_Reco_P2.root";

  bool translate = false;

  if(translate){
    legreco = "reco";
    leggen = "gen";
    titleY = "Eventos";
    cmstitle = "CMS Preliminar";
    correction ="";
  }else{
    legreco = "reco";
    leggen = "gen";
    titleY = "Events";
    cmstitle = "CMS Preliminary";
    correction ="";
  }

  // Rebin. If rebin <= 0, no changes.
  rebin = 2;

  MyCorrelation("Generator/correlXiMinus_single_NGapCASTOR","Generator/correlXiMinus_single_NGapCASTOR");


}

// C M S   O F F I C I A L   S T Y L E
//------------------------------------

void loadFiles(TString hname1, TString hname2){

  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  TFile *l_muon  = TFile::Open(mc_file_muon.c_str());
  //TFile *l_electron  = TFile::Open(mc_file_electron.c_str());

  TH1F* h_reco_muon = (TH1F*)l_muon->Get(hname1);
  //TH1F* h_reco_electron = (TH1F*)l_electron->Get(hname1);

  TList *listreco = new TList;
  listreco->Add(h_reco_muon);
  //listreco->Add(h_reco_electron);

  TH2F *reco = (TH2F*)h_reco_muon->Clone("reco");
  reco->Reset();
  reco->Merge(listreco);

}

void MyCorrelation(TString hname1, TString hname2){

  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  loadFiles(hname1, hname2);

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

  reco->SetDirectory(0);
  reco->SetStats(0);

  TLegend* leg = new TLegend(0.7597956,0.822335,0.9931857,0.9949239,NULL,"brNDC");

  leg->SetFillColor(kWhite);
  leg->SetLineColor(kWhite);

  if(xmin != xmax) reco->GetXaxis()->SetRangeUser(xmin,xmax);
    reco->GetXaxis()->SetNdivisions(506);
    reco->GetXaxis()->SetLabelFont(42);
    reco->GetXaxis()->SetTickLength(0.02554496);
    reco->GetXaxis()->SetLabelSize(0.04598093);
    reco->GetXaxis()->SetTitleSize(0.04);
    reco->GetXaxis()->SetTitleFont(42);
    reco->GetXaxis()->SetTitleOffset(1.2);
    reco->GetYaxis()->SetNdivisions(506);
    reco->GetYaxis()->SetLabelFont(42);
    reco->GetYaxis()->SetLabelOffset(0.011);
    reco->GetYaxis()->SetLabelSize(0.04598093);
    reco->GetYaxis()->SetTitleSize(0.04);
    reco->GetYaxis()->SetTickLength(0.02721248);
    reco->GetYaxis()->SetTitleFont(42);
   
  //reco->SetMinimum(0);
  if(rebin>0){
    reco->RebinX(rebin);
    reco->RebinY(rebin);
  }
  gPad->SetLogz();
  reco->GetZaxis()->SetLabelSize(0.03);
  reco->Sumw2();

  //leg->AddEntry(reco,legreco,"LF");

  c->cd();

  TLine *line = new TLine(-4,-4,0,0);
  line->SetLineColor(kRed);

  line->SetLineStyle(2);
  line->SetLineColor(kBlack);
  line->SetLineWidth(2.);
  reco->Draw("cont1colz");
  line->Draw("same");
  //leg->Draw();

   //TPaletteAxis *p = (TPaletteAxis*)reco->GetListOfFunctions()->FindObject("palette");
   //c->Update();

  TLatex *   tex = new TLatex(0.94,0.9346049,correction);
  tex->SetNDC();
  tex->SetTextAlign(31);
  tex->SetTextFont(42);
  tex->SetTextSize(0.05);
  tex->SetLineWidth(2);
  tex->Draw();

  tex = new TLatex(0.1,0.95,cmstitle);
  tex->SetNDC();
  tex->SetTextAlign(13);
  tex->SetTextFont(61);
  tex->SetTextSize(0.05);
  tex->SetLineWidth(2);
  tex->Draw();

  c->cd();

  c->cd();
  c->Modified();
  c->cd();
  c->SetSelected(c);

}



