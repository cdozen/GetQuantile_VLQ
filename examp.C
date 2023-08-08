/**
 * final results comparisions 
 * default cuts - after quantile method
 * After quantile method:
 * we had a minor issue in the quantile code :
 * before: Derive quantile values from binX until infinity. 
 * after: Derive quantile values for each bin interval : from binX to binX+1 
 * So after correction:
 * fluctuation in the high-mass region due to low statistic - so 2 different method applied
 * 1- Merged bins after giving a threshold (>500 entries) for each bin. : f
 * 2- Rebinned X by *2  
 *So you can see the comparisions between old method and after/ before correction with quantile method
 * CDozen
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
void examp(){

  //final validation 3T all cuts //before correction
  TFile *f0 = new TFile ("before_correction/20230228_3T_2018UL_Mtop140_FullBRew_finalresultallfit/listinput2018ULData.root","read");

  //final validation 3T all cuts //after correction and MERGEDBINS//26 MART
  TFile *fM  = new TFile ("data/MergedBins500/20230325_3T_2018UL_Mtop140_FullBRew_Merged_3T_validation/listinput2018ULData.root","read");
  
  //final validation 3T all cuts //after correction and REBINX2//26 MART
  TFile *fR  = new TFile ("data/RebinX2/20230326_3T_2018UL_Mtop140_FullBRew_REBINX_3T_validation/listinput2018ULData.root","read");

  //final results old cut order from Stephanie BG
  TFile *fold = new TFile ("defcuts/Plots_2018ULMtop140FullDataCorrectJetID.root","read");


  TH1F* ddold = (TH1F*)fold->Get("TprimeMass13");   //old cut order
  TH1F* dd0 = (TH1F*)f0->Get("TprimeMass13");       //quantile before correction 
  TH1F* ddmerged = (TH1F*)fM->Get("TprimeMass13");  //quantile after correction and merged bins
  TH1F* ddrebin = (TH1F*)fR->Get("TprimeMass13");   //quantile after correction and RebinX*2 
  
  dd0->SetLineColor(kBlue+2);
  dd0->SetMarkerColor(2);
  dd0->SetMarkerStyle(2);
  ddmerged->SetLineColor(kRed);
  ddrebin->SetLineColor(kRed);
  ddold->SetLineColor(kGreen+3);
  ddold->SetMarkerStyle(0);
  ddold->SetLineWidth(3);
    
 
  dd0->SetStats(kFALSE);
  ddmerged->SetStats(kFALSE);
  ddrebin->SetStats(kFALSE);
  ddold->SetStats(kFALSE);

  dd0->Rebin(2.);
  ddold->Rebin(2.);
  ddmerged->Rebin(2.);
  ddrebin->Rebin(2.);

  //ddrebin->Draw("HIST");
  ddmerged->Draw("HIST");
  dd0->Draw("HIST SAME");
  ddold->Draw("HIST SAME");
  ddrebin->SetLineWidth(3);
  dd0->SetLineWidth(3);
  ddmerged->SetLineWidth(3);
  //dd0->Draw("e");
  //ddold->Draw("esame");
  
  //dd0 : quantile before correction stat box
  TPaveStats* stats0 = new TPaveStats(0.55,0.50,0.90,0.70,"brNDC");
  stats0->SetFillColor(kWhite);
  //stats0->SetFillStyle(0);
  stats0->SetName("stats0");
  stats0->SetTextColor(kBlue+2);
  stats0->AddText("TMass13_Before_Correction");
  stats0->SetTextFont(10); // not bold
  stats0->AddText(Form("Entries: %.0f",dd0->GetEntries()));
  stats0->AddText(Form("Mean: %.2f",dd0->GetMean()));
  stats0->AddText(Form("Std Dev: %.2f",dd0->GetRMS()));
  stats0->SetShadowColor(0);
  stats0->Draw();
  dd0->GetListOfFunctions()->Add(stats0);


  //dd_old : old cut order stat box
  TPaveStats* stats1 = new TPaveStats(0.55,0.50,0.90,0.70,"brNDC");
  //stats1->SetFillColorAlpha(0, 0);
  stats1->SetFillColor(kWhite);
  stats1->SetName("stats1");
  stats1->SetTextColor(kGreen+3);
  //stats1->SetOptStat(1111);
  stats1->SetTextFont(10); // not bold
  stats1->AddText("TMass13_oldcut");
  stats1->AddText(Form("Entries: %.0f",ddold->GetEntries()));
  stats1->AddText(Form("Mean: %.2f",ddold->GetMean()));
  stats1->AddText(Form("Std Dev: %.2f",ddold->GetRMS()));
  stats1->SetShadowColor(0);
  stats1->Draw();
  ddold->GetListOfFunctions()->Add(stats1);

  //ddrebin: RebinX*2 : quantile after correction stat box
  TPaveStats* stats2 = new TPaveStats(0.55,0.50,0.90,0.70,"brNDC");
  stats2->SetFillColor(kWhite);
  stats2->SetName("stats2");
  stats2->SetTextColor(kRed);
  stats2->AddText("TMass13_After_Correction");
  stats2->SetTextFont(10); // not bold
  stats2->AddText(Form("Entries: %.0f",ddrebin->GetEntries()));
  stats2->AddText(Form("Mean: %.2f",ddrebin->GetMean()));
  stats2->AddText(Form("Std Dev: %.2f",ddrebin->GetRMS()));
  //stats2->Draw();
  //ddrebin->GetListOfFunctions()->Add(stats2);
  
  //ddmerged: Merged bins : quantile after correction stat box
  TPaveStats* stats3 = new TPaveStats(0.55,0.50,0.90,0.70,"brNDC");
  stats3->SetFillColor(kWhite);
  stats3->SetName("stats3");
  stats3->SetTextColor(kRed);
  stats3->AddText("TMass13_After_Correction");
  stats3->SetTextFont(10); // not bold
  stats3->AddText(Form("Entries: %.0f",ddmerged->GetEntries()));
  stats3->AddText(Form("Mean: %.2f",ddmerged->GetMean()));
  stats3->AddText(Form("Std Dev: %.2f",ddmerged->GetRMS()));
  stats3->Draw();
  ddmerged->GetListOfFunctions()->Add(stats2);
  
  TLegend* legend = new TLegend(0.30, 0.75, 0.75, 0.90); // (x1, y1, x2, y2) in NDC coordinates
  legend->SetBorderSize(1);
  legend->SetFillColor(0);
  legend->SetTextSize(0.03);
  legend->AddEntry(ddold, "TMass13_oldcuts", "l");
  legend->AddEntry(dd0, "TMass13_before_correction", "l");
  //legend->AddEntry(ddrebin, "TMass13_after_correction/RebinX*2", "l");
  //legend->AddEntry(ddrebin, "TMass13_after_correction", "l");
  legend->AddEntry(ddmerged, "TMass13_after_correction", "l");
  legend->AddEntry(ddmerged, "[MergedBins<500]", "");
  legend->Draw();
}
