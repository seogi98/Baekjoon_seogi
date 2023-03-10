#include <bits/stdc++.h>
using namespace std;
#define MAX 100010
#define INF 1987654321
vector<int> E[MAX];
// 노드의 깊이(레벨)
int depth[MAX];
// ac[x][y] :: x의 2^y번째 조상을 의미
int ac[MAX][20];

// 최대 높이는 LOG2(MAX)이상 안 높아지므로
int max_level = (int)floor(log2(MAX));


// ac 배열 만드는 과정
void getTree(int cur,int parent)
{
    // 깊이는 부모노드의 깊이 + 1
    depth[cur] = depth[parent]+1;

    // cur의 첫번째 조상은 부모노드
    ac[cur][0] = parent;

    for(int i=1;i<=max_level;i++)
    {
        /* 
            즉, ac[here][i] = ac[tmp][i-1]은
            here의 2^i번째 조상은 tmp의 2^(i-1)번째 조상의 2^(i-1)번째 조상과 같다는 의미
            예를들어 i = 3일때
            here의 8번째 조상은 tmp(here의 4번째 조상)의 4번째 조상과 같다.
            i =  4일때 here의 16번째 조상은 here의 8번째 조상(tmp)의 8번째와 같다.
        */

        // tmp :: here의 2^(i-1)번째 조상
        int tmp = ac[cur][i-1];
        ac[cur][i] = ac[tmp][i-1];
    }
    int len = E[cur].size();
    for(int i=0;i<len;i++)
    {
        int nx = E[cur][i];
        // 양방향으로 연결되어있으므로 부모노드로 가는 방향은 스킵해줘야한다.
        if(nx == parent) continue;
         getTree(nx,cur);
    }

}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    for(int i=0;i<N-1;i++)
    {
        // 그래프 생성
        int node1, node2;
        cin >> node1 >> node2;
        E[node1].push_back(node2);
        E[node2].push_back(node1);
    }
    // tree에 cur = 1 parent = 0 즉, 0은 없는 노드이기떄문에 가정 => 0은 -1로 지정해야한다.
    depth[0] = -1;
    getTree(1,0);
    int M;
    cin >> M;
    while(M--)
    {
        int node1,  node2;
        cin >> node1 >> node2;
        // 만약에 깊이가 같지않으면 깊은 노드를 위로 끌어 올려줘야 한다.
        if(depth[node1] != depth[node2])
        {
            // 만약에 node2이 높이가 깊으면 swap
            if(depth[node1] < depth[node2])
            {
                int tmp = node1;
                node1 = node2;
                node2 = tmp;
            }
                  // b를 올려서 depth를 맞춰준다.
            /* 
                이렇게하면 만약 max_level이 4라면
                2^4 -> 2^3 -> 2^2 -> 2^1 -> 2^0방식으로 찾아갈텐데
                결국 1, 2, 3, 4, 5 ..., 31까지 모두 찾는 방식과 같아진다.
                예를들어, i가 4일때와 1일때 만족했다 치면
                depth[a] <= depth[ac[b][4]]에 의해
                b = ac[b][4];가 되어 b는 b의 16번째 조상을 보고 있을 것이고
                depth[a] <= depth[ac[b][1]]에 의해(현재 b는 처음 b의 16번째 조상인 b로 바뀌었다.)
                b = ac[b][1];이 되어 b는 b의 2번째 조상을 보게 된다.
                즉, b의 16번째 조상의 2번째 조상을 보는 것이니 b의 18번째 조상을 보게 된다.
                (하고자 하는 말은 3번째, 7번째, 11번째 이런 조상들도 모두 볼 수 있다는 의미이다.)
            */
            for(int i=max_level; i>=0;i--)
            {
                if(depth[node2] <= depth[ac[node1][i]])
                {
                    node1 = ac[node1][i];
                }
            }
        }

        int ans = node1;
        // 만약에 node1 , node2가 같지 않은 경우 공통조상이 아니란 뜻이다.
        // 따라서 같아질때 까지 높이를 올려줘야한다.
        if(node1!=node2)
        {
            for(int i=max_level; i>=0;i--)
            {
                if(ac[node2][i] != ac[node1][i])
                {
                    node1 = ac[node1][i];
                    node2 = ac[node2][i];
                }
                ans = ac[node1][i];
            }
        }
        cout << ans << "\n";
    }
}
