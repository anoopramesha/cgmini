#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<iostream>
#include<math.h>
using namespace std;
#define PI 3.14152653597689786
#define RandomFactor 2.0
#define ESCAPE 27
#define TEXTID 3
unsigned int i;
int flag=0,f=2;
int vflag=0;
GLfloat xt=0.0,yt=0.0,zt=0.0;
GLfloat xangle=0.0,yangle=0.0,zangle=0.0;
GLfloat X[3];
GLint ListNum;
GLfloat OuterRadius = 2.4;
GLfloat InnerRadius = 2.0;
GLint NumOfVerticesStone = 6;
GLfloat StoneHeight = 0.5;
GLfloat WaterHeight = 0.45;
struct SVertex
{
GLfloat x,y,z;
};
class CDrop
{
private:
GLfloat time;
SVertex ConstantSpeed;
GLfloat AccFactor;
public:
void SetConstantSpeed (SVertex NewSpeed);
void SetAccFactor(GLfloat NewAccFactor);
void SetTime(GLfloat NewTime);
void GetNewPosition(SVertex * PositionVertex);
};
void CDrop::SetConstantSpeed(SVertex NewSpeed)
{
ConstantSpeed = NewSpeed;
}
void CDrop::SetAccFactor (GLfloat NewAccFactor)
{
AccFactor = NewAccFactor;
}
void CDrop::SetTime(GLfloat NewTime)
{
time = NewTime;
}
void CDrop::GetNewPosition(SVertex * PositionVertex)
{
SVertex Position;
time += 0.15;
Position.x = ConstantSpeed.x * time;
Position.y = ConstantSpeed.y * time - AccFactor * time *time;
Position.z = ConstantSpeed.z * time;
PositionVertex->x = Position.x;
PositionVertex->y = Position.y + WaterHeight;
PositionVertex->z = Position.z;
if (Position.y < 0.0)
{
time = time - int(time);
if (time > 0.0) time -= 1.0;
}
}
CDrop * FountainDrops;
SVertex * FountainVertices;
GLint Steps = 4;
GLint RaysPerStep =8;
GLint DropsPerRay = 80;
GLfloat DropsComplete = Steps * RaysPerStep * DropsPerRay;
GLfloat AngleOfDeepestStep = 80;
GLfloat AccFactor = 0.011;

int glob=0;
int boat=0;
int n;
int bi;
int s;
int id;
void day();
void night();
void drawsea();
void drawsea2();
void mountain();
void mountain2();
void drawtree2();
void drawtree();
void drawboat();
void redrawboat();
void drawsmallboat();
void circle_draw(GLint h,GLint k,GLint r);
void plotpixels(GLint h,GLint k,GLint x,GLint y);
void display();
void randcolor();
void colour(int id);

void key(unsigned char key,int x,int y);
void mainmenu(int id);

void init();
int main(int argc,char** argv);



void init()
{	glClearColor(.8,.5,0.0,1.0);

	glColor3f(1.0,0.0,0.0);
	glPointSize(5.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,2200.0,0.0,1800.0);

	printf("press 'x' to move boat in +ve x-direction\n");
	printf("press 'y' to move boat in -ve x-direction\n");
	printf("press 'z' to move the moon in +ve y-direction\n");
	printf("press 'w' to move the moon in -ve y-direction\n");
	printf("press 's' to stop the smallboat\n");
	printf("press 'r' to restart the smallboat\n");

	glutPostRedisplay();
}

//To draw Mountain for DAY

