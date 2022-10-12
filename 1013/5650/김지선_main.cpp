#include <iostream>
#include <vector>
using namespace std;

struct Cell {
    int value;
    int dir;
};
vector<Cell> cells[100][100];
vector<Cell> temp_cells[100][100];
int ydir[] = { 0,-1,1,0,0 };
int xdir[] = { 0,0,0,-1,1 };
int N, M, K;

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> N >> M >> K;
        // cell �ʱ�ȭ
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cells[i][j].clear();
            }
        }
        //�̻��� ���� �ޱ�
        for (int k = 0; k < K; k++) {
            int y, x, v, d;
            cin >> y >> x >> v >> d;
            cells[y][x].push_back({ v,d });
        }

        //m�� ���ֱ�
        for (int m = 0; m < M; m++) {
            //temp_cells �ʱ�ȭ
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    temp_cells[i][j].clear();
                }
            }

            //�ϴ� �̵����� ������
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (cells[i][j].size() > 0) {
                        int ny = i + ydir[cells[i][j][0].dir];
                        int nx = j + xdir[cells[i][j][0].dir];
                        temp_cells[ny][nx].push_back({ cells[i][j][0].value , cells[i][j][0].dir });
                        cells[i][j].clear();
                    }
                }
            }
            // 1. �����ڸ� ���̸� ����ٲ��ֱ� + �̻��� �� ������ ���̱�
            // 2. �� ���Ϳ� ������ �ִٸ� ���� ū ���� �ִ� �������� �ٲٱ�
            //    + �� �����ֱ�
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (i >= 1 && i <= N - 2 && j >= 1 && j <= N - 2) {
                        if (temp_cells[i][j].size() > 1) {
                            int max_value = -1;
                            int max_dir;
                            int sum = 0;
                            for (int n = 0; n < temp_cells[i][j].size(); n++) {
                                if (max_value < temp_cells[i][j][n].value) {
                                    max_value = temp_cells[i][j][n].value;
                                    max_dir = temp_cells[i][j][n].dir;
                                }
                                sum += temp_cells[i][j][n].value;
                            }
                            cells[i][j].push_back({ sum, max_dir });
                        }
                        else if (temp_cells[i][j].size() == 1) {
                            cells[i][j].push_back({ temp_cells[i][j][0].value, temp_cells[i][j][0].dir });
                        }
                    }
                    else {
                        if (temp_cells[i][j].size() == 1) {
                            temp_cells[i][j][0].value /= 2;
                            if (temp_cells[i][j][0].dir % 2 == 1) {
                                temp_cells[i][j][0].dir++;
                            }
                            else {
                                temp_cells[i][j][0].dir--;
                            }
                            cells[i][j].push_back({ temp_cells[i][j][0].value, temp_cells[i][j][0].dir });
                        }
                    }
                }
            }
        }
        // �䳻��
        int ans = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (cells[i][j].size() > 0) {
                    ans += cells[i][j][0].value;
                }
            }
        }
        cout << "#" << t << " " << ans << endl;
    }
}