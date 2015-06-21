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

TString legdata, legmcbkg, legmcall, cmstitle, luminosity;
char legmcsignal[300];
std::string datafile_z_muon, datafile_z_electron;
std::string mcfile_z_muon_bkg, mcfile_z_electron_bkg;
std::string mcfile_z_muon_signal, mcfile_z_electron_signal;
std::string titleY, titleYsigma;
std::string outputinfo;
double xmin, xmax;
int rebin;
bool makeXS, sigma;

double lumi_z_muon;
double lumi_z_electron;
double lumi_z_muon;
double lumi_z_electron;
double accep_muon;
double accep_electron;
double surv;

void DiffractiveCrossSectionZ(){

  // Files
  datafile_z_muon = "histo_Z_muon_reco.root";
  datafile_z_electron = "histo_Z_electron_reco.root";

  mcfile_z_muon_bkg = "histo_Z_bkg_muon_reco.root";
  mcfile_z_electron_bkg = "histo_Z_bkg_electron_reco.root";

  mcfile_z_muon_signal = "histo_Z_signal_muon_reco.root";
  mcfile_z_electron_signal = "histo_Z_signal_electron_reco.root";

  outputinfo="NumberOfEvents.txt";

  // Survival Pomwig
  surv = 0.17;
  //surv = 1.;

  // Legend
  legmcbkg = "PYTHIA6";
  sprintf(legmcsignal,"POMWIG,  #LT |S^{#scale[0.9]{2}}| #GT = %.2f",surv);
  legmcall = "PYTHIA6 + POMWIG";

  bool translate = false;

  if(translate){
    legdata = "Dados";
    titleY = "Eventos";
    cmstitle = "CMS Preliminar";
    luminosity ="W, Todos os canais (7 TeV)";
    titleYsigma = "Assimetria";
  }else{
    legdata = "Data";
    titleY = "Events";
    cmstitle = "CMS Preliminary";
    luminosity ="W, all channels (7 TeV)";
    titleYsigma = "Asymmetry";
  }

  // Luminosity
  lumi_z_muon = 25.216;
  lumi_z_electron = 24.229;

  // Acceptance
  accep_muon = 1.;
  accep_electron = 1.;  

  // Make Cross Section
  makeXS = false;

  // Make Sigma Plots
  sigma = false;

  // X axis range. If xmin == xmax, no changes.
  xmin = -5;
  xmax = 5;

  // Rebin. If rebin <= 0, no changes.
  rebin = 0;

  // hname_W, hname_Z
  //MyOfficialCMS("BosonKinematics/BosonWMass_single_step7");
  //MyOfficialCMS("BosonKinematics/BosonWEta_single_step7");
  //MyOfficialCMS("BosonKinematics/BosonWEta_single_NGapCMS");
  //MyOfficialCMS("BosonKinematics/BosonWEta_single_NGapCASTOR");
  //MyOfficialCMS("BosonKinematics/BosonWEta_single_NGapCMSAndCASTOR");
  //MyOfficialCMS("BosonKinematics/BosonWEta_single_PGapCMSAndCASTOR");
  //MyOfficialCMS("Detector/CastorMultiplicity_single_step7");
  //MyOfficialCMS("Detector/CastorMultiplicity_single_without_cuts");
  //MyOfficialCMS("Detector/EnergyVsEtaBin1D_single_step7");
  //MyOfficialCMS("Detector/sumECastorAndSumHFMinus_single_step7");
  //MyOfficialCMS("Detector/minusNHF_single_step7");
  //MyOfficialCMS("Detector/plusNHF_single_step7");
  //MyOfficialCMS("Detector/sumEEEminus_single_step7");
  //MyOfficialCMS("Detector/sumEHFplus_single_step7");
  //MyOfficialCMS("Detector/sumEHFplusPF_single_step7");
  //MyOfficialCMS("Detector/sumEHFplus_S_single_step7");  
  //MyOfficialCMS("Detector/sumEHFplus_L_single_step7");
  //MyOfficialCMS("Detector/sumEHFminus_single_step7");
  //MyOfficialCMS("Detector/sumEHFminusPF_single_step7");
  //MyOfficialCMS("Detector/sumEHFminus_S_single_step7");
  //MyOfficialCMS("Detector/sumEHFminus_L_single_step7");
  //MyOfficialCMS("Detector/sumECastorMinus_single_step7");
  //MyOfficialCMS("Detector/sumEHFMax_single_step7");
  //MyOfficialCMS("Detector/sumEHFMin_single_step7");
  //MyOfficialCMS("Detector/sumEHEminus_single_step7");
  //MyOfficialCMS("Detector/sumEHEplus_single_step7");
  //MyOfficialCMS("Detector/sumECastorAndSumHFMinus_single_step7");
  //MyOfficialCMS("Run/TracksMultiplicity_single_step7");
  //MyOfficialCMS("Run/vertex_single_step7");
  //MyOfficialCMS("Diffraction/deltaEtamaxmin_single_step7");
  //MyOfficialCMS("Diffraction/AEcastor_single_step7");
  //MyOfficialCMS("Diffraction/etaminimum_single_NGapCASTOR");
  //MyOfficialCMS("Diffraction/etasignedHF_single_step7");
  //MyOfficialCMS("Diffraction/etasignedCASTOR_single_step7");
  //MyOfficialCMS("Diffraction/xiMinus_single_step7");
  MyOfficialCMS("Diffraction/xiMinusAll_single_step7");
  //MyOfficialCMS("Diffraction/xiPlus_single_step7");
  //MyOfficialCMS("Diffraction/SumPTMingap_single_step7");
  //MyOfficialCMS("Diffraction/SumPTMaxgap_single_step7");
  //MyOfficialCMS("Diffraction/maxetagap_single_NGapCASTOR");
  //MyOfficialCMS("Diffraction/etamin_single_NGapCASTOR");
  //MyOfficialCMS("Diffraction/etamax_single_NGapCASTOR");
  //MyOfficialCMS("Diffraction/mHF_single_step7");

}

