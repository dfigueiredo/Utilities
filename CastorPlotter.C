/*

Program: Castor Analysis Plotter
Goal: Create histograms.
Project: Diffractive Z Analysis. Castor Studies.

How to Execute:

> root -l CastorPlotter.C

No defense for empyt histograms or files. Private use.

 */

#include <iostream>
#include <fstream>


void CastorPlotter(){

  MakeMultipleSingle("muon");
  //ThresholdsStudiesChannels("histo_Castor_threshold_p1_unpaired.root","unpaired",0,1);
  //ThresholdsStudiesSectors("histo_Castor_threshold_p2_unpaired.root","unpaired",0,1);
  //ThresholdsStudiesSectors("histo_Castor_threshold_p3_unpaired.root","unpaired",0,1);

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
  h_1->Scale(weight1*100);
  h_1->GetYaxis()->SetTitle("Fraction of Events %");
  leg->AddEntry(h_1,legdata,"p");

  h_2->SetLineColor(kRed);
  h_2->SetLineWidth(2);
  h_2->Scale(weight2*100);
  h_2->SetFillColor(kRed-4);
  h_2->SetFillStyle(3020);
  h_2->GetYaxis()->SetTitle("Fraction of Events %");
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

  TCanvas *c3 = new TCanvas("multiple3","multiple3",2000,1000);
  c3->Divide(4,4);

  TCanvas *c4 = new TCanvas("multiple4","multiple4",500,500);

  TCanvas *c5 = new TCanvas("multiple5","multiple5",2000,250);
  c5->Divide(5,1);

  TCanvas *c6 = new TCanvas("multiple6","multiple6",500,500);

  TCanvas *c7 = new TCanvas("multiple7","multiple7",2000,1000);
  c7->Divide(4,4);

  TLegend* leg = new TLegend(0.7597956,0.822335,0.9931857,0.9949239,NULL,"brNDC");

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
    h_1->GetYaxis()->SetTitleOffset(1.4);
    h_1->DrawNormalized("same");
  }

  for (int i=1; i< 17; i++){
    gStyle->SetPalette(1);
    char name2[300];
    sprintf(name2,"Sector%d_EnergyVsMultiplicity_step7",i);
    TH2F* h_1b = (TH2F*)l1->Get(name2);
    TH2F* h_2b = h_1b->Clone();
    h_2b->Reset();
    c2->cd(i);
    h_1b->RebinY(3);
    h_2b->Draw("colz");
    h_1b->GetYaxis()->SetTitleOffset(1.4);
    h_1b->Draw("colzsame");
  }

  for (int i=1; i< 17; i++){
    gStyle->SetPalette(1);
    char name3[300];
    sprintf(name3,"AlongZ_Sector%d_EnergyVsModule_step7",i);
    TH2F* h_1c = (TH2F*)l1->Get(name3);
    TH2F* h_2c = h_1c->Clone();
    h_2c->Reset();
    c3->cd(i);
    h_1c->GetYaxis()->SetRangeUser(0.,400.);
    h_2c->GetYaxis()->SetRangeUser(0.,400.);
    h_1c->RebinY(3);
    h_2c->Draw("colz");
    h_1c->GetYaxis()->SetTitleOffset(1.4);
    h_1c->Draw("colzsame");
  }

  for (int i=1; i< 6; i++){
    char name4[300];
    sprintf(name4,"CastorMultiplicityModule%d_step7",i);
    TH1F* h_1d = (TH1F*)l1->Get(name4);
    c4->cd();
    h_1d->GetYaxis()->SetTitleOffset(1.4);
      h_1d->SetMarkerColor(i);
      h_1->SetMarkerSize(1.5);
      h_1d->SetMarkerStyle(8);
      h_1d->GetYaxis()->SetRangeUser(0.,470.);
      h_1d->SetTitle("Multiplicity");
      char legtitle[300];
      sprintf(legtitle,"Module %d",i);
      leg->AddEntry(h_1d,legtitle,"p");
    if (i==1) {
       h_1d->Draw("p");
    }else{
       h_1d->Draw("psame");
    }
    leg->Draw();

    char name5[300];
    sprintf(name5,"CastorMultiplicityModule%dVsTotal_step7",i);
    TH2F* h_1e = (TH2F*)l1->Get(name5);
    c5->cd(i);
    gStyle->SetPalette(1);
    h_1e->GetYaxis()->SetTitleOffset(1.4);
    h_1e->Draw("colz");
  }

  TH1F* h_1f = (TH1F*)l1->Get("CastorMultiplicity_step7");
  c6->cd();
  h_1f->GetYaxis()->SetTitleOffset(1.4);
  h_1f->Draw();

  for (int i=1; i< 17; i++){
    gStyle->SetPalette(1);
    char name6[300];
    sprintf(name6,"AlongZ_Sector%d_EnergyVsModuleTProf_step7",i);
    TProfile* h_1g = (TProfile*)l1->Get(name6);
    c7->cd(i);
    h_1g->GetYaxis()->SetTitleOffset(1.4);
    h_1g->Draw();
  }

}

