#ifndef T103Ana_h
#define T103Ana_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>

#include <vector>
#include <TH1.h>

class T103Ana
{
public:
    TTree *fChain; //! pointer to the analyzed TTree or TChain
    Int_t fCurrent; //! current Tree number in a TChain

    //ブランチの変数

    std::vector<Int_t>* id_utof_l = nullptr;
    std::vector<Int_t>* id_utof_r = nullptr;
    std::vector<std::vector<Double_t>>* tot_utof_l = nullptr;
    std::vector<std::vector<Double_t>>* tot_utof_r = nullptr;
    std::vector<std::vector<Double_t>>* ltdc_utof_l = nullptr;
    std::vector<std::vector<Double_t>>* ltdc_utof_r = nullptr;

    std::vector<Int_t>* id_dtof_l = nullptr;
    std::vector<Int_t>* id_dtof_r = nullptr;
    std::vector<std::vector<Double_t>>* tot_dtof_l = nullptr;
    std::vector<std::vector<Double_t>>* tot_dtof_r = nullptr;
    std::vector<std::vector<Double_t>>* ltdc_dtof_l = nullptr;
    std::vector<std::vector<Double_t>>* ltdc_dtof_r = nullptr;

    std::vector<Int_t>* id_ltof_l = nullptr;
    std::vector<Int_t>* id_ltof_r = nullptr;
    std::vector<std::vector<Double_t>>* tot_ltof_l = nullptr;
    std::vector<std::vector<Double_t>>* tot_ltof_r = nullptr;
    std::vector<std::vector<Double_t>>* ltdc_ltof_l = nullptr;
    std::vector<std::vector<Double_t>>* ltdc_ltof_r = nullptr;

    std::vector<Int_t>* id_t0_l = nullptr;
    std::vector<Int_t>* id_t0_r = nullptr;
    std::vector<std::vector<Double_t>>* tot_t0_l = nullptr;
    std::vector<std::vector<Double_t>>* tot_t0_r = nullptr;
    std::vector<std::vector<Double_t>>* ltdc_t0_l = nullptr;
    std::vector<std::vector<Double_t>>* ltdc_t0_r = nullptr;

    // t0rはよくわからない
    std::vector<Int_t>* id_t0r_l = nullptr;
    std::vector<Int_t>* id_t0r_r = nullptr;
    std::vector<std::vector<Double_t>>* tot_t0r_l = nullptr;
    std::vector<std::vector<Double_t>>* tot_t0r_r = nullptr;
    std::vector<std::vector<Double_t>>* ltdc_t0r_l = nullptr;
    std::vector<std::vector<Double_t>>* ltdc_t0r_r = nullptr;

    // brefを飛ばす。

    std::vector<Int_t>* id_t1_l = nullptr;
    std::vector<Int_t>* id_t1_r = nullptr;
    std::vector<std::vector<Double_t>>* tot_t1_l = nullptr;
    std::vector<std::vector<Double_t>>* tot_t1_r = nullptr;
    std::vector<std::vector<Double_t>>* ltdc_t1_l = nullptr;
    std::vector<std::vector<Double_t>>* ltdc_t1_r = nullptr;

    // bhtはよくわからない
    std::vector<Int_t>* id_bht_l = nullptr;
    std::vector<Int_t>* id_bht_r = nullptr;
    std::vector<std::vector<Double_t>>* tot_bht_l = nullptr;
    std::vector<std::vector<Double_t>>* tot_bht_r = nullptr;
    std::vector<std::vector<Double_t>>* ltdc_bht_l = nullptr;
    std::vector<std::vector<Double_t>>* ltdc_bht_r = nullptr;

