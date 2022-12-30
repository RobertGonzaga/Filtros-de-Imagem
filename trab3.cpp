#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <iomanip>

const int MAXALTURA  = 700;								//tamanho maximo aceito (pode ser alterado)
const int MAXLARGURA = 700;
const int RGB = 3;

using namespace std;

int imagemaux[MAXALTURA][MAXLARGURA][RGB]; 				//cria uma matriz auxiliar com o mesmo tamanho da original
int mx[MAXALTURA][MAXLARGURA][RGB];
int my[MAXALTURA][MAXLARGURA][RGB];

int main() {
	unsigned char imagem[MAXALTURA][MAXLARGURA][RGB];	//a imagem propriamente dita
	unsigned char imagemcinza[MAXALTURA][MAXLARGURA];
	int largura, altura;								//dimensoes da imagem
	char tipo[4];										//tipo da imagem
	ifstream arqentrada;								//arquivo que contem a imagem original
	ofstream arqsaida;									//arquivo que contera a imagem modificada
	char comentario[200], c;							//auxiliares
	int i, j, k, RGB2, valor;									//auxiliares
	char nomearq[100];									//nome do arquivo
	char nomesaida[100];
	RGB2=RGB;

//*** LEITURA DA IMAGEM ***//
	//*** Abertura do arquivo ***//
	cout << "Nome do arquivo com a imagem PNM: ";
	cin >> nomearq;
	arqentrada.open(nomearq,ios::in); //Abre arquivo para leitura
	if (!arqentrada) {
		cout << "Nao consegui abrir arquivo " << nomearq << endl;
		return 0;
	}
	//***************************//


	//*** Leitura do cabecalho ***//
	arqentrada >> tipo;		//Le o tipo de arquivo
	arqentrada.get();		//Le e descarta o \n do final da 1a. linha

	if (strcmp(tipo,"P2")==0) {
		cout << "Imagem em tons de cinza\n";
		RGB2=1;
	}
	else if (strcmp(tipo,"P3")==0) {
		cout << "Imagem colorida\n";
	}
	else if (strcmp(tipo,"P1")==0) {
		cout << "Imagem preto e branco\n";
		cout << "Desculpe, nao trabalho com esse tipo de imagem.\n";
		arqentrada.close();
		return 0;
	}
	else if (strcmp(tipo,"P4")==0 || strcmp(tipo,"P5")==0 || strcmp(tipo,"P6")==0) {
		cout << "Imagem no formato RAW\n";
		cout << "Desculpe, nao trabalho com esse tipo de imagem.\n";
		arqentrada.close();
		return 0;
	}

	while((c = arqentrada.get()) == '#')	//Enquanto for comentario
		arqentrada.getline(comentario,200);	//Le e descarta a linha "inteira"

	arqentrada.putback(c);	//Devolve o caractere lido para a entrada, pois como
							//nao era comentario, era o primeiro digito da largura

	arqentrada >> largura >> altura;	//Le as dimensoes da imagem, numero de pixels da horizontal e da vertical
	cout << "Tamanho: " << largura << " x " << altura << endl;
	if (largura>MAXLARGURA) {
		cout << "Desculpe, ainda nao trabalho com imagens com mais de " << MAXLARGURA << " pixels de largura.\n";
		arqentrada.close();
		return 0;
	}
	if (altura>MAXALTURA) {
		cout << "Desculpe, ainda nao trabalho com imagens com mais de " << MAXALTURA << " pixels de altura.\n";
		arqentrada.close();
		return 0;
	}

	arqentrada >> valor;	//Valor maximo do pixel (temos que ler, mas nao sera usado)
	//****************************//


	//*** Leitura dos pixels da imagem ***//
	for(i=0;i<altura;i++){
		for(j=0;j<largura;j++){
			for(k=0;k<RGB2;k++){
				arqentrada >> valor;
				imagem[i][j][k] = (unsigned char)valor;
			}
		}
	}
	//************************************//

	arqentrada.close();  //Fecha arquivo apos a leitura

	//*** FIM DA LEITURA DA IMAGEM ***//


	//*** TRATAMENTO DA IMAGEM ***//
	int operacao;
	cout<<"Digite a operacao desejada"<<endl;
	cout<<"Escurecer [1]"<<endl;
	cout<<"Clarear [2]"<<endl;
	cout<<"Negativo [3]"<<endl;
	cout<<"Espelhar na horizontal [4]"<<endl;
	cout<<"Filtro de Sobel [5]"<<endl;
	cout<<"Filtro de Laplace [6]"<<endl;
	cout<<"Desfocagem Gaussiana [7]"<<endl;
	cout<<"Tons de cinza [8]"<<endl;
	cout<<"Filtro Sepia [9]"<<endl;
	cout<<"Espelhar na vertical [10]"<<endl;
	cin>>operacao;
	
	if(operacao==1){
		int fator;
		cout << "Qual o fator de escurecimento (1-100)? ";
		cin >> fator;
		//*** Escurece a imagem ***//
		for(i=0;i<altura;i++){
			for(j=0;j<largura;j++) {
				for(k=0;k<RGB2;k++){
					valor = (int)imagem[i][j][k];				//pega o valor do pixel
					valor -= fator;								//escurece o pixel
					if (valor < 0)								//se der negativo
						valor = 0;								//  deixa preto
					imagem[i][j][k] = (unsigned char)valor;		//modifica o pixel
				}
			}
		}
	}
	if(operacao==2){
		int fator;
		cout << "Qual o fator de clareamento (1-100)? ";
		cin >> fator;
		//*** Clareia a imagem ***//
		for(i=0;i<altura;i++){
			for(j=0;j<largura;j++) {
				for(k=0;k<RGB2;k++){
					valor = (int)imagem[i][j][k];				//pega o valor do pixel
					valor += fator;								//clareia o pixel
					if (valor > 255)							//se der maior que 255
						valor = 255;							//  deixa branco
					imagem[i][j][k] = (unsigned char)valor;		//modifica o pixel
				}
			}
		}
	}
	if (operacao==3){
		int inv;
        for (i=0;i<altura;i++){
            for (j=0;j<largura;j++){
				for(k=0;k<RGB2;k++){
					valor = (int)imagem[i][j][k];
					if ((int)imagem[i][j][k] == 0){
						valor = 255;
					}
					if ((int)imagem[i][j][k]==255){
						valor = 0;
					}
					if ((int)imagem[i][j][k]>0 && (int) imagem[i][j][k]<255){
						inv = 255-valor;
						valor = inv;
					}
					imagem[i][j][k] = (unsigned char)valor;
				}
            }
		}
    }
	if(operacao==4){
		//*** Espelha a imagem ***//
		for(i=0;i<altura;i++){
			for(j=0;j<largura;j++) {
				for(k=0;k<RGB2;k++){
					valor = (int)imagem[i][j][k];	 						//pega o valor do pixel
					imagemaux[i][largura-j-1][k] = (unsigned char)valor; 
				}
			}
		}
		//copia os valores da matriz auxiliar para a matriz original
		for(i=0;i<altura;i++){
			for(j=0;j<largura;j++){
				for(k=0;k<RGB2;k++){
					imagem[i][j][k]=imagemaux[i][j][k];
				}
			}
		}
	}
	if(operacao==5){
		int gx[3][3][1];
		int gy[3][3][1];
		
		gy[0][0][1]=1; gy[0][1][1]=2; gy[0][2][1]=1;
		gy[1][0][1]=0; gy[1][1][1]=0; gy[1][2][1]=0;
		gy[2][0][1]=-1; gy[2][1][1]=-2; gy[2][2][1]=-1;
		
		gx[0][0][1]=1; gx[0][1][1]=0; gx[0][2][1]=-1;
		gx[1][0][1]=2; gx[1][1][1]=0; gx[1][2][1]=-2;
		gx[2][0][1]=1; gx[2][1][1]=0; gx[2][2][1]=-1;
		
		for(i=0;i<altura;i++){
			for(j=0;j<largura;j++){
				for(k=0;k<RGB2;k++){
					valor=(int)imagem[i][j][k]*gy[1][1][1];
					valor+=(int)imagem[i-1][j-1][k]*gy[0][0][1];
					valor+=(int)imagem[i-1][j][k]*gy[0][1][1];
					valor+=(int)imagem[i-1][j+1][k]*gy[0][2][1];
					valor+=(int)imagem[i][j-1][k]*gy[1][0][1];
					valor+=(int)imagem[i][j+1][k]*gy[1][2][1];
					valor+=(int)imagem[i+1][j-1][k]*gy[2][0][1];
					valor+=(int)imagem[i+1][j][k]*gy[2][1][1];
					valor+=(int)imagem[i+1][j+1][k]*gy[2][2][1];
					if(valor>255){
						valor=255;
					}
					if(valor<0){
						valor=0;
					}
					my[i][j][k]=(unsigned char)valor;
				}
			}
		}
		for(i=0;i<altura;i++){
			for(j=0;j<largura;j++){
				for(k=0;k<RGB2;k++){
					valor=(int)imagem[i][j][k]*gx[1][1][1];
					valor+=(int)imagem[i-1][j-1][k]*gx[0][0][1];
					valor+=(int)imagem[i-1][j][k]*gx[0][1][1];
					valor+=(int)imagem[i-1][j+1][k]*gx[0][2][1];
					valor+=(int)imagem[i][j-1][k]*gx[1][0][1];
					valor+=(int)imagem[i][j+1][k]*gx[1][2][1];
					valor+=(int)imagem[i+1][j-1][k]*gx[2][0][1];
					valor+=(int)imagem[i+1][j][k]*gx[2][1][1];
					valor+=(int)imagem[i+1][j+1][k]*gx[2][2][1];
					if(valor>255){
						valor=255;
					}
					if(valor<0){
						valor=0;
					}
					mx[i][j][k]=(unsigned char)valor;
				}
			}
		}
		for(i=0;i<altura;i++){
			for(j=0;j<largura;j++){
				for(k=0;k<RGB2;k++){
					valor=(sqrt((pow(mx[i][j][k],2))+(pow(my[i][j][k],2))));
					if(valor>255){
						valor=255;
					}
					if(valor<0){
						valor=0;
					}
					imagem[i][j][k]=(unsigned char)valor;
				}
			}
		}
	}
	if(operacao==6){
		int fl[3][3][1];
		
		fl[0][0][1]=0; fl[0][1][1]=-1; fl[0][2][1]=0;
		fl[1][0][1]=-1; fl[1][1][1]=4; fl[1][2][1]=-1;
		fl[2][0][1]=0; fl[2][1][1]=-1; fl[2][2][1]=0;
		
		for(i=0;i<altura;i++){
			for(j=0;j<largura;j++){
				for(k=0;k<RGB2;k++){
					valor=(int)imagem[i][j][k]*fl[1][1][1];
					valor+=(int)imagem[i-1][j-1][k]*fl[0][0][1];
					valor+=(int)imagem[i-1][j][k]*fl[0][1][1];
					valor+=(int)imagem[i-1][j+1][k]*fl[0][2][1];
					valor+=(int)imagem[i][j-1][k]*fl[1][0][1];
					valor+=(int)imagem[i][j+1][k]*fl[1][2][1];
					valor+=(int)imagem[i+1][j-1][k]*fl[2][0][1];
					valor+=(int)imagem[i+1][j][k]*fl[2][1][1];
					valor+=(int)imagem[i+1][j+1][k]*fl[2][2][1];
					if(valor>255){
						valor=255;
					}
					if(valor<0){
						valor=0;
					}
					imagemaux[i][j][k]=(unsigned char)valor;
				}
			}
		}
		for(i=0;i<altura;i++){
			for(j=0;j<largura;j++){
				for(k=0;k<RGB2;k++){
					imagem[i][j][k]=imagemaux[i][j][k];
				}
			}
		}
	}
	if(operacao==7){
		int fdg[3][3][1];
		
		fdg[0][0][1]=1; fdg[0][1][1]=2; fdg[0][2][1]=1;
		fdg[1][0][1]=2; fdg[1][1][1]=4; fdg[1][2][1]=2;
		fdg[2][0][1]=1; fdg[2][1][1]=2; fdg[2][2][1]=1;
		
		for(i=0;i<altura;i++){
			for(j=0;j<largura;j++){
				for(k=0;k<RGB2;k++){
					valor=(int)imagem[i][j][k]*fdg[1][1][1]*1/16;
					valor+=(int)imagem[i-1][j-1][k]*fdg[0][0][1]*1/16;
					valor+=(int)imagem[i-1][j][k]*fdg[0][1][1]*1/16;
					valor+=(int)imagem[i-1][j+1][k]*fdg[0][2][1]*1/16;
					valor+=(int)imagem[i][j-1][k]*fdg[1][0][1]*1/16;
					valor+=(int)imagem[i][j+1][k]*fdg[1][2][1]*1/16;
					valor+=(int)imagem[i+1][j-1][k]*fdg[2][0][1]*1/16;
					valor+=(int)imagem[i+1][j][k]*fdg[2][1][1]*1/16;
					valor+=(int)imagem[i+1][j+1][k]*fdg[2][2][1]*1/16;
					if(valor>255){
						valor=255;
					}
					if(valor<0){
						valor=0;
					}
					imagemaux[i][j][k]=(unsigned char)valor;
				}
			}
		}
		for(i=0;i<altura;i++){
			for(j=0;j<largura;j++){
				for(k=0;k<RGB2;k++){
					imagem[i][j][k]=imagemaux[i][j][k];
				}
			}
		}
	}
	if(operacao==8){
		for(i=0;i<altura;i++){
			for(j=0;j<largura;j++){
				for(k=0;k<RGB2;k++){
					valor=(int)imagem[i][j][k];
					imagemcinza[i][j]+=(unsigned char)valor/3;
				}
			}
		}
		//*** Grava a nova imagem ***//
		cout<<"Nome que deseja salvar a imagem PNM: ";
		cin>>nomesaida;
		arqsaida.open(nomesaida,ios::out);				//Abre arquivo para escrita
		if (!arqsaida) {
			cout << "Nao consegui criar novaimagem.pnm\n";
			return 0;
		}

		arqsaida << tipo << endl;								//tipo
		arqsaida << "# TP3-INF110, by AGS\n";					//comentario
		arqsaida << largura << " " << altura;					//dimensoes
		arqsaida << " " << 255 << endl;							//maior valor
		for(i=0;i<altura;i++)
			for(j=0;j<largura;j++)
				for(k=0;k<RGB2;k++)
					arqsaida << (int)imagemcinza[i][j] << endl;	//pixels

		arqsaida.close();										//fecha o arquivo
		//*** FIM DA GRAVACAO DA IMAGEM ***//
		return 0;
	}
	if(operacao==9){
		if(RGB2<3){
			cout<<"Desculpe, funciona apenas com imagens coloridas";
			return 0;
		}
		for(i=0;i<altura;i++){
			for(j=0;j<largura;j++) {
				for(k=0;k<RGB2;k++){
					if(k==0){
						valor = (int)imagem[i][j][0]*0.393;
						valor += (int)imagem[i][j][1]*0.769;
						valor += (int)imagem[i][j][2]*0.189;											
						if (valor < 0){			
							valor = 0;
						}
						if (valor > 255)			
							valor = 255;
						imagem[i][j][k] = (unsigned char)valor;	
					}
					if(k==1){
						valor = (int)imagem[i][j][0]*0.349;
						valor += (int)imagem[i][j][1]*0.686;
						valor += (int)imagem[i][j][2]*0.168;											
						if (valor < 0){			
							valor = 0;
						}
						if (valor > 255)			
							valor = 255;
						imagem[i][j][k] = (unsigned char)valor;	
					}
					if(k==2){
						valor = (int)imagem[i][j][0]*0.272;
						valor += (int)imagem[i][j][1]*0.534;
						valor += (int)imagem[i][j][2]*0.131;											
						if (valor < 0){			
							valor = 0;
						}
						if (valor > 255)			
							valor = 255;
						imagem[i][j][k] = (unsigned char)valor;	
					}
				}
			}
		}
	}
	if(operacao==10){
		for(i=0;i<altura;i++){
			for(j=0;j<largura;j++) {
				for(k=0;k<RGB2;k++){
					valor = (int)imagem[i][j][k];	 				
					imagemaux[altura-i-1][j][k] = (unsigned char)valor; 
				}
			}
		}
		//copia os valores da matriz auxiliar para a matriz original
		for(i=0;i<altura;i++){
			for(j=0;j<largura;j++){
				for(k=0;k<RGB2;k++){
					imagem[i][j][k]=imagemaux[i][j][k];
				}
			}
		}
	}
	//*********************************************************//
	//*** FIM DO TRATAMENTO DA IMAGEM ***//

	//*** GRAVACAO DA IMAGEM ***//

	//*** Grava a nova imagem ***//
	cout<<"Nome que deseja salvar a imagem PNM: ";
	cin>>nomesaida;
	arqsaida.open(nomesaida,ios::out);					//Abre arquivo para escrita
	if (!arqsaida) {
		cout << "Nao consegui criar novaimagem.pnm\n";
		return 0;
	}

	arqsaida << tipo << endl;									//tipo
	arqsaida << "# TP3-INF110, by AGS\n";						//comentario
	arqsaida << largura << " " << altura;						//dimensoes
	arqsaida << " " << 255 << endl;								//maior valor
	for(i=0;i<altura;i++)
		for(j=0;j<largura;j++)
			for(k=0;k<RGB2;k++)
				arqsaida << (int)imagem[i][j][k] << endl;		//pixels

	arqsaida.close();											//fecha o arquivo
	//*** FIM DA GRAVACAO DA IMAGEM ***//
	return 0;
}