//
// Castor: sector thresholds. Thresholds Measurements.
//
// Output: file with each sector threshold.

void ThresholdsStudiesSectors(TString openfile, TString complement, bool printPar, bool printTh){

  gStyle->SetOptStat("em");

  TCanvas *c1 = new TCanvas("sectorenergy","sectorenergy",2000,1000);
  c1->Divide(4,4);
  TCanvas *c2 = new TCanvas("thresholds","thresholds",500,500);
  TCanvas *c3 = new TCanvas("sigma","sigma",500,500);

  TFile *l1  = TFile::Open(openfile);

  TString outtxt = openfile;
  outtxt.ReplaceAll("root","txt");
  TString newname = "FitResults_"+outtxt;
  std::ofstream outstring(newname);
  Double_t x[16], y[16];
  Double_t ex[16], ey[16];
  Double_t ys[16];
  Double_t eys[16];

  for (int i=1; i< 17; i++){

    char name[300];
    char text[300];
    char textth[300];
    char textthf[300];     

    sprintf(name,"Sector%d_CastorSumEnergy_with_type_",i);
    TString finalname = name + complement;
    cout << finalname << endl;
    TH1F* h_1 = (TH1F*)l1->Get(finalname);
    c1->cd(i);
    h_1->Fit("gaus","","",-5.,5.);
    h_1->GetXaxis()->SetRangeUser(-5*h_1->GetFunction("gaus")->GetParameter(2),5*h_1->GetFunction("gaus")->GetParameter(2));
    h_1->GetYaxis()->SetRangeUser(0.,1.3*h_1->GetFunction("gaus")->GetMaximum());
    h_1->GetYaxis()->SetTitleOffset(1.4);
    h_1->Draw();

    double limit = 4*h_1->GetFunction("gaus")->GetParameter(2);
    Double_t maxvalue = 0.9*h_1->GetMaximum();

    TLine *line = new TLine(limit,0,limit,0.7*maxvalue);
    line->SetLineColor(8);
    line->SetLineWidth(3);
    line->Draw();

    outstring << "\n<< Sector " << i << " >>" << endl;
    outstring << "Mean: " << h_1->GetFunction("gaus")->GetParameter(1)<< " GeV" << endl;
    outstring << "Sigma: " << h_1->GetFunction("gaus")->GetParameter(2)<< " GeV" << endl;
    outstring << "Threshold (4xsigma): " << 4*h_1->GetFunction("gaus")->GetParameter(2)<< " GeV" << endl;
    outstring << "Error Threshold (4xsigma): " << h_1->GetFunction("gaus")->GetParError(2) << " GeV" << endl;

    y[i-1] = 4*h_1->GetFunction("gaus")->GetParameter(2);
    x[i-1] = i;
    ex[i-1] = 0;
    ey[i-1] = 4*h_1->GetFunction("gaus")->GetParError(2);

    ys[i-1] = h_1->GetFunction("gaus")->GetParameter(2);
    eys[i-1] = h_1->GetFunction("gaus")->GetParError(2);

    TLatex *lt = new TLatex(0.7,160,text);
    sprintf(text,"f(x) = %g*e^{#frac{x-%g}{%g}}",h_1->GetFunction("gaus")->GetParameter(1),h_1->GetFunction("gaus")->GetParameter(2),h_1->GetFunction("gaus")->GetParameter(3));
    lt->SetTextSize(0.1);
    lt->SetTextFont(72);
    lt->SetTextColor(kBlue);
    if (printPar) lt->DrawLatex(2.,1.,text);

    TLatex *ltt = new TLatex(0.7,160,textth);
    sprintf(textth,"Threshold: %g GeV",4*h_1->GetFunction("gaus")->GetParameter(2));
    ltt->SetTextSize(0.08);
    ltt->SetTextFont(72);
    ltt->SetTextColor(kBlack);
    if (printTh) ltt->DrawLatex(-3*h_1->GetFunction("gaus")->GetParameter(2),1.1*h_1->GetFunction("gaus")->GetMaximum(),textth);

  }

  c2->cd();
  gr = new TGraphErrors(16,x,y,ex,ey);
  gr->SetTitle("Castor Threshold per Sector");
  gr->GetYaxis()->SetTitle("Threshold [GeV]");
  gr->GetXaxis()->SetTitle("Sector");
  gr->SetMarkerSize(1.);
  gr->GetYaxis()->SetTitleOffset(1.4);
  gr->SetMarkerStyle(21);
  gr->GetYaxis()->SetRangeUser(0.,1.5*y[0]);
  gr->Draw("AP");

  c3->cd();
  grs = new TGraphErrors(16,x,ys,ex,eys);
  grs->SetTitle("#sigma_{fit} per Sector");
  grs->GetYaxis()->SetTitle("#sigma_{fit} [GeV]");
  grs->GetXaxis()->SetTitle("Sector");
  grs->SetMarkerSize(1.);
  grs->SetMarkerStyle(21);
  grs->GetYaxis()->SetTitleOffset(1.4);
  grs->GetYaxis()->SetRangeUser(0.,1.5*ys[0]);
  grs->Fit("pol0");
  grs->Draw("AP");

  TLatex *lttf = new TLatex(0.7,160,textthf);
  sprintf(textthf,"#sigma_{fit}: %g GeV, Threshold: %g GeV",grs->GetFunction("pol0")->GetParameter(0),4*grs->GetFunction("pol0")->GetParameter(0));
  lttf->SetTextSize(0.03);
  lttf->SetTextFont(72);
  lttf->SetTextColor(kBlack);
  lttf->DrawLatex(1,1.35*ys[0],textthf);

  outstring.close();

}

