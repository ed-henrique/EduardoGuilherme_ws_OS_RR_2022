#include <iostream>
#include <iterator>
#include <thread>
#include <list>
#include <map>

void DFSUtil(int v, std::map<int, std::list<int>> adj, std::map<int, bool> visited) {
    visited[v] = true;
    std::cout << v << " ";

    std::list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i) {
        if (!visited[*i]) {
            DFSUtil(*i, adj, visited);
        }
    }
}

void DFS(std::map<int, std::list<int>> adj, std::map<int, bool> visited) {
	for (auto i : adj) {
		if (visited[i.first] == false) {
			DFSUtil(i.first, adj, visited);
        }
    }
    std::cout << std::endl;
}

class Graph {

	void DFSUtil(int v);

public:
	std::map < int, bool > visited;
	std::map < int, std::list<int> > adj;
	void addEdge(int v, int w);
	void DFS();
};

void Graph::addEdge(int v, int w) {
	adj[v].push_back(w);
}

void Graph::DFSUtil(int v) {
    visited[v] = true;
    std::cout << v << " ";

    std::list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i) {
        if (!visited[*i]) {
            DFSUtil(*i);
        }
    }
}

void Graph::DFS() {
	for (auto i : adj) {
		if (visited[i.first] == false) {
			DFSUtil(i.first);
        }
    }
    std::cout << std::endl;
}

int main() {
    Graph g;

    /*
    TEST 1
    g.addEdge(0, 1);
    g.addEdge(0, 9);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(9, 3);
    g.addEdge(4, 6);
    g.addEdge(6, 19);
    */

    /*
    TEST 2
    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(4, 3);
    g.addEdge(5, 3);
    */

    g.addEdge(1, 0);
    g.addEdge(2, 0);
    g.addEdge(0, 4);
    g.addEdge(2, 1);
    g.addEdge(4, 2);

    std::cout << "Following is Depth First Traversal" << std::endl;
 
    //std::thread t (DFS, g.adj, g.visited);

    //g.DFS();

    //t.join();

    DFS(g.adj, g.visited);

    return 0;
}