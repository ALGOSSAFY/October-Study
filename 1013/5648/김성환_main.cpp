#include <iostream>
#include <string.h>
#include <queue>
 
using namespace std;
 
struct Atom {
    int x;
    int y;
    int dir;
    int K;
};
struct Collision {
    int a;
    int b;
    int time;
};
 
struct cmp {
    bool operator()(Collision a, Collision b) {
        if (a.time < b.time)
            return false;
        if (a.time > b.time)
            return true;
        return false;
    }
};
 
priority_queue<Collision, vector<Collision>, cmp> pq;
 
int N;
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };
int collision_case[4][3] = {
    {1, 2, 3},
    {0, 2, 3},
    {3, 0, 1},
    {2, 0, 1}
};
Atom arr[1000];
int used[1000];
int pop_time[1000];
 
int check_collision() {
    int energy = 0;
    int time = 0;
    while (!pq.empty()) {
        Collision now = pq.top();
        pq.pop();
 
        if (now.time == time) {
            if (used[now.a] == 1 && used[now.b] == 1)
                continue;
            else if (used[now.a] == 0 && used[now.b] == 0) {
                used[now.a] = 1;
                used[now.b] = 1;
                time = now.time;
                pop_time[now.a] = time;
                pop_time[now.b] = time;
                energy += arr[now.a].K + arr[now.b].K;
            }
            else if (used[now.a] == 1 && used[now.b] == 0) {
                if (pop_time[now.a] != time)
                    continue;
                used[now.b] = 1;
                time = now.time;
                pop_time[now.b] = time;
                energy += arr[now.b].K;
            }
            else if (used[now.a] == 0 && used[now.b] == 1) {
                if (pop_time[now.b] != time)
                    continue;
                used[now.a] = 1;
                time = now.time;
                pop_time[now.a] = time;
                energy += arr[now.a].K;
            }
        }
        else {
            if (used[now.a] != 0)
                continue;
            if (used[now.b] != 0)
                continue;
            used[now.a] = 1;
            used[now.b] = 1;
            time = now.time;
            pop_time[now.a] = time;
            pop_time[now.b] = time;
            energy += arr[now.a].K + arr[now.b].K;
        }
 
    }
 
    return energy;
}
 
int solution() {
    for (int i = 0; i < N; i++) {
        Atom now = arr[i];
        for (int j = i + 1; j < N; j++) {
            Atom next = arr[j];
            if (now.dir == next.dir)
                continue;
            if (collision_case[now.dir][0] == next.dir) {
                if (now.dir == 0) {
                    if (next.y < now.y)
                        continue;
                    if (next.x != now.x)
                        continue;
                    pq.push({ i, j, abs(next.y - now.y) });
                }
                else if (now.dir == 1) {
                    if (next.y > now.y)
                        continue;
                    if (next.x != now.x)
                        continue;
                    pq.push({ i, j, abs(next.y - now.y) });
                }
                else if (now.dir == 2) {
                    if (next.x > now.x)
                        continue;
                    if (next.y != now.y)
                        continue;
                    pq.push({ i, j, abs(next.x - now.x) });
                }
                else if (now.dir == 3) {
                    if (next.x < now.x)
                        continue;
                    if (next.y != now.y)
                        continue;
                    pq.push({ i, j, abs(next.x - now.x) });
                }
            }
            else {
                if (now.dir == 0) {
                    if (next.dir == 2) {
                        if (!(next.y > now.y && next.x > now.x))
                            continue;
                        if (abs(next.y - now.y) != abs(next.x - now.x))
                            continue;
                        pq.push({ i, j, abs(next.x - now.x) * 2 });
                    }
                    else if (next.dir == 3) {
                        if (!(next.y > now.y && next.x < now.x))
                            continue;
                        if (abs(next.y - now.y) != abs(next.x - now.x))
                            continue;
                        pq.push({ i, j, abs(next.x - now.x) * 2 });
                    }
                }
                else if (now.dir == 1) {
                    if (next.dir == 2) {
                        if (!(next.y < now.y && next.x > now.x))
                            continue;
                        if (abs(next.y - now.y) != abs(next.x - now.x))
                            continue;
                        pq.push({ i, j, abs(next.x - now.x) * 2 });
                    }
                    else if (next.dir == 3) {
                        if (!(next.y < now.y && next.x < now.x))
                            continue;
                        if (abs(next.y - now.y) != abs(next.x - now.x))
                            continue;
                        pq.push({ i, j, abs(next.x - now.x) * 2 });
                    }
                }
                else if (now.dir == 2) {
                    if (next.dir == 0) {
                        if (!(next.y < now.y && next.x < now.x))
                            continue;
                        if (abs(next.y - now.y) != abs(next.x - now.x))
                            continue;
                        pq.push({ i, j, abs(next.x - now.x) * 2 });
                    }
                    else if (next.dir == 1) {
                        if (!(next.y > now.y && next.x < now.x))
                            continue;
                        if (abs(next.y - now.y) != abs(next.x - now.x))
                            continue;
                        pq.push({ i, j, abs(next.x - now.x) * 2 });
                    }
                }
                else if (now.dir == 3) {
                    if (next.dir == 0) {
                        if (!(next.y < now.y && next.x > now.x))
                            continue;
                        if (abs(next.y - now.y) != abs(next.x - now.x))
                            continue;
                        pq.push({ i, j, abs(next.x - now.x) * 2 });
                    }
                    else if (next.dir == 1) {
                        if (!(next.y > now.y && next.x > now.x))
                            continue;
                        if (abs(next.y - now.y) != abs(next.x - now.x))
                            continue;
                        pq.push({ i, j, abs(next.x - now.x) * 2 });
                    }
                }
            }
 
        }
    }
    return check_collision();
}
 
void input() {
    memset(arr, 0, sizeof(arr));
    memset(used, 0, sizeof(used));
    while (!pq.empty())
        pq.pop();
 
    cin >> N;
    for (int i = 0; i < N; i++) {
        Atom now;
        cin >> now.x >> now.y >> now.dir >> now.K;
        arr[i] = now;
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
        cout << "#" << tc << " " << solution() <<"\n";
    }
 
    return 0;
}
