#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"


int main(int argc, char *argv[])
{
    SDL_Window *pWindow=NULL;           //Pointeur sur la fen�tre, ref d'un window win32
    SDL_Renderer *pRenderer=NULL;       //Pointeur sur le Rendus, ref rendu encapsul� dans window
    //SDL_Texture *pTexture=NULL;         //Pointeur sur la texture, qui poss�de l'image � afficher, ref image/texture/materiel


    //Requis pour utiliser la SDL
    if(SDL_Init(SDL_INIT_EVERYTHING)>=0)    //INIT_EVERYTHING = initialise l'audio, la vid�o, les contr�les,... cf; SDL wiki/API by name/SDL_Init
    {
        //succ�s, cr�er window
        pWindow=SDL_CreateWindow("SDL_Application",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 780, SDL_WINDOW_SHOWN);//x,y,width,eight

        //si succ�s, cr�er window et renderer
        if(pWindow!=NULL)
        {
            pRenderer=SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_PRESENTVSYNC);
           /* }
            else
            {*/

            SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);


            SDL_SetRenderTarget(pRenderer, NULL);
            SDL_Surface* image = IMG_Load("youpi_wallpaper.png");                   //Creation d'une surface � partir d'une image
            SDL_Texture* Image = SDL_CreateTextureFromSurface(pRenderer,image);     //Creation d'une texture � partir de la surface
            if(!image)
            {
                printf("Erreur de chargement de l'image : %s",SDL_GetError());
                return -1;
            }

            SDL_Rect myRect;                                                        //D�finition d'une zone d'affichage
            myRect.x = 0;
            myRect.y = 0;
            SDL_QueryTexture(Image, NULL, NULL, &myRect.w, &myRect.h);              //Appel de la texture dans le rectangle

            SDL_RenderCopy(pRenderer, Image, NULL, &myRect);
            SDL_RenderPresent(pRenderer);

            SDL_Delay(10000);

            //SDL_FreeSurface(image);
            SDL_DestroyRenderer(pRenderer); //On supprime tout ce qui � �t� cr�er
            SDL_DestroyWindow(pWindow);
            SDL_Quit();
        }
     }

    return 0;
}
