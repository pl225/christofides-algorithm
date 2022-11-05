#pragma once

#include "./Matching/Graph.h"
#include "./Matching/BinaryHeap.h"
#include "./Matching/Globals.h"
#include <limits>

//Prim's algorithm using binary heap
pair< list<int>, double > Prim(const Graph & G, const vector<double> & cost, const list<pair<int, int>> &fixedOne = list<pair<int, int>>());