/*

Program: Castor Analysis Plotter
Goal: Create histograms.
Project: Diffractive Z Analysis. Castor Studies.
Created: 18th July, 2013.

How to Execute:

> root -l CastorAnalysisPlotter.C

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

void CastorAnalysisPlotter(){

  //RunAll
  MakeMultipleSingle("muon");
 
}

//
// Create a list of objects from a rootfile
//
// Output: ListOfHistograms.txt

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
// Castor Phi Plots
//

void SectorPhi(TString name1){

  TCanvas *c1 = new TCanvas(name1,name1);
  c1->cd();   

  gStyle->SetOptStat(0);

  TLegend* leg = new TLegend(0.7597956,0.822335,0.9931857,0.9949239,NULL,"brNDC");
  TString legdata, legmc;

  TFile *l1  = TFile::Open("histo_Muon_Reco.root");
  TFile *l2  = TFile::Open("histo_DyToMuMu_Reco.root");
  legdata = "2010 data";
  legmc = "MC";

  TH1F* h_1 = (TH1F*)l1->Get(name1);
  TH1F* h_2 = (TH1F*)l2->Get(name1);
 
  double weight1, weight2;

  weight1 = 1./h_1->GetEntries();
  weight2 = 1./h_2->GetEntries();

  h_1->SetLineColor(kBlack);
  h_1->SetMarkerStyle(20);
  h_1->SetMarkerSize(0.8);
  h_1->Scale(weight1);
  h_1->GetYaxis()->SetTitle("Density");
  leg->AddEntry(h_1,legdata,"p");

  h_2->SetLineColor(kRed);
  h_2->SetLineWidth(2);
  h_2->Scale(weight2);
  h_2->SetFillColor(kRed-4);
  h_2->SetFillStyle(3020);
  h_2->GetYaxis()->SetTitle("Density");
  leg->AddEntry(h_2,legmc,"LFP");

  h_1->Draw("histo");
  h_2->Draw("histosame");
  leg->Draw();

}

//
// Castor: Each sector energy distribution. Each sector energy Vs Total Castor Multiplicity Plots
//

void MakeMultipleSingle(TString type){
    
    gStyle->SetOptStat(0);
    
    TCanvas *c1 = new TCanvas("multiple1","multiple1",2000,1000);
    c1->Divide(4,4);
    
    TCanvas *c2 = new TCanvas("multiple2","multiple2",2000,1000);
    c2->Divide(4,4);
    
    
    if (type == "muon" || type == "Muon" || type == "MUON"){
        TFile *l1  = TFile::Open("histo_Castor_muon.root");
    }
    else if (type == "electron" || type == "Electron" || type == "ELECTRON"){
        TFile *l1  = TFile::Open("histo_Castor_electron.root");
    }
    else {
        std::cout << "Please, put correct option." << std::endl;
        exit(0);
    }
    
    
    for (int i=1; i< 17; i++){
        char name[300];
        sprintf(name,"TotalEnergySector%d_step7",i);
        TH1F* h_1 = (TH1F*)l1->Get(name);
        TH1F* h_2 = h_1->Clone();
        h_2->Reset();
        h_2->SetMaximum(1.);
        c1->cd(i);
        gPad->SetLogx(1);
        gPad->SetLogy(1);
        h_2->Draw();
        h_1->DrawNormalized("same");

        
    }
    
    for (int i=1; i< 17; i++){
        gStyle->SetPalette(1);
        char name2[300];
        sprintf(name2,"Sector%d_EnergyVsMultiplicity_step7",i);
        TH2F* h_1b = (TH2F*)l1->Get(name2);
        TH2F* h_2b = h_1b->Clone();
        h_2b->Reset();
        h_2b->SetMaximum(1.);
        c2->cd(i);
        h_1b->RebinY(50);
        h_2b->Draw("colz");
        h_1b->Draw("colzsame");
    }
    
}

//
// Histograms: configure colors
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