#include "../inc/text.h"

static void mx_swap_char(char *s1, char *s2)
{
    char t = *s1;
    *s1 = *s2;
    *s2 = t;
}

static void mx_str_reverse(char *s)
{
    int len = strlen(s) - 1;

    if (!s)
        return;

    for (int i = 0; i <= len / 2; i++)
        mx_swap_char(&s[i], &s[len - i]);
}

static char *mx_strnew(const int size)
{
    if (size < 0)
        return NULL;

    char *str = (char *)malloc(size + 1);

    for (int i = 0; i <= size; i++)
        str[i] = '\0';

    return str;
}

static int number_length(int number)
{
    int length = 0;

    while (number)
    {
        number /= 10;
        length++;
    }
    return length;
}

char *mx_itoa(int number)
{
    int length = number_length(number);
    int temp = number;
    char *result = mx_strnew(length);

    if (number == 0)
        return strcpy(result, "0");

    if (number == -2147483648)
        return strcpy(result, "-2147483648");

    temp = number;
    for (int i = 0; i < length; i++)
    {
        if (temp < 0)
        {
            result[length] = '-';
            temp = -temp;
        }
        result[i] = (temp % 10) + '0';
        temp /= 10;
    }

    mx_str_reverse(result);

    return result;
}

char *concat(char *s1, char *s2)
{
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);

    char *result = malloc(len1 + len2 + 1);

    if (!result)
    {
        fprintf(stderr, "malloc() failed: insufficient memory!\n");
        return NULL;
    }

    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1);

    return result;
}

void init_text()
{
    if (TTF_Init() == -1)
    {
        printf("[ERROR] TTF_Init() Failed with: %s\n", TTF_GetError());
        exit(-1);
    }
}

SDL_Texture *drawText(SDL_Renderer *gRenderer, int x, int y, char *string, int size, SDL_Color fgC)
{
    TTF_Font *font = TTF_OpenFont("./resource/NEON CLUB MUSIC_medium.ttf", size);
    if (!font)
    {
        printf("[ERROR] TTF_OpenFont() Failed with: %s\n", TTF_GetError());
        exit(-1);
    }
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, string, fgC);
    SDL_Texture *tTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    SDL_Rect imagePos2 = {((WIDTH_SCREEN - textSurface->w) / 2) + x, ((HEIGHT_SCREEN - textSurface->h) / 2) + y, textSurface->w, textSurface->h};
    SDL_RenderCopy(gRenderer, tTexture, NULL, &imagePos2);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);

    return tTexture;
}
