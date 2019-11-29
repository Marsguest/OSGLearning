#include "../Common/Common.h"
#include <windows.h>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osg/ShapeDrawable>
#include <osgUtil/IntersectionVisitor>
#include <osgUtil/LineSegmentIntersector>
#include <osg/Material>
#include <osg/StateSet>
#include <osg/Image>
#include <osg/Texture2D>
#include <iostream>
#ifdef _DEBUG
#pragma comment(lib,"../x64/Debug/Common.lib")

#else
#pragma comment(lib,"../x64/Release/Common.lib")
#endif // _DEBUG

osg::ref_ptr<osg::Geode> CreateLine(const osg::Vec3& start, const osg::Vec3& end) {
	osg::ref_ptr <osg::Geode > gnode = new osg::Geode;
	osg::ref_ptr<osg::Geometry> gy = new osg::Geometry;
	osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array;

	gnode->addDrawable(gy);
	gy->setVertexArray(coords);

	coords->push_back(start);
	coords->push_back(end);
	gy->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP, 0, 2));

	return gnode;
}

osg::ref_ptr<osg::Geode> CreateSphere(osg::Vec3 center) {
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(center,0.2)));
	return geode;
}

osg::ref_ptr<osg::Geode> CreateBox() {
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	osg::ref_ptr <osg::TessellationHints> hints = new osg::TessellationHints;
	osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable(new osg::Box(osg::Vec3(0.0, 0.0, 0.0), 10.0, 10.0, 10.0), hints.get());
	osg::ref_ptr<osg::Material> material = new osg::Material;


	//设置材质
	shape->setColor(osg::Vec4(0.5, 0.5, 0.5, 0.2));
	//设置精度
	hints->setDetailRatio(0.8);
	//设置材质
	material->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0, 1.0, 1.0, 0.2));
	material->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0, 1.0, 1.0, 0.2));
	material->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0, 1.0, 1.0, 0.2));
	material->setShininess(osg::Material::FRONT_AND_BACK, 60.0);

	//set state
	geode->getOrCreateStateSet()->setAttributeAndModes(material.get(), osg::StateAttribute::ON);
	geode->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
	geode->addDrawable(shape.get());
	return geode;
}


int main() {
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	osg::ref_ptr<osg::Group> group = new osg::Group;
	osg::Vec3 start = osg::Vec3(-10, 7, 15);
	osg::Vec3 end = osg::Vec3(5,-4,-12);


	//
	osgUtil::LineSegmentIntersector::Intersections intersectinos;
	osg::ref_ptr<osgUtil::LineSegmentIntersector> ls = new osgUtil::LineSegmentIntersector(start, end);
	osg::ref_ptr<osgUtil::IntersectionVisitor> iv = new osgUtil::IntersectionVisitor(ls);
	//
	group->addChild(CreateBox());
	group->accept(*(iv.get()));
	//画出那条检测线
	group->addChild(CreateLine(start, end));

	//如果有碰撞，输出所有的焦点
	if (ls->containsIntersections()) {
		intersectinos = ls->getIntersections();
		for (osgUtil::LineSegmentIntersector::Intersections::iterator iter = intersectinos.begin(); iter != intersectinos.end(); iter++)
		{
			std::cout << iter->getWorldIntersectPoint().x() << " " << iter->getWorldIntersectPoint().y() << " " << iter->getWorldIntersectPoint().z() << std::endl;
			group->addChild(CreateSphere(osg::Vec3(iter->getWorldIntersectPoint())));
			
		}
	}

	viewer->setSceneData(group);
	viewer->run();
	return 0;
} 