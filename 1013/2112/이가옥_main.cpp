#include <iostream>
#include <vector>
using namespace std;

int MAP[14][21];
int MAP_copy[14][21];

vector<int> path;
vector<int> color_path;

int d, w, k;
int minCnt = 14;

void fill_MAP(int row, int type, bool flag) {

	// 약품 넣어보기
	if (flag == true) {
		for (int i = 0; i < w; i++) {
			MAP_copy[row][i] = type;
		}
	}

	// 백트래킹
	else if (flag == false) {
		for (int i = 0; i < w; i++) {
			MAP_copy[row][i] = MAP[row][i];
		}
	}

}

bool check() {

	for (int i = 0; i < w; i++) {

		int A_cnt = 0;
		int B_cnt = 0;
		int flag = 0;

		for (int j = 0; j < d; j++) {
			if (MAP_copy[j][i] == 0) {
				A_cnt += 1;
				B_cnt = 0;
			}

			if (MAP_copy[j][i] == 1) {
				B_cnt += 1;
				A_cnt = 0;
			}

			if (A_cnt == k) {
				flag = 1;
				break;
			}
			if (B_cnt == k) {
				flag = 1;
				break;
			}
		}
		if (flag == 0) return false;
		
	}
	
	return true;

}


void dfs(int idx, int cnt) { // idx: 행

	if (minCnt <= cnt) return;
	
	if (idx >= d) {
		// 성능검사
		int flag = check();
		if (flag == 1) {
			if (minCnt > cnt) minCnt = cnt;
			return;
		}

	}

	dfs(idx + 1, cnt);
	for (int j = 0; j < 2; j++) {
		
		fill_MAP(idx, j, true);
		dfs(idx + 1, cnt + 1);
		fill_MAP(idx, j, false);

	}

}

int main() {

	int t;
	cin >> t;

	for (int testcase = 1; testcase <= t; testcase++) {

		cin >> d >> w >> k; // 두께: d, 가로크기: w, 합격기준: k

		for (int i = 0; i < d; i++) {
			for (int j = 0; j < w; j++) {
				cin >> MAP[i][j];
				MAP_copy[i][j]=MAP[i][j];
			}
		}

		// A: 0, B: 1
		int flag = 0;
		if (check()==true || k==1) {
			flag = 1;
		}

		if (flag == 1) {
			cout <<"#"<<testcase<<" "<< 0 << "\n";
		}
		else if(flag==0){
			dfs(0, 0);
			cout << "#" << testcase << " " << minCnt << "\n";
		}

		minCnt = 14;
		
		
	}

	return 0;
}
