
///////////////////////////////////////////////////////////////////////////////
// O=C-C=C CONJUGATION
///////////////////////////////////////////////////////////////////////////////
"molcomp ["
	" description \" OCCC conjugation (no aromatic bond)\""
	" priority 1"
	" energy  -1.55"
	" node [ id 0 label \"O\" ]"
	" node [ id 1 label \"C\" ]"
	" node [ id 2 label \"C\" ]"
	" node [ id 3 label \"C\" ]"
	" edge [ source 0 target 1 label \"=\" ]"
	" edge [ source 1 target 2 label \"-\" ]"
	" edge [ source 2 target 3 label \"=\" ]"
	" compIDs [ id 0 id 1 id 2 id 3 ]"
"]"
,
///////////////////////////////////////////////////////////////////////////////
//"molcomp ["
//	" description \" OCCC conjugation (one aromatic bond [0-1])\""
//	" priority 1"
//	" energy  -1.55"
//	" node [ id 0 label \"o\" ]"
//	" node [ id 1 label \"c\" ]"
//	" node [ id 2 label \"C\" ]"
//	" node [ id 3 label \"C\" ]"
//	" edge [ source 0 target 1 label \":\" ]"
//	" edge [ source 1 target 2 label \"-\" ]"
//	" edge [ source 2 target 3 label \"=\" ]"
//	" compIDs [ id 0 id 1 id 2 id 3 ]"
//"]"
//,
///////////////////////////////////////////////////////////////////////////////
//"molcomp ["
//	" description \" OCCC conjugation (one aromatic bond [1-2])\""
//	" priority 1"
//	" energy  -1.55"
//	" node [ id 0 label \"O\" ]"
//	" node [ id 1 label \"c\" ]"
//	" node [ id 2 label \"c\" ]"
//	" node [ id 3 label \"C\" ]"
//	" edge [ source 0 target 1 label \"=\" ]"
//	" edge [ source 1 target 2 label \":\" ]"
//	" edge [ source 2 target 3 label \"=\" ]"
//	" compIDs [ id 0 id 1 id 2 id 3 ]"
//"]"
//,
///////////////////////////////////////////////////////////////////////////////
"molcomp ["
	" description \" OCCC conjugation (one aromatic bond [2-3]) (c:c:*) [heteroaromatic]\""
	" priority 1"
	" energy  -1.55"
	" node [ id 0 label \"O\" ]"
	" node [ id 1 label \"C\" ]"
	" node [ id 2 label \"c\" ]"
	" node [ id 3 label \"c\" ]"
	" node [ id 4 label \"*\" ]"
	" edge [ source 0 target 1 label \"=\" ]"
	" edge [ source 1 target 2 label \"-\" ]"
	" edge [ source 2 target 3 label \":\" ]"
	" edge [ source 2 target 4 label \":\" ]"
	" ringFragment [ id 3 id 2 id 4 type heteroaromatic ]"
	" compIDs [ id 0 id 1 id 2 id 3 id 4 ]"
"]"
,
///////////////////////////////////////////////////////////////////////////////
"molcomp ["
	" description \" OCCC conjugation (one aromatic bond [2-3]) (c:c:*) [hydrocarbon]\""
	" priority 1"
	" energy  -1.55"
	" node [ id 0 label \"O\" ]"
	" node [ id 1 label \"C\" ]"
	" node [ id 2 label \"c\" ]"
	" node [ id 3 label \"c\" ]"
	" node [ id 4 label \"*\" ]"
	" edge [ source 0 target 1 label \"=\" ]"
	" edge [ source 1 target 2 label \"-\" ]"
	" edge [ source 2 target 3 label \":\" ]"
	" edge [ source 2 target 4 label \":\" ]"
	" ringFragment [ id 3 id 2 id 4 type aromaticHydrocarbon ]"
	" compIDs [ id 0 id 1 id 2 id 3 id 4 ]"
"]"
,
///////////////////////////////////////////////////////////////////////////////
//"molcomp ["
//	" description \" OCCC conjugation (two aromatic bonds [0-1-2])\""
//	" priority 1"
//	" energy  -1.55"
//	" node [ id 0 label \"o\" ]"
//	" node [ id 1 label \"c\" ]"
//	" node [ id 2 label \"c\" ]"
//	" node [ id 3 label \"C\" ]"
//	" edge [ source 0 target 1 label \":\" ]"
//	" edge [ source 1 target 2 label \":\" ]"
//	" edge [ source 2 target 3 label \"=\" ]"
//	" compIDs [ id 0 id 1 id 2 id 3 ]"
//"]"
//,
///////////////////////////////////////////////////////////////////////////////
"molcomp ["
	" description \" OCCC conjugation (two aromatic bonds [1-2-3]) [single ring]\""
	" priority 1"
	" energy  -1.55"
	" node [ id 0 label \"O\" ]"
	" node [ id 1 label \"c\" ]"
	" node [ id 2 label \"c\" ]"
	" node [ id 3 label \"c\" ]"
	" edge [ source 0 target 1 label \"=\" ]"
	" edge [ source 1 target 2 label \":\" ]"
	" edge [ source 2 target 3 label \":\" ]"
	" constrainAdj ["
		" id 2"
		" op ="
		" count 2"
		" edgeLabels [ label \":\" ]"
	" ]"
	" compIDs [ id 0 id 1 id 2 id 3 ]"
