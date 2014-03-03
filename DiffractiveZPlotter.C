/*
Program: Diffractive Z Plotter
Goal: Create histograms.
Project: Diffractive Z Analysis

>> H O W   T O   E X E C U T E :
--------------------------------

> root -l DiffractiveZPlotter.C


>> A N A L Y S I S   C U T S
----------------------------

without_cuts-> No Trigger
with_trigger-> Trigger
step2-> Trigger, Vertex, pT Lepton
step3-> Trigger, Vertex, pT Lepton, NSel
step4-> Trigger, Vertex, pT Lepton, NSel, Charge
step5-> Trigger, Vertex, pT Lepton, NSel, Charge, DiMass
step6-> Trigger, Vertex, pT Lepton, NSel, Charge, DiMass, Isolation
step7-> Trigger, Vertex, pT Lepton, NSel, Charge, DiMass, Isolation, CandSel
GapHFMinus-> Step7 + EtaMinPf > -3;
GapHFPlus-> Step7 + EtaMaxPf < 3;
GapHFMinusAndCastor->Step7 + (EtaMinPf > -3 && CastorGap);
GapHFPlusAndCastorActivity
GapHFPlusAndCastorActivityZKinNegative
GapHFMinusAndCastorZKinPositive

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

void DiffractiveZPlotter(){

  StyleNice();

  //PlotterFour("muon");
  //RunAll("histo_Electron_Reco.root");
  //PlotCalorimeter("muon");
  //PlotterDivide("muon","RunNumberHighCastorAfter_single_step7","RunNumber_singleAfter_single_step7");

  // Diffraction Plots 
  //------------------

  //MakePlotRatio("Diffraction/xiMinusPF_single_NGapCASTOR","Diffraction/xiMinusPF_single_NGapCASTOR","noauto","z","width","#frac{d#sigma}{d#xi}_{-}",0,"noratio","all"); //always 0!
  //MakePlotRatio("Diffraction/xiMinusPF_single_NGapCASTORAndZKinP","Diffraction/xiMinusPF_single_NGapCASTORAndZKinP","noauto","z","width","#frac{d#sigma}{d#xi}_{-}",0,"noratio","all"); //always 0!
  //MakePlotRatio("Diffraction/etasignedHF_single_step7","Diffraction/etasignedHF_single_step7","noauto","z","nowidth","",5,"noratio","nall"); //always 0!
  //MakePlotRatio("Diffraction/etasignedCASTOR_single_step7","Diffraction/etasignedCASTOR_single_step7","noauto","z","nowidth","",5,"noratio","nall"); //always 0!
  //MakePlotRatio("Diffraction/xiMinusPF_single_NGapCASTORAndZKinP","Diffraction/xiMinusPF_single_NGapCASTORAndZKinP","noauto","z","width","#frac{d#sigma}{d#xi}_{-}",0,"noratio","all");//always 0!
  //MakePlotRatio("Diffraction/xiMinusPF_single_NGapCASTORAndZKinP","Diffraction/xiMinusPF_single_NGapCASTORAndZKinP","noauto","z","nowidth","",0,"ratio","all");//always 0!
  //MakePlotRatio("Diffraction/xiMinusPF_single_NGapCMSAndZKinP","Diffraction/xiMinusPF_single_NGapCMSAndZKinP","noauto","z","nowidth","",0,"ratio","all"); //always 0!
  //MakePlotRatio("Diffraction/xiMinusPF_single_step7","Diffraction/xiMinusPF_single_step7","noauto","z","nowidth","",0,"ratio","all"); //always 0!
  //MakePlotRatio("Diffraction/maxetagap_single_step7","Diffraction/maxetagap_single_step7","noauto","z","nowidth","",0,"noratio","all"); //always 0!
  //MakePlotRatio("Diffraction/maxetagap_single_NGapCMS","Diffraction/maxetagap_single_NGapCMS","noauto","z","nowidth","",0,"noratio","all"); //always 0!
  //MakePlotRatio("Diffraction/maxetagap_single_NGapCASTORAndZKinP","Diffraction/maxetagap_single_NGapCASTORAndZKinP","noauto","z","nowidth","",0,"noratio","all"); //always 0!

  // Detector Plots
  //---------------

  //MakePlotRatio("Detector/TracksLow_single_NGapCASTORAndZKinP","Detector/TracksLow_single_NGapCASTORAndZKinP","noauto","z","nowidth","",4,"noratio","all"); //always 0!
  //MakePlotRatio("Detector/TracksLow_single_NGapCASTOR","Detector/TracksLow_single_NGapCASTOR","noauto","z","nowidth","",4,"noratio","all"); //always 0!
  //MakePlotRatio("Detector/TracksLow_single_step7","Detector/TracksLow_single_step7","noauto","z","nowidth","",4,"noratio","all"); //always 0!
  //MakePlotRatio("Detector/TracksLow_single_NGapCMS","Detector/TracksLow_single_NGapCMS","noauto","z","nowidth","",4,"ratio","all"); //always 0!
  //MakePlotRatio("Detector/sumEEEminus_single_NGapCASTORAndZKinP","Detector/sumEEEminus_single_NGapCASTORAndZKinP","noauto","z","nowidth","",0,"noratio","all"); //always 0!
  //MakePlotRatio("Detector/sumEEEminus_single_step7","Detector/sumEEEminus_single_step7","noauto","z","nowidth","",0,"ratio","nall"); //always 0!
  //MakePlotRatio("Detector/sumEEEminus_single_NGapCMSAndZKinP","Detector/sumEEEminus_single_NGapCMSAndZKinP","noauto","z","nowidth","",0,"ratio","all"); //always 0!
  //MakePlotRatio("Detector/sumEEEminus_single_NGapCASTORAndZKinP","Detector/sumEEEminus_single_NGapCASTORAndZKinP","noauto","z","nowidth","",0,"ratio","all"); //always 0!

  // Kinematics Plots
  //-----------------

  //MakePlotRatio("LeptonsKinematics/BosonZEta_single_NGapCASTORAndZKinP","LeptonsKinematics/BosonZEta_single_NGapCASTORAndZKinP","noauto","z","nowidth","",0,"ratio","all"); //always 0!
  //MakePlotRatio("LeptonsKinematics/BosonZEta_single_step7","LeptonsKinematics/BosonZEta_single_step7","noauto","z","nowidth","",2,"ratio","nall"); //always 0!
  //MakePlotRatio("LeptonsKinematics/BosonZEta_single_NGapCASTOR","LeptonsKinematics/BosonZEta_single_NGapCASTOR","noauto","z","nowidth","",0,"ratio","all"); //always 0!
  //MakePlotRatio("LeptonsKinematics/BosonZEta_single_NGapCASTORAndZKinP","LeptonsKinematics/BosonZEta_single_NGapCASTORAndZKinP","noauto","z","nowidth","",0,"ratio","all"); //always 0!


  // Options: AllZ, GoldenZ, GapCASTORZ, AllElectron, GoldenElectron, GapCASTORElectron, AllMuon, GoldenMuon, GapCASTORMuon  
  DGlobalFit("GoldenZ");

}


// M A K E   A   L I S T   O F   H I S T O G R A M S
//--------------------------------------------------


void RunAll(TString filename){

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



// P L O T   C A L O R I M E T E R
//--------------------------------

void PlotCalorimeter(TString type){


  gStyle->SetOptStat(0);

  TCanvas *c1 = new TCanvas("calo","calo",500,1000);
  c1->Divide(2,2);

  if (type == "muon" || type == "Muon" || type == "MUON"){
    TFile *l1  = TFile::Open("histo_Muon_Reco.root");
    TFile *l2  = TFile::Open("histo_DyToMuMu_Reco.root");
    TFile *l3  = TFile::Open("histo_Pompyt_muon_Reco.root");
  }
  else if (type == "electron" || type == "Electron" || type == "ELECTRON"){
    TFile *l1  = TFile::Open("histo_Electron_Reco.root");
    TFile *l2  = TFile::Open("histo_DyToEE_Reco.root");
    TFile *l3  = TFile::Open("histo_Pompyt_electron_Reco.root");
  }
  else {
    std::cout << "Please, put correct option." << std::endl;
    exit(0);
  }

  c1->cd(1);
  gPad->SetLogx(1);
  gPad->SetLogy(1);
  TH1F* h_1 = (TH1F*)l1->Get("sumECastorMinus_single_step7");
  TH1F* h_2 = (TH1F*)l2->Get("sumECastorMinus_single_step7");
  TH1F* h_c = h_1->Clone();
  TH1Draw(h_1,h_2,h_c);
  h_1->DrawNormalized();
  h_2->DrawNormalized("same");

  c1->cd(2);
  gPad->SetLogx(1);
  gPad->SetLogy(1);
  TH1F* h_3 = (TH1F*)l1->Get("sumEHFminus_single_step7");
  TH1F* h_4 = (TH1F*)l2->Get("sumEHFminus_single_step7");
  TH1Draw(h_3,h_4,h_c);
  h_3->DrawNormalized();
  h_4->DrawNormalized("same");

  c1->cd(3);
  gPad->SetLogx(1);
  gPad->SetLogy(1);
  TH1F* h_5 = (TH1F*)l1->Get("sumECastorAndSumHFMinus_single_step7");
  TH1F* h_6 = (TH1F*)l2->Get("sumECastorAndSumHFMinus_single_step7");
  TH1Draw(h_5,h_6,h_c);
  h_5->DrawNormalized();
  h_6->DrawNormalized("same");

  c1->cd(4);
  TH1F* h_7 = (TH1F*)l1->Get("CastorMultiplicity_single_step7");
  TH1F* h_8 = (TH1F*)l2->Get("CastorMultiplicity_single_step7");
  TH1Draw(h_7,h_8,h_c);
  h_5->DrawNormalized();
  h_6->DrawNormalized("same");

}


// P L O T   E A C H   V E R T E X   D I S T R I B U T I O N
//----------------------------------------------------------

void PlotterFour(TString type){

  gStyle->SetOptStat(0);

  if (type == "muon" || type == "Muon" || type == "MUON"){
    TFile *l1  = TFile::Open("histo_Muon_Reco.root");
    TFile *l2  = TFile::Open("histo_Muon_Vertex2_Reco.root");
    TFile *l3  = TFile::Open("histo_Muon_Vertex3_Reco.root");
    TFile *l4  = TFile::Open("histo_Muon_Vertex4_Reco.root");
  }
  else if (type == "electron" || type == "Electron" || type == "ELECTRON"){
    TFile *l1  = TFile::Open("histo_Electron_Reco.root");
    TFile *l2  = TFile::Open("histo_Electron_Vertex2_Reco.root");
    TFile *l3  = TFile::Open("histo_Electron_Vertex3_Reco.root");
    TFile *l4  = TFile::Open("histo_Electron_Vertex4_Reco.root");
  }
  else {
    std::cout << "Please, put correct option." << std::endl;
    exit(0);
  }

  TH1D* h_1 = (TH1D*)l1->Get("CastorMultiplicity_single_step7");
  TH1D* h_2 = (TH1D*)l2->Get("CastorMultiplicity_single_step7");
  TH1D* h_3 = (TH1D*)l3->Get("CastorMultiplicity_single_step7");
  TH1D* h_4 = (TH1D*)l4->Get("CastorMultiplicity_single_step7");

  cout << "Integral H1: " << h_1->Integral(0,16) << endl;
  N2H1DSameArea(h_1,h_3);
  h_3->Scale(1./2.);
  TH1D* h1_sub = h_1->Clone(); 
  h1_sub->Add(h_3,-1);

  // Plot three histograms
  plotHists(h_1,h1_sub,h_3,"Castor Multiplicity","Castor Multiplicity","NEvents","H1","H1_sub","H2",0);

  // Plot four histograms
  //plotHists(h_1,h_2,h_3,h_4,"Castor Multiplicity","Castor Multiplicity","NEvents","Data, Vertex 1","Data, Vertex 2","Data, Vertex 3","Data, Vertex 4",0);

}


// C O M P U T E   F R A C T I O N S   C A S T O R
//------------------------------------------------

void PlotterDivide(TString type,TString name,TString name2){

  TCanvas *c1 = new TCanvas("frac","frac",1000,1000);
  c1->Divide(2,2);

  gStyle->SetOptStat(0);

  if (type == "muon" || type == "Muon" || type == "MUON"){
    TFile *l1  = TFile::Open("histo_Muon_Reco.root");
  }
  else if (type == "electron" || type == "Electron" || type == "ELECTRON"){
    TFile *l1  = TFile::Open("histo_Electron_Reco.root");
  }
  else {
    std::cout << "Please, put correct option." << std::endl;
    exit(0);
  }
  TH1I* h_1 = (TH1I*)l1->Get(name);
  TH1I* h_1D = (TH1I*)l1->Get(name2);

  TH2D* h_fraction = new TH2D("hp0","Normal histogram",16000,134000,150000,20,0,1);
  TH1D* h_fraction1 = new TH1D("hp1","Normal histogram",20,0,1);
  TH1D* h_fraction2 = new TH1D("hp2","Normal histogram",20,0,1);
  TH1D* h_fraction3 = new TH1D("hp3","Normal histogram",20,0,1);

  int j;
  double fraction;
  for (j=1; j<=h_1->GetNbinsX(); j++){
    if (h_1->GetBinContent(j) > 0){
      fraction = h_1->GetBinContent(j)*1./h_1D->GetBinContent(j)*1.;
      cout << "Bin Content, High: " << h_1->GetBinContent(j) << endl;
      cout << "Bin Content, Total: " << h_1D->GetBinContent(j) << endl;
      cout << "Fraction: " << fraction << endl; 
      h_fraction->Fill(134000+j,fraction);
      h_fraction1->Fill(fraction);

      if (j > 14900){
	h_fraction2->Fill(fraction);
      } else h_fraction3->Fill(fraction);

    }
  }

  c1->cd(1);
  h_fraction->Draw();

  c1->cd(2);
  h_fraction1->Draw();

  c1->cd(3);
  h_fraction2->Draw();

  c1->cd(4);
  h_fraction3->Draw();

}


// S T Y L E    C O S M E T I C S
//-------------------------------

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

//  S T Y L E   C O S M E T I C S
//-------------------------------

void format_h(TH1F* h, int linecolor){
  h->SetLineWidth(3);
  h->SetLineColor(linecolor);
}

// P L O T T E R    D I F F R A C T I V E   Z
//-------------------------------------------

void MakePlotRatio(TString name1, TString name2, TString AutoNorma, TString type, TString diff, TString ytitle, int rebinopt, TString mode, TString SumHisto){

  TLegend* leg = new TLegend(0.7597956,0.822335,0.9931857,0.9949239,NULL,"brNDC");
  TString legdata, legmc1, legmc2, legboth;

  leg->SetFillColor(kWhite);

  if (type == "muon" || type == "Muon" || type == "MUON"){
    TFile *l1  = TFile::Open("histo_Muon_Reco.root");
    TFile *l2  = TFile::Open("histo_DyToMuMu_Reco.root");
    TFile *l3  = TFile::Open("histo_Pompyt_muon_Reco.root");
    legdata = "2010 data";
    legmc1 = "Pythia6, DY to #mu^{+}#mu^{-}";
    legmc2 = "Pompyt, Z to #mu^{+}#mu^{-}";
  }
  else if (type == "electron" || type == "Electron" || type == "ELECTRON"){
    TFile *l1  = TFile::Open("histo_Electron_Reco.root");
    TFile *l2  = TFile::Open("histo_DyToEE_Reco.root");
    TFile *l3  = TFile::Open("histo_Pompyt_electron_Reco.root");
    legdata = "2010 data";
    legmc1 = "Pythia6, DY to e^{+}e^{-}";
    legmc2 = "Pompyt, Z to e^{+}e^{-}";
  }else if (type == "Z" || type == "z"){
    TFile *l1  = TFile::Open("histo_Z_Reco.root");
    TFile *l2  = TFile::Open("histo_DY_Reco.root");
    TFile *l3  = TFile::Open("histo_Pompyt_Reco.root"); 
    legdata = "2010 data";
    legmc1 = "Pythia6, DY";
    legmc2 = "Pompyt*0.05, Z";
    legboth = "Pythia6 + Pompyt*0.05";
  }
  else {
    std::cout << "Please, put correct option." << std::endl;
    exit(0);
  }

  TH1F* h_1 = (TH1F*)l1->Get(name1);
  TH1F* h_2 = (TH1F*)l2->Get(name2);
  TH1F* h_3 = (TH1F*)l3->Get(name2);

  if(AutoNorma == "Auto" || AutoNorma == "AUTO" || AutoNorma == "auto") {
    NEntriesNorma(h_1,h_2,h_3);
  }

  h_1->Sumw2();
  h_2->Sumw2();
  h_3->Sumw2();


  if(diff == "width" || diff == "WIDTH"){
    double lumi = 0.07341; // 1.Bin_i/29.08 + Bin_i/25.61 (full data luminosity each period)
    h_1->Scale(lumi,"width");
    h_2->Scale(lumi,"width");
    h_3->Scale(lumi,"width");
    h_1->GetYaxis()->SetTitle(ytitle);
    h_2->GetYaxis()->SetTitle(ytitle);
    h_3->GetYaxis()->SetTitle(ytitle);
  }else{
    h_1->GetYaxis()->SetTitle("N Events");
    h_2->GetYaxis()->SetTitle("N Events");
    h_3->GetYaxis()->SetTitle("N Events");
  }

  if(rebinopt > 0){
    h_1->Rebin(rebinopt);
    h_2->Rebin(rebinopt);
    h_3->Rebin(rebinopt);
  }

  leg->AddEntry(h_1,legdata,"p");
  leg->AddEntry(h_2,legmc1,"LFP");
  leg->AddEntry(h_3,legmc2,"LFP");

  h_3->Scale(0.05);

  h_1->SetLineColor(kBlack);
  h_1->SetMarkerStyle(20);
  h_1->SetMarkerSize(1.2);

  h_2->SetLineColor(kRed);
  h_2->SetLineWidth(4);
  h_2->SetFillColor(kRed-4);
  h_2->SetFillStyle(3020);

  h_3->SetLineColor(kBlue);
  h_3->SetLineWidth(4);
  h_3->SetFillColor(kBlue-4);
  h_3->SetFillStyle(3020);

  TH1F* dividend=new TH1F(*h_1);
  dividend->Divide(h_2);

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

  TList *listAll = new TList;
  listAll->Add(h_2);
  listAll->Add(h_3);

  TH1F *MCtogether = (TH1F*)h_2->Clone("MCtogether");
  MCtogether->Reset();
  MCtogether->SetLineColor(kGreen);
  MCtogether->Merge(listAll);

  h_2->SetFillStyle(0);
  h_3->SetFillStyle(0);
  if (SumHisto=="all" || SumHisto == "ALL"){
    MCtogether->SetFillStyle(0);
    MCtogether->SetLineWidth(4);
    MCtogether->SetFillColor(kGreen);
    MCtogether->Draw("Hist");
    leg->AddEntry(MCtogether,legboth,"LFP");
  }
  h_2->Draw("HistSame");
  h_3->Draw("HistSame");
  h_1->Draw("epsame");
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

  DFitExtended(h_1,h_2,h_3,h_1->GetXaxis()->GetTitle(),h_1->GetXaxis()->GetXmin(),h_1->GetXaxis()->GetXmax());

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

  //POMPYT,  PYTHIA
  RooRealVar fsig("fsig","signal fraction",0.5,0.,1.);
  RooAddPdf model("model","model",RooArgList(PDFMC2_in,PDFMC1_in),fsig) ;
  model.fitTo(Data_in);

  // Perform fit and save result
  RooFitResult* r = model.fitTo(Data_in,RooFit::Save()) ;
  r->Print("fsig");

  RooPlot* frame = x.frame() ;

  Data_in.plotOn(frame,  RooFit::Name("Data"),RooFit::DrawOption(" ")) ; 
  model.plotOn(frame, RooFit::Name("Fit"),RooFit::LineColor(kGreen)) ; 
  model.paramOn(frame) ; 

  model.plotOn(frame,  RooFit::Name("Pythia"), RooFit::Components(PDFMC1_in),
      RooFit::LineColor(kRed),RooFit::LineStyle(kDotted)) ; 
  model.plotOn(frame, RooFit::Name("Pompyt"),RooFit::Components(PDFMC2_in),
      RooFit::LineColor(kBlue),RooFit::LineStyle(kDashed)) ; 

  frame->Draw() ;

  TLegend *legend = new TLegend(0.7,0.7,0.9,0.9);
  legend->SetTextFont(72);
  legend->SetTextSize(0.05);
  legend->AddEntry("Data","Data","P ");
  legend->AddEntry("Fit","Fit","L ");
  legend->AddEntry("Pythia","Pythia","L ");
  legend->AddEntry("Pompyt","Pompyt","L ");
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
  RooRealVar nsig("nsig","number of signal events",500,0.,10000);
  RooRealVar nbkg("nbkg","number of background events",500,0,10000);
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
  model.plotOn(xframe,Normalization(1.0,RooAbsReal::RelativeExpected)) ;

  // Overlay the background component of model with a dashed line
  model.plotOn(xframe,Components(bkg),Name("Pythia"),LineStyle(kDashed),LineColor(kRed),Normalization(1.0,RooAbsReal::RelativeExpected)) ;

  // Overlay the background+sig2 components of model with a dotted line
  model.plotOn(xframe,Components(RooArgSet(bkg,sig)),LineStyle(kDotted),Name("Pythia+Pompyt"),Normalization(1.0,RooAbsReal::RelativeExpected)) ;

  // Print structure of composite p.d.f.
  model.Print("t") ;

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

  RooFitResult* r = model2.fitTo(data_in,RooFit::Save()) ;
  r->Print("esig");
  r->Print("ebkg");
  r->Print("v") ;

  // Fit chi2
  //Double_t chi2 = xframe->chiSquare("model", "data", 3);

  model2.paramOn(xframe);

  // Draw the frame on the canvas
  new TCanvas("composite","composite",600,600) ;
  gPad->SetLeftMargin(0.15) ; xframe->GetYaxis()->SetTitleOffset(1.4) ; xframe->Draw() ;

  TLegend *legend = new TLegend(0.7,0.7,0.9,0.9);
  legend->SetTextFont(72);
  legend->SetTextSize(0.05);
  legend->AddEntry("Data","Data","P ");
  legend->AddEntry("Pythia+Pompyt","Pythia+Pompyt","L ");
  legend->AddEntry("Pythia","Pythia","L ");
  legend->Draw();

}

// L I K E L I H O O D   E X T E N D E D   G L O B A L   F I T//

void DGlobalFit(TString type){

  if(type == "AllZ"){
    TFile *data  = TFile::Open("TTreeAllZ_histo_Z_Reco.root");
    TFile *pythia  = TFile::Open("TTreeAllZ_histo_DY_Reco.root");
    TFile *pompyt  = TFile::Open("TTreeAllZ_histo_Pompyt_Reco.root");
  }else if(type == "GoldenZ"){
    TFile *data  = TFile::Open("TTreeGoldenDiffZ_histo_Z_Reco.root");
    TFile *pythia  = TFile::Open("TTreeGoldenDiffZ_histo_DY_Reco.root");
    TFile *pompyt  = TFile::Open("TTreeGoldenDiffZ_histo_Pompyt_Reco.root");
  }else if(type == "GapCASTORZ"){
    TFile *data  = TFile::Open("TTreeCASTOR_histo_Z_Reco.root");
    TFile *pythia  = TFile::Open("TTreeCASTOR_histo_DY_Reco.root");
    TFile *pompyt  = TFile::Open("TTreeCASTOR_histo_Pompyt_Reco.root");
  }else if(type == "AllElectron"){
    TFile *data  = TFile::Open("TTreeAllDiffZ_histo_Electron_Reco.root");
    TFile *pythia  = TFile::Open("TTreeAllDiffZ_histo_DyToEE_Reco.root");
    TFile *pompyt  = TFile::Open("TTreeAllDiffZ_histo_Pompyt_electron_Reco.root");
  }else if(type == "GoldenElectron"){
    TFile *data  = TFile::Open("TTreeGoldenDiffZ_histo_Electron_Reco.root");
    TFile *pythia  = TFile::Open("TTreeGoldenDiffZ_histo_DyToEE_Reco.root");
    TFile *pompyt  = TFile::Open("TTreeGoldenDiffZ_histo_Pompyt_electron_Reco.root");
  }else if(type == "GapCASTORElectron"){
    TFile *data  = TFile::Open("TTreeCASTOR_histo_Electron_Reco.root");
    TFile *pythia  = TFile::Open("TTreeCASTOR_histo_DyToEE_Reco.root");
    TFile *pompyt  = TFile::Open("TTreeCASTOR_histo_Pompyt_electron_Reco.root");
  }else if(type == "AllMuon"){
    TFile *data  = TFile::Open("TTreeAllDiffZ_histo_Muon_Reco.root");
    TFile *pythia  = TFile::Open("TTreeAllDiffZ_histo_DyToMuMu_Reco.root");
    TFile *pompyt  = TFile::Open("TTreeAllDiffZ_histo_Pompyt_muon_Reco.root");
  }else if(type == "GoldenMuon"){
    TFile *data  = TFile::Open("TTreeGoldenDiffZ_histo_Muon_Reco.root");
    TFile *pythia  = TFile::Open("TTreeGoldenDiffZ_histo_DyToMuMu_Reco.root");
    TFile *pompyt  = TFile::Open("TTreeGoldenDiffZ_histo_Pompyt_muon_Reco.root");
  }else if(type == "GapCASTORMuon"){
    TFile *data  = TFile::Open("TTreeCASTOR_histo_Muon_Reco.root");
    TFile *pythia  = TFile::Open("TTreeCASTOR_histo_DyToMuMu_Reco.root");
    TFile *pompyt  = TFile::Open("TTreeCASTOR_histo_Pompyt_muon_Reco.root");
  }else{
    std::cout << "Please, put correct option." << std::endl;
    exit(0);
  }

  TTree *datain = (TTree*)data->Get("Events");
  TTree *pythiain = (TTree*)pythia->Get("Events");
  TTree *pompytin = (TTree*)pompyt->Get("Events");

  RooRealVar SumEEEMinus("SumEEEMinus","SumEEEMinus",0,100); //100
  RooRealVar XiMinusFromPFCands("XiMinusFromPFCands","XiMinusFromPFCands",0,1);
  RooRealVar MultiplicityTracks("MultiplicityTracks","MultiplicityTracks",0,500);
  RooRealVar DiBosonEta("DiBosonEta","DiBosonEta",-50,50); //Roofit makes an automatic binning. -50,50
  RooRealVar EtaSigned("etasigned","etasigned",-5,5); // different number of events.

  RooDataSet DataSet("data","data",datain,RooArgSet(SumEEEMinus,XiMinusFromPFCands,MultiplicityTracks,DiBosonEta));
  RooDataSet pythiaSet("pythia","pythia",pythiain,RooArgSet(SumEEEMinus,XiMinusFromPFCands,MultiplicityTracks,DiBosonEta));
  RooDataSet pompytSet("pompyt","pompyt",pompytin,RooArgSet(SumEEEMinus,XiMinusFromPFCands,MultiplicityTracks,DiBosonEta));

  DataSet.Print();
  pythiaSet.Print();
  pompytSet.Print();


  //   P Y T H I A
  RooDataHist pythiaHistoSumEEE("pythiaHistoSumEEE","pythiaHistoSumEEE", SumEEEMinus, pythiaSet);
  RooHistPdf pythiaPDFSumEEE("pythiaPDFSumEEE", "pythiaPDFSumEEE", SumEEEMinus, pythiaHistoSumEEE) ;

  RooDataHist pythiaHistoXiMinus("pythiaHistoXiMinus","pythiaHistoXiMinus", XiMinusFromPFCands, pythiaSet);
  RooHistPdf pythiaPDFXiMinus("pythiaPDFXiMinus", "pythiaPDFXiMinus", XiMinusFromPFCands, pythiaHistoXiMinus) ;

  RooDataHist pythiaHistoTracks("pythiaHistoTracks","pythiaHistoTracks", MultiplicityTracks, pythiaSet);
  RooHistPdf pythiaPDFTracks("pythiaPDFTracks", "pythiaPDFTracks", MultiplicityTracks, pythiaHistoTracks) ;

  RooDataHist pythiaHistoDiBosonEta("pythiaHistoDiBosonEta","pythiaHistoDiBosonEta", DiBosonEta, pythiaSet);
  RooHistPdf pythiaPDFDiBosonEta("pythiaPDFDiBosonEta", "pythiaPDFDiBosonEta", DiBosonEta, pythiaHistoDiBosonEta) ;

  RooDataHist pythiaHistoEtaSigned("pythiaHistoEtaSigned","pythiaHistoEtaSigned", EtaSigned, pythiaSet);
  RooHistPdf pythiaPDFEtaSigned("pythiaPDFEtaSigned", "pythiaPDFEtaSigned", EtaSigned, pythiaHistoEtaSigned) ;


  //   P O M P Y T
  RooDataHist pompytHistoSumEEE("pompytHistoSumEEE","pompytHistoSumEEE", SumEEEMinus, pompytSet);
  RooHistPdf pompytPDFSumEEE("pompytPDFSumEEE", "pompytPDFSumEEE", SumEEEMinus, pompytHistoSumEEE) ;

  RooDataHist pompytHistoXiMinus("pompytHistoXiMinus","pompytHistoXiMinus", XiMinusFromPFCands, pompytSet);
  RooHistPdf pompytPDFXiMinus("pompytPDFXiMinus", "pompytPDFXiMinus", XiMinusFromPFCands, pompytHistoXiMinus) ;

  RooDataHist pompytHistoTracks("pompytHistoTracks","pompytHistoTracks", MultiplicityTracks, pompytSet);
  RooHistPdf pompytPDFTracks("pompytPDFTracks", "pompytPDFTracks", MultiplicityTracks, pompytHistoTracks) ;

  RooDataHist pompytHistoDiBosonEta("pompytHistoDiBosonEta","pompytHistoDiBosonEta", DiBosonEta, pompytSet);
  RooHistPdf pompytPDFDiBosonEta("pompytPDFDiBosonEta", "pompytPDFDiBosonEta", DiBosonEta, pompytHistoDiBosonEta) ;

  RooDataHist pompytHistoEtaSigned("pompytHistoEtaSigned","pompytHistoEtaSigned", EtaSigned, pompytSet);
  RooHistPdf pompytPDFEtaSigned("pompytPDFEtaSigned", "pompytPDFEtaSigned", EtaSigned, pompytHistoEtaSigned) ;


  //   F R E E   P A R A M E T E R S 
  RooRealVar nbkg("nbkg","number of background",500,0,10000);
  RooRealVar nsig("nsig","number of signal",500,0,10000);


  //   M U L T I P L Y I N G   P D F S
  RooProdPdf modelPythia("modelpythia","modelpythia",RooArgSet(pythiaPDFSumEEE,pythiaPDFXiMinus,pythiaPDFTracks,pythiaPDFDiBosonEta));
  RooProdPdf modelPompyt("modelpompyt","modelpompyt",RooArgSet(pompytPDFSumEEE,pompytPDFXiMinus,pompytPDFTracks,pompytPDFDiBosonEta));


  //   C R E A T I N G   M O D E L
  RooAddPdf  model("model","(g1+g2)+a",RooArgList(modelPythia,modelPompyt),RooArgList(nbkg,nsig)) ;
  model.fitTo(DataSet,Extended(kTRUE)) ;


  //   P L O T T I N G   E A C H   D I M E N S I O N


  // Plot SumEEE
  RooPlot* xframeSumEEE = SumEEEMinus.frame(Title("extended ML fit example")) ;
  DataSet.plotOn(xframeSumEEE,RooFit::Name("Data")) ;
  model.plotOn(xframeSumEEE,Normalization(1.0,RooAbsReal::RelativeExpected)) ;
  model.plotOn(xframeSumEEE,Components(pythiaPDFSumEEE),Name("Pythia"),LineStyle(kDashed),LineColor(kRed),Normalization(1.0,RooAbsReal::RelativeExpected)) ;
  model.plotOn(xframeSumEEE,Components(RooArgSet(pythiaPDFSumEEE,pompytPDFSumEEE)),LineStyle(kDotted),Name("Pythia+Pompyt"),Normalization(1.0,RooAbsReal::RelativeExpected)) ;
  model.Print("t") ;

  // Plot xiMinus
  RooPlot* xframeXiMinus = XiMinusFromPFCands.frame(Title("extended ML fit example")) ;
  DataSet.plotOn(xframeXiMinus,RooFit::Name("Data")) ;
  model.plotOn(xframeXiMinus,Normalization(1.0,RooAbsReal::RelativeExpected)) ;
  model.plotOn(xframeXiMinus,Components(pythiaPDFXiMinus),Name("Pythia"),LineStyle(kDashed),LineColor(kRed),Normalization(1.0,RooAbsReal::RelativeExpected)) ;
  model.plotOn(xframeXiMinus,Components(RooArgSet(pythiaPDFXiMinus,pompytPDFXiMinus)),LineStyle(kDotted),Name("Pythia+Pompyt"),Normalization(1.0,RooAbsReal::RelativeExpected)) ;
  model.Print("t") ;

  // Plot Tracks
  RooPlot* xframeTracks = MultiplicityTracks.frame(Title("extended ML fit example")) ;
  DataSet.plotOn(xframeTracks,RooFit::Name("Data")) ;
  model.plotOn(xframeTracks,Normalization(1.0,RooAbsReal::RelativeExpected)) ;
  model.plotOn(xframeTracks,Components(pythiaPDFTracks),Name("Pythia"),LineStyle(kDashed),LineColor(kRed),Normalization(1.0,RooAbsReal::RelativeExpected)) ;
  model.plotOn(xframeTracks,Components(RooArgSet(pythiaPDFTracks,pompytPDFTracks)),LineStyle(kDotted),Name("Pythia+Pompyt"),Normalization(1.0,RooAbsReal::RelativeExpected)) ;
  model.Print("t") ;

  // Plot DiBoson Eta
  RooPlot* xframeDiBosonEta = DiBosonEta.frame(Title("extended ML fit example")) ;
  DataSet.plotOn(xframeDiBosonEta,RooFit::Name("Data"));
  model.plotOn(xframeDiBosonEta,Normalization(1.0,RooAbsReal::RelativeExpected)) ;
  model.plotOn(xframeDiBosonEta,Components(pythiaPDFDiBosonEta),Name("Pythia"),LineStyle(kDashed),LineColor(kRed),Normalization(1.0,RooAbsReal::RelativeExpected)) ;
  model.plotOn(xframeDiBosonEta,Components(RooArgSet(pythiaPDFDiBosonEta,pompytPDFDiBosonEta)),LineStyle(kDotted),Name("Pythia+Pompyt"),Normalization(1.0,RooAbsReal::RelativeExpected)) ;
  model.Print("t") ;

  /////////////////////
  // M E T H O D   2 //
  /////////////////////

  // C o n s t r u c t   e x t e n d e d   c o m p o n e n t s   f i r s t
  // ---------------------------------------------------------------------

  // Associated nsig/nbkg as expected number of events with sig/bkg
  RooExtendPdf esig("esig","extended signal p.d.f",modelPompyt,nsig) ;
  RooExtendPdf ebkg("ebkg","extended background p.d.f",modelPythia,nbkg) ;

  // S u m   e x t e n d e d   c o m p o n e n t s   w i t h o u t   c o e f s
  // -------------------------------------------------------------------------

  // Construct sum of two extended p.d.f. (no coefficients required)
  RooAddPdf  model2("model2","(g1+g2)+a",RooArgList(ebkg,esig)) ;

  RooFitResult* r = model2.fitTo(DataSet,RooFit::Save()) ;
  r->Print("esig");
  r->Print("ebkg");
  r->Print("v") ;

  model2.paramOn(xframeSumEEE);
  model2.paramOn(xframeTracks);
  model2.paramOn(xframeXiMinus);
  model2.paramOn(xframeDiBosonEta);

  TCanvas *c1 = new TCanvas("c1","multipads",900,700);
  c1->Divide(2,2);

  gPad->SetLeftMargin(0.15);
  c1->cd(1);
  xframeSumEEE->GetYaxis()->SetTitleOffset(1.4) ; xframeSumEEE->Draw() ;
  c1->cd(2);
  xframeXiMinus->GetYaxis()->SetTitleOffset(1.4) ; xframeXiMinus->Draw() ;
  c1->cd(3);
  xframeTracks->GetYaxis()->SetTitleOffset(1.4) ; xframeTracks->Draw() ;
  c1->cd(4);
  xframeDiBosonEta->GetYaxis()->SetTitleOffset(1.4) ;  xframeDiBosonEta->Draw() ;

  c1->cd(1);
  TLegend *legend = new TLegend(0.7,0.7,0.9,0.9);
  legend->SetTextFont(72);
  legend->SetTextSize(0.05);
  legend->AddEntry("Data","Data","P ");
  legend->AddEntry("Pythia+Pompyt","Pythia+Pompyt","L ");
  legend->AddEntry("Pythia","Pythia","L ");
  legend->Draw();

}
