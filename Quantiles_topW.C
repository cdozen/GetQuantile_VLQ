/**
 * Full Range Get quantile from 2D dR vs tprimeMass histogram
 * Then plot dR vs Quantile..
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
#include <TFitResultPtr.h>
void Quantiles_topW()
{
/*DRtopWcut<1.2*/
/*=================================================================================================================================*/
//INPUT_REBINX-- cut5:70-pol3 , cut7:80-pol4, cut9:05-pol4 
 // TFile *f1= new TFile("data/RebinX2/20230326_3T_2018UL_Mtop140_FullBRew_REBINX_cut5pol3_70_cut7pol4_80_cut9pol4_0.5/BkgEst3Tlistinput2018ULData.root","read");
/*=================================================================================================================================*/
//INPUT_FULLRANGE-- cut5:65-pol3 , cut7:80-pol4, cut9:05-pol4 
//TFile *f1= new TFile("data/FullRange/20230326_3T_2018UL_Mtop140_FullBRew_FULLRANGE_cut5pol3_70_cut7pol4_80_cut9pol4_0.5/BkgEst3Tlistinput2018ULData.root","read");

/*=================================================================================================================================*/

//11 April Signal region 
//TFile *f1 = new TFile ("/Users/dozen-altuntas/Desktop/Quantile/data/Signal/MergedBins/20230412_3T_2018UL_Signal_FullBRew_forcut11/BkgEst3Tlistinput2018ULData.root","read");  

  TH2F* dd2 = (TH2F*)f1->Get("TPMassvsDRBTopW_CD");
//create canvas and test print
  TCanvas * can = new TCanvas("can", "can", 600, 450);
  //TAxis* yAxis = dd2->GetYaxis();
  //yAxis->SetRangeUser(0.8, 2.3);
  dd2->Draw("Colz");
  //dd2->RebinX(2);

  TH1F * zz[50];
  const int nq  = 50;
  double a,b;
  b=0.65; 
  
  Double_t xbins[nq]; //dR
  Double_t ybins[nq];
  Double_t quantile[nq]; // mass quantile

  for(int i =0;i<dd2->GetNbinsX();i++){
  TString hname= Form("ProjectionY_%d",i+1); //Get DR plots depends on each TprimeMass bins
  zz[i] = (TH1F*) dd2->ProjectionY(hname,i+1,i+1);
  }
  TCanvas * can2 = new TCanvas("can2", "can2", 800, 600);
  can2->Divide(5,10);
  can2->cd();
  std::cout<<"NbinsX:"<<dd2->GetNbinsX()<<std::endl;
  std::cout<<"NbinsY:"<<dd2->GetNbinsY()<<std::endl;


  for(int i=0;i<dd2->GetNbinsX();i++){
    can2->cd(i+1);
    zz[i]->Draw();
    zz[i]->GetQuantiles(1,&a,&b);
    TAxis* xAxis = dd2->GetXaxis();
    TAxis* yAxis = dd2->GetYaxis();
    ybins[i]=yAxis->GetBinUpEdge(i);
    //xbins[i]=xAxis->GetBinCenter(i); // TMAss X-axis starts from 200 with GetBinCenter
    xbins[i]=xAxis->GetBinUpEdge(i); //TMAss X-axis starts from 300 with GetBinUpEdge.
    quantile[i]=a;
    std::cout<<"bin"<<i<<"\t LE:"<<xbins[i]<<"\t a:"<<a<<"\t b:"<<b<<std::endl;
  }

  /*====//Create canvas for quantile plot //====*/  
  TCanvas * can3 = new TCanvas("can3", "can3", 800, 600);
  can3->cd();
  /*====//CCalculate quantile with TGraph=============================================================*/ 
  //nq: bin number | xbins: TprimeMass bin range |  quantile: quantile value of Y for on each xbins
  /*===================================================================================================*/ 
  TGraph *gr = new TGraph(nq,xbins, quantile); 
  gPad->SetGrid();
  gStyle->SetOptFit(1111);
  gr->SetLineColor(0); 
  
  /*==//for FullRange//==*/
  //gr->SetMarkerColor(kRed+2); 
  gr->SetMarkerColor(kRed);
  gr->SetMarkerStyle(20); 
  //gr->SetLineColor(kBlue+2);
  
  /*==//for RebinX2//==*/  
  //gr->SetMarkerColor(kGreen+2); 
  //gr->SetMarkerSize(1.5);       
  //gr->SetMarkerStyle(32);
  /*==//Set Title//==*/  
  gr->SetTitle("DR_TopW_2M1L_weighted");
  gr->GetXaxis()->SetTitle("TprimeMass(GeV)");
  gr->GetYaxis()->SetTitle("quantile");
  gr->Draw("ap");

  /*====//Fit Functions//===*/
  //gStyle->SetOptFit(1111);
/*  gr->Fit("pol6","SR","",280,1280); 
  //gr->Fit("pol5","SR+","",280,1280);
  //gr->Fit("pol6","SR+","",280,1280);
  TF1* fitFunc = gr->GetFunction("pol6"); // get the fit function
  //TF1* fitFunc5 = gr->GetFunction("pol5"); 
  //TF1* fitFunc6= gr->GetFunction("pol6"); 
  TVirtualFitter* fitter = TVirtualFitter::GetFitter(); // get the TVirtualFitter object
  TH1F* hConfIntervals = new TH1F("hConfIntervals", "Confidence Intervals", fitFunc->GetNpx(), fitFunc->GetXmin(), fitFunc->GetXmax());
  fitFunc->SetLineColor(kRed);
  fitFunc->SetLineWidth(4); 
  //fitFunc5->SetLineColor(28);
  //fitFunc5->SetLineWidth(2);
  //fitFunc6->SetLineColor(kBlue);
  //fitFunc6->SetLineWidth(2);   
  fitter->GetConfidenceIntervals(hConfIntervals); // get the confidence intervals
  hConfIntervals->SetFillColorAlpha(kBlue, 0.2);
  hConfIntervals->Draw("e6 SAME"); // draw the confidence intervals as a band


  //====//Print out the polynomial fit function//=== 
  //Create an empty string called "Correction" using the TString class
  TString Correction = "";
  // Loop over the first four parameters of the fit function
  for (int i = 0; i < 7; i++)
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
  */
  /*====//create a TLegend object//====*/
  TLegend* legend = new TLegend(0.40, 0.80, 0.60, 0.90); // (x1, y1, x2, y2) in NDC coordinates
  legend->SetBorderSize(1);
  legend->SetFillColor(0);
  legend->SetTextSize(0.03);

  //legend->AddEntry(gr, "RebinX*2", "");
  legend->AddEntry(gr, "Full Range", "");
  legend->AddEntry(gr, "65% quantile", "lep"); // (object, label, option)
  //legend->AddEntry(fitFunc, "Fit: pol6", "l"); //defult for pol3
  //legend->AddEntry(fitFunc5, "Fit: pol5", "l"); 
  //legend->AddEntry(fitFunc6, "Fit: pol6", "l"); 
  //legend->AddEntry(hConfIntervals, "%95 CL band", "f");
  legend->Draw();

  /*====//create new root file and save the quantile plot//====*/
  //TFile f("Outputs/FullRange/TOPW_FULLRANGE_85_pol6.root","RECREATE");
  //TFile f("Outputs/RebinX2/topW_REBINX_85_pol6.root","RECREATE");
  //gr->Write();
  //f.Write();


}  