"]"
,
///////////////////////////////////////////////////////////////////////////////
"molcomp ["
	" description \" OCCC conjugation (two aromatic bonds [1-2-3]) [fused ring]\""
	" priority 1"
	" energy  -1.55"
	" node [ id 0 label \"O\" ]"
	" node [ id 1 label \"c\" ]"
	" node [ id 2 label \"c\" ]"
	" node [ id 3 label \"c\" ]"
	" node [ id 4 label \"*\" ]"
	" edge [ source 0 target 1 label \"=\" ]"
	" edge [ source 1 target 2 label \":\" ]"
	" edge [ source 2 target 3 label \":\" ]"
	" edge [ source 2 target 4 label \":\" ]"
	" compIDs [ id 0 id 1 id 2 id 3 id 4 ]"
"]"
,
///////////////////////////////////////////////////////////////////////////////
//"molcomp ["
//	" description \" OCCC conjugation (two aromatic bonds [0-1,2-3])\""
//	" priority 1"
//	" energy  -1.55"
//	" node [ id 0 label \"o\" ]"
//	" node [ id 1 label \"c\" ]"
//	" node [ id 2 label \"c\" ]"
//	" node [ id 3 label \"c\" ]"
//	" edge [ source 0 target 1 label \":\" ]"
//	" edge [ source 1 target 2 label \"-\" ]"
//	" edge [ source 2 target 3 label \":\" ]"
//	" compIDs [ id 0 id 1 id 2 id 3 ]"
//"]"
//,
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
// O=C-C=O CONJUGATION
///////////////////////////////////////////////////////////////////////////////
"molcomp ["
	" description \" OCCO conjugation (no aromatic bond)\""
	" priority 1"
	" energy  2.46"
	" node [ id 0 label \"O\" ]"
	" node [ id 1 label \"C\" ]"
	" node [ id 2 label \"C\" ]"
	" node [ id 3 label \"O\" ]"
	" edge [ source 0 target 1 label \"=\" ]"
	" edge [ source 1 target 2 label \"-\" ]"
	" edge [ source 2 target 3 label \"=\" ]"
	" compIDs [ id 0 id 1 id 2 id 3 ]"
"]"
,
///////////////////////////////////////////////////////////////////////////////
//"molcomp ["
//	" description \" OCCO conjugation (one aromatic bond [0-1] == [2-3])\""
//	" priority 1"
//	" energy  2.46"
//	" node [ id 0 label \"o\" ]"
//	" node [ id 1 label \"c\" ]"
//	" node [ id 2 label \"C\" ]"
//	" node [ id 3 label \"O\" ]"
//	" edge [ source 0 target 1 label \":\" ]"
//	" edge [ source 1 target 2 label \"-\" ]"
//	" edge [ source 2 target 3 label \"=\" ]"
//	" compIDs [ id 0 id 1 id 2 id 3 ]"
//"]"
//,
///////////////////////////////////////////////////////////////////////////////
//"molcomp ["
//	" description \" OCCO conjugation (one aromatic bond [1-2])\""
//	" priority 1"
//	" energy  2.46"
//	" node [ id 0 label \"O\" ]"
//	" node [ id 1 label \"c\" ]"
//	" node [ id 2 label \"c\" ]"
//	" node [ id 3 label \"O\" ]"
//	" edge [ source 0 target 1 label \"=\" ]"
//	" edge [ source 1 target 2 label \":\" ]"
//	" edge [ source 2 target 3 label \"=\" ]"
//	" compIDs [ id 0 id 1 id 2 id 3 ]"
//"]"
//,
///////////////////////////////////////////////////////////////////////////////
//"molcomp ["
//	" description \" OCCO conjugation (two aromatic bonds [0-1-2] == [1-2-3])\""
//	" priority 1"
//	" energy  2.46"
//	" node [ id 0 label \"o\" ]"
//	" node [ id 1 label \"c\" ]"
//	" node [ id 2 label \"c\" ]"
//	" node [ id 3 label \"O\" ]"
//	" edge [ source 0 target 1 label \":\" ]"
//	" edge [ source 1 target 2 label \":\" ]"
//	" edge [ source 2 target 3 label \"=\" ]"
//	" compIDs [ id 0 id 1 id 2 id 3 ]"
//"]"
//,
///////////////////////////////////////////////////////////////////////////////
//"molcomp ["
//	" description \" OCCO conjugation (two aromatic bonds [0-1,2-3])\""
//	" priority 1"
//	" energy  2.46"
//	" node [ id 0 label \"o\" ]"
//	" node [ id 1 label \"c\" ]"
//	" node [ id 2 label \"c\" ]"
//	" node [ id 3 label \"o\" ]"
//	" edge [ source 0 target 1 label \":\" ]"
//	" edge [ source 1 target 2 label \"-\" ]"
//	" edge [ source 2 target 3 label \":\" ]"
//	" compIDs [ id 0 id 1 id 2 id 3 ]"
//"]"
//,
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
// O=C-C=N CONJUGATION
///////////////////////////////////////////////////////////////////////////////
"molcomp ["
	" description \" OCCN conjugation (no aromatic bond)\""
	" priority 1"
	" energy  -3.02"
	" node [ id 0 label \"O\" ]"
	" node [ id 1 label \"C\" ]"
	" node [ id 2 label \"C\" ]"
	" node [ id 3 label \"N\" ]"
	" edge [ source 0 target 1 label \"=\" ]"
	" edge [ source 1 target 2 label \"-\" ]"
	" edge [ source 2 target 3 label \"=\" ]"
	" compIDs [ id 0 id 1 id 2 id 3 ]"
