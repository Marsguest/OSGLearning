#include <windows.h>
#include "../Common/Common.h"
#include <osgViewer/Viewer>
#include <osg/GraphicsContext>
#include <osgDB/ReadFile>
#include <iostream>
#include <osgGA/GUIEventHandler>


#ifdef _DEBUG
#pragma comment(lib,"../x64/Debug/Common.lib")
#else
#pragma comment(lib,"../x64/Release/Common.lib")
#endif // _DEBUG



int main() {
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	viewer->setSceneData(osgDB::readNodeFile("glider.osg"));
	
	viewer->addEventHandler(new ChangeWindow());
	viewer->run();

	/*osg::GraphicsContext::WindowingSystemInterface* ws = osg::GraphicsContext::getWindowingSystemInterface();
	unsigned int height, width;
	osg::GraphicsContext::Traits traits;

	if (ws) {
		std::cout << "Get device inteface sucess" << std::endl;
		ws->getScreenResolution(traits,width,height);
		std::cout << "系统分辨率为：" << width << " x " << height << std::endl;
		std::cout << "边框：" << traits.windowDecoration << std::endl;
	}
	else {
		std::cout << "Get device inteface failure" << std::endl;
	}*/


	return 0;
}