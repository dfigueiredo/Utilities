/*

Program: Diffractive Z Plotter
Goal: Create histograms.
Project: Diffractive Z Analysis
Created: 18th July, 2013.

How to Execute:

> root -l DiffractiveZPlotter.C

Version: v0.1

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

void DiffractiveZPlotter(){

  //PlotterFour("muon");
  //RunAll("histo_Electron_Reco.root","log","auto","electron", "TH1");
  //MakePlot("xiPF_single_step7","xiPF_single_step7","log","auto","muon",0,"TH1"); //always 0!
  //MakePlot("CastorMultiplicityAfter_single_step7","CastorMultiplicity_single_step7","nolog","auto","muon",0,"TH1"); //always 0!
  //MakePlot("CastorMultiplicityBefore_single_step7","CastorMultiplicity_single_step7","nolog","auto","muon",0,"TH1"); //always 0!
  //MakePlot("SectorVsTotalCastorEnergyAfter_single_step7","SectorVsTotalCastorEnergy_single_step7","nolog","auto","muon",0,"TH2"); //always 0!

  //MakePlot("SectorVsTotalCastorEnergy_single_step7","SectorVsTotalCastorEnergy_single_step7","nolog","auto","muon",0,"TH1"); //always 0!


  //PlotCalorimeter("muon");
  //PlotterDivide("muon","RunNumberHighCastorAfter_single_step7","RunNumber_singleAfter_single_step7");

  //MakeAllKinematics("step7");
  //MakeAllKinematics("GapHFMinus");
  //MakeAllKinematics("GapHFMinusAndCastor");
  //MakeAllKinematics("GapHFMinusAndCastorZKinPositive");
  //MakeXiAll("muon");
  MakeXi("xiPF_single_step7","xiPF_single_step7","log","auto","muon",0,"TH1",0.05); //always 0!
  MakeXi("xiPF_single_GapHFMinus","xiPF_single_step7","log","auto","muon",0,"TH1",0.05); //always 0!
  MakeXi("xiPF_single_GapHFMinusAndCastor","xiPF_single_step7","log","auto","muon",0,"TH1",0.05); //always 0!

}

//
// RunAll: to create a list file with all *.root objects
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
	//MakePlot(hName1,hName1,logOpt,autonorma,type,0,th);
      }
    }

  }

  outstring.close();

}


//
// MakeAllKinematics: create kinematics plots for Z for a given cut
//
void MakeAllKinematics(TString complement){

  gStyle->SetOptStat("em");

  TLegend* leg_electron = new TLegend(0.7597956,0.822335,0.9931857,0.9949239,NULL,"brNDC");
  TLegend* leg_muon = new TLegend(0.7597956,0.822335,0.9931857,0.9949239,NULL,"brNDC");
  TString legdata, legmc1_e, legmc2_e, legmc1_m, legmc2_m;

  TCanvas *c1 = new TCanvas(complement,complement,2000,1200);
  c1->Divide(4,2);

  TFile *l1e  = TFile::Open("histo_Electron_Reco.root");
  TFile *l2e  = TFile::Open("histo_DyToEE_Reco.root");
  TFile *l3e  = TFile::Open("histo_Pompyt_electron_Reco.root");

  TFile *l1m  = TFile::Open("histo_Muon_Reco.root");
  TFile *l2m  = TFile::Open("histo_DyToMuMu_Reco.root");
  TFile *l3m  = TFile::Open("histo_Pompyt_muon_Reco.root");

  legdata = "2010 data";
  legmc1_e = "Pythia6, DY to e^{+}e^{-}";
  legmc2_e = "Pompyt, Z to e^{+}e^{-}";
  legmc1_m = "Pythia6, DY to #mu^{+}#mu^{-}";
  legmc2_m = "Pompyt, Z to #mu^{+}#mu^{-}";

  TString name_e1 = "DiElectronMass_single_" + complement;
  TString name_e2 = "DiElectronEta_single_" + complement;
  TString name_e3 = "DiElectronPhi_single_" + complement;
  TString name_e4 = "DiElectronPt_single_" + complement;

  vector<TString> histoname_e;
  histoname_e.push_back(name_e1);
  histoname_e.push_back(name_e2);
  histoname_e.push_back(name_e3);
  histoname_e.push_back(name_e4);

  double weight1_e = 0.;
  double weight2_e = 0.;
  double weight3_e = 0.;
  double ratio1_e = 0.;
  double ratio2_e = 0.;
    
  TH1F* h_1ew = (TH1F*)l1e->Get("DiElectronMass_single_step7");
  TH1F* h_2ew = (TH1F*)l2e->Get("DiElectronMass_single_step7");
  TH1F* h_3ew = (TH1F*)l3e->Get("DiElectronMass_single_step7");
    
  weight1_e = 1./h_1ew->GetEntries();
  weight2_e = 1./h_2ew->GetEntries();
  weight3_e = 1./h_3ew->GetEntries();
    
  ratio1_e = weight2_e/weight1_e;
  ratio2_e = weight3_e/weight1_e;
    
  for (unsigned i=0; i<histoname_e.size(); i++){

    cout << histoname_e[i] << endl;
    TH1F* h_1e = (TH1F*)l1e->Get(histoname_e.at(i));
    TH1F* h_2e = (TH1F*)l2e->Get(histoname_e.at(i));
    TH1F* h_3e = (TH1F*)l3e->Get(histoname_e.at(i));

    h_1e->SetLineColor(kBlack);
    h_1e->SetMarkerStyle(20);
    h_1e->SetMarkerSize(0.8);
    h_1e->GetYaxis()->SetTitle("N Events");
    if(i==0)leg_electron->AddEntry(h_1e,legdata,"p");

    h_2e->SetLineColor(kRed);
    h_2e->SetLineWidth(2);
    h_2e->Scale(ratio1_e);
    h_2e->SetFillColor(kRed-4);
    h_2e->SetFillStyle(3020);
    h_2e->GetYaxis()->SetTitle("N Events");
    if(i==0)leg_electron->AddEntry(h_2e,legmc1_e,"LFP");

    h_3e->SetLineColor(kBlue);
    h_3e->SetLineWidth(2);
    h_3e->Scale(0.05*ratio2_e);
    h_3e->SetFillColor(kBlue-4);
    h_3e->SetFillStyle(3020);
    h_3e->GetYaxis()->SetTitle("N Events");
    if(i==0)leg_electron->AddEntry(h_3e,legmc2_e,"LFP");

    c1->cd(i+1);
    h_1e->Draw("ep");
    h_2e->Draw("histosame");
    h_3e->Draw("histosame");

    leg_electron->Draw("histosames");

  }

  TString name_m1 = "DiMuonMass_single_" + complement;
  TString name_m2 = "DiMuonEta_single_" + complement;
  TString name_m3 = "DiMuonPhi_single_" + complement;
  TString name_m4 = "DiMuonPt_single_" + complement;

  vector<TString> histoname_m;
  histoname_m.push_back(name_m1);
  histoname_m.push_back(name_m2);
  histoname_m.push_back(name_m3);
  histoname_m.push_back(name_m4);
    
  double weight1_m = 0.;
  double weight2_m = 0.;
  double weight3_m = 0.;
  double ratio1_m = 0.;
  double ratio2_m = 0.;
    
  TH1F* h_1mw = (TH1F*)l1e->Get("DiMuonMass_single_step7");
  TH1F* h_2mw = (TH1F*)l2e->Get("DiMuonMass_single_step7");
  TH1F* h_3mw = (TH1F*)l3e->Get("DiMuonMass_single_step7");
    
  weight1_m = 1./h_1mw->GetEntries();
  weight2_m = 1./h_2mw->GetEntries();
  weight3_m = 1./h_3mw->GetEntries();
    
  ratio1_m = weight2_m/weight1_m;
  ratio2_m = weight3_m/weight1_m;

  for (unsigned i=0; i<histoname_m.size(); i++){

    cout << histoname_m[i] << endl;
    TH1F* h_1m = (TH1F*)l1m->Get(histoname_m[i]);
    TH1F* h_2m = (TH1F*)l2m->Get(histoname_m[i]);
    TH1F* h_3m = (TH1F*)l3m->Get(histoname_m[i]);

    h_1m->SetLineColor(kBlack);
    h_1m->SetMarkerStyle(20);
    h_1m->SetMarkerSize(0.8);
    h_1m->GetYaxis()->SetTitle("N Events");
    if(i==0)leg_muon->AddEntry(h_1m,legdata,"p");

    h_2m->SetLineColor(kRed);
    h_2m->SetLineWidth(2);
    h_2m->Scale(ratio1_m);
    h_2m->SetFillColor(kRed-4);
    h_2m->SetFillStyle(3020);
    h_2m->GetYaxis()->SetTitle("N Events");
    if(i==0)leg_muon->AddEntry(h_2m,legmc1_m,"LFP");

    h_3m->SetLineColor(kBlue);
    h_3m->SetLineWidth(2);
    h_3m->Scale(0.05*ratio2_m);
    h_3m->SetFillColor(kBlue-4);
    h_3m->SetFillStyle(3020);
    h_3m->GetYaxis()->SetTitle("N Events");
    if(i==0)leg_muon->AddEntry(h_3m,legmc2_m,"LFP");

    c1->cd(i+5);
    h_1m->Draw("ep");
    h_2m->Draw("histosame");
    h_3m->Draw("histosame");

    leg_muon->Draw("histosames");

  }
    
}

//
// Make a single plot with Fit
//
void MakeXi(TString name1,TString name2, TString logscale, TString AutoNorma, TString type, bool destructor, TString th, double per){
    
    TCanvas *c1 = new TCanvas(name1,name1);
    c1->Divide(1,2);
    c1->cd(1);
    
    //gStyle->SetOptStat(0);
    
    TLegend* leg = new TLegend(0.7597956,0.822335,0.9931857,0.9949239,NULL,"brNDC");
    TString legdata, legmc1, legmc2;
    
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
    }
    else {
        std::cout << "Please, put correct option." << std::endl;
        exit(0);
    }
    
    double weight1 = 0.;
    double weight2 = 0.;
    double weight3 = 0.;
    double ratio1 = 0.;
    double ratio2 = 0.;
    
    if(logscale == "log" || logscale == "LOG" || logscale == "Log") {
       c1->SetLogx(1);
    }
    
    if (th=="TH1"){
        TH1F* h_1 = (TH1F*)l1->Get(name1);
        TH1F* h_2 = (TH1F*)l2->Get(name2);
        TH1F* h_3 = (TH1F*)l3->Get(name2);
    }
    else if (th=="TH2"){
        TH2F* h_1 = (TH2F*)l1->Get(name1);
        TH2F* h_2 = (TH2F*)l2->Get(name2);
        TH3F* h_3 = (TH1F*)l3->Get(name2);
    }
    
    TH1F* h_1w = (TH1F*)l1->Get("xiPF_single_step7");
    TH1F* h_2w = (TH1F*)l2->Get("xiPF_single_step7");
    TH1F* h_3w = (TH1F*)l3->Get("xiPF_single_step7");
    
    if(AutoNorma == "Auto" || AutoNorma == "AUTO" || AutoNorma == "auto") {
        weight1 = 1./h_1w->GetEntries();
        weight2 = 1./h_2w->GetEntries();
        weight3 = 1./h_3w->GetEntries();
        
        ratio1 = weight2/weight1;
        ratio2 = weight3/weight1;
    }
    else {
        weight1 = 1.;
        weight2 = 1.;
        weight3 = 1.;
    }
    
    h_1->SetLineColor(kBlack);
    h_1->SetMarkerStyle(20);
    h_1->SetMarkerSize(0.8);
    h_1->GetYaxis()->SetTitle("N Events");
    leg->AddEntry(h_1,legdata,"p");
    
    h_2->SetLineColor(kRed);
    h_2->SetLineWidth(2);
    h_2->Scale(ratio1);
    h_2->SetFillColor(kRed-4);
    h_2->SetFillStyle(3020);
    h_2->GetYaxis()->SetTitle("N Events");
    leg->AddEntry(h_2,legmc1,"LFP");
    
    h_3->SetLineColor(kBlue);
    h_3->SetLineWidth(2);
    h_3->Scale(per*ratio2);
    h_3->SetFillColor(kBlue-4);
    h_3->SetFillStyle(3020);
    h_3->GetYaxis()->SetTitle("N Events");
    leg->AddEntry(h_3,legmc2,"LFP");
    
    h_1->Draw("ep");
    h_2->Draw("histosame");
    h_3->Draw("histosame");
    leg->Draw("histosames");
    
    c1->cd(2);
    NFitMCToData(h_1,h_2,h_3);
    
    c1->Update();
    c1->SaveAs(name1+TString(".png"));
    c1->SaveAs(name1+TString(".C"));
    
    if (destructor){
        delete c1;
        delete h_1;
        delete h_2;
        delete leg;
    }
    
}

//
// MakeXi Plot: create Xi plots for Z.
//
void MakeXiAll(TString type){
    
    gStyle->SetOptStat("em");
    
    TCanvas *c1 = new TCanvas("xiAllGapPlus","xiAllGapPlus",2000,400);
    c1->Divide(4,1);
    
    TCanvas *c2 = new TCanvas("xiAllGapMinus","xiAllGapMinus",2000,400);
    c2->Divide(4,1);
    
    TCanvas *c3 = new TCanvas("xiPlusGapMinus","xiPlusGapMinus",2000,400);
    c3->Divide(4,1);
    
    TCanvas *c4 = new TCanvas("xiPlusGapPlus","xiPlusGapPlus",2000,400);
    c4->Divide(4,1);
    
    TCanvas *c5 = new TCanvas("xiMinusGapMinus","xiMinusGapMinus",2000,400);
    c5->Divide(4,1);
    
    TCanvas *c6 = new TCanvas("xiMinusGapPlus","xiMinusGapPlus",2000,400);
    c6->Divide(4,1);
    
    gPad->SetLogx();
    gPad->SetLogy();

    TLegend* leg = new TLegend(0.7597956,0.822335,0.9931857,0.9949239,NULL,"brNDC");
    TString legdata, legmc1, legmc2;
    
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
    }
    else {
        std::cout << "Please, put correct option." << std::endl;
        exit(0);
    }
    
    TString name_xi1 = "xiPF_single_step7";
    TString name_xi2 = "xiPF_single_GapHFMinus";
    TString name_xi3 = "xiPF_single_GapHFMinusAndCastor";
    TString name_xi4 = "xiPF_single_GapHFMinusAndCastorZKinPositive";
    
    TString name_xi5 = "xiPF_single_step7";
    TString name_xi6 = "xiPF_single_GapHFPlus";
    TString name_xi7 = "xiPF_single_GapHFPlusAndCastorActivity";
    TString name_xi8 = "xiPF_single_GapHFPlusAndCastorActivityZKinNegative";
    
    TString name_xi9 = "xiPlusPF_single_step7";
    TString name_xi10 = "xiPlusPF_single_GapHFMinus";
    TString name_xi11 = "xiPlusPF_single_GapHFMinusAndCastor";
    TString name_xi12 = "xiPlusPF_single_GapHFMinusAndCastorZKinPositive";
    
    TString name_xi13 = "xiPlusPF_single_step7";
    TString name_xi14 = "xiPlusPF_single_GapHFPlus";
    TString name_xi15 = "xiPlusPF_single_GapHFPlusAndCastorActivity";
    TString name_xi16 = "xiPlusPF_single_GapHFPlusAndCastorActivityZKinNegative";
    
    TString name_xi17 = "xiMinusPF_single_step7";
    TString name_xi18 = "xiMinusPF_single_GapHFMinus";
    TString name_xi19 = "xiMinusPF_single_GapHFMinusAndCastor";
    TString name_xi20 = "xiMinusPF_single_GapHFMinusAndCastorZKinPositive";
    
    TString name_xi21 = "xiMinusPF_single_step7";
    TString name_xi22 = "xiMinusPF_single_GapHFPlus";
    TString name_xi23 = "xiMinusPF_single_GapHFPlusAndCastorActivity";
    TString name_xi24 = "xiMinusPF_single_GapHFPlusAndCastorActivityZKinNegative";
    
    vector<TString> histoname_xi;
    histoname_xi.push_back(name_xi1);
    histoname_xi.push_back(name_xi2);
    histoname_xi.push_back(name_xi3);
    histoname_xi.push_back(name_xi4);
    histoname_xi.push_back(name_xi5);
    histoname_xi.push_back(name_xi6);
    histoname_xi.push_back(name_xi7);
    histoname_xi.push_back(name_xi8);
    histoname_xi.push_back(name_xi9);
    histoname_xi.push_back(name_xi10);
    histoname_xi.push_back(name_xi11);
    histoname_xi.push_back(name_xi12);
    histoname_xi.push_back(name_xi13);
    histoname_xi.push_back(name_xi14);
    histoname_xi.push_back(name_xi15);
    histoname_xi.push_back(name_xi16);
    histoname_xi.push_back(name_xi17);
    histoname_xi.push_back(name_xi18);
    histoname_xi.push_back(name_xi19);
    histoname_xi.push_back(name_xi20);
    histoname_xi.push_back(name_xi21);
    histoname_xi.push_back(name_xi22);
    histoname_xi.push_back(name_xi23);
    histoname_xi.push_back(name_xi24);
    
    double weight1 = 0.;
    double weight2 = 0.;
    double weight3 = 0.;
    double ratio1 = 0.;
    double ratio2 = 0.;

    TH1F* h_1w = (TH1F*)l1->Get("xiPF_single_step7");
    TH1F* h_2w = (TH1F*)l2->Get("xiPF_single_step7");
    TH1F* h_3w = (TH1F*)l3->Get("xiPF_single_step7");
    
    weight1 = 1./h_1w->GetEntries();
    weight2 = 1./h_2w->GetEntries();
    weight3 = 1./h_3w->GetEntries();
    
    ratio1 = weight2/weight1;
    ratio2 = weight3/weight1;
    
    double xi_bin[9]={0.0003,0.002,0.0045,0.01,0.02,0.04,0.06,0.08,0.1};
    
    for (unsigned i=0; i<histoname_xi.size(); i++){
        
        /*
        TH1F* h_1new = (TH1F*)l1->Get(histoname_xi[i]);
        TH1F* h_2new = (TH1F*)l2->Get(histoname_xi[i]);
        TH1F* h_3new = (TH1F*)l3->Get(histoname_xi[i]);

        h_1new->Rebin(8,"h_1xi",xi_bin);
        h_2new->Rebin(8,"h_2xi",xi_bin);
        h_3new->Rebin(8,"h_3xi",xi_bin);
        */
        
        TH1F* h_1xi= (TH1F*)l1->Get(histoname_xi[i]);
        TH1F* h_2xi = (TH1F*)l2->Get(histoname_xi[i]);
        TH1F* h_3xi = (TH1F*)l3->Get(histoname_xi[i]);
        
        h_1xi->SetLineColor(kBlack);
        h_1xi->SetMarkerStyle(20);
        h_1xi->SetMarkerSize(0.8);
        h_1xi->GetYaxis()->SetTitle("N Events");
        if (i==0) leg->AddEntry(h_1xi,legdata,"p");
        
        h_2xi->SetLineColor(kRed);
        h_2xi->SetLineWidth(2);
        h_2xi->Scale(ratio1);
        h_2xi->SetFillColor(kRed-4);
        h_2xi->SetFillStyle(3020);
        h_2xi->GetYaxis()->SetTitle("N Events");
        if(i==0)leg->AddEntry(h_2xi,legmc1,"LFP");
        
        h_3xi->SetLineColor(kBlue);
        h_3xi->SetLineWidth(2);
        h_3xi->Scale(ratio2);
        h_3xi->SetFillColor(kBlue-4);
        h_3xi->SetFillStyle(3020);
        h_3xi->GetYaxis()->SetTitle("N Events");
        if(i==0)leg->AddEntry(h_3xi,legmc2,"LFP");
        
        if (i>=0 && i<=3) c1->cd(i+1);
        if (i>=4 && i<=7) c2->cd(i-3);
        if (i>=8 && i<=11) c3->cd(i-7);
        if (i>=12 && i<=15) c4->cd(i-11);
        if (i>=16 && i<=19) c5->cd(i-15);
        if (i>=20 && i<=23) c6->cd(i-19);
        
        h_1xi->Draw("ep");
        h_2xi->Draw("histosame");
        h_3xi->Draw("histosame");
        
        //NFitMCToData(h_1xi,h_2xi,h_3xi);
        
        leg->Draw("histosames");
        
    }
    
}

