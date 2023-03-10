#include <bits/stdc++.h>
using namespace std;
#define MAX 51
//위치를 저장해놨다가 한꺼번에 퍼트린다.
int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};
int R,C,T;
struct Dirty{
	int Y;
	int X;
	int size;
};
vector<vector<int>> spread(vector<vector<int>> mp)
{
	vector<vector<int>> ans(MAX,vector<int>(MAX,0));
	//전체 탐색 해서 queue에 넣어놓는다.
	queue<Dirty> q;
	for(int i=0;i<R;i++)
	{
		for(int j=0;j<C;j++)
		{
			if(mp[i][j])
			{
				q.push({i,j,mp[i][j]});
			}
		}
	}
	//임시로 저장해 놓았다가 한거번에 더한다.
	queue<Dirty> sumQ;
	while(!q.empty())
	{
		int y = q.front().Y;
		int x = q.front().X;
		int size = q.front().size;
		q.pop();
		//확산할 수 있는 방향의 수
		int dirSize = 0;
		for(int j=0;j<4;j++)
		{
			int nx = x+dx[j];
			int ny = y+dy[j];
			if(nx < 0 || nx >=C || ny <0 || ny >=R) continue;
			if(mp[ny][nx] == -1) continue;
			dirSize++;
			//확산
			sumQ.push({ny,nx,size/5});
		}
		sumQ.push({y,x,size-(size/5)*dirSize});
	}
	//한거번에 더함
	while(!sumQ.empty())
	{
		int y = sumQ.front().Y;
		int x = sumQ.front().X;
		int dty = sumQ.front().size;
		ans[y][x] += dty;
		sumQ.pop();
	}
	return ans;	
}
void seeM(vector<vector<int>> mp)
{
	cout << "SeeMap\n";
	for(int i=0;i<R;i++)
	{
		for(int j=0;j<C;j++)
		{
			cout << mp[i][j] << " ";
		}
		cout << "\n";
	}
}
vector<vector<int>> refresh(vector<vector<int>> mp,pair<int,int> upAirFresh , pair<int,int> downAirFresh)
{
	vector<vector<int>> ans = mp;
	//다음 이동할 방향 저장해놓음
	queue<Dirty> q;

	//updfresh
	//오른쪽 방향
	for(int i=1;i<C-1;i++)
	{
		int Y1 = upAirFresh.first;
		q.push({Y1,i+1,mp[Y1][i]});
		ans[Y1][i]=0;
	}
	// 위쪽 방향
	for(int i=upAirFresh.first;i>=1;i--)
	{
		int X1 = C-1;
		q.push({i-1,X1,mp[i][X1]});
		ans[i][X1]=0;
	}
	// 왼쪽 방향
	for(int i=C-1;i>0;i--)
	{
		int Y1 = 0;
		q.push({Y1,i-1,mp[Y1][i]});
		ans[Y1][i]=0;
	}
	// 아래쪽 방향
	for(int i=0;i<upAirFresh.first;i++)
	{
		int X1 = 0;
		q.push({i+1,X1,mp[i][X1]});
		ans[i][X1]=0;
	}
	//downdfresh
	//오른쪽 방향
	for(int i=1;i<C-1;i++)
	{
		int Y1 = downAirFresh.first;
		q.push({Y1,i+1,mp[Y1][i]});
		ans[Y1][i] =0;
	}
	// 아래쪽 방향
	for(int i=downAirFresh.first;i<R-1;i++)
	{
		int X1 = C-1;
		//아래로
		q.push({i+1,X1,mp[i][X1]});
		ans[i][X1]=0;
	
	}
	// 왼쪽 방향
	for(int i=C-1;i>0;i--)
	{
		int Y1 = R-1;
		q.push({Y1,i-1,mp[Y1][i]});
		ans[Y1][i]=0;
	}
	// 위쪽 방향
	for(int i=R-1;i>downAirFresh.first;i--)
	{
		int X1 = 0;
		q.push({i-1,X1,mp[i][X1]});
		ans[i][X1]=0;
	}
	while(!q.empty())
	{
		int y = q.front().Y;
		int x = q.front().X;
		int dty = q.front().size;
		q.pop();
		if(y == upAirFresh.first && x == upAirFresh.second) continue;
		if(y == downAirFresh.first && x == downAirFresh.second) continue;
		ans[y][x] = dty;
	}
	return ans;
}
int countDirty(vector<vector<int>> mp)
{
	int sum=0;
	for(int i=0;i<R;i++)
	{
		for(int j=0;j<C;j++)
		{
			if(mp[i][j] == -1) continue;
			sum+=mp[i][j];
		}
	}
	return sum;
}
int main(void)
{
	// ios::sync_with_stdio(false);
	// cin.tie(NULL);
	cin >> R >> C >> T;
	//공기청정기
	pair<int,int> upAirFresh = {-1,-1};
	pair<int,int> downAirFresh = {-1,-1};
	vector<vector<int>> mp(MAX,vector<int>(MAX,0));
	for(int i=0;i<R;i++)
	{
		for(int j=0;j<C;j++)
		{
			cin >> mp[i][j];
			if(mp[i][j] == -1) 
			{
				if(upAirFresh.first == -1)
				{
					upAirFresh = {i,j};
					continue;
				}
				downAirFresh = {i,j};
			}
		}
	}
	while(T--)
	{
	mp  = spread(mp);
	//seeM(mp);
	mp = refresh(mp,upAirFresh,downAirFresh);
	//seeM(mp);
	}
	cout << countDirty(mp);
}