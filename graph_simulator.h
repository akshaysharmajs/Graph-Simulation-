#include "graph_operations.h"
#include <iostream>

using namespace std;

//The vertices u and v are connected by an edge if u − v = ±1 or u − v = ±(n − 1).
//There is one connected component, every shortest path has length at most n/2, and there is a unique cycle of length n
undirected_graph n_cycle(long int  n)
{
	undirected_graph G(n);
	for(long int  i = 0; i < n; i++)
	{
		for(long int  j = i + 1; j < n; j++)
		{
			if(i - j == 1 || i - j == -1 || i - j == n - 1 || i - j == -(n - 1))
			{
				G.add_edge(i, j);
				G.add_edge(j, i);
			}
		}
	}
	return G;
}

//The vertices are integers from 0 to n − 1, where k ≤ n.(here k is taken as n / 3)
//The vertices u and v are connected by an edge if u − v is evenly divisible by k. 
//There are k components, and each component is a complete graph.
undirected_graph equivalence_mod_k(long int  n)
{
	long int k = n / 3;
	undirected_graph G(n);
	for(long int  i = 0; i < n; i++)
	{
		for(long int  j = i + 1; j < n; j++)
		{	
			if((i - j) % k == 0)
			{
				G.add_edge(i, j);
				G.add_edge(j, i);	
			}
			
		}
	}

	return G;
}


//There are no edges. 
//There are n connected components, no paths, and no cycles.
undirected_graph empty_graph(long int  n)
{
	undirected_graph G(n);
	return G;
}