// C M S   O F F I C I A L   S T Y L E
//------------------------------------

void loadFiles(TString hname_w){

  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  TFile *ldata_z_muon  = TFile::Open(datafile_z_muon.c_str());
  TFile *ldata_z_electron  = TFile::Open(datafile_z_electron.c_str());

  TFile *lmc_z_muon_bkg  = TFile::Open(mcfile_z_muon_bkg.c_str());
  TFile *lmc_z_electron_bkg  = TFile::Open(mcfile_z_electron_bkg.c_str());

  TFile *lmc_z_muon_signal  = TFile::Open(mcfile_z_muon_signal.c_str());
  TFile *lmc_z_electron_signal  = TFile::Open(mcfile_z_electron_signal.c_str());

  TH1F* h_data_z_muon = (TH1F*)ldata_z_muon->Get(hname_w);
  TH1F* h_data_z_electron = (TH1F*)ldata_z_electron->Get(hname_w);

  TH1F* h_mc_z_muon_bkg = (TH1F*)lmc_z_muon_bkg->Get(hname_w);
  TH1F* h_mc_z_electron_bkg = (TH1F*)lmc_z_electron_bkg->Get(hname_w);

  TH1F* h_mc_z_muon_signal = (TH1F*)lmc_z_muon_signal->Get(hname_w);
  TH1F* h_mc_z_electron_signal = (TH1F*)lmc_z_electron_signal->Get(hname_w);

  if(surv>0.){
    h_mc_z_muon_signal->Scale(surv);
    h_mc_z_electron_signal->Scale(surv);
  }

  if(makeXS){
    //Divide per Luminosity and Bin Size
    h_data_z_muon->Scale(1./lumi_z_muon,"width");
    h_data_z_electron->Scale(1./lumi_z_electron,"width");

    h_mc_z_muon_bkg->Scale(1./lumi_z_muon,"width");
    h_mc_z_electron_bkg->Scale(1./lumi_z_electron,"width");

    h_mc_z_muon_signal->Scale(1./lumi_z_muon,"width");
    h_mc_z_electron_signal->Scale(1./lumi_z_electron,"width");
  }

  // All histograms data
  TList *listdata = new TList;
  listdata->Add(h_data_z_muon);
  listdata->Add(h_data_z_electron);

  // All histograms bkg
  TList *listmcbkg = new TList;
  listmcbkg->Add(h_mc_z_muon_bkg);
  listmcbkg->Add(h_mc_z_electron_bkg);

  // All histograms signal
  TList *listmcsignal = new TList;
  listmcsignal->Add(h_mc_z_muon_signal);
  listmcsignal->Add(h_mc_z_electron_signal);

  // All histograms signal + bkg
  TList *listmcall = new TList;
  listmcall->Add(h_mc_z_muon_signal);
  listmcall->Add(h_mc_z_electron_signal);
  listmcall->Add(h_mc_z_muon_bkg);
  listmcall->Add(h_mc_z_electron_bkg);

  TH1F *data = (TH1F*)h_data_z_muon->Clone("data");
  data->Reset();
  data->Merge(listdata);

  TH1F *bkg = (TH1F*)h_mc_z_muon_bkg->Clone("bkg");
  bkg->Reset();
  bkg->Merge(listmcbkg);

  TH1F *signal = (TH1F*)h_mc_z_muon_signal->Clone("signal");
  signal->Reset();
  signal->Merge(listmcsignal);

  TH1F *allmc = (TH1F*)h_mc_z_muon_bkg->Clone("allmc");
  allmc->Reset();
  allmc->Merge(listmcall);

}

