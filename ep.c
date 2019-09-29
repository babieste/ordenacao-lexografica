//Barbara Este Fernandez - 31937039

#include <stdio.h>

void insertionSort(FILE *in, FILE *out) {
	int i = 0;
	char palavra[50], c;

	while((c = fgetc(in)) != EOF) {
		if(c == ' ') {
			palavra[i] = '\0';
			if(fputs(palavra, out) != EOF) {
				printf("\npalavra gravada!");
			} else {
				printf("\nErro ao gravar palavra em \"out1.txt\".");
			}
			break;
		} else {
			palavra[i] = c;
			i++;
		}
	}
	
}

int main() {
	FILE *in = fopen("in.txt", "r"), *out1 = fopen("out1.txt", "r+"), *out2;
	fpos_t *posIn;
	int tamanho;
	char palavra[50], c;
	
	if(in == NULL || out1 == NULL) {
		printf("Erro ao abrir um ou mais arquivos.\n");
		return 1;
	}
	
	insertionSort(in, out1);
	
	if(ferror(in)) {
		perror("\nErro ao ler arquivo.");
		fclose(in);
		return 1;
	}
	
	fclose(in);
	return 0;
}
