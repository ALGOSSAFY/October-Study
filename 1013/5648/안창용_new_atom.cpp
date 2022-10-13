#include <iostream>
#include <vector>
#include <cstring>
#define MAX 4001


using namespace std;

struct Atom_Info {
	int x, y, dir, Energy;
};

struct ANB {
	int A, B;
};

int N, Total_Energy;

vector<Atom_Info> Atom;

vector <ANB> timeflo[4001];
int dat[4001];
int dx[] = { 0, 0, -1, 1 };
int dy[] = { 1, -1, 0, 0 };

int TC, T;
int x, y, dir, k;
int i, j;
int cur_x, cur_y, cur_dic_x, cur_dic_y;
int target_x, target_y, target_dic_x, target_dic_y;
int t_delA, t_delB;
int tsize;

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	cin >> TC;

	for (T = 1; T <= TC; T++) {
		//initialize
		Total_Energy = 0;
		memset(dat, 0, sizeof(dat));
		Atom.clear();

		cin >> N;

		for (i = 0; i < N; i++) {
			cin >> x >> y >> dir >> k;
			x = (x + 1000) * 2;
			y = (y + 1000) * 2;
			Atom.push_back({ x,y,dir,k});
		}

		for (i = 0; i < N; i++) {
			cur_x = Atom[i].x;
			cur_y = Atom[i].y;
			cur_dic_x = dx[Atom[i].dir];
			cur_dic_y = dy[Atom[i].dir];
			
			for (j = i + 1; j < N; j++) {
				target_x = Atom[j].x;
				target_y = Atom[j].y;
				target_dic_x = dx[Atom[j].dir];
				target_dic_y = dy[Atom[j].dir];

				int timeA = cur_dic_x * (target_x - cur_x) + cur_dic_y * (target_y - cur_y);
				int timeB = target_dic_x * (cur_x - target_x) + target_dic_y * (cur_y - target_y);

				if (cur_dic_x && target_dic_x && (target_y - cur_y)) {
					continue;
				}
				if (cur_dic_y && target_dic_y && (cur_x - target_x)) {
					continue;
				}
				if (timeA <= 0 || timeB <= 0) continue;

				else {
					if (timeA == timeB) {
						if(cur_dic_x + target_dic_x) timeflo[timeA].push_back({i,j});
						else  timeflo[timeA/2].push_back({ i,j });
					}
				}
			}
		}

		for (i = 1; i < 4001; i++) {
			tsize = timeflo[i].size();
			for (j = 0; j < tsize; j++) {
				t_delA = dat[timeflo[i][j].A];
				t_delB = dat[timeflo[i][j].B]; 
				if (t_delA  || t_delB) {
					if (t_delA  ==  i && !t_delB) {
						Total_Energy += Atom[timeflo[i][j].B].Energy;
						dat[timeflo[i][j].B] = i;	
					}
					else if (t_delB == i && !t_delA) {
						Total_Energy += Atom[timeflo[i][j].A].Energy;
						dat[timeflo[i][j].A] = i;
					}
					else { continue; }
				}
				else {
					Total_Energy += Atom[timeflo[i][j].A].Energy;
					dat[timeflo[i][j].A] = i;
					Total_Energy += Atom[timeflo[i][j].B].Energy;
					dat[timeflo[i][j].B] = i;
				}
			}
			timeflo[i].clear();
		}
		cout << '#' << T << ' ' << Total_Energy << "\n";
	}
}