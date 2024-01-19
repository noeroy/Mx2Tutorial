#include "cafTree.h"
#include "/home/nroy/noe_basic_style.h"


TH3D * frame_3D;

cafTree * myCaf;
TCanvas * c_data;
TCanvas * c_3D =new TCanvas("c_3D","c_3D",1200,700);
TPad * visio = new TPad("visioPad","visioPad",.005,.2,.75,.995);
TPad * legendPad = new TPad("legendPad","legendPad",.76,.2,1.,1.);
TPad * lower = new TPad("lowerPad","lowerPad",.005,.005,1.,0.15);
int entry; 
TLegend * l = new TLegend(.1,.1, .95,.9);
TLegend * l2 = new TLegend(.1,.1, .95,.9);


struct part
{
int pdg;
int event_id;
double E;
int g4id;
int type;
} ;

void next(bool extrapolate =false)
{
  
    l2->Clear();


    myCaf->GetEntry(entry++);
    int mnv_entry =  myCaf->rec_meta_nd_lar_event%500;
    // mnv_entry = entry;
    // myCaf->GetEntry(mnv_entry);

    cout<<entry-1<<" "<<mnv_entry<<endl;



    c_3D->cd();
    visio->cd();
    frame_3D->Draw();

    frame_3D->SetTitle(Form("Spill - %i",entry-1));

    //Drawing wireframe detectors (coordinates are approx)
    double x_nd[18] = {-66, -66, -66, 66, 66, 66, 66, 66, 66, -66, -66, -66, -66, -66, 66, 66, -66, -66};
    
    double y_nd[18] = {-330, -330, -330, -330, -330, -330, -206, -206, -206, -206, -206, -206, -330, -330, -330, -206, -206, -330} ;

    double z_nd[18] = {1235, 1366, 1235, 1235, 1366, 1235, 1235, 1366, 1235, 1235, 1366, 1235, 1235, 1366, 1366, 1366 , 1366, 1366 };


    std::vector<double> v_x_minerva, v_y_minerva, v_z_us, v_z_ds;

    double x_base[6] = {0,1050,1050,0,-1050,-1050};
    double y_base[6] = {-3900,-3300,-2040, -1450, -2060,-3300};


    double z_base_ds[2] = {1500, 1650};
    double z_base_us[2] = {1045, 1100};


    for (int i = 0; i<6; i++)
    {
        for (int j=0 ;j<3; j++)
        {
            v_x_minerva.push_back(x_base[i]/10);
            v_y_minerva.push_back(y_base[i]/10);
            v_z_us.push_back(z_base_us[j%2]);
            v_z_ds.push_back(z_base_ds[j%2]);
        }

    }

    v_x_minerva.push_back(x_base[0]/10);
    v_y_minerva.push_back(y_base[0]/10);
    v_z_us.push_back(z_base_us[0]);
    v_z_ds.push_back(z_base_ds[0]);

    for (int i = 0; i<6; i++)
    {
        v_x_minerva.push_back(x_base[i]/10);
        v_y_minerva.push_back(y_base[i]/10);
        v_z_us.push_back(z_base_us[1]);
        v_z_ds.push_back(z_base_ds[1]);
    }

    v_x_minerva.push_back(x_base[0]/10);
    v_y_minerva.push_back(y_base[0]/10);
    v_z_us.push_back(z_base_us[1]);
    v_z_ds.push_back(z_base_ds[1]);


    TPolyLine3D *mnv_ds = new TPolyLine3D(v_x_minerva.size(), &v_x_minerva[0],&v_z_us[0], &v_y_minerva[0]);
    TPolyLine3D *mnv_us = new TPolyLine3D(v_x_minerva.size(), &v_x_minerva[0],&v_z_ds[0], &v_y_minerva[0]);



    TPolyLine3D *nd_frame = new TPolyLine3D(18, x_nd,z_nd, y_nd);

    mnv_ds->SetLineStyle(2);
    mnv_us->SetLineStyle(2);
    nd_frame->SetLineStyle(2);


    mnv_ds->Draw("Lsame");
    mnv_us->Draw("Lsame");
    nd_frame->Draw("Lsame");

    

    //Getting and plotting Minerva Tracks
    int k = 0;

    
    for (int inx = 0; inx < myCaf->rec_nd_minerva_ixn__length; inx++)//Loop over the Minerva triggers
    {
        for (ULong64_t tr =  0; tr < myCaf->rec_nd_minerva_ixn_ntracks[inx]; tr++) //Loop over the reconstructed tracks
        {
            std::vector<part> ml_part;

            double x[2] = {myCaf->rec_nd_minerva_ixn_tracks_start_x[k],myCaf->rec_nd_minerva_ixn_tracks_end_x[k]};
            double y[2] = {myCaf->rec_nd_minerva_ixn_tracks_start_y[k],myCaf->rec_nd_minerva_ixn_tracks_end_y[k]};
            double z[2] = {myCaf->rec_nd_minerva_ixn_tracks_start_z[k],myCaf->rec_nd_minerva_ixn_tracks_end_z[k]};
            double xyz[6]  = {myCaf->rec_nd_minerva_ixn_tracks_start_x[k],myCaf->rec_nd_minerva_ixn_tracks_start_z[k],myCaf->rec_nd_minerva_ixn_tracks_start_y[k]
                              , myCaf->rec_nd_minerva_ixn_tracks_end_x[k],myCaf->rec_nd_minerva_ixn_tracks_end_z[k],myCaf->rec_nd_minerva_ixn_tracks_end_y[k]};
            TPolyLine * pxy = new TPolyLine(2,x,y);
            TPolyLine * pzx = new TPolyLine(2,z,x);
            TPolyLine * pzy = new TPolyLine(2,z,y);
            TPolyLine3D * p3D = new TPolyLine3D(2,x,z,y);
            pxy->SetLineColor(cblue);
            pzx->SetLineColor(cblue);
            pzy->SetLineColor(cblue);
            p3D->SetLineColor(cblue);
            p3D->SetLineWidth(2);
            // c->cd(1);
            // pxy->Draw();

            c_3D->cd();
            visio->cd();
            p3D->Draw();

            //Find truth

            int t_ixn = myCaf->rec_nd_minerva_ixn_tracks_truth_ixn[k];
            int t_part = myCaf->rec_nd_minerva_ixn_tracks_truth_part[k];
            int t_type = myCaf->rec_nd_minerva_ixn_tracks_truth_type[k];
            int tot_id = t_part + myCaf->rec_mc_nu_prim__idx[t_ixn];

            part my_part;
            if (t_type == 1)
            {
                my_part.pdg = myCaf->rec_mc_nu_prim_pdg[tot_id];
                my_part.event_id = myCaf->rec_mc_nu_prim_interaction_id[tot_id]%1000000;
                my_part.E = myCaf->rec_mc_nu_prim_p_E[tot_id];
                my_part.g4id = myCaf->rec_mc_nu_prim_G4ID[tot_id];
                my_part.type = myCaf->rec_nd_minerva_ixn_tracks_truth_type[k];
            }
            else
            {
                my_part.pdg = myCaf->rec_mc_nu_sec_pdg[tot_id];
                my_part.event_id = myCaf->rec_mc_nu_sec_interaction_id[tot_id]%1000000;
                my_part.E = myCaf->rec_mc_nu_sec_p_E[tot_id];
                my_part.g4id = myCaf->rec_mc_nu_sec_G4ID[tot_id];
                my_part.type = myCaf->rec_nd_minerva_ixn_tracks_truth_type[k];
            }

            ml_part.push_back(my_part);


            TPolyMarker3D * m3D = new TPolyMarker3D(2,xyz);
            m3D->SetMarkerStyle(20+k);
            m3D->SetMarkerColor(cblue);
            m3D->Draw();
            // c_3D->cd();
            TString p_data = "(PDG, Energy, EventId, Type)";
            for (auto p :  ml_part)
            {
                p_data += Form (" (%i, %.2f, %i, %i)", p.pdg, p.E, p.event_id, p.type);
                p_data += Form(" || G4ID: %i",p.g4id);
            }
            

            l2->AddEntry(m3D,p_data,"p");



            k+=1;
        }
    }
    
    k = 0;

    std::map<int,std::vector<part>> ml_marker_part;
    //Looping over the MLreco reco object to find tracks 
    for (int inx = 0; inx < myCaf->rec_common_ixn_dlp__length; inx++)
    {
       
    
        for (int tr =  0; tr < myCaf->rec_common_ixn_dlp_part_dlp__length[inx]; tr++) 
        {
             std::vector<part> ml_part;

            if (int(myCaf->rec_common_ixn_dlp_part_dlp_primary[k]) !=1) 
            {
                k+=1;
                continue;
            }

            double x[2] = {myCaf->rec_common_ixn_dlp_part_dlp_start_x[k],myCaf->rec_common_ixn_dlp_part_dlp_end_x[k]};
            double y[2] = {myCaf->rec_common_ixn_dlp_part_dlp_start_y[k],myCaf->rec_common_ixn_dlp_part_dlp_end_y[k]};
            double z[2] = {myCaf->rec_common_ixn_dlp_part_dlp_start_z[k],myCaf->rec_common_ixn_dlp_part_dlp_end_z[k]};
            double xyz[6]  = {myCaf->rec_common_ixn_dlp_part_dlp_start_x[k],myCaf->rec_common_ixn_dlp_part_dlp_start_z[k],myCaf->rec_common_ixn_dlp_part_dlp_start_y[k]
                              , myCaf->rec_common_ixn_dlp_part_dlp_end_x[k],myCaf->rec_common_ixn_dlp_part_dlp_end_z[k],myCaf->rec_common_ixn_dlp_part_dlp_end_y[k]};

           

            //Find associated truth
            
            for (int t_id = myCaf->rec_common_ixn_dlp_part_dlp_truth__idx[k]; t_id < myCaf->rec_common_ixn_dlp_part_dlp_truth__idx[k]+myCaf->rec_common_ixn_dlp_part_dlp_truth__length[k]; t_id++)
            {
                int t_ixn = myCaf->rec_common_ixn_dlp_part_dlp_truth_ixn[t_id];
                int t_part = myCaf->rec_common_ixn_dlp_part_dlp_truth_part[t_id];
                int t_type = myCaf->rec_common_ixn_dlp_part_dlp_truth_type[t_id];
                if (myCaf->rec_common_ixn_dlp_part_dlp_truthOverlap[t_id] < .1) continue;
                part my_part;
                if (t_type == 1)
                {
                    int tot_id = t_part + myCaf->rec_mc_nu_prim__idx[t_ixn];
                    
                    my_part.pdg = myCaf->rec_mc_nu_prim_pdg[tot_id];
                    my_part.event_id = myCaf->rec_mc_nu_prim_interaction_id[tot_id]%1000000;
                    my_part.E = myCaf->rec_mc_nu_prim_p_E[tot_id];
                    my_part.g4id = myCaf->rec_mc_nu_prim_G4ID[tot_id];
                    my_part.type = t_type;
                }
                else
                {
                    int tot_id = t_part + myCaf->rec_mc_nu_sec__idx[t_ixn];
                    
                    my_part.pdg = myCaf->rec_mc_nu_sec_pdg[tot_id];
                    my_part.event_id = myCaf->rec_mc_nu_sec_interaction_id[tot_id]%1000000;
                    my_part.E = myCaf->rec_mc_nu_sec_p_E[tot_id];
                    my_part.g4id = myCaf->rec_mc_nu_sec_G4ID[tot_id];
                    my_part.type = t_type;
                }
                ml_part.push_back(my_part);
                
                
            }
            


            TPolyLine * pxy = new TPolyLine(2,x,y);
            TPolyLine * pzx = new TPolyLine(2,z,x);
            TPolyLine * pzy = new TPolyLine(2,z,y);
            TPolyLine3D * p3D = new TPolyLine3D(2,x,z,y);
            pxy->SetLineColor(cred);
            pzx->SetLineColor(cred);
            pzy->SetLineColor(cred);
            p3D->SetLineColor(cred);
            p3D->SetLineWidth(2);


            c_3D->cd();
            visio->cd();
            p3D->Draw();

            TPolyMarker3D * m3D = new TPolyMarker3D(2,xyz);
            m3D->SetMarkerStyle(20+k);
            m3D->SetMarkerColor(cred);
            m3D->Draw();

            ml_marker_part[20+k] = ml_part;
            // c_3D->cd();
            TString p_data = "(PDG, Energy, EventId, Type)";
            for (auto p :  ml_part)
            {
                p_data += Form (" (%i, %.2f, %i, %i)", p.pdg, p.E, p.event_id, p.type);
                p_data += Form(" || G4ID: %i",p.g4id);
            }
            
            l2->AddEntry(m3D,p_data,"p");

            


            if (extrapolate)
            {

                double dx = x[1]-x[0];
                double dy = y[1]-y[0];
                double dz = z[1]-z[0];

                double norm = sqrt(dx*dx+dy*dy+dz*dz);

                dx /= norm;
                dy /= norm;
                dz /= norm;

                double t0 = (1045 - z[0]) / dz;
                double t1 = (1650 - z[0]) / dz;

                double ex_x[2] = {x[0] + dx * t0,  x[0] + dx * t1  };
                double ex_y[2] = {y[0] + dy * t0,  y[0] + dy * t1  };
                double ex_z[2] = {1045,1650};
                TPolyLine3D * ex_p3D = new TPolyLine3D(2,ex_x,ex_z,ex_y);
                std::cout<<" - "<<ex_x[0]<<" "<<ex_y[0]<<" "<<ex_z[0]<<" "<<ex_x[1]<<" "<<ex_y[1]<<" "<<ex_z[1]<<endl;
                ex_p3D->SetLineColor(cred);
                ex_p3D->SetLineStyle(2);
                ex_p3D->Draw("Lsame");                
            }
            k+=1;
        }
    }

    legendPad->cd();
    l->Clear();
    // l = new TLegend();

    double tmp[2] = {0,0};
    TPolyLine * p0 = new TPolyLine(2,tmp,tmp);
    p0->SetLineColor(cred);
    TPolyLine * p1 = new TPolyLine(2,tmp,tmp);
    p1->SetLineColor(cblue);

    p0->SetLineWidth(2);
    p1->SetLineWidth(2);  
    l->AddEntry(p0,"ML reco tracks","l");

    if (extrapolate)
    {
        TPolyLine * pext = new TPolyLine(2,tmp,tmp);
        pext->SetLineColor(cred);
        pext->SetLineStyle(2);
        l->AddEntry(pext,"Extrapolated track","l");
    }

    l->AddEntry(p1,"Minerva reco tracks","l");


    l->SetTextSize(0.07);
    l->Draw();

    c_data->cd();
    l2->Draw();

}


void extrapolate(bool extrap = true)
{
    entry -= 1;
    next(extrap);
}

void draw(int i)
{  
    entry =  i;
    next();
}

void track_plotter_merged()
{   
    myCaf = new cafTree("/home/nroy/DUNE/root_minerva/picorun4.1/merged_caf/PicoRun4.1_1E17_RHC.larnd.00000.caf.flat.root");


    frame_3D = new TH3D("frame_3D","frame_3D;x[cm];z[cm]; y[cm]",2, -175,175,2,1000,1700,2,-450,-100 ); // Frames


    frame_3D->SetStats(0);

    c_data = new TCanvas();
    
    c_3D->cd();
    
    visio->Draw();
    legendPad->Draw();
    lower->Draw();

    entry = 0;

    next();
    
}