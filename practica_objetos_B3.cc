//**************************************************************************
// Práctica 3 
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B3.h"
#include <unistd.h> // Necesitas esta biblioteca para usar usleep


using namespace std;

// tipos
typedef enum{CUBO, PIRAMIDE, CUBO_M, OBJETO_PLY, ROTACION, CILINDRO, CONO, CONOTRUN, ESFERA, EXTRUSION, AVIONETA, OBJETILLO, MONTANA} _tipo_objeto;
_tipo_objeto t_objeto=CUBO;
_modo   modo=POINTS;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=650,Window_high=650;


// objetos
_cubo cubo;
_piramide piramide(0.85,1.3);
_cubo_m cubo_m;
_objeto_ply  ply; 
_rotacion rotacion;
_cilindro cilindro(1,2,50); 
_cono cono(1,2,50);
_conoTrun conoTrun(1,2,50);
_esfera esfera(1,50,50);
_avioneta avioneta;
_extrusion *extrusion;
_objetillo_ply objetillo;
_montana montana(6,0.9, 0.8);

int paso = 20;
int pulsar = 0;
float giro1 = 0.0;
float giro2 = 0.0;
float giro3 = 0.0;
float alfa = 0.0;

// _objeto_ply *ply;

//**************************************************************************
//
//***************************************************************************

void clean_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
//  plano_delantero>0  plano_trasero>PlanoDelantero)
glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
	
glDisable(GL_LIGHTING);
glLineWidth(2);
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//****************************2***********************************************

void draw_objects()
{

switch (t_objeto){
	case CUBO: cubo.draw(modo,1.0,0.0,0.0,5);break;
	case PIRAMIDE: piramide.draw(modo,1.0,0.0,0.0,5);break;
        case CUBO_M: cubo_m.draw(modo,1.0,0.0,0.0,5);break;
        case OBJETO_PLY: ply.draw(modo,1.0,0.6,0.0,5);break;
        case ROTACION: rotacion.draw(modo,1.0,0.0,0.0,5);break;
        case CILINDRO: cilindro.draw(modo,1.0,0.0,0.0,5);break;
        case CONO: cono.draw(modo,1.0,0.0,0.0,5);break;
        case CONOTRUN: conoTrun.draw(modo,1.0,0.0,0.0,5);break;
        case ESFERA: esfera.draw(modo,1.0,0.0,0.0,5);break;
        case AVIONETA: avioneta.draw(modo,1.0,0.0,0.0,5);break;
        case EXTRUSION: extrusion->draw(modo,1.0,0.0,0.0,5);break;
        case OBJETILLO: objetillo.draw(modo,1.0,0.0,0.0,5);break;
        case MONTANA: montana.draw(modo,0.2,0.7,0.0,1);break;
	}

}

//**************************************************************************
// Luces
//***************************************************************************
void luces(float alfa){
        GLfloat luz_ambiente[] = {0.2, 0.2, 0.2, 1.0},
                luz_difusa[] = {1.0, 1.0, 1.0, 1.0},
                luz_especular[] = {20, 20, 20, 1.0},
                luz_posicion[] = {10,10,10,10,10};
        
        GLfloat luz_ambiente2[] = {0.05, 0.05, 0.05, 1.0},
                luz_difusa2[] = {0.0, 1.0, 0.0, 1.0},
                luz_especular2[] = {0.0, 1.0, 0.0, 1.0},
                luz_posicion2[] = {10,10,10,10,10}; 

        glLightfv(GL_LIGHT1, GL_AMBIENT, luz_ambiente);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, luz_difusa);
        glLightfv(GL_LIGHT1, GL_SPECULAR, luz_especular);
        glLightfv(GL_LIGHT1, GL_POSITION, luz_posicion);

        glLightfv(GL_LIGHT2, GL_AMBIENT, luz_ambiente2);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, luz_difusa2);
        glLightfv(GL_LIGHT2, GL_SPECULAR, luz_especular2);

        glPushMatrix();
        glRotatef(alfa,0,0,1);
        glLightfv(GL_LIGHT1, GL_POSITION, luz_posicion2);
        glPopMatrix();

        glDisable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        glEnable(GL_LIGHT2);
}


//**************************************************************************
//
//***************************************************************************

void draw(void)
{
clean_window();
change_observer();
luces(alfa);
draw_axis();
draw_objects();
glutSwapBuffers();
}


//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
float Aspect_ratio;

