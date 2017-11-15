#ifndef OSGALLKINDTEXT_H
#define OSGALLKINDTEXT_H
#include <osgViewer/Viewer>
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

osg::ref_ptr<osg::Geode> createText();
osg::ref_ptr<osg::Camera> createAllKindText();
osg::ref_ptr<osg::Camera> createHUDText();
#endif // OSGALLKINDTEXT_H
