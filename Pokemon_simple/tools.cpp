#include "tools.h"
#include <sstream>

inline vector<string> Split(const string& s, char delimiter)
{
    vector<string>out;
    string temp = "";
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == delimiter) { out.push_back(temp); temp = ""; }
        else temp += s[i];
    }
    out.push_back(temp);
    return out;
}
       

  

inline int Stoi(const string& s)
{
    istringstream is(s);
    int num;
    is >> num;
    return num;
}

inline pair<int, int> GetPos()
{
    return pair<int, int>();
}

inline void GotoXY(int x, int y)
{
}

inline void ClearScreen()
{
    system("cls");
    return;
}
