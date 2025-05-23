
/****************************************************************************
 * Data taken from
 ****************************************************************************
 *
 * Group Contribution Method for Thermodynamic Analysis of Complex Metabolic Networks
 * Matthew D. Jankowski, Christopher S. Henry, Linda J. Broadbelt, and Vassily Hatzimanikatis
 * Biophysical Journal, Volume 95, August 2008, 1487�1499
 * doi: 10.1529/biophysj.107.124784
 *
 ****************************************************************************/

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"CH4 (CH4)\""
" priority 1"
" energy -8.2051"
" node [ id 1 label \"C\" ]"
" node [ id 2 label \"H\" ]"
" node [ id 3 label \"H\" ]"
" node [ id 4 label \"H\" ]"
" node [ id 5 label \"H\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"-\" ]"
" edge [ source 1 target 4 label \"-\" ]"
" edge [ source 1 target 5 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 id 5 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"CO2 (C1O2)\""
" priority 1"
" energy -92.26"
" node [ id 1 label \"C\" ]"
" node [ id 2 label \"O\" ]"
" node [ id 3 label \"O\" ]"
" edge [ source 1 target 2 label \"=\" ]"
" edge [ source 1 target 3 label \"=\" ]"
" compIDs [ id 1 id 2 id 3 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"ClO2 (ClO2)\""
" priority 1"
" energy 4.1"
" node [ id 1 label \"Cl\" ]"
" node [ id 2 label \"O\" ]"
" node [ id 3 label \"O\" ]"
" node [ id 4 label \"H\" ]"
" edge [ source 1 target 2 label \"=\" ]"
" edge [ source 1 target 3 label \"-\" ]"
" edge [ source 3 target 4 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"ClO3 (ClO3)\""
" priority 1"
" energy -0.8"
" node [ id 1 label \"Cl\" ]"
" node [ id 2 label \"O\" ]"
" node [ id 3 label \"O\" ]"
" node [ id 4 label \"O\" ]"
" node [ id 5 label \"H\" ]"
" edge [ source 1 target 2 label \"=\" ]"
" edge [ source 1 target 3 label \"=\" ]"
" edge [ source 1 target 4 label \"-\" ]"
" edge [ source 4 target 5 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 id 5 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

