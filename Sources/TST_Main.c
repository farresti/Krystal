
#include "SDL_If.h"

#ifdef _MSC_VER
    #pragma comment( lib, "SDL2.lib" )
    #pragma comment( lib, "SDL2main.lib" )
    #pragma comment( lib, "SDL2_image.lib" )
    #pragma comment( lib, "SDL2_mixer.lib" )
    #pragma comment( lib, "SDL2_ttf.lib" )
#endif

int main(int argc, char* argv[])
{
    SDL_Input   sInput;
    SDL_Sprite *pSprite;
    SDL_Button  sButton;
    char       *szPath = NULL;
    SDL_Sound  *pSndButterfly = NULL;
    SDL_Music  *pMusic = NULL;

    (void) argc;
    (void) argv;

    // Tests module 'COM'
    UTIL_RandInit( );

    COM_Log_Init(COM_LOG_DEBUG, "krystal");
    szPath = UTIL_StrBuild("folder/", "image", ".png", NULL);
    COM_Log_Print(COM_LOG_INFO, szPath);

    COM_Log_Print(COM_LOG_DEBUG,    "COM_LOG_DEBUG");
    COM_Log_Print(COM_LOG_INFO,     "COM_LOG_INFO");
    COM_Log_Print(COM_LOG_WARNING,  "COM_LOG_WARNING");
    COM_Log_Print(COM_LOG_ERROR,    "COM_LOG_ERROR");
    COM_Log_Print(COM_LOG_CRITICAL, "COM_LOG_CRITICAL");

    UTIL_Free(&szPath);

    // Tests module 'SDL'
    SDL_Init( SDL_INIT_VIDEO );
    IMG_Init( IMG_INIT_PNG );

    /* Initialisation de SDL_mixer*/
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
        COM_Log_Print(COM_LOG_CRITICAL, "Can't initialize SDL_Mixer : %s", Mix_GetError());
    }

    SDL_Ctx_Init("Krystal", 640, 480);
    SDL_Input_Init(&sInput);

    pSprite = SDL_Sprite_Alloc( "button" );
    SDL_Button_Init(&sButton, pSprite, 10, 10);

    // Load a sound
    Mix_AllocateChannels(1); 
    pSndButterfly = SDL_Sound_Alloc("boing_x");

    // Load a music
    pMusic = SDL_Music_Alloc("forest");
    Mix_VolumeMusic(100);
    SDL_Music_Play(pMusic, -1);

    while (sInput.bQuit == SDL_FALSE)
    {
        SDL_Input_Update(&sInput);
        SDL_Button_Update(&sButton, &sInput);

        SDL_Ctx_RenderClear( );

        if (sInput.bKey[SDL_SCANCODE_E])
        {
            sInput.bKey[SDL_SCANCODE_E] = SDL_FALSE;
            COM_Log_Print(COM_LOG_INFO, "Playing a sound");
            SDL_Sound_Play(pSndButterfly, 0, 100, 0);
        }
        if (sInput.bKey[SDL_SCANCODE_P])
        {
            sInput.bKey[SDL_SCANCODE_P] = SDL_FALSE;
            COM_Log_Print(COM_LOG_INFO, "Pause/Unpause the music");
            if (Mix_PausedMusic())
            {
                Mix_ResumeMusic();
            }
            else Mix_PauseMusic();
            
        }

        SDL_Button_Draw(&sButton);
        SDL_Ctx_RenderPresent( );
    }

    SDL_Sprite_Free(&pSprite);

    SDL_Ctx_Quit( );

    IMG_Quit( );
    SDL_Sound_Free(&pSndButterfly);
    SDL_Music_Free(&pMusic);
    SDL_Quit( );
    COM_Log_Quit( );
    
    return EXIT_SUCCESS;
}