"]"
,
///////////////////////////////////////////////////////////////////////////////
//"molcomp ["
//	" description \" OCCN conjugation (one aromatic bond [0-1])\""
//	" priority 1"
//	" energy  -3.02"
//	" node [ id 0 label \"o\" ]"
//	" node [ id 1 label \"c\" ]"
//	" node [ id 2 label \"C\" ]"
//	" node [ id 3 label \"N\" ]"
//	" edge [ source 0 target 1 label \":\" ]"
//	" edge [ source 1 target 2 label \"-\" ]"
//	" edge [ source 2 target 3 label \"=\" ]"
//	" compIDs [ id 0 id 1 id 2 id 3 ]"
//"]"
//,
///////////////////////////////////////////////////////////////////////////////
//"molcomp ["
//	" description \" OCCN conjugation (one aromatic bond [1-2])\""
//	" priority 1"
//	" energy  -3.02"
//	" node [ id 0 label \"O\" ]"
//	" node [ id 1 label \"c\" ]"
//	" node [ id 2 label \"c\" ]"
//	" node [ id 3 label \"N\" ]"
//	" edge [ source 0 target 1 label \"=\" ]"
//	" edge [ source 1 target 2 label \":\" ]"
//	" edge [ source 2 target 3 label \"=\" ]"
//	" compIDs [ id 0 id 1 id 2 id 3 ]"
//"]"
//,
///////////////////////////////////////////////////////////////////////////////
"molcomp ["
	" description \" OCCN conjugation (one aromatic bond [2-3]) (n:c:n)\""
	" priority 1"
	" energy  -3.02"
	" node [ id 0 label \"O\" ]"
	" node [ id 1 label \"C\" ]"
	" node [ id 2 label \"c\" ]"
	" node [ id 3 label \"n\" ]"
	" node [ id 4 label \"n\" ]"
	" edge [ source 0 target 1 label \"=\" ]"
	" edge [ source 1 target 2 label \"-\" ]"
	" edge [ source 2 target 3 label \":\" ]"
	" edge [ source 2 target 4 label \":\" ]"
	" constrainAdj ["
		" id 3"
		" op ="
		" count 0"
		" edgeLabels [ label \"-\" ]"
	" ]"
	" ringFragment [ id 3 id 2 id 4 type heteroaromatic ]"
	" compIDs [ id 0 id 1 id 2 id 3 id 4 ]"
"]"
,
///////////////////////////////////////////////////////////////////////////////
"molcomp ["
	" description \" OCCN conjugation (one aromatic bond [2-3]) (n:c:~[c,n])\""
	" priority 1"
	" energy  -3.02"
	" node [ id 0 label \"O\" ]"
	" node [ id 1 label \"C\" ]"
	" node [ id 2 label \"c\" ]"
	" node [ id 3 label \"n\" ]"
	" node [ id 4 label \"*\" ]"
	" edge [ source 0 target 1 label \"=\" ]"
	" edge [ source 1 target 2 label \"-\" ]"
	" edge [ source 2 target 3 label \":\" ]"
	" edge [ source 2 target 4 label \":\" ]"
	" constrainAdj ["
		" id 3"
		" op ="
		" count 0"
		" edgeLabels [ label \"-\" ]"
	" ]"
	" constrainNode [ id 4 op ! nodeLabels [ label \"n\" label \"c\" ] ]\n"
	" ringFragment [ id 3 id 2 id 4 type heteroaromatic ]\n"
	" compIDs [ id 0 id 1 id 2 id 3 ]"
"]"
,
///////////////////////////////////////////////////////////////////////////////
"molcomp ["
	" description \" OCCN conjugation (one aromatic bond [2-3]) (n:c:c:c)\""
	" priority 1"
	" energy  -3.02"
	" node [ id 0 label \"O\" ]"
	" node [ id 1 label \"C\" ]"
	" node [ id 2 label \"c\" ]"
	" node [ id 3 label \"n\" ]"
	" node [ id 4 label \"c\" ]"
	" node [ id 5 label \"c\" ]"
	" edge [ source 0 target 1 label \"=\" ]"
	" edge [ source 1 target 2 label \"-\" ]"
	" edge [ source 2 target 3 label \":\" ]"
	" edge [ source 2 target 4 label \":\" ]"
	" edge [ source 4 target 5 label \":\" ]"
	" constrainAdj ["
		" id 3"
		" op ="
		" count 0"
		" edgeLabels [ label \"-\" ]"
	" ]"
	" ringFragment [ id 3 id 2 id 4 id 5 type heteroaromatic ]\n"
	" compIDs [ id 0 id 1 id 2 id 3 ]"
