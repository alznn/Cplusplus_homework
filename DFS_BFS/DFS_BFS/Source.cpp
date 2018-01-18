#include <cstdlib>
#include <iostream>
#include <vector>

// for sort
#include <algorithm>
#include <functional>

// for BFD
#include <queue>
using namespace std;

vector<vector<unsigned>> graph;

vector<unsigned> DFSResult, BFSResult;

vector<bool> hasTrav;

void DFS(unsigned now);
void BFS(unsigned start);

int main(int argc, const char* const argv[])
{
	unsigned s, d;
	while (cin >> s >> d) {
		if (graph.size() <= s) graph.resize(s + 1);
		if (graph.size() <= d) graph.resize(d + 1);
		graph[s].push_back(d);
		graph[d].push_back(s);
	}

	// sort adjList from less to more
	for (size_t i = 0; i < graph.size(); ++i) {
		sort(graph[i].begin(), graph[i].end(), less<unsigned>());
	}

	// init flag
	hasTrav.assign(graph.size(), false);
	DFS(0);
	cout << "DFS spanning tree: ";
	for (size_t i = 0; i < DFSResult.size(); ++i) cout << DFSResult[i] << " ";
	cout << endl;

	hasTrav.assign(graph.size(), false);
	BFS(0);
	cout << "BFS spanning tree: ";
	for (size_t i = 0; i < BFSResult.size(); ++i) cout << BFSResult[i] << " ";
	cout << endl;
	system("pause");
}

void DFS(unsigned now)
{
	if (hasTrav[now]) return;
	hasTrav[now] = true;
	DFSResult.push_back(now);
	for (size_t i = 0; i < graph[now].size(); ++i) {
		int neighbor = graph[now][i];
		if (!hasTrav[neighbor]) DFS(neighbor);
	}
}

void BFS(unsigned start)
{
	queue<unsigned> Q;
	Q.push(start);
	while (!Q.empty()) {
		unsigned now = Q.front();
		if (hasTrav[now]) return;
		hasTrav[now] = true;
		BFSResult.push_back(now);
		for (size_t i = 0; i < graph[now].size(); ++i) {
			int neighbor = graph[now][i];
			if (!hasTrav[neighbor]) Q.push(neighbor);
		}
		Q.pop();
	}
}