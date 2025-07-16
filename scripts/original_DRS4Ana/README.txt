/*======================================================================================================
 Name:           binaryDataAnalyzer: binary2tree_sato3.C, DRS4Ana.h, DRS4Ana.C 
 Created by:     Akira Sato<sato@phys.sci.osaka-u.ac.jp>
 Date:           December 14th, 2022

 Purpose:        Example macros to analyze binary data of DRS4 Evaluation Board saved by DRSOsc.
======================================================================================================*/

How to use:

* Data taking with DRSOsc
1) Download softwares for the DRS4 Evaluation Board from the url below. And install them.
   https://www.psi.ch/en/drs/software-download
   For Mac OSX, you can download a pre-compiled package.
2) Open the DRSOsc software. Configure it as you want. Do not forget to execute time and voltage calibrations. 
3) Push the Save button on the DRSOsc window to start waveform recording. The data is saved in a binary data file.

* Make a root file from the binary data file
4) Open a terminal. Then execute the following commands.
        $ cd <Directory name ...>/binaryDataAnalyzer/macro
        $ root
        $ root[] .L binary2tree_sato3.C
        $ root[] binary2tree_sato3(<binary data file name>)
   A root file is created in the same directory as the binary data.
    ex) 
        $root[] binary2tree_sato3("../data/test001.dat")
        A created root file is ../data/test001.dat.root .

* Analyze the root file
5) Now you can make histograms with macro DRS4Ana.C. Please read the macro for the detail.
    ex)
        $ root
        $ root[] .L DRS4Ana.C
        $ root[] DRS4Ana a("../data/test001.dat.root")
        $ root[] a.PlotWaves(0,1,20) // Plot waveform from event 1 to 1+20. Click the window to see the next event.
        $ root[] a.SetPedestalTimeRange(0,50) // Set time range in ns for pedestal calculation. 
        $ root[] a.SetChargeIntegralTimeRange(80,1400) // Set time range in ns for charge integration. 
        $ root[] a.PlotChargeIntegral(0,0,0,2000) // Plot a histogram of the charge integration 