"]"
,
///////////////////////////////////////////////////////////////////////////////
//"molcomp ["
//	" description \" OCCN conjugation (two aromatic bonds [0-1-2])\""
//	" priority 1"
//	" energy  -3.02"
//	" node [ id 0 label \"o\" ]"
//	" node [ id 1 label \"c\" ]"
//	" node [ id 2 label \"c\" ]"
//	" node [ id 3 label \"N\" ]"
//	" edge [ source 0 target 1 label \":\" ]"
//	" edge [ source 1 target 2 label \":\" ]"
//	" edge [ source 2 target 3 label \"=\" ]"
//	" compIDs [ id 0 id 1 id 2 id 3 ]"
//"]"
//,
///////////////////////////////////////////////////////////////////////////////
//"molcomp ["
//	" description \" OCCN conjugation (two aromatic bonds [1-2-3])\""
//	" priority 1"
//	" energy  -3.02"
//	" node [ id 0 label \"O\" ]"
//	" node [ id 1 label \"c\" ]"
//	" node [ id 2 label \"c\" ]"
//	" node [ id 3 label \"n\" ]"
//	" edge [ source 0 target 1 label \"=\" ]"
//	" edge [ source 1 target 2 label \":\" ]"
//	" edge [ source 2 target 3 label \":\" ]"
//	" compIDs [ id 0 id 1 id 2 id 3 ]"
//"]"
//,
///////////////////////////////////////////////////////////////////////////////
//"molcomp ["
//	" description \" OCCN conjugation (two aromatic bonds [0-1,2-3])\""
//	" priority 1"
//	" energy  -3.02"
//	" node [ id 0 label \"o\" ]"
//	" node [ id 1 label \"c\" ]"
//	" node [ id 2 label \"c\" ]"
//	" node [ id 3 label \"n\" ]"
//	" edge [ source 0 target 1 label \":\" ]"
//	" edge [ source 1 target 2 label \"-\" ]"
//	" edge [ source 2 target 3 label \":\" ]"
//	" compIDs [ id 0 id 1 id 2 id 3 ]"
//"]"
//,
///////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////
// N=C-C=C CONJUGATION
///////////////////////////////////////////////////////////////////////////////
"molcomp ["
	" description \" NCCC conjugation (no aromatic bond)\""
	" priority 1"
	" energy  -5.29"
	" node [ id 0 label \"N\" ]"
	" node [ id 1 label \"C\" ]"
	" node [ id 2 label \"C\" ]"
	" node [ id 3 label \"C\" ]"
	" edge [ source 0 target 1 label \"=\" ]"
	" edge [ source 1 target 2 label \"-\" ]"
	" edge [ source 2 target 3 label \"=\" ]"
	" compIDs [ id 0 id 1 id 2 id 3 ]"
"]"
,
///////////////////////////////////////////////////////////////////////////////
"molcomp ["
	" description \" NCCC conjugation (one aromatic bond [0-1]) (n:c:n)\""
	" priority 1"
	" energy  -5.29"
	" node [ id 0 label \"n\" ]"
	" node [ id 1 label \"c\" ]"
	" node [ id 2 label \"C\" ]"
	" node [ id 3 label \"C\" ]"
	" node [ id 4 label \"n\" ]"
	" edge [ source 0 target 1 label \":\" ]"
	" edge [ source 1 target 2 label \"-\" ]"
	" edge [ source 2 target 3 label \"=\" ]"
	" edge [ source 1 target 4 label \":\" ]"
	" constrainAdj ["
		" id 0"
		" op ="
		" count 0"
		" edgeLabels [ label \"-\" ]"
	" ]"
	" ringFragment [ id 0 id 1 id 4 type heteroaromatic ]\n"
	" compIDs [ id 0 id 1 id 2 id 3 id 4 ]"
"]"
,
///////////////////////////////////////////////////////////////////////////////
"molcomp ["
	" description \" NCCC conjugation (one aromatic bond [0-1]) (n:c:~[c,n])\""
	" priority 1"
	" energy  -5.29"
	" node [ id 0 label \"n\" ]"
	" node [ id 1 label \"c\" ]"
	" node [ id 2 label \"C\" ]"
	" node [ id 3 label \"C\" ]"
	" node [ id 4 label \"*\" ]"
	" edge [ source 0 target 1 label \":\" ]"
	" edge [ source 1 target 2 label \"-\" ]"
	" edge [ source 2 target 3 label \"=\" ]"
	" edge [ source 1 target 4 label \":\" ]"
	" constrainAdj ["
		" id 0"
		" op ="
		" count 0"
		" edgeLabels [ label \"-\" ]"
	" ]"
	" constrainNode [ id 4 op ! nodeLabels [ label \"n\" label \"c\" ] ]\n"
	" ringFragment [ id 0 id 1 id 4 type heteroaromatic ]\n"
	" compIDs [ id 0 id 1 id 2 id 3 id 4 ]"
