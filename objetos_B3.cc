//**************************************************************************
// Práctica 4
//**************************************************************************

#include "objetos_B3.h"
#include "file_ply_stl.hpp"
#include <time.h> 


//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
//**** usando vertex_array ****
glPointSize(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawArrays(GL_POINTS,0,vertices.size()); 

// int i;
// glPointSize(grosor);
// glColor3f(r,g,b);
// glBegin(GL_POINTS);
// for (i=0;i<vertices.size();i++){
// 	glVertex3fv((GLfloat *) &vertices[i]);
// 	}
// glEnd();
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
  calculadas_normales_caras=0;

  //material por defecto

  ambiente = _vertex4f(1.0, 0.8, 0.0, 1.0);
  difuso = _vertex4f(1.0, 0.8, 0.0, 1.0);
  especular = _vertex4f(0.5, 0.5, 0.5, 1.0);
  brillo = 10;

}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
  /*usando vertex_array ****
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  glLineWidth(grosor);
  glColor3f(r,g,b);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
  glDrawElements(GL_TRIANGLES,caras.size()*3,GL_UNSIGNED_INT,&caras[0]);
  */

  int i;
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glLineWidth(grosor);
  glColor3f(r, g, b);
  glBegin(GL_TRIANGLES);
  for (i = 0; i < caras.size(); i++)
  {
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();
}

//*************************************************************************
// dibujar en modo sólido con un único color
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
long unsigned int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); // Podríamos dividirlo en Front y en back y a partir de ahí poner las caras de atrás negras
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();

}

//*************************************************************************
// dibujar en modo sólido con colores diferentes para cada cara
//*************************************************************************


void _triangulos3D::draw_solido_colores( )
{
long unsigned int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glColor3f(colores_caras[i].r,colores_caras[i].g,colores_caras[i].b);
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// Dibujar en modo sólido con colores diferentes para cada vértice
//*************************************************************************
void _triangulos3D::draw_solido_colores_vertices( )
{
  int i;
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glShadeModel(GL_SMOOTH);
  glBegin(GL_TRIANGLES);
  for (i = 0; i < caras.size(); i++)
  {
    glColor3f(colores_vertices[caras[i]._0].r, colores_vertices[caras[i]._0].g, colores_vertices[caras[i]._0].b);
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
    glColor3f(colores_vertices[caras[i]._1].r, colores_vertices[caras[i]._1].g, colores_vertices[caras[i]._1].b);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
    glColor3f(colores_vertices[caras[i]._2].r, colores_vertices[caras[i]._2].g, colores_vertices[caras[i]._2].b);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();
  glShadeModel(GL_FLAT);
}


//*************************************************************************
// Dibujar en modo iluminación con brilo para las caras
//*************************************************************************
void _triangulos3D::draw_solido_brillo_plano(){
  glShadeModel(GL_FLAT);
  glEnable(GL_NORMALIZE);
  glEnable(GL_LIGHTING);

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat *)&ambiente);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat *)&difuso);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *)&especular);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);

  int i;
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLES);
  for (i = 0; i < caras.size(); i++)
  {
    glNormal3f(normales_caras[i].x, normales_caras[i].y, normales_caras[i].z);
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();

  glDisable(GL_LIGHTING);

}


//*************************************************************************
// Dibujar en modo iluminación con brilo suave para las caras
//*************************************************************************
void _triangulos3D::draw_solido_brillo_suave(){
  glShadeModel(GL_SMOOTH);
  glEnable(GL_NORMALIZE);
  glEnable(GL_LIGHTING);

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat *)&ambiente);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat *)&difuso);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *)&especular);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);

  int i;
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLES);
  for (i = 0; i < caras.size(); i++)
  {
    glNormal3f(normales_vertices[caras[i]._0].x, normales_vertices[caras[i]._0].y, normales_vertices[caras[i]._0].z);
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
    glNormal3f(normales_vertices[caras[i]._1].x, normales_vertices[caras[i]._1].y, normales_vertices[caras[i]._1].z);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
    glNormal3f(normales_vertices[caras[i]._2].x, normales_vertices[caras[i]._2].y, normales_vertices[caras[i]._2].z);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();

  glDisable(GL_LIGHTING);

}



//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r, float g, float b, float grosor)
{
switch (modo){
	case POINTS:draw_puntos(r, g, b, grosor);break;
	case EDGES:draw_aristas(r, g, b, grosor);break;
	case SOLID:draw_solido(r, g, b);break;
	case SOLID_COLORS:draw_solido_colores();break;
  case SOLID_COLORS_GOURAUD:draw_solido_colores_vertices();break;
  case SOLID_PHONG_FLAT:draw_solido_brillo_plano();break;
  case SOLID_PHONG_GOURAUD:draw_solido_brillo_suave();break;
	}
}



//*************************************************************************
// Calculo de normales de caras
//*************************************************************************
void _triangulos3D::calcular_normales_caras()
{
int i, n_c;
_vertex3f va, vb;
float modulo;

n_c=caras.size();
normales_caras.resize(n_c);
for (i=0;i<n_c;i++)
  {va=vertices[caras[i]._1]-vertices[caras[i]._0];
   vb=vertices[caras[i]._2]-vertices[caras[i]._1];
   normales_caras[i].x=va.y*vb.z-va.z*vb.y;
   normales_caras[i].y=va.z*vb.x-va.x*vb.z;   
   normales_caras[i].z=va.x*vb.y-va.y*vb.x; 
   modulo=sqrt(normales_caras[i].x*normales_caras[i].x+
              normales_caras[i].y*normales_caras[i].y+
              normales_caras[i].z*normales_caras[i].z);
   normales_caras[i].x/=modulo;
   normales_caras[i].y/=modulo;   
   normales_caras[i].z/=modulo;     
  }
}

