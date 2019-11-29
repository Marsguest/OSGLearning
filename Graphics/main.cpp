#include <windows.h> 
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgGA/GUIEventAdapter>
#include <osgGA/TrackballManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osgUtil/Optimizer>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Material>
#include <osg/StateSet>
#include <osg/Image>
#include <osg/Texture2D>
#include <iostream>
#include <osg/lineWidth>
osg::ref_ptr<osg::Geode> CreateBox() {
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	osg::ref_ptr <osg::TessellationHints> hints = new osg::TessellationHints;
	osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable(new osg::Box(osg::Vec3(0.0,0.0,0.0),10.0,10.0,10.0),hints.get());
	osg::ref_ptr<osg::Material> material = new osg::Material;
	osg::ref_ptr<osg::Texture2D> texture2D = new osg::Texture2D;
	osg::ref_ptr<osg::Image> image;

	
	//设置材质
	shape->setColor(osg::Vec4(0.5, 0.5, 0.5, 1.0));
	//设置精度
	hints->setDetailRatio(0.8);
	//设置材质
	material->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0, 1.0, 1.0, 1.0));
	material->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0, 1.0, 1.0, 1.0));
	material->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0, 1.0, 1.0, 1.0));
	material->setShininess(osg::Material::FRONT_AND_BACK, 60.0);
	//设置纹理
	image = osgDB::readImageFile("3.png");
	if (image.valid()) {
		texture2D->setImage(image.get());
	}

	//set state
	geode->getOrCreateStateSet()->setAttributeAndModes(material.get(),osg::StateAttribute::ON);
	geode->getOrCreateStateSet()->setMode(GL_BLEND,osg::StateAttribute::ON);
	geode->getOrCreateStateSet()->setTextureAttributeAndModes(0,texture2D.get(), osg::StateAttribute::ON);
	geode->addDrawable(shape.get());
	return geode;
}

//创建简单图元
osg::ref_ptr<osg::Geode> CreateSimple() {
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

	geode->addDrawable(geom.get());
	//打开透明度
	geode->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);


	//申请一些顶点
	osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array;
	//申请颜色
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
	//申请法向量
	osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
	//限制线宽
	osg::ref_ptr<osg::LineWidth> width = new osg::LineWidth;


	//设置线宽
	width->setWidth(15.0);
	geode->getOrCreateStateSet()->setAttributeAndModes(width.get(), osg::StateAttribute::ON);
	//设置顶点
	geom->setVertexArray(coords.get());
	//设置顶点的关联方式
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::Mode::LINE_LOOP, 0, 4));
	//设置顶点颜色
	geom->setColorArray(colors.get());
	geom->setColorBinding(osg::Geometry::AttributeBinding::BIND_PER_VERTEX);
	//设置法向量
	geom->setNormalArray(normals.get());
	geom->setNormalBinding(osg::Geometry::AttributeBinding::BIND_OVERALL);

	//设置点坐标
	#pragma region Vertex Data
		coords->push_back(osg::Vec3(-10.0,0.0,-10.0));
		coords->push_back(osg::Vec3(10.0, 0.0, -10.0));
		coords->push_back(osg::Vec3(10.0, 0.0, 10.0));
		coords->push_back(osg::Vec3(-10.0, 0.0, 10.0));
	#pragma endregion		
	//set color
#pragma region Color Data
	colors->push_back(osg::Vec4(1.0, 0.0, 0.0,0.5));
	colors->push_back(osg::Vec4(0.0, 1.0, 0.0, 0.5));
	colors->push_back(osg::Vec4(0.0, 0.0, 1.0, 0.5));
	colors->push_back(osg::Vec4(1.0, 1.0, 0.0, 0.5));
#pragma endregion
	//压入一个法向量
	normals->push_back(osg::Vec3(0.0, -1.0, 0.0));
	



	return geode;
}

int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;

	osg::ref_ptr<osg::Group> group = new osg::Group;
	group->addChild(osgDB::readNodeFile("glider.osg"));
	group->addChild(CreateSimple());
	

	viewer->setSceneData(group.get());

	viewer->run();
	return 0;
}