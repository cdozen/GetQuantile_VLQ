/**
 * TPrimemass plot before and after corrections for each cut variables
 * TprimeMass7 : new_cut3
 * TprimeMass9 : new_cut4
 * TprimeMass11 : new_cut5
 * TprimeMass13 : new_cut6
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
void FinalFit(){

  //====================================================================================================================//
  /* default cut order */
  //====================================================================================================================//
  TFile *fold = new TFile ("defcuts/20230228_3T_2018UL_Mtop140_FullBRew/listinput2018ULData.root","read");
  //====================================================================================================================//
  /* AFTER quantile BEFORE merged bins correction */
  //====================================================================================================================//
  TFile *f0 = new TFile ("after_quantilecuts/20230228_3T_2018UL_Mtop140_FullBRew_finalresultallfit/listinput2018ULData.root","read");

  //====================================================================================================================//
  /*AFTER quantile and MergedBins correction */
  //====================================================================================================================//
  TFile *fM = new TFile ("data/MergedBins500/20230325_3T_2018UL_Mtop140_FullBRew_Merged_3T_validation/listinput2018ULData.root","read");

  //====================================================================================================================//
  THStack *stack = new THStack("stack", "Histograms");

  
  /*TH1F* dd0 = (TH1F*)f0->Get("TprimeMass7"); //new_cut3 
  TH1F* ddmerged = (TH1F*)fM->Get("TprimeMass7");*/

  /*TH1F* dd0 = (TH1F*)f0->Get("TprimeMass9"); //new_cut4 
  TH1F* ddmerged = (TH1F*)fM->Get("TprimeMass9");*/

  /*TH1F* dd0 = (TH1F*)f0->Get("TprimeMass11"); //new_cut5
  TH1F* ddmerged = (TH1F*)fM->Get("TprimeMas11");*/

  //TH1F* ddold = (TH1F*)fold->Get("TprimeMass13"); 
  TH1F* dd0 = (TH1F*)f0->Get("TprimeMass13"); //new_cut6 
  TH1F* ddmerged = (TH1F*)fM->Get("TprimeMass13");
  
  //ddold->SetTitle("Top+H Invariant Mass");
  //ddold->Rebin(2.);
  //ddold->SetLineColor(kBlack+2);
  dd0->Rebin(2.);
  ddmerged->Rebin(2.);

  
  dd0->SetLineColor(kBlue+2);
  dd0->SetMarkerColor(4);

  ddmerged->SetLineColor(kRed+2);
  ddmerged->SetMarkerColor(2);
  ddmerged->SetMarkerStyle(29);

  ddmerged->Draw("e");
  dd0->Draw("esame");
  //ddold->Draw("esame");

  
  TPaveStats* stats0 = new TPaveStats(0.55,0.50,0.90,0.70,"brNDC");
  stats0->SetFillColor(kWhite);
  stats0->SetName("stats0");
  stats0->SetTextColor(kBlue+2);
  stats0->AddText("TMass13_BC");
  stats0->SetTextFont(10); // not bold
  stats0->AddText(Form("Entries: %.0f",dd0->GetEntries()));
  stats0->AddText(Form("Mean: %.2f",dd0->GetMean()));
  stats0->AddText(Form("Std Dev: %.2f",dd0->GetRMS()));
  stats0->SetShadowColor(0);
  //stats0->Draw();
  ///dd0->GetListOfFunctions()->Add(stats0);
  
  TPaveStats* stats1 = new TPaveStats(0.55,0.50,0.90,0.70,"brNDC");
  stats1->SetFillColor(kWhite);
  stats1->SetName("stats1");
  stats1->SetTextColor(kRed+2);
  stats1->AddText("TMass13_AC");
  stats1->SetTextFont(10); // not bold
  stats1->AddText(Form("Entries: %.0f",ddmerged->GetEntries()));
  stats1->AddText(Form("Mean: %.2f",ddmerged->GetMean()));
  stats1->AddText(Form("Std Dev: %.2f",ddmerged->GetRMS()));
  stats1->SetShadowColor(0);
  //stats1->Draw();
  //ddmerged->GetListOfFunctions()->Add(stats1);


  //exponantial fit parameters
  TF1 *fit_func = new TF1("fit_func","expo",310,1300);//28 feb bu fiti kullandin.. 
  fit_func->SetLineColor(2); 
  ddmerged->Fit(fit_func,"R");
  gStyle->SetOptFit(0);
 
  TLegend* legend = new TLegend(0.35, 0.80, 0.75, 0.90); // (x1, y1, x2, y2) in NDC coordinates
  legend->SetBorderSize(1);
  legend->SetFillColor(0);
  legend->SetTextSize(0.03);

  legend->AddEntry(fit_func, "Fit: expo", "l");
  // Add entries to the legend for each histogram
  legend->AddEntry(dd0, Form("before_correction (%.0f entries)", dd0->GetEntries()),  "lep");
  legend->AddEntry(ddmerged, Form("after_correction (%.0f entries)",  ddmerged->GetEntries()), "lep");
  legend->Draw();


}