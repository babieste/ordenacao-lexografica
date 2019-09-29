//Barbara Este Fernandez - 31937039

#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 50

void insertionSort(FILE *in, FILE *out) {
	int i = 0, j = 0, posOut, flag = 0;
	char bufferIn[BUFFER_SIZE], bufferOut[BUFFER_SIZE], cIn, cOut;

	while(1) {
		cIn = fgetc(in);
		if(cIn == ' ' || cIn == '\0' || cIn == EOF) {
			fseek(out, 0, SEEK_SET);
			cOut = fgetc(out);
			
			if(cOut != EOF) {
				//se cOut == EOF, significa que nao ha palavras em out, portanto passamos
				//bufferIn para out diretamente, sem validacao
				
				//salvando ponteiro para primeiro char de cOut
				posOut = ftell(out);
				
				//voltar o pointeiro para trás para salvar a palavra toda no laco
				fseek(out, -1, SEEK_CUR);
				
				while(1) {
					cOut = fgetc(out);
					if(cOut == ' ' || cOut == '\0' || cOut == EOF) {
						//termino da leitura da palavra atual

						j = 0;
						while(1) {
							//comparando bufferIn e bufferOut por valores ascii
							if((int) bufferIn[j] == (int) bufferOut[j]) {
								//se os caracteres atuais de bufferIn e bufferOut sao iguais
								//devemos entao ler os proximos
								j++;
							} else {
								if((int) bufferIn[j] < (int) bufferOut[j]) {
									//se a palavra em bufferIn for, alfabeticamente falando,
									//menor do que a palavra em bufferOut, entao ela vem antes
									flag = 1;
									
									//coloca o pointeiro de out no inicio da palavra lida em
									//bufferOut para gravar a palavra em bufferIn antes dela
									fseek(out, 0, posOut);
								}
								break;
							}
						}
						
						if(flag) break;
						if(cOut == EOF) break;
						memset(bufferOut, 0, BUFFER_SIZE);
						j = 0;
					}
					bufferOut[j] = cOut;
					j++;
				}
			}
			
			if(fputs(bufferIn, out) != EOF) {
				if (fputc(' ', out) == EOF) {
					printf("\nErro ao gravar palavra em \"out1.txt\".");
					break;
				}
			} else {
				printf("\nErro ao gravar palavra em \"out1.txt\".");
				break;
			}
			
			if(cIn == EOF) break;
			memset(bufferIn, 0, BUFFER_SIZE);
			i = 0;
		} else {
			bufferIn[i] = cIn;
			i++;
		}
	}
}

int main() {
	FILE *in = fopen("in.txt", "r"), *out1 = fopen("out1.txt", "w+"), *out2;
	
	if(in == NULL || out1 == NULL) {
		printf("Erro ao abrir um ou mais arquivos.\n");
		return 1;
	}
	
	insertionSort(in, out1);
	
	fclose(in);
	fclose(out1);
	return 0;
}
