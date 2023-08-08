# GetQuantile_VLQ
New validation with the GetQuantile method for VLQ top+H all hadronic analysis

### Quantiles_*.C: 
  Derive quantile values for each bin interval (for each cut variable (FullRange)): DR_bbH/DR_jjW/Relative_HT/DR_Topw: from binX to binX+1  

These will give you a complete picture of the Y-axis distribution for each bin in the X-axis, and you can calculate quantiles for each of these 1D histograms using the TH1F::GetQuantiles method.


### Mergebins100.C: 

  After Deriving the quantile values for each bin interval: from binX to binX+1 
encountered fluctuation in the high-mass region due to low statistics - so we used the merged bins method:
- Merged bins after giving a threshold (>500 entries) for each bin.


### exam.C:
  final results comparisons: 
Before and After the quantile method

### norm.C:

  After quantile method, derive all TPrimemass plots : TprimeMass1-13 (with quantiles: TprimeMass7 - TprimeMass9 - TprimeMass11 - TprimeMass13 )

### Presentations:
1- https://indico.cern.ch/event/1272626/contributions/5345701/attachments/2624769/4538923/Status_Update_QuantileMethod_04042023.pdf

2- https://cernbox.cern.ch/pdf-viewer/eos/user/c/cdozen/quantile_pdfs/Presentations/Quantiles_method_Signal-Region.pdf?contextRouteName=files-spaces-generic&contextRouteParams.driveAliasAndItem=eos/user/c/cdozen/quantile_pdfs/Presentations



