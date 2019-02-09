// C++11
#include <cmath>
#include <string>
#include <array>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <time.h>
#include <sys/timeb.h>

using namespace std;

// #include <iostream>
// #include <fstream>

template<class F, class S> string in_v_to_str (const pair<F, S> v);
template<class F, class S> string v_to_str (const pair<F, S> v);
string in_v_to_str (const char v) { return "'" + string{v} + "'"; }
string in_v_to_str (const char *v) { return '"' + v + '"'; }
string in_v_to_str (const string v) { return '"' + v + '"'; }
template<class T> string in_v_to_str (const T v) { stringstream ss; ss << v; return ss.str(); }
template<class T> string v_to_str (const T v) { stringstream ss; ss << v; return ss.str(); }
template<class T, size_t N> string v_to_str (const array<T, N> &v) { stringstream ss; if (v.size() > 0) { ss << "["; for (int i = 0; i < v.size() - 1; ++i) { ss << in_v_to_str(v[i]) << ", "; } ss << in_v_to_str(v[v.size() - 1]) << "]"; } else { ss << "[]"; } return ss.str();
}
template<class T, size_t N> string v_to_str (const array< array<T, N>, N > &v) { stringstream ss; if (v.size() > 0) { ss << "["; for (int i = 0; i < v.size() - 1; ++i) { ss << v_to_str(v[i]) << ", "; } ss << v_to_str(v[v.size() - 1]) << "]"; } else { ss << "[-]"; } return ss.str(); }
template<class T> string v_to_str (const vector<T> &v) { stringstream ss; if (v.size() > 0) { ss << "["; for (int i = 0; i < v.size() - 1; ++i) { ss << in_v_to_str(v[i]) << ", "; } ss << in_v_to_str(v[v.size() - 1]) << "]"; } else { ss << "[]"; } return ss.str(); }
template<class T> string v_to_str (const vector< vector<T> > &v) { stringstream ss; if (v.size() > 0) { ss << "["; for (int i = 0; i < v.size() - 1; ++i) { ss << v_to_str(v[i]) << ", "; } ss << v_to_str(v[v.size() - 1]) << "]"; } else { ss << "[-]"; } return ss.str(); }
template<class T> string v_to_str (const set<T> &v) { stringstream ss; int len = v.size(); ss << (v.size() > 0 ? "{" : "{}"); for (auto& i : v) { ss << in_v_to_str(i) << (len-- > 1 ? ", " : "}"); } return ss.str(); }
template<class K, class V> string v_to_str (const map<K, V> &v) { stringstream ss; int len = v.size(); ss << (v.size() > 0 ? "{" : "{}"); for (auto& i : v) { ss << in_v_to_str(i.first) << " : " << in_v_to_str(i.second) << (len-- > 1 ? ", " : "}"); } return ss.str(); }
template<class T> string v_to_str (const unordered_set<T> &v) { stringstream ss; int len = v.size(); ss << (v.size() > 0 ? "{" : "{}"); for (auto& i : v) { ss << in_v_to_str(i) << (len-- > 1 ? ", " : "}"); } return ss.str(); }
template<class K, class V> string v_to_str (const unordered_map<K, V> &v) { stringstream ss; int len = v.size(); ss << (v.size() > 0 ? "{" : "{}"); for (auto& i : v) { ss << in_v_to_str(i.first) << " : " << in_v_to_str(i.second) << (len-- > 1 ? ", " : "}"); } return ss.str(); }
template<class F, class S> string in_v_to_str (const pair<F, S> v) { stringstream ss; ss << "<" << v_to_str(v.first) << ", " << v_to_str(v.second) << ">"; return ss.str(); }
template<class F, class S> string v_to_str (const pair<F, S> v) { stringstream ss; ss << "<" << v_to_str(v.first) << ", " << v_to_str(v.second) << ">"; return ss.str(); }
string print () { return ""; }
template<typename F, typename... R> string print (const F &f, const R &...r) { stringstream ss; ss << v_to_str(f); if (sizeof...(r) > 0) { ss << " " << print(r...); } return ss.str(); }

template<typename F, typename... R> void pdebug (const F &f, const R &...r) {
    stringstream ss;
    ss << v_to_str(f); if (sizeof...(r) > 0) { ss << " " << print(r...); }
    cerr << "<cerr>" << ss.str() << "</cerr>" << endl;
}