Aspect_ratio=(float) Alto1/(float )Ancho1;
Size_y=Size_x*Aspect_ratio;
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1,int x,int y)
{
switch (toupper(Tecla1)){
	case 'Q':exit(0);
	case '1':modo=POINTS;break; // Bien
	case '2':modo=EDGES;break; // Bien
	case '3':modo=SOLID;break; // Bien
	case '4':modo=SOLID_COLORS;break; // Ni compila
        case '5':modo=SOLID_COLORS_GOURAUD;break; // Ni compila
        case '6':modo=SOLID_PHONG_FLAT;break; // Ni compila
        case '7':modo=SOLID_PHONG_GOURAUD;break; // Bien
        case 'P':t_objeto=PIRAMIDE;break;
        case 'C':t_objeto=CUBO;break;
        case 'M':t_objeto=CUBO_M;break;
        case 'O':t_objeto=OBJETO_PLY;break;	
        case 'R':t_objeto=ROTACION;break; 
        case 'L':t_objeto=CILINDRO;break;
        case 'N':t_objeto=CONO;break;
        case 'T':t_objeto=CONOTRUN;break;
        case 'E':t_objeto=ESFERA;break;
        case 'A':t_objeto=AVIONETA;break; 
        case 'X':t_objeto=EXTRUSION;break;
        case 'J':t_objeto=OBJETILLO;break;
        case 'B':t_objeto=MONTANA;break;
        case 'Z': if (pulsar == 0){
                        giro1 = 1.0;
                        giro2 = 1.0;
                        giro3 = 1.0;
                }else {
                        giro1 = 0.0;
                        giro2 = 0.0;
                        giro3 = 0.0;
                }; break;
	}
glutPostRedisplay();
}


//***************************************************************************
// Funcion animación
//
//***************************************************************************

