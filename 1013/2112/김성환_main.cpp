#include <iostream>
#include <string.h>

using namespace std;

int D, W, K;
int board[13][20];
int min_cnt;

bool isValid() {
	for (int col = 0; col < W; col++) {
		int cnt = 0;
		int now = board[0][col];
		for (int row = 0; row < D; row++) {
			if (cnt >= K)
				break;
			if (board[row][col] == now) {
				cnt++;
			}
			else {
				cnt = 1;
				now = board[row][col];
			}
		}
		if (cnt < K)
			return false;
	}
	return true;
}

void dfs(int level, int cnt) {
	// base case
	if (level == D) {
		if (min_cnt <= cnt)
			return;
		if (isValid())
			min_cnt = min(min_cnt, cnt);
		return;
	}

	// recursive case
	int row_cpy[20] = {};

	dfs(level + 1, cnt);
	memcpy(row_cpy, board[level], W * sizeof(int));
	memset(board[level], 0, W * sizeof(int));
	dfs(level + 1, cnt + 1);
	memset(board[level], -1, W * sizeof(int));
	dfs(level + 1, cnt + 1);
	memcpy(board[level], row_cpy, W * sizeof(int));
}

void solution() {
	dfs(0, 0);
}

void input() {
	min_cnt = 2147483647;
	cin >> D >> W >> K;
	for (int i = 0; i < D; i++) {
		for (int j = 0; j < W; j++) {
			cin >> board[i][j];
			board[i][j] *= -1;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		input();
		solution();
		cout << "#" << tc << " " << min_cnt << "\n";
	}
	return 0;
}

/*
dfs구성
level : 두께 / 깊이
branch : a주입, b주입, 주입안함
*/
