#pragma once
#include "../Common/Common.h"


#include <windows.h> 
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgGA/GUIEventAdapter>
#include <osgGA/TrackballManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osgUtil/Optimizer>
#include <iostream>

#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
#include <osg/Matrixd>
#include <osgGA/OrbitManipulator>


class TravelManipulator : public osgGA::OrbitManipulator {
public:
	TravelManipulator(osg::Node* node);

public:
	//实现得到和设置矩阵的接口
	/*设置当前视口*/
	virtual void setByMatrix(const osg::Matrixd& matrix);
	/*设置当前视口*/
	virtual void setByInverseMatrix(const osg::Matrixd& matrix);
	/*得到当前的矩阵*/
	virtual osg::Matrixd getMatrix() const;
	/*得到当前的逆矩阵*/
	virtual osg::Matrixd getInverseMatrix() const;
	//响应事件
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us);
	
	//设置步长
	void setStep(double step);

	//得到步长
	double getStep();

	//设置到某一点
	void setPosition(osg::Vec3d position);

	//得到当前坐标
	osg::Vec3d getPosition();

private:
	//改变位置
	void changePosition(osg::Vec3d delta);

private:
	//视点
	osg::Vec3 m_vPosition;
	//朝向
	osg::Vec3 m_vRotation;
	//移动步长
	double m_vStep;
	//旋转步长
	float m_vRotateStep;
	//记录坐标
	int m_iLeftX;
	int m_iLeftY;
	bool m_bLeftDown;
	osg::Node *m_node;
};