#include <iostream>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

void swap(char &a, char &b){
    char tmp = a;
    a = b;
    b = tmp;
    return;
}

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

set<string> mem; //record the searched parttern
queue<dataT> Q; //main search Queue

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

inline bool canMoveLeft(const char &c, const dataT &dta){
    char tmpPos = c - 'A';
    char tmpPosLetter = dta.pos[tmpPos].a;
    char tmpVacantPos1 = dta.pos[10].a, tmpVacantPos2 = dta.pos[11].a;
    if(tmpVacantPos1 > tmpVacantPos2) swap(tmpVacantPos1, tmpVacantPos2);
    if(c == 'A' || dta.pos[tmpPos].ifv){
        if(tmpPosLetter - 1 == tmpVacantPos1 && tmpPosLetter + 3 == tmpVacantPos2) return 1;
        else return 0;
    }
    else{
        if(tmpPosLetter - 1 == tmpVacantPos1 || tmpPosLetter - 1 == tmpVacantPos2) return 1;
        else return 0;
    }
}
inline bool canMoveRight(const char &c, const dataT &dta){
    char tmpPos = c - 'A';
    char tmpPosLetter = dta.pos[tmpPos].a;
    char tmpVacantPos1 = dta.pos[10].a, tmpVacantPos2 = dta.pos[11].a;
    if(tmpVacantPos1 > tmpVacantPos2) swap(tmpVacantPos1, tmpVacantPos2);
    if(c == 'A' || dta.pos[tmpPos].ifv){
        if(tmpPosLetter + 2 == tmpVacantPos1 && tmpPosLetter + 6 == tmpVacantPos2) return 1;
        else return 0;
    }
    else if(tmpPosLetter <= 5 && tmpPosLetter >= 0){
        if(tmpPosLetter + 2 == tmpVacantPos1 || tmpPosLetter + 2 == tmpVacantPos2) return 1;
        else return 0;
    }
    else{
        if(tmpPosLetter + 1 == tmpVacantPos1 || tmpPosLetter + 1 == tmpVacantPos2) return 1;
        else return 0;
    }
}
inline bool canMoveUp(const char &c, const dataT &dta){
    char tmpPos = c - 'A';
    char tmpPosLetter = dta.pos[tmpPos].a;
    char tmpVacantPos1 = dta.pos[10].a, tmpVacantPos2 = dta.pos[11].a;
    if(tmpVacantPos1 > tmpVacantPos2) swap(tmpVacantPos1, tmpVacantPos2);
    if(dta.pos[tmpPos].ifv == 1){
        if(tmpPosLetter - 4 == tmpVacantPos1 || tmpPos - 4 == tmpVacantPos2) return 1;
        else return 0;
    }
    else if(tmpPos >= 0 && tmpPos <= 5){
        if(tmpPosLetter - 4 == tmpVacantPos1 && tmpPosLetter - 3 == tmpVacantPos2) return 1;
        else return 0;
    }
    else{
        if(tmpPosLetter - 4 == tmpVacantPos1 || tmpPosLetter - 4 == tmpVacantPos2) return 1;
        else return 0;
    }
}
inline bool canMoveDown(const char &c, const dataT &dta){
    char tmpPos = c - 'A';
    char tmpPosLetter = dta.pos[tmpPos].a;
    char tmpVacantPos1 = dta.pos[10].a, tmpVacantPos2 = dta.pos[11].a;
    if(tmpVacantPos1 > tmpVacantPos2) swap(tmpVacantPos1, tmpVacantPos2);
    if(dta.pos[tmpPos].ifv){
        if(tmpPosLetter + 8 == tmpVacantPos1 || tmpPosLetter + 8 == tmpVacantPos2) return 1;
        else return 0;
    }
    else if(tmpPos == 0){
        if(tmpPosLetter + 8 == tmpVacantPos1 && tmpPosLetter + 9 == tmpVacantPos2) return 1;
        else return 0;
    }
    else if(tmpPos > 0  && tmpPos <= 5){
        if(tmpPosLetter + 4 == tmpVacantPos1 && tmpPosLetter + 5 == tmpVacantPos2) return 1;
        else return 0;
    }
    else{
        if(tmpPosLetter + 4 == tmpVacantPos1 || tmpPosLetter + 4 == tmpVacantPos2) return 1;
        else return 0;
    }
}


dataT moveUp(const char &c, const dataT &dta){
    dataT tmp = dta;
}
dataT moveDown(const char &c, const dataT &dta){}
dataT moveLeft(const char &c, const dataT &dta){}
dataT moveRight(const char &c, const dataT &dta){}

int main(){
    dataT tmp = getData(), tmp1;
    Q.push(tmp);
    while(!Q.empty()){
        tmp = Q.front();
        Q.pop();
        for(int i = 0; i < 12; ++i){
            if(canMoveUp('A' + i, tmp)){
                tmp1 = moveUp('A' + i, tmp);
                if(tmp1.pos[0].a != -1) Q.push(tmp1); // let pos[0].a = -1 when cut branch
            }
            if(canMoveLeft('A' + i, tmp)){
                tmp1 = moveLeft('A' + i, tmp);
                if(tmp1.pos[0].a == 13){
                    tmp = tmp1;
                    break;
                }
                if(tmp1.pos[0].a != -1) Q.push(tmp1);
            }
            if(canMoveDown('A' + i, tmp)){
                tmp1 = moveDown('A' + i, tmp);
                if(tmp1.pos[0].a == 13){
                    tmp = tmp1;
                    break;
                }
                if(tmp1.pos[0].a != -1) Q.push(tmp1);
            }
            if(canMoveRight('A' + i, tmp)){
                tmp1 = moveRight('A' + i, tmp);
                if(tmp1.pos[0].a == 13){
                    tmp = tmp1;
                    break;
                }
                if(tmp1.pos[0].a != -1) Q.push(tmp1);
            }
        }
        if(tmp.pos[0].a == 13) break;
    }
    cout << tmp.his.size() << "\n";
    for(int i = 0; i < tmp.his.size(); ++i){
        cout << tmp.his[i].a << " ";
        cout << tmp.his[i].b;
        if(tmp.his[i].c) cout << tmp.his[i].c;
        cout << "\n";
    }
}











