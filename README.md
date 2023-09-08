# Mx2Tutorial
Minerva CAFs session tutorial


## track_plotter.cpp
Need to run the compiling macro first.
`root -l -q compile.C`

"Quick and dirty" macro to loop over tracks of MLReco and Mx2.
Can be ran on your laptop as they use the Flat caf

`root -l track_plotter.cpp`
Draws the tracks for a given trigger of both detector.
`next()` Draws the next trigger
`draw(i)` Draws trigger i


## truth_survey.cpp

"Quick and dirty" macro to look cout track details and to show how we do the truth matching.
This uses the CAF format - need to be ran on a fermilab machine and load the setup script before.
There seems to be still some memory issues in the truth filling for the CAF objects but the global reading procedure will stay the same
