#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include"lexer.h"



#define InputNodes 784
#define HiddenNodes 120
#define Outputs 9
extern double HiddenLayerBias[HiddenNodes];
extern double OuputLayerBias[Outputs];


extern double HiddenWeights[InputNodes][HiddenNodes];
extern double OutputWeights[HiddenNodes][Outputs];


int dir_exists(char* path){
	// if(mkdir(path,0777)==-1){
	// 	return 0;
	// }
	// return 1;
	DIR* dir=opendir("neural");
	if(dir == NULL){
		mkdir(path,0777);
		return 0;
	}
	closedir(dir);
	return 1;
	// if(is_dir(path))
	// 	return 1;
	// 
	// return 0;
}


void read_hiddenweights(){
	FILE* file;
	int line=0;
	file=fopen("neural/HiddenWeights.neural","r");
	while(!feof(file)){
			for(int i=0; i<HiddenNodes; i++){
				if(fscanf(file, "%lf",&HiddenWeights[line][i])==EOF)
				 	break;
			}
			line++;
			if(line==InputNodes) break;
	}
	
	fclose(file);
}

void read_outputweights(){
	FILE* file;
	int line=0;
	file=fopen("neural/OutputWeights.neural","r");
	while(!feof(file)){
			for(int i=0; i<Outputs; i++){
				if(fscanf(file, "%lf",&OutputWeights[line][i])==EOF)
				 	break;
			}
			line++;
			if(line==HiddenNodes) break;
	}
	fclose(file);
}

void read_hiddenbias(){
	FILE* file;
	file=fopen("neural/hiddenbias.neural", "r");
	for(int i =0; i<HiddenNodes; i++){
		if(fscanf(file, "%lf", &HiddenLayerBias[i])==EOF)
				break;
	}
	fclose(file);
}

void read_outputbias(){
	FILE* file;
	file=fopen("neural/outputbias.neural", "r");
	for(int i =0; i<Outputs; i++){
		if(fscanf(file, "%lf", &OuputLayerBias[i])==EOF)
				break;
	}
	fclose(file);
}
//____________________________write____________________

void write_hiddenweights(){
	FILE* writer= fopen("neural/HiddenWeights.neural", "w");
	for(int i=0; i<InputNodes; i++){
		int j =0;
		while(j<HiddenNodes-1){
			fprintf(writer, "%lf",HiddenWeights[i][j]);
			fprintf(writer," ");
			j++;
		}
		fprintf(writer, "%lf",HiddenWeights[i][HiddenNodes-1]);
		fprintf(writer,"\n");
	}
	fclose(writer);
}

void write_outputweights(){
	FILE* writer= fopen("neural/OutputWeights.neural", "w");
	for(int i=0; i<HiddenNodes; i++){
		int j =0;
		while(j<Outputs-1){
			fprintf(writer, "%lf",OutputWeights[i][j]);
			fprintf(writer," ");
			j++;
		}
		fprintf(writer, "%lf",OutputWeights[i][Outputs-1]);
		fprintf(writer,"\n");
	}
	fclose(writer);
}


void write_hiddenbias(){
	FILE* writer= fopen("neural/hiddenbias.neural", "w");
	for(int i =0; i<HiddenNodes; i++){
		// printf("%f ", HiddenLayerBias[i]);
		fprintf(writer, "%lf", HiddenLayerBias[i]);
		fprintf(writer," ");
	}
	fclose(writer);
}

void write_outputbias(){
	FILE* writer= fopen("neural/outputbias.neural", "w");
	for(int i =0; i<Outputs; i++){
		fprintf(writer, "%lf", OuputLayerBias[i]);
		fprintf(writer," ");
	}
	fclose(writer);
}


void print_matrix(double matrix[][10]){
	for(size_t i =0; i< 2; i++){
		for(size_t j=0; j<10; j++){
			printf("%f ", matrix[i][j]);
		}
		printf("\n");
	}
}



// int main(void){
// 	//still need to figure out wheter the item to read is a 1-D or 2-D matrix
// 	dir_exists("bin");
// 	// char* path="bin/mat";
// 	return 0;
// }
