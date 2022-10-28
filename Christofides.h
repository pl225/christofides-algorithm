#pragma once

#include "MST.h"
#include "./Matching/Matching.h"
#include "./Matching/Graph.h"

/*
Christofides algorithm
returns a pair containing a vector and a double
the vector contains the indices of the edges in the solution
the double is the solution cost
*/
pair< vector<int>, double > Christofides(const Graph & G, const vector<double> & cost);