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

	
	//���ò���
	shape->setColor(osg::Vec4(0.5, 0.5, 0.5, 1.0));
	//���þ���
	hints->setDetailRatio(0.8);
	//���ò���
	material->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0, 1.0, 1.0, 1.0));
	material->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0, 1.0, 1.0, 1.0));
	material->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0, 1.0, 1.0, 1.0));
	material->setShininess(osg::Material::FRONT_AND_BACK, 60.0);
	//��������
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

//������ͼԪ
osg::ref_ptr<osg::Geode> CreateSimple() {
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

	geode->addDrawable(geom.get());
	//��͸����
	geode->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);


	//����һЩ����
	osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array;
	//������ɫ
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
	//���뷨����
	osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
	//�����߿�
	osg::ref_ptr<osg::LineWidth> width = new osg::LineWidth;


	//�����߿�
	width->setWidth(15.0);
	geode->getOrCreateStateSet()->setAttributeAndModes(width.get(), osg::StateAttribute::ON);
	//���ö���
	geom->setVertexArray(coords.get());
	//���ö���Ĺ�����ʽ
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::Mode::LINE_LOOP, 0, 4));
	//���ö�����ɫ
	geom->setColorArray(colors.get());
	geom->setColorBinding(osg::Geometry::AttributeBinding::BIND_PER_VERTEX);
	//���÷�����
	geom->setNormalArray(normals.get());
	geom->setNormalBinding(osg::Geometry::AttributeBinding::BIND_OVERALL);

	//���õ�����
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
	//ѹ��һ��������
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