    std::vector<Int_t>* id_bft_l1 = nullptr;
    std::vector<Int_t>* id_bft_l2 = nullptr;
    std::vector<Int_t>* id_bft_l3 = nullptr;
    std::vector<Int_t>* id_bft_l4 = nullptr;
    std::vector<Int_t>* id_bft_l5 = nullptr;
    std::vector<Int_t>* id_bft_l6 = nullptr;
    std::vector<std::vector<Double_t>>* tot_bft_l1 = nullptr;
    std::vector<std::vector<Double_t>>* tot_bft_l2 = nullptr;
    std::vector<std::vector<Double_t>>* tot_bft_l3 = nullptr;
    std::vector<std::vector<Double_t>>* tot_bft_l4 = nullptr;
    std::vector<std::vector<Double_t>>* tot_bft_l5 = nullptr;
    std::vector<std::vector<Double_t>>* tot_bft_l6 = nullptr;
    std::vector<std::vector<Double_t>>* ltdc_bft_l1 = nullptr;
    std::vector<std::vector<Double_t>>* ltdc_bft_l2 = nullptr;
    std::vector<std::vector<Double_t>>* ltdc_bft_l3 = nullptr;
    std::vector<std::vector<Double_t>>* ltdc_bft_l4 = nullptr;
    std::vector<std::vector<Double_t>>* ltdc_bft_l5 = nullptr;
    std::vector<std::vector<Double_t>>* ltdc_bft_l6 = nullptr;

    std::vector<Int_t>* id_sft_l1 = nullptr;
    std::vector<Int_t>* id_sft_l2 = nullptr;
    std::vector<Int_t>* id_sft_l3 = nullptr;
    std::vector<Int_t>* id_sft_l4 = nullptr;
    std::vector<Int_t>* id_sft_l5 = nullptr;
    std::vector<Int_t>* id_sft_l6 = nullptr;
    std::vector<std::vector<Double_t>>* tot_sft_l1 = nullptr;
    std::vector<std::vector<Double_t>>* tot_sft_l2 = nullptr;
    std::vector<std::vector<Double_t>>* tot_sft_l3 = nullptr;
    std::vector<std::vector<Double_t>>* tot_sft_l4 = nullptr;
    std::vector<std::vector<Double_t>>* tot_sft_l5 = nullptr;
    std::vector<std::vector<Double_t>>* tot_sft_l6 = nullptr;
    std::vector<std::vector<Double_t>>* ltdc_sft_l1 = nullptr;
    std::vector<std::vector<Double_t>>* ltdc_sft_l2 = nullptr;
    std::vector<std::vector<Double_t>>* ltdc_sft_l3 = nullptr;
    std::vector<std::vector<Double_t>>* ltdc_sft_l4 = nullptr;
    std::vector<std::vector<Double_t>>* ltdc_sft_l5 = nullptr;
    std::vector<std::vector<Double_t>>* ltdc_sft_l6 = nullptr;


    T103Ana(const Char_t *fRootFile_par = "../test1181.root");
    virtual ~T103Ana();
    virtual Int_t GetEntry(Long64_t entry);
    virtual Long64_t LoadTree(Long64_t entry);
    virtual Bool_t Notify() { return kTRUE; } // Called when loading a new file
    virtual void Init(TTree *tree);

    // ここから解析用の関数
    TString Makedir_Date();
    Int_t IfFile_duplication(TString folderPath, TString &fileName);
    virtual void PlotTOF(Int_t nbins = 100, Double_t xmin = -140.0, Double_t xmax = -120.0);
    virtual void CheckNumComponents();

    TH1F *fH1TOF = NULL;

private:
    TString fRootFile; // Root file name
};

#endif

#ifdef T103Ana_cxx
T103Ana::T103Ana(const Char_t *fRootFile_par) : fChain(0)
{

    fRootFile.Form("%s", fRootFile_par);
    TFile *f = (TFile *)gROOT->GetListOfFiles()->FindObject(fRootFile);
    if (!f || !f->IsOpen())
    {
        f = new TFile(fRootFile);
    }
    TTree *tree;
    f->GetObject("tree", tree);
    Init(tree);
}

