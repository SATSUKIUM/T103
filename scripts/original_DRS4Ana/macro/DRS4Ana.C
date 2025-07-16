/*======================================================================================================
 Name:           DRS4Ana.C
 Created by:     Akira Sato<sato@phys.sci.osaka-u.ac.jp>
 Date:           December 14th, 2022

 Purpose:        Example macro to analyze a root file created by binary2tree_sato3.C

How to use:

$ root
$ root[] .L DRS4Ana.C
$ root[] DRS4Ana a(<root file name>)
         ex) root[] DRS4Ana a("../data/test001.dat.root")
$ root[] a.PlotWaves()
$ root[] a.PlotChargeIntegral()

Please read the macro for the detail.
======================================================================================================*/

#define DRS4Ana_cxx
#include "DRS4Ana.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

void DRS4Ana::PlotADCSum(Int_t iCh)
{
    gStyle->SetOptStat(0);
    TCanvas *c_adcsum = new TCanvas("c_adcsum",
                                    Form("%s:ch%d ADCsum", fRootFile.Data(), iCh),
                                    800, 400);
    c_adcsum->Draw();

    if (fH1AdcSum != NULL)
    {
        delete fH1AdcSum;
    }
    fH1AdcSum = new TH1F("fH1AdcSum",
                         Form("%s:ch%d ADCsum", fRootFile.Data(), iCh),
                         1000, fADCsumXmin, fADCsumXmax);
    fH1AdcSum->SetXTitle("ADCsum");
    fH1AdcSum->SetYTitle("[count]");
    fChain->Draw(Form("adcSum[0][%d]>>fH1AdcSum", iCh));

    // c_adcsum->Print(Form("%s_ch%d_adcSum.pdf", fRootFile.Data(), iCh));
}

void DRS4Ana::PlotWave(Int_t iCh, Int_t EventID)
{
    gStyle->SetOptStat(0);

    if (fH2Waveform != NULL)
    {
        delete fH2Waveform;
    }

    fH2Waveform = new TH2F("fH2Waveform",
                           Form("%s:ch%d,Ev%d", fRootFile.Data(), iCh, EventID),
                           10, fWaveformXmin, fWaveformXmax, 10, fWaveformYmin, fWaveformYmax);
    fH2Waveform->SetXTitle("Time [ns]");
    fH2Waveform->SetYTitle("Voltage [V]");
    fH2Waveform->Draw();
    fChain->Draw(Form("waveform[0][%d]:%f*Iteration$", iCh, fTimeBinWidthInNanoSec), "", "lsame", 1, EventID);
}

void DRS4Ana::PlotWaves(Int_t iCh, Int_t EventID, Int_t nEvent)
{
    TCanvas *c_wave = new TCanvas("c_canvas", fRootFile.Data(), 800, 600);
    c_wave->Draw();

    for (Int_t i = 0; i < nEvent; i++)
    {
        PlotWave(iCh, EventID + i);
        c_wave->WaitPrimitive();
    }
}

void DRS4Ana::SetWaveRangeX(Double_t min, Double_t max)
{
    fWaveformXmin = min;
    fWaveformXmax = max;
}

void DRS4Ana::SetWaveRangeY(Double_t min, Double_t max)
{
    fWaveformYmin = min;
    fWaveformYmax = max;
}

void DRS4Ana::SetPedestalTimeRange(Double_t min, Double_t max)
{
    fPedestalTmin = min;
    fPedestalTmax = max;
}

void DRS4Ana::SetChargeIntegralTimeRange(Double_t min, Double_t max)
{
    fChargeIntegralTmin = min;
    fChargeIntegralTmax = max;
}

Double_t DRS4Ana::GetMinVoltage(Int_t iCh)
{
    Double_t minV = 100.0;
    for (Int_t i = 0; i < 1024; i++)
    {
        if (fWaveform[0][iCh][i] < minV)
        {
            // printf("%d:%f\n",i,waveform[0][iCh][i]);
            minV = (Double_t)fWaveform[0][iCh][i];
        }
    }
    return minV;
}

