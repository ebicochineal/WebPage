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
        
        best = this->SA(9800 - this->sw.get_milli_time(), best, cnt, 2.0);
        
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
        vector<mpos> ad;
        vector<mpos> dl;
        int k = 300000;
        int maxx, maxy, minx, miny;
        
        this->allSet(ret);
        
        while ((saTimeCurrent = sw.get_milli_time()) < saTimeEnd) {
            const double T = saTimeEnd-saTimeStart;
            const double t = saTimeCurrent-saTimeStart;
            
            const int q = saTimeEnd - saTimeCurrent;
            if (q < 1500) {
                k = 150000;
                if (q < 800) {
                    k = 30000;
                    if (q < 400) { k = 15000; }
                }
            }
            
            for (int z = 0; z < k; ++z) {
                ad.clear();
                dl.clear();
                int r1 = 1;
                int r2 = 1;
                int e = 1;
                int xr = xrnd() % 32;
                
                if (xr < 4) {
                    r1 = 2;
                    r2 = 1;
                } else if (xr < 5) {
                    r1 = 1;
                    r2 = 2;
                    e = 2;
                }
                
                if (xrnd()%8 > 0) {
                    maxx = 0;
                    maxy = 0;
                    minx = this->W;
                    miny = this->H;
                    int px = xrnd() % (this->W - (this->w - 1));
                    int py = xrnd() % (this->H - (this->h - 1));
                    
                    int ax = -1;
                    int ay = -1;
                    int bx = -1;
                    int by = -1;
                    for (int i = 0; i < 32; ++i) {
                        int x = px + xrnd() % this->w;
                        int y = py + xrnd() % this->h;
                        
                        if (ret[y][x] == 0 && ad.size() < r1 && (x != ax || y != ay)) {
                            maxx = max(maxx, x);
                            minx = min(minx, x);
                            maxy = max(maxy, y);
                            miny = min(miny, y);
                            ad.emplace_back(x, y);
                            ax = x;
                            ay = y;
                        } else if (ret[y][x] == 1 && dl.size() < r2 && (x != bx || y != by)) {
                            maxx = max(maxx, x);
                            minx = min(minx, x);
                            maxy = max(maxy, y);
                            miny = min(miny, y);
                            dl.emplace_back(x, y);
                            bx = x;
                            by = y;
                        }
                        if (ad.size() >= r1 && dl.size() >= r2) { break; }
                    }
                    
                } else {
                    maxx = 0;
                    maxy = 0;
                    minx = this->W;
                    miny = this->H;
                    for (int i = 0; i < 32; ++i) {
                        int x = xrnd() % this->W;
                        int y = xrnd() % this->H;
                        if (ret[y][x] == 1) { continue; }
                        maxx = max(maxx, x);
                        minx = min(minx, x);
                        maxy = max(maxy, y);
                        miny = min(miny, y);
                        ad.emplace_back(x, y);
                        break;
                    }
                    for (int i = 0; i < 32; ++i) {
                        int x = xrnd() % this->W;
                        int y = xrnd() % this->H;
                        if (ret[y][x] == 0) { continue; }
                        maxx = max(maxx, x);
                        minx = min(minx, x);
                        maxy = max(maxy, y);
                        miny = min(miny, y);
                        dl.emplace_back(x, y);
                        break;
                    }
                }
                
                
                
                double tmpscore = lastscore;
                for (auto &i : ad) { tmpscore += this->iboard[i.y][i.x]; }
                for (auto &i : dl) { tmpscore -= this->iboard[i.y][i.x]; }
                
                const double startTemp   = u * e;
                const double endTemp     = 0.0;
                const double temp        = startTemp + (endTemp - startTemp) * t / T;
                const double probability = exp((tmpscore - lastscore) / temp);
                const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if ( !(tmpscore >= lastscore || (FORCE_NEXT)) ) {
                    cnt += 1;
                    continue;
                }
                
                for (auto &i : ad) {
                    ret[i.y][i.x] = 1;
                    this->Update(i, 1);
                }
                for (auto &i : dl) {
                    ret[i.y][i.x] = 0;
                    this->Update(i, -1);
                }
                if (this->allCheck(minx, miny, maxx, maxy) >= 0) {
                    lastscore = tmpscore;
                    if (tmpscore > bestscore) {
                        bestscore = tmpscore;
                        bestret = ret;
                        lastuptime = saTimeCurrent + saTimeStart;
                    }
                } else {
                    for (auto &i : ad) {
                        ret[i.y][i.x] = 0;
                        this->Update(i, -1);
                    }
                    for (auto &i : dl) {
                        ret[i.y][i.x] = 1;
                        this->Update(i, 1);
                    }
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
    
    array< array<int, 50>, 50> arr;
    inline void allSet (const vector< vector<int> > &v) {
        const int H = this->H - (this->h - 1);
        const int W = this->W - (this->w - 1);
        for (int iy = 0; iy < 50; ++iy) {
            for (int ix = 0; ix < 50; ++ix) {
                this->arr[iy][ix] = 0;
            }
        }
        for (int iy = 0; iy < H; ++iy) {
            const int my = this->h + iy;
            for (int ix = 0; ix < W; ++ix) {
                const int mx = this->w + ix;
                int cnt = 0;
                for (int y = iy; y < my; ++y) {
                    for (int x = ix; x < mx; ++x) {
                        cnt += v[y][x];
                    }
                }
                this->arr[iy][ix] = cnt;
            }
        }
    }
    
    inline int allCheck (int minx, int miny, int maxx, int maxy) {
        const int H = this->H - (this->h - 1);
        const int W = this->W - (this->w - 1);
        miny = max(miny - this->h + 1, 0);
        minx = max(minx - this->w + 1, 0);
        maxy = min(maxy + 1, H);
        maxx = min(maxx + 1, W);
        for (int iy = miny; iy < maxy; ++iy) {
            for (int ix = minx; ix < maxx; ++ix) {
                const int cnt = this->arr[iy][ix];
                if (cnt < this->Kmin) { return -1; }
                if (cnt > this->Kmax) { return -1; }
            }
        }
        return 1;
    }
    
    inline void Update (const mpos &p, const int v) {
        const int H = this->H - (this->h - 1);
        const int W = this->W - (this->w - 1);
        const int miny = max(p.y - this->h + 1, 0);
        const int minx = max(p.x - this->w + 1, 0);
        const int maxy = min(p.y + 1, H);
        const int maxx = min(p.x + 1, W);
        for (int iy = miny; iy < maxy; ++iy) {
            for (int ix = minx; ix < maxx; ++ix) {
                this->arr[iy][ix] += v;
            }
        }
    }
    
    
    inline int allCheck (const vector< vector<int> > &v, int minx, int miny, int maxx, int maxy) {
        const int H = this->H - (this->h - 1);
        const int W = this->W - (this->w - 1);
        miny = max(miny - this->h + 1, 0);
        minx = max(minx - this->w + 1, 0);
        maxy = min(maxy + 1, H);
        maxx = min(maxx + 1, W);
        int prevcnt = 0;
        int xmin_prevcnt = 0;
        int cnt = 0;
        for (int iy = miny; iy < maxy; ++iy) {
            const int my = this->h + iy;
            for (int ix = minx; ix < maxx; ++ix) {
                const int mx = this->w + ix;
                
                if (ix == minx) {
                    if (iy == miny) {
                        for (int y = iy; y < my; ++y) {
                            for (int x = ix; x < mx; ++x) {
                                cnt += v[y][x];
                            }
                        }
                    } else {
                        cnt = xmin_prevcnt;
                        for (int x = ix; x < mx; ++x) {
                            cnt -= v[iy-1][x];
                            cnt += v[my-1][x];
                        }
                    }
                    xmin_prevcnt = cnt;
                } else {
                    cnt = prevcnt;
                    for (int y = iy; y < my; ++y) {
                        cnt -= v[y][ix-1];
                        cnt += v[y][mx-1];
                    }
                    
                }
                
                prevcnt = cnt;
                
                if (cnt < this->Kmin) { return -1; }
                if (cnt > this->Kmax) { return -1; }
            }
        }
        
        return 1;
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