struct mpos {
public:
    int x;
    int y;
    mpos () { this->x = 0; this->y = 0; }
    mpos (int x, int y) {
        this->x = x;
        this->y = y;
    }
    mpos operator + (const mpos &t) { return mpos(this->x + t.x, this->y + t.y); }
    mpos operator - (const mpos &t) { return mpos(this->x - t.x, this->y - t.y); }
    bool operator == (const mpos &t) const { return this->x == t.x && this->y == t.y; }
};

namespace std {
    template <> class hash<mpos> {
    public:
        size_t operator()(const mpos& t) const{ return hash<int>()(t.x<<16) | hash<int>()(t.y); }
    };
}

inline uint32_t xrnd() {
    static uint32_t y = 2463534242;
    y = y ^ (y << 13);
    y = y ^ (y >> 17);
    return y = y ^ (y << 5);
}

class PointsOnGrid {
public:
    int H, W, h, w, Kmin, Kmax;
    vector<string> board;
    vector< vector<int> > iboard;
    vector<string> findSolution (int H, int W, int h, int w, int Kmin, int Kmax, vector<string> board) {
        this->H = H; this->W = W; this->h = h; this->w = w; this->Kmin = Kmin; this->Kmax = Kmax;
        this->board = board;
        pdebug(H, W, h, w, Kmin, Kmax);
        
        this->iboard = vector< vector<int> >(H, vector<int>(W, 0));
        for (int y = 0; y < this->H; ++y) {
            for (int x = 0; x < this->W; ++x) {
                this->iboard[y][x] = this->board[y][x] - 48;
            }
        }
        
        vector< vector<int> > g = this->greedy(0);
        int bestscore = this->allScoreCheck(g);
        for (int i = 1; i < 32; ++i) {
            vector< vector<int> > g2 = this->greedy(i);
            if (this->allScoreCheck(g2) > bestscore) {
                bestscore = this->allScoreCheck(g2);
                g = g2;
            }
        }
        
        vector< vector<int> > t = this->testput();
        vector< vector<int> > best = t;
        bestscore = this->allScoreCheck(t);
        for (auto &i : t) { reverse(i.begin(), i.end()); }
        if (this->allScoreCheck(t) > bestscore) {
            bestscore = this->allScoreCheck(t);
            best = t;
        }
        reverse(t.begin(), t.end());
        if (this->allScoreCheck(t) > bestscore) {
            bestscore = this->allScoreCheck(t);
            best = t;
        }
        for (auto &i : t) { reverse(i.begin(), i.end()); }
        if (this->allScoreCheck(t) > bestscore) {
            bestscore = this->allScoreCheck(t);
            best = t;
        }
        
        if (this->allScoreCheck(g) < 0) { pdebug("---"); }
        vector< vector<int> > iret = (this->allScoreCheck(g) > bestscore ? g : best);
        
        vector<string> ret;
        for (int y = 0; y < this->H; ++y) {
            string s = "";
            for (int x = 0; x < this->W; ++x) {
                if (iret[y][x] == 1) {
                    s += "x";
                } else {
                    s += ".";
                }
            }
            ret.emplace_back(s);
        }
        
        // pdebug(ret);
        // pdebug(this->allScore(ret));
        
        return ret;
    }
    
    vector< vector<int> > testput () {
        vector< vector<int> > ret(this->H, vector<int>(this->W, 0));
        vector< vector<int> > xxx(this->H, vector<int>(this->W, 0));
        
        vector<mpos> mp;
        
        for (int y = 0; y < this->H - (this->h - 1); ++y) {
            for (int x = 0; x < this->W - (this->w - 1); ++x) {
                mp.emplace_back(x, y);
            }
        }
        
        for (auto &i : mp) {
            vector< pair<int, mpos> > t;
            int cnt = 0;
            for (int y = 0; y < this->h; ++y) {
                int py = i.y + y;
                for (int x = 0; x < this->w; ++x) {
                    int px = i.x + x;
                    if (ret[py][px] == 0) {
                        if (xxx[py][px] == 0) {
                            t.emplace_back(this->iboard[py][px], mpos(px, py));
                        }
                    } else {
                        cnt += 1;
                    }
                }
            }
            
            if (cnt < this->Kmax) {
                for (auto &j : t) {
                    const mpos p = j.second;
                    ret[p.y][p.x] = 1;
                    cnt += 1;
                    if (cnt == this->Kmax) { break; }
                }
            }
            
            for (int y = 0; y < this->h; ++y) {
                for (int x = 0; x < this->w; ++x) {
                    xxx[i.y+y][i.x+x] = 1;
                }
            }
            
        }
        
        return ret;
    }
    
