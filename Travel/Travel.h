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
	//ʵ�ֵõ������þ���Ľӿ�
	/*���õ�ǰ�ӿ�*/
	virtual void setByMatrix(const osg::Matrixd& matrix);
	/*���õ�ǰ�ӿ�*/
	virtual void setByInverseMatrix(const osg::Matrixd& matrix);
	/*�õ���ǰ�ľ���*/
	virtual osg::Matrixd getMatrix() const;
	/*�õ���ǰ�������*/
	virtual osg::Matrixd getInverseMatrix() const;
	//��Ӧ�¼�
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us);
	
	//���ò���
	void setStep(double step);

	//�õ�����
	double getStep();

	//���õ�ĳһ��
	void setPosition(osg::Vec3d position);

	//�õ���ǰ����
	osg::Vec3d getPosition();

private:
	//�ı�λ��
	void changePosition(osg::Vec3d delta);

private:
	//�ӵ�
	osg::Vec3 m_vPosition;
	//����
	osg::Vec3 m_vRotation;
	//�ƶ�����
	double m_vStep;
	//��ת����
	float m_vRotateStep;
	//��¼����
	int m_iLeftX;
	int m_iLeftY;
	bool m_bLeftDown;
	osg::Node *m_node;
};