//
// Castor: channels thresholds. Thresholds Measurements.
//
// Output: file with each channel threshold.

void ThresholdsStudiesChannels(TString openfile, TString complement, bool printPar, bool printTh){
    
    gStyle->SetOptStat("em");
    
    TCanvas *c1 = new TCanvas("channelenergy1","channelenergy1",2000,1000);
    c1->Divide(4,4);
   
    TCanvas *c2 = new TCanvas("channelenergy2","channelenergy2",2000,1000);
    c2->Divide(4,4);
    
    TCanvas *c3 = new TCanvas("channelenergy3","channelenergy3",2000,1000);
    c3->Divide(4,4);
    
    TCanvas *c4 = new TCanvas("channelenergy4","channelenergy4",2000,1000);
    c4->Divide(4,4);
    
    TCanvas *c5 = new TCanvas("channelenergy5","channelenergy5",2000,1000);
    c5->Divide(4,4);
    
    TCanvas *c6 = new TCanvas("thresholds","thresholds",500,500);
    TCanvas *c7 = new TCanvas("sigma","sigma",500,500);
    
    TFile *l1  = TFile::Open(openfile);
    
    TString outtxt = openfile;
    outtxt.ReplaceAll("root","txt");
    TString newname = "FitResults_"+outtxt;
    std::ofstream outstring(newname);
    Double_t x[80], y[80];
    Double_t ex[80], ey[80];
    Double_t ys[80];
    Double_t eys[80];
    
    for (int i=1; i< 81; i++){
        
        char name[300];
        char text[300];
        char textth[300];
        char textthf[300];
        
        sprintf(name,"Channel%d_Energy_with_type_",i);
        TString finalname = name + complement;
        cout << finalname << endl;
        TH1F* h_1 = (TH1F*)l1->Get(finalname);
        if (i>=1 && i<=16) c1->cd(i);
        if (i>=17 && i<=32) c2->cd(i-16);
        if (i>=33 && i<=48) c3->cd(i-32);
        if (i>=49 && i<=64) c4->cd(i-48);
        if (i>=65 && i<=80) c5->cd(i-64);
        h_1->Fit("gaus","","",-5.,5.);
        h_1->GetXaxis()->SetRangeUser(-5*h_1->GetFunction("gaus")->GetParameter(2),5*h_1->GetFunction("gaus")->GetParameter(2));
        h_1->GetYaxis()->SetRangeUser(0.,1.3*h_1->GetFunction("gaus")->GetMaximum());
        h_1->GetYaxis()->SetTitleOffset(1.4);
        h_1->Draw();
        
        double limit = 4*h_1->GetFunction("gaus")->GetParameter(2);
        Double_t maxvalue = 0.9*h_1->GetMaximum();
        
        TLine *line = new TLine(limit,0,limit,0.7*maxvalue);
        line->SetLineColor(8);
        line->SetLineWidth(3);
        line->Draw();
        
        outstring << "\n<< Sector " << i << " >>" << endl;
        outstring << "Mean: " << h_1->GetFunction("gaus")->GetParameter(1)<< " GeV" << endl;
        outstring << "Sigma: " << h_1->GetFunction("gaus")->GetParameter(2)<< " GeV" << endl;
        outstring << "Threshold (4xsigma): " << 4*h_1->GetFunction("gaus")->GetParameter(2)<< " GeV" << endl;
        outstring << "Error Threshold (4xsigma): " << h_1->GetFunction("gaus")->GetParError(2) << " GeV" << endl;
        
        y[i-1] = 4*h_1->GetFunction("gaus")->GetParameter(2);
        x[i-1] = i;
        ex[i-1] = 0;
        ey[i-1] = 4*h_1->GetFunction("gaus")->GetParError(2);
        
        ys[i-1] = h_1->GetFunction("gaus")->GetParameter(2);
        eys[i-1] = h_1->GetFunction("gaus")->GetParError(2);
        
        TLatex *lt = new TLatex(0.7,160,text);
        sprintf(text,"f(x) = %g*e^{#frac{x-%g}{%g}}",h_1->GetFunction("gaus")->GetParameter(1),h_1->GetFunction("gaus")->GetParameter(2),h_1->GetFunction("gaus")->GetParameter(3));
        lt->SetTextSize(0.1);
        lt->SetTextFont(72);
        lt->SetTextColor(kBlue);
        if (printPar) lt->DrawLatex(2.,1.,text);
        
        TLatex *ltt = new TLatex(0.7,160,textth);
        sprintf(textth,"Threshold: %g GeV",4*h_1->GetFunction("gaus")->GetParameter(2));
        ltt->SetTextSize(0.08);
        ltt->SetTextFont(72);
        ltt->SetTextColor(kBlack);
        if (printTh) ltt->DrawLatex(-3*h_1->GetFunction("gaus")->GetParameter(2),1.1*h_1->GetFunction("gaus")->GetMaximum(),textth);
        
    }
    
    c6->cd();
    gr = new TGraphErrors(80,x,y,ex,ey);
    gr->SetTitle("Castor Threshold per Sector");
    gr->GetYaxis()->SetTitle("Threshold [GeV]");
    gr->GetXaxis()->SetTitle("Sector");
    gr->SetMarkerSize(1.);
    gr->GetYaxis()->SetTitleOffset(1.4);
    gr->SetMarkerStyle(21);
    gr->GetYaxis()->SetRangeUser(0.,1.5*y[0]);
    gr->Draw("AP");
    
    c7->cd();
    grs = new TGraphErrors(80,x,ys,ex,eys);
    grs->SetTitle("#sigma_{fit} per Sector");
    grs->GetYaxis()->SetTitle("#sigma_{fit} [GeV]");
    grs->GetXaxis()->SetTitle("Sector");
    grs->SetMarkerSize(1.);
    grs->SetMarkerStyle(21);
    grs->GetYaxis()->SetTitleOffset(1.4);
    grs->GetYaxis()->SetRangeUser(0.,1.5*ys[0]);
    grs->Fit("pol0");
    grs->Draw("AP");
    
    TLatex *lttf = new TLatex(0.7,160,textthf);
    sprintf(textthf,"#sigma_{fit}: %g GeV, Threshold: %g GeV",grs->GetFunction("pol0")->GetParameter(0),4*grs->GetFunction("pol0")->GetParameter(0));
    lttf->SetTextSize(0.03);
    lttf->SetTextFont(72);
    lttf->SetTextColor(kBlack);
    lttf->DrawLatex(1,1.35*ys[0],textthf);
    
    outstring.close();
    
}

