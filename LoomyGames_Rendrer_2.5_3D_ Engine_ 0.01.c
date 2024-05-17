
#include <math.h>
#include <stdio.h>
#include <GL/glut.h> 

#define res        1                        //0=160x120 1=360x240 4=640x480
#define SW         160*res                  //screen width
#define SH         120*res                  //screen height
#define SW2        (SW/2)                   //half of screen width
#define SH2        (SH/2)                   //half of screen height
#define pixelScale 4/res                    //OpenGL pixel scale
#define GLSW       (SW*pixelScale)          //OpenGL window width
#define GLSH       (SH*pixelScale)          //OpenGL window height
//------------------------------------------------------------------------------
typedef struct 
{
 int fr1,fr2;           //frame 1 frame 2, to create constant frame rate
}time; time Time;

typedef struct 
{
 int w,s,a,d;           //move up, down, left, right
 int sl,sr;             //strafe left, right 
 int m;                 //move up, down, look up, down
}keys; keys Key;

typedef struct 
{
 float cos[360];  /* data */
 float sin[360];
}math; math Math;

typedef struct 
{
  int x,y,z; /* Position */
  int angle;
  int pich;
}Player; Player Player1;


//------------------------------------------------------------------------------

void pixel(int x,int y, int c)                  //draw a pixel at x/y with rgb
{int rgb[3];
 if(c==0)
    {
         rgb[0]=255; rgb[1]=255; rgb[2]=  0;//Yellow
    } 	
 if(c==1)
    { 
        rgb[0]=160; rgb[1]=160; rgb[2]=  0;//Yellow darker
    } 
 if(c==2)
    { 
        rgb[0]=  0; rgb[1]=255; rgb[2]=  0;//Green
    } 	
 if(c==3)
    { 
        rgb[0]=  0; rgb[1]=160; rgb[2]=  0;//Green darker	
    } 
 if(c==4)
    { 
        rgb[0]=  0; rgb[1]=255; rgb[2]=255;//Cyan
    } 	
 if(c==5)
    { 
        rgb[0]=  0; rgb[1]=160; rgb[2]=160;//Cyan darker
    } 
 if(c==6)
    { 
        rgb[0]=160; rgb[1]=100; rgb[2]=  0;//brown
    } 	
 if(c==7)
    { 
        rgb[0]=110; rgb[1]= 50; rgb[2]=  0;//brown darker
    } 
 if(c==8)
    {
         rgb[0]=  0; rgb[1]= 60; rgb[2]=130;//background 
    } 

 glColor3ub(rgb[0],rgb[1],rgb[2]); 
 glBegin(GL_POINTS);
 glVertex2i(x*pixelScale+2,y*pixelScale+2);
 glEnd();
}

void movePlayer()
{
 //move up, down, left, right
 if(Key.a ==1 && Key.m==0)
    {
         printf("left\n");

         Player1.angle-=4;

         if(Player1.angle< 0)
            {
               Player1.angle+=360;
            }
    }  

 if(Key.d ==1 && Key.m==0)
    {
         printf("right\n");

         Player1.angle+=4;

         if(Player1.angle>359)
         {
            Player1.angle-=360;
         }
         
    }  
 if(Key.w ==1 && Key.m==0)
    {
         printf("up\n");
    }
 if(Key.s ==1 && Key.m==0)
    { 
        printf("down\n");
    }
 //strafe left, right
 if(Key.sr==1)
    {
         printf("strafe left\n");
    }
 if(Key.sl==1)
    {
         printf("strafe right\n");
    }
 //move up, down, look up, look down
 if(Key.a==1 && Key.m==1)
    {
         printf("look up\n");
    }
 if(Key.d==1 && Key.m==1)
    {
         printf("look down\n");
    }
 if(Key.w==1 && Key.m==1)
    {
        printf("move up\n");
    }
 if(Key.s==1 && Key.m==1)
    {
        printf("move down\n");
    }
}

void clearBackground() 
{
    
int x,y;

 for(y=0;y<SH;y++)
 { 
  for(x=0;x<SW;x++)
    {
         pixel(x,y,8); //clear background color
    } 
 }	
}

int tick;

void draw3D()
{
   int x,y,c=0;

 for(y=0;y<SH2;y++)
 {

  for(x=0;x<SW2;x++)
  {
   pixel(x,y,c); 
   c+=1; 

   if(c>8)
    {
        c=0;
    }
  }
 }
 //frame rate
 tick+=1; 
 if(tick>20)
    { 
        tick=0;
    } 

pixel(SW2,SH2+tick,6); 

}

void display() 
{

int x,y;

 if(Time.fr1-Time.fr2>=50)                        //only draw 20 frames/second
 { 
  clearBackground();
  movePlayer();
  draw3D(); 

  Time.fr2=Time.fr1;   
  glutSwapBuffers(); 
  glutReshapeWindow(GLSW,GLSH);             //prevent window scaling
 }

 Time.fr1=glutGet(GLUT_ELAPSED_TIME);          //1000 Milliseconds per second
 glutPostRedisplay();
} 

void KeysDown(unsigned char key,int x,int y)   
{ 
 if(key=='w'==1)
    {
         Key.w =1;
    } 

 if(key=='s'==1)
    {
         Key.s =1;
    } 

 if(key=='a'==1)    
    { 
        Key.a =1;
    } 

 if(key=='d'==1)
    { 
        Key.d =1;
    } 

 if(key=='m'==1)
    {
        Key.m =1;
    } 

 if(key==','==1)
    { 
        Key.sr=1;
    } 

 if(key=='.'==1)
    {
         Key.sl=1;
    } 
}

void KeysUp(unsigned char key,int x,int y)
    { 
if(key=='w'==1)
    {
        Key.w =0;
    }

if(key=='s'==1)
    {
        Key.s =0;
    }

 if(key=='a'==1)
    { 
        Key.a =0;
    }

 if(key=='d'==1)
    { 
        Key.d =0;
    }

 if(key=='m'==1)
    { 
        Key.m =0;
    }

 if(key==','==1)
    { 
        Key.sr=0;
    } 

 if(key=='.'==1)
    { 
        Key.sl=0;
    }

}

void init()
{
    int x;

    for (x=0;x<360;x++)
    {
      Math.cos[x]=cos(x/180.0*M_PI);
      Math.sin[x]=sin(x/180.0*M_PI);
    } 

    Player1.x=70;
    Player1.y=110;  
    Player1.z=20;
    Player1.angle=0;
    Player1.pich=0;
}

int main(int argc, char* argv[])
{
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 glutInitWindowPosition(GLSW/2,GLSH/2);
 glutInitWindowSize(GLSW,GLSH);
 glutCreateWindow("©LoomyGames"); 
 glPointSize(pixelScale);                        //pixel size
 gluOrtho2D(0,GLSW,0,GLSH);                      //origin bottom left
 init();
 glutDisplayFunc(display);
 glutKeyboardFunc(KeysDown);
 glutKeyboardUpFunc(KeysUp);
 glutMainLoop();
 return 0;
} 