void mountain()
{

	glColor3f(0.5,0.42,0.12);
    glBegin(GL_TRIANGLES);
	glVertex2f(250,1300);
		glColor3f(0.55,0.44,0.15);
	glVertex2f(0,1600);
		glColor3f(0.50,0.42,0.20);
	glVertex2f(0,1300);
	glEnd();
	glColor3f(0.75,0.5,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(100,1300);
	glVertex2f(300,1600);
	glVertex2f(400,1600);
		glColor3f(0.60,0.12,0.0);
	glVertex2f(500,1650);
	glVertex2f(700,1630);
		glColor3f(0.50,0.40,0.0);
	glVertex2f(900,1300);
	glEnd();

	glColor3f(0.66,0.12,0.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(300,1300);
	glColor3f(0.40,0.15,0.0);
	glVertex2f(700,1680);
	glColor3f(0.0,0.0,1.0);
	glVertex2f(900,1300);
	glEnd();
	glColor3f(0.35,0.10,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(500,1300);
	glVertex2f(700,1500);
	glColor3f(0.50,0.40,0.12);
	glVertex2f(900,1650);
	glVertex2f(1300,1500);
	glColor3f(0.55,0.40,0.12);
	glVertex2f(1500,1450);
	glVertex2f(1600,1300);
	glEnd();
	glColor3f(0.62,0.42,0.12);
	glBegin(GL_POLYGON);
	glVertex2f(1400,1300);
	glVertex2f(1800,1600);
	glColor3f(0.50,0.40,0.12);
	glVertex2f(1850,1650);
	glVertex2f(1900,1600);
	glColor3f(0.55,0.40,0.12);
	glVertex2f(2000,1300);
	glEnd();glColor3f(0.62,0.42,0.13);
	glBegin(GL_TRIANGLES);
	glVertex2f(2000,1300);
	glColor3f(0.50,0.40,0.12);
	glVertex2f(2200,1600);
	glColor3f(0.55,0.40,0.12);
	glVertex2f(2200,1300);

glEnd();



}

//To Draw Mountain for Night

void mountain2()
{

	glColor3f(0.10,0.10,0.0);
    glBegin(GL_TRIANGLES);
	glVertex2f(250,1300);
	glColor3f(0.60,0.40,0.12);
	glVertex2f(0,1600);
	glColor3f(0.10,0.10,0.0);
	glVertex2f(0,1300);
	glEnd();
	glColor3f(0.60,0.40,0.12);
	glBegin(GL_POLYGON);
	glVertex2f(100,1300);
	glColor3f(0.10,0.10,0.0);
	glVertex2f(300,1600);
	glColor3f(0.10,0.10,0.0);

	glVertex2f(400,1600);
	glColor3f(0.10,0.10,0.0);
	glVertex2f(500,1650);
	glVertex2f(700,1630);
	glColor3f(0.10,0.10,0.0);

	glVertex2f(900,1300);
	glEnd();
	glColor3f(0.60,0.40,0.12);
	glBegin(GL_TRIANGLES);
	glVertex2f(300,1300);
	glColor3f(0.10,0.10,0.0);

	glVertex2f(700,1680);
	glColor3f(0.10,0.10,0.0);

	glVertex2f(900,1300);
	glEnd();
	glColor3f(0.60,0.42,0.12);
	glBegin(GL_POLYGON);
	glVertex2f(500,1300);
	glColor3f(0.10,0.10,0.0);
	glVertex2f(700,1500);
	glColor3f(0.10,0.10,0.0);
	glVertex2f(900,1650);
	glVertex2f(1300,1500);
		glColor3f(0.10,0.10,0.0);
	glVertex2f(1500,1450);
	glVertex2f(1600,1300);
//	glEnd();
	glColor3f(0.62,0.42,0.12);
	glBegin(GL_POLYGON);
	glVertex2f(1400,1300);
	glVertex2f(1800,1600);
	glColor3f(0.10,0.10,0.0);
	glVertex2f(1850,1650);
	glVertex2f(1900,1600);
	glColor3f(0.10,0.10,0.0);

	glVertex2f(2000,1300);
	glEnd();
	glColor3f(0.62,0.42,0.13);
	glBegin(GL_TRIANGLES);
	glVertex2f(2000,1300);
	glColor3f(0.10,0.10,0.0);
	glVertex2f(2200,1600);
		glColor3f(0.10,0.10,0.0);
//	glColor3f(0.60,0.40,0.0);

	glVertex2f(2200,1300);
	glEnd();

	//to draw road for Night

	glPointSize(8.0);
	glColor3f(0.10,0.10,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(2200,700);
	glColor3f(0.05,0.05,0.0);
	glVertex2f(2200,400);
	glColor3f(0.10,0.10,0.0);
	glVertex2f(1700,0);
	glColor3f(0.05,0.07,0.0);
	glVertex2f(1400,0);
	glEnd();
	glColor3f(.8,.7,0.0);
	glBegin(GL_LINES);
	glVertex2f(2200,550);
	glVertex2f(1600,0);
	glVertex2f(2200,560);
	glVertex2f(1590,0);
	glEnd();


}


void draw_pixel(GLint cx,GLint cy)
{	glPolygonMode(GL_FRONT,GL_FILL);

	glBegin(GL_POINTS);

	glVertex2i(cx,cy);

	glEnd();
}


void plotpixels(GLint h,GLint k,GLint x,GLint y)
{
	draw_pixel(x+h,y+k);
    draw_pixel(-x+h,y+k);
	draw_pixel(x+h,-y+k);
	draw_pixel(-x+h,-y+k);

	draw_pixel(y+h,x+k);
	draw_pixel(-y+h,x+k);
	draw_pixel(y+h,-x+k);
	draw_pixel(-y+h,-x+k);

}

void circle_draw(GLint h,GLint k,GLint r)
{
	GLint d=1-r,x=0,y=r;

	while(y>x)
	{
		plotpixels(h,k,x,y);
		if(d<0)
			d+=2*x+3;
		else
		{
			d+=2*(x-y)+5;
			--y;
		}
		++x;
	}
	plotpixels(h,k,x,y);
}

//To draw Sea for DAY

void drawsea()
{glColor3f(0,0,1);
	//glColor3f(0.0,0.6,1.0);
	glBegin(GL_POLYGON);
	glVertex2f(2200,900);
	glVertex2f(2200,900);
	//glColor3f(0.0,0.7,1.0);
	glVertex2f(2200,800);
	glVertex2f(2200,750);
	glVertex2f(1900,700);
	//glColor3f(0.0,0.7,1.0);
	glVertex2f(1850,600);
	glVertex2f(1800,600);
	//glColor3f(.0,0.8,.9);
	glVertex2f(1700,550);
	glVertex2f(1600,550);
	//glColor3f(0.0,0.6,.98);
	glVertex2f(1450,400);
	//glColor3f(.0,0.8,.95);
	glVertex2f(1300,300);
	//glColor3f(.0,0.7,.98);
	glVertex2f(1100,250);
	//glColor3f(.0,0.8,.9);
	glVertex2f(900,200);
	//glColor3f(.0,0.8,.9);
	glVertex2f(700,200);

	//glColor3f(.0,0.7,.9);
	glVertex2f(500,300);
	glVertex2f(400,400);
	//glColor3f(0.0,0.6,.9);
	glVertex2f(300,500);
	glVertex2f(150,600);
	//glColor3f(.0,0.7,.9);
	glVertex2f(0,700);
	glVertex2f(0,1300);
	//glColor3f(.0,0.8,.9);
	glVertex2f(2200,1300);
	glEnd();

}

//To draw sea for NIGHT

void drawsea2()
{
       glColor3f(0,0,1);
	//glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex2f(2200,900);
	//glColor3f(0.,0.,.0);

	glVertex2f(2200,900);
	//glColor3f(.0,0.,.0);
	glVertex2f(2200,800);
	//glColor3f(1.,1.,1.0);
	glVertex2f(2200,750);
	//glColor3f(.0,0.,.0);
	glVertex2f(1900,700);
	//glColor3f(.0,0.,.0);
	glVertex2f(1850,600);
	//glColor3f(.0,0.,.0);
	glVertex2f(1800,600);

	glVertex2f(1700,550);
	//glColor3f(.0,0.,.0);
	glVertex2f(1600,550);
	//glColor3f(.0,0.,.0);

	glVertex2f(1450,400);
	//glColor3f(.0,0.0,.0);
	glVertex2f(1300,300);
	//glColor3f(.0,0.,.0);
	glVertex2f(1100,250);
	//glColor3f(.0,0.0,.0);
	glVertex2f(900,200);
	//glColor3f(.0,0.,.0);
	glVertex2f(700,200);

	//glColor3f(.0,0.0,.0);
	glVertex2f(500,300);
	//glColor3f(.0,0.0,.0);
	glVertex2f(400,400);
	//glColor3f(0.0,0.,.0);
	glVertex2f(300,500);
	//glColor3f(.0,0.0,.0);
	glVertex2f(150,600);
	//glColor3f(.0,0.,.0);
	glVertex2f(0,700);
	//glColor3f(.0,0.0,.0);
	glVertex2f(0,1300);
	//glColor3f(.0,0.,.0);
	glVertex2f(2200,1300);
	//glColor3f(.0,0.,.0);
	glEnd();


}



void night()
{	// to set the background color to black

	glColor3f(0.0,0.0,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(2200,1800);
	glVertex2f(0,1800);
	glVertex2f(0,0);
	glVertex2f(2200,0);
	glEnd();

	//to draw the moon

	glPointSize(9.0);
	glColor3f(1.0,1.0,1.0);

	circle_draw(1400,1600+s,100);
	circle_draw(1400,1600+s,90);
	circle_draw(1400,1600+s,70);
	circle_draw(1400,1600+s,50);
	circle_draw(1400,1600+s,30);
	circle_draw(1400,1600+s,10);
	glPointSize(5.0);



//to draw the stars

	glBegin(GL_POINTS);
	glVertex2f(900,1700);
	glVertex2f(800,1700);
	glVertex2f(1000,1500);
	glVertex2f(1200,1500);
	glVertex2f(1800,1700);
	glVertex2f(1700,1500);
	glVertex2f(2000,1500);
	glEnd();
//	glColor3f(.25,.25,.25);
	mountain2();
	glColor3f(.7,.7,.7);

	drawsea2();

//to draw street light for NIGHT

	glColor3f(0.10,0.10,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(1400,0);
	glColor3f(0.10,0.10,0.0);
	glVertex2f(1425,0);
	glColor3f(0.10,0.10,0.0);
	glVertex2f(1425,250);
	glVertex2f(1400,250);
	glEnd();
	glColor3f(1.0,01.0,01.0);
	circle_draw(1410,280,30);
	circle_draw(1410,280,10);

	glColor3f(0.10,0.10,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(1600,200);
	glColor3f(0.10,0.10,0.0);
	glVertex2f(1625,200);
	glColor3f(0.10,0.10,0.0);
	glVertex2f(1625,350);
	glVertex2f(1600,350);
	glEnd();
	glColor3f(1.0,01.0,01.0);
	circle_draw(1610,380,30);
	circle_draw(1610,380,10);

	glColor3f(0.10,0.10,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(1800,380);
	glColor3f(0.10,0.10,0.0);
	glVertex2f(1825,380);
	glColor3f(0.10,0.10,0.0);
	glVertex2f(1825,525);
	glVertex2f(1800,525);
	glEnd();
	glColor3f(1.0,01.0,01.0);
	circle_draw(1810,555,30);
	circle_draw(1810,555,10);

	glColor3f(0.10,0.10,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(2000,500);
	glColor3f(0.10,0.10,0.0);
	glVertex2f(2025,500);
	glColor3f(0.10,0.10,0.0);
	glVertex2f(2025,650);
	glVertex2f(2000,650);
	glEnd();
	glColor3f(1.0,01.0,01.0);
	circle_draw(2010,680,30);
	circle_draw(2010,680,10);

	//to draw tree and boat

	drawtree2();
	drawsmallboat();
	drawboat();

}

//To draw user BOAT

void drawboat()
{

	glColor3f(0.1,0.0,0.1);
	glBegin(GL_POLYGON);

	glVertex2f(700+800,950);
	glColor3f(.6,0.5,0.0);
	glVertex2f(800+800,800);
	glVertex2f(1200+800,800);
	glColor3f(0.1,0.0,0.1);
	glVertex2f(1400+800,950);
	glEnd();

     glColor3f(.6,0.5,0.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(1200+800,950);

	glColor3f(.6,0.5,0.5);
	glVertex2f(1350+800,950);
	glColor3f(.0,0.2,0.6);
	glVertex2f(1000+800,1150);
	glEnd();
	glPointSize(9.0);
	glBegin(GL_LINES);
	glVertex2f(1000+800,950);
	glVertex2f(1000+800,1150);
	glEnd();

	glColor3f(0.1,0.0,0.1);
	glBegin(GL_POLYGON);
	glVertex2f(850+800,950);
	glVertex2f(1000+800,950);
	glVertex2f(1000+800,1000);
	glVertex2f(850+800,1000);
	glEnd();
}
/*void redrawboat1()
{	if(boat==0)
	{
		if(n<1600)
		{

			n+=2;
			glutPostRedisplay();
		}
		else
		{	n=n-2400;
		glutPostRedisplay();
		}
	}
}
*/

void drawsmallboat()
{
	glColor3f(0.0,1.0,0.0);

	glBegin(GL_POLYGON);

	glVertex2f(400+bi,1200);
		glColor3f(1.0,0.6,.9);
	glVertex2f(475+bi,1100);
	glColor3f(0.3,0.0,0.2);
	glVertex2f(575+bi,1100);
	glVertex2f(650+bi,1200);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2f(550+bi,1200);
	glColor3f(1.0,0.6,.9);

	glVertex2f(650+bi,1200);
	glColor3f(.0,0.2,0.6);
	glVertex2f(500+bi,1250);
	glEnd();
	glPointSize(9.0);
	glBegin(GL_LINES);
	glVertex2f(500+bi,1250);
	glVertex2f(500+bi,1200);
	glEnd();

}

//To loop small boat

void redrawboat()
{	if(boat==0)
	{
		if(bi<1600)
		{

			bi+=2;
			glutPostRedisplay();
		}
		else
		{	bi=bi-2400;
		glutPostRedisplay();
		}
	}
}

// keyboard function

void key(unsigned char key,int x,int y)
{
	if(key=='x')
	{

   	  bi=bi+10;
   	  if(bi>2000) bi=-800;
     glutPostRedisplay();
	}
	if(key=='y')
	{
		bi=bi-10;
		if(bi<-1400) bi=1400;
	glutPostRedisplay();
	}
	if(key=='z')
	{	 s=s+10;
		glutPostRedisplay();
	}
	if(key=='w')
	{	s=s-10;
		glutPostRedisplay();
	}
	if(key=='s') //to stop boat
	{	boat=1;
		glutPostRedisplay();
	}
	if(key=='r') // to restart boat
	{	boat=0;
		glutPostRedisplay();
	}

}


//To draw tree for DAY

void drawtree()
{
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_POLYGON);
	glVertex2f(0,300);
	glVertex2f(100,400);
	glVertex2f(40,400);
		glColor3f(0.30,0.4,0.);
	glVertex2f(150,500);
	glVertex2f(90,500);
	glVertex2f(200,600);
	glColor3f(0.10,0.4,0.);
	glVertex2f(300,500);
	glVertex2f(250,500);

	glVertex2f(350,400);
	glVertex2f(300,400);
	glVertex2f(350,300);
	glEnd();

/*	glColor3f(0.0,0.2,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(400,250);
	glVertex2f(450,350);
//	glVertex2f(400,350);
//	glVertex2f(450,450);
	glColor3f(0.1,0.4,0.);
	glVertex2f(400,450);
	glVertex2f(500,650);
		glColor3f(0.30,0.4,0.);
	glVertex2f(650,450);
	glVertex2f(600,450);
	glColor3f(0.0,0.3,0.2);
	glVertex2f(700,350);
	glVertex2f(650,350);
		glColor3f(0.30,0.4,0.);
	glVertex2f(700,250);
	glEnd();

*/	glColor3f(0.0,0.3,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(750,200);
	glVertex2f(850,300);
	glColor3f(0.30,0.4,0.);

	glVertex2f(800,300);

	glVertex2f(850,400);
	glVertex2f(800,400);
	glColor3f(0.0,0.2,0.1);
	glVertex2f(850,500);
		glColor3f(0.0,0.2,0.0);
	glVertex2f(800,500);
	glVertex2f(900,600);
	glColor3f(0.1,0.4,0.);
	glVertex2f(1000,500);
	glVertex2f(950,500);
	glVertex2f(1100,400);
		glColor3f(0.2,0.4,0.0);
	glVertex2f(1050,400);
	glVertex2f(1150,300);
	glColor3f(0.2,0.5,0.0);
	glVertex2f(1100,300);
	glVertex2f(1150,200);
	glEnd();


//stamp
	glColor3f(.2,0.0,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(150,0);
//		glColor3f(0.47,0.0,0.0);
	glVertex2f(150,300);
	glColor3f(0.57,0.0,0.0);
	glVertex2f(200,300);
	glColor3f(0.47,0.0,0.0);
	glVertex2f(200,0);
	glEnd();


/*	glColor3f(0.2,0.0,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(500,0);
	glVertex2f(500,250);
	glColor3f(0.57,0.0,0.0);
	glVertex2f(550,250);
	glVertex2f(550,0);
	glEnd();

*/	glColor3f(0.2,0.0,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(950,0);
	glVertex2f(950,200);
	glColor3f(0.57,0.0,0.0);
	glVertex2f(1000,200);
	glVertex2f(1000,0);
	glEnd();
}

//To draw tree for NIGHT

void drawtree2()
{
glColor3f(1.0,0.1,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(0,300);

	glVertex2f(100,400);
glColor3f(0.1,0.1,.0);
	glVertex2f(40,400);
	glColor3f(0.,0.,.0);
	glVertex2f(150,500);
	glVertex2f(90,500);
	glVertex2f(200,600);
glColor3f(0.1,0.1,.0);
	glVertex2f(300,500);
	glVertex2f(250,500);
	glColor3f(0.,0.,.0);
	glVertex2f(350,400);
	glVertex2f(300,400);
	glVertex2f(350,300);
	glEnd();


/*	glColor3f(0.1,0.1,.0);
	glBegin(GL_POLYGON);
	glVertex2f(400,250);
	glVertex2f(450,350);
	glColor3f(0.,0.,.0);
	glVertex2f(400,450);
	glVertex2f(500,650);
	glColor3f(0.1,0.1,.0);
	glVertex2f(650,450);
	glVertex2f(600,450);
	glColor3f(0.,0.,.0);
	glVertex2f(700,350);
	glVertex2f(650,350);
	glColor3f(0.1,0.1,.0);
	glVertex2f(700,250);
	glEnd();


*/	glBegin(GL_POLYGON);
	glVertex2f(750,200);
	glVertex2f(850,300);
	glColor3f(0.,0.,.0);
	glVertex2f(800,300);
	glColor3f(0.1,0.1,.0);
	glVertex2f(850,400);
	glVertex2f(800,400);

	glVertex2f(850,500);
	glColor3f(0.1,0.1,.0);

	glVertex2f(800,500);
	glVertex2f(900,600);
	glColor3f(0.,0.,.0);
	glVertex2f(1000,500);
	glVertex2f(950,500);
	glVertex2f(1100,400);
	glColor3f(0.1,0.1,.0);
	glVertex2f(1050,400);
	glVertex2f(1150,300);
	glColor3f(0.,0.,.0);
	glVertex2f(1100,300);
	glVertex2f(1150,200);
	glEnd();


//stamp
	glColor3f(.2,0.0,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(150,0);
	glColor3f(0.,0.,.0);
	glVertex2f(150,300);
		glColor3f(0.1,0.0,0.0);
	glVertex2f(200,300);
		glColor3f(0.2,0.0,0.0);
	glVertex2f(200,0);
	glEnd();


	/*glColor3f(0.2,0.0,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(500,0);
	glVertex2f(500,250);
		glColor3f(0.0,0.0,0.0);
	glVertex2f(550,250);
		glColor3f(0.1,0.0,0.0);
	glVertex2f(550,0);
	glEnd();
*/
	glColor3f(0.2,0.0,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(950,0);
	glVertex2f(950,200);
		glColor3f(0.0,0.0,0.0);
	glVertex2f(1000,200);
		glColor3f(0.1,0.0,0.0);
	glVertex2f(1000,0);
	glEnd();
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,1.0);
	if(glob==1)
		night();
	if(glob==0)
		day();

   redrawboat();
  // redrawboat1();

	glFlush();
	glutSwapBuffers();

}
void day()
{	//to set the sky color and ground color

	glColor3f(.8,.37,0.0);

	glBegin(GL_POLYGON);
	glVertex2f(2200,1800);
	glColor3f(.7,.37,0.0);
	glVertex2f(0,1800);
	glColor3f(.4,.6,0.0);
	glVertex2f(0,0);
			glColor3f(.4,.6,0.0);
	glVertex2f(2200,0);
	glEnd();

	// to draw the mountains
	mountain();

// to draw the sea
	drawsea();

	// to draw the sun

	glPointSize(9.0);
	glColor3f(.9,0.2,0.0);
	circle_draw(1400,1600,100);
	glColor3f(.95,0.2,0.0);
	circle_draw(1400,1600,90);
	glColor3f(1.0,0.25,0.0);
	circle_draw(1400,1600,70);
		glColor3f(1.1,0.3,0.0);
	circle_draw(1400,1600,50);
		glColor3f(1.15,0.35,0.0);
	circle_draw(1400,1600,30);
		glColor3f(1.18,.38,0.0);

	circle_draw(1400,1600,10);

	drawtree();

//to draw street light for DAY

		glColor3f(0.10,0.10,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(1400,0);
		glColor3f(0.10,0.10,0.0);
	glVertex2f(1425,0);
		glColor3f(0.10,0.10,0.0);
	glVertex2f(1425,250);
	glVertex2f(1400,250);
	glEnd();
	glColor3f(1.0,01.0,01.0);
	circle_draw(1410,280,30);
	circle_draw(1410,280,10);

			glColor3f(0.10,0.10,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(1600,200);
		glColor3f(0.10,0.10,0.0);
	glVertex2f(1625,200);
		glColor3f(0.10,0.10,0.0);
	glVertex2f(1625,350);
	glVertex2f(1600,350);
	glEnd();
	glColor3f(1.0,01.0,01.0);
	circle_draw(1610,380,30);
	circle_draw(1610,380,10);

			glColor3f(0.10,0.10,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(1800,380);
		glColor3f(0.10,0.10,0.0);
	glVertex2f(1825,380);
		glColor3f(0.10,0.10,0.0);
	glVertex2f(1825,525);
	glVertex2f(1800,525);
	glEnd();
	glColor3f(1.0,01.0,01.0);
	circle_draw(1810,555,30);
	circle_draw(1810,555,10);

			glColor3f(0.10,0.10,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(2000,500);
		glColor3f(0.10,0.10,0.0);
	glVertex2f(2025,500);
		glColor3f(0.10,0.10,0.0);
	glVertex2f(2025,650);
	glVertex2f(2000,650);
	glEnd();
	glColor3f(1.0,01.0,01.0);
	circle_draw(2010,680,30);
	circle_draw(2010,680,10);
	drawsmallboat();
	drawboat();
		//to draw road DAY

	glPointSize(8.0);
		glColor3f(0.10,0.10,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(2200,700);
		glColor3f(0.05,0.05,0.0);
	glVertex2f(2200,400);
		glColor3f(0.10,0.10,0.0);
	glVertex2f(1700,0);
	glColor3f(0.05,0.07,0.0);
	glVertex2f(1400,0);
	glEnd();
		glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINES);
	glVertex2f(2200,550);
	glVertex2f(1600,0);
	glVertex2f(2200,560);
	glVertex2f(1590,0);
	glEnd();

}
void DrawFountain(void)
{
if(flag==0)
glColor3f(0,1,1);
else if(flag==1)
glColor3fv(X);
else if(flag==2)
glColor3f(0.0,1.0,0.0);
else
glColor3f(1.0,0.0,1.0);
for (int i = 0; i < DropsComplete; i++)
{
FountainDrops[i].GetNewPosition(&FountainVertices[i]);
}
glDrawArrays( GL_POINTS,
0,
DropsComplete);
glutPostRedisplay();
}
void Display(void)
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

glLoadIdentity();


glClearColor(0,0,1,1);
//glClearColor(0.0,0.6,1.0,1);
glTranslatef(0,0.0,-6.0);
//glColor3f(0.0,0.7,1.0);
glTranslatef(0.0,-1.0,0.0);
drawsea();
DrawFountain();

glFlush();
glutSwapBuffers();
}

void Reshape(int x, int y)
{
if (y == 0 || x == 0) return;
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(50.0,(GLdouble)x/(GLdouble)y,0.10,20.0);
glMatrixMode(GL_MODELVIEW);
glViewport(0,0,x,y);
glPointSize(GLfloat(x)/600.0);
}

GLfloat GetRandomFloat(GLfloat range)
{
return (GLfloat)rand() / (GLfloat)RAND_MAX * range * RandomFactor;
}
void InitFountain(void)
{
FountainDrops = new CDrop [ (int)DropsComplete ];
FountainVertices = new SVertex [ (int)DropsComplete ];

	SVertex NewSpeed;
GLfloat DropAccFactor;
GLfloat TimeNeeded;
GLfloat StepAngle;
GLfloat RayAngle;
GLint i,j,k;
for (k = 0; k <Steps; k++)
{
for (j = 0; j < RaysPerStep; j++)
{
for (i = 0; i < DropsPerRay; i++)
{
DropAccFactor = AccFactor + GetRandomFloat(0.0005);
StepAngle = AngleOfDeepestStep + (90.0-AngleOfDeepestStep)
* GLfloat(k) / (Steps-1) + GetRandomFloat(0.2+0.8*(Steps-k-1)/(Steps-1));
NewSpeed.x = cos ( StepAngle * PI / 180.0) * (0.2+0.04*k);
NewSpeed.y = sin ( StepAngle * PI / 180.0) * (0.2+0.04*k);
RayAngle = (GLfloat)j / (GLfloat)RaysPerStep * 360.0;
NewSpeed.z = NewSpeed.x * sin ( RayAngle * PI /180.0);
NewSpeed.x = NewSpeed.x * cos ( RayAngle * PI /180.0);
TimeNeeded = NewSpeed.y/ DropAccFactor;
FountainDrops[i+j*DropsPerRay+k*DropsPerRay*RaysPerStep].SetConstantSpeed ( NewSpeed );
FountainDrops[i+j*DropsPerRay+k*DropsPerRay*RaysPerStep].SetAccFactor (DropAccFactor);
FountainDrops[i+j*DropsPerRay+k*DropsPerRay*RaysPerStep].SetTime(TimeNeeded * i / DropsPerRay);
}
}
}
glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer( 3,GL_FLOAT,0,FountainVertices);
}

void mainmenu(int id)
{
	switch(id)
	{
		case 1:exit(0);
		break;
		case 2:glob=0;
			break;
		case 3:glob=1;
			break;

	}
	glutPostRedisplay();
}


void randcolor()
{
GLint a,b,c;
a=rand()%101;
b=rand()%101;
c=rand()%101;
X[0]=(GLfloat)a/100.0;
X[1]=(GLfloat)b/100.0;
X[2]=(GLfloat)c/100.0;
}
void colour(int id)
{
flag=id;
if(flag==1)
randcolor();
glutPostRedisplay();
}


int main(int argc,char** argv)
{
int ww;

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(2200,1800);
	glutInitWindowPosition(0,0);
	id=glutCreateWindow("sea view");

	glutKeyboardFunc(key);
	glutDisplayFunc(display);

	glutCreateMenu(mainmenu);
	glutAddMenuEntry("QUIT",1);
	glutAddMenuEntry("DAY VIEW",2);
	glutAddMenuEntry("NIGHT VIEW",3);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	//glutCreateSubWindow(id,200,200,400,400);
	init();
	ww=glutCreateSubWindow(id,250,300,100,200);
        glEnable(GL_DEPTH_TEST);
InitFountain();

glutDisplayFunc(Display);
glutReshapeFunc(Reshape);
glutCreateMenu(colour);
//int sub_menu=glutCreateMenu(colours);
glutAddMenuEntry("RANDOM",1);
glutAddMenuEntry("GREEN",2);
glutAddMenuEntry("PINK",3);
glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}

