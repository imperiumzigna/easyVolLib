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

	GLfloat fovy;
	GLfloat fAspect;
	GLfloat zNear;
	GLfloat zFar;

	GLfloat angulo_Rot_Perspec;

	GLdouble  	pos_Olho_X;
	GLdouble  	pos_Olho_Y;
	GLdouble  	pos_Olho_Z;
	GLdouble  	pos_Centro_Tela_X;
	GLdouble  	pos_Centro_Tela_Y;
	GLdouble  	pos_Centro_Tela_Z;
	GLdouble  	upX;
	GLdouble  	upY;
	GLdouble  	upZ;

	GLdouble  	eye;
	GLdouble  	center;
	GLdouble  	up;


	GLdouble  	rotX;
	GLdouble  	rotY;
	GLdouble  	rotZ;
	
}fileConfig;

void carregaArquivo(void);
void desenha(void);
void criaTela(void);


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