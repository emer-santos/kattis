#include <cstdio>
#include <cassert>
#include <string>
#include <algorithm>

using std::string;

int rosterSize = 0;
string roster[10];
int16_t isVisited;
int16_t dislikes[10];

int pathSize = 0;
int path[10];

void init()
{
    pathSize = 0;
    isVisited = 0;
    for(int i = 0; i < 10; i++)
        dislikes[i] = 0;
}

bool DFS(int curr)
{
    path[pathSize++] = curr;
    isVisited |= 1 << curr;

    if(pathSize == rosterSize)
    {
        return true;
    }
    else
    {
        for(int i = 0; i < rosterSize; ++i)
        {
            if((isVisited >> i) & 1) continue;
            if((dislikes[curr] >> i) & 1) continue;
            if(DFS(i)) return true;
        }
    }

    --pathSize;
    isVisited &= ~(1 << curr);
    return false;
}

void answer()
{
    for(int i = 0; i < rosterSize; ++i)
    {
        if(DFS(i))
        {
            for(int n = 0; n < pathSize; ++n)
            {
                printf("%s ", roster[path[n]].c_str());
            }
            printf("\n");
            return;
        }
    }
    printf("You all need therapy.\n");
}

void setDislikes(const string name1, const string name2)
{
    int index1 = 0, index2 = 0;
    bool isFound1 = false, isFound2 = false;
    for(int i = 0; i < rosterSize; ++i)
    {
        if(roster[i] == name1)
        {
            index1 = i;
            isFound1 = true;
        }

        if(roster[i] == name2)
        {
            index2 = i;
            isFound2 = true;
        }

        if(isFound1 && isFound2) break;
    }

    assert((isFound1 && isFound2) && "Error: Items are not found\n");

    dislikes[index1] |= 1 << index2;
    dislikes[index2] |= 1 << index1;
}

int main()
{
    int cnt;
    char name1[21], name2[21];
    char buffer[5];
    while(fgets(buffer, 5, stdin))
    {
        init();
        sscanf(buffer, "%d\n", &rosterSize);
        for(int n = 0; n < rosterSize; ++n)
        {
            scanf("%20s\n", name1);
            roster[n] = string(name1);
        }

        std::sort(roster, roster + rosterSize);

        scanf("%d\n", &cnt);
        for(int n = 0; n < cnt; ++n)
        {
            scanf("%20s %20s\n", name1, name2);
            setDislikes(name1, name2);
        }

        answer();
    }
    return 0;
}