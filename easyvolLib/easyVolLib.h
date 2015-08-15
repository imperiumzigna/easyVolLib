#pragma once
#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#include <GL\glut.h> // a remover 
#include <GL\GLU.h> //
#include <string.h>
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
	GLfloat fOvy;
	GLfloat fAspect;
	GLfloat zNear;
	GLfloat zFar;
	GLfloat angulo_Rot_Perspec;
	//

	GLdouble  	pos_Olho_X;
	GLdouble  	pos_Olho_Y;
	GLdouble  	pos_Olho_Z;
	GLdouble  	pos_Centro_Tela_X;
	GLdouble  	pos_Centro_Tela_Y;
	GLdouble  	pos_Centro_Tela_Z;
	GLdouble  	upX;
	GLdouble  	upY;
	GLdouble  	upZ;

	GLdouble  	pos_Olho_Global;
	GLdouble  	pos_Centro_Global;
	GLdouble  	pos_Top_Global;


	GLdouble  	rotX;
	GLdouble  	rotY;
	GLdouble  	rotZ;
	
}fileConfig;

void carregaArquivo(void);
void inicializa(void);
void alteraTamJanela(void);

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
	gluPerspective(fileConfig.angulo_Rot_Perspec, fileConfig.fAspect,fileConfig.zNear,fileConfig.zFar);

	// Rotaciona o objeto nos valores especificados
	glRotatef(fileConfig.angulo_Rot_Perspec,fileConfig.rotX,fileConfig.rotY,fileConfig.rotZ);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posição do observador e do alvo
	gluLookAt(fileConfig.pos_Olho_X, fileConfig.pos_Olho_Y, fileConfig.pos_Olho_Z, fileConfig.pos_Centro_Tela_X, fileConfig.pos_Centro_Tela_Y, fileConfig.pos_Centro_Tela_Z, fileConfig.upX, fileConfig.upY,fileConfig.upZ);
	

 
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
	 fileConfig.fAspect = (GLfloat)width / (GLfloat)height;

	 // Atualiza os parâmetros de inicialização
	 inicializa();
 }