//*************************************************************************
// Calculo de normales de vertices
//*************************************************************************
void _triangulos3D::calcular_normales_vertices()
{
  int i, n_c, n_v;
  float modulo;

  if (calculadas_normales_caras == 0)
    calcular_normales_caras();

  n_v = vertices.size();
  n_c = caras.size();
  normales_vertices.resize(n_v);

  for (i = 0; i < n_v; i++)
  {
    normales_vertices[i].x = 0.0;
    normales_vertices[i].y = 0.0;
    normales_vertices[i].z = 0.0;
  }

  for (i = 0; i < n_c; i++)
  {
    normales_vertices[caras[i]._0] += normales_caras[i];
    normales_vertices[caras[i]._1] += normales_caras[i];
    normales_vertices[caras[i]._2] += normales_caras[i];
  }

  //normalización
  for (i = 0; i < n_v; i++)
  {
    modulo = sqrt(normales_vertices[i].x * normales_vertices[i].x +
                  normales_vertices[i].y * normales_vertices[i].y +
                  normales_vertices[i].z * normales_vertices[i].z);

    normales_vertices[i].x /= modulo;
    normales_vertices[i].y /= modulo;
    normales_vertices[i].z /= modulo;
  }

  calculadas_normales_caras=1;
}
//*************************************************************************
// asignación colores
//*************************************************************************

void _triangulos3D::colors_random()
{
int i, n_c;
n_c=caras.size();
colores_caras.resize(n_c);
srand (time(NULL));
for (i=0;i<n_c;i++)  
  {colores_caras[i].r=rand()%1000/1000.0;
   colores_caras[i].g=rand()%1000/1000.0;
   colores_caras[i].b=rand()%1000/1000.0;
  }
}

//*************************************************************************

void _triangulos3D::colors_chess(float r1, float g1, float b1, float r2, float g2, float b2)
{
int i, n_c;
n_c=caras.size();
colores_caras.resize(n_c);
for (i=0;i<n_c;i++)  
  {if (i%2==0) 
     {colores_caras[i].r=r1;
      colores_caras[i].g=g1;
      colores_caras[i].b=b1;
     }
   else 
     {colores_caras[i].r=r2;
      colores_caras[i].g=g2;
      colores_caras[i].b=b2;
     } 
  }
}



//*************************************************************************
// clase colores difusos
//*************************************************************************

void _triangulos3D::colors_diffuse_flat (float kr, float kg, float kb,
                             float lpx, float lpy, float lpz)
{
int i, n_c;
float modulo, escalar;
_vertex3f l;

n_c=caras.size();
colores_caras.resize(n_c);
for (i=0;i<n_c;i++)
  {
   l.x=lpx-vertices[caras[i]._0].x;
   l.y=lpy-vertices[caras[i]._0].y;
   l.z=lpz-vertices[caras[i]._0].z;
   modulo=sqrt(l.x*l.x+l.y*l.y+l.z*l.z);
   l.x/=modulo;
   l.y/=modulo;
   l.z/=modulo;
   
   escalar=l.x*normales_caras[i].x+l.y*normales_caras[i].y+l.z*normales_caras[i].z;
   if (escalar>0.0)
     {colores_caras[i].r=kr*escalar;
      colores_caras[i].g=kg*escalar;
      colores_caras[i].b=kb*escalar;
     }
   else {colores_caras[i].r=0.0;
        colores_caras[i].g=0.0;
        colores_caras[i].b=0.0;
        }
  }
}

//*************************************************************************
// Colores difuso Gouraud
//*************************************************************************
void _triangulos3D::colors_diffuse_gouraud(float kr, float kg, float kb, float lpx, float lpy, float lpz){
  int i, n_v;
  _vertex3f dif_pto_luz;
  float modulo, escalar;
  n_v = vertices.size();
  colores_vertices.resize(n_v);

  for (i=0; i<n_v; i++){

    dif_pto_luz.x = lpx - vertices[i].x;
    dif_pto_luz.y = lpy - vertices[i].y;
    dif_pto_luz.z = lpz - vertices[i].z;

    modulo = sqrt(dif_pto_luz.x*dif_pto_luz.x + dif_pto_luz.y*dif_pto_luz.y + dif_pto_luz.z*dif_pto_luz.z);

    dif_pto_luz.x /= modulo;
    dif_pto_luz.y /= modulo;
    dif_pto_luz.z /= modulo;

    escalar = dif_pto_luz.x*normales_vertices[i].x + dif_pto_luz.y*normales_vertices[i].y + dif_pto_luz.z*normales_vertices[i].z;

    if (escalar < 0.0) escalar = 0; // si el escalar es negativo, no hay luz, es decir, las normales y el vector de luz están en sentidos opuestos
    colores_vertices[i].r = kr*escalar;
    colores_vertices[i].g = kg*escalar;
    colores_vertices[i].b = kb*escalar;
  }
}





