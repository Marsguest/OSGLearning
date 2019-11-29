#include "Travel.h"
#include "../NodeMatrix/NodeMatrix.h"
#ifdef _DEBUG
#pragma comment(lib,"../x64/Debug/NodeMatrix.lib")
#else
#pragma comment(lib,"../x64/Release/NodeMatrix.lib")
#endif // _DEBUG

int main() {
	osg::ref_ptr <osgViewer::Viewer> viewer = new osgViewer::Viewer;
	osg::ref_ptr<NodeMatrix> nm = new NodeMatrix;
	nm->addsChild(osgDB::readNodeFile("ceep.ive"));
	nm->toPosition(osg::Vec3d(0, 0, 0));
	viewer->setSceneData(nm.get());
	viewer->setCameraManipulator(new TravelManipulator(nm));
	viewer->run();
	return 0;
}