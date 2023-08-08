# GetQuantile_VLQ
New validation with getquantile method for VLQ top+H all hadronic analysis

Quantiles_*.C : Derive quantile values for each bin interval (for each cut variables (FullRange)): DR_bbH/DR_jjW/Relative_HT/DR_Topw: from binX to binX+1  

These will give you a complete picture of the Y-axis distribution for each bin in the X-axis, and you can calculate quantiles for each of these 1D histograms using the TH1F::GetQuantiles method.


Mergebins100.C: 

After Deriving the quantile values for each bin interval : from binX to binX+1 
encountered fluctuation in the high-mass region due to low statistic - so we used mergedbins method:
- Merged bins after giving a threshold (>500 entries) for each bin. 



exam.C:
final results comparisions : 
Before and After quantile method



norm.C:

After quantile method, derive all TPrimemass plots : TprimeMass1-13 (with quantiles: TprimeMass7 - TprimeMass9 - TprimeMass11 - TprimeMass13 )