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

class StopWatch {
public:
    int starts;
    int startm;
    struct timeb timebuffer;
    StopWatch () {
        ftime(&this->timebuffer);
        this->starts = this->timebuffer.time;
        this->startm = this->timebuffer.millitm;
    }
    
    inline int get_milli_time () {
        ftime(&this->timebuffer);
        return (this->timebuffer.time - this->starts) * 1000 + (this->timebuffer.millitm - this->startm);
    }
};

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
    
    StopWatch sw;
    
    vector<string> findSolution (int H, int W, int h, int w, int Kmin, int Kmax, vector<string> board) {
        this->sw = StopWatch();
        this->H = H; this->W = W; this->h = h; this->w = w; this->Kmin = Kmin; this->Kmax = Kmax;
        this->board = board;
        pdebug(H, W, h, w, Kmin, Kmax);
        
        this->iboard = vector< vector<int> >(H, vector<int>(W, 0));
        for (int y = 0; y < this->H; ++y) {
            for (int x = 0; x < this->W; ++x) {
                this->iboard[y][x] = this->board[y][x] - 48;
            }
        }
        
        vector< vector<int> > t = this->testput();
        vector< vector<int> > best = t;
        int bestscore = this->allScoreCheck(best);
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
        bestscore = this->allScoreCheck(best);
        int cnt = 0;
        
        best = this->SA(4000 - this->sw.get_milli_time() , best, cnt, 4.0);
        
        while (this->sw.get_milli_time() < 4800) {
            for (int i = 0; i < 3000; ++i) {
                int x = xrnd() % this->W;
                int y = xrnd() % this->H;
                if (best[y][x] == 1) { continue; }
                best[y][x] = 1;
                int score = this->allScoreCheck(best);
                if (score > bestscore) {
                    bestscore = score;
                } else {
                    best[y][x] = 0;
                }
                cnt += 1;
            }
        }
        best = this->SA(9800 - this->sw.get_milli_time() , best, cnt, 2.0);
        
        pdebug(cnt);
        pdebug(this->sw.get_milli_time());
        return this->toRet(best);
    }
    
    vector< vector<int> > SA (int limit, vector< vector<int> > ret, int &cnt, const double u) {////
        StopWatch sw;
        
        vector< vector<int> > bestret = ret;
        double bestscore = this->allScoreCheck(ret);////
        double lastscore = bestscore;
        int saTimeStart = sw.get_milli_time();
        int saTimeEnd   = limit;
        int saTimeCurrent = saTimeStart;
        int64_t R = 1000000000;
        int lastuptime = saTimeStart;
        vector<mpos> p1;
        vector<mpos> p2;
        
        while ((saTimeCurrent = sw.get_milli_time()) < saTimeEnd) {
            for (int z = 0; z < 800; ++z) {
                p1.clear();
                p2.clear();
                int r = xrnd() % 2 + 1;
                
                for (int i = 0; i < 100; ++i) {
                    int x = xrnd() % this->W;
                    int y = xrnd() % this->H;
                    if (ret[y][x] == 1) { continue; }
                    p1.emplace_back(x, y);
                    if (p1.size() >= r) { break; }
                }
                for (int i = 0; i < 100; ++i) {
                    int x = xrnd() % this->W;
                    int y = xrnd() % this->H;
                    if (ret[y][x] == 0) { continue; }
                    p2.emplace_back(x, y);
                    if (p2.size() >= r) { break; }
                }
                if (p1.size() != p2.size()) { continue; }
                
                for (auto &i : p1) { ret[i.y][i.x] = 1; }
                for (auto &i : p2) { ret[i.y][i.x] = 0; }
                
                double tmpscore = this->allScoreCheck(ret);////
                
                const double T = saTimeEnd-saTimeStart;
                const double t = saTimeCurrent-saTimeStart;
                const double startTemp   = u;
                double endTemp     = 0.0;
                double temp        = startTemp + (endTemp - startTemp) * t / T;
                double probability = exp((tmpscore - lastscore) / temp);
                bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if (tmpscore >= lastscore || (FORCE_NEXT)) {
                    lastscore = tmpscore;
                    if (tmpscore > bestscore) {
                        bestscore = tmpscore;
                        bestret = ret;
                        lastuptime = saTimeCurrent + saTimeStart;
                    }
                } else {
                    for (auto &i : p1) { ret[i.y][i.x] = 0; }
                    for (auto &i : p2) { ret[i.y][i.x] = 1; }
                }
                cnt += 1;
            }
        }
        
        return bestret;
    }
    
    
    vector<string> toRet (vector< vector<int> > iret) {
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
        return ret;
    }
    
    vector< vector<int> > testput () {
        vector< vector<int> > ret(this->H, vector<int>(this->W, 0));
        vector< vector<int> > xxx(this->H, vector<int>(this->W, 0));
        int maxk = this->Kmin + (this->Kmax - this->Kmin) / 2 + (this->Kmax - this->Kmin) / 3;
        maxk = max(maxk, this->Kmax - 64);
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
            
            if (cnt < maxk) {
                for (auto &j : t) {
                    const mpos p = j.second;
                    ret[p.y][p.x] = 1;
                    cnt += 1;
                    if (cnt >= maxk) { break; }
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