T103Ana::~T103Ana()
{
    if (!fChain)
        return;
    delete fChain->GetCurrentFile();
}
Int_t T103Ana::GetEntry(Long64_t entry)
{
    // Read contents of entry.
    if (!fChain)
        return 0;
    return fChain->GetEntry(entry);
}
Long64_t T103Ana::LoadTree(Long64_t entry)
{
    // Set the environment to read one entry
    if (!fChain)
        return -5;
    Long64_t centry = fChain->LoadTree(entry);
    if (centry < 0)
        return centry;
    if (fChain->GetTreeNumber() != fCurrent)
    {
        fCurrent = fChain->GetTreeNumber();
        Notify();
    }
    return centry;
}

void T103Ana::Init(TTree *tree)
{
    // Set branch addresses and branch pointers
    if (!tree)
        return;

    fChain = tree;
    fCurrent = -1; // Initialize current Tree number

    fChain->SetMakeClass(1);

    fChain->SetBranchAddress("id_utof_l", &id_utof_l);
    fChain->SetBranchAddress("id_utof_r", &id_utof_r);
    fChain->SetBranchAddress("tot_utof_l", &tot_utof_l);
    fChain->SetBranchAddress("tot_utof_r", &tot_utof_r);
    fChain->SetBranchAddress("ltdc_utof_l", &ltdc_utof_l);
    fChain->SetBranchAddress("ltdc_utof_r", &ltdc_utof_r); 
    fChain->SetBranchAddress("id_dtof_l", &id_dtof_l);
    fChain->SetBranchAddress("id_dtof_r", &id_dtof_r);
    fChain->SetBranchAddress("tot_dtof_l", &tot_dtof_l);
    fChain->SetBranchAddress("tot_dtof_r", &tot_dtof_r);
    fChain->SetBranchAddress("ltdc_dtof_l", &ltdc_dtof_l);
    fChain->SetBranchAddress("ltdc_dtof_r", &ltdc_dtof_r);
    fChain->SetBranchAddress("id_ltof_l", &id_ltof_l);
    fChain->SetBranchAddress("id_ltof_r", &id_ltof_r);
    fChain->SetBranchAddress("tot_ltof_l", &tot_ltof_l);
    fChain->SetBranchAddress("tot_ltof_r", &tot_ltof_r);
    fChain->SetBranchAddress("ltdc_ltof_l", &ltdc_ltof_l);
    fChain->SetBranchAddress("ltdc_ltof_r", &ltdc_ltof_r);
    fChain->SetBranchAddress("id_t0_l", &id_t0_l);
    fChain->SetBranchAddress("id_t0_r", &id_t0_r);
    fChain->SetBranchAddress("tot_t0_l", &tot_t0_l);
    fChain->SetBranchAddress("tot_t0_r", &tot_t0_r);
    fChain->SetBranchAddress("ltdc_t0_l", &ltdc_t0_l);
    fChain->SetBranchAddress("ltdc_t0_r", &ltdc_t0_r);
    fChain->SetBranchAddress("id_t0r_l", &id_t0r_l);
    fChain->SetBranchAddress("id_t0r_r", &id_t0r_r);
    fChain->SetBranchAddress("tot_t0r_l", &tot_t0r_l);
    fChain->SetBranchAddress("tot_t0r_r", &tot_t0r_r);
    fChain->SetBranchAddress("ltdc_t0r_l", &ltdc_t0r_l);
    fChain->SetBranchAddress("ltdc_t0r_r", &ltdc_t0r_r);
    fChain->SetBranchAddress("id_t1_l", &id_t1_l);
    fChain->SetBranchAddress("id_t1_r", &id_t1_r);
    fChain->SetBranchAddress("tot_t1_l", &tot_t1_l);
    fChain->SetBranchAddress("tot_t1_r", &tot_t1_r);
    fChain->SetBranchAddress("ltdc_t1_l", &ltdc_t1_l);
    fChain->SetBranchAddress("ltdc_t1_r", &ltdc_t1_r);
    fChain->SetBranchAddress("id_bht_l", &id_bht_l);
    fChain->SetBranchAddress("id_bht_r", &id_bht_r);
    fChain->SetBranchAddress("tot_bht_l", &tot_bht_l);
    fChain->SetBranchAddress("tot_bht_r", &tot_bht_r);
    fChain->SetBranchAddress("ltdc_bht_l", &ltdc_bht_l);
    fChain->SetBranchAddress("ltdc_bht_r", &ltdc_bht_r);
    fChain->SetBranchAddress("id_bft_l1", &id_bft_l1);
    fChain->SetBranchAddress("id_bft_l2", &id_bft_l2);
    fChain->SetBranchAddress("id_bft_l3", &id_bft_l3);
    fChain->SetBranchAddress("id_bft_l4", &id_bft_l4);
    fChain->SetBranchAddress("id_bft_l5", &id_bft_l5);
    fChain->SetBranchAddress("id_bft_l6", &id_bft_l6);
    fChain->SetBranchAddress("tot_bft_l1", &tot_bft_l1);
    fChain->SetBranchAddress("tot_bft_l2", &tot_bft_l2);
    fChain->SetBranchAddress("tot_bft_l3", &tot_bft_l3);
    fChain->SetBranchAddress("tot_bft_l4", &tot_bft_l4);
    fChain->SetBranchAddress("tot_bft_l5", &tot_bft_l5);
    fChain->SetBranchAddress("tot_bft_l6", &tot_bft_l6);
    fChain->SetBranchAddress("ltdc_bft_l1", &ltdc_bft_l1);
    fChain->SetBranchAddress("ltdc_bft_l2", &ltdc_bft_l2);
    fChain->SetBranchAddress("ltdc_bft_l3", &ltdc_bft_l3);
    fChain->SetBranchAddress("ltdc_bft_l4", &ltdc_bft_l4);
    fChain->SetBranchAddress("ltdc_bft_l5", &ltdc_bft_l5);
    fChain->SetBranchAddress("ltdc_bft_l6", &ltdc_bft_l6);
    fChain->SetBranchAddress("id_sft_l1", &id_sft_l1);
    fChain->SetBranchAddress("id_sft_l2", &id_sft_l2);
    fChain->SetBranchAddress("id_sft_l3", &id_sft_l3);
    fChain->SetBranchAddress("id_sft_l4", &id_sft_l4);
    fChain->SetBranchAddress("id_sft_l5", &id_sft_l5);
    fChain->SetBranchAddress("id_sft_l6", &id_sft_l6);
    fChain->SetBranchAddress("tot_sft_l1", &tot_sft_l1);
    fChain->SetBranchAddress("tot_sft_l2", &tot_sft_l2);
    fChain->SetBranchAddress("tot_sft_l3", &tot_sft_l3);
    fChain->SetBranchAddress("tot_sft_l4", &tot_sft_l4);
    fChain->SetBranchAddress("tot_sft_l5", &tot_sft_l5);
    fChain->SetBranchAddress("tot_sft_l6", &tot_sft_l6);
    fChain->SetBranchAddress("ltdc_sft_l1", &ltdc_sft_l1);
    fChain->SetBranchAddress("ltdc_sft_l2", &ltdc_sft_l2);
    fChain->SetBranchAddress("ltdc_sft_l3", &ltdc_sft_l3);
    fChain->SetBranchAddress("ltdc_sft_l4", &ltdc_sft_l4);
    fChain->SetBranchAddress("ltdc_sft_l5", &ltdc_sft_l5);
    fChain->SetBranchAddress("ltdc_sft_l6", &ltdc_sft_l6); 

    printf("\tbranch address set\n");

    fChain->GetEntry(0);
    printf("\tGetEntry(0)\n");

    Notify();
}

#endif