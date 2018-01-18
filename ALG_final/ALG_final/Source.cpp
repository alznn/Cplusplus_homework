#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>
#include <vector>
#include <functional>
#include <time.h>
using namespace std;

struct mydata {
	// num is edge id
	int num, value;
	int start;
	int destination;
	bool isempty;
	bool operator>(const mydata &n) const {
		return this->value > n.value; // this Àu¥ýÅv¤j
	}
};
struct pdata {
	int start, dest;
	int cost;
	vector<int> sp;
};
struct dijdata {
	int id;
	int value;
	int parent;
	dijdata() :id(-1), value(1e9), parent(-1) {}
};

bool dijdataCmp(const dijdata* const lhs, const dijdata const *rhs) {
	return lhs->value > rhs->value;
}

#define MAX_VER 600
#define INF 99999

vector <vector<mydata>> graph;
vector <pdata> assign_route;
vector <dijdata*> PQ;					//num為路徑編號 , value為權重
vector <vector<dijdata>> dist;         //DP存路徑，num為parent , value為distance , isempty為 isvisit
vector <vector<pdata>> result;		//num紀錄路徑點   value紀錄目前總權重
clock_t t1, t2;
string str;

void init(int size);
void parser();
void DrawGraph(int o_graph[]);
void Dijkstra();
void trace(pdata path, int index);
void print();

int main() {
	t1 = clock();
	parser();
	Dijkstra();
	for (int r = 0; r < assign_route.size(); r++)
		trace(assign_route[r], r);
	system("pause");
}


void parser() {
	/*--------------------------------------------( V , E )parser-------------------------------------------*/
	ifstream input("topo2.csv");
	while (!input.eof()) {
		getline(input, str);
		stringstream ss(str);
		string stt;
		//0 0	13	15
		//		cout << str << endl;
		int set[4];
		int i = 0;
		for (int i = 0; i < 4; i++)
			while (getline(ss, stt, ','))
				set[i++] = atoi(stt.c_str());
	
		DrawGraph(set);
	}
	input.close();
	cout << "總點數: " << graph.size() << endl;

	/*--------------------------------------------指定路徑parser-------------------------------------------*/
	ifstream in("demand2.csv");
	pdata sppath;
	string line;
	while (!in.eof()) {
		getline(in, str);
		string s;
		line = static_cast<string>(str);
		s = line.substr(0, line.find(","));
		sppath.start = atoi(s.c_str());
		line.erase(0, s.size() + 1);
		s = line.substr(0, line.find(","));
		sppath.dest = atoi(s.c_str());
		line.erase(0, s.size() + 1);
		while (!line.empty())
		{
			s = line.substr(0, line.find("|"));
			sppath.sp.push_back(atoi(s.c_str()));
			line.erase(0, s.size() + 1);
		}

		assign_route.push_back(sppath);
	}
	in.close();
	cout << "指定路徑數: " << assign_route.size() << endl;

	init(graph.size());
}

void DrawGraph(int o_graph[]) {
	//LinkID,SourceID,DestinationID,Cost 
	if (graph.size() <= o_graph[1])
		graph.resize(o_graph[1] + 1);
	mydata info;
	info.start = o_graph[1];
	info.destination = o_graph[2];
	info.num = o_graph[0];
	info.value = o_graph[3];
	info.isempty = false;
	if (graph[o_graph[1]].empty()) {
		graph[o_graph[1]].push_back(info);
		return;
	}
	for (int index = 0; index < graph[o_graph[1]].size(); index++) {
		if (graph[o_graph[1]][index].destination == info.destination) {		//點與點間只有保留一條最短路徑
			if (graph[o_graph[1]][index].value > info.value) {
				graph[o_graph[1]][index].value = info.value;
				graph[o_graph[1]][index].num = info.num;
			}
			else return;
		}
		else {
			graph[o_graph[1]].push_back(info);
			return;
		}
	}
	return;
}
//先初始化
void init(int size) {
	/*
	vector<mydata> assign_route;	//num為點編號，isempty為是否拜訪過
	priority_queue<mydata> PQ;//num為路徑編號 , value為權重
	*/
	dist.assign(size, vector<dijdata>(size));
	result.resize(assign_route.size(), vector<pdata>(size));
	for (int a = 0; a < size; a++) {
		dist[a][a].value = 0;
		for (int b = 0; b < size; b++) {
			dist[a][b].id = b;
		}
	}
}

