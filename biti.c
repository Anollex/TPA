#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<math.h>

#define RANGE 1001

void count(uint8_t *array, FILE *in)
{
    uint16_t nr = 0;

    while(fscanf(in, "%hu", &nr) == 1)
    {
        array[nr / 8] |= (uint8_t)1 << (nr % 8);
    }
}

void print(uint8_t *array, FILE * out)
{
    for(uint16_t index = 0; index < RANGE; index ++)
    {
        if((array[index / 8] & (uint8_t)1 << (index % 8)) == 0)
        {
            fprintf(out,"%u nu apare \n", index);
        }
        else
        {
            fprintf(out,"%u apare \n", index);
        }
    }
}

void printb(uint8_t *array, FILE *out)
{

    for(uint16_t index = 0; index < RANGE; index ++)
    {
        if((array[index / 8] & (uint8_t)1 << (index % 8)) == 0)
        {
            fprintf(out,"0");
        }
        else
        {
            fprintf(out,"1");
        }
    }
    fprintf(out,"\n");
}

int main(int argc, char ** argv) // arg1 in, arg2 out
{
    uint8_t *array = NULL;
    uint16_t size = 0;
    FILE *in = NULL, *out = NULL;

    in = fopen(argv[1], "r");

    if(in == NULL)
    {
        perror("path not found");
        exit(-2);
    }

    out = fopen(argv[2], "w");

    if(out == NULL)
    {
        fclose(in);
        perror("path not found or can't be created");
        exit(-3);
    }

    size = ceil((double)RANGE / 8);
    //printf("%u", size);
    array = (uint8_t *)malloc(size * sizeof(uint8_t));

    if(array == NULL)
    {
        fclose(in);
        fclose(out);
        perror("not enough memory");
        exit(-1);
    }

    count(array, in);
    printb(array, out);
    print(array, out);

    free(array);
    fclose(in);
    fclose(out);
    return 0;
}