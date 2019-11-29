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
	/*设置当前模型转动方式*/
	void rotating(const osg::Vec3d& pivot,
		const osg::Vec3d& axis,
		float angularVelocity
	);

	/*旋转模型*/
	void toRotate(const osg::Matrix& mat);

	/*旋转模型*/
	void toRotate(float angle,const osg::Vec3f &axis);

	/*缩放模型*/
	void toScale(const osg::Matrix& mat);

	/*缩放模型*/
	void toScale(float lel);

	/*addsChild方法*/
	void addsChild(osg::Node* node);

	/*将模型移到目的点*/
	void toPosition(osg::Vec3d pos);

	/*得到模型当前位置*/
	osg::Vec3d getPosition();

	/*限制模型大小*/
	void adapt(osg::BoundingSphere& sps);

	/*限制模型大小*/
	void adapt(osg::Node *node);
private:
	osg::ref_ptr<osg::MatrixTransform> pat;
	osg::BoundingSphere ps;
	osg::Node* pNode;
	float level = 1.0;
	osg::Vec3d position;
};