Double_t DRS4Ana::GetAbsMaxVoltage(Int_t iCh)
{
    Double_t maxAbsV = 0.0;
    for (Int_t i = 0; i < 1024; i++)
    {
        if (fWaveform[0][iCh][i] < -maxAbsV)
        {
            // printf("%d:%f\n",i,fWaveform[0][iCh][i]);
            maxAbsV = -(Double_t)fWaveform[0][iCh][i];
        }
    }
    // cout << "Debug: GetMaxVoltage passed." << endl;
    return maxAbsV;
}

Double_t DRS4Ana::GetMaxVoltage(Int_t iCh)
{
    Double_t maxV = -100.0;
    for (Int_t i = 0; i < 1024; i++)
    {
        if (fWaveform[0][iCh][i] > maxV)
        {
            // printf("%d:%f\n",i,waveform[0][iCh][i]);
            maxV = (Double_t)fWaveform[0][iCh][i];
        }
    }
    return maxV;
}

Double_t DRS4Ana::GetPedestal(Int_t iCh, Double_t Vcut)
{
    if (fSignalPolarity == 1)
    {
        if (GetMaxVoltage(iCh) <= Vcut)
        {
            return -9999.9;
        }
    }
    else
    {
        if (GetMinVoltage(iCh) >= Vcut)
        {
            return -9999.9;
        }
    }

    Double_t pedestalV = 0.0;
    Int_t counter = 0;
    for (Int_t i = 0; i < 1024; i++)
    {
        if (fTime[0][iCh][i] >= fPedestalTmin && fTime[0][iCh][i] <= fPedestalTmax)
        {
            counter++;
            pedestalV += fWaveform[0][iCh][i];
        }
    }
    return pedestalV / counter;
}

Double_t DRS4Ana::GetPedestalMean(Int_t iCh, Double_t Vcut)
{
    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t counter = 0;
    Double_t pedMean = 0.0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
        fChain->GetEntry(jentry);
        Double_t ped = GetPedestal(iCh, Vcut);
        if (ped > -9999.9)
        {
            counter++;
            pedMean += ped;
        }
    }
    return pedMean / counter;
}

Double_t DRS4Ana::PlotPedestalMean(Int_t iCh, Double_t Vcut)
{
    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t counter = 0;
    Double_t pedMean = 0.0;

    if (fH1Pedestal != NULL)
    {
        delete fH1Pedestal;
    }
    fH1Pedestal = new TH1F("fH1Pedestal", Form("%s:ch%d Pedestal", fRootFile.Data(), iCh),
                           1000, -0.01, 0.01);
    fH1Pedestal->SetXTitle("Voltage [V]");
    fH1Pedestal->SetYTitle("[counts]");

    for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
        fChain->GetEntry(jentry);
        Double_t ped = GetPedestal(iCh, Vcut);
        if (ped > -9999.9)
        {
            counter++;
            pedMean += ped;
            fH1Pedestal->Fill(ped);
        }
    }
    fH1Pedestal->Draw();
    return pedMean / counter;
}

// Double_t DRS4Ana::GetChargeIntegral(Int_t iCh, Double_t Vcut)
// {
//     if (fSignalPolarity == 1)
//     {
//         if (GetMaxVoltage(iCh) <= Vcut)
//         {
//             return -9999.9;
//         }
//     }
//     else
//     {
//         if (GetMinVoltage(iCh) >= Vcut)
//         {
//             return -9999.9;
//         }
//     }

//     Double_t pedestal = GetPedestal(iCh, Vcut);

//     Double_t charge = 0.0;
//     for (Int_t i = 0; i < 1024; i++)
//     {
//         if (fTime[0][iCh][i] >= fChargeIntegralTmin && fTime[0][iCh][i] <= fChargeIntegralTmax)
//         {
//             charge += fWaveform[0][iCh][i] - pedestal;
//         }
//     }
//     return charge;
// }

