#ifndef REDELEGEO_H
#define REDELEGEO_H
#include <osg/Geode>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

typedef struct node
{
    float x;
    float y;
    float z;
} Node;
typedef struct element
{
    int n1;
    int n2;
    int n3;
    int n4;
    int n5;
    int n6;
    int n7;
    int n8;
} Element;

using namespace std;

//模板函数：将string类型变量转换为常用的数值类型（此方法具有普遍适用性）
template <class Type>
Type stringToNum(const string& str)
{
    istringstream iss(str);
    Type num;
    iss >> num;
    return num;
}

class RedEleGeo
{

public:

    RedEleGeo();
    osg::ref_ptr<osg::Vec3Array> createEleGeoArray();
    int readElementTotalNumber() const;
private:
    int m_eleTot;
    std::vector<Node> m_node;
    std::map<int, Element> m_element;
};

#endif // REDELEGEO_H
