#include<bits/stdc++.h>
using namespace std;

#define INF 9999

int v, cost[100][100], src, dist[100];
bool visited[100] = {0};
int parent[100];

void init() {
	for (int i = 0; i < v; i++){
		parent[i] = i;
		dist[i] = INF;
	}
	dist[src] = 0; 
}

int getNearest() {
	int min_value = INF;
	int min_node = 0;
	for (int i = 0; i < v; i++) {
		if (!visited[i] && dist[i] < min_value) {
			min_value = dist[i];
			min_node = i;
		}
	}
	return min_node;
}
void dijkstra()
{
	for (int i = 0; i < v; i++) {
		int nearest = getNearest();	
		visited[nearest] = true;
		
		for (int adj = 0; adj < v; adj++) {
			if(cost[nearest][adj] != INF && dist[adj] > dist[nearest]+cost[nearest][adj]) {
				dist[adj] = dist[nearest] + cost[nearest][adj];
				parent[adj] = nearest;
			}
		}
	}
}

void display() {
	cout << "\nNode\t\t\tCost\t\t\tPath\n";
	for (int i = 0; i < v; i++) 
	{
		cout << i << "\t\t\t" << dist[i] << "\t\t\t" << " ";
		cout << i << " ";
		int parent_node = parent[i];
		while (parent_node != src) {
			cout << " <- " << parent_node << " ";
			parent_node = parent[parent_node]; 
		}
		cout << "\n";
	}
}

int main()
{
	cout << "\nEnter number of nodes: ";
	cin >> v;
	cout << "\nEnter Cost Matrix: \n";
	for (int i = 0; i < v; i++)
 	{	
 		for (int j = 0; j < v; j++) {
 			cin >> cost[i][j];
 		}	
 	}
 	cout << "\nEnter Source: ";
 	cin >> src;
 	init();
 	dijkstra();
 	display();
 }
