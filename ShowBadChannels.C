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
  CreateList();
}


void CreateList(){

 std::ofstream outstring("ListOfBadChannels.txt");

 outstring << "" << std::endl;
 outstring << "<< List of CASTOR channels >>" << std::endl;
 outstring << " " << std::endl;
 outstring << "It shows number of times that a channel was active." << std::endl;
 outstring << "0 = Bad Channel" << std::endl;
 outstring << "" << std::endl;

 TFile *l1  = TFile::Open("ZeroBiasA.root");
 TH1F* h_1 = (TH1F*)l1->Get("diffractiveZAnalysisTTreeAfter/CastorChannelWorking");

    for (int j=2; j<=225; j++){
            outstring << "Channel(" << j-1 << "): "<< h_1->GetBinContent(j) << endl;
    }
    
 outstring.close();

}