    vector< vector<int> > greedy (int n) {
        vector< vector<int> > ret(this->H, vector<int>(this->W, 0));
        vector< vector<int> > xxx(this->H, vector<int>(this->W, 0));
        
        vector<mpos> mp;
        
        
        // ofstream outputfile("out.txt");
        // string o;
        
        
        for (int y = 0; y < this->H - (this->h - 1); ++y) {
            for (int x = 0; x < this->W - (this->w - 1); ++x) {
                mp.emplace_back(x, y);
            }
        }
        
        for (auto &i : mp) {
            vector< pair<int, mpos> > t;
            int minx = 100;
            int miny = 100;
            int maxx = 0;
            int maxy = 0;
            int cnt = 0;
            for (int y = 0; y < this->h; ++y) {
                int py = i.y + y;
                for (int x = 0; x < this->w; ++x) {
                    int px = i.x + x;
                    if (ret[py][px] == 0) {
                        if (xxx[py][px] == 0) {
                            t.emplace_back(this->iboard[py][px], mpos(px, py));
                        }
                    } else {
                        cnt += 1;
                        minx = min(minx, px);
                        miny = min(miny, py);
                        maxx = max(maxx, px);
                        maxy = max(maxy, py);
                    }
                }
            }
            
            if (cnt < this->Kmax-n) {
                sort(t.begin(), t.end(), [](const pair<int, mpos> &a, const pair<int, mpos> &b) { return a.first > b.first; });
                
                for (auto &j : t) {
                    const mpos p = j.second;
                    ret[p.y][p.x] = 1;
                    minx = min(minx, p.x);
                    miny = min(miny, p.y);
                    maxx = max(maxx, p.x);
                    maxy = max(maxy, p.y);
                    cnt += 1;
                    if (cnt == this->Kmax) { break; }
                }
            }
            
            
            for (int y = max(maxy-this->h, 0); y < min(miny+this->h, this->H); ++y) {
                for (int x = max(maxx-this->w, 0); x < min(minx+this->w, this->W); ++x) {
                    xxx[y][x] = 1;
                }
            }
            
            ///
            // for (int y = 0; y < this->H; ++y) {
            //     for (int x = 0; x < this->W; ++x) {
            //         o += ret[y][x] < 1 ? (xxx[y][x] < 1 ? "0" : "1") : "X";
            //     }
            //     o += "\n";
            // }
            // o += "\n";
        }
        
        // outputfile<< o << endl;///
        // outputfile.close();///
        
        return ret;
    }
    
    
    int allScoreCheck (vector< vector<int> > &v) {
        int score = 0;
        
        vector<mpos> mp;
        
        for (int y = 0; y < this->H - (this->h - 1); ++y) {
            for (int x = 0; x < this->W - (this->w - 1); ++x) {
                mp.emplace_back(x, y);
            }
        }
        
        for (auto &i : mp) {
            vector< pair<int, mpos> > t;
            int cnt = 0;
            for (int y = 0; y < this->h; ++y) {
                int py = i.y + y;
                for (int x = 0; x < this->w; ++x) {
                    int px = i.x + x;
                    if (v[py][px] == 0) {
                    } else {
                        cnt += 1;
                    }
                }
            }
            
            if (cnt < this->Kmin) { return -1; }
            if (cnt > this->Kmax) { return -1; }
        }
        
        for (int y = 0; y < this->H; ++y) {
            for (int x = 0; x < this->W; ++x) {
                if (v[y][x] == 1) {
                    score += this->iboard[y][x];
                }
            }
        }
        
        return score;
    }
    
    int allScore (vector<string> &v) {
        int score = 0;
        for (int y = 0; y < this->H; ++y) {
            for (int x = 0; x < this->W; ++x) {
                if (v[y][x] == 'x') {
                    score += this->iboard[y][x];
                }
            }
        }
        return score;
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