#include <cstdio>
#include <vector>
#include <string>
#include <unordered_set>

using std::string;

struct SCard
{
    SCard(const string& in)
    {
        values.insert(std::stoi(in));
        // Set reverse value
        if(in.find_first_of("347") == string::npos)
        {
            string rev(in.rbegin(), in.rend());
            values.insert(std::stoi(rev));
        }

    }

    std::unordered_set<int> values;
};

std::vector<SCard> cards;

int main()
{
    int N, S;
    char str[10];
    scanf("%d %d", &N, &S);

    for(int i = 0; i < N; i++)
    {
        scanf("%s", &str[0]);
        cards.emplace_back(str);
    }

    // for(auto e : cards)
    //     printf("value=%d hasRev=%d rev=%d\n", e.value, e.hasReverseValue, e.reverseValue);

    for(int first = 0; first < cards.size(); first++)
    {
        for(int second = 0; second < cards.size(); second++)
        {

            if(first == second) continue;

            for(auto firstValue : cards[first].values)
            {
                for(auto secondValue : cards[second].values)
                {
                    if(firstValue + secondValue == S)
                    {
                        printf("YES\n");
                        return 0;
                    }
                }
            }
        }
    }

    printf("NO\n");
    return 0;
}