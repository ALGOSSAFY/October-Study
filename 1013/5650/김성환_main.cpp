#include <iostream>
#include <string.h>
 
using namespace std;
 
struct Node {
    int y;
    int x;
};
 
int N;
int board[100][100];
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };
int worm_hole_DAT[11];
Node worm_hole[11][2];
int bump_max;
 
int bounce[5][4] = {
    {1, 3, 0, 2},
    {3, 0, 1, 2},
    {2, 0, 3, 1},
    {1, 2, 3, 0},
    {1, 0, 3, 2},
};
 
 
void dfs(Node start, Node now, int dir, int bump) {
    //cout << now.y << " " << now.x << "\n";
 
    while (true) {
        // 도착하자마자 움직여서 다음 위치 확정하기
        int ny = now.y + dy[dir];
        int nx = now.x + dx[dir];
 
        if (!(0 <= ny && ny < N && 0 <= nx && nx < N)) {
            ny = now.y;
            nx = now.x;
            dir = bounce[4][dir];
            bump++;
        }
     
        // 다음 위치 확정된 상태
        int type = board[ny][nx];

        if (type == -1) {
            bump_max = max(bump_max, bump);
            return;
        }
        if (ny == start.y && nx == start.x) {
            bump_max = max(bump_max, bump);
            return;
        }
        if (1 <= type && type <= 5) {
            dir = bounce[type - 1][dir];
            bump++;
        }
        if (6 <= type && type <= 10) {
            Node next = worm_hole[type][0];
            if (next.y == ny && next.x == nx) {
                next = worm_hole[type][1];
            }
            ny = next.y;
            nx = next.x;
        }
        now.y = ny;
        now.x = nx;
    }
}
 
int solution() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] != 0)
                continue;
            for (int dir = 0; dir < 4; dir++) {
                //cout << "start " << dir << "\n";
                dfs({ i, j }, { i, j }, dir, 0);
            }
        }
    }
 
    return bump_max;
}
 
void input() {
    memset(worm_hole_DAT, 0, sizeof(worm_hole_DAT));
    memset(worm_hole, 0, sizeof(worm_hole));
    bump_max = -1;
 
    cin >> N;
 
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int type;
            cin >> type;
            board[i][j] = type;
            if (6 <= type && type <= 10) {
                int idx = worm_hole_DAT[type];
                worm_hole[type][idx] = { i, j };
                worm_hole_DAT[type]++;
            }
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
        cout << "#" << tc << " " << solution() << "\n";
    }
 
    return 0;
}
