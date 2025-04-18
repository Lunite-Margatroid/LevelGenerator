/*
 * DEFINES THE AROMATICITY MODEL
 *

Training data

 data/aromModel/AP_NSPDK_Model_OpenBabel_2013.smi

Training setup

 ringCentered = true
 maxRingSize = 15
 nspdk bits  = 15
 nspdk dist  = 4
 nspdk rad   = 2
 epochs      = 5

Test via 2-fold cross validation

 overall rings correct  = 55324 / 56019 = 98.7593 %
 aromatic rings correct = 22340 / 22431 = 99.5943 %
 non-aromatic r correct = 32984 / 33588 = 98.2017 %

 whole molecule correct = 16476 / 17014 = 96.8379 %

 *
 */


	aromaticityModel->description = "Linear SGD SVM model based on NSPDK"
			" produced from OpenBabel predictions."
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

	aromaticityModel->bias = -0.636327;
	aromaticityModel->wscale = 0.00355397;

