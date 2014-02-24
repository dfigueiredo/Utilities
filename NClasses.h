#ifndef NClasses.h
#define NClasses.h


#include "TH1.h"
#include "TH2F.h"
#include "TString.h"
#include "TFile.h"
#include "TMath.h"
#include <fstream>

#include <iostream>
#include <algorithm>
#include <string>


class NSetLabelSize{
 public:

  NSetLabelSize(TH1 *histo,Float_t Xoffset = 0.01,Float_t Yoffset = 0.01 ,Float_t Size = 0.06)
    {
      histo->GetXaxis()->SetLabelSize(Size);
      histo->GetXaxis()->SetLabelOffset(Xoffset);
      histo->GetYaxis()->SetLabelSize(Size);
      histo->GetYaxis()->SetLabelOffset(Yoffset);
    }

  NSetLabelSize(TH2F *histo,Float_t Xoffset = 0.01,Float_t Yoffset = 0.01 ,Float_t Size = 0.06)
    {
      histo->GetXaxis()->SetLabelSize(Size);
      histo->GetXaxis()->SetLabelOffset(Xoffset);
      histo->GetYaxis()->SetLabelSize(Size);
      histo->GetYaxis()->SetLabelOffset(Yoffset);
    }
  ~NSetLabelSize() {}
};

class NSetTitleSize{
 public:

  NSetTitleSize(TH1 *histo,Float_t Xoffset = 0.7,Float_t Yoffset = 1. ,Float_t Size = 0.08)
    {
      histo->GetXaxis()->SetTitleSize(Size);
      histo->GetXaxis()->SetTitleOffset(Xoffset);
      histo->GetYaxis()->SetTitleSize(Size);
      histo->GetYaxis()->SetTitleOffset(Yoffset);
    }
  NSetTitleSize(TH2F *histo,Float_t Xoffset = 0.7,Float_t Yoffset = 1. ,Float_t Size = 0.08)
    {
      histo->GetXaxis()->SetTitleSize(Size);
      histo->GetXaxis()->SetTitleOffset(Xoffset);
      histo->GetYaxis()->SetTitleSize(Size);
      histo->GetYaxis()->SetTitleOffset(Yoffset);
    }
  ~NSetTitleSize(){}
};

Class NSetTitle{
 public:
  NSetTitle( TH1 *histo, TString Titlex, TString Titley)
    {
      histo->GetXaxis()->SetTitle(Titlex);
      histo->GetYaxis()->SetTitle(Titley);
    }
  NSetTitle( TH2F *histo, TString Titlex, TString Titley)
    {
      histo->GetXaxis()->SetTitle(Titlex);
      histo->GetYaxis()->SetTitle(Titley);
    }
  ~ NSetTitle(){}
};

class NHSetMarker{
 public:

  NHSetMarker(TH1 *histo, Color_t Color=2, Style_t Style=2, Size_t Size = 0.2)
    {
      histo->SetMarkerColor(Color);
      histo->SetMarkerStyle(Style);
      histo->SetLineColor(Color);
      histo->SetMarkerSize(Size);
    }

  NHSetMarker(TH2F *histo, Color_t Color=2, Style_t Style=2, Size_t Size = 0.2)
    {
      histo->SetMarkerColor(Color);
      histo->SetMarkerStyle(Style);
      histo->SetLineColor(Color);
      histo->SetMarkerSize(Size);
    }
  ~NHSetMarker(){}
};




class NHSetLine{
 public:

  NHSetLine(TH1 *histo, Color_t Color=2, Style_t Style=2, Size_t Size = 0.2)
    {
      histo->SetLineColor(Color);
      histo->SetLineStyle(Style);
      histo->SetLineWidth(Size);
    }
  NHSetLine(TH2F *histo, Color_t Color=2, Style_t Style=2, Size_t Size = 0.2)
    {
      histo->SetLineColor(Color);
      histo->SetLineStyle(Style);
      histo->SetLineWidth(Size);
    }

  ~NHSetLine(){}
};



class NStat{

 public:
  NStat(TH1 *histo, Int_t Flag == 0)
    {
      if (Flag ==1)
	{
	  histo->SetStats(kTRUE);
	  gStyle->SetOptStat(1111111);
	}  
      else
	histo->SetStats(0);
    }
  NStat(TH2F *histo, Int_t Flag)
    {
      if (Flag ==1)
	{
	  histo->SetStats(kTRUE);
	  gStyle->SetOptStat(1111111);
	}  
      else
	histo->SetStats(0);
    }

