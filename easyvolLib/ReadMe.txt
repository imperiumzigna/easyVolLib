========================================================================
    easyVolLib.h ------ Versão 0.0.2
========================================================================

Descrição:

Igor Amorim Silva - Desenvolveu a biblioteca easyvolLib para facilitar 
					a visualização de arquivos volumétricos em OpenGL.
========================================================================
Função:
 
 carregaArquivo - aloca memória e prepara o arquivo para ser visualizado na tela.

Requisitos: { preConfig, visualConfig}			

---------------------------------------------------------------------
 
 inicializa - prepara as rotinas de inicialização do OpenGL
 
 Requisitos: {visualConfig}
 
---------------------------------------------------------------------

 alteraTamJanela - atualiza a janela após ser redimensionada
 
 Requisitos: {nenhum}

---------------------------------------------------------------------

 mouse - implementação de controlador de mouse pronto para ser aplicado
		 adicionando Zoom a imagem
 
 Requisitos: {nenhum}

/////////////////////////////////////////////////////////////////////////////
Notas:

Atualmente a biblioteca apenas funciona para arquivos que possuem cabeçalho
com valor acima de 1. Em versões futuras isso será tratado.

/////////////////////////////////////////////////////////////////////////////