//*************************************************************************
// objetos o modelos
//*************************************************************************

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
//vertices
vertices.resize(8);
vertices[0].x=-tam;vertices[0].y=-tam;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=-tam;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=tam;vertices[2].z=tam;
vertices[3].x=-tam;vertices[3].y=tam;vertices[3].z=tam;
vertices[4].x=-tam;vertices[4].y=-tam;vertices[4].z=-tam;
vertices[5].x=tam;vertices[5].y=-tam;vertices[5].z=-tam;
vertices[6].x=tam;vertices[6].y=tam;vertices[6].z=-tam;
vertices[7].x=-tam;vertices[7].y=tam;vertices[7].z=-tam;

// triangulos
caras.resize(12);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=3;
caras[1]._0=3;caras[1]._1=1;caras[1]._2=2;
caras[2]._0=1;caras[2]._1=5;caras[2]._2=2;
caras[3]._0=5;caras[3]._1=6;caras[3]._2=2;
caras[4]._0=5;caras[4]._1=4;caras[4]._2=6;
caras[5]._0=4;caras[5]._1=7;caras[5]._2=6;
caras[6]._0=0;caras[6]._1=7;caras[6]._2=4;
caras[7]._0=0;caras[7]._1=3;caras[7]._2=7;
caras[8]._0=3;caras[8]._1=2;caras[8]._2=7;
caras[9]._0=2;caras[9]._1=6;caras[9]._2=7;
caras[10]._0=0;caras[10]._1=1;caras[10]._2=4;
caras[11]._0=1;caras[11]._1=5;caras[11]._2=4; 

  // normales de las caras
  calcular_normales_caras();
  calcular_normales_vertices();

  // colores de las caras
  colors_random();
  // colores
  colors_diffuse_flat(0.8, 0.9, 0.2, 0, 6, 6);
  colors_diffuse_gouraud(0.8, 0.9, 0.2, 0, 6, 6);
}


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{
long unsigned int i;
//vertices 
vertices.resize(5); 
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;

  // normales de las caras
  calcular_normales_caras();
  calcular_normales_vertices();

  // colores de las caras
  colors_random();
  // colores
  colors_diffuse_flat(0.8, 0.9, 0.2, 0, 6, 6);
  colors_diffuse_gouraud(0.8, 0.9, 0.2, 0, 6, 6);
}



//*************************************************************************
// clase medio cubo
//*************************************************************************

_cubo_m::_cubo_m(float tam)
{
//vertices
vertices.resize(6);
vertices[0].x=tam;vertices[0].y=-tam;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=tam;vertices[1].z=tam;
vertices[2].x=-tam;vertices[2].y=-tam;vertices[2].z=-tam;
vertices[3].x=tam;vertices[3].y=-tam;vertices[3].z=-tam;
vertices[4].x=tam;vertices[4].y=tam;vertices[4].z=-tam;
vertices[5].x=-tam;vertices[5].y=tam;vertices[5].z=-tam;

// triangulos
caras.resize(8);
caras[0]._0=0;caras[0]._1=3;caras[0]._2=1;
caras[1]._0=3;caras[1]._1=4;caras[1]._2=1;
caras[2]._0=3;caras[2]._1=2;caras[2]._2=4;
caras[3]._0=2;caras[3]._1=5;caras[3]._2=4;
caras[4]._0=1;caras[4]._1=4;caras[4]._2=5;
caras[5]._0=0;caras[5]._1=3;caras[5]._2=2; 
caras[6]._0 = 0; caras[6]._1 = 1; caras[6]._2 = 5; // Cara frontal
caras[7]._0 = 0; caras[7]._1 = 5; caras[7]._2 = 2; // Cara derecha

  // normales de las caras
  calcular_normales_caras();
  calcular_normales_vertices();

  // colores de las caras
  colors_random();
  // colores
  colors_diffuse_flat(0.8, 0.9, 0.2, 0, 6, 6);
  colors_diffuse_gouraud(0.8, 0.9, 0.2, 0, 6, 6);
}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply() 
{
   // leer lista de coordenadas de vértices y lista de indices de vértices
 
}



void _objeto_ply::parametros(char *archivo)
{
int i, n_ver,n_car;

vector<float> ver_ply ;
vector<int>   car_ply ;
 
_file_ply::read(archivo, ver_ply, car_ply );

n_ver=ver_ply.size()/3;
n_car=car_ply.size()/3;

printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

vertices.resize(n_ver);
caras.resize(n_car);
// vértices

for (i=0;i<n_ver;i++)
  {vertices[i].x=ver_ply[3*i];
   vertices[i].y=ver_ply[3*i+1];
   vertices[i].z=ver_ply[3*i+2];
  }

// vértices
for (i=0;i<n_car;i++)
  {caras[i].x=car_ply[3*i];
   caras[i].y=car_ply[3*i+1];
   caras[i].z=car_ply[3*i+2];
  }

  // normales de las caras
  calcular_normales_caras();
  calcular_normales_vertices();

  // colores de las caras
  colors_random();
  // colores
  colors_diffuse_flat(0.8, 0.9, 0.2, 0, 6, 6);
  colors_diffuse_gouraud(0.8, 0.9, 0.2, 0, 6, 6);
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}


void _rotacion::parametros(vector<_vertex3f> perfil, int num, 
                           int tapa_in, int tapa_su, int tipo)
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;
float radio;

