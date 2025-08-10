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
#include <TF2.h>

// グラフ
#include <TGraphErrors.h>
#include <TLegend.h>

// 見栄え関係
#include <TPad.h>
#include <TColor.h>

void dist_E_e(){
    // 関数定義
    TF1 *f = new TF1("f", "-8*x**3+6*x**2", 0, 0.5);
    
    f->SetTitle("f(Z, a) = 8Z^{3} - 6Z^{2};a;Z");
    f->SetNpx(100);  // x方向の分割数

    f->Draw();  // カラーマップ表示
}