"]"
,
///////////////////////////////////////////////////////////////////////////////
"molcomp ["
	" description \" NCCC conjugation (one aromatic bond [0-1]) (n:c:c:c)\""
	" priority 1"
	" energy  -5.29"
	" node [ id 0 label \"n\" ]"
	" node [ id 1 label \"c\" ]"
	" node [ id 2 label \"C\" ]"
	" node [ id 3 label \"C\" ]"
	" node [ id 4 label \"c\" ]"
	" node [ id 5 label \"c\" ]"
	" edge [ source 0 target 1 label \":\" ]"
	" edge [ source 1 target 2 label \"-\" ]"
	" edge [ source 2 target 3 label \"=\" ]"
	" edge [ source 1 target 4 label \":\" ]"
	" edge [ source 4 target 5 label \":\" ]"
	" constrainAdj ["
		" id 0"
		" op ="
		" count 0"
		" edgeLabels [ label \"-\" ]"
	" ]"
	" ringFragment [ id 0 id 1 id 4 id 5 type heteroaromatic ]\n"
	" compIDs [ id 0 id 1 id 2 id 3 ]"
"]"
,
///////////////////////////////////////////////////////////////////////////////
//"molcomp ["
//	" description \" NCCC conjugation (one aromatic bond [1-2])\""
//	" priority 1"
//	" energy  -5.29"
//	" node [ id 0 label \"N\" ]"
//	" node [ id 1 label \"c\" ]"
//	" node [ id 2 label \"c\" ]"
//	" node [ id 3 label \"C\" ]"
//	" edge [ source 0 target 1 label \"=\" ]"
//	" edge [ source 1 target 2 label \":\" ]"
//	" edge [ source 2 target 3 label \"=\" ]"
//	" compIDs [ id 0 id 1 id 2 id 3 ]"
//"]"
//,
///////////////////////////////////////////////////////////////////////////////
"molcomp ["
	" description \" NCCC conjugation (one aromatic bond [2-3]) (c:c:*) [heteroaromatic]\""
	" priority 1"
	" energy  -5.29"
	" node [ id 0 label \"N\" ]"
	" node [ id 1 label \"C\" ]"
	" node [ id 2 label \"c\" ]"
	" node [ id 3 label \"c\" ]"
	" node [ id 4 label \"*\" ]"
	" edge [ source 0 target 1 label \"=\" ]"
	" edge [ source 1 target 2 label \"-\" ]"
	" edge [ source 2 target 3 label \":\" ]"
	" edge [ source 2 target 4 label \":\" ]"
	" ringFragment [ id 3 id 2 id 4 type heteroaromatic ]"
	" compIDs [ id 0 id 1 id 2 id 3 id 4 ]"
"]"
,
///////////////////////////////////////////////////////////////////////////////
"molcomp ["
	" description \" NCCC conjugation (one aromatic bond [2-3]) (c:c:*) [hydrocarbon]\""
	" priority 1"
	" energy  -5.29"
	" node [ id 0 label \"N\" ]"
	" node [ id 1 label \"C\" ]"
	" node [ id 2 label \"c\" ]"
	" node [ id 3 label \"c\" ]"
	" node [ id 4 label \"*\" ]"
	" edge [ source 0 target 1 label \"=\" ]"
	" edge [ source 1 target 2 label \"-\" ]"
	" edge [ source 2 target 3 label \":\" ]"
	" edge [ source 2 target 4 label \":\" ]"
	" ringFragment [ id 3 id 2 id 4 type aromaticHydrocarbon ]"
	" compIDs [ id 0 id 1 id 2 id 3 id 4 ]"
"]"
,
///////////////////////////////////////////////////////////////////////////////
//"molcomp ["
//	" description \" NCCC conjugation (two aromatic bonds [0-1-2])\""
//	" priority 1"
//	" energy  -5.29"
//	" node [ id 0 label \"n\" ]"
//	" node [ id 1 label \"c\" ]"
//	" node [ id 2 label \"c\" ]"
//	" node [ id 3 label \"C\" ]"
//	" edge [ source 0 target 1 label \":\" ]"
//	" edge [ source 1 target 2 label \":\" ]"
//	" edge [ source 2 target 3 label \"=\" ]"
//	" compIDs [ id 0 id 1 id 2 id 3 ]"
//"]"
//,
///////////////////////////////////////////////////////////////////////////////
//"molcomp ["
//	" description \" NCCC conjugation (two aromatic bonds [1-2-3])\""
//	" priority 1"
//	" energy  -5.29"
//	" node [ id 0 label \"N\" ]"
//	" node [ id 1 label \"c\" ]"
//	" node [ id 2 label \"c\" ]"
//	" node [ id 3 label \"c\" ]"
//	" edge [ source 0 target 1 label \"=\" ]"
//	" edge [ source 1 target 2 label \":\" ]"
//	" edge [ source 2 target 3 label \":\" ]"
//	" compIDs [ id 0 id 1 id 2 id 3 ]"
//"]"
//,
///////////////////////////////////////////////////////////////////////////////
"molcomp ["
	" description \" NCCC conjugation (two aromatic bonds [0-1,2-3]) (n:c:n)+(c:c:*) [heteroaromatic]\""
	" priority 1"
	" energy  -5.29"
	" node [ id 0 label \"n\" ]"
	" node [ id 1 label \"c\" ]"
	" node [ id 2 label \"c\" ]"
	" node [ id 3 label \"c\" ]"
	" node [ id 4 label \"*\" ]"
	" node [ id 5 label \"n\" ]"
	" edge [ source 0 target 1 label \":\" ]"
	" edge [ source 1 target 2 label \"-\" ]"
	" edge [ source 2 target 3 label \":\" ]"
	" edge [ source 2 target 4 label \":\" ]"
	" edge [ source 1 target 5 label \":\" ]"
	" constrainAdj ["
		" id 0"
		" op ="
		" count 0"
		" edgeLabels [ label \"-\" ]"
	" ]"
	" ringFragment [ id 3 id 2 id 4 type heteroaromatic ]"
	" ringFragment [ id 0 id 1 id 5 type heteroaromatic ]"
	" compIDs [ id 0 id 1 id 2 id 3 id 4 id 5 ]"
