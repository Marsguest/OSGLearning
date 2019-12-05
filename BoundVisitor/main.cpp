#include <windows.h>
#include "../Common/Common.h"
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osg/MatrixTransform>
#include <osg/NodeVisitor>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <iostream>


#ifdef _DEBUG
#pragma comment(lib,"../x64/Debug/Common.lib")
#else
#pragma comment(lib,"../x64/Release/Common.lib")
#endif // _DEBUG

osg::ref_ptr<osg::Geode> CreateBox(osg::Vec3Array *va) {
	osg::ref_ptr<osg::Geode> gnode = new osg::Geode;
	for (osg::Vec3Array::iterator iter = va->begin(); iter != va->end(); iter++) {
		gnode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(iter->x(),iter->y(),iter->z()),0.01,0.01,0.01)));
	}
	return gnode;
}

class BoundVisiotr : public osg::NodeVisitor {
public:

	void apply(osg::Geode& gnode) {
		/*这里由于osg版本更新，找不到视频中的DrawableList.通过观察源码
		发现Geode有getNumDrawables方法用来记录Drawsble数量，以及
		getDrawable方法通过传入index来获取指定位置Drawable*/
		int drawableNum = gnode.getNumDrawables();
		for (int i = 0; i < drawableNum; i++)
		{
			osg::ref_ptr<osg::Geometry> gm = dynamic_cast<osg::Geometry*> (gnode.getDrawable(i));
			osg::Vec3Array* vx = dynamic_cast<osg::Vec3Array*> (gm->getVertexArray());
			//for (osg::Vec3Array::iterator iter = vx->begin(); iter != vx->end(); iter++)
			{
				//std::cout << iter->x() << "     :      " << iter->y() << "     :      " << iter->z() << std::endl;
				if (group.valid()) {
					if ("root" == group->getName()) {
						group->addChild(CreateBox(vx));
					}
				}
				
			}

		}
	}
	void setGroup(osg::Group *gp) {
		group = gp;
	}
private:
	osg::ref_ptr<osg::Group> group;
};

int main() {
	osg::ref_ptr<osgViewer::Viewer>     viewer = new osgViewer::Viewer;
	osg::ref_ptr<osg::Group>              root = new osg::Group;
	osg::ref_ptr<osg::Node>             glider = osgDB::readNodeFile("glider.osg");
	BoundVisiotr bv;
	bv.setGroup(root);

	root->setName("root");
	glider->accept(bv);
	
	root->addChild(glider);

	viewer->setSceneData(root.get());
	viewer->addEventHandler(new ChangeWindow());
	return viewer->run();
}