//
// Make a single plot with Fit
//
void MakePlot(TString name1,TString name2, TString logscale, TString AutoNorma, TString type, bool destructor, TString th){

  TCanvas *c1 = new TCanvas(name1,name1);
  c1->Divide(1,2);
  c1->cd(1);   

  //gStyle->SetOptStat(0);

  TLegend* leg = new TLegend(0.7597956,0.822335,0.9931857,0.9949239,NULL,"brNDC");
  TString legdata, legmc1, legmc2;

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
  }
  else {
    std::cout << "Please, put correct option." << std::endl;
    exit(0);
  }

  double weight1 = 0.;
  double weight2 = 0.;
  double weight3 = 0.;
  double ratio1 = 0.;
  double ratio2 = 0.;

  if(logscale == "log" || logscale == "LOG" || logscale == "Log") c1->SetLogy(1);

  if (th=="TH1"){
    TH1F* h_1 = (TH1F*)l1->Get(name1);
    TH1F* h_2 = (TH1F*)l2->Get(name2);
    TH1F* h_3 = (TH1F*)l3->Get(name2);
  }
  else if (th=="TH2"){
    TH2F* h_1 = (TH2F*)l1->Get(name1);
    TH2F* h_2 = (TH2F*)l2->Get(name2);
    TH3F* h_3 = (TH1F*)l3->Get(name2);
  }

  if(AutoNorma == "Auto" || AutoNorma == "AUTO" || AutoNorma == "auto") {
    weight1 = 1./h_1->GetEntries();
    weight2 = 1./h_2->GetEntries();
    weight3 = 1./h_3->GetEntries();

    ratio1 = weight2/weight1;
    ratio2 = weight3/weight1;
  }
  else {
    weight1 = 1.;
    weight2 = 1.;
    weight3 = 1.;
  }

  h_1->SetLineColor(kBlack);
  h_1->SetMarkerStyle(20);
  h_1->SetMarkerSize(0.8);
  h_1->GetYaxis()->SetTitle("N Events");
  leg->AddEntry(h_1,legdata,"p");

  h_2->SetLineColor(kRed);
  h_2->SetLineWidth(2);
  h_2->Scale(ratio1);
  h_2->SetFillColor(kRed-4);
  h_2->SetFillStyle(3020);
  h_2->GetYaxis()->SetTitle("N Events");
  leg->AddEntry(h_2,legmc1,"LFP");

  h_3->SetLineColor(kBlue);
  h_3->SetLineWidth(2);
  h_3->Scale(ratio2);
  h_3->SetFillColor(kBlue-4);
  h_3->SetFillStyle(3020);
  h_3->GetYaxis()->SetTitle("N Events");
  leg->AddEntry(h_3,legmc2,"LFP");

  h_1->Draw("ep");
  h_2->Draw("histosame");
  h_3->Draw("histosame");
  leg->Draw("histosames");

  c1->cd(2);
  NFitMCToData(h_1,h_2,h_3);

  c1->Update();
  c1->SaveAs(name1+TString(".png"));
  c1->SaveAs(name1+TString(".C"));

  if (destructor){
    delete c1;
    delete h_1;
    delete h_2;
    delete leg;
  }

}