"]"
,
///////////////////////////////////////////////////////////////////////////////
"molcomp ["
	" description \" NCCC conjugation (two aromatic bonds [0-1,2-3]) (n:c:n)+(c:c:*) [hydrocarbon]\""
	" priority 1"
	" energy  -5.29"
	" node [ id 0 label \"n\" ]"
	" node [ id 1 label \"c\" ]"
	" node [ id 2 label \"c\" ]"
	" node [ id 3 label \"c\" ]"
	" node [ id 4 label \"*\" ]"
	" node [ id 5 label \"n\" ]"
	" edge [ source 0 target 1 label \":\" ]"
	" edge [ source 1 target 2 label \"-\" ]"
	" edge [ source 2 target 3 label \":\" ]"
	" edge [ source 2 target 4 label \":\" ]"
	" edge [ source 1 target 5 label \":\" ]"
	" constrainAdj ["
		" id 0"
		" op ="
		" count 0"
		" edgeLabels [ label \"-\" ]"
	" ]"
	" ringFragment [ id 3 id 2 id 4 type aromaticHydrocarbon ]"
	" ringFragment [ id 0 id 1 id 5 type heteroaromatic ]"
	" compIDs [ id 0 id 1 id 2 id 3 id 4 id 5 ]"
"]"
,
///////////////////////////////////////////////////////////////////////////////
"molcomp ["
	" description \" NCCC conjugation (two aromatic bonds [0-1,2-3]) (n:c:~[c,n])+(c:c:*) [heteroaromatic]\""
	" priority 1"
	" energy  -5.29"
	" node [ id 0 label \"n\" ]"
	" node [ id 1 label \"c\" ]"
	" node [ id 2 label \"c\" ]"
	" node [ id 3 label \"c\" ]"
	" node [ id 4 label \"*\" ]"
	" node [ id 5 label \"*\" ]"
	" edge [ source 0 target 1 label \":\" ]"
	" edge [ source 1 target 2 label \"-\" ]"
	" edge [ source 2 target 3 label \":\" ]"
	" edge [ source 2 target 4 label \":\" ]"
	" edge [ source 1 target 5 label \":\" ]"
	" constrainAdj ["
		" id 0"
		" op ="
		" count 0"
		" edgeLabels [ label \"-\" ]"
	" ]"
	" constrainNode [ id 5 op ! nodeLabels [ label \"n\" label \"c\" ] ]\n"
	" ringFragment [ id 3 id 2 id 4 type heteroaromatic ]"
	" ringFragment [ id 0 id 1 id 5 type heteroaromatic ]"
	" compIDs [ id 0 id 1 id 2 id 3 id 4 id 5 ]"
"]"
,
///////////////////////////////////////////////////////////////////////////////
"molcomp ["
	" description \" NCCC conjugation (two aromatic bonds [0-1,2-3]) (n:c:~[c,n])+(c:c:*) [hydrocarbon]\""
	" priority 1"
	" energy  -5.29"
	" node [ id 0 label \"n\" ]"
	" node [ id 1 label \"c\" ]"
	" node [ id 2 label \"c\" ]"
	" node [ id 3 label \"c\" ]"
	" node [ id 4 label \"*\" ]"
	" node [ id 5 label \"*\" ]"
	" edge [ source 0 target 1 label \":\" ]"
	" edge [ source 1 target 2 label \"-\" ]"
	" edge [ source 2 target 3 label \":\" ]"
	" edge [ source 2 target 4 label \":\" ]"
	" edge [ source 1 target 5 label \":\" ]"
	" constrainAdj ["
		" id 0"
		" op ="
		" count 0"
		" edgeLabels [ label \"-\" ]"
	" ]"
	" constrainNode [ id 5 op ! nodeLabels [ label \"n\" label \"c\" ] ]\n"
	" ringFragment [ id 3 id 2 id 4 type aromaticHydrocarbon ]"
	" ringFragment [ id 0 id 1 id 5 type heteroaromatic ]"
	" compIDs [ id 0 id 1 id 2 id 3 id 4 id 5 ]"