void MyOfficialCMS(TString hname_w){

  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  loadFiles(hname_w);

  float canv_X =  10;
  float canv_Y =  10;
  float canv_W =  700;
  float canv_H =  1000;

  int ci = TColor::GetColor("#ccccff");
  int histFillColor = ci;
  int histLineColor = kBlue+1;

  int histLineWidth = 1;
  float markerSize_ = 0.85;

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
  //pad1->SetGridx();
  pad1->SetLeftMargin(0.15);
  pad1->SetTopMargin(0.08);
  pad1->SetBottomMargin(0.02);
  pad1->SetRightMargin(0.065);
  pad1->SetFrameFillStyle(0);
  pad1->SetFrameBorderMode(0);
  pad1->SetFrameFillStyle(0);
  pad1->SetFrameBorderMode(0);

  data->SetDirectory(0);
  data->SetStats(0);

  Int_t ci;      // for color index setting
  TColor *color; // for color definition with alpha
  ci = TColor::GetColor("#0000cc");

  TLegend* leg = new TLegend(0.7597956,0.822335,0.9931857,0.9949239,NULL,"brNDC");

  leg->SetFillColor(kWhite);
  leg->SetLineColor(kWhite);

  data->SetLineColor(ci);
  data->SetLineWidth(2);
  if(xmin != xmax) data->GetXaxis()->SetRangeUser(xmin,xmax);
  data->GetXaxis()->SetNdivisions(506);
  data->GetXaxis()->SetLabelFont(42);
  data->GetXaxis()->SetLabelOffset(1000);
  data->GetXaxis()->SetLabelSize(0);
  data->GetXaxis()->SetTitleSize(0);
  data->GetXaxis()->SetTickLength(0.02554496);
  data->GetXaxis()->SetTitleOffset(1000);
  data->GetXaxis()->SetTitleFont(42);
  data->GetYaxis()->SetTitle(titleY.c_str());
  data->GetYaxis()->SetNdivisions(506);
  data->GetYaxis()->SetLabelFont(42);
  data->GetYaxis()->SetLabelOffset(0.011);
  data->GetYaxis()->SetLabelSize(0.04598093);
  data->GetYaxis()->SetTitleSize(0.04904632);
  data->GetYaxis()->SetTickLength(0.02721248);
  data->GetYaxis()->SetTitleOffset(1.414173);
  data->GetYaxis()->SetTitleFont(42);
  data->SetLineColor(kBlack);
  //data->SetMinimum(0);
  if(rebin>0) data->Rebin(rebin);
  data->SetMarkerStyle(20);
  data->SetMarkerSize(markerSize_);
  data->Sumw2();

  bkg->SetDirectory(0);
  bkg->SetLineColor(2);
  bkg->SetLineWidth(2);
  bkg->GetYaxis()->SetTitleSize(0);
  bkg->SetLineColor(histLineColor);
  bkg->SetFillColor(histFillColor);
  if(xmin != xmax) bkg->GetXaxis()->SetRangeUser(xmin,xmax);
  bkg->GetXaxis()->SetNdivisions(506);
  bkg->GetXaxis()->SetLabelFont(42);
  bkg->GetXaxis()->SetLabelOffset(1000);
  bkg->GetXaxis()->SetLabelSize(0);
  bkg->GetXaxis()->SetTitleSize(0);
  bkg->GetXaxis()->SetTickLength(0.02554496);
  bkg->GetXaxis()->SetTitleOffset(1000);
  bkg->GetXaxis()->SetTitleFont(42);
  bkg->GetYaxis()->SetTitle(titleY.c_str());
  bkg->GetYaxis()->SetNdivisions(506);
  bkg->GetYaxis()->SetLabelFont(42);
  bkg->GetYaxis()->SetLabelOffset(0.011);
  bkg->GetYaxis()->SetLabelSize(0.04598093);
  bkg->GetYaxis()->SetTitleSize(0.04904632);
  bkg->GetYaxis()->SetTickLength(0.02721248);
  bkg->GetYaxis()->SetTitleOffset(1.414173);
  bkg->GetYaxis()->SetTitleFont(42);
  //bkg->SetMinimum(0);
  bkg->Sumw2();
  if(rebin>0) bkg->Rebin(rebin);

  signal->SetDirectory(0);
  signal->SetLineColor(2);
  signal->SetLineWidth(2);
  signal->GetYaxis()->SetTitleSize(0);
  signal->SetLineColor(kOrange+1);
  //signal->SetFillColor(kOrange);
  if(xmin != xmax) signal->GetXaxis()->SetRangeUser(xmin,xmax);
  signal->GetXaxis()->SetNdivisions(506);
  signal->GetXaxis()->SetLabelFont(42);
  signal->GetXaxis()->SetLabelOffset(1000);
  signal->GetXaxis()->SetLabelSize(0);
  signal->GetXaxis()->SetTitleSize(0);
  signal->GetXaxis()->SetTickLength(0.02554496);
  signal->GetXaxis()->SetTitleOffset(1000);
  signal->GetXaxis()->SetTitleFont(42);
  signal->GetYaxis()->SetTitle(titleY.c_str());
  signal->GetYaxis()->SetNdivisions(506);
  signal->GetYaxis()->SetLabelFont(42);
  signal->GetYaxis()->SetLabelOffset(0.011);
  signal->GetYaxis()->SetLabelSize(0.04598093);
  signal->GetYaxis()->SetTitleSize(0.04904632);
  signal->GetYaxis()->SetTickLength(0.02721248);
  signal->GetYaxis()->SetTitleOffset(1.414173);
  signal->GetYaxis()->SetTitleFont(42);
  //signal->SetMinimum(0);
  signal->Sumw2();
  if(rebin>0) signal->Rebin(rebin);

  allmc->SetDirectory(0);
  allmc->SetLineColor(2);
  allmc->SetLineWidth(2);
  allmc->GetYaxis()->SetTitleSize(0);
  allmc->SetLineColor(kTeal+1);
  //signal->SetFillColor(kTeal);
  if(xmin != xmax) allmc->GetXaxis()->SetRangeUser(xmin,xmax);
  allmc->GetXaxis()->SetNdivisions(506);
  allmc->GetXaxis()->SetLabelFont(42);
  allmc->GetXaxis()->SetLabelOffset(1000);
  allmc->GetXaxis()->SetLabelSize(0);
  allmc->GetXaxis()->SetTitleSize(0);
  allmc->GetXaxis()->SetTickLength(0.02554496);
  allmc->GetXaxis()->SetTitleOffset(1000);
  allmc->GetXaxis()->SetTitleFont(42);
  allmc->GetYaxis()->SetTitle(titleY.c_str());
  allmc->GetYaxis()->SetNdivisions(506);
  allmc->GetYaxis()->SetLabelFont(42);
  allmc->GetYaxis()->SetLabelOffset(0.011);
  allmc->GetYaxis()->SetLabelSize(0.04598093);
  allmc->GetYaxis()->SetTitleSize(0.04904632);
  allmc->GetYaxis()->SetTickLength(0.02721248);
  allmc->GetYaxis()->SetTitleOffset(1.414173);
  allmc->GetYaxis()->SetTitleFont(42);
  //allmc->SetMinimum(0);
  allmc->Sumw2();
  if(rebin>0) allmc->Rebin(rebin);

  leg->AddEntry(data,legdata,"p");
  leg->AddEntry(bkg,legmcbkg,"LF");
  leg->AddEntry(signal,legmcsignal,"LF");
  leg->AddEntry(allmc,legmcall,"LF");

  c->cd();
  pad1->cd();

  allmc->Draw("histsame");
  bkg->Draw("histsame");
  signal->Draw("histsame");
  data->Draw("esamex0");
  leg->Draw();

  TLatex *   tex = new TLatex(0.94,0.9346049,luminosity);
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

  pad1->Modified();
  c->cd();

  // ------------>Primitives in pad: pad2 0,0,1,0.39
  pad2 = new TPad("pad2", "pad2",0,0,1,0.266);
  pad2->Draw();
  pad2->cd();
  pad2->SetFillColor(0);
  pad2->SetBorderMode(0);
  pad2->SetBorderSize(2);
  //pad2->SetGridx();
  pad2->SetLeftMargin(0.15);
  pad2->SetRightMargin(0.065);
  pad2->SetTopMargin(0.03);
  pad2->SetBottomMargin(0.4);
  pad2->SetFrameBorderMode(0);
  pad2->SetFrameBorderMode(0);

  //TH1F* h4=new TH1F(*data);
  TH1F *h4=(TH1F*)data->Clone();
  h4->Divide(bkg);
  h4->SetStats(0);

  //TH1F* h5=new TH1F(*data);
  TH1F *h5=(TH1F*)data->Clone();
  h5->Divide(signal);
  h5->SetStats(0);

  //TH1F* h6=new TH1F(*data);
  TH1F *h6=(TH1F*)data->Clone();
  h6->Divide(allmc);
  h6->SetStats(0);

  h4->SetMinimum(0.7);
  h4->SetMaximum(1.3);
  h4->SetDirectory(0);
  h4->SetStats(0);
  h4->SetLineStyle(0);
  h4->SetMarkerStyle(20);
  h4->SetMarkerColor(histLineColor);
  h4->SetLineColor(histLineColor);
  h4->GetXaxis()->SetRangeUser(xmin,xmax);
  h4->GetXaxis()->SetNdivisions(506);
  h4->GetXaxis()->SetLabelFont(42);
  h4->GetXaxis()->SetLabelOffset(0.012);
  h4->GetXaxis()->SetLabelSize(0.1268797);
  h4->GetXaxis()->SetTitleSize(0.169173);
  h4->GetXaxis()->SetTickLength(0.07048873);
  h4->GetXaxis()->SetTitleOffset(0.935);
  h4->GetXaxis()->SetTitleFont(42);
  h4->GetYaxis()->SetTitle("#chi");
  h4->GetYaxis()->CenterTitle(true);
  h4->GetYaxis()->SetNdivisions(504);
  h4->GetYaxis()->SetLabelFont(42);
  h4->GetYaxis()->SetLabelOffset(0.011);
  h4->GetYaxis()->SetLabelSize(0.1268797);
  h4->GetYaxis()->SetTitleSize(0.1353384);
  h4->GetYaxis()->SetTickLength(0.03972916);
  h4->GetYaxis()->SetTitleOffset(0.5124933);
  h4->GetYaxis()->SetTitleFont(42);

  h5->SetMinimum(0.7);
  h5->SetMaximum(1.3);
  h5->SetDirectory(0);
  h5->SetStats(0);
  h5->SetLineStyle(0);
  h5->SetMarkerStyle(22);
  h5->SetMarkerColor(kOrange+1);
  h5->SetLineColor(kOrange+1);
  h5->GetXaxis()->SetRangeUser(xmin,xmax);
  h5->GetXaxis()->SetNdivisions(506);
  h5->GetXaxis()->SetLabelFont(42);
  h5->GetXaxis()->SetLabelOffset(0.012);
  h5->GetXaxis()->SetLabelSize(0.1268797);
  h5->GetXaxis()->SetTitleSize(0.169173);
  h5->GetXaxis()->SetTickLength(0.07048873);
  h5->GetXaxis()->SetTitleOffset(0.935);
  h5->GetXaxis()->SetTitleFont(42);
  h5->GetYaxis()->SetTitle("#chi");
  h5->GetYaxis()->CenterTitle(true);
  h5->GetYaxis()->SetNdivisions(504);
  h5->GetYaxis()->SetLabelFont(42);
  h5->GetYaxis()->SetLabelOffset(0.011);
  h5->GetYaxis()->SetLabelSize(0.1268797);
  h5->GetYaxis()->SetTitleSize(0.1353384);
  h5->GetYaxis()->SetTickLength(0.03972916);
  h5->GetYaxis()->SetTitleOffset(0.5124933);
  h5->GetYaxis()->SetTitleFont(42);

  h6->SetMinimum(0.7);
  h6->SetMaximum(1.3);
  h6->SetDirectory(0);
  h6->SetStats(0);
  h6->SetLineStyle(0);
  h6->SetMarkerStyle(22);
  h6->SetMarkerColor(kTeal+1);
  h6->SetLineColor(kTeal+1);
  h6->GetXaxis()->SetRangeUser(xmin,xmax);
  h6->GetXaxis()->SetNdivisions(506);
  h6->GetXaxis()->SetLabelFont(42);
  h6->GetXaxis()->SetLabelOffset(0.012);
  h6->GetXaxis()->SetLabelSize(0.1268797);
  h6->GetXaxis()->SetTitleSize(0.169173);
  h6->GetXaxis()->SetTickLength(0.07048873);
  h6->GetXaxis()->SetTitleOffset(0.935);
  h6->GetXaxis()->SetTitleFont(42);
  h6->GetYaxis()->SetTitle("#chi");
  h6->GetYaxis()->CenterTitle(true);
  h6->GetYaxis()->SetNdivisions(504);
  h6->GetYaxis()->SetLabelFont(42);
  h6->GetYaxis()->SetLabelOffset(0.011);
  h6->GetYaxis()->SetLabelSize(0.1268797);
  h6->GetYaxis()->SetTitleSize(0.1353384);
  h6->GetYaxis()->SetTickLength(0.03972916);
  h6->GetYaxis()->SetTitleOffset(0.5124933);
  h6->GetYaxis()->SetTitleFont(42);

  h6->Draw("ep");
  h4->Draw("epsame");
  h5->Draw("epsame");

  pad2->Modified();
  c->cd();
  c->Modified();
  c->cd();
  c->SetSelected(c);

  pad1->SetTickx(1);
  pad1->SetTicky(1);
  pad2->SetTickx(1);
  pad2->SetTicky(1);

  //DFit(data,bkg,signal,"",xmin,xmax);
  //DFitExtended(data,bkg,signal,"",xmin,xmax);

  pad1->RedrawAxis();
  pad2->RedrawAxis();

  // Saving Text File
  std::ofstream outstring(outputinfo.c_str());  
  outstring << "\nS U M M A R Y" << endl;
  if(makeXS){
    outstring << "XS data  : " << data->Integral() << endl;
    outstring << "XS bkg   : " << bkg->Integral() << endl;
    outstring << "XS signal: " << signal->Integral() << "\n" << endl;
  }else{
    outstring << "Events data  : " << data->Integral() << endl;
    outstring << "Events bkg   : " << bkg->Integral() << endl;
    outstring << "Events signal: " << signal->Integral() << "\n" << endl;
    outstring << "Entries bin(0) data: " << data->GetBinContent(1) << endl;
    outstring << "Entries bin(0) MC: " << bkg->GetBinContent(1) << endl;
    outstring << "Difference data-MC: " << fabs(data->GetBinContent(1)-bkg->GetBinContent(1)) << endl;
  }

  if(sigma){

    TCanvas *c2 = new TCanvas("c2", "canvas2",canv_X,canv_Y,canv_W,canv_H);
    c2->SetFillColor(0);
    c2->SetBorderMode(0);
    c2->SetFrameBorderMode(0);
    c2->SetFrameFillStyle(0);
    c2->Draw();

    c2->cd();

    TH1 *Adata = (TH1F*)data->Clone("Adata");
    Adata = HistoSplit(data,"Adata");

    TH1 *Abkg = (TH1F*)bkg->Clone("Abkg");
    Abkg = HistoSplit(bkg,"Abkg");

    TH1 *Asignal = (TH1F*)signal->Clone("Asignal");
    Asignal = HistoSplit(signal,"Asignal");

    TH1 *Aallmc = (TH1F*)allmc->Clone("Aallmc");
    Aallmc = HistoSplit(allmc,"Aallmc");

    TLine *line = new TLine(0,0,4.,0);
    line->SetLineColor(kRed);
    line->SetLineWidth(1.);

    Adata->SetMarkerStyle(20);
    Adata->SetMarkerSize(markerSize_);
    Adata->GetYaxis()->CenterTitle();
    Adata->GetXaxis()->SetLabelFont(42);
    Adata->GetXaxis()->SetLabelOffset(0.009);
    Adata->GetXaxis()->SetLabelSize(0.03);
    Adata->GetXaxis()->SetTitleSize(0.055);
    Adata->GetXaxis()->SetTickLength(0.02554496);
    Adata->GetXaxis()->SetTitleOffset(0.6);
    Abkg->SetLineColor(histLineColor);
    Abkg->SetLineWidth(3.);
    Aallmc->SetLineColor(kTeal+1);
    Aallmc->SetLineWidth(3.);
    Asignal->SetLineColor(kOrange+1);
    Asignal->SetLineWidth(3.);

    Adata->SetMinimum(-1.5);
    Adata->SetMaximum(1.5);
    Adata->Draw("EPsame");
    Abkg->Draw("histosame");
    Asignal->Draw("histosame");
    Aallmc->Draw("histosame");
    line->Draw("same");
    leg->Draw("same");
    Adata->Draw("EPsame");
    c2->Update();

  }

}

