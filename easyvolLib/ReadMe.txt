========================================================================
    easyVolLib.h ------ Vers�o 0.0.2
========================================================================

Descri��o:

Igor Amorim Silva - Desenvolveu a biblioteca easyvolLib para facilitar 
					a visualiza��o de arquivos volum�tricos em OpenGL.
========================================================================
Fun��o:
 
 carregaArquivo - aloca mem�ria e prepara o arquivo para ser visualizado na tela.

Requisitos: { preConfig, visualConfig}			

---------------------------------------------------------------------
 
 inicializa - prepara as rotinas de inicializa��o do OpenGL
 
 Requisitos: {visualConfig}
 
---------------------------------------------------------------------

 alteraTamJanela - atualiza a janela ap�s ser redimensionada
 
 Requisitos: {nenhum}

---------------------------------------------------------------------

 mouse - implementa��o de controlador de mouse pronto para ser aplicado
		 adicionando Zoom a imagem
 
 Requisitos: {nenhum}

/////////////////////////////////////////////////////////////////////////////
Notas:

Atualmente a biblioteca apenas funciona para arquivos que possuem cabe�alho
com valor acima de 1. Em vers�es futuras isso ser� tratado.

/////////////////////////////////////////////////////////////////////////////
