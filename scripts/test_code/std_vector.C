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

void std_vector(){
    std::vector<std::vector<Double_t>>* vec2d = new std::vector<std::vector<Double_t>>();
    vec2d->push_back(std::vector<Double_t>{1.0, 2.0, 3.0});
    vec2d->push_back(std::vector<Double_t>{4.0, 5.0, 6.0});
    vec2d->push_back(std::vector<Double_t>{7.0, 8.0, 9.0});

    std::cout << (*vec2d)[0][0] << std::endl;

    std::cout << vec2d[0][0][0] << std::endl;

    std::cout << vec2d->at(0).at(0) << std::endl;

    auto value = *((vec2d->begin()+0)->begin()+0);
    std::cout << value << std::endl;
}