// A S Y M M E T R Y   H I S T O G R A M
//--------------------------------------

TH1* HistoSplit(TH1* histo, TString name){

  bool debug = false;
  int nBins = histo->GetNbinsX();

  TString h1title = name + "_result";
  TString h2title = name + "_den";

  TH1F *hresult = new TH1F(h1title, h1title, nBins/2, 0, xmax);
  TH1F *hden = new TH1F(h2title, h2title, nBins/2, 0, xmax);

  for(int i=0, j=nBins/2; i<nBins/2; i++, j--){
    if (debug) cout << "Bins, difference: " << nBins - i << " and " << i + 1 << " to fill bin " << j << endl;
    hresult->SetBinContent(j,histo->GetBinContent(nBins-i)-histo->GetBinContent(i+1));
    hden->SetBinContent(j,histo->GetBinContent(nBins-i)+histo->GetBinContent(i+1));
    hresult->SetBinError(j,TMath::Sqrt(TMath::Power(histo->GetBinError(nBins-i),2)+TMath::Power(histo->GetBinError(i+1),2)));
    hden->SetBinError(j,TMath::Sqrt(TMath::Power(histo->GetBinError(nBins-i),2)+TMath::Power(histo->GetBinError(i+1),2)));
  }

  hresult->Divide(hden);
  hresult->GetXaxis()->SetTitle(histo->GetXaxis()->GetTitle());
  hresult->GetYaxis()->SetTitle(titleYsigma.c_str());
  return hresult;

}

