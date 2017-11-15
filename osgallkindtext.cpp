#include "osgallkindtext.h"

osg::ref_ptr<osg::Camera> createAllKindText()
{
    osg::ref_ptr<osg::Camera> camera = new osg::Camera();
    //设置投影矩阵
    camera->setProjectionMatrix(osg::Matrix::ortho2D(0, 1280, 0, 800));
    camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    //设置视图矩阵
    camera->setViewMatrix(osg::Matrix::identity());
    //清除深度缓存
    camera->setClearMask(GL_DEPTH_BUFFER_BIT);
    //设置渲染顺序，在主摄像机之后渲染
    camera->setRenderOrder(osg::Camera::POST_RENDER);
    //设置为不接收事件，始终不得到焦点
    //camera->setAllowEventFocus(false);
    osg::ref_ptr<osgText::Font> font = osgText::readFontFile("Fonts/arial.ttf");

    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    osg::ref_ptr<osg::StateSet> stateset = geode->getOrCreateStateSet();
    stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    //设置文字输出的格式
    //设置格式为LEFT_TO_RIGHT,从左到右
    {
        osg::ref_ptr<osgText::Text> text = new osgText::Text;
        text-> setFont(font.get());
        text-> setColor(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));
        text-> setCharacterSize(20.0f);
        text->setPosition(osg::Vec3(50.0f, 750.0f, 0.0f));
        text->setLayout(osgText::Text::LEFT_TO_RIGHT);
        text->setText("text->setLayout(osgText::Text::LEFT_TO_RIGHT);");
        geode->addDrawable(text.get());
    }
    /*//设置格式为RIGHT_TO_LEFT,从右到左
    {
        osg::ref_ptr<osgText::Text> text = new osgText::Text;
        text->setFont(font.get());
        text->setColor(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));
        text-> setCharacterSize(30.0f);
        text->setPosition(osg::Vec3(1200.0f, 750.0f, 0.0f));
        text->setLayout(osgText::Text::RIGHT_TO_LEFT);
        text->setAlignment(osgText::Text::RIGHT_BASE_LINE);
        text->setText("text->setLayout(osgText::Text::RIGHT_TO_LEFT);");
        geode->addDrawable(text.get());
    }
    //设置格式为VERTICAL，垂直
    {
        osg::ref_ptr<osgText::Text> text = new osgText::Text;
        text->setFont(font.get());
        text->setColor(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));
        text-> setCharacterSize(20.0f);
        text->setPosition(osg::Vec3(5.0f, 750.0f, 0.0f));
        text->setLayout(osgText::Text::VERTICAL);
        text->setText("text->setLayout(osgText::Text::VERTICAL);");
        geode->addDrawable(text.get());
    }
    //设置阴影
    {
        osg::ref_ptr<osgText::Text> text = new osgText::Text;
        text->setFont(font.get());
        text->setColor(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));
        text-> setCharacterSize(40.0f);
        text->setPosition(osg::Vec3(100.0f, 650.0f, 0.0f));
        text->setBackdropType(osgText::Text::DROP_SHADOW_BOTTOM_RIGHT);
        text->setBackdropColor(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
        text->setBackdropOffset(0.1f, -0.1f);

        text->setText("text->setLayout(osgText::Text::DROP_SHADOW_BOTTOM_RIGHT);");
        geode->addDrawable(text.get());
    }
    //设置边框
    {
        osg::ref_ptr<osgText::Text> text = new osgText::Text;
        text->setFont(font.get());
        text->setColor(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));
        text-> setCharacterSize(30.0f);
        text->setPosition(osg::Vec3(100.0f, 450.0f, 0.0f));
        text->setDrawMode(osgText::Text::TEXT | osgText::Text::BOUNDINGBOX | osgText::Text::ALIGNMENT);

        text->setText("text->setDrawMode(osgText::Text::TEXT | osgText::Text::BOUNDINGBOX | osgText::Text::ALIGNMENT);");
        geode->addDrawable(text.get());
    }
    //设置颜色倾斜模式
    {
        osg::ref_ptr<osgText::Text> text = new osgText::Text;
        text->setFont(font.get());
        text->setColor(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));
        text-> setCharacterSize(30.0f);
        text->setPosition(osg::Vec3(100.0f, 250.0f, 0.0f));

        text->setColorGradientMode(osgText::Text::PER_CHARACTER);
        text->setColorGradientCorners(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f), osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f),
                                      osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f), osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));


        text->setText("text->setColorGradientMode(osgText::Text::PER_CHARACTER);");
        geode->addDrawable(text.get());
    }*/


    camera->addChild(geode.get());
    return camera.get();

}

osg::ref_ptr<osg::Geode> createText()
{
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    osg::ref_ptr<osgText::Text> text =  new osgText::Text;
    osg::ref_ptr<osgText::Font> font = new osgText::Font();

    font = osgText::readFontFile("simhei.ttf");

    text->setFont(font.get());
    text->setText(L"我的世界只有你一个人，从来都是这样的");
    text->setCharacterSize(2.0f);
    text->setAutoRotateToScreen(true);
    text->setColor(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
    osg::Vec3f position = osg::Vec3f(0.0f, 0.0f, 0.0f);
    text->setPosition(position);
    text->setAlignment(osgText::Text::CENTER_BOTTOM);
    text->setAxisAlignment(osgText::Text::SCREEN);

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    geode->addDrawable(text.get());
    return geode.get();
}

osg::ref_ptr<osg::Camera> createHUDText()
{
    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setProjectionMatrix(osg::Matrix::ortho2D(0, 1280, 0, 800));
    camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    camera->setViewMatrix(osg::Matrix::identity());
    camera->setClearMask(GL_DEPTH_BUFFER_BIT);
    camera->setAllowEventFocus(false);

    osg::ref_ptr<osg::Geode> geode =  new osg::Geode();
    osg::ref_ptr<osg::StateSet> stateset = geode->getOrCreateStateSet();
    stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    stateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
    osg::ref_ptr<osgText::Text> text = new osgText::Text;
    osg::ref_ptr<osgText::Font> font = new osgText::Font;
    font = osgText::readFontFile("Fonts/simhei.ttf");
    text -> setFont(font.get());
    text -> setText(L"3D solid Wing C3D8R：");
    text -> setPosition(osg::Vec3(100.0f, 600.0f, 0.0f));
    text -> setCharacterSize(40.0f);
    text -> setColor(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
    text -> setDrawMode(osgText::Text::TEXT | osgText::Text::BOUNDINGBOX);
    geode -> addDrawable(text.get());
    camera ->addChild(geode.get());
    return camera.get();
}
