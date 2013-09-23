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
  SectorPhi("CastorCentroidPhi_single_step7");
  //PlotterFour("muon");
  //RunAll("histo_Electron_Reco.root","log","auto","electron", "TH1");
  //MakePlot("patDiElectronMass_single_step7","patDiElectronMass_single_step7","nolog","auto","electron",0,"TH1"); //always 0!
  //MakePlot("CastorMultiplicityAfter_single_step7","CastorMultiplicity_single_step7","nolog","auto","muon",0,"TH1"); //always 0!
  //MakePlot("CastorMultiplicityBefore_single_step7","CastorMultiplicity_single_step7","nolog","auto","muon",0,"TH1"); //always 0!
  //MakePlot("SectorVsTotalCastorEnergyAfter_single_step7","SectorVsTotalCastorEnergy_single_step7","nolog","auto","muon",0,"TH2"); //always 0!

  //MakePlot("SectorVsTotalCastorEnergy_single_step7","SectorVsTotalCastorEnergy_single_step7","nolog","auto","muon",0,"TH1"); //always 0!

  //MakeMultiple("muon");
  //PlotCalorimeter("muon");
  //PlotterDivide("muon","RunNumberHighCastorBefore_single_step7","RunNumber_singleBefore_single_step7");
  //PlotterDivide("muon","RunNumberHighCastorAfter_single_step7","RunNumber_singleAfter_single_step7");
 
}

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


void MakePlot(TString name1,TString name2, TString logscale, TString AutoNorma, TString type, bool destructor, TString th){

  TCanvas *c1 = new TCanvas(name1,name1);
  c1->Divide(1,2);
  c1->cd(1);   

  //gStyle->SetOptStat(0);

  TLegend* leg = new TLegend(0.7597956,0.822335,0.9931857,0.9949239,NULL,"brNDC");
  TString legdata, legmc1, legmc2;

  if (type == "muon" || type == "Muon" || type == "MUON"){
    //TFile *l1  = TFile::Open("histo_Muon_Reco.root");
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
^

void MakeMultiple(TString type){

  gStyle->SetOptStat(0);

  TCanvas *c1 = new TCanvas("multiple1","multiple1",2000,1000);
  c1->Divide(4,4);

  TCanvas *c2 = new TCanvas("multiple2","multiple2",2000,1000);
  c2->Divide(4,4);

  TCanvas *c3 = new TCanvas("multiple3","multiple3",2000,1000);
  c3->Divide(4,4);

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


  for (int i=1; i< 17; i++){
    char name[300];
    sprintf(name,"TotalEnergyCastor_sector%d_single_step7",i);
    TH1F* h_1 = (TH1F*)l1->Get(name);
    TH1F* h_2 = (TH1F*)l2->Get(name);
    TH1F* h_3 = (TH1F*)l3->Get(name);
    TH1F* h_4 = h_1->Clone();
    h_4->Reset();
    h_4->SetMaximum(1.);
    TH1Draw(h_1,h_2,h_3);
    c1->cd(i);
    gPad->SetLogx(1);
    gPad->SetLogy(1);
    h_4->Draw();
    h_1->DrawNormalized("same");
    h_2->DrawNormalized("same");
    //h_3->DrawNormalized("same");

  }


  for (int i=1; i< 17; i++){
    char name[300];
    char name2[300];
    sprintf(name,"TotalEnergyCastor_Before_sector%d_single_step7",i);
    sprintf(name2,"TotalEnergyCastor_sector%d_single_step7",i);
    TH1F* h_1b = (TH1F*)l1->Get(name);
    TH1F* h_2b = (TH1F*)l2->Get(name2);
    TH1F* h_3b = (TH1F*)l3->Get(name2);
    TH1F* h_4b = h_1b->Clone();
    h_4b->Reset();
    TH1Draw(h_1b,h_2b,h_3b);
    c2->cd(i);
    gPad->SetLogx(1);
    gPad->SetLogy(1);
    h_4b->Draw();
    h_4b->SetMaximum(1.);
    h_1b->DrawNormalized("same");
    h_2b->DrawNormalized("same");
    //h_3b->DrawNormalized("same");

  }


  for (int i=1; i< 17; i++){
    char name[300];
    char name2[300];
    sprintf(name,"TotalEnergyCastor_After_sector%d_single_step7",i);
    sprintf(name2,"TotalEnergyCastor_sector%d_single_step7",i);
    TH1F* h_1a = (TH1F*)l1->Get(name);
    TH1F* h_2a = (TH1F*)l2->Get(name2);
    TH1F* h_3a = (TH1F*)l3->Get(name2);
    TH1F* h_4a = h_1a->Clone();
    h_4a->Reset();
    TH1Draw(h_1a,h_2a,h_3a);
    c3->cd(i);
    gPad->SetLogx(1);
    gPad->SetLogy(1);
    h_4a->SetMaximum(1.);
    h_4a->Draw();
    h_1a->DrawNormalized("same");
    h_2a->DrawNormalized("same");
    //h_3a->DrawNormalized("same");
  }


}

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


