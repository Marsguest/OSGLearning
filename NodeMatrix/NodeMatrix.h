#pragma once
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

#ifdef NODE_MATRIX
#else
#define NODE_MATRIX __declspec(dllimport)
#endif // NODE_MATRIX



class NodeMatrix :
	public osg::MatrixTransform
{
public:
	NodeMatrix(void);
	~NodeMatrix(void);

public:
	/*���õ�ǰģ��ת����ʽ*/
	void rotating(const osg::Vec3d& pivot,
		const osg::Vec3d& axis,
		float angularVelocity
	);

	/*��תģ��*/
	void toRotate(const osg::Matrix& mat);

	/*��תģ��*/
	void toRotate(float angle,const osg::Vec3f &axis);

	/*����ģ��*/
	void toScale(const osg::Matrix& mat);

	/*����ģ��*/
	void toScale(float lel);

	/*addsChild����*/
	void addsChild(osg::Node* node);

	/*��ģ���Ƶ�Ŀ�ĵ�*/
	void toPosition(osg::Vec3d pos);

	/*�õ�ģ�͵�ǰλ��*/
	osg::Vec3d getPosition();

	/*����ģ�ʹ�С*/
	void adapt(osg::BoundingSphere& sps);

	/*����ģ�ʹ�С*/
	void adapt(osg::Node *node);
private:
	osg::ref_ptr<osg::MatrixTransform> pat;
	osg::BoundingSphere ps;
	osg::Node* pNode;
	float level = 1.0;
	osg::Vec3d position;
};

