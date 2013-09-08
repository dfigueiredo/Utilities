{

  // load some basics functions

#include "/Users/dmf/PhysicsPrograms/RootTools/saveHistograms.C"
#include "/Users/dmf/PhysicsPrograms/RootTools/NCutil.C"
#include "/Users/dmf/PhysicsPrograms/RootTools/NClasses.h"
#include "/Users/dmf/PhysicsPrograms/RootTools/plotHistsAndRatio.C"
#include "/Users/dmf/PhysicsPrograms/RootTools/plotHists.C"

  gROOT->LoadMacro("/Users/dmf/PhysicsPrograms/RootTools/styleTDR.C");
  setTDRStyle();


  // Basics styles
  gStyle->SetMarkerStyle(20);
  gStyle->SetMarkerSize(0.4);
  gStyle->SetFillColor(0);
  gStyle->SetPalette(1);
  gSystem->Load("libRooFitCore");
  gSystem->Load("libRooFit");

}


