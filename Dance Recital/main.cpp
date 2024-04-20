#include <cstdio>
#include <bitset>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>

using bitset32_t = std::bitset<32>;
using bitset16_t = std::bitset<16>;

std::vector<bitset32_t> routines;
bitset16_t isVisited;
int minQuickChange = INT32_MAX;

int getQuickChanges(const std::deque<bitset32_t>& permQ)
{
   int sum = 0;
   for(int i = 0; i + 1 < permQ.size(); i++)
   {
       bitset32_t diff = permQ[i] & permQ[i + 1];
       sum += diff.count();
   }
   return sum;
}

void DFS(int index, std::deque<bitset32_t>& permQ)
{
    isVisited.set(index);
    permQ.push_back(routines[index]);

    if(permQ.size() == routines.size())
    {
       int ans = getQuickChanges(permQ);
       if(ans < minQuickChange) minQuickChange = ans;
    }
    else
    {
       for(int i = 0; i < routines.size(); i++)
       {
           if(isVisited[i]) continue;
           DFS(i, permQ);
       }
    }

    isVisited.reset(index);
    permQ.pop_back();
}

void execute()
{
    std::deque<bitset32_t> permQ;
    for(int i = 0; i < routines.size(); i++)
    {
        DFS(i, permQ);
    }
}

bitset32_t convertStringToBitset(char routine[27])
{
    bitset32_t input;
    for(int i = 0; routine[i] != '\0'; i++)
    {
        input.set(routine[i] - 'A');
    }
    return input;
}

int main()
{
    int R;
    char routine[27];
    scanf("%d\n", &R);
    for(int i = 0; i < R; i++)
    {
        scanf("%s\n", routine);
        routines.emplace_back(convertStringToBitset(routine));
    }
    execute();
    printf("%d\n", minQuickChange);
    return 0;
}