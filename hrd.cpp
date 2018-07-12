#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
struct historyT{
    char a, b, c;
    historyT(const char &_a, const char &_b):a(_a), b(_b), c(-1){}
    historyT():a(-1), b(-1), c(-1){}
};

struct posT{
    char a, ifv; //ifv == 1 vertical otherwise horizontal
    posT():a(-1),ifv(-1){}
};

struct dataT{
    posT pos[12];
    vector<historyT> his;
};

string hashData(const dataT &d){ //[A][VERTICAL_PART][0][HORIZONTAL_PART][SINGLE_PART] ----> 11 chars
    string res = "";
    char bucket[20] = {0};
    char ver[5], hor[5], single[4], verp = 0, horp = 0, singlep = 0;
    res += (char)(d.pos[0].a + 'A');
    for(int i = 1; i < 6; ++i){
        if(d.pos[i].ifv) ver[verp++] = d.pos[i].a;
        else hor[horp++] = d.pos[i].a;
    }
    for(int i = 6; i < 10; ++i) single[singlep++] = d.pos[i].a;
    for(int i = 0; i < verp; ++i) bucket[ver[i]]++;
    verp = 0;
    for(int i = 0; i < 20; ++i){
        if(bucket[i]){
            ver[verp++] = i;
            bucket[i]--;
        }
    }
    for(int i = 0; i < horp; ++i) bucket[hor[i]]++;
    horp = 0;
    for(int i = 0; i < 20; ++i){
        if(bucket[i]){
            hor[horp++] = i;
            bucket[i]--;
        }
    }
    for(int i = 0; i < singlep; ++i) bucket[single[i]]++;
    singlep = 0;
    for(int i = 0; i < 20; ++i){
        if(bucket[i]){
            single[singlep++] = i;
            bucket[i]--;
        }
    }
    for(int i = 0; i < verp; ++i) res += char(ver[i] + 'A');
    res += '0';
    for(int i = 0; i < horp; ++i) res += char(hor[i] + 'A');
    for(int i = 0; i < singlep; ++i) res += char(single[i] + 'A');
    return res;
}

dataT getData(){
    char m[5][4];
    dataT tmp;
    char vcount = 0;
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 4; ++j) cin >> m[i][j];
    for(int i = 0; i < 5; ++i){
        for(int j = 0; j < 4; ++j){
            if(m[i][j] == '-') tmp.pos[10 + (vcount++)].a = i * 4 + j;
            else{
                int tmpPos = m[i][j] - 'A';
                if(tmp.pos[tmpPos].a == -1){
                    tmp.pos[tmpPos].a = i * 4 + j;
                    if(i + 1 < 5 && m[i][j] == m[i + 1][j]) tmp.pos[tmpPos].ifv = 1;
                    else tmp.pos[tmpPos].ifv = 0;
                }
            }
        }
    }
    return tmp;
}

/*set<string> mem;

bool canMoveUp(const char &a, const dataT &m){
    //if()
}*/

int main(){
    dataT dta = getData();
    cout << hashData(dta);
}











