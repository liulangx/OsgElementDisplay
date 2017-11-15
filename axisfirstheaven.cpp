#include "axisfirstheaven.h"

AxisFirstHeaven::AxisFirstHeaven()
    :m_axis(new osg::Geometry),
    m_xMax(500),
    m_xMin(-500),
    m_yMax(500),
    m_yMin(-500),
    m_zMax(500),
    m_zMin(-500),
    m_color({192.0/255.0,192.0/255.0,192.0/255.0}),
    m_xSectionAmount(20),
    m_ySectionAmount(20),
    m_zSectionAmount(20),
    m_xMimusPiece(0.2),
    m_yMimusPiece(0.2),
    m_zMimusPiece(0.2),
    m_axisScaleMarkLength(0.01)
{
}

AxisFirstHeaven::~AxisFirstHeaven()
{
}

osg::ref_ptr<osg::Geometry> AxisFirstHeaven::createOsgAxis(int xMin,int xMax, int yMin, int yMax, int zMin, int zMax)
{
    setXMax(xMax);  setXMin(xMin);
    setYMax(yMax);  setYMin(yMin);
    setZMax(zMax);  setZMin(zMin);
    const int xWidth = getXMax() - getXMin();
    const int yWidth = getYMax() - getYMin();
    const int zWidth = getZMax() - getZMin();
    //geometry Vertices
    osg::ref_ptr<osg::Vec3Array> axisVertices = new osg::Vec3Array(xWidth*3+ yWidth*3+zWidth*3+15);
    //divide the x axis into xSection pieces, each section length is xWidth / xSection,
    //and the xlabel can be written as i*xWidth / xSection, i = 0, 1, 2 ... 20
    const int xSection = m_xSectionAmount;
    const float xMimusPiece = m_xMimusPiece;
    const float axisScaleMarkLength = m_axisScaleMarkLength;
    for(int i(0); i<xWidth; ++i)
    {
        (*axisVertices)[3*i    ].set(i + xMin       , 0.0   ,   0.0);
        (*axisVertices)[3*i+1].set(i + xMin + 1 , 0.0   ,   0.0);

        if( 0 == (i+xMin+1) % (xWidth / xSection))
            (*axisVertices)[3*i+2].set( i+xMin + 1, 0.0     , axisScaleMarkLength*xWidth       );
        else if(0 == (i+xMin + 1)%10)
            (*axisVertices)[3*i+2].set( i+xMin + 1, 0.0     , 2*xMimusPiece  );
        else
            (*axisVertices)[3*i+2].set( i+xMin + 1, 0.0     , xMimusPiece       );
    }
    (*axisVertices)[3*xWidth     ].set(float(xMax)                               , 0.0    ,               0.0);
    (*axisVertices)[3*xWidth +1].set(float(xMax)*21.0/20.0             , 0.0    ,               0.0);
    (*axisVertices)[3*xWidth +2].set(float(xMax)*21.0/20.0 * 0.95 , 0.0     ,  0.05*xMax);
    (*axisVertices)[3*xWidth +3].set(float(xMax)*21.0/20.0            , 0.0     ,               0.0);
    (*axisVertices)[3*xWidth +4].set(float(xMax)*21.0/20.0 * 0.95 , 0.0     , -0.05*xMax);

    //divide the y axis into ySection pieces, each section length is yWidth / ySection,
    //and the ylabel can be written as i*yWidth / ySection, i = 0, 1, 2 ... 20
    const int       ySection            = m_ySectionAmount;
    const float    yMimusPiece    = m_yMimusPiece;

    for(int i(0); i<yWidth; ++i)
    {
        (*axisVertices)[3*i    + 3*xWidth + 5].set(0.0,       i+yMin,         0.0);
        (*axisVertices)[3*i+1+ 3*xWidth + 5].set(0.0,       i + yMin + 1, 0.0);
        if( 0 == (i+yMin+1) % (yWidth / ySection))
            (*axisVertices)[3*i+2+ 3*xWidth + 5].set( axisScaleMarkLength*yWidth       , i+yMin + 1, 0.0);
        else if( 0 == (i+yMin + 1)%10 )
            (*axisVertices)[3*i+2+ 3*xWidth + 5].set( 2*yMimusPiece ,  i+yMin + 1, 0.0 );
        else
            (*axisVertices)[3*i+2+ 3*xWidth + 5].set(yMimusPiece       , i+yMin + 1, 0.0);
    }
    (*axisVertices)[3*yWidth     + 3*xWidth + 5].set(0.0                , float(yMax)                              , 0.0);
    (*axisVertices)[3*yWidth +1+ 3*xWidth + 5].set(0.0                , float(yMax)*21.0/20.0            , 0.0);
    (*axisVertices)[3*yWidth +2+ 3*xWidth + 5].set(0.05*yMax   , float(yMax)*21.0/20.0 * 0.95, 0.0);
    (*axisVertices)[3*yWidth +3+ 3*xWidth + 5].set(0.0                , float(yMax)*21.0/20.0,             0.0);
    (*axisVertices)[3*yWidth +4+ 3*xWidth + 5].set(-0.05*yMax  , float(yMax)*21.0/20.0 * 0.95, 0.0);
    //divide the z axis into 20 pieces, each section length is zWidth / zSection,
    //and the zlabel can be written as i*zWidth / zSection, i = 0, 1, 2 ... 20
    const int       zSection        = m_zSectionAmount;
    const float   zMimusPiece = m_zMimusPiece;

    for(int i(0); i<zWidth; ++i)
    {
        (*axisVertices)[3*i    + 3*xWidth + 5+ 3*yWidth + 5].set(0.0,  0.0, i + zMin       );
        (*axisVertices)[3*i+1+ 3*xWidth + 5+ 3*yWidth + 5].set(0.0,  0.0, i + zMin + 1);
        if(0 == (i+zMin+1) % (zWidth / zSection) )
            (*axisVertices)[3*i+2+ 3*xWidth + 5+ 3*yWidth + 5].set( axisScaleMarkLength*zWidth     ,  0.0,i+zMin + 1);
        else if(0 == (i+zMin + 1)%10)
            (*axisVertices)[3*i+2+ 3*xWidth + 5+ 3*yWidth + 5].set( 2*zMimusPiece,  0.0,i+zMin + 1 );
        else
            (*axisVertices)[3*i+2+ 3*xWidth + 5+ 3*yWidth + 5].set(zMimusPiece      ,  0.0,i+zMin + 1);
    }
    (*axisVertices)[3*zWidth     + 3*xWidth + 5 + 3*yWidth + 5].set( 0.0                                  ,            0.0,float(zMax));
    (*axisVertices)[3*zWidth +1+ 3*xWidth + 5 + 3*yWidth + 5].set( 0.0,               0.0, float(zMax)*21.0/20.0             );
    (*axisVertices)[3*zWidth +2+ 3*xWidth + 5 + 3*yWidth + 5].set( 0.05*zMax,  0.0,  float(zMax)*21.0/20.0 * 0.95);
    (*axisVertices)[3*zWidth +3+ 3*xWidth + 5 + 3*yWidth + 5].set( 0.0             ,  0.0,  float(zMax)*21.0/20.0            );
    (*axisVertices)[3*zWidth +4+ 3*xWidth + 5 + 3*yWidth + 5].set(-0.05*zMax, 0.0,  float(zMax)*21.0/20.0 * 0.95);
    osg::ref_ptr<osg::Vec3Array> colorAxisVertices = new osg::Vec3Array(1);
    (*colorAxisVertices)[0].set(m_color[0],m_color[1],m_color[2]);

    //osg::ref_ptr<osg::Geometry> axisXYZ = new osg::Geometry;
    m_axis->setVertexArray(axisVertices.get());
    m_axis->addPrimitiveSet(new osg::DrawArrays(osg::DrawArrays::LINE_STRIP, 0,3*xWidth+5));
    m_axis->addPrimitiveSet(new osg::DrawArrays(osg::DrawArrays::LINE_STRIP, 3*xWidth+5,3*yWidth+5));
    m_axis->addPrimitiveSet(new osg::DrawArrays(osg::DrawArrays::LINE_STRIP, 3*xWidth+5+3*yWidth+5,3*zWidth+5));

    m_axis->setInitialBound(osg::BoundingBox(osg::Vec3(xMin,yMin,zMin),osg::Vec3(xMax,yMax,zMax)));
    m_axis->setUseDisplayList(false);
    m_axis->setUseVertexBufferObjects(true);
    m_axis->setColorArray(colorAxisVertices.get());
    m_axis->setColorBinding(osg::Geometry::BIND_OVERALL);
    return m_axis;
}
osg::ref_ptr<osg::Geometry> AxisFirstHeaven::createOsgAxis()
{
    int xMax = getXMax(); int xMin = getXMin();
    int yMax = getYMax(); int yMin = getYMin();
    int zMax = getZMax(); int zMin = getZMin();
    const int xWidth = xMax - xMin;
    const int yWidth = yMax - yMin;
    const int zWidth = zMax - zMin;

    osg::ref_ptr<osg::Vec3Array> axisVertices = new osg::Vec3Array(xWidth*3+ yWidth*3+zWidth*3+15);

    const int xSection = m_xSectionAmount;
    const float xMimusPiece = m_xMimusPiece;
    const float axisScaleMarkLength = m_axisScaleMarkLength;
    for(int i(0); i<xWidth; ++i)
    {
        (*axisVertices)[3*i    ].set(i + xMin, 0.0, 0.0);
        (*axisVertices)[3*i+1].set(i + xMin + 1, 0.0, 0.0);
        if(0 == (i+xMin+1) % (xWidth / xSection) )
            (*axisVertices)[3*i+2].set( i+xMin + 1, 0.0, axisScaleMarkLength*xWidth);
        else if(0 == (i+xMin + 1)%10)
            (*axisVertices)[3*i+2].set( i+xMin + 1, 0.0, 2*xMimusPiece);
        else
            (*axisVertices)[3*i+2].set( i+xMin + 1, 0.0, xMimusPiece);
    }
    (*axisVertices)[3*xWidth    ].set(float(xMax)                               , 0.0,               0.0);
    (*axisVertices)[3*xWidth +1].set(float(xMax)*21.0/20.0            , 0.0,               0.0);
    (*axisVertices)[3*xWidth +2].set(float(xMax)*21.0/20.0 * 0.95, 0.0, 0.05*xMax);
    (*axisVertices)[3*xWidth +3].set(float(xMax)*21.0/20.0           , 0.0,               0.0);
    (*axisVertices)[3*xWidth +4].set(float(xMax)*21.0/20.0 * 0.95, 0.0,-0.05*xMax);
    //divide the y axis into 20 pieces
    //each section length is yWidth / ySection,
    //and the ylabel can be written as i*yWidth / ySection
    //i = 0, 1, 2 ... 20

    const int ySection = 20;
    const float yMimusPiece = m_yMimusPiece;

    for(int i(0); i<yWidth; ++i)
    {
        (*axisVertices)[3*i    + 3*xWidth + 5].set(0.0,       i+yMin        , 0.0);
        (*axisVertices)[3*i+1+ 3*xWidth + 5].set(0.0,       i + yMin + 1, 0.0);
        if(0 == (i+yMin+1) % (yWidth / ySection) )
            (*axisVertices)[3*i+2+ 3*xWidth + 5].set( axisScaleMarkLength*yWidth,i+yMin + 1, 0.0);
        else if(0 == (i+yMin + 1)%10)
            (*axisVertices)[3*i+2+ 3*xWidth + 5].set( 2*yMimusPiece             , i+yMin + 1, 0.0 );
        else
            (*axisVertices)[3*i+2+ 3*xWidth + 5].set(yMimusPiece                , i+yMin + 1, 0.0);
    }
    (*axisVertices)[3*yWidth     + 3*xWidth + 5].set(0.0               , float(yMax)                           , 0.0);
    (*axisVertices)[3*yWidth +1+ 3*xWidth + 5].set(0.0              , float(yMax)*21.0/20.0          , 0.0);
    (*axisVertices)[3*yWidth +2+ 3*xWidth + 5].set(0.05*yMax, float(yMax)*21.0/20.0 * 0.95, 0.0 );
    (*axisVertices)[3*yWidth +3+ 3*xWidth + 5].set( 0.0             , float(yMax)*21.0/20.0           , 0.0);
    (*axisVertices)[3*yWidth +4+ 3*xWidth + 5].set(-0.05*yMax, float(yMax)*21.0/20.0 * 0.95,0.0);
    //divide the z axis into 20 pieces
    //each section length is zWidth / zSection,
    //and the zlabel can be written as i*zWidth / zSection
    //i = 0, 1, 2 ... 20

    const int zSection = m_zSectionAmount;
    const float zMimusPiece = m_zMimusPiece;

    for(int i(0); i<zWidth; ++i)
    {
        (*axisVertices)[3*i    + 3*xWidth + 5+ 3*yWidth + 5].set(0.0,       0.0,  i+zMin);
        (*axisVertices)[3*i+1+ 3*xWidth + 5+ 3*yWidth + 5].set(0.0,       0.0,  i + zMin + 1);
        if(0 == (i+zMin+1) % (zWidth / zSection) )
            (*axisVertices)[3*i+2+ 3*xWidth + 5+ 3*yWidth + 5].set( axisScaleMarkLength*zWidth, 0.0,      i+zMin + 1);
        else if(0 == (i+zMin + 1)%10)
            (*axisVertices)[3*i+2+ 3*xWidth + 5+ 3*yWidth + 5].set( 2*zMimusPiece             ,  0.0,     i+zMin + 1 );
        else
            (*axisVertices)[3*i+2+ 3*xWidth + 5+ 3*yWidth + 5].set(zMimusPiece                ,  0.0,    i+zMin + 1);
    }
    (*axisVertices)[3*zWidth     + 3*xWidth + 5 + 3*yWidth + 5].set( 0.0             ,  0.0,float(zMax));
    (*axisVertices)[3*zWidth +1+ 3*xWidth + 5 + 3*yWidth + 5].set(  0.0            , 0.0, float(zMax)*21.0/20.0);
    (*axisVertices)[3*zWidth +2+ 3*xWidth + 5 + 3*yWidth + 5].set( 0.05*zMax, 0.0, float(zMax)*21.0/20.0 * 0.95);
    (*axisVertices)[3*zWidth +3+ 3*xWidth + 5 + 3*yWidth + 5].set(  0.0            , 0.0, float(zMax)*21.0/20.0);
    (*axisVertices)[3*zWidth +4+ 3*xWidth + 5 + 3*yWidth + 5].set(-0.05*zMax, 0.0, float(zMax)*21.0/20.0 * 0.95);
    osg::ref_ptr<osg::Vec3Array> colorAxisVertices = new osg::Vec3Array(1);
    //silver
    (*colorAxisVertices)[0].set(m_color[0],m_color[1],m_color[2]);

    //osg::ref_ptr<osg::Geometry> axisXYZ = new osg::Geometry;
    m_axis->setVertexArray(axisVertices.get());
    m_axis->addPrimitiveSet(new osg::DrawArrays(osg::DrawArrays::LINE_STRIP,0,3*xWidth+5));
    m_axis->addPrimitiveSet(new osg::DrawArrays(osg::DrawArrays::LINE_STRIP,3*xWidth+5,3*yWidth+5));
    m_axis->addPrimitiveSet(new osg::DrawArrays(osg::DrawArrays::LINE_STRIP,3*xWidth+5+3*yWidth+5,3*zWidth+5));

    m_axis->setInitialBound(osg::BoundingBox(osg::Vec3(xMin,yMin,zMin),osg::Vec3(xMax,yMax,zMax)));
    m_axis->setUseDisplayList(false);
    m_axis->setUseVertexBufferObjects(true);
    m_axis->setColorArray(colorAxisVertices.get());
    m_axis->setColorBinding(osg::Geometry::BIND_OVERALL);
    return m_axis;
}
osg::ref_ptr<osg::Geometry> AxisFirstHeaven::createOsgAxis(int xMin, int xMax,int zMin, int zMax)
{
    setXMax(xMax); setXMin(xMin);
    setZMax(zMax); setZMin(zMin);
    const int xWidth = getXMax() - getXMin();
    const int zWidth = getZMax() - getZMin();
    //geometry Vertices
    osg::ref_ptr<osg::Vec3Array> axisVertices = new osg::Vec3Array(xWidth*3+ zWidth*3+10);

    const int xSection = m_xSectionAmount;
    const float xMimusPiece = m_xMimusPiece;
    const float axisScaleMarkLength = m_axisScaleMarkLength;
    for(int i(0); i<xWidth; ++i)
    {
        (*axisVertices)[3*i    ].set(i + xMin, 0.0, 0.0);
        (*axisVertices)[3*i+1].set(i + xMin + 1, 0.0, 0.0);
        if(0 == (i+xMin+1) % (xWidth / xSection) )
            (*axisVertices)[3*i+2].set( i+xMin + 1, 0.0, axisScaleMarkLength*xWidth);
        else if(0 == (i+xMin + 1)%10)
            (*axisVertices)[3*i+2].set( i+xMin + 1, 0.0, 2*xMimusPiece);
        else
            (*axisVertices)[3*i+2].set( i+xMin + 1, 0.0, xMimusPiece);
    }
    (*axisVertices)[3*xWidth    ].set(float(xMax)                               , 0.0,               0.0);
    (*axisVertices)[3*xWidth +1].set(float(xMax)*21.0/20.0             , 0.0,               0.0);
    (*axisVertices)[3*xWidth +2].set(float(xMax)*21.0/20.0 * 0.95, 0.0, 0.05*xMax);
    (*axisVertices)[3*xWidth +3].set(float(xMax)*21.0/20.0           , 0.0,               0.0);
    (*axisVertices)[3*xWidth +4].set(float(xMax)*21.0/20.0 * 0.95, 0.0,-0.05*xMax);

    const int zSection = m_zSectionAmount;
    const float zMimusPiece = m_zMimusPiece;

    for(int i(0); i<zWidth; ++i)
    {
        (*axisVertices)[3*i    + 3*xWidth + 5].set(0.0,       0.0, i+zMin);
        (*axisVertices)[3*i+1+ 3*xWidth + 5].set(0.0,       0.0, i + zMin + 1);
        if(0 == (i+zMin+1) % (zWidth / zSection) )
            (*axisVertices)[3*i+2+ 3*xWidth + 5].set( axisScaleMarkLength*zWidth, 0.0,  i+zMin + 1);
        else if(0 == (i+zMin + 1)%10)
            (*axisVertices)[3*i+2+ 3*xWidth + 5].set( 2*zMimusPiece             , 0.0,  i+zMin + 1 );
        else
            (*axisVertices)[3*i+2+ 3*xWidth + 5].set(zMimusPiece                , 0.0,   i+zMin + 1);
    }
    (*axisVertices)[3*zWidth     + 3*xWidth + 5 ].set(0.0             , 0.0, float(zMax));
    (*axisVertices)[3*zWidth +1+ 3*xWidth + 5].set(  0.0            , 0.0, float(zMax)*21.0/20.0);
    (*axisVertices)[3*zWidth +2+ 3*xWidth + 5].set( 0.05*zMax, 0.0, float(zMax)*21.0/20.0 * 0.95);
    (*axisVertices)[3*zWidth +3+ 3*xWidth + 5].set( 0.0             , 0.0, float(zMax)*21.0/20.0);
    (*axisVertices)[3*zWidth +4+ 3*xWidth + 5].set(-0.05*zMax, 0.0, float(zMax)*21.0/20.0 * 0.95);
    osg::ref_ptr<osg::Vec3Array> colorAxisVertices = new osg::Vec3Array(1);
    (*colorAxisVertices)[0].set(m_color[0],m_color[1],m_color[2]);
    //osg::ref_ptr<osg::Geometry> axisXYZ = new osg::Geometry;
    m_axis->setVertexArray(axisVertices.get());
    m_axis->addPrimitiveSet(new osg::DrawArrays(osg::DrawArrays::LINE_STRIP,0,3*xWidth+5));
    m_axis->addPrimitiveSet(new osg::DrawArrays(osg::DrawArrays::LINE_STRIP,3*xWidth+5,3*zWidth+5));

    m_axis->setInitialBound(osg::BoundingBox(osg::Vec3(xMin,-500,zMin),osg::Vec3(xMax,500,zMax)));
    m_axis->setUseDisplayList(false);
    m_axis->setUseVertexBufferObjects(true);
    m_axis->setColorArray(colorAxisVertices.get());
    m_axis->setColorBinding(osg::Geometry::BIND_OVERALL);
    return m_axis;
}
osg::ref_ptr<osg::Geometry> AxisFirstHeaven::createSimpleOsgAxis(int xMin,int xMax, int yMin, int yMax, int zMin, int zMax)
{
    //x
    osg::ref_ptr<osg::Vec3Array> axisVertices = new osg::Vec3Array(15);
    (*axisVertices)[0].set(xMax*0.95, 0.0,   0.05*xMax);
    (*axisVertices)[1].set(xMax          , 0.0,               0.0 );
    (*axisVertices)[2].set(xMin           , 0.0,               0.0 );
    (*axisVertices)[3].set(xMax          , 0.0,               0.0 );
    (*axisVertices)[4].set(xMax*0.95,  0.0, -0.05*xMax);
    //y
    (*axisVertices)[5].set(-zMax*0.05, 0.0,   0.95*zMax);
    (*axisVertices)[6].set(              0.0, 0.0,             zMax);
    (*axisVertices)[7].set(              0.0, 0.0,             zMin );
    (*axisVertices)[8].set(              0.0, 0.0,             zMax);
    (*axisVertices)[9].set(  zMax*0.05, 0.0,   0.95*zMax);
    //z
    (*axisVertices)[10].set(              0.0, 0.95*yMax,-yMax*0.05);
    (*axisVertices)[11].set(              0.0, yMax,             0.0);
    (*axisVertices)[12].set(              0.0, yMin,             0.0);
    (*axisVertices)[13].set(              0.0, yMax,             0.0);
    (*axisVertices)[14].set(              0.0, 0.95*yMax, yMax*0.05);

    osg::ref_ptr<osg::Vec3Array> colorAxisVertices = new osg::Vec3Array(1);
    (*colorAxisVertices)[0].set(m_color[0],m_color[1],m_color[2]);

    m_axis->setVertexArray(axisVertices.get());
    m_axis->addPrimitiveSet(new osg::DrawArrays(osg::DrawArrays::LINE_STRIP,0,5));
    m_axis->addPrimitiveSet(new osg::DrawArrays(osg::DrawArrays::LINE_STRIP,5,5));
    m_axis->addPrimitiveSet(new osg::DrawArrays(osg::DrawArrays::LINE_STRIP,10,5));

    m_axis->setInitialBound(osg::BoundingBox(osg::Vec3(xMin,yMin,zMin),osg::Vec3(xMax,yMax,zMax)));
    m_axis->setUseDisplayList(false);
    m_axis->setUseVertexBufferObjects(true);
    m_axis->setColorArray(colorAxisVertices.get());
    m_axis->setColorBinding(osg::Geometry::BIND_OVERALL);

    return m_axis;
}

