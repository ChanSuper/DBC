#include <iostream>
#include <vector>
#include <cstdio>
#include <assert.h>
#include <map>
#include "main.h"
#include "UnionFindSets.h"
using namespace std;

// 待调整的输入参数
const int SIZE = 600;
const int INF = 1<<20;
const double EPS = 0.75, R = 0.1, TOL = 0.5, T=20, iterationNum = 20;
const double MAX_RATIO = 0.97, MIN_D=0.05;
double MIN_STEP = 0;

vector<Point> old_points;
vector<Point> points;
vector<int> neighborNumArray;
vector<Cluster> clusters;
map<int, int> clusterLabel;


void readFile(string name);
void DBC();

void print_points(int);

int main() {
    readFile("/Users/chenchao/Clion_workplace/DBC_v4/R15_cluster=15.txt");
    old_points = points;
    DBC();
    return 0;
}

bool cmp(const Point &x, const Point &y)
{
    return x.moveDist > y.moveDist;
}

void DBC()
{
    init(SIZE);
    int cnt = 1;
    do {
        vector<Point> newPoints;
        int moveNum = 0;
        for(int i=0; i<points.size(); i++) {
            Vector distVec, distVecNoNormalize, finalVec;
            int neighborNum = 1;

            // 计算 基于距离 的移动向量
            for(int j=0; j<points.size(); j++) {
                if(j != i && dist(points[i], points[j]) < EPS) {
                    distVec += normalize(points[j]-points[i]);
                    distVecNoNormalize += points[j] - points[i];
                    ++neighborNum;
                }
            }

            Point newPoint = points[i];

            if(dist(distVec) >= MIN_STEP) {
                finalVec = normalize(distVec) * dist(distVecNoNormalize) / neighborNum;
                newPoint += finalVec;
                newPoint.state = 1;
                ++moveNum;
            }

            assert(newPoint.index == points[i].index);

            newPoint.moveDist = dist(finalVec);
            newPoints.push_back(newPoint);
        }

        // 打印移动后点的情况
        char fileName[100] = "/Users/chenchao/Clion_workplace/DBC_v4/", t[20];
        sprintf(t, "pointsMoved_%d.txt", cnt);
        ofstream out(strcat(fileName, t));
        for(int i=0; i<newPoints.size(); i++) {
            for(int j=0; j<DIM; j++) {
                out << newPoints[i].p[j] << " ";
            }
            out << endl;
        }


        sort(newPoints.begin(), newPoints.end(), cmp);

//        if(moveNum < 20 && MIN_STEP - MIN_D >= 2.9){
////            MIN_STEP *= MAX_RATIO;
//            MIN_STEP -= MIN_D;
//        }
//        cout << moveNum << " " << MIN_STEP << endl;

        vector<Point> realNewPoints;

        for(int i=0; i<newPoints.size(); i++) {
            if(newPoints[i].state == 0) {
                realNewPoints.push_back(newPoints[i]);
            } else if(newPoints[i].state == 1){
                double minn = INF;
                int index = -1;
                for(int j=0; j<newPoints.size(); j++) {
//                    if(j != i && !points[i].isMove && dist(newPoints[i], newPoints[j]) < R) {
                    if(j != i && newPoints[j].state <= 1 && dist(newPoints[i], newPoints[j]) < R && minn > newPoints[j].moveDist) {
                        minn = newPoints[j].moveDist;
                        index = j;
                    }
                }
                if(index == -1) {
                    newPoints[i].state = 0;
                    realNewPoints.push_back(newPoints[i]);
                } else {
                    newPoints[i].state = 2;
                    unite(newPoints[i].index, newPoints[index].index);
                }
            }
        }

        // 新旧替换
        points = realNewPoints;
        cout << cnt << " The size of points is: " << points.size() << endl;
        //输出 细菌 的 新位置
        print_points(cnt);

        cnt++;

    } while(cnt <= iterationNum);

    clusters.clear();
    for(int i=0; i<points.size(); i++) {
        int index = -1, min = INF;
        for(int j=0; j<clusters.size(); j++) {
            double diff = dist(points[i], clusters[j].center);
            if(diff < min) {
                min = diff;
                index = j;
            }
        }
        if(min <= TOL) {
            clusterLabel[points[i].index] = index;
            clusters[index].center = (clusters[index].center * clusters[index].tot + points[i]) / (++clusters[index].tot);
            clusters[index].familyNum += getNum(points[i].index);
        } else {
            clusterLabel[points[i].index] = clusters.size();
            clusters.push_back(Cluster(points[i], 1, getNum(points[i].index)));
        }
    }

    for(int i=0; i<points.size(); i++) {
        if(clusters[clusterLabel[points[i].index]].familyNum < T) {
            clusterLabel[points[i].index] = -1;
        }
    }

    ofstream out("/Users/chenchao/Clion_workplace/DBC_v4/firstBlood.txt");
    for(int i=0; i<old_points.size(); i++) {
        assert(clusterLabel.find(find(i)) != clusterLabel.end());
        out << clusterLabel[find(i)] << endl;
    }
}

void readFile(string name)
{
    ifstream in(name);
    if(!in) {
        cout << "Can't find file!" << endl;
        return;
    }

    points.resize(SIZE);
    for(int i=0; i<points.size(); i++) {
        points[i].index = i;
        for(int j=0; j<DIM; j++) {
            in >> points[i].p[j];
        }
    }
}

void print_points(int cur)
{
    char fileName[100] = "/Users/chenchao/Clion_workplace/DBC_v4/", t[20];
    sprintf(t, "points_%d.txt", cur);
    ofstream out(strcat(fileName, t));
    // 打印点的坐标信息
    for(int i=0; i<points.size(); i++) {
        for(int j=0; j<DIM; j++) {
            out << points[i].p[j] << " ";
        }
        out << endl;
    }
}