Double_t DRS4Ana::GetChargeIntegral(Int_t iCh, Double_t Vcut)
{
    if (fSignalPolarity == 1)
    {
        if (GetMaxVoltage(iCh) <= Vcut)
        {
            return -9999.9;
        }
    }
    else
    {
        if (GetMinVoltage(iCh) >= Vcut)
        {
            return -9999.9;
        }
    }

    Double_t pedestal = GetPedestal(iCh, Vcut);

    Double_t charge = 0.0;
    for (Int_t i = 0; i < 1024; i++)
    {
        if (fTime[0][iCh][i] >= fChargeIntegralTmin && fTime[0][iCh][i] <= fChargeIntegralTmax)
        {
            charge += fWaveform[0][iCh][i] - pedestal;
        }
    }
    return charge;
}


Double_t DRS4Ana::PlotChargeIntegral(Int_t iCh, Double_t Vcut, Double_t xmin, Double_t xmax)
{
    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t counter = 0;

    if (fH1ChargeIntegral != NULL)
    {
        delete fH1ChargeIntegral;
    }
    fH1ChargeIntegral = new TH1F("fH1ChargeIntegral", Form("%s:ch%d Charge Integral [%.1f,%.1f]", fRootFile.Data(), iCh, fChargeIntegralTmin, fChargeIntegralTmax),
                                 50, xmin, xmax);
    fH1ChargeIntegral->SetXTitle("voltage sum [V]");
    fH1ChargeIntegral->SetYTitle("[counts]");

    for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
        fChain->GetEntry(jentry);
        Double_t chargeIntegral = GetChargeIntegral(iCh, Vcut);
        if (chargeIntegral > -9999.9)
        {
            counter++;
            //元のコード
            // fH1ChargeIntegral->Fill(chargeIntegral);
            //PMTのパルスは負極性だからマイナスを付けた
            fH1ChargeIntegral->Fill(1.0*(-chargeIntegral)+0.0);
            if(chargeIntegral > -1e10-3 && chargeIntegral < 1e10-3){
                std::cout << "Debug : chaegeIntegral = " << chargeIntegral << std::endl;
                std::cout << jentry << std::endl;
            }
            // cout << "Debug : success" << endl;
        }
        else{
            std::cout << "Debug : chargeIntegral: " << chargeIntegral << std::endl;
        }
    }
    // fH1ChargeIntegral->SetMinimum(0);
    // fH1ChargeIntegral->SetMaximum(800);

    // gPad->SetGrid(1, 1);
    fH1ChargeIntegral->Draw();

    // // 第1のピークに対するフィッティング
    // TF1 *fitFunc1 = new TF1("fitFunc1", "gaus", 21.5, 24); // 適切な範囲を設定
    // fitFunc1->SetParameters(150, 22.5, 3); // 初期パラメータ（例）
    // fH1ChargeIntegral->Fit(fitFunc1, "R"); // "R"は指定した範囲内でフィッティング

    // // 第1のフィッティング結果を取得
    // double mean1 = fitFunc1->GetParameter(1);
    // double sigma1 = fitFunc1->GetParameter(2);
    // std::cout << "Peak 1 - Mean: " << mean1 << ", Sigma: " << sigma1 << std::endl;

    // // 第2のピークに対するフィッティング
    // TF1 *fitFunc2 = new TF1("fitFunc2", "gaus", 24.5, 27); // 第2ピークに対する範囲
    // fitFunc2->SetParameters(125, 26, 3); // 初期パラメータ
    // fH1ChargeIntegral->Fit(fitFunc2, "R");

    // // 第2のフィッティング結果を取得
    // double mean2 = fitFunc2->GetParameter(1);
    // double sigma2 = fitFunc2->GetParameter(2);
    // std::cout << "Peak 2 - Mean: " << mean2 << ", Sigma: " << sigma2 << std::endl;

    // // 両方のフィット結果を描画（ヒストグラムに重ねる）
    // fitFunc1->Draw("same");
    // fitFunc2->Draw("same");

    // // // PNG形式で保存
    // fH1ChargeIntegral->SaveAs("../../../figure/22Na_fit.png");

    // // PDF形式で保存
    // fH1ChargeIntegral->SaveAs("../../../figure/22Na_fit.pdf");


    //22Naのフィッティング
    // // 第1のピークに対するフィッティング
    // TF1 *fitFunc1 = new TF1("fitFunc1", "gaus", 23, 27); // 適切な範囲を設定
    // fitFunc1->SetParameters(150, 24, 10); // 初期パラメータ（例）
    // fH1ChargeIntegral->Fit(fitFunc1, "R"); // "R"は指定した範囲内でフィッティング

    // // 第1のフィッティング結果を取得
    // double mean1 = fitFunc1->GetParameter(1);
    // double sigma1 = fitFunc1->GetParameter(2);
    // std::cout << "Peak 1 - Mean: " << mean1 << ", Sigma: " << sigma1 << std::endl;

    // // 第2のピークに対するフィッティング
    // TF1 *fitFunc2 = new TF1("fitFunc2", "gaus", 8, 12); // 第2ピークに対する範囲
    // fitFunc2->SetParameters(500, 10, 3); // 初期パラメータ
    // fH1ChargeIntegral->Fit(fitFunc2, "R");

    // // 第2のフィッティング結果を取得
    // double mean2 = fitFunc2->GetParameter(1);
    // double sigma2 = fitFunc2->GetParameter(2);
    // std::cout << "Peak 2 - Mean: " << mean2 << ", Sigma: " << sigma2 << std::endl;

    // // 両方のフィット結果を描画（ヒストグラムに重ねる）
    // fitFunc1->Draw("same");
    // fitFunc2->Draw("same");

    // // // PNG形式で保存
    // fH1ChargeIntegral->SaveAs("../../../figure/22Na_fit.png");

    // // PDF形式で保存
    // fH1ChargeIntegral->SaveAs("../../../figure/22Na_fit.pdf");

    // // cout << "counter: " << counter << endl; 
    return (Double_t)counter;
}
// Double_t DRS4Ana::PlotChargeIntegral(Int_t iCh, Double_t Vcut, Double_t xmin, Double_t xmax)
// {
//     Long64_t nentries = fChain->GetEntriesFast();
//     Long64_t counter = 0;

