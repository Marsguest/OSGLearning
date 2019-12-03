#pragma once
#ifndef _COMMON_H__
#define _COMMON_H__

#ifdef _DEBUG
#pragma comment(lib,"osgd.lib")
#pragma comment(lib,"osgDBd.lib")
#pragma comment(lib,"osgViewerd.lib")
#pragma comment(lib,"OpenThreadsd.lib")
#pragma comment(lib,"osgUtild.lib")
#pragma comment(lib,"osgGAd.lib")
#pragma comment(lib,"osgTextd.lib")

#else
#pragma comment(lib,"osg.lib")
#pragma comment(lib,"osgDB.lib")
#pragma comment(lib,"osgViewer.lib")
#pragma comment(lib,"OpenThreads.lib")
#pragma comment(lib,"osgUtil.lib")
#pragma comment(lib,"osgGA.lib")
#pragma comment(lib,"osgText.lib")
#endif // _DEBUG
#include <windows.h>
#include <osgViewer/Viewer>
#include <osgGA/GUIEventHandler>

/* 用于改变窗口的各项参数 */
class ChangeWindow : public osgGA::GUIEventHandler {
public:
	ChangeWindow() { first = false; }
	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) {
		if (!first) {
			first = true;
			osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
			osgViewer::Viewer::Windows ws;
			viewer->getWindows(ws);
			if (!ws.empty()) {
				osgViewer::Viewer::Windows::iterator iter = ws.begin();
				for (; iter != ws.end(); iter++)
				{
					(*iter)->setWindowRectangle(240, 90, 1440, 900);
					(*iter)->setWindowDecoration(false);
					//设置是否使用鼠标
					//(*iter)->useCursor(true);
					//设置鼠标样式
					//(*iter)->setCursor(osgViewer::GraphicsWindow::WaitCursor);
				}
			}
		}

		return false;
	}

private:
	bool first;
};
#endif // !_COMMON_H__



