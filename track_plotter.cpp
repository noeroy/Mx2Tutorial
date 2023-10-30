#include "cafTree.h"

TH2D * frame_xy;
TH2D * frame_zx;
TH2D * frame_zy;

cafTree * mlCaf;
cafTree * mnvCaf;
TCanvas * c;
int entry; 

void next()
{
    
    mlCaf->GetEntry(entry++);
    int mnv_entry =  mlCaf->rec_meta_nd_lar_event%500;
    mnvCaf->GetEntry(mnv_entry);

    cout<<entry-1<<" "<<mnv_entry<<endl;

    frame_zx->SetTitle(Form("Entry %i",entry-1));
    frame_zy->SetTitle(Form("Entry %i",entry-1));

    // c->cd(1);
    // frame_xy->Draw();
    c->cd(1);
    frame_zx->Draw();
    c->cd(2);
    frame_zy->Draw();
    int k =0;
    for (int inx = 0; inx < mlCaf->rec_nd_lar_dlp__length; inx++)  //Loop over the ML reco triggers
    {
        for (int tr =  0; tr < mlCaf->rec_nd_lar_dlp_ntracks[inx]; tr++) //Loop over the reconstructed tracks
        {
            double x[2] = {mlCaf->rec_nd_lar_dlp_tracks_start_x[k],mlCaf->rec_nd_lar_dlp_tracks_end_x[k]};
            double y[2] = {mlCaf->rec_nd_lar_dlp_tracks_start_y[k],mlCaf->rec_nd_lar_dlp_tracks_end_y[k]};
            double z[2] = {mlCaf->rec_nd_lar_dlp_tracks_start_z[k],mlCaf->rec_nd_lar_dlp_tracks_end_z[k]};
            TPolyLine * pxy = new TPolyLine(2,x,y);
            TPolyLine * pzx = new TPolyLine(2,z,x);
            TPolyLine * pzy = new TPolyLine(2,z,y);
            pxy->SetLineColor(kRed);
            pzx->SetLineColor(kRed);
            pzy->SetLineColor(kRed);
            // c->cd(1);
            // pxy->Draw();
            c->cd(1);
            pzx->Draw();
            c->cd(2);
            pzy->Draw();
            k+=1;
        }
    }

    k = 0;
    for (int inx = 0; inx < mnvCaf->rec_nd_minerva_ixn__length; inx++)//Loop over the Minerva triggers
    {
        for (int tr =  0; tr < mnvCaf->rec_nd_minerva_ixn_ntracks[inx]; tr++) //Loop over the reconstructed tracks
        {
            
            double x[2] = {mnvCaf->rec_nd_minerva_ixn_tracks_start_x[k],mnvCaf->rec_nd_minerva_ixn_tracks_end_x[k]};
            double y[2] = {mnvCaf->rec_nd_minerva_ixn_tracks_start_y[k],mnvCaf->rec_nd_minerva_ixn_tracks_end_y[k]};
            double z[2] = {mnvCaf->rec_nd_minerva_ixn_tracks_start_z[k],mnvCaf->rec_nd_minerva_ixn_tracks_end_z[k]};
            TPolyLine * pxy = new TPolyLine(2,x,y);
            TPolyLine * pzx = new TPolyLine(2,z,x);
            TPolyLine * pzy = new TPolyLine(2,z,y);
            pxy->SetLineColor(kBlue);
            pzx->SetLineColor(kBlue);
            pzy->SetLineColor(kBlue);
            // c->cd(1);
            // pxy->Draw();
            c->cd(1);
            pzx->Draw();
            c->cd(2);
            pzy->Draw();
            k+=1;
        }
    }

    TLegend * l = new TLegend();
    double tmp[2] = {0,0};
    TPolyLine * p0 = new TPolyLine(2,tmp,tmp);
    p0->SetLineColor(kRed);
    TPolyLine * p1 = new TPolyLine(2,tmp,tmp);
    p1->SetLineColor(kBlue);
    l->AddEntry(p0,"ML reco tracks","l");
    l->AddEntry(p1,"Minerva reco tracks","l");
    l->Draw();
}

void draw(int i)
{  
    entry =  i;
    next();
}

void track_plotter()
{   
    mlCaf = new cafTree("outputCAF_notruth_27023276_40.flat.root"); // mlCaf file
    mnvCaf = new cafTree("CAFS_MR4_00084.flat.root"); // Mx2 file that correspond

    frame_xy = new TH2D("frame_xy","frame_xy;x[cm]; y[cm]",2,-150,150,2,-450,-100); // Frames
    frame_zx = new TH2D("frame_zx","frame_zy;z[cm]; x[cm]",2,1000,2000,2,-150,150); // Frames
    frame_zy = new TH2D("frame_zy","frame_zy;z[cm]; y[cm]",2,1000,2000,2,-450,-100); // Frames


    frame_xy->SetStats(0);
    frame_zx->SetStats(0);
    frame_zy->SetStats(0);
    c = new TCanvas();
    c->Divide(1,2);

    
    entry = 0;

    next();
    
}