void animacion(){
        static float x = 0.5;  // Usa 'static' para conservar el valor de 'x' entre llamadas.
        static int cont = 0;
        bool acabo = false;

        switch (paso)
        {
              
        case 0:
        // Despegue: Gira las hélices hasta llegar a una velocidad determinada y despega
                avioneta.giro_helice += x/6;
                if(x < 100)
                        x++;

                if(x >= 100){
                        avioneta.despegue+=0.4;
                        if(avioneta.despegue > avioneta.despegue_max){
                                avioneta.despegue = avioneta.despegue_max;
                                paso = 1;
                                break;
                        }
                
                }
                break;
                
        case 1:
        // Despegue: Sube el tren de aterrizaje y sigue subiendo (las hélices siguen girando)
                avioneta.giro_helice += x/2;

                avioneta.ruedas+=0.009; 
                if(avioneta.ruedas > avioneta.ruedas_max/2){
                        avioneta.tam_sus-=0.01;
                        if(avioneta.tam_sus <= avioneta.tam_sus_min){
                                avioneta.tam_sus = avioneta.tam_sus_min;
                                acabo = true;
                        }
                }
                if(avioneta.ruedas > avioneta.ruedas_max){
                        avioneta.ruedas = avioneta.ruedas_max;
                        if (acabo){
                                acabo = false;
                                paso = 2;
                        }
                }
                break;

        case 2:
        // Las hélices siguen girando y el avión se estabiliza bajando un poco
                avioneta.giro_helice += x/2;
                avioneta.despegue-=0.6;
                if(avioneta.despegue < -avioneta.despegue_max/2){
                        avioneta.despegue = -avioneta.despegue_max/2;
                        paso = 3;
                }
                break;
        
        case 3: 
        // Las hélices siguen girando y el avión se estabiliza subiendo un poco
                avioneta.giro_helice += x/2;
                avioneta.despegue+=0.5;
                        if(avioneta.despegue > avioneta.despegue_max/3){
                                avioneta.despegue = avioneta.despegue_max/3;
                                paso = 4;
                                break;
                        }
        case 4:
        // Fuego abierto: Las hélices siguen girando y el avión dispara
                avioneta.giro_helice += x/2;
                avioneta.balas += 0.2;
                if (avioneta.balas > avioneta.balas_max) {
                        avioneta.balas = 0.0;
                        cont++;
                }
                if (cont == 3)
                {
                        cont = 0;
                        paso = 5;
                }
                
                break;

        case 5: // Acrobacia: El avión hace un loop
                avioneta.giro_helice += x/2;
                avioneta.giro_avioneta += 5;
                if(avioneta.giro_avioneta > 360)
                        paso = 6;
                break;

        case 6:
        // Fuego abierto: Las hélices siguen girando y va haciendo loop despacio
                avioneta.giro_helice += x/2;
                avioneta.giro_avioneta -= 2;
                cont++;
                if (cont == 100)
                {
                        cont = 0;
                        paso = 7;
                }
                break;
        
        case 7: // Acrobacia: El avión hace el loop contrario y dispara
                avioneta.giro_helice += x/2;
                avioneta.balas += 0.2;
                avioneta.giro_avioneta -= 7;
                if (avioneta.balas > avioneta.balas_max) {
                        avioneta.balas = 0.0;
                }
                if(avioneta.giro_avioneta < -360){
                        avioneta.giro_avioneta = 0;
                        paso = 8;
                }

                break;

        case 8:
                // Las hélices siguen girando y el avión se estabiliza bajando un poco
                avioneta.giro_helice += x/2;
                avioneta.despegue-=0.6;
                if(avioneta.despegue < -avioneta.despegue_max*2){
                        avioneta.despegue = -avioneta.despegue_max*2;
                        paso = 9;
                }
                break;
        
        case 9:
                //Las hélices siguen girando y el avion despliega el tren de aterrizaje
                avioneta.giro_helice += x/2;
                avioneta.ruedas-=0.009; 
                if(avioneta.ruedas > avioneta.ruedas_max/3){
                        avioneta.tam_sus+=0.01;
                }
                if(avioneta.ruedas < 0.0){
                        avioneta.ruedas = 0.0;
                        paso = 10;
                }
                break;
        
        case 10:
        // Las hélices siguen girando y el avión se estabiliza subiendo un poco
                avioneta.giro_helice += x/2;
                avioneta.despegue+=0.3;
                if(avioneta.despegue >= 0.0){
                        paso = 11;
                       
                }
                break;

        case 11: // El avión ha aterrizado
                if (x > 0){
                        avioneta.giro_helice -= x/30;
                        x -= 1;
                }
                if (avioneta.giro_helice <= 0){
                        avioneta.giro_helice = 0;  
                        paso = 12;
                        break; 
                }

                
        case 12: // El avion se queda quieto y abre la cabina
                avioneta.giro_ventanilla = avioneta.giro_ventanilla - 6;
                if(avioneta.giro_ventanilla < avioneta.giro_ventanilla_min){
                        paso = 13;
                        break;
                }


        case 13: // El avión se queda quieto y cierra la cabina
                avioneta.giro_ventanilla+=2;
                if(avioneta.giro_ventanilla > avioneta.giro_ventanilla_max)
                        avioneta.giro_ventanilla = avioneta.giro_ventanilla_max;
                break;
        }
        glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1,int x,int y)
{
// bool acabo = false;

switch (Tecla1){
        case GLUT_KEY_LEFT:Observer_angle_y--;break;
        case GLUT_KEY_RIGHT:Observer_angle_y++;break;
        case GLUT_KEY_UP:Observer_angle_x--;break;
        case GLUT_KEY_DOWN:Observer_angle_x++;break;
        case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
        case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
                
        case GLUT_KEY_F1: // Avioneta gira las hélices
        static int x = 0.5;  // Usa 'static' para conservar el valor de 'x' entre llamadas.
        avioneta.giro_helice += x/2;
        if(x < 70)
                x++;
        break;

        case GLUT_KEY_F2: // Avioneta sube
                avioneta.despegue+=0.4;
                if(avioneta.despegue > avioneta.despegue_max)
                avioneta.despegue = avioneta.despegue_max;break;

        case GLUT_KEY_F3: //Avioneta baja
                avioneta.despegue-=0.4;
                if(avioneta.despegue < -avioneta.despegue_max)
                        avioneta.despegue = -avioneta.despegue_max;break;

        case GLUT_KEY_F4: // Avioneta sube el tren de aterrizaje
        //Hay que tener en cuenta que como no cabía todo el tren de aterrizaje, 
        //en tiempo real tengo que ajustar el tamaño de forma que no se note
                avioneta.ruedas+=0.009; 
                if(avioneta.ruedas > avioneta.ruedas_max/2){
                        avioneta.tam_sus-=0.01;
                        if(avioneta.tam_sus <= avioneta.tam_sus_min){
                                avioneta.tam_sus = avioneta.tam_sus_min;
                        }
                }
                if(avioneta.ruedas > avioneta.ruedas_max){
                        avioneta.ruedas = avioneta.ruedas_max;
                }
                break;

        case GLUT_KEY_F5: // Avioneta baja el tren de aterrizaje
        //Hay que tener en cuenta que como no cabía todo el tren de aterrizaje, 
        //en tiempo real tengo que ajustar el tamaño de forma que no se note
                avioneta.ruedas-=0.009; 
                if(avioneta.ruedas > avioneta.ruedas_max/2){
                        avioneta.tam_sus+=0.01;
                        if(avioneta.tam_sus >= avioneta.tam_sus_og){
                                avioneta.tam_sus = avioneta.tam_sus_og;
                        }
                }
                if(avioneta.ruedas < 0.0){
                        avioneta.ruedas = 0.0;
                }
                break;

        case GLUT_KEY_F6: // Avioneta abre la ventanilla
                avioneta.giro_ventanilla-=2;
                if(avioneta.giro_ventanilla < avioneta.giro_ventanilla_min)
                        avioneta.giro_ventanilla = avioneta.giro_ventanilla_min;break;
        
        case GLUT_KEY_F7: // Avioneta cierra la ventanilla
                avioneta.giro_ventanilla+=2;
                if(avioneta.giro_ventanilla > avioneta.giro_ventanilla_max)
                        avioneta.giro_ventanilla = avioneta.giro_ventanilla_max;break;

        case GLUT_KEY_F8: // Avioneta dispara balas
                avioneta.balas += 0.2;
                if (avioneta.balas > avioneta.balas_max) {
                        avioneta.balas = 0.0;
                }break;

        case GLUT_KEY_F9: // Avioneta acrobacia
                avioneta.giro_avioneta += 10;break;

        case GLUT_KEY_F10: // Avioneta acrobacia inversa
                avioneta.giro_avioneta -= 10;break;

        case GLUT_KEY_F11: // Animación
                paso = 0;
                animacion();
                break;

}

glutPostRedisplay();
}