void AxisFirstHeaven::setColor(float x, float y, float z)
{
    m_color[0] = x;
    m_color[1] = y;
    m_color[2] = z;
}
void AxisFirstHeaven::setColor(AxisColor color)
{
    switch(color)
    {
    case red:
        m_color[0] = 1.0;
        m_color[1] = 0.0;
        m_color[2] = 0.0;
        break;
    case orange:
        m_color[0] = 1.0;
        m_color[1] = 165.0/255.0;
        m_color[2] = 0.0;
        break;
    case yellow:
        m_color[0] = 1.0;
        m_color[1] = 1.0;
        m_color[2] = 0.0;
        break;
    case green:
        m_color[0] = 0.0;
        m_color[1] = 1.0;
        m_color[2] = 0.0;
        break;
    case cyan:
        m_color[0] = 0.0;
        m_color[1] = 1.0;
        m_color[2] = 1.0;
        break;
    case blue:
        m_color[0] = 0.0;
        m_color[1] = 0.0;
        m_color[2] = 1.0;
        break;
    case purple:
        m_color[0] = 139.0/255.0;
        m_color[1] = 0.0;
        m_color[2] = 1.0;
        break;
    }
}

void AxisFirstHeaven::setSectionAmount(int xSectionAmount, int ySectionAmount, int zSectionAmount)
{
    m_xSectionAmount = xSectionAmount;
    m_ySectionAmount = ySectionAmount;
    m_zSectionAmount = zSectionAmount;
}
void AxisFirstHeaven::setSectionAmount(int sectionAmount)
{
    m_xSectionAmount = sectionAmount;
    m_ySectionAmount = sectionAmount;
    m_zSectionAmount = sectionAmount;
}

