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

void E_e(){
    // 関数定義
    TF2 *f = new TF2("f", "(-1.0)*x*(4*y**3 - y**2) - 4*y**3 + 3*y**2", -1, 1, 0, 0.5);
    
    f->SetTitle("f(Z, a) = -a(4Z^{3} - Z^{2}) - 4Z^{3} + 3Z^{2};a;Z");
    f->SetNpx(100);  // x方向の分割数
    f->SetNpy(100);  // y方向の分割数

    f->Draw("COLZ");  // カラーマップ表示
}