// tratamiento de los vértice
radio=sqrt(perfil[0].x*perfil[0].x+perfil[0].y*perfil[0].y);

num_aux=perfil.size();
if (tipo==2) num_aux=1;
vertices.resize(num_aux*num);

for (j=0;j<num;j++)
  {for (i=0;i<num_aux;i++)
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
     }
  }

// tratamiento de las caras 
if (tipo<2)
{
for (j=0;j<num;j++)
  {for (i=0;i<num_aux-1;i++)
     {cara_aux._0=i+j*num_aux;
      cara_aux._1=i+((j+1)%num)*num_aux;
      cara_aux._2=i+1+j*num_aux;
      caras.push_back(cara_aux);

      cara_aux._0=i+((j+1)%num)*num_aux;
      cara_aux._1=i+1+((j+1)%num)*num_aux;
      cara_aux._2=i+1+j*num_aux;
      caras.push_back(cara_aux);
     }
   }
}
 
// tapa inferior
if (tapa_in==1)
{
  // punto central de la tapa
  vertice_aux.x=0.0;
  if (tipo==1) vertice_aux.y=-radio;
  else vertice_aux.y=perfil[0].y;
  vertice_aux.z=0.0;
  vertices.push_back(vertice_aux);
  //caras tapa inferior

  cara_aux._0=num_aux*num;
  for (j=0;j<num;j++)
    {
     cara_aux._1=((j+1)%num)*num_aux;
     cara_aux._2=j*num_aux;
     caras.push_back(cara_aux);
    }

}
 
// tapa superior

if (tapa_su==1)
{
  // punto central de la tapa
  vertice_aux.x=0.0;
  vertice_aux.y=perfil[num_aux-1].y;
  if (tipo==1) vertice_aux.y=radio;
  if (tipo==2) vertice_aux.y=perfil[1].y;
  vertice_aux.z=0.0;
  vertices.push_back(vertice_aux);

  //caras tapa superior
  if (tapa_in==1) cara_aux._0=num_aux*num+1;
  else cara_aux._0=num_aux*num;

  for (j=0;j<num;j++)
    {cara_aux._1=j*num_aux+num_aux-1;
     cara_aux._2=((j+1)%num)*num_aux+num_aux-1;
     caras.push_back(cara_aux);
    }
}

  // normales de las caras
  calcular_normales_caras();
  calcular_normales_vertices();

  // colores de las caras
  colors_random();
  // colores
  colors_diffuse_flat(0.8, 0.9, 0.2, 0, 6, 6);
  colors_diffuse_gouraud(0.8, 0.9, 0.2, 0, 6, 6);

}


//************************************************************************
// objeto por extrusión
//************************************************************************

_extrusion::_extrusion(vector<_vertex3f> poligono, float x, float y, float z)
{
int i;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértice

num_aux=poligono.size();
vertices.resize(num_aux*2);
for (i=0;i<num_aux;i++)
    {
      vertices[2*i]=poligono[i];
      vertices[2*i+1].x=poligono[i].x+x;
      vertices[2*i+1].y=poligono[i].y+y;
      vertices[2*i+1].z=poligono[i].z+z;
    }
    
// tratamiento de las caras 

caras.resize(num_aux*2);
int c=0;
for (i=0;i<num_aux;i++)         
  {
   caras[c]._0=i*2;
   caras[c]._1=(i*2+2)%(num_aux*2);
   caras[c]._2=i*2+1;    
   c=c+1;
   caras[c]._0=(i*2+2)%(num_aux*2);
   caras[c]._1=(i*2+2)%(num_aux*2)+1;
   caras[c]._2=i*2+1;    
   c=c+1;    
   }  

// normales de las caras
  calcular_normales_caras();
  calcular_normales_vertices();
  // colores de las caras
  colors_random();
  // colores
  colors_diffuse_flat(0.8, 0.9, 0.2, 0, 6, 6);
  colors_diffuse_gouraud(0.8, 0.9, 0.2, 0, 6, 6);
}

//************************************************************************
//************************************************************************

//************************************************************************
// objeto cilindro (caso especial de rotacion)
//************************************************************************

_cilindro::_cilindro(float radio, float altura, int num)
{
vector<_vertex3f> perfil;
_vertex3f aux;

aux.x=radio; aux.y=-altura/2.0; aux.z=0.0;
perfil.push_back(aux);
aux.x=radio; aux.y=altura/2.0; aux.z=0.0;
perfil.push_back(aux);
parametros(perfil,num,1,1,0);
}

//************************************************************************
// objeto cono (caso especial de rotacion)
//************************************************************************

_cono::_cono(float radio, float altura, int num)
{
vector<_vertex3f> perfil;
_vertex3f aux;

aux.x=radio; aux.y=0; aux.z=0.0;
perfil.push_back(aux);
aux.x=0.0; aux.y=altura; aux.z=0.0;
perfil.push_back(aux);
parametros(perfil,num,1,1,2);
}

//************************************************************************
// objeto cono truncado (caso especial de rotacion)
//************************************************************************

_conoTrun::_conoTrun(float radio, float altura, int num)
{
vector<_vertex3f> perfil;
_vertex3f aux;

aux.x=radio; aux.y=-altura/2.0; aux.z=0.0;
perfil.push_back(aux);
aux.x=radio/3.0; aux.y=altura/2.0; aux.z=0.0;
perfil.push_back(aux);
parametros(perfil,num,1,1,0);
}