  ~NStat(){}
};


 
//Sum 2 MC histo to the data
class NFitMCToData{
 public:
  NFitMCToData(TH1 *Dat, TH1 *MC1, TH1 *MC2, TString Str = "Plot")  // Dat = fsig*MC1+(1-fsig)*MC2
    {
      Float_t x_min = Dat->GetXaxis()->GetXmin();
      Float_t x_max = Dat->GetXaxis()->GetXmax();


      RooRealVar x("x", Str, x_min, x_max);  


      RooDataHist MC1_in("MC1_in","MC1_in",RooArgList(x),MC1) ;
      RooDataHist Data_in("Data_in","Data_in",x,Dat);
      RooDataHist MC2_in("MC2_in","MC2_in",x,MC2) ;

      RooHistPdf PDFMC2_in("PDFMC2_in", "PDFMC2_in", RooArgList(x), MC2_in) ;
      RooHistPdf PDFMC1_in("PDFMC1_in", "PDFMC1_in", RooArgList(x), MC1_in) ;
      
      RooRealVar fsig("fsig","signal fraction",0.5,0.,1.) ;
      
      // model(x) = fsig*MC2_in(x) + (1-fsig)*MC1_in(x)
      
      RooAddPdf model("model","model",RooArgList(PDFMC2_in,PDFMC1_in),fsig) ;

      
      model.fitTo(Data_in);

      // Perform fit and save result
      RooFitResult* r = model.fitTo(Data_in,RooFit::Save()) ;
      r->Print("fsig");

      RooPlot* frame = x.frame() ;

      Data_in.plotOn(frame,  RooFit::Name("Data"),RooFit::DrawOption(" ")) ; 

      model.plotOn(frame, RooFit::Name("Fit")) ; 
      model.paramOn(frame) ; 
      // 

      model.plotOn(frame,  RooFit::Name("Pythia"), RooFit::Components(PDFMC1_in),
		   RooFit::LineColor(kBlue),RooFit::LineStyle(kDotted)) ; 
      model.plotOn(frame, RooFit::Name("Pompyt"),RooFit::Components(PDFMC2_in),
		   RooFit::LineColor(kRed),RooFit::LineStyle(kDashed)) ; 
      
      frame->Draw() ;
      frame->SetMinimum(1.);
      //      frame->SetMaximum(800.);
      frame->SetXTitle(Str);
      frame->SetTitle(Str);

       TLegend *legend = new TLegend(0.7,0.7,0.9,0.9);
       legend->SetTextFont(72);
       legend->SetTextSize(0.05);
       legend->AddEntry("Data","Data","P ");
       legend->AddEntry("Fit","Fit","L ");
       legend->AddEntry("Pythia","Pythia","L ");
       legend->AddEntry("Pompyt","Pompyt","L ");
       legend->Draw();
       
      
      
      
    }  
  ~ NFitMCToData(){}
};


class NFitPartialMCToData{
 public:
  NFitMCToData(TH1 *Dat, TH1 *MC1, TH1 *MC2, TString Str = "Plot")  // Dat = fsig*MC1+(1-fsig)*MC2
    {
      Float_t x_min = Dat->GetXaxis()->GetXmin();
      Float_t x_max = Dat->GetXaxis()->GetXmax();


      RooRealVar x("x", Str, x_min, x_max);  


      RooDataHist MC1_in("MC1_in","MC1_in",RooArgList(x),MC1) ;
      RooDataHist Data_in("Data_in","Data_in",x,Dat);
      RooDataHist MC2_in("MC2_in","MC2_in",x,MC2) ;

      RooHistPdf PDFMC2_in("PDFMC2_in", "PDFMC2_in", RooArgList(x), MC2_in) ;
      RooHistPdf PDFMC1_in("PDFMC1_in", "PDFMC1_in", RooArgList(x), MC1_in) ;
      
      RooRealVar fsig("fsig","signal fraction",0.5,0.,1.) ;
      
      model(x) = fsig*MC2_in(x) + (1-fsig)*MC1_in(x)
      
      RooAddPdf model("model","model",RooArgList(PDFMC2_in,PDFMC1_in),fsig) ;

      
      model.fitTo(Data_in);

      // Perform fit and save result
      RooFitResult* r = model.fitTo(Data_in,RooFit::Save()) ;
      r->Print("fsig");

      RooPlot* frame = x.frame() ;

      Data_in.plotOn(frame,  RooFit::Name("Data"),RooFit::DrawOption(" ")) ; 

      model.plotOn(frame, RooFit::Name("Fit")) ; 
      model.paramOn(frame) ; 
      // 

      model.plotOn(frame,  RooFit::Name("Pythia"), RooFit::Components(PDFMC1_in),
		   RooFit::LineColor(kBlue),RooFit::LineStyle(kDotted)) ; 
      model.plotOn(frame, RooFit::Name("Pompyt"),RooFit::Components(PDFMC2_in),
		   RooFit::LineColor(kRed),RooFit::LineStyle(kDashed)) ; 
      

      frame->Draw() ;
      frame->SetMinimum(1.);
      //      frame->SetMaximum(800.);
      frame->SetXTitle(Str);
      frame->SetTitle(Str);

       TLegend *legend = new TLegend(0.7,0.7,0.9,0.9);
       legend->SetTextFont(72);
       legend->SetTextSize(0.05);
       legend->AddEntry("Data","Data","P ");
       legend->AddEntry("Fit","Fit","L ");
       legend->AddEntry("Pythia","Pythia","L ");
       legend->AddEntry("Pompyt","Pompyt","L ");
       legend->Draw();
       
      
      
      
    }  
  ~ NFitPartialMCToData(){}
};

#endif