//
// Compare Signal and Noise, same Run Range
//

void CompareSignalAndNoise(TString name,bool logscale, bool swtmsg){

  gStyle->SetOptStat(0);

  // Data
  TFile *l1  = TFile::Open("histo_Castor_threshold_p1_collisions.root");
  TFile *l2  = TFile::Open("histo_Castor_threshold_p1_unpaired.root");
  TFile *l3  = TFile::Open("histo_Castor_threshold_p1_nocollisions.root");

  TCanvas* c1 = new TCanvas(name,name);
  c1->cd()->SetRightMargin(0.04);

  TLegend* leg = new TLegend(0.696, 0.35, 0.94, 0.92);
  leg->SetBorderSize(0);
  leg->SetLineStyle(0);
  leg->SetTextFont(42);
  leg->SetFillStyle(0);
  leg->SetFillColor(0);

  TString name1 = name + "_collisions";
  TString name2 = name + "_unpaired";
  TString name3 = name + "_no_collisions";

  if(logscale) c1->SetLogy(1);

  TH1F* h_1 = (TH1F*)l1->Get(name1);
  h_1->SetMarkerStyle(20);
  h_1->SetMarkerColor(kBlack);
  h_1->GetYaxis()->SetTitle("Fraction of Events %");
  leg->AddEntry(h_1,"Data 2010, Collisions","P");

  TH1F* h_2 = (TH1F*)l2->Get(name2);
  h_2->SetMarkerStyle(20);
  h_2->SetLineColor(kRed);
  h_2->SetLineWidth(1.6);
  h_2->GetYaxis()->SetTitle("Fraction of Events %");
  leg->AddEntry(h_2,"Data 2010, Unpaired","L");

  TH1F* h_3 = (TH1F*)l3->Get(name3);
  h_3->SetMarkerStyle(20);
  h_3->SetLineColor(kBlue);
  h_3->SetLineWidth(1.6);
  h_3->GetYaxis()->SetTitle("Fraction of Events %");
  leg->AddEntry(h_3,"Data 2010, No Collisions","L");

  Double_t xmin = h_2->GetXaxis()->GetXmin();
  Double_t xmax = h_2->GetXaxis()->GetXmax();

  cout << "X min: " << xmin << " | X max: " << xmax << endl;

  TAxis *axis = h_2->GetXaxis();
  Int_t bin_X_min = axis->FindBin(xmin);
  Int_t bin_X_max = axis->FindBin(xmax);

  cout << "First Bin: " << bin_X_min << " | Last Bin: " << bin_X_max << endl;

  Double_t binCenter_x_min = h_2->GetBinCenter(bin_X_min);
  Double_t binCenter_x_max = h_2->GetBinCenter(bin_X_max);

  int entries=0;
  for (int i = 0; i<= bin_X_max; i++){
    entries += h_2->GetBinContent(i);
  }

  int porcentage = 0.99*entries;
  int count =0;

  cout << "Total Entries: " << entries << endl;
  cout << "Porcentage: " << porcentage << endl;

  Double_t value_limit_95;

  for (int i=0; i<= bin_X_max; i++){

    count += h_2->GetBinContent(i);
    cout << "Count[" << i << "]: " << count << endl;

    if (count > porcentage){
      cout << "Passed Count[" << i << "]: " << count << endl;
      value_limit_95 = axis->GetBinCenter(i);
      break;
    }
  }

  Double_t maxvalue = h_2->GetMaximum();
  c1->Update();

  TLine *line = new TLine(value_limit_95,0,value_limit_95,maxvalue);
  line->SetLineColor(8);
  line->SetLineWidth(3);

  h_1->Scale(100./h_1->GetEntries());
  h_2->Scale(100./h_2->GetEntries());
  h_3->Scale(100./h_3->GetEntries());

  h_2->Draw("histo");
  h_1->Draw("psame");
  h_3->Draw("histosame");
  leg->Draw("same");
  gPad->RedrawAxis();

  if (swtmsg){
    text1 = new TLatex(5.0,10.0,"Castor Pedestals");
    text1->SetNDC();
    text1->SetTextAlign(13);
    text1->SetX(0.5);
    text1->SetY(0.5);
    text1->SetTextFont(42);
    text1->SetTextSizePixels(24);// dflt=28
    text1->Draw();
  }

  c1->SaveAs(name+TString(".png"));

}

