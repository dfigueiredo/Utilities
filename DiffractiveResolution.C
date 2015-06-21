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

void DiffractiveResolution(){

  // Files
  mc_file_muon = "histo_all_signal.root";
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

  // X axis range. If xmin == xmax, no changes.
  xmin = 0.;
  xmax = 1.;

  // Rebin. If rebin <= 0, no changes.
  rebin = 0;

  //MyResolution("Diffraction/xiMinus_single_zeropileup","Generator/genXiMinus_single_zeropileup");
  //MyResolution("Diffraction/xiMinus_single_NGapCASTOR","Generator/genXiMinus_single_NGapCASTOR");
  //MyResolution("Diffraction/xiMinusAll_single_zeropileup","Generator/genXiMinusAll_single_zeropileup");
  MyResolution("Diffraction/xiMinusAll_single_NGapCASTOR","Generator/genXiMinusAll_single_NGapCASTOR");


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

  TH1F* h_gen_muon = (TH1F*)l_muon->Get(hname2);
  //TH1F* h_gen_electron = (TH1F*)l_electron->Get(hname2);

  TList *listreco = new TList;
  listreco->Add(h_reco_muon);
  //listreco->Add(h_reco_electron);

  TList *listgen = new TList;
  listgen->Add(h_gen_muon);
  //listgen->Add(h_gen_electron);

  TH1F *reco = (TH1F*)h_reco_muon->Clone("reco");
  reco->Reset();
  reco->Merge(listreco);

  TH1F *gen = (TH1F*)h_gen_muon->Clone("gen");
  gen->Reset();
  gen->Merge(listgen);

}

