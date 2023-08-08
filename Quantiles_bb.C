/**
 * Get quantile from 2D dR vs tprimeMass histogram
 * Then plot dR vs Quantile..
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
void Quantiles_bb(){

//24Mart_cut5// BG 
//TFile *f1 = new TFile ("MergedBins_InputRootFiles_24Mart/20230324_3T_2018UL_Mtop140_FullBRew_forcut5/BkgEst3Tlistinput2018ULData.root","read"); 
//11 April signal region 
TFile *f1 = new TFile ("/Users/dozen-altuntas/Desktop/Quantile/data/Signal/MergedBins/20230411_3T_2018UL_Signal_FullBRew_forcut5/BkgEst3Tlistinput2018ULData.root","read"); 
TH2F* dd1 = (TH2F*)f1->Get("TPMassvsDRbbHiggs_CD"); //DR_bbHiggs



  //TFile *f1 = new TFile ("15Mart_inputs/20230316_3T_2018UL_Mtop140_FullBRew_cut5pol3/BkgEst3Tlistinput2018ULData.root","read");//cut5pol3 cut7 tested 16Mart!
  //TH2F* dd1 = (TH2F*)f1->Get("TPMassvsDRjjW_CD"); //%80
  
  //TFile *f3 = new TFile ("15Mart_inputs/20230316_3T_2018UL_Mtop140_FullBRew_cu5pol3_cut7pol4newrange/BkgEst3Tlistinput2018ULData.root","read");
  //TH2F* dd = (TH2F*)f3->Get("TPMassvsRelative_THT_CD");  //%0.5 

  //TFile *f4 = new TFile ("15Mart_inputs/20230316_3T_2018UL_Mtop140_FullBRew_cut9pol4/BkgEst3Tlistinput2018ULData.root","read");
  //TH2F* dd = (TH2F*)f4->Get("TPMassvsDRBTopW_CD"); //%80
  
//create canvas and test print

 TCanvas * can = new TCanvas("can", "can", 600, 450);
 //can->cd();
//TAxis* yAxis = dd1->GetYaxis();
//yAxis->SetRangeUser(0.79, 2.66);
 dd1->Draw("Colz");
 
//int nRebin = 5.;
 //SetProjectionY for DRbbHiggs
//dd1->RebinX(2);
TH1F * zz[50];
const int nq  = 50;
double a,b;
b=0.65;

for(int i =0;i<dd1->GetNbinsX();i++){

TString hname= Form("ProjectionY_%d",i+1); //Get DR plots depends on each TprimeMass bins
zz[i] = (TH1F*) dd1->ProjectionY(hname,i+1,i+1);
}
TCanvas * can2 = new TCanvas("can2", "can2", 800, 600);
//double n= dd->GetNbinsY()/2;
can2->Divide(5,10);
can2->cd();
std::cout<<"NbinsX:"<<dd1->GetNbinsX()<<std::endl;
std::cout<<"NbinsY:"<<dd1->GetNbinsY()<<std::endl;

  //Quantiles: 20

  Double_t xq[nq];     // position where to compute the quantiles in [0,1]
  Double_t yq1[nq];  // array to contain the quantiles
  Double_t yq2[nq];  // array to contain the quantiles

//b=0.50;
//b=0.65;
 //if b=0.5 DRbbHiggs <1 for Mass 700GeV if b=0.6 DRbbHiggs~1.03.. if b=0.7 DrbbHiggs~1.14
//Double_t b[5]={0.5,0.60,0.70,0.80,0.90};
// y bins array
Double_t xbins[nq]; //dR
Double_t ybins[nq];
Double_t quantile[nq]; // mass quantile
for(int i=0;i<dd1->GetNbinsX();i++){
    can2->cd(i+1);
    zz[i]->Draw();
    zz[i]->GetQuantiles(1,&a,&b);// calculate the quantiles for zz[i] and store it &a. 
    TAxis* xAxis = dd1->GetXaxis();
    TAxis* yAxis = dd1->GetYaxis();
    //xbins[i] = ( Double_t (i) + 1)/(nq)
    //ybins[i] = ( Double_t (i) + 1)/(nq)
    ybins[i]=yAxis->GetBinUpEdge(i);
    xbins[i]=xAxis->GetBinUpEdge(i);
    //xbins[i]=xAxis->GetBinCenter(i); // TMAss X-axis starts from 200 with GetBinCenter
    //xbins[i]=xAxis->GetBinUpEdge(i); //TMAss X-axis starts from 300 with GetBinUpEdge.
    quantile[i]=a; //assign the a value to quantile[i]
    
    std::cout<<"bin"<<i<<"\t LE:"<<xbins[i]<<"\t a:"<<a<<"\t b:"<<b<<std::endl;
    //std::cout<<"bin"<<i<<"\t LE_Y:"<<ybins[i]<<"\t a:"<<a<<"\t b:"<<b<<std::endl;
    //std::cout<<"binY"<<i<<"\t LEY:"<<ybins[i]<<std::endl;
}


TCanvas * can3 = new TCanvas("can3", "can3", 800, 600);
can3->cd();
 TGraph *gr = new TGraph(nq,xbins, quantile); 
 //gr->GetXaxis()->SetLimits(250, 1100);

 
  
    //gStyle->SetPalette(kSolar);
  //TGraph *g1 = new TGraph(5,x,y1); g1->SetTitle("Graph with a red star");
  gPad->SetGrid();
  gStyle->SetOptFit(0);
  //gr->SetLineColor(0); //cut7
  gr->SetMarkerColor(kRed);
  gr->SetMarkerStyle(20);
  gr->SetLineWidth(0);
  //gr->SetMarkerColor(kGreen+2);
  //gr->SetMarkerSize(1.5);
  //gr->SetMarkerStyle(32);
  gr->SetTitle("DR_bb{Higgs}_2M1L_signal_region");
  //gr->SetTitle("DR_jjW_2M1L_weighted");
  gr->GetXaxis()->SetTitle("TprimeMass(GeV)");
  gr->GetYaxis()->SetTitle("quantile");
  
 
  gr->Draw("ap");
  //gPad->BuildLegend();
  //TF1 *f4 = new TF1("f4","expo+[c]",300,1300);//28 feb bu fiti kullandin..
  //TF1 *g2 = new TF1("g2","pol3",290,1270);//perfectly fit rebinX2
  //TF1 *g2 = new TF1("g2","pol4",290,1290);//pol4 perfectly fit to rebinX2 and full bin 
  //TF1 *g2 = new TF1("g2","pol2(2)+expo(0)",340,1290);
  //g2->SetLineColor(2); 
  //f4->SetLineColor(2); 
  //gr->Fit(f4,"R");
  //gr->Fit(g2,"SR");

/*
gr->Fit("pol3","SR","",300,1300); //topw->pol5-300/1190
TF1* fitFunc = gr->GetFunction("pol3"); // get the fit function

TVirtualFitter* fitter = TVirtualFitter::GetFitter(); // get the TVirtualFitter object
TH1F* hConfIntervals = new TH1F("hConfIntervals", "Confidence Intervals", fitFunc->GetNpx(), fitFunc->GetXmin(), fitFunc->GetXmax());
fitFunc->SetLineColor(kBlue);
fitFunc->SetLineWidth(2);  
//fitFunc3->SetLineColor(9);
  
fitter->GetConfidenceIntervals(hConfIntervals); // get the confidence intervals

hConfIntervals->SetFillColorAlpha(kBlue, 0.2);
//hConfIntervals->Draw("e6 SAME"); // draw the confidence intervals as a band



  // Create an empty string called "Correction" using the TString class
TString Correction = "";

// Loop over the first four parameters of the fit function
for (int i = 0; i < 4; i++)
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

// add an entry to the legend
//legend->AddEntry(gr, "RebinX*2", "");
legend->AddEntry(gr, "Full Range", "");
//legend->AddEntry(fitFunc, "Fit: pol3", "l"); //defult for pol3
legend->AddEntry(gr, "65% quantile", "lep"); // (object, label, option)
//legend->AddEntry(hConfIntervals, "%95 CL band", "f");
//legend->AddEntry(f4, "Fit: expo+[c]", "l"); //default
legend->Draw();

//TFile f("Outputs/FullRange/BBH_FULLRANGE_65_pol3.root","RECREATE");
//TFile f("Outputs/RebinX2/BBH_REBINX2_70_pol3.root","RECREATE");
//  gr->Write();
//  f.Write();


}