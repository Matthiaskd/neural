#include <stdlib.h>
#include <stdio.h>
#include<math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "file.h"
#include"lexer.h"



//return a random value between 0 and 1
double init_weights(){
    return ( (double)rand())/((double)RAND_MAX); 
}

//sigmoid activation function
double sigmoid(double x){
    return 1/(1+exp(-x));
}
//the derivative of sgmoid
double dsigmoid(double x){
    return x*(1-x);
}

//rectifier actvation function
double relu(double x){
    if(x>0)
        return x;
    return 0.0f;
}

//rectifier derivative
double drelu(double x){
    if(x>0)
        return 1;
    return 0.0f;
}



//shuffles the array (used for the training)
void shuffle(int *array, size_t n){
    if(n>1){
        size_t i;
        for(i=0; i<n-1; i++){
            size_t j =i+ rand()/(RAND_MAX/(n-i)+1);
            int t =array[j];
            array[j]=array[i];
            array[i]=t;
        }
    }
}

//defining the inputs/hidden and output nodes number
#define InputNodes 784
#define HiddenNodes 120
#define Outputs 9
#define Trainings 9



//the learning rate
const double lr =0.1f;

//defining the nodes and weights as global variables
double HiddenLayer[HiddenNodes];
double OutputLayer[Outputs];

double HiddenLayerBias[HiddenNodes];
double OuputLayerBias[Outputs];


double HiddenWeights[InputNodes][HiddenNodes];
double OutputWeights[HiddenNodes][Outputs];



double training_outputs[Trainings][Outputs]={{1,0,0,0,0,0,0,0,0},
                                             {0,1,0,0,0,0,0,0,0},
                                             {0,0,1,0,0,0,0,0,0},
                                             {0,0,0,1,0,0,0,0,0},
                                             {0,0,0,0,1,0,0,0,0},
                                             {0,0,0,0,0,1,0,0,0},
                                             {0,0,0,0,0,0,1,0,0},
                                             {0,0,0,0,0,0,0,1,0},
                                             {0,0,0,0,0,0,0,0,1}
                                            };



void softmax(){
    double sum = 0;
    for(int i=0; i<Outputs; i++)
        sum+=exp(sum);
    for(int i=0; i<Outputs; i++)
        OutputLayer[i]=exp(OutputLayer[i])/sum;
}   

//feeds forward the input nodes, and backpropagates if backpropagate is set to true (i.e TRUE)
int feed(int inputs[InputNodes], int backpropagate){
    //feed forward
    //activation of the hidden layer
    for(int i=0; i<HiddenNodes; i++){
        double activation=HiddenLayerBias[i];
        for(int j =0; j<InputNodes; j++){
            activation+=inputs[j] * HiddenWeights[j][i];
        }               
        HiddenLayer[i] = sigmoid(activation);
    }

    //activation of the output layer
    for(int i=0; i<Outputs; i++){
        double activation=OuputLayerBias[i];
        for(int  j=0; j<HiddenNodes; j++){
            activation+=HiddenLayer[j] * OutputWeights[j][i];
        }
        OutputLayer[i] = sigmoid(activation);
    }

    //looking for the corresponding number in te training set
    int res=0;
    for(int i =0; i<Outputs; i++){
        if(OutputLayer[i]>OutputLayer[res])
                res=i;
    }
    res+=1;
    
    
    //-------------------------------------------BACKPROPAGATION-----------------------------------------//
    //runs only if backpropagate==1
    if(backpropagate!=0){

        // printf("OK\n");
        //calculates output weights error
        double deltaOutput[Outputs];
        for(int i=0; i<Outputs; i++){
            double error = (training_outputs[backpropagate][i]-OutputLayer[i]);
            deltaOutput[i]=error * sigmoid(OutputLayer[i]);
        }


        //transpose output weights
        double ThiddenOutput[Outputs][HiddenNodes];
    
        for(int i =0; i<HiddenNodes; i++ ){
            for(int  j =0; j<Outputs; j++){
                ThiddenOutput[j][i]=OutputWeights[i][j];
            }
        }

        //calculates hidden weights error
        double deltaHidden[HiddenNodes];
        for(int i=0; i<HiddenNodes; i++){
            double error=0.0f;
            for(int j =0; j<Outputs; j++){
                error+=deltaOutput[j]*ThiddenOutput[j][i];
            }
            deltaHidden[i]=error * dsigmoid(HiddenLayer[i]);
        }
    
        //output weights and bias update
        for(int i =0; i<Outputs; i++){
            OuputLayerBias[i]+=deltaOutput[i]*lr;
            for(int j=0;j<HiddenNodes;j++){
                OutputWeights[j][i]+=HiddenLayer[j] * deltaOutput[i] * lr;
            }
        }

        //hidden weights and bias update
        for(int i =0; i<HiddenNodes; i++){
            HiddenLayerBias[i]+=deltaHidden[i]*lr;
            for(int j=0;j<InputNodes;j++){
                HiddenWeights[j][i]+=inputs[j] * deltaHidden[i] * lr;
            }
        }
        
        write_hiddenweights();
        // // printf("weights1\n");
        write_outputweights();
        // // printf("weights2\n");
        write_hiddenbias();
        // // printf("bias1\n");
        write_outputbias();
        // printf("bias2\n");


        // printf("nn terminated\n");
    }
    return res;
    
}

//the function from which the setup will be launched
int setup(){
    
    //initialisation of hidden layers weights
    char* path="neural/";
    // DIR* dir = opendir(path);
    // int exists=dir_exists(path);
    // printf("%i\n", exists);
    if(dir_exists(path)){
           read_hiddenweights();
           read_outputweights();
           read_hiddenbias();
           read_outputbias();
        //    printf("all read\n");
    }
    else{
            for(int i =0; i<InputNodes; i++){
                for(int j=0; j<HiddenNodes;j++){
                    HiddenWeights[i][j]=init_weights();
                }
            }
            //initialisation of output layers weights
            for(int i =0; i<HiddenNodes; i++){
                for(int j=0; j<Outputs;j++){
                    OutputWeights[i][j]=init_weights();
                }
            }

            //initialisation of hidden layer bias
            for(int i=0; i <HiddenNodes; i++){
                HiddenLayerBias[i]=init_weights();
            }

    
            //initialisation of the output layer bias
            for(int i=0; i <Outputs; i++){
                OuputLayerBias[i]=init_weights();
            }
    }
    
    return 1;
}

int all(int inputs[InputNodes], int t){
    //t=the number we're waiting to output-1
    //initialise the weights
    // printf("OK\n");
    setup();
    // printf("OK\n");
    //if t>0, that means we expect an output, therefore the backprop only launches if t>0
    // if(t>0)
    //     return feed(inputs, t);
    int res=feed(inputs, t);
    return res;
}

