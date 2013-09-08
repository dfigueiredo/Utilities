string line;
string NameFile;
Float_t Sigma;   // = 0.051;
Float_t BlindLimit;  // = 0.05; // minimum distance to check merging of 3 vtx 
Float_t MCEff_EtaCut;
Int_t Draw; 
Float_t SelNDOF;
Int_t NTrkVtx;
Int_t PtCut;  
Int_t MCPt;
Int_t TrkEffF;
bool RunListF;  // run only on selected runs
bool LumiCorF; // use lumicorrection
Int_t MC_MigF; // use MC Migration
bool HadronF; // Correct to Hadron Level
bool DAV; // for DAV files
Int_t eeF; // for ee or mm files
Int_t SystCheck; // Syst Check
Int_t VtxMult_limit;   // Minimum Vertex Multiplicity //
Int_t MinNtracksLowpT; // Min number of tracks of LowPt
char DataFile[100] = {0};
char MigrationFile[100] = {0};
char LumiCorFile[100] = {0};
char MCMBFile[100] = {0};
char MCMigFile[100] = {0};
char MCchar[20]; 
char Vtxchar[20]; 
Float_t MinDist = 0.1;
Float_t MinSig = 0.06;
Float_t M_PI = 3.14;

// Number of PU vertices considered
 const Int_t NumPU = 10; 

//2011 Luminosity limit
//Float_t UpLim = 1.5;
//Float_t LowLim = 0.5;
//Int_t MinLumBin = 0;
//const Int_t LumBin = 10;

// 2010
Float_t UpLim = 0.7;
Float_t LumiBinWidth = 0.05; 
Int_t MinLumBin = 0;
const Int_t LumBin = 14;
Float_t LowLim = 0.;

//const Int_t RunBin = 50;
const Int_t RunBin = 56;