//************************************************************************
// objeto esfera (caso especial de rotacion)
//************************************************************************

_esfera::_esfera(float radio, int latitud, int longitud)
{
vector<_vertex3f> perfil;
_vertex3f aux;
int i;
for (i=1;i<latitud;i++)
  {aux.x=radio*cos(M_PI*i/(latitud*1.0)-M_PI/2.0);
   aux.y=radio*sin(M_PI*i/(latitud*1.0)-M_PI/2.0);
   aux.z=0.0;
   perfil.push_back(aux);
  }
parametros(perfil,longitud,1,1,1);
}


//************************************************************************
// rotacion archivo PLY (caso especial de rotacion)
//************************************************************************

_rotacion_PLY::_rotacion_PLY()
{

}

void _rotacion_PLY::parametros_PLY(char *archivo, int num)
{

}


//************************************************************************
// OBJETILLO PLY (caso especial de rotacion)
//************************************************************************


_objetillo_ply::_objetillo_ply()
{
   // leer lista de coordenadas de vértices y lista de indices de vértices
}



void _objetillo_ply::parametrosply(char *archivo, int lados) 
{
  int n_ver,n_car;

  vector<float> ver_ply ; //Vector de los vértices del objeto ply
  vector<int>   car_ply ; //Vector de las caras del objeto ply
  vector<_vertex3f> perfil;
  _file_ply::read(archivo, ver_ply, car_ply ); //Leemos el archivo ply y lo guardamos en los vectores

  //Calculamos el número de vértices y caras
  n_ver=ver_ply.size()/3;
  n_car=car_ply.size()/3;

  printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

  vertices.resize(n_ver);
  caras.resize(n_car);

  //Cargamos los vértices y las caras en los vectores de la clase
  for (int i=0; i<n_ver; i++){ //Recorremos el vector de vértices
    vertices[i].x=ver_ply[i*3];
    vertices[i].y=ver_ply[i*3+1];
    vertices[i].z=ver_ply[i*3+2];
    perfil.push_back(vertices[i]);
  }
  
  _rotacion::parametros(perfil,lados,1,1,0);

}



//************************************************************************
// objeto montaña fractal
//************************************************************************

float gauss(float ga, float gf )
{
float sum;
int i;
sum=0.0;
for (i=0;i<4;i++) sum=sum+rand()%32767;
return gf*sum/4.0-ga;
}


_montana::_montana(int nivelmax, float sigma, float h)

{

if (nivelmax>8) nivelmax=8;
int i,j,etapa;
float ga=sqrt(12.0);
float gf=2*ga/(32767*1.0);
int num=pow(2,nivelmax)+1;
srand (time(NULL));

vertices.resize(num*num);

for (j=0;j<num;j++)
  for (i=0;i<num;i++)
    {vertices[i+j*num].x=-0.1*(num-1)/2.0+i*0.1;
     vertices[i+j*num].z=-0.1*(num-1)/2.0+j*0.1;
     vertices[i+j*num].y=0.0;
    }

vertices[0].y=sigma*gauss(ga,gf);
vertices[num-1].y=sigma*gauss(ga,gf);
vertices[num*(num-1)].y=sigma*gauss(ga,gf);
vertices[num*num-1].y=sigma*gauss(ga,gf);

int d1=num-1;
int d2=(num-1)/2;

for (etapa=0;etapa<nivelmax;etapa++)
   {
    sigma=sigma*pow(0.5,0.5*h);
    for (j=d2;j<num-d2;j=j+d1)
       for (i=d2;i<num-d2;i=i+d1)
         {vertices[i+j*num].y=sigma*gauss(ga,gf)+
             (vertices[i+d2+(j+d2)*num].y+vertices[i+d2+(j-d2)*num].y+
              vertices[i-d2+(j+d2)*num].y+vertices[i-d2+(j-d2)*num].y)/4.0;
         }
     sigma=sigma*pow(0.5,0.5*h);
     for (i=d2;i<num-d2;i=i+d1)
	{vertices[i].y=sigma*gauss(ga,gf)+(vertices[i+d2].y+
                     vertices[i-d2].y+vertices[i+d2*num].y)/3.0;
         vertices[i+num*(num-1)].y=sigma*gauss(ga,gf)+
                    (vertices[i+d2+num*(num-1)].y+
                     vertices[i-d2+num*(num-1)].y+
                     vertices[i+(num-1-d2)*num].y)/3.0;
	 vertices[i*num].y=sigma*gauss(ga,gf)+(vertices[(i+d2)*num].y+
                     vertices[(i-d2)*num].y+vertices[d2+i*num].y)/3.0;
         vertices[num-1+i*num].y=sigma*gauss(ga,gf)+
                    (vertices[num-1+(i+d2)*num].y+
                     vertices[num-1+(i-d2)*num].y+
                     vertices[num-1-d2+i*num].y)/3;
	}
      	
     for (j=d2;j<num-d2;j=j+d1)
	for (i=d1;i<num-d2;i=i+d1)
          vertices[i+j*num].y=sigma*gauss(ga,gf)+
                   (vertices[i+(j+d2)*num].y+vertices[i+(j-d2)*num].y+
                    vertices[i+d2+j*num].y+vertices[i-d2+j*num].y)/4.0;
     for (j=d1;j<num-d2;j=j+d1)
	for (i=d2;i<num-d2;i=i+d1)
	  vertices[i+j*num].y=sigma*gauss(ga,gf)+
                   (vertices[i+(j+d2)*num].y+vertices[i+(j-d2)*num].y+
                    vertices[i+d2+j*num].y+vertices[i-d2+j*num].y)/4.0;

     d1=(int)d1/2;
     d2=(int)d2/2;
    }


// caras 
caras.resize((num-1)*(num-1)*2);
int c=0; 
for (j=0;j<num-1;j++)
  for (i=0;i<num-1;i++)
    {caras[c]._0=i+j*num;
     caras[c]._1=i+1+j*num; 
     caras[c]._2=i+1+(j+1)*num;
     c=c+1; 
     caras[c]._0=i+j*num;
     caras[c]._1=i+1+(j+1)*num; 
     caras[c]._2=i+(j+1)*num;
     c=c+1;
    }

// normales de las caras
  calcular_normales_caras();
  calcular_normales_vertices();
  // colores de las caras
  colors_random();
  // colores
  colors_diffuse_flat(0.8, 0.9, 0.2, 0, 6, 6);
  colors_diffuse_gouraud(0.8, 0.9, 0.2, 0, 6, 6);

}

