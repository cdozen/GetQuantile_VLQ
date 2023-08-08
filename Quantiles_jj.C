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
void Quantiles_jj(){

//signal
TFile *f1 = new TFile ("/Users/dozen-altuntas/Desktop/Quantile/data/Signal/MergedBins/20230411_3T_2018UL_Signal_FullBRew_forcut7/BkgEst3Tlistinput2018ULData.root","read"); 


//25mart-cut5=pol3- fullrange
//TFile *f1= new TFile("FullRange_25Mart/20230325_3T_2018UL_Mtop140_FullBRew_cut7/BkgEst3Tlistinput2018ULData.root","read");
//25mart rebinX2 cut5 pol3
//TFile *f1 = new TFile ("15Mart_inputs/20230316_3T_2018UL_Mtop140_FullBRew_cut5pol3/BkgEst3Tlistinput2018ULData.root","read");//cut5pol3 cut7 tested 16Mart!
  //TH2F* dd1 = (TH2F*)f1->Get("TPMassvsDRjjW_CD"); //%80

//fit DRbbH cut newcut_1=f2 =cut7
//TFile *f2 = new TFile ("fitcuts_rebinned20/20230227_3T_2018UL_Mtop140_FullBRew_cut5drbbfit70expo/BkgEst3Tlistinput2018ULData.root","read");
//12 March corrected quantile
//TFile *f2 = new TFile ("fitcuts_rebinned20/20230312_3T_2018UL_Mtop140_FullBRew/BkgEst3Tlistinput2018ULData_12MartDRbbH_singleYbinquantile.root","read");


//dd1=TPMassvsDRjjW_CD
TH2F* dd1 = (TH2F*)f1->Get("TPMassvsDRjjW_CD");
//dd1->GetXaxis()->SetRangeUser(300, 1100); // set the X axis range to be from 0 to 1000
//dd1->RebinX(2);

//create canvas and test print

 TCanvas * can = new TCanvas("can", "can", 600, 450);
 //can->cd();
 dd1->Draw("Colz");
 
//int nRebin = 5.;
 //SetProjectionY for DRbbHiggs

TH1F * zz[50];

for(int i =0;i<dd1->GetNbinsX();i++){

TString hname= Form("ProjectionY_%d",i+1); //Get DR plots depends on each TprimeMass bins
zz[i] = (TH1F*) dd1->ProjectionY(hname,i+1,i+1);// calculating the quantiles for the full range of Y-axis bins for each value of i.
//zz[i] = (TH1F*) dd1->ProjectionY(hname,i+1,i+1); //projecting only a single Y-axis bin for each value of i.
//TH1F* h1d = (TH1F*) dd1->ProjectionY(hname, i+1, i+1);
  //zz[i] = (TH1F*) h1d->Rebin(nRebin, hname + "_rebin");

  //zz[i]->Rebin(10);
}
TCanvas * can2 = new TCanvas("can2", "can2", 800, 600);
//double n= dd->GetNbinsY()/2;
can2->Divide(5,10);
can2->cd();
std::cout<<"NbinsX:"<<dd1->GetNbinsX()<<std::endl;
std::cout<<"NbinsY:"<<dd1->GetNbinsY()<<std::endl;

  //Quantiles: 20
  const int nq  = 50;
  Double_t xq[nq];     // position where to compute the quantiles in [0,1]
  Double_t yq1[nq];  // array to contain the quantiles
  Double_t yq2[nq];  // array to contain the quantiles
double a,b;
//b=0.50;
//b=0.65;
b=0.50; //if b=0.5 DRbbHiggs <1 for Mass 700GeV if b=0.6 DRbbHiggs~1.03.. if b=0.7 DrbbHiggs~1.14
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
  gr->SetMarkerColor(kRed);
  gr->SetMarkerStyle(20);
  //gr->SetMarkerColor(kGreen+2);
  //gr->SetMarkerSize(1.5);
  //gr->SetMarkerStyle(32);
  gr->SetLineWidth(0);
  gr->SetTitle("DR_jjW_2M1L_signal");
  gr->GetXaxis()->SetTitle("TprimeMass(GeV)");
  gr->GetYaxis()->SetTitle("quantile");
  gr->Draw("apl");
  //gPad->BuildLegend();
/*
  TF1 *f4 = new TF1("f4","expo+[c]",300,1300);//28 feb bu fiti kullandin..
  //TF1 *g2 = new TF1("g2","pol3",300,1270);//1.sirada
  TF1 *g2 = new TF1("g2","pol4",300,1230);//full bin range 1.sirada
  //TF1 *g2 = new TF1("g2","pol4",300,1250);//rebinX*2 
  //TF1 *g2 = new TF1("g2","pol2(2)+expo(0)",340,1290);
  g2->SetLineColor(2); 
  //f4->SetLineColor(2); 
  //gr->Fit(f4,"R");
  gr->Fit(g2,"R");
*/
/*
gr->Fit("pol4","SR","",280,1270); //for fullrange!!
//gr->Fit("pol5","SR+","",290,1270);
//gr->Fit("pol6","SR+","",290,1270);
TF1* fitFunc = gr->GetFunction("pol4"); // get the fit function
//TF1* fitFunc5 = gr->GetFunction("pol5");
//TF1* fitFunc6 = gr->GetFunction("pol6");
TVirtualFitter* fitter = TVirtualFitter::GetFitter(); // get the TVirtualFitter object
TH1F* hConfIntervals = new TH1F("hConfIntervals", "Confidence Intervals", fitFunc->GetNpx(), fitFunc->GetXmin(), fitFunc->GetXmax());
fitFunc->SetLineColor(kRed);
fitFunc->SetLineWidth(2); 
//fitFunc5->SetLineColor(28);
//fitFunc5->SetLineWidth(2);
//fitFunc6->SetLineColor(kBlue);
//fitFunc6->SetLineWidth(2);  
  
fitter->GetConfidenceIntervals(hConfIntervals); // get the confidence intervals

hConfIntervals->SetFillColorAlpha(kBlue, 0.2);
hConfIntervals->Draw("e6 SAMEBkgEst3Tlistinput2018ULData.root"); // draw the confidence intervals as a band

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

// add an entry to the legend
//legend->AddEntry(gr, "RebinX*2", "");
legend->AddEntry(gr, "Full Range", "");
legend->AddEntry(gr, "50% quantile", "p"); // (object, label, option)
//legend->AddEntry(fitFunc, "Fit: pol4", "l"); //defult for pol3
//legend->AddEntry(fitFunc5, "Fit: pol5", "l");
//legend->AddEntry(fitFunc6, "Fit: pol6", "l");
//legend->AddEntry(hConfIntervals, "%95 CL band", "f");
legend->Draw();


//TFile f("Outputs/FullRange/JJW_FULLRANGE_80_pol4.root","RECREATE");
//TFile f("Outputs/RebinX2/JJW_REBINX2_80_pol4.root","RECREATE");

 // gr->Write();
  
//  f.Write();

//exponantial fit parameters

//TF1 *f1 = new TF1("f1","pol1", 300, 600);
//TF1 *f2 = new TF1("f2","expo+[c]",600,1196);
//TF1 *total = new TF1("total","pol1(0)+expo(2)+[c]",300,1196);

//TF1 *f3 = new TF1("f3","pol2+[c]", 300, 1000);

//TF1 *f4 = new TF1("f4","expo+[c]",330,1250);//28 feb bu fiti kullandin.. 


  //TF1 *g2 = new TF1("g2","expo+[c]",310,760);
  //TF1 *g1 = new TF1("m1","gaus",290,700);
  //TF1 *g2 = new TF1("m2","gaus",785,1200);
  //TF1 *total = new TF1("mstotal","expo+[c]+gaus",340,1270);// bu da 5.sirada
  //TF1 *total = new TF1("mstotal","gaus(0)+gaus(2)",310,1270);// 5.sirada
  //TF1 g3 = new TF1("m3","gaus",110,121);
  //TF1 *g2 = new TF1("g2","(exp([p0]+[p1]*x)*[c])",290,1290);

//TF1 *g2 = new TF1("g2","pol2(0)+gaus(0)",300,1290); //5.sirada
//TF1 *g2 = new TF1("g2","pol3",320,1290); //1.sirada
//TF1 *g2 = new TF1("g2","pol2(0)+pol1(0)",320,1290); //5.sirada
//TF1 *g2 = new TF1("g2","pol0+expo(1)",330,1290);//2.sirada
//TF1 *g2 = new TF1("g2","pol0+expo(0)+[c]",330,1290);//2.sirada
//TF1 *fitFunc = new TF1("fitFunc", "[0]+exp([1]*x)", 330, 1290);
//TF1 *g2 = new TF1("g2","pol3",300,1290);//1.sirada
//pol3 = p0 + p1*x + p2*x*x + p3*x*x*x
  //g2->SetLineColor(2);
  //g3->SetLineColor(3);
//TF1* func = new TF1("func", "[0] * exp(-pow(x/[1], [2]))", 300, 1290);
//// Fit each function and add it to the list of functions
//Double_t par[3];
  //func->GetParameter(0);
  //func->GetParameter(1);
  //func->GetParameter(2);
 
  //gr->Fit(func,"R");
  //gr->Fit(g1,"R");
//gr->Fit(g2,"RVS");
//gr->GetFunction("g2");
//gr->Fit(f1,"RV");
//gr->Fit(f4,"R");
//gr->Fit(total,"R");
//gr->Fit(f3,"RV");
//gr->Fit(f4,"RSV");
//gr->Fit(total,"RV");


//jjw-pol4fit:fullrange
/*gr->Fit("pol4","SR","",290,1270); 
1.681746e+00*pow(Reconstructed_Tprime->M(),0) + 9.749353e-03*pow(Reconstructed_Tprime->M(),1) - 2.959029e-05*pow(Reconstructed_Tprime->M(),2) + 2.929847e-08*pow(Reconstructed_Tprime->M(),3) - 9.536934e-12*pow(Reconstructed_Tprime->M(),4)
*/
/*
/jjw-pol4fit:rebinX
gr->Fit("pol4","SR","",290,1270); 
1.296805e+00*pow(Reconstructed_Tprime->M(),0) + 1.244615e-02*pow(Reconstructed_Tprime->M(),1) - 3.640947e-05*pow(Reconstructed_Tprime->M(),2) + 3.637701e-08*pow(Reconstructed_Tprime->M(),3) - 1.209537e-11*pow(Reconstructed_Tprime->M(),4)
*/

}