//***************************************************************************
// Funcion del menu
//***************************************************************************
void menu(int key){
        switch (key){

                case 0: paso=0;
                        animacion(); break;
                case 1: 
                        paso = 20;
                        printf("Se detuvo la animación"); break;
        }
        glutPostRedisplay();

}


//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Size_x=0.5;
Size_y=0.5;
Front_plane=1;
Back_plane=1000;

// se incia la posicion del observador, en el eje z
Observer_distance=5*Front_plane;
Observer_angle_x=3;
Observer_angle_y=-25;

// se indica el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(0.84, 0.92, 1.0, 1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,Window_width,Window_high);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


int main(int argc, char *argv[] )
{
 
// perfil 

vector<_vertex3f> perfil, poligono;
_vertex3f aux;

aux.x=1.0; aux.y=-1.0; aux.z=0.0;
perfil.push_back(aux);
aux.x=1.5; aux.y=0.0; aux.z=0.0;
perfil.push_back(aux);
aux.x=1.0; aux.y=1.0; aux.z=0.0;
perfil.push_back(aux);
aux.x=1.5; aux.y=1.2; aux.z=0.0;
perfil.push_back(aux);


rotacion.parametros(perfil,6,1,1,0);

aux.x=1.0; aux.y=0.0; aux.z=1.0;
poligono.push_back(aux);
aux.x=1.0; aux.y=0.0; aux.z=-1.0;
poligono.push_back(aux);
aux.x=-1.2; aux.y=0.0; aux.z=-1.0;
poligono.push_back(aux);
aux.x=-0.8; aux.y=0.0; aux.z=0.0;
poligono.push_back(aux);
aux.x=-1.2; aux.y=0.0; aux.z=1.0;
poligono.push_back(aux);

extrusion= new _extrusion(poligono, 0.25, 1.0, 0.25);

// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(Window_x,Window_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(Window_width,Window_high);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("PRACTICA - 3");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "change_window_size" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "normal_key" al evento correspondiente
glutKeyboardFunc(normal_key);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);

glutIdleFunc(animacion);

//Creamos menu
glutCreateMenu(menu);
glutAddMenuEntry("Animacion", 0);
glutAddMenuEntry("Acabar con la animacion", 1);
glutAttachMenu(GLUT_RIGHT_BUTTON);

// funcion de inicialización
initialize();

// creación del objeto ply
ply.parametros(argv[1]);
objetillo.parametrosply(argv[2], 20);

//ply = new _objeto_ply(argv[1]);

// inicio del bucle de eventos
glutMainLoop();
return 0;
}