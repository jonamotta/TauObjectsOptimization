# L1TauObjectsOptimization
Set of tools to evaluate tau trigger performance on T&amp;P

## Foreword
This package is based on the developments done by Olivier Davignon, Luca Cadamuro, and Jean-Baptiste Sauvan.
The original work done by them can be found mainly at these two links: [NTuples production](https://github.com/davignon/TauTagAndProbe/tree/master/TauTagAndProbe), [Objects calibration](https://github.com/jbsauvan/RegressionTraining)

This forlder is an attempt to put together all of the developments done on top of these two folders in one single repositoty and one tool: ONE TOOL TO OPTIMIZE THEM ALL - CIT.

## Install instructions
These instalation instructions work only for CMSSW_11_0_2. To use the updated CMSSW_12_0_2 version for the TauTagAndProbe package and the production of the NTuples refer to [these instructions](https://github.com/jonamotta/TauTagAndProbe/tree/CMSSW_12_0_2-l1t-integration-v110.0). On the other hand, still use the following instructions to do the optimization of the objects (even if NTuples are produced with CMSSW_12_0_2).


```bash
cmsrel CMSSW_11_0_2
cd CMSSW_11_0_2/src
cmsenv
git cms-init
git remote add cms-l1t-offline git@github.com:cms-l1t-offline/cmssw.git
git fetch cms-l1t-offline l1t-integration-CMSSW_11_0_2
git cms-merge-topic -u cms-l1t-offline:l1t-integration-v104.5
git cms-addpkg L1Trigger/L1TCommon
git cms-addpkg L1Trigger/L1TMuon
git clone https://github.com/cms-l1t-offline/L1Trigger-L1TMuon.git L1Trigger/L1TMuon/data
git cms-addpkg L1Trigger/L1TCalorimeter
git clone https://github.com/cms-l1t-offline/L1Trigger-L1TCalorimeter.git L1Trigger/L1TCalorimeter/data

mkdir HiggsAnalysis
cd HiggsAnalysis
git clone git@github.com:bendavid/GBRLikelihood.git
# modify the first line of `HiggsAnalysis/GBRLikelihood/BuildFile.xml` to have `-std=c++17`

cd ..
git clone https://github.com/davignon/TauTagAndProbe # package for the production of the starting NTuples

git cms-checkdeps -A -a

scram b -j 10

git clone https://github.com/jonamotta/TauObjectsOptimization # package for the full optimization
```

L1T emulation relevant GlobalTags in `CMSSW_11_0_2` are:
* for run2 data reprocessing `110X_dataRun2_v12`
* for run2 mc `110X_mcRun2_asymptotic_v6`
* for run3 mc `110X_mcRun3_2021_realistic_v6(9)`

## Tool utilization
To do the optimization two things are needed:
* L1 objects (sometimes re-emulated) that are extracted from the RAW tier (in principle, non-re-emulated L1 objects can also be extracted from MiniAOD, but for consistency we never do that)
* Offline objects that are extracted from the AOD or MiniAOD tier

The optimization is run in several sequential steps:
* Production of the L1 objects (from RAW) and offline objects (from MiniAOD)
* Merge of the two inputs, match of the L1 objects to the offline ones, compression of the variables
* Calculation of the calibration, pruduction of its LUTs, and its application
* Calculation of the isolation, pruduction of its LUTs, and its application
* Prodution of turnon curves
* Evaluation of the L1 rate

### Production of the input objects
To produce the input NTuples to the optimization the `TauTagAndProbe` package is used. The useful scripts for this are mainly in the `test` subfolder.

Jobs on RAW are submitted using `submitOnTier3_reEmulL1_zeroBias.py` which in turn launches `reEmulL1_X.py`
Before launching this you need to fix
* the Global Tag
* the configuration of the L1Calorimeter (`process.load("L1Trigger.L1TCalorimeter.caloStage2Params_20XX_vX_X_XXX_cfi")`)


Jobs on MiniAOD are submitted using `submitOnTier3.py` which in turn launches `test_noTagAndProbe.py`
Before launching this you need to fix
* the Global Tag

For Monte Carlo (MC), we implemented a truth matching rather than a Tag & Probe technique which would dramatically and artificially decrease the available statistics.

After having produced the input object `hadd` all the files.


Jobs on ZeroBias are submitted using `submitOnTier3_reEmulL1_zeroBias.py` which in turn launches `reEmulL1_ZeroBias.py`
Before launching this you need to fix
* the `isMC` flag
* the input folder and file list
The datasets that have to be used are among the ones listed here: https://twiki.cern.ch/twiki/bin/viewauth/CMS/TriggerStudiesChangesInDataTaking2018

After having produced the input object `hadd` all the files.

### Merging, matching, and compression
Enter `MergeTrees` and run `make clean ; make`.

To merge the files first create/modify the needed `.config` file inside the `MergeTrees/run` directory. There the `MINIAOD` file has to be specified as primary and the `RAW` one as secondary (always use absolute paths). Check that the files really contain the TTrees that the executable will look for. 
Then jus run:
```bash
./merge.exe run/<whatevername>.config 
```

After that we need to match the reco taus to the L1 taus. To do so edit the `MakeTreeForCalibration.C` file (inside the `MatchAndCompress` folder) with the correct in and out files, then just run:
```bash
root -l
.L MakeTreeForCalibration.C+
MakeTreeForCalibration()
```

After the matching the compression needs to be performed. To do so edit the `produceTreeWithCompressedIetaEShape_NewFormat.py` file (inside the `MatchAndCompress` folder) with the correct in and out files, then just run:
```bash
python produceTreeWithCompressedIetaEShape_NewFormat.py
```

### Calibration
Enter `Calibrate/RegressionTraining` and run `make clean ; make`.

To do the calibration first create/modify the needed `.config` file inside the `Calibrate/RegressionTraining/run` directory, then just run:
```bash
./regression.exe run/<whatevername>.config
```

Now that the regression has been trained, adapt to your needs the `makeTH4_<whateverag>.py` file  and run:
```bash
python makeTH4_<whateverag>.py
```

Now that the TH4 histos have been created, adapt to your needs the `MakeTauCalibLUT_<whatevertag>.C` file and run:
```bash
root -l
.L MakeTauCalibLUT_<whatevertag>.C+
MakeTauCalibLUT() # insert needed arguments
```

Now that the LUTs have been created, we can apply the calibration to teh L1 objects. Adapt to your needs `ApplyCalibration_newnTT.C`
```bash
root -l
.L ApplyCalibration_newnTT.C+
ApplyCalibration() # insert needed arguments
```

### Isolation
Now that the calibration has been done the isolation needs to be compute and applyed.
To do so go to the `Isolate` folder.

To compute the isolation, adapt to your needs the `Build_Isolation_WPs_MC_newnTT.C` file and run:
```bash
root -l
.L Build_Isolation_WPs_MC_newnTT.C+
Build_Isolation_WPs() # insert needed arguments
```

Then the relaxation of the isolation needs to be performed. To do so, adapt to your needs `Fill_Isolation_TH3_MC_newnTT.C` and run:
```bash
root -l
.L Fill_Isolation_TH3_MC_newnTT.C+
Fill_Isolation_TH3() # insert needed arguments
```
or
```bash
root -l
.L Fill_Isolation_TH3_MC_newnTT_gridSearch.C+
Fill_Isolation_TH3() # insert needed arguments
```
to start a a grid search over the possible relaxation schemes that give rise to different turnON shapes.

### Calibration of ZeroBias
Enter `Calibrate/`, adapt to your needs `ApplyCalibrationZeroBias_nTT.C` and run:
```bash
root -l
.L ApplyCalibrationZeroBias_nTT.C+
ApplyCalibrationZeroBias() # insert needed arguments
```

### Rates
To produce rates go to the `MakeRates` folder, adapt to your needs `Rate_ZeroBias_Run323755_unpacked.C` and `Rate_ZeroBias_Run323755_newnTT.C` and run:
```bash
root -l
.L Rate_ZeroBias_unpacked.C+
Rate() # insert needed arguments
```
and 
```bash
root -l
.L Rate_ZeroBias_newnTT.C+
Rate() # insert needed arguments
```
or 
```bash
root -l
.L Rate_ZeroBias_newnTT_gridSearch.C+
Rate() # insert needed arguments
```
if you are doing the grid search over the possible relaxation parametrizations.

Having computed the rates, they can be plotted going to the `PlotRates` folder, adapting to your needs `CompareRates_newnTT_withunpacked.C`, and running:
```bash
root -l 
.L CompareRates_newnTT_withunpacked.C
compare() # insert needed arguments
```
or
```bash
root -l 
.L CompareRates_gridSearch_newnTT_withunpacked.C
compare() # insert needed arguments
```
if you are doing the grid search over the possible relaxation parametrizations.

In case you want to evaluate the rate you would get from a specific relaxation skim at a fixed threshold you can use:
```bash
root -l
.L BestRatesAtFixedThr_gridSearch.C+
compare() # insert needed arguments
```
this will print out `.txt` files with the value of the rate for the differnt optons. (This must be done after the rates have been computed in the usual manner as explained above)

### TurnONs
Now that also the isolation has been created we can test everything on the turn-on curves. 
To do so go to the `MakeTurnOns` folder, adapt to to your needs `ApplyIsolationForTurnOns_newnTT.C` and run:
```bash
root -l
.L ApplyIsolationForTurnOns_newnTT.C+
ApplyIsolationForTurnOns() # insert needed arguments
```
or 
```bash
root -l
.L ApplyIsolationForTurnOns_newnTT_gridSearch.C+
ApplyIsolationForTurnOns() # insert needed arguments
```
if you are doing the grid search over the possible relaxation parametrizations.

Having computed the turnONs, they can be plotted going to the `PlotTurnOns` folder, adapting to your needs `CompareTunrOns_withunpacked.C`, and running:
```bash
root -l
.L CompareTunrOns_withunpacked.C
compare() # insert needed arguments
```
or
```bash
root -l
.L CompareTunrOns_gridSearch_withunpacked.C
compare() # insert needed arguments
```
if you are doing the grid search over the possible relaxation parametrizations.

The plots produced above will be a bit crouded and difficult to read. FO this reason a second plotting folder is used where only selected turnons will be plotted.
Move to `PlotGoodGridSearch/` and run one of the followings after having adapted the scripts to your needs:
```bash
root -l
.L GoodTurnOns_gridSearch.C
compare() # insert needed arguments
```
or
```bash
root -l
.L BestFMturnOns_gridSearch.C
compare() # insert needed arguments
```
or
```bash
root -l
.L FinalComparison_gridSearch.C
compare() # insert needed arguments
```
These three scripts all allow to plot what we define as "good turnons" depending on different comparison options (i.e. a turn on can be defined as good if it has a certain acceptance, a certain efficiency at a certain pT, or any other possible definition)
