#define T103Ana_cxx
#include "T103Ana.h"

#include <TStyle.h>
#include <TCanvas.h>

#include <TSystem.h>

// C++の標準ライブラリ
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

// 時刻情報
#include <iomanip>
#include <chrono>
#include <ctime>

// ヒストグラム関係
#include <TH1.h>
#include <TH2.h>

// グラフ
#include <TGraphErrors.h>
#include <TLegend.h>

// 見栄え関係
#include <TPad.h>
#include <TColor.h>

TString T103Ana::Makedir_Date(){
    //YYYYMMDDのフォルダを作る関数。呼び出せば勝手にYYYYMMDDのフォルダができる。
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char date[9];
    strftime(date, sizeof(date), "%Y%m%d", ltm);
    TString folderPath = TString::Format("./figure/%s", date);

    if(gSystem->AccessPathName(folderPath)){
        if(gSystem->mkdir(folderPath, true) != 0){
                std::cerr << "フォルダの作成に失敗しました: " << folderPath << std::endl;
                return -1;
        }
    }
    return (folderPath);
}
Int_t T103Ana::IfFile_duplication(TString folderPath, TString &fileName){
    //例えば、"./figure/YYYYMMDD"というパスと、hoge.pdfを渡せば、そのディレクトリにhoge.pdfとhoge2.pdfが存在する場合に、渡した"hoge.pdf"を"hoge3.pdf"に変えてくれる関数
    Int_t index =1;
    Int_t lastDotPos = fileName.Last('.');
    TString filename_buf_before_dot = fileName(0, lastDotPos);
    TString filename_buf_after_dot = fileName(lastDotPos, fileName.Length());
    TString filename_buf = fileName;
    while(gSystem->AccessPathName(folderPath + '/' + filename_buf) == 0){
        filename_buf = filename_buf_before_dot + TString::Format("%d", index) + filename_buf_after_dot;
        index++;
        std::cout << Form("\tfilename : %s exists, rename...", filename_buf.Data()) << std::endl;
    }
    fileName = filename_buf;
    return index;
}

void T103Ana::PlotTOF(Int_t nbins = 100, Double_t xmin = -140.0, Double_t xmax = -120.0)
{
    // ツリーから直接Draw
    TCanvas *c1 = new TCanvas("c1", Form("TOF Plot %s", fRootFile.Data()), 800, 600);
    c1->Draw();

    fH1TOF = new TH1F("fH1TOF", Form("TOF Distribution %s", fRootFile.Data()), nbins, xmin, xmax);
    fH1TOF->SetXTitle("TOF [ns]");
    fH1TOF->SetYTitle("Counts");

    fChain->Draw("(ltdc_utof_l[0]+ltdc_utof_r[0])/2.0 - (ltdc_t1_l[0]+ltdc_t1_r[0])/2.0>>fH1TOF");

}

void T103Ana::CheckNumComponents()
{
    Long64_t nentries = fChain->GetEntries();
    std::cout << "Number of entries in the tree: " << nentries << std::endl;

    nentries = 50;
    for(Int_t Entry=0; Entry<nentries; Entry++){
        fChain->GetEntry(Entry);
        printf("\nEntry %d:\n", Entry);
        std::cout << "\t(*ltdc_utof_l)[0] size : " << (*ltdc_utof_l)[0].size() << std::endl;
        std::cout << "\t(*ltdc_utof_r)[0] size : " << (*ltdc_utof_r)[0].size() << std::endl;

        std::cout << "\t(*ltdc_utof_l) size : " << (*ltdc_utof_l).size() << std::endl;
        std::cout << "\t(*ltdc_utof_r) size : " << (*ltdc_utof_r).size() << std::endl;

        printf("L\n");
        for(Int_t i=0; i<ltdc_utof_l->size(); i++){
            for(Int_t j=0; j<ltdc_utof_l[i].size(); j++){
                std::cout << Form("\tltdc_utof_l[%d][%d] = %f\n", i, j, (*ltdc_utof_l)[i][j]);
            }
        }
        printf("R\n");
        for(Int_t i=0; i<ltdc_utof_r->size(); i++){
            for(Int_t j=0; j<ltdc_utof_r[i].size(); j++){
                std::cout << Form("\tltdc_utof_r[%d][%d] = %f\n", i, j, (*ltdc_utof_r)[i][j]);
            }
        }
    }
}

void T103Ana::CheckNumComponents_general()
{
    fChain->SetBranchStatus("*", 0); // 全てのブランチを無効化

    fChain->SetBranchStatus("ltdc_t0_l", 1);
    fChain->SetBranchStatus("ltdc_t0_r", 1); // ltdc_t0_lとltdc_t0_rのみ有効化

    Long64_t nentries = fChain->GetEntries();
    std::cout << "Number of entries in the tree: " << nentries << std::endl;

    nentries = 50;
    for(Int_t Entry=0; Entry<nentries; Entry++){
        fChain->GetEntry(Entry);
        printf("\nEntry %d:\n", Entry);


        std::cout << "\tinner vector size : " << (*ltdc_t0_l)[0].size() << std::endl;
        std::cout << "\tinner vector size : " << (*ltdc_t0_r)[0].size() << std::endl;

        std::cout << "\touter vector size : " << (*ltdc_t0_l).size() << std::endl;
        std::cout << "\touter vector size : " << (*ltdc_t0_r).size() << std::endl;

        printf("L\n");
        for(Int_t i=0; i<ltdc_t0_l->size(); i++){
            for(Int_t j=0; j<(*ltdc_t0_l)[i].size(); j++){
                std::cout << Form("\tltdc_t0_l[%d][%d] = %f\n", i, j, (*ltdc_t0_l)[i][j]);
            }
        }
        printf("R\n");
        for(Int_t i=0; i<ltdc_t0_r->size(); i++){
            for(Int_t j=0; j<(*ltdc_t0_r)[i].size(); j++){
                std::cout << Form("\tltdc_t0_r[%d][%d] = %f\n", i, j, (*ltdc_t0_r)[i][j]);
            }
        }
    }
}

