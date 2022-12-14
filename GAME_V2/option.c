#include "header.h"
#include "option.h"

void save_volume(int volume)
{
    FILE *fichier = NULL;
    fichier = fopen("resources/file/volume.txt", "w");
    fprintf(fichier, "%d", volume);
    fclose(fichier);
}

int get_volume()
{
    int volume;
    FILE *fichier = NULL;
    fichier = fopen("resources/file/volume.txt", "r");
    while (!feof(fichier))
        fscanf(fichier, "%d", &volume);
    fclose(fichier);
    return volume;
}

int afficher_option(SDL_Surface *screen)
{
    int sng = 0, scr = 0, sex = 0, sop = 0, x, y;
    int volum = get_volume();

    int hb = 100, //Button Height
        lb = 300, //Button Width
        bs = 100,
        vol_width = 300;
    TTF_Init();

    Mix_Chunk *music1;
    Mix_AllocateChannels(2);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
        printf("%s", Mix_GetError());
    }
    music1 = Mix_LoadWAV("resources/sound/ClicDeSouris.wav");

    Mix_Music *music;
    music = Mix_LoadMUS("resources/sound/music.mp3");
    Mix_VolumeMusic(volum);
    Mix_PlayMusic(music, -1);

    //background creation
    SDL_Surface *background = NULL;
    background = IMG_Load("resources/image/optionback.png");
    // get back pos
    SDL_Rect background_pos;
    background_pos.x = 0;
    background_pos.y = 0;

    //chargement de la nouvelle souris
    SDL_Surface *mouse2 = IMG_Load("resources/image/curseur3.png");
    SDL_Rect pos_mouse2;

    //volume button creation
    SDL_Surface *volume[4];
    volume[0] = IMG_Load("resources/image/volume1.png");
    volume[1] = IMG_Load("resources/image/volume2.png");
    volume[2] = IMG_Load("resources/image/volume3.png");
    volume[3] = IMG_Load("resources/image/volume4.png");
    int vl = 0, v = 0;
    if (volum == 0)
        v = 0;
    if (volum == 33)
        v = 1;
    if (volum == 66)
        v = 2;
    if (volum == 99)
        v = 3;
    //volume button pos
    SDL_Rect volume_pos;
    volume_pos.x = 450;
    volume_pos.y = 50;

    //fullscreen button creation
    SDL_Surface *full[3];
    full[0] = IMG_Load("resources/image/button_full.png");
    full[1] = IMG_Load("resources/image/button_full2.png");
    full[2] = IMG_Load("resources/image/button_full1.png");
    int fl = 0;
    //fullscreen button pos
    SDL_Rect full_pos;
    full_pos.x = 100;
    full_pos.y = volume_pos.y + hb + bs;

    //back button creation
    SDL_Surface *back[3];
    back[0] = IMG_Load("resources/image/button_back.png");
    back[1] = IMG_Load("resources/image/button_back2.png");
    back[2] = IMG_Load("resources/image/button_back1.png");
    int ba = 0;
    //back button pos
    SDL_Rect back_pos;
    back_pos.x = 100;
    back_pos.y = full_pos.y + hb + bs;

    //text creation

    TTF_Font *police = NULL;
    police = TTF_OpenFont("resources/font.ttf", 60);
    SDL_Color couleur = {255, 255, 255}, couleur1 = {255, 0, 0};
    SDL_Surface *texte = NULL;
    texte = TTF_RenderText_Solid(police, "volume", couleur);

    //text pos
    SDL_Rect texte_pos;
    texte_pos.x = 100;
    texte_pos.y = volume_pos.y + 20;
    SDL_Flip(screen);
    int t = 0;
    SDL_Event event;
    int done = 1;
    while (done)
    {
        t = 0;

        SDL_GetMouseState(&x, &y);
        pos_mouse2.x = x;
        pos_mouse2.y = y;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                done = 0;
                break;
            case SDLK_ESCAPE:
                done = 0;
                break;

            //with keyboard
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    /*****************************************************************************************************/
                case SDLK_UP: //upper arrow
                    if (vl == 0 && fl == 0 && ba == 0)
                    {
                        vl = 1;
                        Mix_PlayChannel(-1, music1, 0);
                    }
                    else if (vl == 1 && t == 0)
                    {
                        ba = 1;
                        vl = 0;
                        fl = 0;
                        Mix_PlayChannel(-1, music1, 0);
                        t = 1;
                    }
                    else if (ba == 1 && t == 0)
                    {
                        fl = 1;
                        vl = 0;
                        ba = 0;
                        t = 1;
                        Mix_PlayChannel(-1, music1, 0);
                    }
                    else if (fl == 1 && t == 0)
                    {
                        fl = 0;
                        vl = 1;
                        ba = 0;
                        t = 1;
                        Mix_PlayChannel(-1, music1, 0);
                    }

                    break;
                    /*****************************************************************************************************/
                case SDLK_DOWN: //lower arrow
                    if (vl == 0 && fl == 0 && ba == 0)
                    {
                        ba = 1;
                        Mix_PlayChannel(-1, music1, 0);
                    }
                    else if (vl == 1 && t == 0)
                    {
                        ba = 0;
                        vl = 0;
                        fl = 1;

                        t = 1;
                        Mix_PlayChannel(-1, music1, 0);
                    }
                    else if (fl == 1 && t == 0)
                    {
                        fl = 0;
                        vl = 0;
                        ba = 1;

                        t = 1;
                        Mix_PlayChannel(-1, music1, 0);
                    }
                    else if (ba == 1 && t == 0)
                    {
                        ba = 0;
                        fl = 0;
                        vl = 1;
                        t = 1;
                        Mix_PlayChannel(-1, music1, 0);
                    }

                    break;

                    /*****************************************************************************************************/
                case SDLK_RETURN: //enter
                    if (fl == 1)
                    {
                        screen = SDL_SetVideoMode(1366, 768, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
                    }
                    else if (ba == 1)
                    {
                        done = 0;
                    }
                    break;
                    /*****************************************************************************************************/
                case SDLK_RIGHT: //raise volume
                    if (volum < 99 && vl == 1)
                    {
                        volum += 33;
                        v++;
                        Mix_VolumeMusic(volum);
                    }
                    break;
                    /*****************************************************************************************************/
                case SDLK_LEFT: //lower volume
                    if (volum > 0 && vl == 1)
                    {
                        volum -= 33;
                        v--;
                        Mix_VolumeMusic(volum);
                    }
                    break;

                }

                /*****************************************************************************************************/

            case SDL_MOUSEMOTION: //with mouse
                vl = 0;
                fl = 0;
                ba = 0;
                t = 0;

                if (event.motion.x > texte_pos.x && event.motion.y > texte_pos.y && event.motion.x < texte_pos.x + lb && event.motion.y < texte_pos.y + hb)

                {

                    vl = 1;
                    sng++;
                    if (sng == 1)
                        Mix_PlayChannel(-1, music1, 0);
                    sop = 0;
                    scr = 0;
                }

                if ((event.motion.x > full_pos.x && event.motion.y > full_pos.y) && (event.motion.x < full_pos.x + lb && event.motion.y < full_pos.y + hb))
                {

                    fl = 1;
                    sop++;
                    if (sop == 1)
                        Mix_PlayChannel(-1, music1, 0);
                    sng = 0;
                    scr = 0;
                }
                if (event.motion.x > back_pos.x && event.motion.y > back_pos.y && event.motion.x < back_pos.x + lb && event.motion.y < back_pos.y + hb)
                {
                    ba = 1;
                    scr++;
                    if (scr == 1)
                        Mix_PlayChannel(-1, music1, 0);
                    sng = 0;
                    sop = 0;
                }

                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (vl == 1)
                    {
                        if (volum < 99 && vl == 1)
                        {
                            volum += 33;
                            v++;
                            Mix_VolumeMusic(volum);
                        }
                        Mix_PlayChannel(-1, music1, 0);
                    }

                    else if (fl == 1)
                    {
                        screen = SDL_SetVideoMode(1366, 768, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
                        Mix_PlayChannel(-1, music1, 0);
                    }

                    else if (ba == 1)
                    {
                        Mix_PlayChannel(-1, music1, 0);
                        //SDL_Delay(600);
                        done = 0;
                    }
                }
                if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    if (vl == 1)
                        if (volum > 0 && vl == 1)
                        {
                            volum -= 33;
                            v--;
                            Mix_VolumeMusic(volum);
                        }
                }
                break;
                /*****************************************************************************************************/

            } //fin switch event
        }     //fin pollevent

        //couleur text volume
        if (vl == 1)
            texte = TTF_RenderText_Solid(police, "volume", couleur1);
        else
            texte = TTF_RenderText_Solid(police, "volume", couleur);

        //afficher
        //SDL_FillRect(screen, NULL, SDL_MapRGB((screen)->format, 0, 0, 0));
        SDL_BlitSurface(background, NULL, screen, &background_pos);
        SDL_BlitSurface(volume[v], NULL, screen, &volume_pos);
        SDL_BlitSurface(full[fl], NULL, screen, &full_pos);
        SDL_BlitSurface(back[ba], NULL, screen, &back_pos);
        SDL_BlitSurface(texte, NULL, screen, &texte_pos);
        SDL_BlitSurface(mouse2, NULL, screen, &pos_mouse2);
        SDL_Flip(screen);

    } //fin while done

    save_volume(volum);
    Mix_FreeChunk(music1);
    SDL_FreeSurface(background);
    TTF_CloseFont(police);
    TTF_Quit();
} //fin focnt
