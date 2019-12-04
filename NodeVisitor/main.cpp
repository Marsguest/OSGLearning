#include <windows.h>
#include "../Common/Common.h"
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osg/MatrixTransform>
#include <osg/NodeVisitor>
#include <iostream>

class VisitorNodePath : public osg::NodeVisitor {
public:
	VisitorNodePath():osg::NodeVisitor(TRAVERSE_PARENTS){}
	void apply(osg::Node& node) {
		std::cout << "Apply node : " << node.getName() << std::endl;
		if (node.getName() == "glider") {
			//Do something
		}
		traverse(node);
	}
	void apply(osg::Group& group) {
		std::cout << "Apply group : " << group.getName() << std::endl;
		if (group.getName() == "root") {
			//Do something
		}
		traverse(group);
	}
	void apply(osg::MatrixTransform& mt) {
		std::cout << "Apply matrixTransform : " << mt.getName() << std::endl;
		if (mt.getName() == "childe2") {
			//Do something
		}
		traverse(mt);
	}
};

#ifdef _DEBUG
#pragma comment(lib,"../x64/Debug/Common.lib")
#else
#pragma comment(lib,"../x64/Release/Common.lib")
#endif // _DEBUG

int main() {
	osg::ref_ptr<osgViewer::Viewer>     viewer = new osgViewer::Viewer;
	osg::ref_ptr<osg::Group>              root = new osg::Group;
	osg::ref_ptr<osg::Node>             glider = osgDB::readNodeFile("glider.osg");
	osg::ref_ptr<osg::Node>                cow = osgDB::readNodeFile("cow.osg");
	osg::ref_ptr<osg::MatrixTransform>  child1 = new osg::MatrixTransform;
	osg::ref_ptr<osg::MatrixTransform>  child2 = new osg::MatrixTransform;
	osg::ref_ptr<osg::MatrixTransform>  child3 = new osg::MatrixTransform;
	osg::ref_ptr<osg::MatrixTransform>  child4 = new osg::MatrixTransform;
	osg::ref_ptr<osg::MatrixTransform>  child5 = new osg::MatrixTransform;

	VisitorNodePath vn;
	
	root->setName("root");
	glider->setName("glider");
	cow->setName("cow");
	root->addChild(glider);
	root->addChild(child1);
	root->addChild(child2);

	child1->setName("child1");
	child1->addChild(glider);
	child1->addChild(child3);
	child1->addChild(child4);
	child1->setMatrix(osg::Matrix::translate(-5, -5, 0));

	child2->setName("child2");
	child2->addChild(glider);
	child2->addChild(child5);
	child2->setMatrix(osg::Matrix::translate(5, -5, 0));

	child3->setName("child3");
	child3->addChild(cow);
	child3->setMatrix(osg::Matrix::translate(-5, -5, 0));

	child4->setName("child4");
	child4->addChild(cow);
	child4->setMatrix(osg::Matrix::translate(5, -5, 0));

	child5->setName("child5");
	child5->addChild(cow);
	child5->setMatrix(osg::Matrix::translate(5, -5, 0));




	cow->accept(vn);
	viewer->setSceneData(root.get());
	viewer->addEventHandler(new ChangeWindow());
	return viewer->run();
}