//************************************************************************
// práctica 3, objeto jerárquico articulado
//************************************************************************

// //************************************************************************
// // piezas
// //************************************************************************

// //************************************************************************
// // Ventanilla
// //************************************************************************

_ventanilla::_ventanilla(float radio, float ancho, int num)
{

//Crear un vector que almacena el perfil del medio cilindro
vector<_vertex3f> perfil;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int i, j;

//Agregar los extremos del cilindro al perfil
vertice_aux.x=radio; vertice_aux.y=0; vertice_aux.z=-ancho/2.0;
perfil.push_back(vertice_aux);
vertice_aux.x=radio/3.0;
vertice_aux.z=ancho/1.5;
perfil.push_back(vertice_aux);

//Generar los vértices del cilindro a partir del perfil

for (j=0;j<=num;j++)
  {for (i=0;i<2;i++)	
     {
      vertice_aux.x=perfil[i].x*cos(M_PI*j/(1.0*num))-
                    perfil[i].y*sin(M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].x*sin(M_PI*j/(1.0*num))+
                    perfil[i].y*cos(M_PI*j/(1.0*num));
      vertice_aux.z=perfil[i].z;
      vertices.push_back(vertice_aux);
     }
  }
  
// Generar las caras del cilindro 

for (j=0;j<num;j++)
   {cara_aux._0=j*2;
    cara_aux._1=(j+1)*2;
    cara_aux._2=(j+1)*2+1;
    caras.push_back(cara_aux);
    
    cara_aux._0=j*2;
    cara_aux._1=(j+1)*2+1;
    cara_aux._2=j*2+1;
    caras.push_back(cara_aux);
   }
   
// Agregar la tapa inferior
vertice_aux.x=0;
vertice_aux.y=0;
vertice_aux.z=-ancho/2.0;
vertices.push_back(vertice_aux); 

for (j=0;j<num;j++)
   {cara_aux._0=j*2;
    cara_aux._1=(j+1)*2;
    cara_aux._2=vertices.size()-1;
    caras.push_back(cara_aux);
   }
  
// Agregar la tapa superior
vertice_aux.x=0;
vertice_aux.y=0;
vertice_aux.z=ancho/2.0;
vertices.push_back(vertice_aux); 

for (j=0;j<num;j++)
   {cara_aux._0=j*2+1;
    cara_aux._1=(j+1)*2+1;
    cara_aux._2=vertices.size()-1;
    caras.push_back(cara_aux);
   }
  

// normales de las caras y vértices
calcular_normales_caras();
calcular_normales_vertices();
//Aplicamos los colores con estilo ajedrez a las caras
colors_chess(0.5, 0.5, 0.8, 0.5, 0.8, 0.5);
colors_diffuse_flat(0.8, 0.9, 0.2, 0, 6, 6);
colors_diffuse_gouraud(0.8, 0.9, 0.2, 0, 6, 6);
}

//************************************************************************
// cabina
//************************************************************************

_cabina::_cabina()
{
ancho=0.3;
alto=1.1;
fondo=0.3;
cilindro.colors_chess(1.0, 0.0, 0.0, 0.0, 0.0, 0.0);
};

void _cabina::draw(_modo modo, float r, float g, float b, float grosor)
{
glPushMatrix();
glRotatef(-90,0,0,1);
glTranslatef(-0.5,0.0,0.0);
glScalef(ancho, alto, fondo);
cilindro.draw(modo, r, g, b, grosor);
glPopMatrix();
};

//************************************************************************
// Ala
//************************************************************************

_ala::_ala()
{
ancho=0.9;
alto=0.04;
fondo=4;

ancho_s = 0.05;
alto_s = 0.75;
fondo_s = 0.05;

// // normales de las caras y vértices
calcular_normales_caras();
calcular_normales_vertices();
cubo.colors_chess(1.0, 0.0, 0.0, 0.0, 0.0, 0.0);
cubo.colors_diffuse_flat(0.8, 0.9, 0.2, 0, 6, 6);
cubo.colors_diffuse_gouraud(0.8, 0.9, 0.2, 0, 6, 6);
};