Double_t T103Ana::CheckNumComponents2()
{
    fChain->SetBranchStatus("*", 0); // 全てのブランチを無効化
    fChain->SetBranchStatus("ltdc_utof_l", 1); 
    fChain->SetBranchStatus("ltdc_utof_r", 1); // ltdc_utof_lとltdc_utof_rのみ有効化
    Long64_t nentries = fChain->GetEntries();
    std::cout << "Number of entries in the tree: " << nentries << std::endl;

    if(fH1General != NULL){
        delete fH1General;
    }

    fH1General = new TH1F("fH1General", "number of components in a vector", 10, 0, 10);
    fH1General->SetXTitle("Number of components");
    fH1General->SetYTitle("Counts");

    Int_t numComponents, counter = 0;
    for(Int_t Entry=0; Entry<nentries; Entry++){
        fChain->GetEntry(Entry);

        numComponents = ltdc_utof_r[0].size();
        fH1General->Fill(numComponents);
        counter++;
    }
    fH1General->Draw();
    return counter;

}

Double_t T103Ana::T0_check()
{
    fChain->SetBranchStatus("*", 0); // 全てのブランチを無効化

    fChain->SetBranchStatus("ltdc_t0_l", 1);
    fChain->SetBranchStatus("ltdc_t0_r", 1); // ltdc_t0_lとltdc_t0_rのみ有効化

    Long64_t nentries = fChain->GetEntries();
    std::cout << "Number of entries in the tree: " << nentries << std::endl;

    fChain->GetEntry(0);
    std::cout << "(*ltdc_t0_l).size() = " << (*ltdc_t0_l).size() << std::endl;
    std::cout << "(*ltdc_t0_l[0]).size() = " << (*ltdc_t0_l)[0].size() << std::endl;

    if(fH2General != NULL){
        delete fH2General;
    }
    fH2General = new TH2F("fH2General", "distribution of T0", 100, 600, 1400, 8, 0, 7);
    fH2General->SetXTitle("time [ns]");
    fH2General->SetYTitle("channel");

    Double_t tof_buf;
    Double_t counter = 0;
    for(Int_t Entry=0; Entry<nentries; Entry++){
        fChain->GetEntry(Entry);
        for(Int_t outer=0; outer<(*ltdc_t0_l).size(); outer++){
            for(Int_t inner=0; inner<(*ltdc_t0_l)[outer].size(); inner++){
            fH2General->Fill((*ltdc_t0_l)[outer][inner], outer);
            if((*ltdc_t0_l)[outer].size() != 0){
                std::cout << Form("Entry %d : ltdc_t0_l[%d][%d] = %f\n", Entry, outer, inner, (*ltdc_t0_l)[outer][inner]) << std::endl;
            }
            }
        }
        
        counter++;
    }
    fH2General->Draw("colz");
    gPad->SetLogz();
    gPad->SetGrid();
    return counter;

}

Double_t T103Ana::T0r_check()
{
    fChain->SetBranchStatus("*", 0); // 全てのブランチを無効化

    fChain->SetBranchStatus("ltdc_t0r_l", 1);
    fChain->SetBranchStatus("ltdc_t0r_r", 1); // ltdc_t0_lとltdc_t0_rのみ有効化

    Long64_t nentries = fChain->GetEntries();
    std::cout << "Number of entries in the tree: " << nentries << std::endl;

    fChain->GetEntry(0);
    std::cout << "(*ltdc_t0r_l).size() = " << (*ltdc_t0r_l).size() << std::endl;
    std::cout << "(*ltdc_t0r_l[0]).size() = " << (*ltdc_t0r_l)[0].size() << std::endl;

    // 下記は同じ意味？
    std::cout << "ltdc_t0r_l->size() = " << ltdc_t0r_l[0].size() << std::endl;
    std::cout << "ltdc_t0r_l[0].size() = " << ltdc_t0r_l[0][0].size() << std::endl;

    if(fH2General != NULL){
        delete fH2General;
    }
    fH2General = new TH2F("fH2General", "distribution of T0r", 100, 600, 1400, 8, 0, 7);
    fH2General->SetXTitle("time [ns]");
    fH2General->SetYTitle("channel");

    Double_t tof_buf;
    Double_t counter = 0;
    for(Int_t Entry=0; Entry<nentries; Entry++){
        fChain->GetEntry(Entry);
        for(Int_t outer=0; outer<(*ltdc_t0r_l).size(); outer++){
            for(Int_t inner=0; inner<(*ltdc_t0r_l)[outer].size(); inner++){
            fH2General->Fill((*ltdc_t0r_l)[outer][inner], outer);
            if((*ltdc_t0r_l)[outer].size() != 0){
                std::cout << Form("Entry %d : ltdc_t0r_l[%d][%d] = %f\n", Entry, outer, inner, (*ltdc_t0r_l)[outer][inner]) << std::endl;
            }
            }
        }
        
        counter++;
    }
    fH2General->Draw("colz");
    gPad->SetLogz();
    gPad->SetGrid();
    return counter;

}

Double_t T103Ana::LTDC_check() {
    // 仮でも空でOK
    return 0.0;
}