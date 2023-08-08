/**
 * Get quantile from 2D dR vs tprimeMass histogram
 * This will give you a complete picture of the Y-axis distribution for each bin in the X-axis, and you can calculate quantiles for each of these 1D histograms using the TH1F::GetQuantiles method.
 * CDozen
*/
#include <iostream>
//#include <cmath>
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
void Quantiles_relht(){

//Mtop140 2M1L with weighted all cuts with cut5

//TFile *myfile = new TFile ("defcuts/20230227_3T_2018UL_Mtop140_FullBRew_v1/BkgEst3Tlistinput2018ULData.root","read");

//Mtop140 cut5 DrbbH and cut7 Drjj expo rebinned 20 
//TFile *myfile = new TFile ("20230227_3T_2018UL_Mtop140_FullBRew_cut5drbbfit70expo_cut7drjjwfit80expo_cut9others_rebinned20/BkgEst3Tlistinput2018ULData.root","read");
//fit DRbbH cut+ fit DrjjW newcut_2=f3
//TFile *f3 = new TFile ("fitcuts_rebinned20/20230227_3T_2018UL_Mtop140_FullBRew_cut5drbbfit70expo_cut7drjjwfit80expo/BkgEst3Tlistinput2018ULData.root","read");

//12 March corrected quantiles
//TFile *f3 = new TFile ("fitcuts_rebinned20/20230312_3T_2018UL_Mtop140_FullBRew/BkgEst3Tlistinput2018ULData.root","read");

//TFile *f3 = new TFile ("15Mart_inputs/20230316_3T_2018UL_Mtop140_FullBRew_cut5pol3_cut7pol4/BkgEst3Tlistinput2018ULData.root","read");
//TFile *f3 = new TFile ("15Mart_inputs/20230316_3T_2018UL_Mtop140_FullBRew_cu5pol3_cut7pol4newrange/BkgEst3Tlistinput2018ULData.root","read");

//24 Mart RebinX cut9 = cut7 pol4 and cut5 pol3
//TFile *f1= new TFile("RebinX2_InputFiles_24Mart/20230324_3T_2018UL_Mtop140_FullBRew_cut9/BkgEst3Tlistinput2018ULData.root","read");

//TFile *f1= new TFile("RebinX2_InputFiles_24Mart/20230324_3T_2018UL_Mtop140_FullBRew_rebinX_cut9/BkgEst3Tlistinput2018ULData.root","read");
//INPUT_REBINX
//cut5pol3-0.70- cuy7-pol4 0.80- 
//TFile *f1= new TFile("INPUTS_REBINX/20230326_3T_2018UL_Mtop140_FullBRew_REBINX_cut5pol3_70_cut7pol4_80/BkgEst3Tlistinput2018ULData.root","read");

//FULL_RANGE
//TFile *f1= new TFile("data/FullRange/20230326_3T_2018UL_Mtop140_FullBRew_FULLRANGEcut5pol3_65_cut7pol4_80/BkgEst3Tlistinput2018ULData.root","read");



//11 April signal region 
TFile *f1 = new TFile ("/Users/dozen-altuntas/Desktop/Quantile/data/Signal/MergedBins/20230412_3T_2018UL_Signal_FullBRew_forcut9/BkgEst3Tlistinput2018ULData.root","read"); 
TH2F* dd = (TH2F*)f1->Get("TPMassvsRelative_THT_CD");

//TFile f("myfile_cut5_0.50_2M1L_reweigh_reltht.root","RECREATE");

//create canvas and test print
 TCanvas * can = new TCanvas("can", "can", 600, 450);
 //TAxis* yAxis = dd->GetYaxis();
//yAxis->SetRangeUser(0.08, 0.48);
 dd->Draw("Colz");
 //dd->RebinX(2);

 //SetProjectionY for DRbbHiggs

TH1F * zz[50];
for(int i =0;i<dd->GetNbinsX();i++){
//TString hname= Form("ProjectionX_%d",i);
//zz[i] = (TH1F*) dd->ProjectionX(hname,i);
TString hname= Form("ProjectionY_%d",i); //Get DR plots depends on each TprimeMass bins
zz[i] = (TH1F*) dd->ProjectionY(hname,i+1,i+1);
  //zz[i]->Draw();
}
TCanvas * can2 = new TCanvas("can2", "can2", 800, 600);
//double n= dd->GetNbinsY()/2;
can2->Divide(5,10);
can2->cd();
std::cout<<"NbinsX:"<<dd->GetNbinsX()<<std::endl;
std::cout<<"NbinsY:"<<dd->GetNbinsY()<<std::endl;

  //Quantiles: 20
  const int nq  = 50;
  Double_t xq[nq];     // position where to compute the quantiles in [0,1]
  Double_t yq1[nq];  // array to contain the quantiles
  Double_t yq2[nq];  // array to contain the quantiles
double a,b; //RelHTCut=0.4; must >0.4
b=0.05; //if b=0.5 DRbbHiggs <1 for Mass 700GeV if b=0.6 DRbbHiggs~1.03.. if b=0.7 DrbbHiggs~1.14
//Double_t b[5]={0.5,0.60,0.70,0.80,0.90};
// y bins array
Double_t xbins[nq]; //dR
Double_t ybins[nq];
Double_t quantile[nq]; // mass quantile
for(int i=0;i<dd->GetNbinsX();i++){
    can2->cd(i+1);
    zz[i]->Draw();
    zz[i]->GetQuantiles(1,&a,&b);
    TAxis* xAxis = dd->GetXaxis();
    TAxis* yAxis = dd->GetYaxis();
    //xbins[i] = ( Double_t (i) + 1)/(nq)
    ybins[i]=yAxis->GetBinUpEdge(i);
    //xbins[i]=xAxis->GetBinCenter(i); // TMAss X-axis starts from 200 with GetBinCenter
    xbins[i]=xAxis->GetBinUpEdge(i); //TMAss X-axis starts from 300 with GetBinUpEdge.
    quantile[i]=a;
    std::cout<<"bin"<<i<<"\t LE:"<<xbins[i]<<"\t a:"<<a<<"\t b:"<<b<<std::endl;
    //std::cout<<"bin"<<i<<"\t LE_Y:"<<ybins[i]<<"\t a:"<<a<<"\t b:"<<b<<std::endl;
    //std::cout<<"binY"<<i<<"\t LEY:"<<ybins[i]<<std::endl;
}


TCanvas * can3 = new TCanvas("can3", "can3", 800, 600);
can3->cd();
 TGraph *gr = new TGraph(nq,xbins, quantile); 
 
    //gStyle->SetPalette(kSolar);
  //TGraph *g1 = new TGraph(5,x,y1); g1->SetTitle("Graph with a red star");
  gPad->SetGrid();
  //gr->SetLineColor(kRed+2); //cut7
  //gr->SetMarkerColor(kRed+2);
  //gr->SetLineColor(0);
  gr->SetMarkerColor(kRed);
  gr->SetMarkerStyle(20); 
  //gr->SetMarkerColor(kGreen+2);
  //gr->SetMarkerSize(1.5);
  //gr->SetMarkerStyle(32);
  gr->SetTitle("Relative_HT_2M1L_weighted");
  gr->GetXaxis()->SetTitle("TprimeMass(GeV)");
  gr->GetYaxis()->SetTitle("quantile");
  gr->Draw("ap");


  //gPad->BuildLegend();

  //can3->Update();

//exponantial fit parameters

  //TF1 *g2 = new TF1("g2","expo+[c]",290,1290);
  
  //TF1 *f3 = new TF1("f3","pol2+expo", 300, 1200);

  //TF1 *f1 = new TF1("f1","gaus", 300, 700);
  
  //TF1 *f2 = new TF1("f2","pol2",600,1200);
  //TF1 *f6 = new TF1("f6","gaus+pol2",300,1200);
  //TF1 *f5 = new TF1("f5","pol2",290,1220);//cok iyi
  //TF1 *f5 = new TF1("f5","pol4",290,1300);//cok iyi bunu da sonra denedein candan 16 mart 22:09
  
  //TF1 *f7 = new TF1("f5","f2+f1",300,1200);
  
  //TF1 *total = new TF1("total","pol2(2)+expo",290,1200);//1. sirada


  //g2->SetLineColor(2);
  //g3->SetLineColor(3);

//// Fit each function and add it to the list of functions
  //f1->FixParameter(3,701.7);
  //f1->FixParameter(2,0.4208);
  //f1->FixParameter(3,701.7);
  //f1->FixParameter(4,348.6);
  //f2->FixParameter(1);
  //f2->FixParameter(4,0.0004567);
  //f6->FixParameter(3,701.7);
  //f6->FixParameter(1,0.0004567);
  
  //gr->Fit(f1,"RV");
  //gr->Fit(f2,"R+");
  
  //gr->Fit(f5,"R");

  //can3->SaveAs("Result.C");

  
  //can3->Update();
  //TPaveStats *stats1 = (TPaveStats*)gr->GetListOfFunctions()->FindObject("stats");
  //TPaveStats *stats2 = (TPaveStats*)gr2->GetListOfFunctions()->FindObject("stats");
  //stats1->SetTextColor(kBlue);
  //stats2->SetTextColor(kRed);
  //stats1->SetX1NDC(0.12); stats1->SetX2NDC(0.32); stats1->SetY1NDC(0.75);
  //stats2->SetX1NDC(0.72); stats2->SetX2NDC(0.92); stats2->SetY1NDC(0.78);
  //can3->Modified();
  //return c1;
  //can3->Write();
  //gr->Write();
  //f.Write();
  //Double_t p0 = f5->GetParameter(0);
  //Double_t p1 = f5->GetParameter(1);
  //Double_t p2 = f5->GetParameter(2);
  //Double_t p3 = f5->GetParameter(3);




gStyle->SetOptFit(1111);
/*
gr->Fit("pol4","SR","",280,1300); //topw->pol5-300/1190
//gr->Fit("pol5","SR+","",280,1300); //topw->pol5-300/1190
//gr->Fit("pol6","SR+","",280,1300);
//gr->Fit("pol7","SR+","",290,1300); //topw->pol5-300/1190
TF1* fitFunc = gr->GetFunction("pol4"); // get the fit function
//TF1* fitFunc5 = gr->GetFunction("pol5"); // get the fit function
//TF1* fitFunc6 = gr->GetFunction("pol6"); // get the fit function
//TF1* fitFunc7 = gr->GetFunction("pol7");
TVirtualFitter* fitter = TVirtualFitter::GetFitter(); // get the TVirtualFitter object
TH1F* hConfIntervals = new TH1F("hConfIntervals", "Confidence Intervals", fitFunc->GetNpx(), fitFunc->GetXmin(), fitFunc->GetXmax());
fitFunc->SetLineColor(kBlue);
fitFunc->SetLineWidth(2);  
//fitFunc5->SetLineColor(kGreen);
//fitFunc5->SetLineWidth(2);
//fitFunc6->SetLineColor(kBlue);
//fitFunc6->SetLineWidth(2);  
//fitFunc7->SetLineColor(kBlack);
//fitFunc7->SetLineWidth(2);  
//fitFunc3->SetLineColor(9);
  
fitter->GetConfidenceIntervals(hConfIntervals); // get the confidence intervals

hConfIntervals->SetFillColorAlpha(kBlue, 0.2);
hConfIntervals->Draw("e6 SAME"); // draw the confidence intervals as a band


// Create an empty string called "Correction" using the TString class
TString Correction = "";

// Loop over the first four parameters of the fit function
for (int i = 0; i < 5; i++)
{
  // Get the i-th fit parameter
  double param = fitFunc->GetParameter(i);

  // Check the sign of the parameter and add the appropriate sign symbol to the correction string
  if (param >= 0 && i > 0)
  {
    Correction += " + ";
  }
  else if (param < 0)
  {
    Correction += " - ";
    param = -param;
  }

  // Create a stringstream object to convert the parameter to scientific notation
  std::stringstream myparameter;
  myparameter << std::scientific << param;

  // Define a string indicating what the correction is based on (mass or eta, for example)
  std::string cutTP = "Reconstructed_Tprime->M()";

  // Add a term to the Correction TString that includes the i-th fit parameter
  Correction += Form("%s*pow(%s,%d)", myparameter.str().c_str(), cutTP.c_str(), i);
}

// Print the Correction TString to the console
std::cout << "Correction: " << Correction << std::endl;
//In this output, there is a minus sign before the first term and a plus sign between each subsequent term, as appropriate based on the sign of the corresponding fit parameter.
*/
TLegend* legend = new TLegend(0.40, 0.70, 0.60, 0.90); // (x1, y1, x2, y2) in NDC coordinates

// set the legend style
legend->SetBorderSize(1);
legend->SetFillColor(0);
legend->SetTextSize(0.03);

//legend->AddEntry(gr, "RebinX*2", "");
legend->AddEntry(gr, "Full Range", "");
legend->AddEntry(gr, "0.5% quantile", "p"); // (object, label, option)
//legend->AddEntry(fitFunc, "Fit: pol4", "l"); //defult for pol3
//legend->AddEntry(fitFunc5, "Fit: pol5", "l"); //defult for pol3
//legend->AddEntry(fitFunc6, "Fit: pol6", "l"); //defult for pol3
//legend->AddEntry(fitFunc7, "Fit: pol7", "l");
//legend->AddEntry(hConfIntervals, "%95 CL band", "f");
legend->Draw();


//TFile f("Outputs/FullRange/RELHT_FULLRANGE_05_pol4.root","RECREATE");
//TFile f("Outputs/RebinX2/rel_HT_REBINX_05_pol4.root","RECREATE");
//gr->Write();
//f.Write();


 
}