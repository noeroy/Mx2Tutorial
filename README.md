## track_plotter.cpp

Need to compile the cafTree class first.

`root -l -q compile.C`

  

`cafTree.h` is class obtained by calling the MakeClass method on the flat caf root file, where we added an option to load a namefile and raised the container sizes to be sure we don't have any memory issue.
Not the optimal way of working with CAFs, as Sindhu presented, `SRProxy` is a cleaner way of working with those. 

`track_plotter.cpp` is a macro that plots the Mx2 tracks and 2x2 MLreco objects in a 3D frame. 

Can be ran on your laptop as they use the Flat caf. Root will complain about GENIE dependancies not being loaded but it's not a issue.

  

`root -l track_plotter.cpp`

Draws the tracks for a given trigger of both detector.

`next()` Draws the next trigger

`draw(i)` Draws trigger i

`extrapolate()` Projects the 2x2 tracks into the Mx2 planes
  
  There is one example of merged CAFs inside the repository but the other files processed by Jeremy can be found here:  `/dune/data/users/jwolcott/nd/nd-lar-reco/caf/PicoRun4.1/2x2+MINERvA-v0/PicoRun4.1_1E17_RHC.larnd.*.caf.flat.root`