// num is edge id
mydata find(int a, int b) {
	for (int i = 0; i < graph[a].size(); ++i) {
		if (graph[a][i].destination == b) {
			return graph[a][i];
		}
	}
	return mydata{ -1 };
}

// dist  num為edge id , value為cost , isempty為 isvisit  
// dist[ start ][ dest ]
void Dijkstra() {
	pair<int, int> val;

	// 以每個點當起點然後dijkstra
	for (int s = 0; s < graph.size(); s++) {
		// 將所有原點相鄰的邊push進priority_queue
		for (int i = 0; i < dist[s].size(); ++i) {
			PQ.push_back(&dist[s][i]);
		}
		make_heap(PQ.begin(), PQ.end(), dijdataCmp);

		while (!PQ.empty()) {
			dijdata *u = PQ.front(); pop_heap(PQ.begin(), PQ.end(), dijdataCmp); PQ.pop_back();
			for (mydata v : graph[u->id]) {
				int alt = dist[s][u->id].value + v.value;
				if (alt < dist[s][v.destination].value) {
					dist[s][v.destination].value = alt;
					dist[s][v.destination].parent = u->id;
					make_heap(PQ.begin(), PQ.end(), dijdataCmp);
				}
			}
		}
	}
/*	for (int i = 0; i < graph.size(); ++i) {
		for (int j = 0; j < graph.size(); ++j) {
			cout << dist[i][j].value << " ";
		}
		cout << endl;
	}
*/
}
void trace(pdata path , int index) {
	sort(path.sp.begin(), path.sp.end());
	cout << "指定路徑\n"
		<<"起始點: "<< path.start<<"\n"<<"終點: "<< path.dest << endl;
	cout << "指定必經節點:\n";
	for(int i = 0 ; i< path.sp.size() ; i++)
		cout << path.sp[i] << " ";
	cout << endl<<"=======================================可能路徑=======================================\n";

	do {
		pdata froute;
		for (int i = 0; i< path.sp.size(); i++)
			cout << path.sp[i] << " ";
		cout << endl;
		int start = path.start;
		int pos = 0;
		int cost = 0;
		bool flag = false;
		if (dist[start][path.sp[pos]].value == 1e9) break;
		else {
			cost += dist[start][path.sp[pos]].value;
			froute.sp.push_back(path.sp[pos]);
			start = path.sp[pos];//起點到指定節點1走完，指定節點1繼續往下走
			
			for (int i = 1; i < path.sp.size(); i++) {
				if (dist[start][path.sp[i]].value == 1e9) {
					flag = true;
					break;
				}
				else {
					cost += dist[start][path.sp[i]].value;
					froute.sp.push_back(path.sp[i]);
					start = path.sp[i];
				}
			}
			if (flag) continue;
			if (dist[start][path.dest].value == 1e9) continue;
			else {
				froute.start = path.start;
				froute.dest = path.dest;
				cost += dist[start][path.dest].value;
				froute.cost = cost;
				result[index].push_back(froute);
				cout << endl << "=======================================可能路徑=======================================\n";
			}
		}
	} while (next_permutation(path.sp.begin(), path.sp.end()));

	// 對每一個result set依照cost由大而小做排序
	for_each(result.begin(), result.end(), [](vector<pdata> &res) {
		sort(res.begin(), res.end(), [](const pdata& a, const pdata& b) {
			return a.cost > b.cost;
		});
	});

	while (result[index][result[index].size() - 1].cost == 0)
		result[index].resize(result[index].size()-1);

	// 對每一個result set依照cost由小而大做排序
	for_each(result.begin(), result.end(), [](vector<pdata> &res) {
		sort(res.begin(), res.end(), [](const pdata& a, const pdata& b) {
			return a.cost < b.cost;
		});
	});
	t2 = clock();
	print();
}

void print() {

	cout << "\n最短路徑為：\n\n";
	for (int i = 0; i < result.size(); ++i) {
		cout << result[i][0].start << " | ";
		for (int j = 0; j < result[i][0].sp.size(); ++j) {
			cout << result[i][0].sp[j] << " | ";
		}
		cout<< result[i][0].dest << " | ";
		cout << endl;
	}
	cout << endl;
	cout<<"本次執行時間為： "<<(t2 - t1) / (double)(CLOCKS_PER_SEC)<<endl;
}
