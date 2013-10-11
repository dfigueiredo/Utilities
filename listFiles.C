void list()
{
   std::vector<std::string> lista;
/*
   TString path = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
   path.ReplaceAll("ToBeDeleted.C", "");
   path.ReplaceAll("/./", "/");
*/

   TString path = "/afs/cern.ch/work/d/dmf/public/Samples/DiffractiveZ/5_October_2013/ZeroBias/ZeroBiasA/";
   TChain chain("diffractiveZAnalysisTTreeBefore/ProcessedTree");
   TSystemDirectory dire(path, path);

   TList *files = dire.GetListOfFiles();
   TIter next(files);
   TSystemFile *file;
   TString fname;
   while((file = (TSystemFile*)next())) {
      fname = file->GetName();
      if(file->IsDirectory()) continue;
      lista.push_back(fname.Data());
   }
   for(vector<string>::iterator it = lista.begin(); it != lista.end(); it++) { 
   cout << *it << endl;
   TString file_ = *it;
   TString fullpath = path + file_;
   cout << fullpath << endl;
   chain.Add(fullpath);
   }

chain.Show(10);

}

