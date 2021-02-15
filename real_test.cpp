#include "graph_make.h"
#include "graph_operations.h"
#include <unordered_set>
#include <iostream>

using namespace std;

void load_graph(string file)
{
	ifstream edges(file);
	string line, node1, node2;
	undirected_graph G(3000000);
	long int u, v;
	unordered_set<long int> uniq;// will help later to not visiting the nodes that are not present in the graph.

	while(getline(edges, line))
	{
		istringstream s(line);
		getline(s, node1, ' ');
		u = stoi(node1);
		getline(s, node2, ' ');
		v = stoi(node2);
		uniq.insert(u);
		uniq.insert(v);
		G.add_edge(u,v);
		G.add_edge(v,u);
	}

	vector<vector<long int > > cc;

	cout<<"Number of Connected Components: ";
	cc = G.connected_components_real(uniq);
	cout<<cc.size()<<endl;
	cout<<endl<<"Size of Each connected component:\n";
	for(long int  i= 0; i < cc.size(); i++)
	{
		cout<<cc[i].size()<<endl;
	}
	return;
}



int main()
{
	criteria_1();
	load_graph("criteria_1_edges.txt");

	//criteria_2();
	//load_graph("criteria_2_edges.txt");

	//criteria_3();
	//load_graph("criteria_3_edges.txt");
}