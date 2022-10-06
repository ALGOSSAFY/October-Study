#include<iostream>
#include<bitset>
#include<string>

using namespace std;

bitset<200000> Bitset_M, Bitset_F;
string Members, Fans;
int M, N, cnt;

int fanmeeting() {
	cnt = 0;
	Bitset_M.set();
	Bitset_F.set();

	cin >> Members >> Fans;
	M = Members.length();
	N = Fans.length();

	for (int i = 0; i < M; i++) {
		Bitset_M <<= 1;
		if (Members[i] == 'F') Bitset_M.set(0);
		Bitset_F <<= 1;
		if (Fans[i] == 'F') Bitset_F.set(0);
	}
	if ((Bitset_M | Bitset_F).all()) cnt++;

	for (int i = M; i < N; i++) {
		Bitset_F <<= 1;
		Bitset_F.set(M);
		if (Fans[i] == 'F')  Bitset_F.set(0);
		if ((Bitset_M | Bitset_F).all())cnt++;
	}

	return cnt;
}


int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int C;
	cin >> C;
	while(C--)cout << fanmeeting() << "\n";
	return 0;
}