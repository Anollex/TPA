#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define CHUNK 16

int *scana(FILE *in, int *index)
{
    int *array = NULL, *aux = NULL;
    int size = CHUNK;

    array = (int *)malloc(size * sizeof(int));

    if(array == NULL)
    {
        perror("not enough memory");
        exit(-1);
    }

    while((fscanf(in, "%d", &array[*index])) == 1)
    {
        if(size <= *index)
        {
            size += CHUNK;
            aux = (int *)realloc(array, size * sizeof(int));

            if(aux == NULL)
            {
                free(array);
                perror("not enough memory");
                exit(-1);
            }
            array = aux;
        }
        (*index) ++;
    }
    
    return array;
}

void printa(int *set, uint *permutare, int size, FILE *out)
{
    for(int i = 0; i < size; i++)
    {
        fprintf(out, "%d ", set[permutare[i] - 1]);
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


void combinari(int *set, int size, int max, FILE *out)
{
    int index = 1, n = 0, v = 0;
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
            n = next(&poz[index - 1], max);

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
                printa(set, poz, size, out);
            }
            else
            {
                index ++;
                poz[index - 1] = poz[index - 2];
            }
        }
        else
        {
            
            index --;
        }
    }

    
    free(poz);
}

int main(int argc, char **argv)
{
    int *array = NULL;
    FILE *in = NULL, *out = NULL;
    int max = 0, size = 0;

    in = fopen(argv[1], "r");

    if(in == NULL)
    {
        perror("path not found");
        return 1;
    }

    out = fopen(argv[2], "w");

    if(out == NULL)
    {
        fclose(in);
        perror("path not found or can't be created");
        return 2;
    }

    array = scana(in, &max);
    printf("combinari de %d luate cate ", max);
    scanf("%d", &size);
    combinari(array, size, max, out);

    free(array);
    fclose(in);
    fclose(out);

    return 0;
}