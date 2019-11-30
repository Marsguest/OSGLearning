#include <windows.h>
#include "../Common/Common.h"
#include "../NodeMatrix/NodeMatrix.h"
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgDB/ReadFile>
#include <osgGA/GUIEventHandler>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/LineSegment>
#include <osgUtil/IntersectVisitor>
#include <iostream>


#ifdef _DEBUG
#pragma comment(lib,"../x64/Debug/Common.lib")
#pragma comment(lib,"../x64/Debug/NodeMatrix.lib")
#else
#pragma comment(lib,"../x64/Release/Common.lib")
#pragma comment(lib,"../x64/Release/NodeMatrix.lib")
#endif // _DEBUG

#define LEFT   1
#define RIGHT  2
#define UP	   3
#define DOWN   4
#define FRONT  5
#define BACK    6


class MoveSphereEventHandler : public osgGA::GUIEventHandler {
public:
	MoveSphereEventHandler(NodeMatrix* node) {
		if (!node) {
			// Node is null,i can throw a exception
		}
		sphere = node;
		point = 0;
		pop = NULL;
	}
	/*Solve input like mouse and keyboard*/
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa){
		switch (ea.getEventType())
		{
		case osgGA::GUIEventAdapter::KEYDOWN: 
		{
			switch (ea.getKey())
			{
			case osgGA::GUIEventAdapter::KEY_Left:
			{
				point = LEFT;
				position = sphere->getPosition();
				changePosition(osg::Vec3d(position.x() - 20, position.y(), position.z()), position);
				
				break;
			}
			case osgGA::GUIEventAdapter::KEY_Right:
			{
				point = RIGHT;
				position = sphere->getPosition();
				changePosition(osg::Vec3d(position.x() + 20, position.y(), position.z()), position);

				break;
			}
			case osgGA::GUIEventAdapter::KEY_Up:
			{
				point = FRONT;
				position = sphere->getPosition();
				changePosition(osg::Vec3d(position.x(), position.y() + 20, position.z()), position);

				break;
			}
			case osgGA::GUIEventAdapter::KEY_Down:
			{
				point = BACK;
				position = sphere->getPosition();
				changePosition(osg::Vec3d(position.x() , position.y() - 20, position.z()), position);

				break;
			}
			case osgGA::GUIEventAdapter::KEY_Q:
			{
				point = UP;
				position = sphere->getPosition();
				changePosition(osg::Vec3d(position.x(), position.y(), position.z() + 20), position);

				break;
			}
			case osgGA::GUIEventAdapter::KEY_E:
			{
				point = DOWN;
				position = sphere->getPosition();
				changePosition(osg::Vec3d(position.x(), position.y(), position.z() - 20), position);

				break;
			}
				
			default:
				break;
			}// end switch getKey
			break;
		}
			
		default:
			break;
		} // end switch getEventType
		
		return false;
		
	}
	/* set hit scene */
	void setNode(osg::Node* node) {
		if (!node) {
			//exception
		}
		box = node;
	}
	/* ball move */
	void changePosition(osg::Vec3d newPos,osg::Vec3d oldPos) {
		osg::ref_ptr<osg::LineSegment> ls = new osg::LineSegment();
		osg::ref_ptr<osgUtil::IntersectVisitor> iv = new osgUtil::IntersectVisitor();
		switch (point)
		{
		case LEFT:
		{
			ls->set(osg::Vec3d(newPos.x() - 40, newPos.y(), newPos.z()), oldPos);
		}
		case RIGHT:
		{
			ls->set(osg::Vec3d(newPos.x() + 40, newPos.y(), newPos.z()), oldPos);
		}
		case FRONT:
		{
			ls->set(osg::Vec3d(newPos.x() , newPos.y()+ 40, newPos.z()), oldPos);
		}
		case BACK:
		{
			ls->set(osg::Vec3d(newPos.x() , newPos.y()- 40, newPos.z()), oldPos);
		}
		case UP:
		{
			ls->set(osg::Vec3d(newPos.x(), newPos.y() , newPos.z()+ 40), oldPos);
		}
		case DOWN:
		{
			ls->set(osg::Vec3d(newPos.x(), newPos.y() , newPos.z()- 40), oldPos);
		}
		default:
			break;
		}
		iv->addLineSegment(ls.get());
		box->accept(*(iv.get()));
		if (iv->hits()) {
			//To find out what is hited
			{
				//To get HitList
				osgUtil::IntersectVisitor::HitList hitList = iv->getHitList(ls.get());
				osg::NodePath nodePath;
				for (osgUtil::IntersectVisitor::HitList::iterator iter = hitList.begin() ; iter != hitList.end() ; iter++)
				{
					nodePath = iter->getNodePath();
					for (osg::NodePath::iterator iterNode = nodePath.begin(); iterNode!=nodePath.end(); iterNode++)
					{
						std::cout << "hit: " << (*iterNode)->getName() << std::endl;
						if ((*iterNode)->getName() != "ReadBox") {
							if (!pop) {
								pop = (*iterNode);
							}
							else {
								pop->setNodeMask(1);
							}
							(*iterNode)->setNodeMask(0);
							pop = (*iterNode);
						}
					
					}
				}
			}// END To find out it which is hited
		}
		sphere->toPosition(newPos);
		

		
	}
private:
	/*ÒÆ¶¯µÄÐ¡Çò*/
	NodeMatrix* sphere;
	/*Now Position*/
	osg::Vec3d position;
	/* the node which is hited*/
	osg::Node* box;
	/* move direction*/
	int point;
	/* POP */
	osg::Node* pop;

};
/*draw a sphere*/
osg::ref_ptr<osg::Geode> CreateSphere() {
	osg::ref_ptr<osg::Geode> gnode = new osg::Geode;
	osg::ref_ptr<osg::ShapeDrawable> sd = new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0, 0, 0), 40.0));
	gnode->addDrawable(sd.get());
	return gnode;


}
int main() {
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	osg::ref_ptr<osg::Group> group = new osg::Group;
	osg::ref_ptr<NodeMatrix> nm = new NodeMatrix;

	osg::ref_ptr<osg::Node> node = CreateSphere();
	osg::ref_ptr<osg::Node> box = osgDB::readNodeFile("Box.ive");
	osg::ref_ptr<MoveSphereEventHandler> eh = new MoveSphereEventHandler(nm.get());

	nm->addsChild(node);
	nm->toPosition(osg::Vec3d(0, 0, 250));

	node->setName("Sphere");
	box->setName("ReadBox");
	group->setName("Root Group");

	group->addChild(nm.get());
	group->addChild(box.get());

	eh->setNode(box.get());

	viewer->addEventHandler(new osgViewer::WindowSizeHandler);
	viewer->addEventHandler(eh);
	viewer->setSceneData(group);
	viewer->run();

	return 0;
}
