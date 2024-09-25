#include "GraphicObject.h"
GraphicObject::GraphicObject()
{
	this->angle = 0;
	this->position = { 0,0,0 };
	this->color = { 1,1,1 };
	this->modelMatrix = { 
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1}
	};
}
void GraphicObject::setPosition(vec3 position)
{
	this->position[0] = position[0];
	this->position[1] = position[1];
	this->position[2] = position[2];
	
}
vec3 GraphicObject::getPosition()
{
	vec3 temp = { 0,0,0 };
	temp[0] = this->position[0];
	temp[1] = this->position[1];
	temp[2] = this->position[2];
	return temp;
}
void GraphicObject::setAngle(float grad)
{
	this->angle = grad;
	recalculateModelMatrix();
}
float GraphicObject::getAngle()
{
	return this->angle;
}
void GraphicObject::setСolor(vec3 color)
{
	this->color[0] = color[0];
	this->color[1] = color[1];
	this->color[2] = color[2];
}
vec3 GraphicObject::getColor()
{
	vec3 temp = { 0,0,0 };
	temp[0] = this->color[0];
	temp[1] = this->color[1];
	temp[2] = this->color[2];
	return temp;
}
// расчет матрицы modelMatrix на основе position и angle
void GraphicObject::recalculateModelMatrix()
{
	modelMatrix = translate(modelMatrix, position);
	modelMatrix = rotate(modelMatrix, radians(-angle), vec3(0, 1, 0));

}
// вывести объект
void GraphicObject::draw()
{
	glColor3f(color.r, color.g, color.b);
	glPushMatrix();
	glMultMatrixf((GLfloat*)&modelMatrix);
	glutWireTeapot(1.0);
	glPopMatrix();
}