void _ala::draw(_modo modo, float r, float g, float b, float grosor)
{
glPushMatrix();
glTranslatef(0,0.9,0);
glScalef(ancho, alto, fondo);
cubo.draw(modo, r, g, b, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0,0.15,0);
glScalef(ancho, alto, fondo);
cubo.draw(modo, r, g, b, grosor);
glPopMatrix();

// Postes de sustentación

glPushMatrix();
glTranslatef(0,0.525,0.6);
glScalef(ancho_s, alto_s, fondo_s);
cubo.draw(modo, r, g, b, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0,0.525,1.5);
glScalef(ancho_s, alto_s, fondo_s);
cubo.draw(modo, r, g, b, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0,0.525,-1.5);
glScalef(ancho_s, alto_s, fondo_s);
cubo.draw(modo, r, g, b, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0,0.525,-0.6);
glScalef(ancho_s, alto_s, fondo_s);
cubo.draw(modo, r, g, b, grosor);
glPopMatrix();
};


//************************************************************************
// Colitas
//************************************************************************

_colitas::_colitas()
{
ancho=0.7;
alto=0.08;
fondo=0.7;

// // normales de las caras y vértices
calcular_normales_caras();
calcular_normales_vertices();
cubo.colors_chess(1.0, 0.0, 0.0, 0.0, 0.0, 0.0);
cubo_m.colors_chess(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
cubo.colors_diffuse_flat(0.8, 0.9, 0.2, 0, 6, 6);
cubo.colors_diffuse_gouraud(0.8, 0.9, 0.2, 0, 6, 6);

};

void _colitas::draw(_modo modo, float r, float g, float b, float grosor)
{

//Colita alta
glPushMatrix();
glTranslatef(-2.544,0.8,0.0);
glRotatef(90,0,1,0);
glRotatef(-90, 0, 0 , 1);
glScalef(ancho, alto, fondo);
cubo_m.draw(modo, r, g, b, grosor);
glPopMatrix();

//Colita izquierda
glPushMatrix();
glTranslatef(-2.544,0.5,-0.4);
glRotatef(180,0,1,0);
glScalef(ancho, alto, fondo);
cubo_m.draw(modo, r, g, b, grosor);
glPopMatrix();

//Colita derecha
glPushMatrix();
glTranslatef(-2.544,0.5,0.4);
glRotatef(180,0,0,1);
glScalef(ancho, alto, fondo);
cubo_m.draw(modo, r, g, b, grosor);
glPopMatrix();

};

//************************************************************************
// Punta 
//************************************************************************
_punta::_punta()
{
ancho=0.3;
alto=0.3;
fondo=0.3;

// // normales de las caras y vértices
calcular_normales_caras();
calcular_normales_vertices();
conoTrun.colors_chess(1.0, 0.0, 0.0, 0.0, 0.0, 0.0);
conoTrun.colors_diffuse_flat(0.8, 0.9, 0.2, 0, 6, 6);
conoTrun.colors_diffuse_gouraud(0.8, 0.9, 0.2, 0, 6, 6);

};

void _punta::draw(_modo modo, float r, float g, float b, float grosor)
{
// glPushMatrix();
// glRotatef(-90,0,0,1);
// glTranslatef(-0.5,1.3,0);
// glScalef(ancho, alto - 0.1, fondo);
// conoTrun.draw(modo, r, g, b, grosor);
// glPopMatrix();

glPushMatrix();
glRotatef(90,0,0,1);
glTranslatef(0.5,2,0);
glScalef(ancho, alto + 0.6, fondo);
conoTrun.draw(modo, r, g, b, grosor);
glPopMatrix();

};

//************************************************************************
// Hélice
//************************************************************************

_helice::_helice()
{
ancho_c=0.02;
alto_c=1;
fondo_c=0.04;

ancho_e=0.08;
alto_e=0.08;
fondo_e=0.08;

// // normales de las caras y vértices
calcular_normales_caras();
calcular_normales_vertices();
cubo.colors_chess(0.0,0.0,0.0,0.0,0.0,0.0);
esfera.colors_chess(0.5, 0.5, 0.5, 0.5, 0.5, 0.5);

cubo.colors_diffuse_flat(0.8, 0.9, 0.2, 0, 6, 6);
cubo.colors_diffuse_gouraud(0.8, 0.9, 0.2, 0, 6, 6);

esfera.colors_diffuse_flat(0.8, 0.9, 0.2, 0, 6, 6);
esfera.colors_diffuse_gouraud(0.8, 0.9, 0.2, 0, 6, 6);
};

void _helice::draw(_modo modo, float r, float g, float b, float grosor)
{
glPushMatrix();
glTranslatef(0.05,0,0);
glScalef(ancho_c, alto_c, fondo_c);
cubo.draw(modo, r, g, b, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.05,0,0);
glScalef(ancho_c, fondo_c, alto_c);
cubo.draw(modo, r, g, b, grosor);
glPopMatrix();

glPushMatrix();
glScalef(ancho_e, alto_e, fondo_e);
esfera.draw(modo, r, g, b, grosor);
glPopMatrix();
};


//************************************************************************
// sustentación
//************************************************************************

_sustentacion::_sustentacion()
{
ancho_r=0.14;
alto_r=0.04;
fondo_r=0.14;
radio_r=0.05;

ancho_p=0.02;
alto_p=0.085;
fondo_p=0.02;
radio_p=0.001;
// // normales de las caras y vértices
calcular_normales_caras();
calcular_normales_vertices();
rueda.colors_chess(0.2,0.2,0.2,0.0,0.0,0.0);
cilindro.colors_chess(0.5,0.5,0.5,0.5,0.5,0.5);

rueda.colors_diffuse_flat(0.8, 0.9, 0.2, 0, 6, 6);
rueda.colors_diffuse_gouraud(0.8, 0.9, 0.2, 0, 6, 6);

cilindro.colors_diffuse_flat(0.8, 0.9, 0.2, 0, 6, 6);
cilindro.colors_diffuse_gouraud(0.8, 0.9, 0.2, 0, 6, 6);
};

void _sustentacion::draw(_modo modo, float r, float g, float b, float grosor)
{
glPushMatrix();
glTranslatef(0.6,0,0.2);
glRotatef(90,1,0,0);
glScalef(ancho_r, alto_r, fondo_r);
rueda.draw(modo, r, g, b, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.6,0,-0.2);
glRotatef(90,1,0,0);
glScalef(ancho_r, alto_r, fondo_r);
rueda.draw(modo, r, g, b, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.7,0,0);
glRotatef(90,1,0,0);
glScalef(ancho_r, alto_r, fondo_r);
rueda.draw(modo, r, g, b, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.6,0.2,0.2);
glScalef(ancho_p, alto_p, fondo_p);
cilindro.draw(modo, r, g, b, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.6,0.2,-0.2);
glScalef(ancho_p, alto_p, fondo_p);
cilindro.draw(modo, r, g, b, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.7,0.2,0.0);
glScalef(ancho_p, alto_p, fondo_p);
cilindro.draw(modo, r, g, b, grosor);
glPopMatrix();
};



//************************************************************************
// Proyectiles
//************************************************************************

_proyectiles::_proyectiles()
{
ancho=0.06;
alto=0.15;
fondo=0.08;

// // normales de las caras y vértices
calcular_normales_caras();
calcular_normales_vertices();
conoTrun.colors_chess(0.0, 0.2, 0.0, 0.0, 0.2, 0.0);

conoTrun.colors_diffuse_flat(0.8, 0.9, 0.2, 0, 6, 6);
conoTrun.colors_diffuse_gouraud(0.8, 0.9, 0.2, 0, 6, 6);

};

void _proyectiles::draw(_modo modo, float r, float g, float b, float grosor)
{
glPushMatrix();
glTranslatef(0.0,0.85,0.9);
glRotatef(-90,0,0,1);
glScalef(ancho, alto, fondo);
conoTrun.draw(modo, r, g, b, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.0,0.85,1.2);
glRotatef(-90,0,0,1);
glScalef(ancho, alto, fondo);
conoTrun.draw(modo, r, g, b, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.0,0.85,-0.9);
glRotatef(-90,0,0,1);
glScalef(ancho, alto, fondo);
conoTrun.draw(modo, r, g, b, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.0,0.85,-1.2);
glRotatef(-90,0,0,1);
glScalef(ancho, alto, fondo);
conoTrun.draw(modo, r, g, b, grosor);
glPopMatrix();

};


// ************************************************************************
// avioneta (montaje del objeto final)
// ************************************************************************

_avioneta::_avioneta()
{
   giro_helice = 0.0;
   despegue = 0.0;
   despegue_max = 15.0;
   ruedas = 0.0;
   ruedas_max = 0.8;
   tam_sus = 1.0;
   tam_sus_min = 0.5;
   tam_sus_og = 1.0;
   giro_ventanilla = 0.0;
   giro_ventanilla_min = -110;
   giro_ventanilla_max = 0.0;
   balas = 0.0;
   balas_max = 5;
   giro_avioneta = 0.0;
};


void _avioneta::draw(_modo modo, float r, float g, float b, float grosor)
{
glPushMatrix();

// Giro para el loop de la avioneta
glRotatef(giro_avioneta, 1, 0, 0);
// Giro para el despegue de la avioneta
glRotatef(despegue, 0, 0, 1);

// Proyectiles
glPushMatrix();
glTranslatef(balas, 0.0, 0.0); // Disparos de las balas
proyectiles.draw(modo, r, g, b, grosor);
glPopMatrix();

// Sustentación 
glPushMatrix();
glScalef(1.0,tam_sus, 1.0); // Redimensionar ruedas
glTranslatef(0,ruedas,0); // Tren de aterrizaje
sustentacion.draw(modo, r, g, b, grosor);
glPopMatrix();

// Hélices
glPushMatrix();
glTranslatef(1.1,0.5,0);
glRotatef(giro_helice,1,0,0); // Rotación de las hélices
helice.draw(modo, r, g, b, grosor);
glPopMatrix();

// Parte trasera de la avioneta
punta.draw(modo, r, g, b, grosor);

// Alerones
colitas.draw(modo, r, g, b, grosor);

// Cilindro principal de la avioneta
cabina.draw(modo, r, g, b, grosor);

// Alas
ala.draw(modo, r, g, b, grosor);

// Ventanilla
glPushMatrix();
glTranslatef(0.7,0.75,0);
glRotatef(90,0,1,0);
glRotatef(giro_ventanilla, 0, 0, 1); // Giro de la ventanilla
glScalef(0.15, 0.15, 0.15);
ventanilla.draw(modo, r, g, b, grosor);
glPopMatrix();

glPopMatrix();
};