"]"
,
///////////////////////////////////////////////////////////////////////////////
"molcomp ["
	" description \" NCCC conjugation (two aromatic bonds [0-1,2-3]) (n:c:c:c)+(c:c:*) [heteroaromat]\""
	" priority 1"
	" energy  -5.29"
	" node [ id 0 label \"n\" ]"
	" node [ id 1 label \"c\" ]"
	" node [ id 2 label \"c\" ]"
	" node [ id 3 label \"c\" ]"
	" node [ id 4 label \"*\" ]"
	" node [ id 5 label \"c\" ]"
	" node [ id 6 label \"c\" ]"
	" edge [ source 0 target 1 label \":\" ]"
	" edge [ source 1 target 2 label \"-\" ]"
	" edge [ source 2 target 3 label \":\" ]"
	" edge [ source 2 target 4 label \":\" ]"
	" edge [ source 1 target 5 label \":\" ]"
	" edge [ source 5 target 6 label \":\" ]"
	" constrainAdj ["
		" id 0"
		" op ="
		" count 0"
		" edgeLabels [ label \"-\" ]"
	" ]"
	" ringFragment [ id 3 id 2 id 4 type heteroaromatic ]"
	" ringFragment [ id 0 id 1 id 5 id 6 type heteroaromatic ]"
	" compIDs [ id 0 id 1 id 2 id 3 id 4 id 5 ]"
"]"
,
///////////////////////////////////////////////////////////////////////////////
"molcomp ["
	" description \" NCCC conjugation (two aromatic bonds [0-1,2-3]) (n:c:c:c)+(c:c:*) [hydrocarbon]\""
	" priority 1"
	" energy  -5.29"
	" node [ id 0 label \"n\" ]"
	" node [ id 1 label \"c\" ]"
	" node [ id 2 label \"c\" ]"
	" node [ id 3 label \"c\" ]"
	" node [ id 4 label \"*\" ]"
	" node [ id 5 label \"c\" ]"
	" node [ id 6 label \"c\" ]"
	" edge [ source 0 target 1 label \":\" ]"
	" edge [ source 1 target 2 label \"-\" ]"
	" edge [ source 2 target 3 label \":\" ]"
	" edge [ source 2 target 4 label \":\" ]"
	" edge [ source 1 target 5 label \":\" ]"
	" edge [ source 5 target 6 label \":\" ]"
	" constrainAdj ["
		" id 0"
		" op ="
		" count 0"
		" edgeLabels [ label \"-\" ]"
	" ]"
	" ringFragment [ id 3 id 2 id 4 type aromaticHydrocarbon ]"
	" ringFragment [ id 0 id 1 id 5 id 6 type heteroaromatic ]"
	" compIDs [ id 0 id 1 id 2 id 3 id 4 id 5 ]"
"]"
,
///////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////
// C=C-C=C CONJUGATION
///////////////////////////////////////////////////////////////////////////////
"molcomp ["
	" description \" CCCC conjugation (no aromatic bond)\""
	" priority 1"
	" energy  -4.82"
	" node [ id 0 label \"C\" ]"
	" node [ id 1 label \"C\" ]"
	" node [ id 2 label \"C\" ]"
	" node [ id 3 label \"C\" ]"
	" edge [ source 0 target 1 label \"=\" ]"
	" edge [ source 1 target 2 label \"-\" ]"
	" edge [ source 2 target 3 label \"=\" ]"
	" compIDs [ id 0 id 1 id 2 id 3 ]"
"]"
,
///////////////////////////////////////////////////////////////////////////////
"molcomp ["
	" description \" CCCC conjugation (one aromatic bond [0-1] == [2-3]) (c:c:*) [heteroaromat]\""
	" priority 1"
	" energy  -4.82"
	" node [ id 0 label \"c\" ]"
	" node [ id 1 label \"c\" ]"
	" node [ id 2 label \"C\" ]"
	" node [ id 3 label \"C\" ]"
	" node [ id 4 label \"*\" ]"
	" edge [ source 0 target 1 label \":\" ]"
	" edge [ source 1 target 2 label \"-\" ]"
	" edge [ source 2 target 3 label \"=\" ]"
	" edge [ source 1 target 4 label \":\" ]"
	" ringFragment [ id 0 id 1 id 4 type heteroaromatic ]"
	" compIDs [ id 0 id 1 id 2 id 3 id 4 ]"
"]"
,
///////////////////////////////////////////////////////////////////////////////
"molcomp ["
	" description \" CCCC conjugation (one aromatic bond [0-1] == [2-3]) (c:c:*) [hydrocarbon]\""
	" priority 1"
	" energy  -4.82"
	" node [ id 0 label \"c\" ]"
	" node [ id 1 label \"c\" ]"
	" node [ id 2 label \"C\" ]"
	" node [ id 3 label \"C\" ]"
	" node [ id 4 label \"*\" ]"
	" edge [ source 0 target 1 label \":\" ]"
	" edge [ source 1 target 2 label \"-\" ]"
	" edge [ source 2 target 3 label \"=\" ]"
	" edge [ source 1 target 4 label \":\" ]"
	" ringFragment [ id 0 id 1 id 4 type aromaticHydrocarbon ]"
	" compIDs [ id 0 id 1 id 2 id 3 id 4 ]"
