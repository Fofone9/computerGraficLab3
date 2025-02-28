#include <windows.h>

#include <iostream>
#include<iomanip>
#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "graphicObject.h"

using namespace std;
using namespace glm;

GraphicObject tempGraphicObject;
vector<GraphicObject> graphicObjects;
//переменные для отрисовки изображения
int current_index = 0;
vector <vec3> colors = { 
	{1.0f, 1.0f, 1.0f },//белый
	{0.0f, 0.0f, 1.0f},//синий
	{1.0f, 0.0f, 0.0f},//красный
	{1.0f, 1.0f, 0.0f},//желтый
	{1.0f, 0, 1.0f}//фиолетовый
};
int accumulation = 0;

//переменные для вывода в консоль
vector<string> color_names = { "white", "blue", "red", "yellow", "purple" };

// функция, вызываемая при изменении размеров окна
void reshape(int w, int h)
{
	// установить новую область просмотра, равную всей области окна
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
void display(void)
{
	glClearColor(0.00, 0.00, 0.00, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);
	// устанавливаем камеру
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(10, 15, 17.5, 0, 0, 0, 0, 1, 0);
	for (auto& go : graphicObjects) {
		go.draw();
	}

	// смена переднего и заднего буферов
	glutSwapBuffers();
};


// вывод некоторой информации о переменных отображения
void showInfo() {
	cout << accumulation * 2 << "%   " << setw(8) << color_names[current_index] << "   \r";
}
// функция вызывается каждые 20 мс
void simulation(int value)
{
	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();
	// эта же функция будет вызвана еще раз через 20 мс
	glutTimerFunc(20, simulation, 0);
};

void main(int argc, char** argv)
{
	setlocale(LC_ALL, "ru");
	GraphicObject obj1;
	obj1.setPosition(glm::vec3(4, 0, 0));
	obj1.setAngle(180);
	obj1.setСolor(glm::vec3(1, 0, 0));
	graphicObjects.push_back(obj1);

	GraphicObject obj2;
	obj2.setPosition(glm::vec3(-4, 0, 0));
	obj2.setAngle(0);
	obj2.setСolor(glm::vec3(1, 1, 1));
	graphicObjects.push_back(obj2);

	GraphicObject obj3;
	obj3.setPosition(glm::vec3(0, 0, 4));
	obj3.setAngle(270);
	obj3.setСolor(glm::vec3(0, 1, 0));
	graphicObjects.push_back(obj3);

	GraphicObject obj4;
	obj4.setPosition(glm::vec3(0, 0, -4));
	obj4.setAngle(90);
	obj4.setСolor(glm::vec3(0, 0, 1));
	graphicObjects.push_back(obj4);
	// инициализация библиотеки GLUT
	glutInit(&argc, argv);
	// инициализация дисплея (формат вывода)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	// СОЗДАНИЕ ОКНА:
	// 1. устанавливаем верхний левый угол окна
	glutInitWindowPosition(200, 200);
	// 2. устанавливаем размер окна
	glutInitWindowSize(800, 600);
	// 3. создаем окно
	glutCreateWindow("Laba_02");
	// УСТАНОВКА ФУНКЦИЙ ОБРАТНОГО ВЫЗОВА
	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(display);
	// устанавливаем функцию, которая будет вызываться при изменении размеров окна
	glutReshapeFunc(reshape);
	// устанавливаем функцию, которая будет вызвана через 20 мс
	glutTimerFunc(20, simulation, 0);

	// основной цикл обработки сообщений ОС
	glutMainLoop();
};