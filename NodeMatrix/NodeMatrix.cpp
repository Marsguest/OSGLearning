#define NODE_MATRIX __declspec(dllexport)
#include "NodeMatrix.h"

NodeMatrix::NodeMatrix(void)
{
	pat = new osg::MatrixTransform;
	addChild(pat);
	level = 1.0;
	position = osg::Vec3d(0, 0, 0);


}

NodeMatrix::~NodeMatrix(void)
{
}

/*设置当前模型转动方式*/
void NodeMatrix::rotating(const osg::Vec3d& pivot, const osg::Vec3d& axis, float angularVelocity)
{
	setUpdateCallback(new osg::AnimationPathCallback(
		pivot,
		axis,
		angularVelocity
	));
}
/*旋转模型*/
void NodeMatrix::toRotate(const osg::Matrix& mat)
{
	pat->setMatrix(mat);
}
void NodeMatrix::toRotate(float angle, const osg::Vec3f& axis)
{
	pat->setMatrix(osg::Matrix::rotate(angle,axis));
}
/*缩放模型*/
void NodeMatrix::toScale(const osg::Matrix& mat)
{
	pat->setMatrix(mat);
}

void NodeMatrix::toScale(float lel)
{
	pat->setMatrix(osg::Matrix::scale(lel,lel,lel));

}
/*addsChild方法*/
void NodeMatrix::addsChild(osg::Node* node)
{
	pat->addChild(node);
	pNode = node;
	ps = node->getBound();
	osg::notify(osg::NOTICE) << ps.center().x() << " " << ps.center().y() << " " << ps.center().z() << std::endl;
}
/*将模型移到目的点*/
void NodeMatrix::toPosition(osg::Vec3d pos) {
	
	osg::Vec3d cps;
	cps.set(-ps.center().x() * level, -ps.center().y() * level, -ps.center().z() * level);
	pat->setMatrix(osg::Matrix::translate(cps)* osg::Matrix::translate(pos));

	position = pos;
}

/*得到模型当前位置*/
osg::Vec3d NodeMatrix::getPosition()
{
	return position;
}
/*限制模型大小*/
void NodeMatrix::adapt(osg::BoundingSphere& sps)
{
	level = sps.radius() / ps.radius();
	toScale(level);
}

void NodeMatrix::adapt(osg::Node* node)
{
	osg::BoundingSphere sps = node->getBound();
	level = sps.radius() / ps.radius();
	toScale(level);
}
