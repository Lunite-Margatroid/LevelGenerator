/*
 * DEFINES THE AROMATICITY MODEL
 *

Training data

 data/aromModel/AP_NSPDK_Model_Marvin_general_2013.smi

Training setup

 ringCentered = true
 maxRingSize = 15
 nspdk bits  = 15
 nspdk dist  = 4
 nspdk rad   = 2
 epochs      = 5

Test via 2-fold cross validation

 overall rings correct  = 54626 / 55583 = 98.2782 %
 aromatic rings correct = 21673 / 21864 = 99.1264 %
 non-aromatic r correct = 32953 / 33719 = 97.7283 %

 whole molecule correct = 16301 / 17014 = 95.8093 %

 *
 */


	aromaticityModel->description = "Linear SGD SVM model based on NSPDK"
			" produced from Marvin predictions for the 'general' method."
			" Training used 5 epochs and lambda 1e-4."
			;

	aromaticityModel->ringCentered = true;
	aromaticityModel->nspdk_maxRingDistance = 0;
	aromaticityModel->nspdk_maxDistance = 4;
	aromaticityModel->nspdk_maxRadius = 2;
	aromaticityModel->nspdk_featureBitSize = 15;
	aromaticityModel->maxRingSize = 15;

	aromaticityModel->ringNodeLabelPrefix = "*";
	aromaticityModel->ringEdgeLabel = "*~";
	aromaticityModel->ringViewLabelPrefix = "?";

	aromaticityModel->bias =  -0.539998;
	aromaticityModel->wscale = 0.00358175;

