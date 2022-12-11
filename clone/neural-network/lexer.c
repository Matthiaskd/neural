#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "nn2.h"
#include "file.h"
int mat[784];
void convert(SDL_Surface* surface)
{
    // int k=1;
    Uint32* pixels = surface->pixels;
    int len = surface->w * surface->h;
    SDL_PixelFormat* format = surface->format;

    SDL_LockSurface(surface);
    for (int i = 0; i < len; i++)
    {
	    Uint8 r, g, b;
	    SDL_GetRGB(pixels[i], format, &r, &g, &b);
	    if (0.3*r + 0.59*g + 0.11*b>255*0.31){
            mat[i] = 0;
            
        }
	        
	    else
	        mat[i] = 1;
    }
    SDL_UnlockSurface(surface);
    SDL_FreeSurface(surface);
}	


int train(){
        // int k=0;
        DIR* dir=opendir("dataset");
        if(dir==NULL)
            return 1;
        struct dirent* entity;
        entity=readdir(dir);
        entity=readdir(dir);
        entity=readdir(dir);

        while(entity !=NULL){
            char folder[30]="dataset/";
            char* file=entity->d_name;
            strcat(folder, file);

            SDL_Surface* surf=IMG_Load(folder);
            convert(surf);
            int num=file[0]-'0';
            printf("num: %i ", num);
        
            printf("got: %i\n",all(mat,num-1));
            
            entity=readdir(dir);
            
        }
        closedir(dir);
        return 1;
}

int main(int argc,char** argv){
    if(argc!=2)
        return 1;
    char* path=argv[1];
    
    if(path[0]=='T'){
        for(int i=0; i < 10000; i++){
            train();
        }
    }
    else{
        SDL_Surface* surf=IMG_Load(path);
        convert(surf);
        printf("int:%i \n",all(mat,1));
    }
    
    
    return 0;
}
