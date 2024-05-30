#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define CHUNK 16

void printa(uint *regine, int size, FILE *out)
{
    for(int i = 0; i < size; i++)
    {
        fprintf(out, "%d-%d\n", i + 1, regine[i]);
    }
    fprintf(out, "\n");
}

uint next(uint *element, int size)
{
    if(*element < size)
    {
        (*element) ++;
        return 1;
    }
    return 0;
}

int valid(uint array[], int index)
{
    for(int i = 0; i < index; i ++)
    {
            if(i + array[i] == index + array[index])
            {
            return 0;
            }

            if(i - array[i] == index - array[index])
            {
            return 0;
            }

            if(array[i] == array[index])
            {
            return 0;
            }
    }
    return 1;
}

int succes(int index, int size)
{
    return index == size;
}


int regine(int size, FILE *out)
{
    int index = 1, n = 0, v = 0, counter = 0;
    uint *poz = NULL;

    poz = (uint *)malloc(size * sizeof(uint));

    if(poz == NULL)
    {
        perror("not enough memory");
        exit(-1);
    }

    memset(poz, 0, sizeof(uint)*size);

    while(index > 0)
    {
        n = 0; v = 0;

        do
        {
            n = next(&poz[index - 1], size);

            if(n)
            {
                v = valid(poz, index - 1);
            }
        }
        while(n && !v);

        if(n)
        {
            if(succes(index, size))
            {
                printa(poz, size, out);
                counter ++;
            }
            else
            {
                index ++;
            }
        }
        else
        {
            poz[index - 1] = 0;
            index --;
        }
    }

    
    free(poz);
    return counter;
}

int main(int argc, char **argv)
{
    FILE *out = NULL;
    int size = 0;

    out = fopen(argv[1], "w");

    if(out == NULL)
    {
        perror("path not found or can't be created");
        return 1;
    }

    printf("Numarul de regine ");
    scanf("%d", &size);
    printf("soluti posibile %d\n", regine(size, out));

    fclose(out);

    return 0;
}