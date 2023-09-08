# Mx2Tutorial
Minerva CAFs session tutorial


## track_plotter.cpp
Need to run the cafTree class first.
`root -l -q compile.C`

`cafTree.h` is class obtained by calling the MakeClass method on the flat caf root file, where we added an option to load a namefile and raised the container sizes to be sure we don't have any memory issue.
`track_plotter.cpp` is a "quick and dirty" macro to loop over tracks of MLReco and Mx2 and plot them in xz and yz views.
Can be ran on your laptop as they use the Flat caf. Root will complain about Genie dependancies not being loaded but it's not a issue.

`root -l track_plotter.cpp`
Draws the tracks for a given trigger of both detector.
`next()` Draws the next trigger
`draw(i)` Draws trigger i


## truth_survey.cpp

"Quick and dirty" macro to look cout track details and to show how we do the truth matching.
This uses the CAF format - need to be ran on a fermilab machine and load the setup script before.

`./setup.sh`

then

`root -l truth_survey.cpp`
it outputs first the list of true particle in the 1st trigger, with their `PDG`, `ID`, `interactionID`
then outputs the list of reco tracks in the 1st trigger, with their `Energy`, `start (x,y,z)`, `end (x,y,z)` and the true particle associated.

There seems to be still some memory issues in the truth filling for the CAF objects but the global reading procedure will stay the same
