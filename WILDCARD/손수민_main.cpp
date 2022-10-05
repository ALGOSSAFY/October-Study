#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
/*
  와일드 카드
  *이 문제
*/
int c;
string card , test;
bool chk(int c, int t)
{
  bool result = false;
  if(c== card.size() && t ==test.size())
    return true;
  if(card[c] =='*')
  {
    for(int i=t;i<=test.size();i++)
      result = max(result, chk(c+1 , i));
    return result;
  }
  else if(card[c] == '?')
  {
    result = max(result ,chk(c+1,t+1));
    return result;
  }
  else
  {
    if(card[c] == test[t])
    {
      result = max(result ,chk(c+1,t+1));
      return result;
    }
    else
      return false;


    
  }



  return result;
}


int main() {
  cin>>c;
  for(int tc=0;tc<c;tc++)
    {

      cin>>card;
      int N;
      cin>>N;
      vector<string>result;
      for(int idx=0;idx<N;idx++)
        {        
          cin>>test;
          if(chk(0,0))
          {
            result.push_back(test);
          }

        } 
      sort(result.begin() , result.end());
      for(int i=0;i<result.size();i++)
        cout<<result[i]<<'\n';
          
  }
}