"]"
,
///////////////////////////////////////////////////////////////////////////////
//"molcomp ["
//	" description \" CCCC conjugation (one aromatic bond [1-2])\""
//	" priority 1"
//	" energy  -4.82"
//	" node [ id 0 label \"C\" ]"
//	" node [ id 1 label \"c\" ]"
//	" node [ id 2 label \"c\" ]"
//	" node [ id 3 label \"C\" ]"
//	" edge [ source 0 target 1 label \"=\" ]"
//	" edge [ source 1 target 2 label \":\" ]"
//	" edge [ source 2 target 3 label \"=\" ]"
//	" compIDs [ id 0 id 1 id 2 id 3 ]"
//"]"
//,
///////////////////////////////////////////////////////////////////////////////
//"molcomp ["
//	" description \" CCCC conjugation (two aromatic bonds [0-1-2] == [1-2-3])\""
//	" priority 1"
//	" energy  -4.82"
//	" node [ id 0 label \"c\" ]"
//	" node [ id 1 label \"c\" ]"
//	" node [ id 2 label \"c\" ]"
//	" node [ id 3 label \"C\" ]"
//	" edge [ source 0 target 1 label \":\" ]"
//	" edge [ source 1 target 2 label \":\" ]"
//	" edge [ source 2 target 3 label \"=\" ]"
//	" compIDs [ id 0 id 1 id 2 id 3 ]"
//"]"
//,
///////////////////////////////////////////////////////////////////////////////
"molcomp ["
	" description \" CCCC conjugation (two aromatic bonds [0-1,2-3]) (c:c:*)+(c:c:*) [2 heteroaromat]\""
	" priority 1"
	" energy  -4.82"
	" node [ id 0 label \"c\" ]"
	" node [ id 1 label \"c\" ]"
	" node [ id 2 label \"c\" ]"
	" node [ id 3 label \"c\" ]"
	" node [ id 4 label \"*\" ]"
	" node [ id 5 label \"*\" ]"
	" edge [ source 0 target 1 label \":\" ]"
	" edge [ source 1 target 2 label \"-\" ]"
	" edge [ source 2 target 3 label \":\" ]"
	" edge [ source 1 target 4 label \":\" ]"
	" edge [ source 2 target 5 label \":\" ]"
	" ringFragment [ id 0 id 1 id 4 type heteroaromatic ]"
	" ringFragment [ id 3 id 2 id 5 type heteroaromatic ]"
	" compIDs [ id 0 id 1 id 2 id 3 id 4 id 5 ]"
"]"
,
///////////////////////////////////////////////////////////////////////////////
"molcomp ["
	" description \" CCCC conjugation (two aromatic bonds [0-1,2-3]) (c:c:*)+(c:c:*) [heteroaromat+hydrocarbon]\""
	" priority 1"
	" energy  -4.82"
	" node [ id 0 label \"c\" ]"
	" node [ id 1 label \"c\" ]"
	" node [ id 2 label \"c\" ]"
	" node [ id 3 label \"c\" ]"
	" node [ id 4 label \"*\" ]"
	" node [ id 5 label \"*\" ]"
	" edge [ source 0 target 1 label \":\" ]"
	" edge [ source 1 target 2 label \"-\" ]"
	" edge [ source 2 target 3 label \":\" ]"
	" edge [ source 1 target 4 label \":\" ]"
	" edge [ source 2 target 5 label \":\" ]"
	" ringFragment [ id 0 id 1 id 4 type heteroaromatic ]"
	" ringFragment [ id 3 id 2 id 5 type aromaticHydrocarbon ]"
	" compIDs [ id 0 id 1 id 2 id 3 id 4 id 5 ]"
"]"
,
///////////////////////////////////////////////////////////////////////////////
"molcomp ["
	" description \" CCCC conjugation (two aromatic bonds [0-1,2-3]) (c:c:*)+(c:c:*) [2 hydrocarbon]\""
	" priority 1"
	" energy  -4.82"
	" node [ id 0 label \"c\" ]"
	" node [ id 1 label \"c\" ]"
	" node [ id 2 label \"c\" ]"
	" node [ id 3 label \"c\" ]"
	" node [ id 4 label \"*\" ]"
	" node [ id 5 label \"*\" ]"
	" edge [ source 0 target 1 label \":\" ]"
	" edge [ source 1 target 2 label \"-\" ]"
	" edge [ source 2 target 3 label \":\" ]"
	" edge [ source 1 target 4 label \":\" ]"
	" edge [ source 2 target 5 label \":\" ]"
	" ringFragment [ id 0 id 1 id 4 type aromaticHydrocarbon ]"
	" ringFragment [ id 3 id 2 id 5 type aromaticHydrocarbon ]"
	" compIDs [ id 0 id 1 id 2 id 3 id 4 id 5 ]"
"]"
,
///////////////////////////////////////////////////////////////////////////////