void AxisFirstHeaven::setXSectionAmount(int xSectionAmount)
{
    m_xSectionAmount = xSectionAmount;
}
void AxisFirstHeaven::setYSectionAmount(int ySectionAmount)
{
    m_ySectionAmount = ySectionAmount;
}
void AxisFirstHeaven::setZSectionAmount(int zSectionAmount)
{
    m_zSectionAmount = zSectionAmount;
}

void AxisFirstHeaven::setXMax(int xMax)
{
    m_xMax = xMax;
}
void AxisFirstHeaven::setXMin(int xMin)
{
    m_xMin = xMin;
}
void AxisFirstHeaven::setYMax(int yMax)
{
    m_yMax = yMax;
}
void AxisFirstHeaven::setYMin(int yMin)
{
    m_yMin = yMin;
}
void AxisFirstHeaven::setZMax(int zMax)
{
    m_zMax = zMax;
}
void AxisFirstHeaven::setZMin(int zMin)
{
    m_zMin = zMin;
}
int AxisFirstHeaven::getXMax() const
{
    return m_xMax;
}
int AxisFirstHeaven::getXMin() const
{
    return m_xMin;
}
int AxisFirstHeaven::getYMax()const
{
    return m_yMax;
}
int AxisFirstHeaven::getYMin() const
{
    return m_yMin;
}
int  AxisFirstHeaven::getZMax() const
{
    return m_zMax;
}
int AxisFirstHeaven::getZMin() const
{
    return m_zMin;
}
