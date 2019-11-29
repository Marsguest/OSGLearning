#include <windows.h>
#include "../Common/Common.h"
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgDB/ReadFile>

#ifdef _DEBUG
#pragma comment(lib,"../x64/Debug/Common.lib")

#else
#pragma comment(lib,"../x64/Release/Common.lib")
#endif // _DEBUG

int main() {
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	viewer->addEventHandler(new osgViewer::WindowSizeHandler);
	viewer->setSceneData(osgDB::readNodeFile("glider.osg"));
	viewer->run();

	return 0;
}
