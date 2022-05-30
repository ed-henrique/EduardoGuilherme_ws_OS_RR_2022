#include <iostream>
#include <iterator>
#include <list>
#include <map>
using namespace std;

class Graph {

	void DFSUtil(int v);

public:
	map < int, bool > visited;
	map < int, list<int> > adj;
	void addEdge(int v, int w);
	void DFS();
    void printGraph(int v);
};

void Graph::addEdge(int v, int w) {
	adj[v].push_back(w);
}

void Graph::DFSUtil(int v) {
    visited[v] = true;
    cout << v << " ";

    list<int>::iterator i;
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
}

void Graph::printGraph(int v) {
    for (int i = 0; i < v; ++i) {
        if (!adj[i].empty()) {
            cout << "Adjacency list of vertex " << i << "\n    >> head ";
            for (auto x : adj[i])
                cout << " -> " << x;
            printf("\n");

        }
    }
}

int main() {
    Graph g;
    g.addEdge(0, 1);
    g.addEdge(0, 9);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(9, 3);
    g.addEdge(4, 6);
    g.addEdge(6, 19);

    cout << "Following is Depth First Traversal" << endl;
    g.printGraph(19);
    g.DFS();
    cout << endl;

    return 0;
}