/*

   >> P R O G R A M   E F F I C I E N C Y   P L O T T E R
   --------------------------------------------------------
GOAL: Create histograms
PROJECT: Diffractive Z/W boson analysis


>> H O W   T O   E X E C U T E :
--------------------------------
> root -l TriggerEfficiencyPlot.C

 */

#include "iostream.h"
#include "fstream.h"
#include "TCanvas.h"
#include "TAxis.h"

TString legdata, cmstitle, titleup;
std::string input_file;
std::string titleY, titleYsigma;
std::string outputinfo;
double xmin, xmax;
int rebin;

void TriggerEfficiencyPlot(){

  // Files
  input_file = "histo_trigger_eff_muonp2.root";
  //input_file = "histo_trigger_eff_muonp3.root";
  //input_file = "histo_trigger_eff_electron.root";
  //input_file = "histo_HLTMu9_eff_zerobiasB.root";
  //input_file = "histo_HLTMu15_eff_zerobiasB.root";
  //input_file = "histo_HLTEle17_eff_zerobiasB.root";

  bool translate = false;

  if(translate){
    legdata = "Dados";
    titleY = "Eventos";
    cmstitle = "CMS Preliminar";
    titleup ="W, Todos os canais (7 TeV)";
    titleYsigma = "Assimetria";
  }else{
    legdata = "Data";
    titleY = "Events";
    cmstitle = "CMS Preliminary";
    titleup ="W, all channels (7 TeV)";
    titleYsigma = "Asymmetry";
  }

  // X axis range. If xmin == xmax, no changes.
  xmin = 0;
  xmax = 100;

  // Rebin. If rebin <= 0, no changes.
  rebin = 0;

  Plot();

}

void Plot(){

  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  TFile *file  = TFile::Open(input_file.c_str());


  // leading_lepton_pt, second_lepton_pt, dilepton_mass
  TH1F *hRefTrigger = (TH1F*)file->Get("leading_lepton_pt_with_Presel_JPsi"); //leading_lepton_pt_with_Presel_JPsi_Tigher, with_Presel_JPsi
  TH1F *hTrigger = (TH1F*)file->Get("leading_lepton_pt_with_Trigger"); // leading_lepton_pt_with_Trigger_Tigher, with_Trigger



  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  float canv_X =  10;
  float canv_Y =  10;
  float canv_W =  700;
  float canv_H =  1000;

  int ci = TColor::GetColor("#ccccff");
  int histFillColor = ci;
  int histLineColor = kBlue+1;

  int histLineWidth = 1;
  float markerSize_ = 0.85;

  TCanvas *c = new TCanvas("c2", "canvas2",canv_X,canv_Y,canv_W,canv_H);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetFrameBorderMode(0);
  c->SetFrameFillStyle(0);
  c->Draw();

  c->cd();

  hTrigger->Divide(hRefTrigger);

  hTrigger->SetMarkerStyle(20);
  hTrigger->SetMarkerSize(markerSize_);
  hTrigger->GetYaxis()->CenterTitle();
/*
  hTrigger->GetXaxis()->SetLabelFont(42);
  hTrigger->GetXaxis()->SetLabelOffset(0.009);
  hTrigger->GetXaxis()->SetLabelSize(0.03);
  hTrigger->GetXaxis()->SetTitleSize(0.055);
  hTrigger->GetXaxis()->SetTickLength(0.02554496);
  hTrigger->GetXaxis()->SetTitleOffset(0.6);
*/

  c->Update();
  hTrigger->Draw("P");
  gPad->RedrawAxis();

}
