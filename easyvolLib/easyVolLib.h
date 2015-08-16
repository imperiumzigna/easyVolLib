/* BIBLIOTECA easyVolLib.h

Desenvolvida por Igor Amorim Silva 
Versão: 0.0.2
Licença: GLP 2.0

*/

#pragma once
#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#include <GL\glut.h> // a remover 
#include <GL\GLU.h> //
#endif
#include <stdio.h>


int ***vol;
struct PRECONFIG
{
	char fileName[] = "";
	
}preConfig;

struct FILECONFIG
{
	// Configurações de perspectiva
	GLfloat fOvy=0;
	GLfloat fAspect=0;
	GLfloat zNear=0;
	GLfloat zFar=0;
	GLfloat angulo_Rot_Perspec=0;
	//

	GLdouble  	pos_Olho_X=0;
	GLdouble  	pos_Olho_Y=0;
	GLdouble  	pos_Olho_Z=0;
	GLdouble  	pos_Centro_Tela_X=0;
	GLdouble  	pos_Centro_Tela_Y=0;
	GLdouble  	pos_Centro_Tela_Z=0;
	GLdouble  	upX=0;
	GLdouble  	upY=0;
	GLdouble  	upZ=0;

	GLdouble  	pos_Olho_Global=0;
	GLdouble  	pos_Centro_Global=0;
	GLdouble  	pos_Top_Global=0;


	GLdouble  	rotX=0;
	GLdouble  	rotY=0;
	GLdouble  	rotZ=0;

	}visualConfig;

struct mouseHandler {
	// Mouse
	int angulo_Padrao = 5;

}mouseConfig;

// Funções Principais
void carregaArquivo(void);
void inicializa(void);
void alteraTamJanela(void);
void mouse(int button, int state, int x, int y);
void resultadoDisplayPadrao(int argc,char**argv);
//
 int carregaArquivo(int fSizeX,int fSizeY, int fSizeZ, int cabSize) 
{
	vol = (int ***)malloc(sizeof(int **) * fSizeX);

	for (int i = 0; i < fSizeX; i++) {
		vol[i] = (int **)malloc(sizeof(int *) * fSizeY);

		for (int j = 0; j < fSizeY; j++) {
			vol[i][j] = (int *)malloc(sizeof(int) * fSizeZ);
		}
	}

	FILE *PTRARQ;

	//Abre o arquivo
	PTRARQ = fopen(preConfig.fileName, "r");

	//Para depois do cabeçalho
	for (int c1 = 0; c1 < cabSize; c1++) {
		getc(PTRARQ);
	}
	//Pega as coordenadas no arquivos

	for (int z = 0; z<fSizeZ; z++) {
		for (int y = 0; y<fSizeY; y++) {
			for (int x = 0; x<fSizeX; x++) {
				vol[x][y][z] = getc(PTRARQ);
			}
		}
	}

	//Fecha o arquivo
	fclose(PTRARQ);
	for (int x = 0; x<fSizeX; x++) {
		for (int y = 0; y<fSizeY; y++) {
			for (int z = 0; z<fSizeZ; z++) {
				if (vol[x][y][z] != 0) {
					
					glVertex3f(x, y, z);
					glColor3f(vol[x][y][z], vol[x][y][z], vol[x][y][z]);
				}
			}
		}
	}

	glEnd();
	//executa a troca dos buffer's
	glutSwapBuffers();

	// Libera Memória
	free(vol);

 
 }

 void inicializa(void)
 {
 // Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(visualConfig.angulo_Rot_Perspec, visualConfig.fAspect,visualConfig.zNear,visualConfig.zFar);

	// Rotaciona o objeto nos valores especificados
	glRotatef(visualConfig.angulo_Rot_Perspec,visualConfig.rotX,visualConfig.rotY,visualConfig.rotZ);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posição do observador e do alvo
	gluLookAt(visualConfig.pos_Olho_X, visualConfig.pos_Olho_Y, visualConfig.pos_Olho_Z, visualConfig.pos_Centro_Tela_X, visualConfig.pos_Centro_Tela_Y, visualConfig.pos_Centro_Tela_Z, visualConfig.upX, visualConfig.upY,visualConfig.upZ);
	

 
 }

 // Suporte a alteração no tamanho da janela
 void alteraTamJanela(GLsizei width, GLsizei height)
 {
	 // Para previnir uma divisão por zero
	 if (height == 0) {
		 height = 1;
	 }

	 // Especifica as dimensões da viewport
	 glViewport(0, 0, width, height);

	 // Calcula a correção de aspecto
	 visualConfig.fAspect = (GLfloat)width / (GLfloat)height;

	 // Atualiza os parâmetros de inicialização
	 inicializa();
 }

 void mouse(int button, int state, int x, int y)
 {
	 if (button == GLUT_LEFT_BUTTON)
		 if (state == GLUT_DOWN) {  // zoom in
			 visualConfig.angulo_Rot_Perspec -= mouseConfig.angulo_Padrao;
			 		 }
	 if (button == GLUT_RIGHT_BUTTON)
		 if (state == GLUT_DOWN) {  // zoom out
			 visualConfig.angulo_Rot_Perspec += mouseConfig.angulo_Padrao;
		 }
	 
	 glutPostRedisplay();
	 
 }

 void resultadoDisplayPadrao(int argc, char**argv) {
	 glutInit(&argc, argv);

	 //define modo de operação da Glut
	 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	 //Especifica o tamanho em pixel da janel Glut
	 glutInitWindowSize(600, 400);

	 //Cria a janela passando como argumento o título da mesma
	 glutCreateWindow(preConfig.fileName);

	 //Registra a função callback de redesenho da janela de visualização
	 glutDisplayFunc(carregaArquivo);

	 // Registra a função callback de redimensionamento da janela de visualização
	 glutReshapeFunc(alteraTamJanela);

	 	 // Registra a função callback que gerencia os eventos do mouse   
	 glutMouseFunc(mouse);

	 

	 glutMainLoop();

 }


// 
// Implementar em futuras versões o handler do teclado
//

// 
// Implementar em futuras versões o handler das teclas especiais
//

// 
// Implementar em futuras versões o handler de arquivos sem cabeçalho
//
