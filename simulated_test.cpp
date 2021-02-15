#include <iostream>
#include "graph_simulator.h"

using namespace std;

void display(undirected_graph& G)
{
	vector<vector<long int > > cc;

	cout<<"Connected Components:\n";
	cc = G.connected_components();

	for(long int  i= 0; i < cc.size(); i++)
	{
		for(long int  j = 0; j < cc[i].size(); j++)
		{
			cout<<cc[i][j]<<" ";
		}
		cout<<endl;
	}


	vector<long int > cycle;
	cycle = G.one_cycle();
	cout<<"\nDetected Cycle: ";
	if(cycle.size())
		cout<<"Yes"<<endl;
	else cout<<"No"<<endl;
	for(auto i : cycle)
		cout<<i<<" ";
	cout<<endl;



	cout<<"\nshortest_paths from each vertex to source(0)"<<endl;
	vector<vector<long int > > sp;
	sp = G.shortest_paths(0);
	for(long int  i = 0; i < sp.size(); i++)
	{	
		if(sp[i].size())
		{
			for(auto j : sp[i])
			cout<<j<<" ";
			cout<<endl;	
		}
		
	}
}


int  main()
{
	long int  n;
	cin>>n;

	undirected_graph G1 = n_cycle(n);
	cout<<"\n\nTYPE OF GRAPH = n_cycle\n";
	display(G1);

	undirected_graph G2 = equivalence_mod_k(n);
	cout<<"\n\nTYPE OF GRAPH = equivalence_mod_k\n";
	display(G2);

	undirected_graph G3 = empty_graph(n);
	cout<<"\n\nTYPE OF GRAPH = empty_graph\n";
	display(G3);
	
	return 0;
}