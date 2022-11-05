#include "MST.h"

//Prim's algorithm using binary heap
pair< list<int>, double > Prim(const Graph & G, const vector<double> & cost, const list<pair<int, int>> &fixedOne)
{
	BinaryHeap B;

	vector<int> father(G.GetNumVertices(), -1);
	vector<int> fixado(G.GetNumVertices(), -3);
	list<int> mst;

	double obj = 0;

	if (fixedOne.empty()) {
		//Put 0 in the heap
		B.Insert(0, 0);
	} else {
		for (const pair<int, int> &edge: fixedOne) {
			int w = edge.first, u = edge.second;
			if (father[u] == -1 && father[w] == -1) {
				B.Insert(std::numeric_limits<double>::min(), u);
				father[u] = w;
				fixado[u] = w;
				father[w] = -2;
			} else if (father[w] == -1 && father[u] != -1) {
				B.Insert(std::numeric_limits<double>::min(), w);
				father[w] = u;
				fixado[w] = u;
			} else if (father[u] == -1 && father[w] != -1) {
				B.Insert(std::numeric_limits<double>::min(), u);
				father[u] = w;
				fixado[u] = w;
			}
		}
	}

	while(B.Size() > 0)
	{
		//Select the vertex that is closest to the growing tree
		int u = B.DeleteMin();
		int w = father[u];

		//Add {w,u} to the tree
		if(w != -1 && w != -3)
		{
			int i = G.GetEdgeIndex(w, u);
			mst.push_back(i);
			obj += cost[i];
		}

		//This is to indicate that u is already in the tree
		father[u] = -2;

		//Update the heap with vertices adjacent to u
		for(list<int>::const_iterator it = G.AdjList(u).begin(); it != G.AdjList(u).end(); it++)
		{
			int v = *it;
			
			//if v is already in the tree
			if(father[v] == -2)
				continue;

			double c = fixado[u] == v || fixado[v] == u
				? std::numeric_limits<double>::min()
				: cost[G.GetEdgeIndex(u,v)];

			//v has not been reached by anyone else
			if(father[v] == -1)
			{
				father[v] = u;	
				B.Insert(c, v);
			}
			//we found a cheaper connection to v
			else
			{
				double cc = fixado[father[v]] == v || fixado[v] == father[v]
					? std::numeric_limits<double>::min()
					: cost[G.GetEdgeIndex(father[v], v)];
				
				if( LESS(c, cc) )
				{
					father[v] = u;
					B.ChangeKey(c, v);
				}
			}
		}
	}

	if((int)mst.size() < G.GetNumVertices()-1)
		throw "Error: graph does not have a spanning tree";

	return pair< list<int>, double >(mst, obj);
}



