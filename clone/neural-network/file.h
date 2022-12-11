#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
int dir_exists(char* path);

void read_hiddenweights();
void read_outputweights();
void read_hiddenbias();
void read_outputbias();
void write_hiddenweights();
void write_outputweights();
void write_hiddenbias();
void write_outputbias();
void print_matrix(double matrix[][10]);