//     if (fH1ChargeIntegral != NULL)
//     {
//         delete fH1ChargeIntegral;
//     }
//     fH1ChargeIntegral = new TH1F("fH1ChargeIntegral", Form("%s:ch%d Charge Integral [%.1f,%.1f]", fRootFile.Data(), iCh, fChargeIntegralTmin, fChargeIntegralTmax),
//                                  50, xmin, xmax);
//     fH1ChargeIntegral->SetXTitle("Energe [keV]");
//     fH1ChargeIntegral->SetYTitle("[counts]");

//     for (Long64_t jentry = 0; jentry < nentries; jentry++)
//     {
//         fChain->GetEntry(jentry);
//         Double_t chargeIntegral = GetChargeIntegral(iCh, Vcut);
//         if (chargeIntegral > -9999.9)
//         {
//             counter++;
//             //元のコード
//             // fH1ChargeIntegral->Fill(chargeIntegral);
//             //PMTのパルスは負極性だからマイナスを付けた
//             fH1ChargeIntegral->Fill(52.926*(-chargeIntegral)-1.1751);
//             if(chargeIntegral > -1e10-3 && chargeIntegral < 1e10-3){
//                 cout << "Debug : chaegeIntegral = " << chargeIntegral << endl;
//                 cout << jentry << endl;
//             }
//             // cout << "Debug : success" << endl;
//         }
//         else{
//             cout << "Debug : chargeIntegral: " << chargeIntegral << endl;
//         }
//     }
//     // fH1ChargeIntegral->SetMinimum(0);
//     // fH1ChargeIntegral->SetMaximum(800);

//     // gPad->SetGrid(1, 1);
//     fH1ChargeIntegral->Draw();

//     // // 第1のピークに対するフィッティング
//     // TF1 *fitFunc1 = new TF1("fitFunc1", "gaus", 21.5, 24); // 適切な範囲を設定
//     // fitFunc1->SetParameters(150, 22.5, 3); // 初期パラメータ（例）
//     // fH1ChargeIntegral->Fit(fitFunc1, "R"); // "R"は指定した範囲内でフィッティング

