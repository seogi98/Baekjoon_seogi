#include <bits/stdc++.h>
using namespace std;
#define MAX 401
#define INF 1999999999
int c[MAX][MAX]; // c[i][j]: i에서 j로 가는 간선의 용량
int f[MAX][MAX]; // f[i][j]: i에서 j로 현재 흐르는 유량
vector<int> E[MAX];
int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int N;
	int P;
	cin >> N >> P;
	for (int i = 0; i < P; i++)
	{
		int node1, node2;
		cin >> node1 >> node2;
		c[node1][node2] += 1;
		E[node1].push_back(node2);
		E[node2].push_back(node1);
	}
	int total = 0;
	int s, e;
	s = 1;
	e = 2;
	while (1)
	{
		// 방문 여부
		int prev[MAX];
		fill(prev, prev + MAX, -1);
		queue<int> q;
		q.push(s);
		while (!q.empty() && prev[e] == -1)
		{
			int cur = q.front();
			q.pop();
			for (auto nx : E[cur])
			{
				// c[i][j]-f[i][j] > 0: i에서 j로 유량을 흘릴 여유가 남았는가?
				// prev[next] == -1: next 정점을 아직 방문하지 않았는가?
				if (c[cur][nx] - f[cur][nx] > 0 && prev[nx] == -1)
				{
					q.push(nx);
					prev[nx] = cur;
					// 마지막 노드
					if (nx == e)
						break;
				}
			}
		}
		if (prev[e] == -1)
			break;
		int flow = INF;
		// 경로상에서 가장 허용치가 낮은 곳을 찾음
		for (int i = e; i != s; i = prev[i])
		{
			int pre = prev[i];
			flow = min(flow, c[pre][i]-f[pre][i]);
		}
		// 찾은 flow만큼 해당 경로에 유량을 흘려줌
		for (int i = e; i != s; i = prev[i])
		{
			int pre = prev[i];
			f[pre][i] += flow;
			f[i][pre] -= flow;
		}
		total += flow;
	}
	cout << total;
}