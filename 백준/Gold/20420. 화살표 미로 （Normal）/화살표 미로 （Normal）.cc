#include <bits/stdc++.h>
using namespace std;
#define INF (2 << 32) - 1
#define MAX 51
#define MMAX 150
map<char, int> D = {{'R', 0}, {'D', 1}, {'L', 2}, {'U', 3}};
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int R, C, K;
char mp[MAX][MAX];
// [y][x][r][l]
bool vst[MAX][MAX][MMAX][MMAX];
struct P
{
    int L;
    int R;
    int y;
    int x;
};
void moveT(int y, int x, int r, int l, queue<P> &q, int curD)
{
    int nx = x + dx[curD];
    int ny = y + dy[curD];
    if(r < 0 || l < 0) return;
    if (nx < 0 || nx >= C || ny < 0 || ny >= R)
        return;
    if (vst[ny][nx][r][l])
        return;
    vst[ny][nx][r][l] = true;
    q.push({l, r, ny, nx});
}
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> R >> C >> K;
    queue<P> q;
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            cin >> mp[i][j];
        }
    }
    q.push({K,K,0,0});
    vst[0][0][K][K] = true;
    string ans = "No";
    while (!q.empty())
    {
        P cur = q.front();
        q.pop();
        if (cur.y == R - 1 && cur.x == C - 1)
            ans = "Yes";
        int curD = D[mp[cur.y][cur.x]];
        // 그냥 움직일 경우
        moveT(cur.y, cur.x, cur.R, cur.L, q, curD);

            // 오른쪽 주문서 1개 쓸 경우
            moveT(cur.y, cur.x, cur.R - 1, cur.L, q, (curD + 1) % 4);

            // 오른쪽 주문서 2개 쓸 경우
            moveT(cur.y, cur.x, cur.R - 2, cur.L, q, (curD + 2) % 4);

            // 오른쪽 주문서 3개 쓸 경우
            moveT(cur.y, cur.x, cur.R - 3, cur.L, q, (curD + 3) % 4);

            // 왼쪽 주문서 1개 쓸 경우
            moveT(cur.y, cur.x, cur.R, cur.L - 1, q, (curD + 3) % 4);

            // 왼쪽 주문서 2개 쓸 경우
            moveT(cur.y, cur.x, cur.R, cur.L - 2, q, (curD + 2) % 4);

             // 왼쪽 주문서 3개 쓸 경우
            moveT(cur.y, cur.x, cur.R, cur.L - 3, q, (curD + 1) % 4);
    }
    cout << ans;
}