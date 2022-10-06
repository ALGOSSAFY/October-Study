#include <iostream>
#include <string.h>
using namespace std;

int flag = 0;
int n;
int arr[101][101];
int visited[101][101];
int dy[2] = { 0,1 };
int dx[2] = { 1,0 };
void dfs(int y,int x) {
	if (flag == 1)
		return;
	if (y == n - 1 && x == n - 1)
	{
		flag = 1;
		return;
	}

	int ny;
	int nx;

	for (int i = 0; i < 2; i++) {
		if (flag == 1)
			return;
		ny = y + arr[y][x]*dy[i];
		nx = x+ arr[y][x]*dx[i];
		if (ny >= n || nx >= n) continue;
		if (visited[ny][nx] == 1) continue;
		visited[ny][nx] = 1;
		dfs(ny, nx);

	}


}

int main() {

	int c;
	cin >> c;

	for (int _ = 0; _ < c; _++) {
	
		cin >> n;
		memset(visited, 0, sizeof(int) * 101 * 101);
		memset(arr, 0, sizeof(int) * 101 * 101);
		flag = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> arr[i][j];
			}
		}
		dfs(0, 0);
		if (flag)
			cout << "YES\n";
		else
			cout << "NO\n";

	}

	return 0;
}
