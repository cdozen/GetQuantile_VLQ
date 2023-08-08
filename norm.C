/*TPrimemass plots after corrections 
 * TprimeMass1-5
 with quantiles:
 * TprimeMass7 
 * TprimeMass9 
 * TprimeMass11 
 * TprimeMass13 
 * 
 */
#include <iostream>
#include <TH1D.h>
#include <TH2F.h>
#include <TFile.h>
#include <TRandom3.h>
#include <TMath.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <THStack.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include <TMultiGraph.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TString.h>
#include <TMath.h>
#include "TPaveStats.h"
void norm(){
    //quantile cuts before correction
    //TFile *f0 = new TFile ("before_correction/20230228_3T_2018UL_Mtop140_FullBRew_finalresultallfit/listinput2018ULData.root","read");
    
    //Quantile cuts after correction and MERGEDBINS//26 MART
    TFile *f0 = new TFile ("data/MergedBins500/20230325_3T_2018UL_Mtop140_FullBRew_Merged_3T_validation/listinput2018ULData.root","read");

    //quantile cuts after correction and REBINX2//26 MART
    //TFile *f0  = new TFile ("data/RebinX2/20230326_3T_2018UL_Mtop140_FullBRew_REBINX_3T_validation/listinput2018ULData.root","read");

    TH1F* dd0 = (TH1F*)f0->Get("TprimeMass1"); 
    TH1F* dd1 = (TH1F*)f0->Get("TprimeMass3");
    TH1F* dd2 = (TH1F*)f0->Get("TprimeMass5");
    TH1F* dd3 = (TH1F*)f0->Get("TprimeMass7");
    TH1F* dd4 = (TH1F*)f0->Get("TprimeMass9");
    TH1F* dd5 = (TH1F*)f0->Get("TprimeMass11");
    TH1F* dd6 = (TH1F*)f0->Get("TprimeMass13");
    gStyle->SetOptStat(0);
    //gStyle->SetPalette(kOcean);
    dd0->SetLineColor(1);
    dd1->SetLineColor(28);
    dd2->SetLineColor(8);
    dd3->SetLineColor(4);
    dd4->SetLineColor(6);
    dd5->SetLineColor(38);
    dd6->SetLineColor(2);

    dd0->SetMarkerStyle(kFullCircle);
    dd0->SetMarkerColor(1);
    dd1->SetMarkerStyle(kFullSquare);
    dd1->SetMarkerColor(28);
    dd2->SetMarkerStyle(kFullTriangleUp);
    dd2->SetMarkerColor(8);
    dd3->SetMarkerStyle(kFullTriangleDown);
    dd3->SetMarkerColor(4);
    dd4->SetMarkerStyle(kOpenCircle);
    dd4->SetMarkerColor(6);
    //dd5->SetLineColor(12);
    dd5->SetMarkerStyle(29);
    dd5->SetMarkerColor(38);
    dd6->SetMarkerStyle(5);
    dd6->SetMarkerColor(2);
   
    dd0->SetStats(kTRUE);
    // normalize to 1
    dd0->Scale(1.0/dd0->Integral());
    dd1->Scale(1.0/dd1->Integral());
    dd2->Scale(1.0/dd2->Integral());
    dd3->Scale(1.0/dd3->Integral());
    dd4->Scale(1.0/dd4->Integral());
    dd5->Scale(1.0/dd5->Integral());
    dd6->Scale(1.0/dd6->Integral());

    dd0->Rebin(2.);
    dd1->Rebin(2.);
    dd2->Rebin(2.);
    dd3->Rebin(2.);
    dd4->Rebin(2.);
    dd5->Rebin(2.);
    dd6->Rebin(2.);

    dd4->Draw("e");
    dd1->Draw("esame");
    dd2->Draw("esame");
    dd3->Draw("esame");
    dd0->Draw("esame");
    dd5->Draw("esame");
    dd6->Draw("esame");


    TLegend* legend = new TLegend(0.40, 0.60, 0.70, 0.90); // (x1, y1, x2, y2) in NDC coordinates
    legend->SetBorderSize(1);
    legend->SetFillColor(0);
    legend->SetTextSize(0.03);
    //legend->AddEntry("", "After MergedBins < 500", ""); 
    legend->AddEntry(dd0, "TMass_1", "lep"); 
    legend->AddEntry(dd1, "TMass_3", "lep"); 
    legend->AddEntry(dd2, "TMass_5", "lep"); 
    legend->AddEntry(dd3, "TMass_7", "lep"); 
    legend->AddEntry(dd4, "TMass_9", "lep"); 
    legend->AddEntry(dd5, "TMass_11", "lep"); 
    legend->AddEntry(dd6, "TMass_13", "lep"); 
    legend->Draw();

}
