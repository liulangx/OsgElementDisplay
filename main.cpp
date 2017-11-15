#include <QCoreApplication>
#include <osg/Geometry>
#include <osg/Geode>
#include <osgDB/ReadFile>
#include <osgUtil/SmoothingVisitor>
#include <osgViewer/Viewer>


#include "RedEleGeo.h"
#include "osgallkindtext.h"
#include "axisfirstheaven.h"

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>

#include <osg/Camera>
#include <osg/Matrix>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgText/Text>
#include <osgText/Font>

#include <osgUtil/Optimizer>

#include <iostream>

#include <QTextCodec>


osg::ref_ptr<osg::Geode> createPlaneWing()
{
    /*-----------------read vertices from RedElGeo.cpp---------------------------*/
    RedEleGeo* ReadGeo = new RedEleGeo;
    //Element Geometry Vertices
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;

    vertices = ReadGeo->createEleGeoArray();
    int eleTot = ReadGeo->readElementTotalNumber();
    int eleNodeTot = eleTot * 24;
    //Element normals
    //osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;

    delete ReadGeo;
    /*----------------end--------------------*/

    osg::ref_ptr<osg::Geometry> planeWing = new osg::Geometry;

    //geometry vertices
    planeWing->setVertexArray(vertices.get());
    for(int i(0); i < eleNodeTot; i += 4)
    {
        planeWing->addPrimitiveSet(new osg::DrawArrays(osg::DrawArrays::LINE_LOOP, i, 4));
        //planeWing->addPrimitiveSet(new osg::DrawArrays(osg::DrawArrays::))
        //planeWing->addPrimitiveSet(new osg::DrawArrays(osg::DrawArrays::LINES, i+4, 1));
    }
    osg::ref_ptr<osg::Vec3Array> colors = new osg::Vec3Array;
    colors->push_back(osg::Vec3(0.0, 0.0, 0.0));

    //Color Array
    planeWing->setColorArray(colors.get());
    planeWing->setColorBinding(osg::Geometry::BIND_OVERALL);

    //element
    osg::ref_ptr<osg::Geometry> planeWingElement = new osg::Geometry;
    planeWingElement ->setVertexArray(vertices.get());
    for(int i(0); i < eleNodeTot; i += 4)
    {
        planeWingElement->addPrimitiveSet(new osg::DrawArrays(osg::DrawArrays::QUADS, i, 4));
    }
    //Element Color
    osg::ref_ptr<osg::Vec3Array> colorVertices = new osg::Vec3Array;
    for(int i(0); i<eleNodeTot; ++i)
        colorVertices->push_back(osg::Vec3(0.25, 0.878, 0.804));
    //Color Array
    planeWingElement->setColorArray(colorVertices.get());
    planeWingElement->setColorBinding(osg::Geometry::BIND_PER_VERTEX);


    //自动生成法线
    osgUtil::SmoothingVisitor::smooth(*(planeWingElement.get()));

    osg::ref_ptr<osg::Geode> plane = new osg::Geode;
    plane->addDrawable(planeWingElement.release());
    plane->addDrawable(planeWing.release());
    return plane.get();

}

int main(int argc, char *argv[])
{     

    //QCoreApplication a(argc, argv);
    osg::ref_ptr<osg::Group> root = new osg::Group;

    //osg::ref_ptr<osg::Drawable> planeWingDrawable = createPlaneWing();
    //osg::ref_ptr<osg::Geode> geode =new osg::Geode;
    osg::ref_ptr<osg::Geode> geode = createPlaneWing();
    //geode->addDrawable(planeWingDrawable);

    AxisFirstHeaven *aF = new AxisFirstHeaven;
    int range = 20;
    osg::ref_ptr<osg::Geometry> axis = aF->createOsgAxis(-range, range, -range, range, -range, range);
    delete aF;
    geode->addDrawable(axis.release());

    root->addChild(geode.get());
    root->addChild(createHUDText());

    //public:
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());

    osgViewer::Viewer viewer;
    //shezhi beijing yanse
    viewer.getCamera()->setClearColor(osg::Vec4f(0.46f, 0.30f, 0.22f, 0.5f));
    viewer.setSceneData(root.get());
    viewer.setUpViewInWindow(20,20,1600,900);
    return viewer.run();
    //return a.exec();

}