//"molcomp ["
//"description \"FeS (Fe1S1)\""
//"priority 1"
//"energy -10000"
//"node [ id 1 label \"S\" ]"
//"node [ id 2 label \"Fe\" ]"
//"node [ id 3 label \"H\" ]"
//"node [ id 4 label \"H\" ]"
//"node [ id 5 label \"H\" ]"
//"node [ id 6 label \"H\" ]"
//"edge [ source 1 target 2 label \"-\" ]"
//"edge [ source 1 target 3 label \"-\" ]"
//"edge [ source 2 target 4 label \"-\" ]"
//"edge [ source 2 target 5 label \"-\" ]"
//"edge [ source 2 target 6 label \"-\" ]"
//"compIDs [ id 1 id 2 id 3 id 4 id 5 id 6 ]"
//"]"
//,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"H2 (H2)\""
" priority 1"
" energy 4.2065"
" node [ id 1 label \"H\" ]"
" node [ id 2 label \"H\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" compIDs [ id 1 id 2 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"H2O OH- HO- (H2O)\""
" priority 1"
" energy -56.687"
" node [ id 1 label \"O\" ]"
" node [ id 2 label \"H\" ]"
" node [ id 3 label \"H\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"H2O2 (H2O2)\""
" priority 1"
" energy -32.05"
" node [ id 1 label \"O\" ]"
" node [ id 2 label \"O\" ]"
" node [ id 3 label \"H\" ]"
" node [ id 4 label \"H\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"-\" ]"
" edge [ source 2 target 4 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"H2S HS- (H2S1)\""
" priority 1"
" energy -6.66"
" node [ id 1 label \"S\" ]"
" node [ id 2 label \"H\" ]"
" node [ id 3 label \"H\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

//"molcomp ["
//"description \"H2Se (Se1H2)\""
//"priority 1"
//"energy -10000"
//"node [ id 1 label \"Se\" ]"
//"node [ id 2 label \"H\" ]"
//"node [ id 3 label \"H\" ]"
//"edge [ source 1 target 2 label \"-\" ]"
//"edge [ source 1 target 3 label \"-\" ]"
//"compIDs [ id 1 id 2 id 3 ]"
//"]"
//,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"HCO3 (C1H1O3)\""
" priority 1"
" energy -140.26"
" node [ id 1 label \"C\" ]"
" node [ id 2 label \"O\" ]"
" node [ id 3 label \"O\" ]"
" node [ id 4 label \"O\" ]"
" node [ id 5 label \"H\" ]"
" node [ id 6 label \"H\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"-\" ]"
" edge [ source 1 target 4 label \"=\" ]"
" edge [ source 2 target 5 label \"-\" ]"
" edge [ source 3 target 6 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 id 5 id 6 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"HNO (HNO)\""
" priority 1"
" energy 11.8205"
" node [ id 1 label \"N\" ]"
" node [ id 2 label \"O\" ]"
" node [ id 3 label \"H\" ]"
" edge [ source 1 target 2 label \"=\" ]"
" edge [ source 1 target 3 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

//"molcomp ["
//"description \"Itriphos (H1O10P3)\""
//"priority 1"
//"energy -10000"
//"node [ id 1 label \"O\" ]"
//"node [ id 2 label \"P\" ]"
//"node [ id 3 label \"P\" ]"
//"node [ id 4 label \"O\" ]"
//"node [ id 5 label \"O\" ]"
//"node [ id 6 label \"O\" ]"
//"node [ id 7 label \"O\" ]"
//"node [ id 8 label \"O\" ]"
//"node [ id 9 label \"O\" ]"
//"node [ id 10 label \"P\" ]"
//"node [ id 11 label \"O\" ]"
//"node [ id 12 label \"O\" ]"
//"node [ id 13 label \"O\" ]"
//"node [ id 14 label \"H\" ]"
//"node [ id 15 label \"H\" ]"
//"node [ id 16 label \"H\" ]"
//"node [ id 17 label \"H\" ]"
//"node [ id 18 label \"H\" ]"
//"edge [ source 1 target 2 label \"-\" ]"
//"edge [ source 1 target 3 label \"-\" ]"
//"edge [ source 2 target 4 label \"-\" ]"
//"edge [ source 2 target 5 label \"-\" ]"
//"edge [ source 2 target 6 label \"=\" ]"
//"edge [ source 3 target 7 label \"-\" ]"
//"edge [ source 3 target 8 label \"-\" ]"
//"edge [ source 3 target 9 label \"=\" ]"
//"edge [ source 4 target 10 label \"-\" ]"
//"edge [ source 5 target 16 label \"-\" ]"
//"edge [ source 7 target 14 label \"-\" ]"
//"edge [ source 8 target 17 label \"-\" ]"
//"edge [ source 10 target 11 label \"-\" ]"
//"edge [ source 10 target 12 label \"-\" ]"
//"edge [ source 10 target 13 label \"=\" ]"
//"edge [ source 11 target 18 label \"-\" ]"
//"edge [ source 12 target 15 label \"-\" ]"
//"compIDs [ id 1 id 2 id 3 id 4 id 5 id 6 id 7 id 8 id 9 id 10 id 11 id 12 id 13 id 14 id 15 id 16 id 17 id 18 ]"
//"]"
//,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"MeOH (C1H4O1)\""
" priority 1"
" energy -41.9"
" node [ id 1 label \"O\" ]"
" node [ id 2 label \"H\" ]"
" node [ id 3 label \"C\" ]"
" node [ id 4 label \"H\" ]"
" node [ id 5 label \"H\" ]"
" node [ id 6 label \"H\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"-\" ]"
" edge [ source 3 target 4 label \"-\" ]"
" edge [ source 3 target 5 label \"-\" ]"
" edge [ source 3 target 6 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 id 5 id 6 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"N2H4 (N2H4)\""
" priority 1"
" energy 30.6"
" node [ id 1 label \"N\" ]"
" node [ id 2 label \"H\" ]"
" node [ id 3 label \"H\" ]"
" node [ id 4 label \"H\" ]"
" node [ id 5 label \"H\" ]"
" node [ id 6 label \"N\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"-\" ]"
" edge [ source 1 target 6 label \"-\" ]"
" edge [ source 4 target 6 label \"-\" ]"
" edge [ source 5 target 6 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 id 5 id 6 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"NH4plus = ammonia(aq) (N1H4)\""
" priority 1"
" energy -18.97"
" node [ id 1 label \"N+1\" ]"
" node [ id 2 label \"H\" ]"
" node [ id 3 label \"H\" ]"
" node [ id 4 label \"H\" ]"
" node [ id 5 label \"H\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"-\" ]"
" edge [ source 1 target 4 label \"-\" ]"
" edge [ source 1 target 5 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 id 5 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"ammonia (N1H3)\""
" priority 1"
" energy -18.97"
" node [ id 1 label \"N\" ]"
" node [ id 2 label \"H\" ]"
" node [ id 3 label \"H\" ]"
" node [ id 4 label \"H\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"-\" ]"
" edge [ source 1 target 4 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"NitrousOx (O2N1)\""
" priority 1"
" energy 18.2552"
" node [ id 1 label \"N\" ]"
" node [ id 2 label \"N\" ]"
" node [ id 3 label \"O\" ]"
" node [ id 4 label \"H\" ]"
" edge [ source 1 target 2 label \"=\" ]"
" edge [ source 1 target 3 label \"=\" ]"
" edge [ source 2 target 4 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"O2 (O2)\""
" priority 1"
" energy 3.9197"
" node [ id 1 label \"O\" ]"
" node [ id 2 label \"O\" ]"
" edge [ source 1 target 2 label \"=\" ]"
" compIDs [ id 1 id 2 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

//"molcomp ["
//"description \"PO3 (O3P)\""
//"priority 1"
//"energy -10000"
//"node [ id 1 label \"P\" ]"
//"node [ id 2 label \"O\" ]"
//"node [ id 3 label \"O\" ]"
//"node [ id 4 label \"O\" ]"
//"node [ id 5 label \"H\" ]"
//"node [ id 6 label \"H\" ]"
//"node [ id 7 label \"H\" ]"
//"edge [ source 1 target 2 label \"-\" ]"
//"edge [ source 1 target 3 label \"-\" ]"
//"edge [ source 1 target 4 label \"=\" ]"
//"edge [ source 1 target 5 label \"-\" ]"
//"edge [ source 2 target 7 label \"-\" ]"
//"edge [ source 3 target 6 label \"-\" ]"
//"compIDs [ id 1 id 2 id 3 id 4 id 5 id 6 id 7 ]"
//"]"
//,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"S2O3H (O3S2)\""
" priority 1"
" energy -122.7"
" node [ id 1 label \"S\" ]"
" node [ id 2 label \"O\" ]"
" node [ id 3 label \"O\" ]"
" node [ id 4 label \"O\" ]"
" node [ id 5 label \"H\" ]"
" node [ id 6 label \"S\" ]"
" node [ id 7 label \"H\" ]"
" edge [ source 1 target 2 label \"=\" ]"
" edge [ source 1 target 3 label \"=\" ]"
" edge [ source 1 target 4 label \"-\" ]"
" edge [ source 1 target 6 label \"-\" ]"
" edge [ source 4 target 5 label \"-\" ]"
" edge [ source 6 target 7 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 id 5 id 6 id 7 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"S2O4 (S2O4)\""
" priority 1"
" energy -143.5"
" node [ id 1 label \"S\" ]"
" node [ id 2 label \"O\" ]"
" node [ id 3 label \"O\" ]"
" node [ id 4 label \"O\" ]"
" node [ id 5 label \"O\" ]"
" node [ id 6 label \"S\" ]"
" node [ id 7 label \"H\" ]"
" node [ id 8 label \"H\" ]"
" edge [ source 1 target 2 label \"=\" ]"
" edge [ source 1 target 3 label \"-\" ]"
" edge [ source 1 target 6 label \"-\" ]"
" edge [ source 3 target 7 label \"-\" ]"
" edge [ source 4 target 6 label \"-\" ]"
" edge [ source 4 target 8 label \"-\" ]"
" edge [ source 5 target 6 label \"=\" ]"
" compIDs [ id 1 id 2 id 3 id 4 id 5 id 6 id 7 id 8 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"SO2 (SO2)\""
" priority 1"
" energy -71.9"
" node [ id 1 label \"S\" ]"
" node [ id 2 label \"O\" ]"
" node [ id 3 label \"O\" ]"
" edge [ source 1 target 2 label \"=\" ]"
" edge [ source 1 target 3 label \"=\" ]"
" compIDs [ id 1 id 2 id 3 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"acetaldehyde (C2H4O)\""
" priority 1"
" energy -33.4"
" node [ id 1 label \"C\" ]"
" node [ id 2 label \"C\" ]"
" node [ id 3 label \"O\" ]"
" node [ id 4 label \"H\" ]"
" node [ id 5 label \"H\" ]"
" node [ id 6 label \"H\" ]"
" node [ id 7 label \"H\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"=\" ]"
" edge [ source 1 target 4 label \"-\" ]"
" edge [ source 2 target 5 label \"-\" ]"
" edge [ source 2 target 6 label \"-\" ]"
" edge [ source 2 target 7 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 id 5 id 6 id 7 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"acetate (C2H3O2)\""
" priority 1"
" energy -88.29"
" node [ id 1 label \"C\" ]"
" node [ id 2 label \"C\" ]"
" node [ id 3 label \"O\" ]"
" node [ id 4 label \"O\" ]"
" node [ id 5 label \"H\" ]"
" node [ id 6 label \"H\" ]"
" node [ id 7 label \"H\" ]"
" node [ id 8 label \"H\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"-\" ]"
" edge [ source 1 target 4 label \"=\" ]"
" edge [ source 2 target 5 label \"-\" ]"
" edge [ source 2 target 6 label \"-\" ]"
" edge [ source 2 target 7 label \"-\" ]"
" edge [ source 3 target 8 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 id 5 id 6 id 7 id 8 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"acetone (C3O1H6)\""
" priority 1"
" energy -38.52"
" node [ id 1 label \"C\" ]"
" node [ id 2 label \"C\" ]"
" node [ id 3 label \"C\" ]"
" node [ id 4 label \"O\" ]"
" node [ id 5 label \"H\" ]"
" node [ id 6 label \"H\" ]"
" node [ id 7 label \"H\" ]"
" node [ id 8 label \"H\" ]"
" node [ id 9 label \"H\" ]"
" node [ id 10 label \"H\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"-\" ]"
" edge [ source 1 target 4 label \"=\" ]"
" edge [ source 2 target 5 label \"-\" ]"
" edge [ source 2 target 6 label \"-\" ]"
" edge [ source 2 target 7 label \"-\" ]"
" edge [ source 3 target 8 label \"-\" ]"
" edge [ source 3 target 9 label \"-\" ]"
" edge [ source 3 target 10 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 id 5 id 6 id 7 id 8 id 9 id 10 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"carbamate (C1H2N1O2)\""
" priority 1"
" energy -95.7"
" node [ id 1 label \"C\" ]"
" node [ id 2 label \"N\" ]"
" node [ id 3 label \"O\" ]"
" node [ id 4 label \"O\" ]"
" node [ id 5 label \"H\" ]"
" node [ id 6 label \"H\" ]"
" node [ id 7 label \"H\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"-\" ]"
" edge [ source 1 target 4 label \"=\" ]"
" edge [ source 2 target 5 label \"-\" ]"
" edge [ source 2 target 6 label \"-\" ]"
" edge [ source 3 target 7 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 id 5 id 6 id 7 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"chloromethane (CH3Cl)\""
" priority 1"
" energy -12.6"
" node [ id 1 label \"C\" ]"
" node [ id 2 label \"Cl\" ]"
" node [ id 3 label \"H\" ]"
" node [ id 4 label \"H\" ]"
" node [ id 5 label \"H\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"-\" ]"
" edge [ source 1 target 4 label \"-\" ]"
" edge [ source 1 target 5 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 id 5 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"cmonox	CO (CO)\""
" priority 1"
" energy -28.6568"
" node [ id 1 label \"O\" ]"
" node [ id 2 label \"C\" ]"
" edge [ source 1 target 2 label \"#\" ]"
" compIDs [ id 1 id 2 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

//"molcomp ["
//"description \"cyanicacid (C1N1O1)\""
//"priority 1"
//"energy -10000"
//"node [ id 1 label \"C\" ]"
//"node [ id 2 label \"N\" ]"
//"node [ id 3 label \"O\" ]"
//"node [ id 4 label \"H\" ]"
//"edge [ source 1 target 2 label \"#\" ]"
//"edge [ source 1 target 3 label \"-\" ]"
//"edge [ source 3 target 4 label \"-\" ]"
//"compIDs [ id 1 id 2 id 3 id 4 ]"
//"]"
//,

///////////////////////////////////////////////////////////////////////////////

//"molcomp ["
//"description \"cyanide CN- (HCN)\""
//"priority 1"
//"energy -10000"
//"node [ id 1 label \"N\" ]"
//"node [ id 2 label \"C\" ]"
//"node [ id 3 label \"H\" ]"
//"edge [ source 1 target 2 label \"#\" ]"
//"edge [ source 2 target 3 label \"-\" ]"
//"compIDs [ id 1 id 2 id 3 ]"
//"]"
//,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"dichloromethane (CH2Cl2)\""
" priority 1"
" energy -15.8"
" node [ id 1 label \"C\" ]"
" node [ id 2 label \"Cl\" ]"
" node [ id 3 label \"Cl\" ]"
" node [ id 4 label \"H\" ]"
" node [ id 5 label \"H\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"-\" ]"
" edge [ source 1 target 4 label \"-\" ]"
" edge [ source 1 target 5 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 id 5 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"ethane (C2H6)\""
" priority 1"
" energy -4.065"
" node [ id 1 label \"C\" ]"
" node [ id 2 label \"C\" ]"
" node [ id 3 label \"H\" ]"
" node [ id 4 label \"H\" ]"
" node [ id 5 label \"H\" ]"
" node [ id 6 label \"H\" ]"
" node [ id 7 label \"H\" ]"
" node [ id 8 label \"H\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"-\" ]"
" edge [ source 1 target 4 label \"-\" ]"
" edge [ source 1 target 5 label \"-\" ]"
" edge [ source 2 target 6 label \"-\" ]"
" edge [ source 2 target 7 label \"-\" ]"
" edge [ source 2 target 8 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 id 5 id 6 id 7 id 8 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"ethanol (C2H6O1)\""
" priority 1"
" energy -43.44"
" node [ id 1 label \"C\" ]"
" node [ id 2 label \"C\" ]"
" node [ id 3 label \"O\" ]"
" node [ id 4 label \"H\" ]"
" node [ id 5 label \"H\" ]"
" node [ id 6 label \"H\" ]"
" node [ id 7 label \"H\" ]"
" node [ id 8 label \"H\" ]"
" node [ id 9 label \"H\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"-\" ]"
" edge [ source 1 target 4 label \"-\" ]"
" edge [ source 1 target 5 label \"-\" ]"
" edge [ source 2 target 6 label \"-\" ]"
" edge [ source 2 target 7 label \"-\" ]"
" edge [ source 2 target 8 label \"-\" ]"
" edge [ source 3 target 9 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 id 5 id 6 id 7 id 8 id 9 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

//"molcomp ["
//"description \"ferricy (Fe1C1N1)\""
//"priority 1"
//"energy -10000"
//"node [ id 1 label \"Fe\" ]"
//"node [ id 2 label \"C\" ]"
//"node [ id 3 label \"C\" ]"
//"node [ id 4 label \"C\" ]"
//"node [ id 5 label \"N\" ]"
//"node [ id 6 label \"N\" ]"
//"node [ id 7 label \"N\" ]"
//"node [ id 8 label \"H\" ]"
//"edge [ source 1 target 2 label \"-\" ]"
//"edge [ source 1 target 3 label \"-\" ]"
//"edge [ source 1 target 4 label \"-\" ]"
//"edge [ source 1 target 8 label \"-\" ]"
//"edge [ source 2 target 5 label \"#\" ]"
//"edge [ source 3 target 6 label \"#\" ]"
//"edge [ source 4 target 7 label \"#\" ]"
//"compIDs [ id 1 id 2 id 3 id 4 id 5 id 6 id 7 id 8 ]"
//"]"
//,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"formaldehyde (C1H2O1)\""
" priority 1"
" energy -31.2"
" node [ id 1 label \"C\" ]"
" node [ id 2 label \"H\" ]"
" node [ id 3 label \"O\" ]"
" node [ id 4 label \"H\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"=\" ]"
" edge [ source 1 target 4 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"formate (C1H1O2)\""
" priority 1"
" energy -83.9"
" node [ id 1 label \"C\" ]"
" node [ id 2 label \"H\" ]"
" node [ id 3 label \"O\" ]"
" node [ id 4 label \"O\" ]"
" node [ id 5 label \"H\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"=\" ]"
" edge [ source 1 target 4 label \"-\" ]"
" edge [ source 4 target 5 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 id 5 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"formate (C1H1O2) ion form\""
" priority 1"
" energy -83.9"
" node [ id 1 label \"C\" ]"
" node [ id 2 label \"H\" ]"
" node [ id 3 label \"O\" ]"
" node [ id 4 label \"O-1\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"=\" ]"
" edge [ source 1 target 4 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"formylphosphate (CH2O5P)\""
" priority 1"
" energy -302.5648"
" node [ id 1 label \"P\" ]"
" node [ id 2 label \"O\" ]"
" node [ id 3 label \"O\" ]"
" node [ id 4 label \"O\" ]"
" node [ id 5 label \"O\" ]"
" node [ id 6 label \"C\" ]"
" node [ id 7 label \"H\" ]"
" node [ id 8 label \"O\" ]"
" node [ id 9 label \"H\" ]"
" node [ id 10 label \"H\" ]"
" edge [ source 1 target 2 label \"=\" ]"
" edge [ source 1 target 3 label \"-\" ]"
" edge [ source 1 target 4 label \"-\" ]"
" edge [ source 1 target 5 label \"-\" ]"
" edge [ source 3 target 10 label \"-\" ]"
" edge [ source 4 target 7 label \"-\" ]"
" edge [ source 5 target 6 label \"-\" ]"
" edge [ source 6 target 8 label \"=\" ]"
" edge [ source 6 target 9 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 id 5 id 6 id 7 id 8 id 9 id 10 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"hydroxylamine (H1O1N1H2)\""
" priority 1"
" energy -38.8954"
" node [ id 1 label \"N\" ]"
" node [ id 2 label \"O\" ]"
" node [ id 3 label \"H\" ]"
" node [ id 4 label \"H\" ]"
" node [ id 5 label \"H\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"-\" ]"
" edge [ source 1 target 4 label \"-\" ]"
" edge [ source 2 target 5 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 id 5 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"methylamine (CNH2)\""
" priority 1"
" energy -9.55"
" node [ id 1 label \"C\" ]"
" node [ id 2 label \"N\" ]"
" node [ id 3 label \"H\" ]"
" node [ id 4 label \"H\" ]"
" node [ id 5 label \"H\" ]"
" node [ id 6 label \"H\" ]"
" node [ id 7 label \"H\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"-\" ]"
" edge [ source 1 target 4 label \"-\" ]"
" edge [ source 1 target 5 label \"-\" ]"
" edge [ source 2 target 6 label \"-\" ]"
" edge [ source 2 target 7 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 id 5 id 6 id 7 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"nitricacid (HNO3)\""
" priority 1"
" energy -26.61"
" node [ id 1 label \"N\" ]"
" node [ id 2 label \"O\" ]"
" node [ id 3 label \"O\" ]"
" node [ id 4 label \"O\" ]"
" node [ id 5 label \"H\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"=\" ]"
" edge [ source 1 target 4 label \"=\" ]"
" edge [ source 2 target 5 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 id 5 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"nitrite (NO2)\""
" priority 1"
" energy -8.9"
" node [ id 1 label \"N\" ]"
" node [ id 2 label \"O\" ]"
" node [ id 3 label \"O\" ]"
" node [ id 4 label \"H\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"=\" ]"
" edge [ source 2 target 4 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"orthophosphate (H1O4P1)\""
" priority 1"
" energy -261.974"
" node [ id 1 label \"P\" ]"
" node [ id 2 label \"O\" ]"
" node [ id 3 label \"O\" ]"
" node [ id 4 label \"O\" ]"
" node [ id 5 label \"O\" ]"
" node [ id 6 label \"H\" ]"
" node [ id 7 label \"H\" ]"
" node [ id 8 label \"H\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"-\" ]"
" edge [ source 1 target 4 label \"-\" ]"
" edge [ source 1 target 5 label \"=\" ]"
" edge [ source 2 target 6 label \"-\" ]"
" edge [ source 3 target 7 label \"-\" ]"
" edge [ source 4 target 8 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 id 5 id 6 id 7 id 8 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"oxalate (C2H2O4)\""
" priority 1"
" energy -161"
" node [ id 1 label \"C\" ]"
" node [ id 2 label \"O\" ]"
" node [ id 3 label \"O\" ]"
" node [ id 4 label \"H\" ]"
" node [ id 5 label \"C\" ]"
" node [ id 6 label \"O\" ]"
" node [ id 7 label \"O\" ]"
" node [ id 8 label \"H\" ]"
" edge [ source 1 target 2 label \"=\" ]"
" edge [ source 1 target 3 label \"-\" ]"
" edge [ source 1 target 5 label \"-\" ]"
" edge [ source 3 target 4 label \"-\" ]"
" edge [ source 5 target 6 label \"=\" ]"
" edge [ source 5 target 7 label \"-\" ]"
" edge [ source 7 target 8 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 id 5 id 6 id 7 id 8 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"pyrophos (H1O7P2)\""
" priority 1"
" energy -480.93"
" node [ id 1 label \"P\" ]"
" node [ id 2 label \"O\" ]"
" node [ id 3 label \"O\" ]"
" node [ id 4 label \"O\" ]"
" node [ id 5 label \"O\" ]"
" node [ id 6 label \"P\" ]"
" node [ id 7 label \"O\" ]"
" node [ id 8 label \"O\" ]"
" node [ id 9 label \"O\" ]"
" node [ id 10 label \"H\" ]"
" node [ id 11 label \"H\" ]"
" node [ id 12 label \"H\" ]"
" node [ id 13 label \"H\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"-\" ]"
" edge [ source 1 target 4 label \"-\" ]"
" edge [ source 1 target 5 label \"=\" ]"
" edge [ source 2 target 6 label \"-\" ]"
" edge [ source 3 target 10 label \"-\" ]"
" edge [ source 4 target 12 label \"-\" ]"
" edge [ source 6 target 7 label \"-\" ]"
" edge [ source 6 target 8 label \"-\" ]"
" edge [ source 6 target 9 label \"=\" ]"
" edge [ source 7 target 11 label \"-\" ]"
" edge [ source 8 target 13 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 id 5 id 6 id 7 id 8 id 9 id 10 id 11 id 12 id 13 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

//"molcomp ["
//"description \"selenophos (Se1P1O3H2)\""
//"priority 1"
//"energy -10000"
//"node [ id 1 label \"P\" ]"
//"node [ id 2 label \"O\" ]"
//"node [ id 3 label \"O\" ]"
//"node [ id 4 label \"O\" ]"
//"node [ id 5 label \"Se\" ]"
//"node [ id 6 label \"H\" ]"
//"node [ id 7 label \"H\" ]"
//"node [ id 8 label \"H\" ]"
//"edge [ source 1 target 2 label \"-\" ]"
//"edge [ source 1 target 3 label \"-\" ]"
//"edge [ source 1 target 4 label \"-\" ]"
//"edge [ source 1 target 5 label \"=\" ]"
//"edge [ source 2 target 6 label \"-\" ]"
//"edge [ source 3 target 7 label \"-\" ]"
//"edge [ source 4 target 8 label \"-\" ]"
//"compIDs [ id 1 id 2 id 3 id 4 id 5 id 6 id 7 id 8 ]"
//"]"
//,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"sulfate ion (S1O4)\""
" priority 1"
" energy -177.97"
" node [ id 1 label \"S\" ]"
" node [ id 2 label \"O\" ]"
" node [ id 3 label \"O\" ]"
" node [ id 4 label \"O-1\" ]"
" node [ id 5 label \"O-1\" ]"
" edge [ source 1 target 2 label \"=\" ]"
" edge [ source 1 target 3 label \"=\" ]"
" edge [ source 1 target 4 label \"-\" ]"
" edge [ source 1 target 5 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 id 5 ]"
" ]"
,


///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"sulfite (O3S1H1)\""
" priority 1"
" energy -126.15"
" node [ id 1 label \"S\" ]"
" node [ id 2 label \"O\" ]"
" node [ id 3 label \"O\" ]"
" node [ id 4 label \"O\" ]"
" node [ id 5 label \"H\" ]"
" node [ id 6 label \"H\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"-\" ]"
" edge [ source 1 target 4 label \"=\" ]"
" edge [ source 2 target 5 label \"-\" ]"
" edge [ source 3 target 6 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 id 5 id 6 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"tetrachloromethane (CCl4)\""
" priority 1"
" energy -10.8"
" node [ id 1 label \"C\" ]"
" node [ id 2 label \"Cl\" ]"
" node [ id 3 label \"Cl\" ]"
" node [ id 4 label \"Cl\" ]"
" node [ id 5 label \"Cl\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"-\" ]"
" edge [ source 1 target 4 label \"-\" ]"
" edge [ source 1 target 5 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 id 5 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"thiocyanate (C1N1S1)\""
" priority 1"
" energy 22.158"
" node [ id 1 label \"C\" ]"
" node [ id 2 label \"N\" ]"
" node [ id 3 label \"S\" ]"
" node [ id 4 label \"H\" ]"
" edge [ source 1 target 2 label \"#\" ]"
" edge [ source 1 target 3 label \"-\" ]"
" edge [ source 3 target 4 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

//"molcomp ["
//"description \"thiopyrophos (H1O5S2P2)\""
//"priority 1"
//"energy -10000"
//"node [ id 1 label \"P\" ]"
//"node [ id 2 label \"O\" ]"
//"node [ id 3 label \"O\" ]"
//"node [ id 4 label \"O\" ]"
//"node [ id 5 label \"S\" ]"
//"node [ id 6 label \"P\" ]"
//"node [ id 7 label \"O\" ]"
//"node [ id 8 label \"O\" ]"
//"node [ id 9 label \"S\" ]"
//"node [ id 10 label \"H\" ]"
//"node [ id 11 label \"H\" ]"
//"node [ id 12 label \"H\" ]"
//"node [ id 13 label \"H\" ]"
//"edge [ source 1 target 2 label \"-\" ]"
//"edge [ source 1 target 3 label \"-\" ]"
//"edge [ source 1 target 4 label \"-\" ]"
//"edge [ source 1 target 5 label \"=\" ]"
//"edge [ source 2 target 6 label \"-\" ]"
//"edge [ source 3 target 10 label \"-\" ]"
//"edge [ source 4 target 12 label \"-\" ]"
//"edge [ source 6 target 7 label \"-\" ]"
//"edge [ source 6 target 8 label \"-\" ]"
//"edge [ source 6 target 9 label \"=\" ]"
//"edge [ source 7 target 11 label \"-\" ]"
//"edge [ source 8 target 13 label \"-\" ]"
//"compIDs [ id 1 id 2 id 3 id 4 id 5 id 6 id 7 id 8 id 9 id 10 id 11 id 12 id 13 ]"
//"]"
//,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"triS (S3O6)\""
" priority 1"
" energy -229"
" node [ id 1 label \"S\" ]"
" node [ id 2 label \"S\" ]"
" node [ id 3 label \"O\" ]"
" node [ id 4 label \"O\" ]"
" node [ id 5 label \"O\" ]"
" node [ id 6 label \"S\" ]"
" node [ id 7 label \"O\" ]"
" node [ id 8 label \"O\" ]"
" node [ id 9 label \"O\" ]"
" node [ id 10 label \"H\" ]"
" node [ id 11 label \"H\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"=\" ]"
" edge [ source 1 target 4 label \"=\" ]"
" edge [ source 1 target 5 label \"-\" ]"
" edge [ source 2 target 6 label \"-\" ]"
" edge [ source 5 target 10 label \"-\" ]"
" edge [ source 6 target 7 label \"=\" ]"
" edge [ source 6 target 8 label \"=\" ]"
" edge [ source 6 target 9 label \"-\" ]"
" edge [ source 9 target 11 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 id 5 id 6 id 7 id 8 id 9 id 10 id 11 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"trichloromethane (CHCl3)\""
" priority 1"
" energy -15.9"
" node [ id 1 label \"C\" ]"
" node [ id 2 label \"Cl\" ]"
" node [ id 3 label \"Cl\" ]"
" node [ id 4 label \"Cl\" ]"
" node [ id 5 label \"H\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"-\" ]"
" edge [ source 1 target 4 label \"-\" ]"
" edge [ source 1 target 5 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 id 5 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

//"molcomp ["
//"description \"SO (OS)\""
//"priority 1"
//"energy -10000"
//"node [ id 1 label \"S\" ]"
//"node [ id 2 label \"O\" ]"
//"edge [ source 1 target 2 label \"=\" ]"
//"compIDs [ id 1 id 2 ]"
//"]"
//,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"N2 (N2)\""
" priority 1"
" energy 4.4694"
" node [ id 1 label \"N\" ]"
" node [ id 2 label \"N\" ]"
" edge [ source 1 target 2 label \"#\" ]"
" compIDs [ id 1 id 2 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"O2s 1 (O2)\""
" priority 1"
" energy 6.9"
" node [ id 1 label \"O\" ]"
" node [ id 2 label \"O\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" compIDs [ id 1 id 2 ]"
" ]"
,
" molcomp ["
" description \"O2s 2 (O2)\""
" priority 1"
" energy 6.9"
" node [ id 1 label \"O\" ]"
" node [ id 2 label \"O\" ]"
" edge [ source 1 target 2 label \"=\" ]"
" compIDs [ id 1 id 2 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

" molcomp ["
" description \"urea (C1H4N2O1)\""
" priority 1"
" energy -48.7"
" node [ id 1 label \"C\" ]"
" node [ id 2 label \"N\" ]"
" node [ id 3 label \"N\" ]"
" node [ id 4 label \"O\" ]"
" node [ id 5 label \"H\" ]"
" node [ id 6 label \"H\" ]"
" node [ id 7 label \"H\" ]"
" node [ id 8 label \"H\" ]"
" edge [ source 1 target 2 label \"-\" ]"
" edge [ source 1 target 3 label \"-\" ]"
" edge [ source 1 target 4 label \"=\" ]"
" edge [ source 2 target 5 label \"-\" ]"
" edge [ source 2 target 6 label \"-\" ]"
" edge [ source 3 target 7 label \"-\" ]"
" edge [ source 3 target 8 label \"-\" ]"
" compIDs [ id 1 id 2 id 3 id 4 id 5 id 6 id 7 id 8 ]"
" ]"
,

///////////////////////////////////////////////////////////////////////////////

