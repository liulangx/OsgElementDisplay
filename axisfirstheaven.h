#ifndef AXISFIRSTHEAVEN_H
#define AXISFIRSTHEAVEN_H
#include "initialInclude.h"
class AxisFirstHeaven
{
public:
    enum AxisColor {red, orange, yellow, green, cyan, blue, purple};

    AxisFirstHeaven();
    ~AxisFirstHeaven();
    //y axis points to the direction into the screen, x axis points rightwards, z axis points upwards
    osg::ref_ptr<osg::Geometry> createOsgAxis(int xMin,int xMax, int yMin, int yMax, int zMin, int zMax);   //openGL coordinate system
    osg::ref_ptr<osg::Geometry> createOsgAxis(int xMin, int xMax,int zMin, int zMax);                       //only the surface showing in the screen without depth(y)
    osg::ref_ptr<osg::Geometry> createOsgAxis();                                                            //defalt openGL coordinate system
    osg::ref_ptr<osg::Geometry> createSimpleOsgAxis(int xMin,int xMax, int yMin, int yMax, int zMin, int zMax);
    //z axis points to the direction outside the screen, x axis points rightwards, y axis points upwards
    //osg::Geometry createFlightAxis(int xMin,int xMax, int yMin, int yMax, int zMin, int zMax);
    //osg::Geometry createFlightAxis(int xMin,int xMax, int yMin, int yMax);
    //set value of the range of axises
    void setXMax(int xMax);
    void setXMin(int xMin);
    void setYMax(int yMax);
    void setYMin(int yMin);
    void setZMax(int zMax);
    void setZMin(int zMin);
    //show value of the range of axises
    int getXMax() const;
    int getXMin() const;
    int getYMax() const;
    int getYMin() const;
    int getZMax() const;
    int getZMin() const;
    //set color (0,0,0) - (1,1,1)
    void setColor(AxisColor color);
    void setColor(float x, float y, float z);
    //set the number of sections for each axis;
    void setSectionAmount(int sectionAmount);
    void setSectionAmount(int xSectionAmount, int ySectionAmount, int zSectionAmount);
    void setXSectionAmount(int xSectionAmount);
    void setYSectionAmount(int ySectionAmount);
    void setZSectionAmount(int zSectionAmount);
protected:
private:
    //the final osg::Geometry which will be used as a node for osg
    osg::ref_ptr<osg::Geometry> m_axis;
    //define the range of axises
    int m_xMax,m_xMin,m_yMax,m_yMin,m_zMax,m_zMin;
    //color
    float m_color[3];
    //the  number of sections for each axis;
    int m_xSectionAmount;
    int m_ySectionAmount;
    int m_zSectionAmount;
    float m_xMimusPiece;
    float m_yMimusPiece;
    float m_zMimusPiece;
    float m_axisScaleMarkLength;
};

#endif // AXISFIRSTHEAVEN_H
