
void get_runs(TString namefile)
{
    gROOT->ProcessLine( "gErrorIgnoreLevel = 6001;");

    TFile * file = TFile::Open(namefile);
    TTree * cafTree = (TTree*) file->Get("cafTree");
    cafTree->Draw("rec.meta.nd_lar.event");
    double * val = cafTree->GetVal(0);
    //cout<<val[0]<<endl;
   // ofstream myfile;
    int runnumber = int(val[0])/1000;
    TString mnv_caf=Form("CAFS_MR4_%05i.root",runnumber);
    cout<<namefile<<" "<<mnv_caf<<" "<<endl;
    //myfile.open ("matching.txt",ios::app);
    //myfile <<namefile<<" "<<int(val[0])/1000<<endl;
    //myfile.close();

}
