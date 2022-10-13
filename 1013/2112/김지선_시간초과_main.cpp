#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

int D, W, K;
int arr[13][20] = { 0, };
int temp_arr[13][20] = { 0, };
int visited[13] = { 0, };
int flag = 0;

void dfs(int now, int final) {
    if (flag == 1) {
        return;
    }
    if (now == final) {
        int cnt = 0;
        for (int i = 0; i < W; i++) {
            for (int j = 0; j <= D - K; j++) {
                int flag2 = 0;
                for (int m = 1; m < K; m++) {
                    if (temp_arr[j + m][i] != temp_arr[j][i]) {
                        flag2 = 1;
                        break;
                    }
                }
                if (flag2 == 0) {
                    cnt++;
                    break;
                }
            }
        }
        if (cnt == W) {
            flag = 1;
        }
        return;
    }

    for (int i = 0; i < D; i++) {
        if (visited[i] == 1) {
            continue;
        }
        visited[i] = 1;
        for (int j = 0; j < 2; j++) {\
            for (int m = 0; m < W; m++) {
                temp_arr[i][m] = j;
            }
            dfs(now + 1, final);
        }
        visited[i] = 0;
        for (int m = 0; m < W; m++) {
            temp_arr[i][m] = arr[i][m];
        }
    }
    return;
}

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        flag = 0;
        cin >> D >> W >> K;
        int ans = 0;
        for (int d = 0; d < D; d++) {
            for (int w = 0; w < W; w++) {
                cin >> arr[d][w];
                temp_arr[d][w] = arr[d][w];
            }
        }
        for (int i = 0; i <= D; i++) {
            dfs(0, i);
            if (flag == 1) {
                ans = i;
                break;
            }
        }
        cout << "#" << t << " " << ans << endl;
    }
}