// S I M P L E   P L O T
//----------------------------

void MyOfficialSimpleCMS(TString hname_w){

  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  loadFiles(hname_w);

  float canv_X =  10;
  float canv_Y =  10;
  float canv_W =  700;
  float canv_H =  1000;

  int ci = TColor::GetColor("#ccccff");
  int histFillColor = ci;
  int histLineColor = kBlue+1;

  int histLineWidth = 1;
  float markerSize_ = 0.85;

  TCanvas *c = new TCanvas("c", "canvas",canv_X,canv_Y,canv_W,canv_H);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetFrameBorderMode(0);
  c->SetFrameFillStyle(0);
  c->Draw();

  data->SetDirectory(0);
  data->SetStats(0);

  Int_t ci;      // for color index setting
  TColor *color; // for color definition with alpha
  ci = TColor::GetColor("#0000cc");

  TLegend* leg = new TLegend(0.7597956,0.822335,0.9931857,0.9949239,NULL,"brNDC");

  leg->SetFillColor(kWhite);
  leg->SetLineColor(kWhite);

  data->SetLineColor(ci);
  data->SetLineWidth(2);
  if(xmin != xmax) data->GetXaxis()->SetRangeUser(xmin,xmax);
  //data->GetXaxis()->SetNdivisions(506);
  data->GetXaxis()->SetLabelFont(42);
  //data->GetXaxis()->SetLabelOffset(0.011);
  data->GetXaxis()->SetLabelSize(0.03);
  data->GetXaxis()->SetTitleSize(0.04904632);
  data->GetXaxis()->SetTickLength(0.02721248);
  data->GetXaxis()->SetTitleOffset(0.7);
  data->GetXaxis()->SetTitleFont(42);
  data->GetYaxis()->SetTitle(titleY.c_str());
  //data->GetYaxis()->SetNdivisions(506);
  data->GetYaxis()->SetLabelFont(42);
  data->GetYaxis()->SetLabelOffset(0.011);
  data->GetYaxis()->SetLabelSize(0.025);
  data->GetYaxis()->SetTitleSize(0.04904632);
  data->GetYaxis()->SetTickLength(0.02721248);
  data->GetYaxis()->SetTitleOffset(1.0);
  data->GetYaxis()->SetTitleFont(42);
  data->SetLineColor(kBlack);
  //data->SetMinimum(0);
  if(rebin>0) data->Rebin(rebin);
  data->SetMarkerStyle(20);
  data->SetMarkerSize(markerSize_);
  data->Sumw2();

  bkg->SetDirectory(0);
  bkg->SetLineColor(2);
  bkg->SetLineWidth(2);
  bkg->GetYaxis()->SetTitleSize(0);
  bkg->SetLineColor(histLineColor);
  bkg->SetFillColor(histFillColor);
  if(xmin != xmax) bkg->GetXaxis()->SetRangeUser(xmin,xmax);
  //bkg->GetXaxis()->SetNdivisions(506);
  bkg->GetXaxis()->SetLabelFont(42);
  bkg->GetXaxis()->SetLabelOffset(0.011);
  bkg->GetXaxis()->SetLabelSize(0.03);
  bkg->GetXaxis()->SetTitleSize(0.04904632);
  bkg->GetXaxis()->SetTickLength(0.02721248);
  bkg->GetXaxis()->SetTitleOffset(0.7);
  bkg->GetXaxis()->SetTitleFont(42);
  bkg->GetYaxis()->SetTitle(titleY.c_str());
  //bkg->GetYaxis()->SetNdivisions(506);
  bkg->GetYaxis()->SetLabelFont(42);
  bkg->GetYaxis()->SetLabelOffset(0.011);
  bkg->GetYaxis()->SetLabelSize(0.025);
  bkg->GetYaxis()->SetTitleSize(0.04904632);
  bkg->GetYaxis()->SetTickLength(0.02721248);
  bkg->GetYaxis()->SetTitleOffset(1.0);
  bkg->GetYaxis()->SetTitleFont(42);
  //bkg->SetMinimum(0);
  bkg->Sumw2();
  if(rebin>0) bkg->Rebin(rebin);

  signal->SetDirectory(0);
  signal->SetLineColor(2);
  signal->SetLineWidth(2);
  signal->GetYaxis()->SetTitleSize(0);
  signal->SetLineColor(kOrange+1);
  //signal->SetFillColor(kOrange);
  if(xmin != xmax) signal->GetXaxis()->SetRangeUser(xmin,xmax);
  //signal->GetXaxis()->SetNdivisions(506);
  signal->GetXaxis()->SetLabelFont(42);
  signal->GetXaxis()->SetLabelOffset(0.011);
  signal->GetXaxis()->SetLabelSize(0.03);
  signal->GetXaxis()->SetTitleSize(0.04904632);
  signal->GetXaxis()->SetTickLength(0.02721248);
  signal->GetXaxis()->SetTitleOffset(0.7);
  signal->GetXaxis()->SetTitleFont(42);
  signal->GetYaxis()->SetTitle(titleY.c_str());
  //signal->GetYaxis()->SetNdivisions(506);
  signal->GetYaxis()->SetLabelFont(42);
  signal->GetYaxis()->SetLabelOffset(0.011);
  signal->GetYaxis()->SetLabelSize(0.025);
  signal->GetYaxis()->SetTitleSize(0.04904632);
  signal->GetYaxis()->SetTickLength(0.02721248);
  signal->GetYaxis()->SetTitleOffset(1.0);
  signal->GetYaxis()->SetTitleFont(42);
  //signal->SetMinimum(0);
  signal->Sumw2();
  if(rebin>0) signal->Rebin(rebin);

  allmc->SetDirectory(0);
  allmc->SetLineColor(2);
  allmc->SetLineWidth(2);
  allmc->GetYaxis()->SetTitleSize(0);
  allmc->SetLineColor(kTeal+1);
  //signal->SetFillColor(kTeal);
  if(xmin != xmax) allmc->GetXaxis()->SetRangeUser(xmin,xmax);
  //allmc->GetXaxis()->SetNdivisions(506);
  allmc->GetXaxis()->SetLabelFont(42);
  allmc->GetXaxis()->SetLabelOffset(0.011);
  allmc->GetXaxis()->SetLabelSize(0.03);
  allmc->GetXaxis()->SetTitleSize(0.04904632);
  allmc->GetXaxis()->SetTickLength(0.02721248);
  allmc->GetXaxis()->SetTitleOffset(0.7);
  allmc->GetXaxis()->SetTitleFont(42);
  allmc->GetYaxis()->SetTitle(titleY.c_str());
  //allmc->GetYaxis()->SetNdivisions(506);
  allmc->GetYaxis()->SetLabelFont(42);
  allmc->GetYaxis()->SetLabelOffset(0.011);
  allmc->GetYaxis()->SetLabelSize(0.025);
  allmc->GetYaxis()->SetTitleSize(0.04904632);
  allmc->GetYaxis()->SetTickLength(0.02721248);
  allmc->GetYaxis()->SetTitleOffset(1.0);
  allmc->GetYaxis()->SetTitleFont(42);
  //allmc->SetMinimum(0);
  allmc->Sumw2();
  if(rebin>0) allmc->Rebin(rebin);

  leg->AddEntry(data,legdata,"p");
  leg->AddEntry(bkg,legmcbkg,"LF");
  leg->AddEntry(signal,legmcsignal,"LF");
  //leg->AddEntry(allmc,legmcall,"LF");

  c->cd();

  //allmc->Draw("histsame");
  bkg->Draw("histsame");
  signal->Draw("histsame");
  data->Draw("esamex0");
  leg->Draw();

  TLatex *   tex = new TLatex(0.90,0.92,luminosity);
  tex->SetNDC();
  tex->SetTextAlign(31);
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->Draw();

  tex = new TLatex(0.10,0.94,cmstitle);
  tex->SetNDC();
  tex->SetTextAlign(13);
  tex->SetTextFont(61);
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->Draw();

  gPad->RedrawAxis();

}

