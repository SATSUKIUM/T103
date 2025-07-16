#define T103Ana_cxx
#include "T103Ana.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <TH1.h>

#include <TH1.h>

void T103Ana::PlotTOF()
{
    TCanvas *c1 = new TCanvas("c1", Form("TOF Plot %s", fRootFile.Data()), 800, 600);
    c1->Draw();

    fH1TOF = new TH1F("fH1TOF", Form("TOF Distribution %s", fRootFile.Data()), 100, -140, -120);
    fH1TOF->SetXTitle("TOF [ns]");
    fH1TOF->SetYTitle("Counts");

    fChain->Draw("(ltdc_utof_l[0]+ltdc_utof_r[0])/2.0 - (ltdc_t1_l[0]+ltdc_t1_r[0])/2.0>>fH1TOF");

}