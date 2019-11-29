#include "NodeMatrix.h"

int main() {
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	osg::ref_ptr<NodeMatrix> nm = new NodeMatrix;
	osg::ref_ptr<osg::Group> group = new osg::Group;
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("glider.osg");

	nm->addsChild(osgDB::readNodeFile("Trcow.osg"));
	/*nm->rotating(osg::Vec3d(10.0, 0.0, 0.0),
		osg::Z_AXIS,
		1.0);
	nm->toRotate(1, osg::Y_AXIS);*/
	nm->toPosition(osg::Vec3d(10.0,0.0,0.0));
	nm->adapt(node.get());

	group->addChild(node.get());
	group->addChild(nm.get());
	

	viewer->setSceneData(group.get());
	viewer->run();
	return 0;
}