// L I K E L I H O O D   F I T
//----------------------------

void DFit(TH1 *Dat, TH1 *MC1, TH1 *MC2, TString title, double x_min, double x_max)  {

  RooRealVar x(title, title, x_min, x_max);  

  RooDataHist Data_in("Data_in","Data_in",x,Dat);
  RooDataHist MC1_in("MC1_in","MC1_in",x,MC1) ;
  RooDataHist MC2_in("MC2_in","MC2_in",x,MC2) ;

  RooHistPdf PDFData_in("PDFData_in", "PDFData_in", x, Data_in) ;
  RooHistPdf PDFMC1_in("PDFMC1_in", "PDFMC1_in", x, MC1_in) ;
  RooHistPdf PDFMC2_in("PDFMC2_in", "PDFMC2_in", x, MC2_in) ;

  //POMWIG,  PYTHIA
  RooRealVar fsig("fsig","signal fraction",0.5,0.,1.);
  RooAddPdf model("model","model",RooArgList(PDFMC2_in,PDFMC1_in),fsig) ;
  model.fitTo(Data_in);

  // Perform fit and save result
  RooFitResult* r = model.fitTo(Data_in,RooFit::Save()) ;
  r->Print("fsig");

  // Draw the frame on the canvas

  RooPlot* xframe = x.frame(Title("Fit")) ;

  Data_in.plotOn(xframe,  RooFit::Name("Data")) ;
  model.plotOn(xframe, RooFit::Name("Fit"),RooFit::LineColor(kTeal+1),RooFit::LineStyle(kDashed));
  model.paramOn(xframe);

  model.plotOn(xframe,  RooFit::Name("PYTHIA6"), RooFit::Components(PDFMC1_in),RooFit::LineColor(kBlue)) ;
  model.plotOn(xframe, RooFit::Name("POMWIG"),RooFit::Components(PDFMC2_in),RooFit::LineColor(kOrange+1)) ;

  new TCanvas("composite","composite",600,600) ;
  gPad->SetLeftMargin(0.15) ; xframe->GetYaxis()->SetTitleOffset(1.4) ; xframe->Draw() ;

  TLegend *legend = new TLegend(0.7,0.7,0.9,0.9);
  legend->SetTextFont(72);
  legend->SetTextSize(0.05);
  legend->AddEntry("Data","Data","P");
  legend->AddEntry("Fit","Fit","L ");
  legend->AddEntry("PYTHIA6","PYTHIA6","L ");
  legend->AddEntry("POMWIG","POMWIG","L ");
  legend->Draw();

}


