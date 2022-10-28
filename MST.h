#pragma once

#include "./Matching/Graph.h"
#include "./Matching/BinaryHeap.h"
#include "./Matching/Globals.h"

//Prim's algorithm using binary heap
pair< list<int>, double > Prim(const Graph & G, const vector<double> & cost);