//     // // 第1のフィッティング結果を取得
//     // double mean1 = fitFunc1->GetParameter(1);
//     // double sigma1 = fitFunc1->GetParameter(2);
//     // std::cout << "Peak 1 - Mean: " << mean1 << ", Sigma: " << sigma1 << std::endl;

//     // // 第2のピークに対するフィッティング
//     // TF1 *fitFunc2 = new TF1("fitFunc2", "gaus", 24.5, 27); // 第2ピークに対する範囲
//     // fitFunc2->SetParameters(125, 26, 3); // 初期パラメータ
//     // fH1ChargeIntegral->Fit(fitFunc2, "R");

//     // // 第2のフィッティング結果を取得
//     // double mean2 = fitFunc2->GetParameter(1);
//     // double sigma2 = fitFunc2->GetParameter(2);
//     // std::cout << "Peak 2 - Mean: " << mean2 << ", Sigma: " << sigma2 << std::endl;

//     // // 両方のフィット結果を描画（ヒストグラムに重ねる）
//     // fitFunc1->Draw("same");
//     // fitFunc2->Draw("same");

//     // // // PNG形式で保存
//     // fH1ChargeIntegral->SaveAs("../../../figure/22Na_fit.png");

//     // // PDF形式で保存
//     // fH1ChargeIntegral->SaveAs("../../../figure/22Na_fit.pdf");


//     //22Naのフィッティング
//     // // 第1のピークに対するフィッティング
//     // TF1 *fitFunc1 = new TF1("fitFunc1", "gaus", 23, 27); // 適切な範囲を設定
//     // fitFunc1->SetParameters(150, 24, 10); // 初期パラメータ（例）
//     // fH1ChargeIntegral->Fit(fitFunc1, "R"); // "R"は指定した範囲内でフィッティング

//     // // 第1のフィッティング結果を取得
//     // double mean1 = fitFunc1->GetParameter(1);
//     // double sigma1 = fitFunc1->GetParameter(2);
//     // std::cout << "Peak 1 - Mean: " << mean1 << ", Sigma: " << sigma1 << std::endl;

//     // // 第2のピークに対するフィッティング
//     // TF1 *fitFunc2 = new TF1("fitFunc2", "gaus", 8, 12); // 第2ピークに対する範囲
//     // fitFunc2->SetParameters(500, 10, 3); // 初期パラメータ
//     // fH1ChargeIntegral->Fit(fitFunc2, "R");

//     // // 第2のフィッティング結果を取得
//     // double mean2 = fitFunc2->GetParameter(1);
//     // double sigma2 = fitFunc2->GetParameter(2);
//     // std::cout << "Peak 2 - Mean: " << mean2 << ", Sigma: " << sigma2 << std::endl;

//     // // 両方のフィット結果を描画（ヒストグラムに重ねる）
//     // fitFunc1->Draw("same");
//     // fitFunc2->Draw("same");

//     // // // PNG形式で保存
//     // fH1ChargeIntegral->SaveAs("../../../figure/22Na_fit.png");

//     // // PDF形式で保存
//     // fH1ChargeIntegral->SaveAs("../../../figure/22Na_fit.pdf");

//     // // cout << "counter: " << counter << endl; 
//     return (Double_t)counter;
// }

