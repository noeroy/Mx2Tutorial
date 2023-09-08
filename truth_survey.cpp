//to be ran somewhere where duneanaobj is installed.
#include "duneanaobj/StandardRecord/StandardRecord.h"

void truth_survey()
{
    auto sr = new caf::StandardRecord();
    TFile * my_file = TFile::Open("CAFS_MR4_00084.root");
    TTree * cafTree = (TTree*) my_file->Get("cafTree");
    cafTree->SetBranchAddress("rec",&sr);
    cafTree->GetEntry(0);
    cout<<"True particle stored"<<endl;
    for (auto const& nu : sr->mc.nu) //Loop over the true particles
    {
      cout<<nu.nsec<<" "<<nu.sec.size()<<endl;
      for (auto const& part : nu.sec) // Loop over the secondaries (for now I've stored every MINERvA particle in secondaries - the primaries would be filled by MLReco I assume)
      {
                std::cout<<part.pdg<<" "<<part.G4ID<<" "<<part.interaction_id<<std::endl;
      }
    }
   cout<<"Reconstructed tracks"<<endl;
   for (auto const& ixn : sr->nd.minerva.ixn) //Loop over the trigger list 
   {
     for (auto const& track : ixn.tracks) //Loop over the track list
     {
      cout<<track.E<<" "<<track.start<<" "<<track.end<<endl; // Ouputs some track information
      
      auto part_id = track.truth; // particle identification
      cout<<part_id.ixn<<" "<<part_id.part<<endl;
      auto nu = sr->mc.nu[part_id.ixn]; //true interaction 
      auto true_part = nu.sec[part_id.part]; //true particle
      cout<<"true particle: PDG "<<true_part.pdg<<" | ID "<<true_part.G4ID<<" | interaction ID "<<true_part.interaction_id<<" | parent ID "<<true_part.parent<<endl;
     }
   }
}
