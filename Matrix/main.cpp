#include <windows.h> 
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgGA/GUIEventAdapter>
#include <osgGA/TrackballManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osgUtil/Optimizer>
#include <iostream>

#include <osg/MatrixTransform>
#include <osg/AnimationPath>
#include <osg/PositionAttitudeTransform>
//Output A Node
void ExportNode() {
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cow.osg");
	osg::ref_ptr<osg::MatrixTransform> max = new osg::MatrixTransform;

	max->addChild(node.get());
	max->setMatrix(osg::Matrix::translate(50.0, 0.0, 0.0));

	osgDB::ReaderWriter::WriteResult result = osgDB::Registry::instance()->writeNode(*max.get(),"TrCow.osg",osgDB::Registry::instance()->getOptions());
	if (result.success()) {
		osg::notify(osg::NOTICE) << "Read Node Success" << std::endl;
	}
}


//Matrix Oprtation
osg::ref_ptr<osg::Node> MatrixOperation() {
	osg::ref_ptr<osg::Group> group = new osg::Group;
	osg::ref_ptr<osg::MatrixTransform> max = new osg::MatrixTransform;
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("glider.osg");
	osg::ref_ptr<osg::MatrixTransform> max2 = new osg::MatrixTransform;


	max2->addChild(node.get());
	max2->setMatrix(osg::Matrix::translate(5.0, 0.0, 0.0));
	max->addChild(max2.get());
	max->setUpdateCallback(new osg::AnimationPathCallback(
		osg::Vec3(5.0,0.0,0.0),
		osg::Z_AXIS,
		1.0
		));

	group->addChild(node.get());
	group->addChild(max.get());

	return group;
}


int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform;


	osg::ref_ptr<osg::Group> group = new osg::Group;
	group->addChild(osgDB::readNodeFile("cow.osg"));
	pat->addChild(osgDB::readNodeFile("Trcow.osg"));
	pat->setPosition(osg::Vec3(0, 0, 0));
	group->addChild(pat.get());
	viewer->setSceneData(group.get());
	viewer->run();
	return 0;
}