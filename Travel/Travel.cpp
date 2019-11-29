#include "Travel.h"


TravelManipulator::TravelManipulator(osg::Node* node)
{
	m_vPosition = osg::Vec3(0, 0, 50);
	m_vRotation = osg::Vec3(osg::PI_2,0,0);
	m_vStep = 1.0;
	m_vRotateStep = 0.0;
	m_bLeftDown = false;
	m_node = node;
}


void TravelManipulator::setByMatrix(const osg::Matrixd& matrix)
{
}

void TravelManipulator::setByInverseMatrix(const osg::Matrixd& matrix)
{
}

osg::Matrixd TravelManipulator::getMatrix() const
{
	osg::Matrixd mat;
	mat.makeTranslate(m_vPosition);
	return osg::Matrixd::rotate(m_vRotation[0], osg::X_AXIS, m_vRotation[1], osg::Y_AXIS, m_vRotation[2], osg::Z_AXIS) * mat;
}

osg::Matrixd TravelManipulator::getInverseMatrix() const
{
	osg::Matrixd mat;
	mat.makeTranslate(m_vPosition);
	return osg::Matrixd::inverse(osg::Matrixd::rotate(m_vRotation[0], osg::X_AXIS, m_vRotation[1], osg::Y_AXIS, m_vRotation[2], osg::Z_AXIS)* mat) ;
	
}

bool TravelManipulator::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us)
{
	switch (ea.getEventType())
	{
	case osgGA::GUIEventAdapter::KEYDOWN:
	{
		if ((ea.getKey() == 'w') || (ea.getKey() == 'W') || (ea.getKey() == osgGA::GUIEventAdapter::KEY_Up)) {
			changePosition(osg::Vec3d(m_vStep * cosf(osg::PI_2 + m_vRotation._v[2]), m_vStep * sinf(osg::PI_2 + m_vRotation._v[2]), 0));
			return true;
		}
		else if ((ea.getKey() == 's') || (ea.getKey() == 'S') || (ea.getKey() == osgGA::GUIEventAdapter::KEY_Down)) {
			changePosition(osg::Vec3d(-m_vStep * cosf(osg::PI_2 + m_vRotation._v[2]), -m_vStep * sinf(osg::PI_2 + m_vRotation._v[2]), 0));
			return true;
		}
		else if ((ea.getKey() == 'D') || (ea.getKey() == 'd')) {
			changePosition(osg::Vec3d(m_vStep * sinf(osg::PI_2 + m_vRotation._v[2]), -m_vStep * cosf(osg::PI_2 + m_vRotation._v[2]), 0));
			return true;
		}
		else if ((ea.getKey() == 'a') || (ea.getKey() == 'A')) {
			changePosition(osg::Vec3d(-m_vStep * sinf(osg::PI_2 + m_vRotation._v[2]), m_vStep * cosf(osg::PI_2 + m_vRotation._v[2]), 0));
			return true;
		}
		else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Left) {
			m_vRotation[2] += 0.2;
			return true;
		}
		else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Right) {
			m_vRotation[2] -= 0.2;
			return true;
		}
		else if (ea.getKey() == 'q') {
			changePosition(osg::Vec3d(0, 0, m_vStep));
			return true;
		}
		else if (ea.getKey() == 'e') {
			changePosition(osg::Vec3d(0, 0, -m_vStep));
			return true;
		}
	}
	case osgGA::GUIEventAdapter::PUSH:
	{
		if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON) {
			m_iLeftX = ea.getX();
			m_iLeftY = ea.getY();
			m_bLeftDown = true;
			return false;
		}
	}
	case osgGA::GUIEventAdapter::DRAG:
	{
		if (m_bLeftDown) {
			int delX = ea.getX() - m_iLeftX;
			int delY = ea.getY() - m_iLeftY;
			m_vRotation[2] -= osg::DegreesToRadians(0.001 * delX);
			m_vRotation[0] += osg::DegreesToRadians(0.001 * delY);
			if (m_vRotation[0] <= 0) m_vRotation[0] = 0;
			if (m_vRotation[0] >=  osg::PI) m_vRotation[0] = osg::PI;
		}
		
	}
	case osgGA::GUIEventAdapter::RELEASE:
	{
		if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON) {
			m_bLeftDown = false;
		}
	}


	default:
		break;
	}
	return false;
}
void TravelManipulator::setStep(double step)
{
	m_vStep = step;
}
double TravelManipulator::getStep()
{
	return m_vStep;
}
void TravelManipulator::setPosition(osg::Vec3d position)
{
	m_vPosition = position;
}
osg::Vec3d TravelManipulator::getPosition()
{
	return m_vPosition;
}
//改变位置
void TravelManipulator::changePosition(osg::Vec3d delta)
{
	//源点m_vPosition与目的点newPos
	osg::Vec3d newPos = m_vPosition + delta;
	osg::Vec3d start = osg::Vec3d(newPos.x(), newPos.y(), newPos.z() + 8);
	osg::Vec3d end = osg::Vec3d(newPos.x(), newPos.y(), newPos.z() -1000);
	osg::ref_ptr<osgUtil::IntersectionVisitor> iv = new osgUtil::IntersectionVisitor;
	osg::ref_ptr<osgUtil::LineSegmentIntersector> ls = new osgUtil::LineSegmentIntersector(start,end);
	
	osgUtil::LineSegmentIntersector::Intersections intersections;
	long height = 0;
	
	iv->setIntersector(ls.get());
	m_node->accept(*(iv.get()));

	if (ls->containsIntersections()) {
		std::cout << "There is a hit!" << std::endl;
		//取出焦点

		intersections = ls->getIntersections();
		osgUtil::LineSegmentIntersector::Intersections::iterator iter = intersections.begin();
		
		for (iter; iter!=intersections.end(); iter++)
		{
			if (height < iter->getWorldIntersectPoint().z()) {
				height = iter->getWorldIntersectPoint().z();
			}
			
		}
		
	}
	else {
		//不许走
		return;
	}
	m_vPosition += delta;
	m_vPosition.set(osg::Vec3f(m_vPosition.x(),m_vPosition.y(),height + 1));
}
