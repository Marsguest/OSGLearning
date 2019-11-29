#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgGA/GUIEventAdapter>
#include <osgGA/TrackballManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osgUtil/Optimizer>


//ģ��һ���¼��࣬��Ӧ����H
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
	//����Viewer���󣬳��������
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	//����������ڵ�
	osg::ref_ptr<osg::Group> root = new osg::Group();

	//����һ����ʱ����
	osg::Timer* timer = new osg::Timer;
	osg::Timer_t start_frame_time = 0;
	osg::Timer_t end_frame_time = 0;

	//����֡��ʹ�õ�˯��ʱ��
	float sleep_time = 0.0;
	//ÿ֡ʵ��ʹ��ʱ��
	float current_time = 0.0;

	//count fps
	int count = 0;

	//�õ�һ��tickΪ����
	//std::cout << timer->getSecondsPerTick() << std::endl;
	//start_time = timer->tick();

	//����һ���ڵ㣬��ȡţ��ģ��
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cow.osg");

	//end_time = timer->tick();

	//std::cout << "��ȡģ��ʱ��Ϊ:" << timer->delta_s(start_time, end_time) << std::endl;

	//��ӵ�����
	root->addChild(node.get());
	//�Ż���������
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());
	//��ӵ����¼�
	viewer->addEventHandler(new osgViewer::HelpHandler);
	viewer->addEventHandler(new PrintName);
	viewer->addEventHandler(new osgViewer::StatsHandler);
	viewer->addEventHandler(new osgViewer::WindowSizeHandler);
	viewer->addEventHandler(new osgViewer::ScreenCaptureHandler);
	//���ó�������
	viewer->setSceneData(root.get());

	//�Ӳ�����
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
			//����֡��Ϊ10,ÿ֡����0.1s

			count = 0;
			end_frame_time = timer->tick();
			std::cout << "��ǰ֡�ʣ�" << 3 / (timer->delta_s(start_frame_time, end_frame_time)) << std::endl;
			
			//�õ���ǰÿ֡��������ʱ��
			sleep_time = 0.1 - (timer->delta_s(start_frame_time, end_frame_time)) / 3;
			if (sleep_time < 0) {
				sleep_time = 0.0;
			}
			
		
		}
	}

	return 0;
}