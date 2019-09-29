//Barbara Este Fernandez - 31937039

#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 50

void insertionSort(FILE *in, FILE *out) {
	fpos_t *posOut;
	int i = 0, ascii;
	char bufferIn[BUFFER_SIZE], bufferOut[BUFFER_SIZE], cIn, cOut;

	while(1) {
		cIn = fgetc(in);
		if(cIn == EOF) break;
		if(cIn == ' ' || cIn == '\0') {
			bufferIn[i] = ' ';
			
			fseek(out, 0, SEEK_SET);
			cOut = fgetc(out);
			
			//se c == EOF, significa que nao ha palavras em out, portanto passamos
			//bufferIn para out diretamente, sem validacao
			if(cOut != EOF) {
				//verificando valor ascii
				// se a palavra lida eh, alfabeticamente falando, menor que a que foi lida 
				//do arquivo out, entao colocar antes.
				if ((int) bufferIn[0] < (int) cOut) {
					fseek(out, 0, SEEK_SET);
				} else {
					fseek(out, 0, SEEK_END);
				}
			}
			
			printf("\nPalavra: %s - caracter: %c (ascii: %d)\nLeitura do buffer: %c (ascii: %d)", bufferIn, bufferIn[0], (int) bufferIn[0], cOut, (int) cOut);
			
			if(fputs(bufferIn, out) != EOF) {
				if (fputc(' ', out) == EOF) {
					printf("\nErro ao gravar palavra em \"out1.txt\".");
					break;
				}
			} else {
				printf("\nErro ao gravar palavra em \"out1.txt\".");
				break;
			}
			memset(bufferIn, 0, BUFFER_SIZE);
			i = 0;
		} else {
			bufferIn[i] = cIn;
			i++;
		}
	}
}

int main() {
	FILE *in = fopen("in.txt", "r"), *out1 = fopen("out1.txt", "r+"), *out2;
	fpos_t *posIn;
	int tamanho;
	char palavra[BUFFER_SIZE], c;
	
	if(in == NULL || out1 == NULL) {
		printf("Erro ao abrir um ou mais arquivos.\n");
		return 1;
	}
	
	insertionSort(in, out1);
	
	fclose(in);
	fclose(out1);
	return 0;
}
