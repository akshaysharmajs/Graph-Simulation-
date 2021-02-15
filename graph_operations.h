#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <unordered_set>
#include <algorithm>
#include <stack>
using namespace std;

//class for defining the undirected_graph, contains adjacency list for the graph
class undirected_graph
{
public:
	long int  V;

	vector<vector<long int> > adjacent;//adjacency list

	long int  cycle_start;//stores start of a cycle
	long int  cycle_end;//stores end of a cycle

	undirected_graph(long int  Vertices) : adjacent(Vertices)
	{
		V = Vertices;
		
	}

	void add_edge(long int  u, long int  v)
	{
		adjacent[u].push_back(v);
		adjacent[v].push_back(u);
	}

	//function to return the list for connected components in netfilx graph
	vector<vector<long int > > connected_components_real(unordered_set<long int> &uniq)
	{	 
		vector <vector<long int > > cc;
		vector<int> marked (V, 0);//keeps track of all visited nodes
		for(auto node : uniq)
		{
			if(!marked[node])
			{
				vector<long int > curr_list;
				dfs_cc(node, marked, curr_list);
				cc.push_back(curr_list);
			}
		}	
		return cc;
	}


	//function to return the list for connected components in graph
	vector<vector<long int > > connected_components()
	{	 
		vector <vector<long int > > cc;
		vector<int> marked (V, 0);//keeps track of all visited nodes
		for(long int  node = 0; node < V; node++)
		{
			if(!marked[node])//
			{
				vector<long int > curr_list;
				dfs_cc(node, marked, curr_list);
				cc.push_back(curr_list);
			}
		}	
		return cc;
	}

	//depth first search utility for connected_components()
	void dfs_cc(long int  curr_node, vector<int>& marked, vector<long int >& curr_list)
	{
		

		stack<long int> s;
		s.push(curr_node);

		while(!s.empty())
		{
			long int n = s.top();
			s.pop();
			if(!marked[n])
			{
				marked[n] = 1;
				curr_list.push_back(n);
			}

			vector<long int >::iterator itr;
			for (itr = adjacent[n].begin(); itr != adjacent[n].end(); ++itr)
    			if (!marked[*itr])
        			s.push(*itr);
		}

		
        return;

	}


	//detect cycle in graph using depth first search
	vector<long int > one_cycle()
	{
		vector<bool> marked (V, false);//keeps track of all visited nodes

		vector<long int > parents (V, -1);//keeps track of parent of every node we visit

		cycle_start = -1;
		for(long int  node = 0; node < V; node++)
		{
			if(!marked[node] && dfs_one_cycle(node, parents[node], marked, parents))
				break;
		}

		if(cycle_start == -1)
			return {};
		else
		{
			vector<long int > detected_cycle;

			//backtracking for getting the path of cycle 
			detected_cycle.push_back(cycle_start);
			
			for(long int  node = cycle_end; node != cycle_start && node != -1; node = parents[node])
				detected_cycle.push_back(node);

			detected_cycle.push_back(cycle_start);//first and last node is same for cycle
			reverse(detected_cycle.begin(), detected_cycle.end());//cycle was stored in bottom up
			return detected_cycle;
		}
	}

	//depth first search utility for one_cycle()
	bool dfs_one_cycle(long int  curr_node, long int  parent_node, vector<bool>& marked, vector<long int >& parents)
	{

		marked[curr_node] = true;

		vector<long int >::iterator itr;
		for (itr = adjacent[curr_node].begin(); itr != adjacent[curr_node].end(); ++itr)
		{
			if(*itr == parent_node)
				continue;

			if(marked[*itr])
			{	
				cycle_end = curr_node;
				cycle_start = *itr;
				return true;
			}
			parents[*itr] = curr_node;
			if(dfs_one_cycle(*itr, parents[*itr], marked, parents))
			{
				return true;
			}
		}

		return false;
	}

	//return the shortest path of each vertex to the given source vertex
	vector<vector<long int > > shortest_paths(long int  source)
	{
		priority_queue <pair<long int , long int > , vector<pair<long int , long int > >, greater<pair<long int ,long int > > > p;

		vector<long int > dist (V, INT_MAX);

		vector<long int > parent(V, -1);//stores the parent of each node to get the nodes of shortest path

		parent[source] = source;

		p.push({0, source});// intializing source node distance to itself which is zero

		dist[source] = 0;

		while(!p.empty())
		{
			long int  curr_node = p.top().second;
			p.pop();

			vector<long int >::iterator itr;
    		for (itr = adjacent[curr_node].begin(); itr != adjacent[curr_node].end(); ++itr)
    		{
    			if(dist[*itr] > dist[curr_node] + 1)//considering all edge weights to be "1"
    			{
    				dist[*itr] = dist[curr_node] + 1;
    				parent[*itr] = curr_node;
    				p.push({dist[*itr], *itr});
    			}
    		}

		}

		 vector <vector<long int > > sp(V, vector<long int >());
		for(long int  node = 0; node < V; node++)
		{
			find_path(sp[node], node, parent);
		}

		return sp;

	}

	//utility for shortest_paths() for following up the path from vertex to source
	void find_path(vector<long int >& v, long int  node, vector<long int >& parent)
	{
		if(parent[node] == -1)
			return;
		else if(parent[node] == node)
		{
			v.push_back(node);
			return;
		}

		v.push_back(node);

		find_path(v, parent[node], parent);
		return;
	}
};

