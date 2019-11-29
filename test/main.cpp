#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgGA/GUIEventAdapter>
#include <osgGA/TrackballManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osgUtil/Optimizer>


//模拟一个事件类，响应单机H
class PrintName : public osgGA::GUIEventHandler {
public:
	virtual void getUsage(osg::ApplicationUsage& usage) const {
		usage.addKeyboardMouseBinding("ssz", "Great");
	}
	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) {
		return false;
	}
};




int main()
{
	//创建Viewer对象，场景浏览器
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	//创建场景组节点
	osg::ref_ptr<osg::Group> root = new osg::Group();

	//申请一个定时器类
	osg::Timer* timer = new osg::Timer;
	osg::Timer_t start_frame_time = 0;
	osg::Timer_t end_frame_time = 0;

	//控制帧率使用的睡眠时间
	float sleep_time = 0.0;
	//每帧实际使用时间
	float current_time = 0.0;

	//count fps
	int count = 0;

	//得到一个tick为多少
	//std::cout << timer->getSecondsPerTick() << std::endl;
	//start_time = timer->tick();

	//创建一个节点，读取牛的模型
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cow.osg");

	//end_time = timer->tick();

	//std::cout << "读取模型时间为:" << timer->delta_s(start_time, end_time) << std::endl;

	//添加到场景
	root->addChild(node.get());
	//优化场景数据
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());
	//添加单击事件
	viewer->addEventHandler(new osgViewer::HelpHandler);
	viewer->addEventHandler(new PrintName);
	viewer->addEventHandler(new osgViewer::StatsHandler);
	viewer->addEventHandler(new osgViewer::WindowSizeHandler);
	viewer->addEventHandler(new osgViewer::ScreenCaptureHandler);
	//设置场景数据
	viewer->setSceneData(root.get());

	//加操作器
	viewer->setCameraManipulator(new osgGA::TrackballManipulator);
	
	//viewer->run();
	while (!viewer->done()) {
		if (count == 0) {
			start_frame_time = timer->tick();
		}
		count++;
		viewer->frame();

		OpenThreads::Thread::microSleep(sleep_time * 1000000);

		if (count == 3) {
			//限制帧率为10,每帧绘制0.1s

			count = 0;
			end_frame_time = timer->tick();
			std::cout << "当前帧率：" << 3 / (timer->delta_s(start_frame_time, end_frame_time)) << std::endl;
			
			//得到当前每帧绘制所用时间
			sleep_time = 0.1 - (timer->delta_s(start_frame_time, end_frame_time)) / 3;
			if (sleep_time < 0) {
				sleep_time = 0.0;
			}
			
		
		}
	}

	return 0;
}