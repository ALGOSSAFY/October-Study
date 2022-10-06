
#include <iostream>
#include <string.h>
using namespace std;

int arr[101][101];
int dp[101][101];
int n;


int main() {
	int c;
	cin >> c;

	for (int _ = 0; _ < c; _++) {
		cin >> n;
		memset(dp, 0, sizeof(int) * 101 * 101);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j <= i; j++) {
				cin >> arr[i][j];
			}
		}

		dp[0][0] = arr[0][0];
		
		for (int i = 1; i < n; i++) {
			for (int j = 0; j <= i; j++) {
				if (j == 0) {
					dp[i][0] = arr[i][0] + dp[i - 1][0];
				}
				else if (j == i) {
					dp[i][j] = dp[i - 1][j - 1] + arr[i][j];
				}
				else {
					if(dp[i-1][j-1]>dp[i-1][j])
						dp[i][j] = dp[i - 1][j - 1] + arr[i][j];
					else
						dp[i][j] = dp[i - 1][j ] + arr[i][j];
				}
			}

		}

		int ans = 0;
		for (int i = 0; i < n; i++) {
			if (dp[n - 1][i] > ans)
				ans = dp[n - 1][i];
		}

		cout << ans << endl;

	}
	return 0;
}