Double_t DRS4Ana::PlotMaxVoltage(Int_t iCh, Double_t Vcut, Double_t xmin, Double_t xmax)
{
    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t counter = 0;

    if (fH1MaxVoltage != NULL)
    {
        delete fH1MaxVoltage;
    }
    fH1MaxVoltage = new TH1F("fH1MaxVoltage", Form("%s:ch%d Max voltage [%.1f,%.1f]", fRootFile.Data(), iCh, fChargeIntegralTmin, fChargeIntegralTmax), 500, xmin, xmax);
    fH1MaxVoltage->SetXTitle("max voltage");
    fH1MaxVoltage->SetYTitle("[counts]");

    for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
        fChain->GetEntry(jentry);
        Double_t maxVoltage = GetAbsMaxVoltage(iCh);
        counter++;
        // cout << "Debug: just before fill maxvoltage" << endl;
        // cout << "Debug: counter = " << counter << endl;

        fH1MaxVoltage->Fill(maxVoltage);
    }
    // cout << "Debug: escaped from for loop." << endl;
    // fH1ChargeIntegral->SetMinimum(0);
    // fH1ChargeIntegral->SetMaximum(800);

    // gPad->SetGrid(1, 1);
    fH1MaxVoltage->Draw();

    // // 第1のピークに対するフィッティング
    // TF1 *fitFunc1 = new TF1("fitFunc1", "gaus", 21.5, 24); // 適切な範囲を設定
    // fitFunc1->SetParameters(150, 22.5, 3); // 初期パラメータ（例）
    // fH1ChargeIntegral->Fit(fitFunc1, "R"); // "R"は指定した範囲内でフィッティング

    // // 第1のフィッティング結果を取得
    // double mean1 = fitFunc1->GetParameter(1);
    // double sigma1 = fitFunc1->GetParameter(2);
    // std::cout << "Peak 1 - Mean: " << mean1 << ", Sigma: " << sigma1 << std::endl;

    // // 第2のピークに対するフィッティング
    // TF1 *fitFunc2 = new TF1("fitFunc2", "gaus", 24.5, 27); // 第2ピークに対する範囲
    // fitFunc2->SetParameters(125, 26, 3); // 初期パラメータ
    // fH1ChargeIntegral->Fit(fitFunc2, "R");

    // // 第2のフィッティング結果を取得
    // double mean2 = fitFunc2->GetParameter(1);
    // double sigma2 = fitFunc2->GetParameter(2);
    // std::cout << "Peak 2 - Mean: " << mean2 << ", Sigma: " << sigma2 << std::endl;

    // // 両方のフィット結果を描画（ヒストグラムに重ねる）
    // fitFunc1->Draw("same");
    // fitFunc2->Draw("same");

    // // // PNG形式で保存
    // fH1ChargeIntegral->SaveAs("../../../figure/22Na_fit.png");

    // // PDF形式で保存
    // fH1ChargeIntegral->SaveAs("../../../figure/22Na_fit.pdf");


    //22Naのフィッティング
    // // 第1のピークに対するフィッティング
    // TF1 *fitFunc1 = new TF1("fitFunc1", "gaus", 23, 27); // 適切な範囲を設定
    // fitFunc1->SetParameters(150, 24, 10); // 初期パラメータ（例）
    // fH1ChargeIntegral->Fit(fitFunc1, "R"); // "R"は指定した範囲内でフィッティング

    // // 第1のフィッティング結果を取得
    // double mean1 = fitFunc1->GetParameter(1);
    // double sigma1 = fitFunc1->GetParameter(2);
    // std::cout << "Peak 1 - Mean: " << mean1 << ", Sigma: " << sigma1 << std::endl;

    // // 第2のピークに対するフィッティング
    // TF1 *fitFunc2 = new TF1("fitFunc2", "gaus", 8, 12); // 第2ピークに対する範囲
    // fitFunc2->SetParameters(500, 10, 3); // 初期パラメータ
    // fH1ChargeIntegral->Fit(fitFunc2, "R");

    // // 第2のフィッティング結果を取得
    // double mean2 = fitFunc2->GetParameter(1);
    // double sigma2 = fitFunc2->GetParameter(2);
    // std::cout << "Peak 2 - Mean: " << mean2 << ", Sigma: " << sigma2 << std::endl;

    // // 両方のフィット結果を描画（ヒストグラムに重ねる）
    // fitFunc1->Draw("same");
    // fitFunc2->Draw("same");

    // // // PNG形式で保存
    // fH1ChargeIntegral->SaveAs("../../../figure/22Na_fit.png");

    // // PDF形式で保存
    // fH1ChargeIntegral->SaveAs("../../../figure/22Na_fit.pdf");

    // // cout << "counter: " << counter << endl; 
    return (Double_t)counter;
}