//
// Plot all calorimeter information
//
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

//
// Plot distribution for each vertex
//
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

  /*
     h_1->Scale(1./h_1->GetBinContent(16));
     h_2->Scale(1./h_2->GetBinContent(16));
     h_3->Scale(1./h_3->GetBinContent(16));
     h_4->Scale(1./h_4->GetBinContent(16));
   */

  cout << "Integral H1: " << h_1->Integral(0,16) << endl;
  N2H1DSameArea(h_1,h_3);
  h_3->Scale(1./2.);
  TH1D* h1_sub = h_1->Clone(); 
  h1_sub->Add(h_3,-1);

  //N2HSameMax(h_1,h_2);
  //N2HSameMax(h_1,h_3);
  //N2HSameMax(h_1,h_4);

  plotHists(h_1,h1_sub,h_3,"Castor Multiplicity","Castor Multiplicity","NEvents","H1","H1_sub","H2",0);
  //plotHists(h_1,h_2,h_3,h_4,"Castor Multiplicity","Castor Multiplicity","NEvents","Data, Vertex 1","Data, Vertex 2","Data, Vertex 3","Data, Vertex 4",0);

}

//
// Compute Fractions of DeltaEta
//
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


  //h_1->Sumw2();
  //h_1D->Sumw2();

  //gStyle->SetLabelSize(10., "X"); 

  int j;
  double fraction;
  for (j=1; j<=h_1->GetNbinsX(); j++){
    //cout << j << endl;
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

//
// Style
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



