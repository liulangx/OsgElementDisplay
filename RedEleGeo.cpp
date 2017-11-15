#include "RedEleGeo.h"

RedEleGeo::RedEleGeo()
{
    ifstream fin;
    fin.open("3DsolidWing.inp");
    if(fin.fail())
    {
        cout << "fail" << endl;
    }
    string ch;
    string mark1Sta = "*Node";
    string mark1End = "*Element"; //mark2Sta = mark1End
    string mark2End = "*End Instance";
    int mark1 = 0;
    int mark2 = 0;

    while(getline(fin, ch))
    {
        if((string::npos != ch.find(mark1Sta)) && (0 == mark1))
        {
            mark1 = 1;
            continue;
        }
        else if ((string::npos != ch.find(mark1End)) && (1 == mark1))
        {
            mark1 = 0;
            mark2 = 1;
            continue;
        }
        else if ((string::npos != ch.find(mark2End)) && (1 == mark2))
        {
            mark2 = 0;
            break;
        }


        if(1 == mark1)
        {
            stringstream ss(ch);
            string subStr;
            float x, y, z, num; // !!!!!!!!!!!!!!!!!!!!
            for(int i(0); i < 4; ++i)
            {
                getline(ss, subStr,',');
                num = stringToNum<float>(subStr);
                switch(i)
                {
                case 0:
                    break;
                case 1:
                    x = num;
                    break;
                case 2:
                    y = num;
                    break;
                case 3:
                    z = num;
                    break;
                }
            }
            Node nd;
            nd.x = x;  nd.y = y; nd.z = z;
            m_node.push_back(nd);
        }
        if(1 == mark2)
        {
            stringstream ss(ch);
            string subStr;
            int nL;
            int n1, n2, n3, n4, n5, n6, n7, n8, num;
            for(int i(0); i < 9; ++i)
            {
                getline(ss, subStr,',');
                num = stringToNum<int>(subStr);
                switch(i)
                {
                case 0:
                    nL = num;
                    break;
                case 1:
                    n1 = num;
                    break;
                case 2:
                    n2 = num;
                    break;
                case 3:
                    n3 = num;
                    break;
                case 4:
                    n4 = num;
                    break;
                case 5:
                    n5 = num;
                    break;
                case 6:
                    n6 = num;
                    break;
                case 7:
                    n7 = num;
                    break;
                case 8:
                    n8 = num;
                    break;
                }
            }
            Element El;
            El.n1 = n1;   El.n2 = n2;   El.n3 = n3;
            El.n4 = n4;   El.n5 = n5;   El.n6 = n6;
            El.n7 = n7;   El.n8 = n8;
            m_element[nL] = El;
            m_eleTot = nL;
        }
    }
    fin.close();
}

osg::ref_ptr<osg::Vec3Array> RedEleGeo::createEleGeoArray()
{
    osg::ref_ptr<osg::Vec3Array> vec = new osg::Vec3Array;
    for(int i(1); i <= m_eleTot; ++i)
    {
        vec->push_back(osg::Vec3((m_node[m_element[i].n4-1]).x, (m_node[m_element[i].n4-1]).y, (m_node[m_element[i].n4-1]).z));
        vec->push_back(osg::Vec3((m_node[m_element[i].n3-1]).x, (m_node[m_element[i].n3-1]).y, (m_node[m_element[i].n3-1]).z));
        vec->push_back(osg::Vec3((m_node[m_element[i].n2-1]).x, (m_node[m_element[i].n2-1]).y, (m_node[m_element[i].n2-1]).z));
        vec->push_back(osg::Vec3((m_node[m_element[i].n1-1]).x, (m_node[m_element[i].n1-1]).y, (m_node[m_element[i].n1-1]).z));

        vec->push_back(osg::Vec3((m_node[m_element[i].n5-1]).x, (m_node[m_element[i].n5-1]).y, (m_node[m_element[i].n5-1]).z));
        vec->push_back(osg::Vec3((m_node[m_element[i].n6-1]).x, (m_node[m_element[i].n6-1]).y, (m_node[m_element[i].n6-1]).z));
        vec->push_back(osg::Vec3((m_node[m_element[i].n7-1]).x, (m_node[m_element[i].n7-1]).y, (m_node[m_element[i].n7-1]).z));
        vec->push_back(osg::Vec3((m_node[m_element[i].n8-1]).x, (m_node[m_element[i].n8-1]).y, (m_node[m_element[i].n8-1]).z));

        vec->push_back(osg::Vec3((m_node[m_element[i].n1-1]).x, (m_node[m_element[i].n1-1]).y, (m_node[m_element[i].n1-1]).z));
        vec->push_back(osg::Vec3((m_node[m_element[i].n2-1]).x, (m_node[m_element[i].n2-1]).y, (m_node[m_element[i].n2-1]).z));
        vec->push_back(osg::Vec3((m_node[m_element[i].n6-1]).x, (m_node[m_element[i].n6-1]).y, (m_node[m_element[i].n6-1]).z));
        vec->push_back(osg::Vec3((m_node[m_element[i].n5-1]).x, (m_node[m_element[i].n5-1]).y, (m_node[m_element[i].n5-1]).z));

        vec->push_back(osg::Vec3((m_node[m_element[i].n3-1]).x, (m_node[m_element[i].n3-1]).y, (m_node[m_element[i].n3-1]).z));
        vec->push_back(osg::Vec3((m_node[m_element[i].n4-1]).x, (m_node[m_element[i].n4-1]).y, (m_node[m_element[i].n4-1]).z));
        vec->push_back(osg::Vec3((m_node[m_element[i].n8-1]).x, (m_node[m_element[i].n8-1]).y, (m_node[m_element[i].n8-1]).z));
        vec->push_back(osg::Vec3((m_node[m_element[i].n7-1]).x, (m_node[m_element[i].n7-1]).y, (m_node[m_element[i].n7-1]).z));

        vec->push_back(osg::Vec3((m_node[m_element[i].n2-1]).x, (m_node[m_element[i].n2-1]).y, (m_node[m_element[i].n2-1]).z));
        vec->push_back(osg::Vec3((m_node[m_element[i].n3-1]).x, (m_node[m_element[i].n3-1]).y, (m_node[m_element[i].n3-1]).z));
        vec->push_back(osg::Vec3((m_node[m_element[i].n7-1]).x, (m_node[m_element[i].n7-1]).y, (m_node[m_element[i].n7-1]).z));
        vec->push_back(osg::Vec3((m_node[m_element[i].n6-1]).x, (m_node[m_element[i].n6-1]).y, (m_node[m_element[i].n6-1]).z));

        vec->push_back(osg::Vec3((m_node[m_element[i].n5-1]).x, (m_node[m_element[i].n5-1]).y, (m_node[m_element[i].n5-1]).z));
        vec->push_back(osg::Vec3((m_node[m_element[i].n8-1]).x, (m_node[m_element[i].n8-1]).y, (m_node[m_element[i].n8-1]).z));
        vec->push_back(osg::Vec3((m_node[m_element[i].n4-1]).x, (m_node[m_element[i].n4-1]).y, (m_node[m_element[i].n4-1]).z));
        vec->push_back(osg::Vec3((m_node[m_element[i].n1-1]).x, (m_node[m_element[i].n1-1]).y, (m_node[m_element[i].n1-1]).z));
    }

    return vec;
}
int RedEleGeo::readElementTotalNumber() const
{
    return m_eleTot;
}
