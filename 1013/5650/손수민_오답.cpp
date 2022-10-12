#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int N;
int T;
int arr[100][100];
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
int path[100][100][4];
int chg_dir[6][4] = {
{
  0,0,0,0
},
{
  2,3,1,0
},
{
  1,3,0,2
},
{
  3,2,0,1
},
{
  2,0,3,1
},
{
  2,3,0,1
},
};
vector<pair<int, int>>portal[11];
/*
  매번 하나씩 가면 시간초과?`
  1 -> 0->1, 1->0 ,
  2
  3
  4
  5
  6~10 텔레포트
  첫번째 간 곳을 다시 들르거나 , -1로 가면 종료
  이미 들른 경로인 곳은 다시 갈 필요가 없음

  -1 끝 , 시작지 도착 -0
*/

bool calc_range(int x, int y)
{
    if (x >= 0 && x < N && y >= 0 && y < N)
        return true;
    return false;

}
int rolling(int sx, int sy, int dir)
{
    //해당 시작지에서 롤링하면서 점수 나온결과
    path[sx][sy][dir] = 1;
    int x = sx;
    int y = sy ;
    int result = 0;
    while (1)
    {
        x += dx[dir];
        y += dy[dir];
        if (!calc_range(x, y))
        {
            result++;
            x -= dx[dir];
            y -= dy[dir];
            dir = chg_dir[5][dir];
        }
        if (x == sx && y == sy)
            break;
        if (arr[x][y] == -1)
            break;
        path[x][y][dir] = 1;
        if (arr[x][y] >= 1 && arr[x][y] <= 5)
        {
            result++;
            dir = chg_dir[arr[x][y]][dir];
        }
        else if (arr[x][y] >= 6)
        {
            int p_x_1, p_y_1;
            int p_x_2, p_y_2;
            p_x_1 = portal[arr[x][y]][0].first;
            p_x_2 = portal[arr[x][y]][1].first;
            p_y_1 = portal[arr[x][y]][0].second;
            p_y_2 = portal[arr[x][y]][1].second;
            if (x == p_x_1 && y == p_y_1)
            {
                x = p_x_2;
                y = p_y_2;
            }
            else
            {
                x = p_x_1;
                y = p_y_1;
            }






        }


    }
    return result;

}
int main() {
    int result = 0;
    cin >> T;
    for (int tc = 0; tc < T; tc++)
    {
        memset(arr, 0, sizeof(arr));
        memset(path, 0, sizeof(path));
        for(int i=0;i<11;i++)
          portal[i].clear();
        result = 0;
        cin >> N;
        for (int r = 0; r < N; r++)
        {
            for (int c = 0; c < N; c++)
            {
                cin >> arr[r][c];
                if (arr[r][c] != 0)
                {
                    for (int d = 0; d < 4; d++)
                    {
                        path[r][c][d] = 1;
                        //아예 시작지가 안됨
                    }
                }
                if (arr[r][c] >= 6)
                {
                    portal[arr[r][c]].push_back({ r,c });

                }
            }
        }
        for (int r = 0; r < N; r++)
        {
            for (int c = 0; c < N; c++)
            {
                for (int d = 0; d < 4; d++)
                {
                    if (!path[r][c][d])
                    {
                        result = max(result, rolling(r, c, d));
                    }

                }

            }


        }
        cout << "#" << tc + 1 << ' ' << result << '\n';





    }



}