//
// Draw Castor Noise with Different Run Ranges
//

void NoiseDifferentPeriods(TString name,bool logscale){

  gStyle->SetOptStat(0);

  // Data
  TFile *l1  = TFile::Open("histo_Castor_threshold_p1_unpaired.root");
  TFile *l2  = TFile::Open("histo_Castor_threshold_p2_unpaired.root");
  TFile *l3  = TFile::Open("histo_Castor_threshold_p3_unpaired.root");

  TCanvas* c1 = new TCanvas(name,name);
  c1->cd()->SetRightMargin(0.04);

  TLegend* leg = new TLegend(0.696, 0.35, 0.94, 0.92);
  leg->SetBorderSize(0);
  leg->SetLineStyle(0);
  leg->SetTextFont(42);
  leg->SetFillStyle(0);
  leg->SetFillColor(0);

  TString name1 = name + "_unpaired";
  TString name2 = name + "_unpaired";
  TString name3 = name + "_unpaired";

  if(logscale) c1->SetLogy(1);

  TH1F* h_1 = (TH1F*)l1->Get(name1);
  h_1->SetMarkerStyle(20);
  h_1->SetMarkerColor(kBlack);
  h_1->GetYaxis()->SetTitle("Fraction of Events %");
  leg->AddEntry(h_1,"Run 136035-138559","L");

  TH1F* h_2 = (TH1F*)l2->Get(name2);
  h_2->SetMarkerStyle(20);
  h_2->SetLineColor(kRed);
  h_2->SetLineWidth(1.6);
  h_2->GetYaxis()->SetTitle("Fraction of Events %");
  leg->AddEntry(h_2,"Run 138560-141955","L");

  TH1F* h_3 = (TH1F*)l3->Get(name3);
  h_3->SetMarkerStyle(20);
  h_3->SetLineColor(kBlue);
  h_3->SetLineWidth(1.6);
  h_3->GetYaxis()->SetTitle("Fraction of Events %");
  leg->AddEntry(h_3,"Run 141956-149291","L");

  Double_t xmin = h_2->GetXaxis()->GetXmin();
  Double_t xmax = h_2->GetXaxis()->GetXmax();

  cout << "X min: " << xmin << " | X max: " << xmax << endl;

  TAxis *axis = h_2->GetXaxis();
  Int_t bin_X_min = axis->FindBin(xmin);
  Int_t bin_X_max = axis->FindBin(xmax);

  cout << "First Bin: " << bin_X_min << " | Last Bin: " << bin_X_max << endl;

  Double_t binCenter_x_min = h_2->GetBinCenter(bin_X_min);
  Double_t binCenter_x_max = h_2->GetBinCenter(bin_X_max);

  int entries=0;
  for (int i = 0; i<= bin_X_max; i++){
    entries += h_2->GetBinContent(i);
  }

  int porcentage = 0.99*entries;
  int count =0;

  cout << "Total Entries: " << entries << endl;
  cout << "Porcentage: " << porcentage << endl;

  Double_t value_limit_95;

  for (int i=0; i<= bin_X_max; i++){

    count += h_2->GetBinContent(i);
    cout << "Count[" << i << "]: " << count << endl;

    if (count > porcentage){
      cout << "Passed Count[" << i << "]: " << count << endl;
      value_limit_95 = axis->GetBinCenter(i);
      break;
    }
  }

  Double_t maxvalue = h_2->GetMaximum();
  c1->Update();

  TLine *line = new TLine(value_limit_95,0,value_limit_95,maxvalue);
  line->SetLineColor(8);
  line->SetLineWidth(3);

  h_1->Scale(100./h_1->GetEntries());
  h_2->Scale(100./h_2->GetEntries());
  h_3->Scale(100./h_3->GetEntries());

  h_2->Draw("histo");
  h_1->Draw("histosame");
  h_3->Draw("histosame");
  leg->Draw("same");
  gPad->RedrawAxis();
  line->Draw();

  c1->SaveAs(name+TString(".png"));

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
