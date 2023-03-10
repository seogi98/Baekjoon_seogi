#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main(void)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--)
    {
        int dp[2][100001];
        int arr[2][100001];
        int N;
        cin >> N;
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cin >> arr[i][j];
            }
        }
        dp[0][0] = arr[0][0];
        dp[1][0] = arr[1][0];
        dp[0][1] = arr[0][1] + arr[1][0];
        dp[1][1] = arr[1][1] + arr[0][0];
        for (int i = 2; i < N; i++)
        {
            dp[0][i] = arr[0][i] + max(dp[1][i - 1], dp[1][i - 2]);
            dp[1][i] = arr[1][i] + max(dp[0][i - 1], dp[0][i - 2]);
        }
        cout << max(dp[0][N-1],dp[1][N-1])<<"\n";
    }
}