// C++11
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <set>
#include <string>

using namespace std;

class PointsOnGrid {
public:
    vector<string> findSolution(int H, int W, int h, int w, int Kmin, int Kmax, vector<string> board) {
      
        vector<string> ret;

        //create an empty grid and place one point in the corner            
        for (int i = 0; i < H; ++i)
        {
          string a=".";
          if (i==0) a="x";
          for (int j = 1; j < W; ++j) a+=".";
        
          ret.push_back(a);
        }
        
        return ret;
    }
};
// -------8<------- end of solution submitted to the website -------8<-------

template<class T> void getVector(vector<T>& v) {
    for (int i = 0; i < v.size(); ++i)
        cin >> v[i];
}

int main() {
    PointsOnGrid pog;
    int H;
    int W;
    int h;
    int w;
    int Kmin;
    int Kmax;
    cin >> H;
    cin >> W;
    cin >> h;
    cin >> w;
    cin >> Kmin;
    cin >> Kmax;
    vector<string> grid(H);
    getVector(grid);

    vector<string> ret = pog.findSolution(H,W,h,w,Kmin,Kmax,grid);
    cout << ret.size() << endl;
    for (int i = 0; i < (int)ret.size(); ++i)
        cout << ret[i] << endl;
    cout.flush();
}