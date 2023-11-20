//**************************************************************************
// Práctica 4
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID,SOLID_COLORS} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
vector<_vertex3f> colores_vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_colores();
void 	draw(_modo modo, float r, float g, float b, float grosor);

/* asignación de colores */
void 	colors_random();
void 	colors_chess(float r1, float g1, float b1, float r2, float g2, float b2);
void colors_diffuse_flat(float kr, float kg, float kb, float lpx, float lpy, float lpz);
void colors_diffuse_gouraud(float kr, float kg, float kb, float lpx, float lpy, float lpz);

/*calcular normales*/
void calcular_normales_caras();
void calcular_normales_vertices();

vector<_vertex3i> caras;
vector<_vertex3f> colores_caras;
vector<_vertex3f> colores_vertices;
vector<_vertex3f> normales_vertices;
vector<_vertex3f> normales_caras;
};

//*************************************************************************
// objetos o modelos
//*************************************************************************

//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=1.0);
};

//*************************************************************************
// clase cubo medio
//*************************************************************************

class _cubo_m: public _triangulos3D
{
public:

	_cubo_m(float tam=0.5);
};


//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

void  parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************


class _rotacion: public _triangulos3D
{
public:
       _rotacion();
       
void  parametros(vector<_vertex3f> perfil, int num,  
                 int tapa_in, int tapa_su, int tipo);
};

// tapa_in=0 sin tapa, tapa_in=1 con tapa
// tapa_su=0 sin tapa, tapa_su=1 con tapa
// tipo=0 revolucion normal
// tipo=1 esfera
// tipo=2 cono

//************************************************************************
// objeto por extrusión
//************************************************************************

class _extrusion: public _triangulos3D
{
public:
       _extrusion(vector<_vertex3f> poligono, float x, float y, float z);
};


//************************************************************************
// objeto por revolución especiales
//************************************************************************

 
//************************************************************************
// cilindro
//************************************************************************

class _cilindro: public _rotacion
{
public:
       _cilindro(float radio=1.0, float altura=2.0, int num=50);
};

//************************************************************************
// cono
//************************************************************************

class _cono: public _rotacion
{
public:
       _cono(float radio=1.0, float altura=2.0, int num=50);
};

//************************************************************************
// cono truncado
//************************************************************************

class _conoTrun: public _rotacion
{
public:
       _conoTrun(float radio=1.0, float altura=2.0, int num=50);
};

//************************************************************************
// esfera
//************************************************************************

class _esfera: public _rotacion
{
public:
       _esfera(float radio=1.0, int latitud=6, int longitud=50);
};


//************************************************************************
// rotacion archivo PLY
//************************************************************************

class _rotacion_PLY: public _rotacion
{
public:
       _rotacion_PLY();
void  parametros_PLY(char *archivo, int num);
};


//************************************************************************
// objeto montaña fractal
//************************************************************************

class _montana: public _triangulos3D
{
public:
       _montana(int nivelmax, float sigma, float h);
};

// nivelmax, ha de ser par es el tamaño de la cuadrícula
// sigma, se relaciona con la altura máxima de la montaña
// h 0<=h<=1, dimensión de Hausdorff indica la forma del relieve, más suave 1


//************************************************************************
// OBJETILLO PLY
//************************************************************************

class _objetillo_ply: public _rotacion
{
public:
   _objetillo_ply();

void  parametrosply(char *archivo, int lados);
};

//************************************************************************
// práctica 3, objeto jerárquico articulado avioneta
//************************************************************************

//************************************************************************
// piezas
//************************************************************************

//************************************************************************
// Ventanilla
//************************************************************************

class _ventanilla: public _triangulos3D
{
public:
      _ventanilla(float radio=1.2, float ancho=2.0, int num=8);

float ancho;
float alto;
float fondo;
};

//************************************************************************
// Ala
//************************************************************************

class _ala: public _triangulos3D
{
public:
      _ala();
void  draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

float ancho_s;
float alto_s;
float fondo_s;

protected:
_cubo cubo;
};

//************************************************************************
// cabina
//************************************************************************

class _cabina: public _triangulos3D
{
public:
       _cabina();
void  draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:
_cilindro cilindro;
};

//************************************************************************
// Colitas
//************************************************************************

class _colitas: public _triangulos3D
{
public:
       _colitas();
void  draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:
_cubo cubo;
_cubo_m cubo_m;
};


//************************************************************************
// punta
//************************************************************************

class _punta: public _triangulos3D
{
public:
       _punta();
void  draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:
_conoTrun conoTrun;
_cilindro cilindro;
};

//************************************************************************
// Hélice
//************************************************************************

class _helice: public _triangulos3D
{
public:
       _helice();
void  draw(_modo modo, float r, float g, float b, float grosor);

float ancho_c;
float alto_c;
float fondo_c;

float ancho_e;
float alto_e;
float fondo_e;

protected:
_cubo cubo;
_esfera esfera;
};


//************************************************************************
// sustentación
//************************************************************************

class _sustentacion: public _triangulos3D
{
public:
      _sustentacion();
void  draw(_modo modo, float r, float g, float b, float grosor);
       
float ancho_r;
float alto_r;
float fondo_r;

float ancho_p;
float alto_p;
float fondo_p;

float radio_r;
float radio_p;

protected:
_cilindro rueda;
_cilindro cilindro;
};

//************************************************************************
// Proyectiles
//************************************************************************

class _proyectiles: public _rotacion
{
public:
       _proyectiles();
void  draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:
_conoTrun conoTrun;
};


//************************************************************************
// avioneta (montaje del objeto final)
//************************************************************************

class _avioneta: public _triangulos3D
{
public:
       _avioneta();
       
void  draw(_modo modo, float r, float g, float b, float grosor);

float giro_helice;
float despegue;
float despegue_max;
float ruedas;
float ruedas_max;
float tam_sus;
float tam_sus_min;
float tam_sus_og;
float giro_ventanilla;
float giro_ventanilla_max;
float giro_ventanilla_min;
float balas;
float balas_max;
float giro_avioneta;


protected:
_ventanilla ventanilla;
_ala ala;
_cabina cabina;
_colitas colitas;
_punta punta;
_helice helice;
_sustentacion sustentacion;
_proyectiles proyectiles;
};