void MyResolution(TString hname1, TString hname2){

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

  // ------------>Primitives in pad: pad1 0, 0.4, 1, 1
  TPad *pad1 = new TPad("pad1", "pad1",0,0.266,1,1);
  pad1->Draw();
  pad1->cd();
  pad1->SetLogy();
  pad1->SetLogx();
  //pad1->SetGridx();
  pad1->SetLeftMargin(0.15);
  pad1->SetTopMargin(0.08);
  pad1->SetBottomMargin(0.02);
  pad1->SetRightMargin(0.065);
  pad1->SetFrameFillStyle(0);
  pad1->SetFrameBorderMode(0);
  pad1->SetFrameFillStyle(0);
  pad1->SetFrameBorderMode(0);

  reco->SetDirectory(0);
  reco->SetStats(0);

  TLegend* leg = new TLegend(0.7597956,0.822335,0.9931857,0.9949239,NULL,"brNDC");

  leg->SetFillColor(kWhite);
  leg->SetLineColor(kWhite);

  if(xmin != xmax) reco->GetXaxis()->SetRangeUser(xmin,xmax);
  reco->GetXaxis()->SetNdivisions(506);
  reco->GetXaxis()->SetLabelFont(42);
  reco->GetXaxis()->SetLabelOffset(1000);
  reco->GetXaxis()->SetLabelSize(0);
  reco->GetXaxis()->SetTitleSize(0);
  reco->GetXaxis()->SetTickLength(0.02554496);
  reco->GetXaxis()->SetTitleOffset(1000);
  reco->GetXaxis()->SetTitleFont(42);
  reco->GetYaxis()->SetTitle(titleY.c_str());
  reco->GetYaxis()->SetNdivisions(506);
  reco->GetYaxis()->SetLabelFont(42);
  reco->GetYaxis()->SetLabelOffset(0.011);
  reco->GetYaxis()->SetLabelSize(0.04598093);
  reco->GetYaxis()->SetTitleSize(0.04904632);
  reco->GetYaxis()->SetTickLength(0.02721248);
  reco->GetYaxis()->SetTitleOffset(1.414173);
  reco->GetYaxis()->SetTitleFont(42);
  reco->SetLineColor(kBlack);
  reco->SetLineWidth(2.);
  //reco->SetMinimum(0);
  if(rebin>0) reco->Rebin(rebin);
  reco->Sumw2();

  gen->SetDirectory(0);
  gen->SetLineColor(2);
  gen->SetLineWidth(2);
  gen->GetYaxis()->SetTitleSize(0);
  gen->SetLineColor(kRed);
  if(xmin != xmax) gen->GetXaxis()->SetRangeUser(xmin,xmax);
  gen->GetXaxis()->SetNdivisions(506);
  gen->GetXaxis()->SetLabelFont(42);
  gen->GetXaxis()->SetLabelOffset(1000);
  gen->GetXaxis()->SetLabelSize(0);
  gen->GetXaxis()->SetTitleSize(0);
  gen->GetXaxis()->SetTickLength(0.02554496);
  gen->GetXaxis()->SetTitleOffset(1000);
  gen->GetXaxis()->SetTitleFont(42);
  gen->GetYaxis()->SetTitle(titleY.c_str());
  gen->GetYaxis()->SetNdivisions(506);
  gen->GetYaxis()->SetLabelFont(42);
  gen->GetYaxis()->SetLabelOffset(0.011);
  gen->GetYaxis()->SetLabelSize(0.04598093);
  gen->GetYaxis()->SetTitleSize(0.04904632);
  gen->GetYaxis()->SetTickLength(0.02721248);
  gen->GetYaxis()->SetTitleOffset(1.414173);
  gen->GetYaxis()->SetTitleFont(42);
  gen->SetLineWidth(2.);
  //gen->SetMinimum(0);
  gen->Sumw2();
  if(rebin>0) gen->Rebin(rebin);

  leg->AddEntry(reco,legreco,"LF");
  leg->AddEntry(gen,leggen,"LF");

  c->cd();
  pad1->cd();

  TLatex *   tex = new TLatex(0.94,0.9346049,correction);
  tex->SetNDC();
  tex->SetTextAlign(31);
  tex->SetTextFont(42);
  tex->SetTextSize(0.05);
  tex->SetLineWidth(2);
  tex->Draw();

  tex = new TLatex(0.15,0.98,cmstitle);
  tex->SetNDC();
  tex->SetTextAlign(13);
  tex->SetTextFont(61);
  tex->SetTextSize(0.05);
  tex->SetLineWidth(2);
  tex->Draw();

  gen->Draw("hist");
  reco->Draw("histsame");
  leg->Draw();

  pad1->Modified();
  c->cd();

  // ------------>Primitives in pad: pad2 0,0,1,0.39
  pad2 = new TPad("pad2", "pad2",0,0,1,0.266);
  pad2->Draw();
  pad2->cd();
  pad2->SetLogx();
  pad2->SetFillColor(0);
  pad2->SetBorderMode(0);
  pad2->SetBorderSize(2);
  //pad2->SetGridx();
  pad2->SetLeftMargin(0.15);
  pad2->SetRightMargin(0.065);
  pad2->SetTopMargin(0.03);
  pad2->SetBottomMargin(0.4);
  pad2->SetFrameBorderMode(0);

  TH1F *ratio=(TH1F*)reco->Clone();
  ratio->Divide(gen);
  ratio->SetStats(0);

  ratio->SetMinimum(0.7);
  ratio->SetMaximum(1.3);
  ratio->SetDirectory(0);
  ratio->SetStats(0);
  ratio->SetLineStyle(0);
  ratio->SetMarkerStyle(4);
  ratio->SetMarkerColor(kBlack);
  ratio->SetLineColor(kBlack);
  ratio->GetXaxis()->SetRangeUser(xmin,xmax);
  ratio->GetXaxis()->SetNdivisions(506);
  ratio->GetXaxis()->SetLabelFont(42);
  ratio->GetXaxis()->SetLabelOffset(0.012);
  ratio->GetXaxis()->SetLabelSize(0.1268797);
  ratio->GetXaxis()->SetTitleSize(0.169173);
  ratio->GetXaxis()->SetTickLength(0.07048873);
  ratio->GetXaxis()->SetTitleOffset(0.935);
  ratio->GetXaxis()->SetTitleFont(42);
  ratio->GetYaxis()->SetTitle("A_{i}");
  ratio->GetYaxis()->CenterTitle(true);
  ratio->GetYaxis()->SetNdivisions(504);
  ratio->GetYaxis()->SetLabelFont(42);
  ratio->GetYaxis()->SetLabelOffset(0.011);
  ratio->GetYaxis()->SetLabelSize(0.1268797);
  ratio->GetYaxis()->SetTitleSize(0.1353384);
  ratio->GetYaxis()->SetTickLength(0.03972916);
  ratio->GetYaxis()->SetTitleOffset(0.5124933);
  ratio->GetYaxis()->SetTitleFont(42);
  ratio->Draw("ep");

  pad2->Modified();
  c->cd();
  c->Modified();
  c->cd();
  c->SetSelected(c);

  pad1->SetTickx(1);
  pad1->SetTicky(1);
  pad2->SetTickx(1);
  pad2->SetTicky(1);

  pad2->RedrawAxis();
  pad1->RedrawAxis();

}



