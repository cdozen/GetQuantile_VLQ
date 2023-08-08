/**
 * Get quantile from 2D dR vs tprimeMass histogram
 * This will give you a complete picture of the Y-axis distribution for each bin in the X-axis, and you can calculate quantiles for each of these 1D histograms using the TH1F::GetQuantiles method.
 * CDozen
 */
#include <iostream>
// #include <cmath>
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
void Mergebins100()
{
  //DR_bbHiggs
  //TFile *f1 = new TFile ("MergedBins_InputRootFiles_24Mart/20230324_3T_2018UL_Mtop140_FullBRew_forcut5/BkgEst3Tlistinput2018ULData.root", "read"); 
  //11 April signal region for drbbH %65 pol3 choosen 
  //but 13 April signal region B2G fit recommedation pol5 for DR_bbH 
  //TFile *f1 = new TFile ("/Users/dozen-altuntas/Desktop/Quantile/data/Signal/MergedBins/20230411_3T_2018UL_Signal_FullBRew_forcut5/ BkgEst3Tlistinput2018ULData.root","read"); 



  //signaldrjjw %75 pol6 choosen : 
  //TFile *f1 = new TFile ("/Users/dozen-altuntas/Desktop/Quantile/data/Signal/MergedBins/20230411_3T_2018UL_Signal_FullBRew_forcut7/ BkgEst3Tlistinput2018ULData.root","read"); 
  //TH2F* dd = (TH2F*)f1->Get("TPMassvsDRjjW_CD");

  //13 April signal region B2G fit recommedation pol7 for DRjjW
  //TFile *f1 = new TFile ("/Users/dozen-altuntas/Desktop/Quantile/data/Signal/MergedBins/20230413_3T_2018UL_Signal_FullBRew_B2G_forcut7/ BkgEst3Tlistinput2018ULData.root","read"); 
  //TH2F* dd = (TH2F*)f1->Get("TPMassvsDRjjW_CD");

  //Signal Relative HT:
  //TFile *f1 = new TFile ("/Users/dozen-altuntas/Desktop/Quantile/data/Signal/MergedBins/20230412_3T_2018UL_Signal_FullBRew_forcut9/ BkgEst3Tlistinput2018ULData.root","read"); 

  //13 April signal region B2G fit recommedation pol6 for RelHT
  TFile *f1 = new TFile ("/Users/dozen-altuntas/Desktop/Quantile/data/Signal/MergedBins/20230413_3T_2018UL_Signal_FullBRew_B2G_forcut9/ BkgEst3Tlistinput2018ULData.root","read"); 
  TH2F* dd = (TH2F*)f1->Get("TPMassvsRelative_THT_CD");


  //11 April Signal region 
  //TFile *f1 = new TFile ("/Users/dozen-altuntas/Desktop/Quantile/data/Signal/MergedBins/20230412_3T_2018UL_Signal_FullBRew_forcut11/  BkgEst3Tlistinput2018ULData.root","read"); 

  //13 April signal region B2G fit recommedation pol6 for DR_topw
  //TFile *f1 = new TFile ("/Users/dozen-altuntas/Desktop/Quantile/data/Signal/MergedBins/20230413_3T_2018UL_Signal_FullBRew_B2G_forcut11/  BkgEst3Tlistinput2018ULData.root","read"); 
  //TH2F* dd = (TH2F*)f1->Get("TPMassvsDRBTopW_CD");


  TCanvas *can = new TCanvas("can", "can", 600, 450);
  can->cd();
  //TAxis* yAxis = dd->GetYaxis();
  //yAxis->SetRangeUser(1.3, 2.5);
  dd->Draw("Colz");
  
  int nbinsX = dd->GetNbinsX();
  int threshold = 500;
  TH1F *zz[50];
  int nPlotted = 0;
  TCanvas *can2 = new TCanvas("can2", "can2", 800, 600);
  can2->Divide(5, 10);

  const int nq = 50;
  double a, b;
  b=0.05;
  //b = 0.75;
  // y bins array
  Double_t xbins[nq];
  Double_t ybins[nq];
  Double_t quantile[nq];
  Double_t Real_xbins[nq] = {-1};
  Double_t Real_quantile[nq] = {-1};
  std::vector<int> previousbin;

  for (int i = 0; i < nbinsX; i++)
  {

    TString hname = Form("ProjectionY_%d", i + 1);
    zz[i] = (TH1F *)dd->ProjectionY(hname, i + 1, i + 1);
    int nbinsY = zz[i]->GetNbinsX();
    previousbin.push_back(i);
    double nEntries = zz[i]->GetEntries();
    if (nEntries > threshold)
    {
      // draw histogram
      TString htitle = Form("ProjectionY for X bin %d", i + 1);
      zz[i]->SetTitle(htitle);
      can2->cd(i + 1);
      zz[i]->Draw();
      zz[i]->GetQuantiles(1, &a, &b);
      quantile[i] = a;
      TAxis *xAxis = dd->GetXaxis();
      TAxis *yAxis = dd->GetYaxis();
      ybins[i] = yAxis->GetBinUpEdge(i);
      xbins[i] = xAxis->GetBinUpEdge(i);
      std::cout << "bin" << i + 1 << "\t xbin:" << xbins[i] << "\t quantile:" << a << "\t percentage:" << b << std::endl;
      nPlotted++;
      // print entries after plotting
      nEntries = zz[i]->GetEntries();
      std::cout << "Plotted bin " << i + 1 << " has " << nEntries << " entries." << std::endl;
    }

    // bool Hepsini_al=false;
    //  merge bins
    if (nEntries < threshold)
    {
      //  if(i>46)Hepsini_al=true; // 47 ve ustu ise ve thr dusuk ise hepsini al..
      int kalanbin = 0;
    
      for (int j = i + 1; j < nbinsX; j++)
      {
        kalanbin = nbinsX - j;
        TString hname_m = Form("ProjectionY_%d", j + 1);
        TH1F *hist_m = (TH1F *)dd->ProjectionY(hname_m, j + 1, j + 1);
        nEntries += hist_m->GetEntries();
        zz[i]->Add(hist_m);
         
        if (nEntries >= threshold && kalanbin > 3)
        {
          std::cout << "Bins " << i + 1 << " to " << j + 1 << " have been merged. Total entries: " << nEntries << std::endl;
          // draw merged histogram
          TString htitle_m = Form("Merged ProjectionY for X bins %d-%d", i + 1, j + 1);
          zz[i]->SetTitle(htitle_m);
          can2->cd(j);
          zz[i]->Draw();
          zz[i]->GetQuantiles(1, &a, &b);
          quantile[j] = a;
          quantile[i] = -1;
          TAxis *xAxis = dd->GetXaxis();
          TAxis *yAxis = dd->GetYaxis();
          ybins[j] = yAxis->GetBinUpEdge(j);
          xbins[i] = -1;
          xbins[j] = xAxis->GetBinUpEdge(j);
          std::cout << "bin" << j << "\t xbin:" << xbins[j] << "\t quantile:" << a << "\t percentage:" << b << std::endl;
          nPlotted++;
          
          i = j;
          break;
        }
        else if (nEntries >= threshold && kalanbin <= 3)
        //else if (kalanbin <= 3)
        {
          if (j == nbinsX - 1)
          {
            std::cout << "Bins " << i + 1 << " to " << j + 1 << " have been merged. Total entries: " << nEntries << std::endl;
            // draw merged histogram
            TString htitle_m = Form("Merged ProjectionY for X bins %d-%d", i + 1, j + 1);
            zz[i]->SetTitle(htitle_m);
            can2->cd(j);
            zz[i]->Draw();
            zz[i]->GetQuantiles(1, &a, &b);
            quantile[j] = a;
            quantile[i] = -1;
            TAxis *xAxis = dd->GetXaxis();
            TAxis *yAxis = dd->GetYaxis();
            ybins[j] = yAxis->GetBinUpEdge(j);
            xbins[i] = -1;
            xbins[j] = xAxis->GetBinUpEdge(j);
            std::cout << "bin" << j << "\t LE:" << xbins[j] << "\t a:" << a << "\t b:" << b << std::endl;
            nPlotted++;
           
            i = j;
            break;
          }
        }
        else if (nEntries < threshold)
        {

          if (j == nbinsX - 1)
          {
            
            int LastUsedBin = previousbin.size();
            int PrevBin= previousbin[LastUsedBin-2];
            std::cout<<"Treshold is low.."<< PrevBin << " -- "<< i <<" -- "<<j <<" --- "<<zz[PrevBin]->GetEntries()<<" -- " << zz[i]->GetEntries() <<std::endl;
            zz[PrevBin]->Add(zz[i]); // eger treshold yetmiorsa bi onceki binin histogramına kat
          double  nEntries2 = zz[PrevBin]->GetEntries();
            std::cout << "BinsLT " << PrevBin +1 << " to " << j + 1 << " have been merged. Total entries: " << nEntries2 << std::endl;
            // draw merged histogram
            TString htitle_m = Form("Merged ProjectionY for X bins %d-%d", PrevBin+1, j + 1);
            zz[PrevBin]->SetTitle(htitle_m);
            can2->cd(j);
            zz[PrevBin]->Draw();
            zz[PrevBin]->GetQuantiles(1, &a, &b);
            quantile[j] = a;
            quantile[PrevBin] = -1;
            TAxis *xAxis = dd->GetXaxis();
            TAxis *yAxis = dd->GetYaxis();
            ybins[j] = yAxis->GetBinUpEdge(j);
            xbins[i] = -1;
            xbins[j] = xAxis->GetBinUpEdge(j);
            std::cout << "bin" << j << "\t LE:" << xbins[j] << "\t a:" << a << "\t b:" << b << std::endl;
            nPlotted++;
     
            i = j;
            break;
          }
        }
      }
    }
  }
  // can2->Update();
  std::cout << "Plotted " << nPlotted << " histograms with more than " << threshold << " entries." << std::endl;
  // First counts the real number of results:
  TCanvas *can3 = new TCanvas("can3", "can3", 800, 600);
  can3->cd();
  int RealBins = 0;
  for (int i = 0; i < nbinsX; i++)
  {
    if (quantile[i] > 0 && xbins[i] > 0.1)
    {
      Real_quantile[RealBins] = quantile[i];
      Real_xbins[RealBins] = xbins[i];
      std::cout << "Xbin: " << xbins[i] << "\t quantile :" << quantile[i] << std::endl;
      RealBins++;
    }
  }

  // TGraph *QuantileRes(RealBins);
  TGraph *gr = new TGraph(RealBins, Real_xbins, Real_quantile);

  // TGraph *gr = new TGraph(nq,xbins, quantile);
  gPad->SetGrid();
  gr->SetLineColor(0);
  gr->SetMarkerColor(kBlue);
  gr->SetMarkerStyle(24);
  //gr->SetTitle("DR_bb{Higgs}_2M1L_signal_region");
  //gr->SetTitle("DR_jjW_2M1L_signal_region");
  gr->SetTitle("Rel_HT_2M1L_signal_region");
  //gr->SetTitle("DR_topW_2M1L_signal_region");
  gr->GetXaxis()->SetTitle("TprimeMass(GeV)");
  gr->GetYaxis()->SetTitle("quantile");
  gr->Draw("ap");


  gStyle->SetOptFit(11111);



//gr->Fit("expo+[c]","SR","",290,1300);
//TF1 *fitFunc = new TF1("fitFunc","expo+[c]",300,1300);
//TF1 *fitFunc4 = new TF1("fitFunc4","pol4",290,1300);
//TF1 *fitFunc5 = new TF1("fitFunc5","pol4",290,1300);
//gr->Fit(fitFunc,"SR");
//gr->Fit(fitFunc4,"R+");
//gr->Fit(fitFunc5,"R+");


//gr->Fit("pol","SR+","",280,1300);
gr->Fit("pol4","SR","",290,1300);
//TF1* fitFunc = gr->GetFunction("pol3"); 
TF1* fitFunc = gr->GetFunction("pol4"); 
//TF1* fitFunc6 = gr->GetFunction("pol6"); 



TVirtualFitter* fitter = TVirtualFitter::GetFitter(); // get the TVirtualFitter object
TH1F* hConfIntervals = new TH1F("hConfIntervals", "Confidence Intervals", fitFunc->GetNpx(), fitFunc->GetXmin(), fitFunc->GetXmax());
fitFunc->SetLineColor(kRed);
fitFunc->SetLineWidth(2);
//fitFunc4->SetLineColor(kBlue);
//fitFunc4->SetLineWidth(2);
//fitFunc5->SetLineColor(kGreen+2);
//fitFunc5->SetLineWidth(2);  
fitter->GetConfidenceIntervals(hConfIntervals); // get the confidence intervals
hConfIntervals->SetFillColorAlpha(kBlue, 0.2);
hConfIntervals->Draw("e6 SAME"); // draw the confidence intervals as a band

  // Create an empty string called "Correction" using the TString class
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

TLegend* legend = new TLegend(0.30, 0.70, 0.60, 0.90); // (x1, y1, x2, y2) in NDC coordinates

// set the legend style
legend->SetBorderSize(1);
legend->SetFillColor(0);
legend->SetTextSize(0.03);

// add an entry to the legend
legend->AddEntry(gr, "[ mergedbins<500 ]", "");
legend->AddEntry(gr, "0.05% quantile ", "p"); // (object, label, option)

legend->AddEntry(fitFunc, "Fit: pol4", "l");
//legend->AddEntry(fitFunc, "Fit: pol3", "l");
//legend->AddEntry(fitFunc, "Fit: expo+[c]", "l");
legend->AddEntry(hConfIntervals, "%95 CL band", "f");
//legend->AddEntry(fitFunc5, "Fit: pol5", "l");
//legend->AddEntry(fitFunc6, "Fit: pol6", "l");
legend->Draw();

/*TFile f("Outputs/MergedBins500/REL_HT_merged_05_pol4.root","RECREATE");
gr->Write();
f.Write();*/
}

/*========*/
