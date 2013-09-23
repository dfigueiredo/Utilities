/*

Program: ShowBadChannels
Goal: Create file with list of bad Castor channels.
Project: Diffractive Z Analysis
Created: 22th September, 2013.

How to Execute:

> root -l ShowBadChannels.C

*/
 
#include <iostream>
#include <fstream>

void ShowBadChannels(){
  CreateList("histo_Electron_Reco.root","log","auto","electron", "TH1");
}


void CreateList(){

 std::ofstream outstring("ListOfHistograms.txt");

 outstring << "" << std::endl;
 outstring << "<< List of bad CASTOR channels >>" << std::endl;
 outstring << " " << std::endl;

 TFile *l1  = TFile::Open("ZeroBiasA.root");
 TH1F* h_1 = (TH1F*)l1->Get("diffractiveZAnalysisTTreeAfter/CastorChannelWorking");
    
    for (j=1; j<=h_1->GetNbinsX(); j++){
            outstring << "Channel: " << j << h_1->GetBinContent(j) << endl;
    }
    
 outstring.close();

}
