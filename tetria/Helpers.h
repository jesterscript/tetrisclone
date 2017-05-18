#ifndef HELPER_H
#define HELPER_H
#include <algorithm>
#include <vector>
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
template <typename T>
const bool Contains( std::vector<T>& Vec, const T& Element )
{
    if (std::find(Vec.begin(), Vec.end(), Element) != Vec.end())
        return true;

    return false;
}
bool ContainsIntPair(std::vector<std::pair<int,int> >& vec,int x,int y)
{
    bool ans = false;
    for(int i = 0 ; i < vec.size() ; ++i)
    {
        if(vec[i].first == x && vec[i].second == y )
            ans = true;
    }
    return ans;

}
void swap (int& a ,int& b)
{
    int temp = a;
    a = b;
    b = temp;

}
int myrandom (int i) { return std::rand()%i;}

#endif // HELPER_H