// L I K E L I H O O D   E X T E N D E D   F I T
//----------------------------------------------

void DFitExtended(TH1 *Dat, TH1 *Bkg, TH1 *Sig, TString title, double x_min, double x_max){

  RooRealVar x(title, title, x_min, x_max); 

  // Get PDFs
  RooDataHist data_in("data_in","data_in",x,Dat);
  RooDataHist bkg_in("bkg_in","bkg_in",x,Bkg) ;
  RooDataHist sig_in("sig_in","sig_in",x,Sig) ;

  RooHistPdf data("PDFdata_in", "PDFdata_in", x, data_in) ;
  RooHistPdf sig("PDFsig_in", "PDFsig_in", x, sig_in) ;
  RooHistPdf bkg("PDFbkg_in", "PDFbkg_in", x, bkg_in) ;

  /////////////////////
  // M E T H O D   1 //
  /////////////////////

  // C o n s t r u c t   e x t e n d e d   c o m p o s i t e   m o d e l 
  // -------------------------------------------------------------------

  // Sum the composite signal and background into an extended pdf nsig*sig+nbkg*bkg
  RooRealVar nsig("nsig","number of signal events",500,0.,40000); //10000
  RooRealVar nbkg("nbkg","number of background events",500,0,40000);
  RooAddPdf  model("model","(g1+g2)+a",RooArgList(bkg,sig),RooArgList(nbkg,nsig)) ;

  // S a m p l e ,   f i t   a n d   p l o t   e x t e n d e d   m o d e l 
  // ---------------------------------------------------------------------
  // = model.expectedEvents() = nsig+nbkg

  // Fit model to data, extended ML term automatically included
  model.fitTo(data_in,Extended(kTRUE)) ; 

  // Plot data and PDF overlaid, use expected number of events for p.d.f projection normalization
  // rather than observed number of events (==data->numEntries())
  RooPlot* xframe = x.frame(Title("extended ML fit example")) ;
  data_in.plotOn(xframe,RooFit::Name("Data")) ;

  //model.plotOn(xframe,LineColor(kBlack),Normalization(1.0,RooAbsReal::RelativeExpected));

  // Overlay the background component of model with a dashed line
  model.plotOn(xframe,Components(bkg),Name("Pythia"),LineColor(kBlue),Normalization(1.0,RooAbsReal::RelativeExpected)) ; //LineStyle(kDashed)

  // Overlay the background+sig2 components of model with a dotted line
  model.plotOn(xframe,Components(RooArgSet(bkg,sig)),LineColor(kTeal+1),Name("Pythia+Pomwig"),Normalization(1.0,RooAbsReal::RelativeExpected)) ; //LineStyle(kDotted)

  /////////////////////
  // M E T H O D   2 //
  /////////////////////

  // C o n s t r u c t   e x t e n d e d   c o m p o n e n t s   f i r s t
  // ---------------------------------------------------------------------

  // Associated nsig/nbkg as expected number of events with sig/bkg
  RooExtendPdf esig("esig","extended signal p.d.f",sig,nsig) ;
  RooExtendPdf ebkg("ebkg","extended background p.d.f",bkg,nbkg) ;

  // S u m   e x t e n d e d   c o m p o n e n t s   w i t h o u t   c o e f s 
  // -------------------------------------------------------------------------

  // Construct sum of two extended p.d.f. (no coefficients required)
  RooAddPdf  model2("model2","(g1+g2)+a",RooArgList(ebkg,esig)) ;

  // Fit chi2
  //Double_t chi2 = xframe->chiSquare("model", "data", 3);
  model2.paramOn(xframe);

  RooFitResult* r = model2.fitTo(data_in,RooFit::Save()) ;
  r->Print("esig");
  r->Print("ebkg");
  r->Print("v") ;

  // Print structure of composite p.d.f.
  ////model.Print("t") ;

  // Draw the frame on the canvas
  new TCanvas("composite","composite",600,600) ;
  gPad->SetLeftMargin(0.15) ; xframe->GetYaxis()->SetTitleOffset(1.4) ; xframe->Draw() ;

  TLegend *legend = new TLegend(0.7,0.7,0.9,0.9);
  legend->SetTextFont(72);
  legend->SetTextSize(0.05);
  legend->AddEntry("Data","Data","P ");
  legend->AddEntry("Pythia+Pomwig","PYTHIA6+POMWIG","L ");
  legend->AddEntry("Pythia","PYTHIA6","L ");
  legend->Draw();

}
