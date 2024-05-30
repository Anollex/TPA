#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define CHUNK 16

int priority(char ch)
{
    if(ch == '*' || ch == '/')
        return 1;
    if(ch == '+' || ch == '-')
        return 2;
    return 0;
}

char *fpp(FILE *in)
{
    char *fp = NULL, *sp = NULL, *aux = NULL;
    char ch;
    int indexfp = 0, indexsp = 0, size = CHUNK;

    fp = (char *)malloc(size * sizeof(char));

    if(fp == NULL)
    {
        perror("not enough memory");
        exit(-1);
    }

    sp = (char *)malloc(CHUNK * sizeof(char));

    if(sp == NULL)
    {
        free(fp);
        perror("not enough memory");
        exit(-1);
    }


    while((ch = fgetc(in)) != '\n')
    {
        if(size <= indexfp)
        {
            size += CHUNK;
            aux = (char *)realloc(fp, size * sizeof(char));

            if(aux == NULL)
            {
                free(fp);
                free(sp);
                perror("not enough memory");
                exit(-1);
            }
            fp = aux;
        }

        if(isalpha(ch))
        {  
            fp[indexfp ++] = ch;
        }
        if(priority(ch) == 1 || ch == '(')
        {
            sp[indexsp ++] = ch;
        }
        if(priority(ch) == 2)
        {
            while(indexsp > 0 && priority(sp[--indexsp]) == 1)
            {
                fp[indexfp ++] = sp[indexsp];
                sp[indexsp] = '\0';
            }
            sp[++ indexsp] = ch;
            indexsp ++;
        }
        if(ch == ')')
        {
            while(indexsp > 0 && sp[-- indexsp] != '(')
            {
                fp[indexfp ++] = sp[indexsp];
                sp[indexsp] = '\0';
            }
            
        }
        
    }
    fp[indexfp] = '\0';
    free(sp);

    return fp;
}

int calcul(int a, int b, char op)
{
    switch(op)
            {
                case '+':
                {
                    return a + b;
                    break;
                }

                case '-':
                {
                    return a - b;
                    break;
                }

                case '*':
                {
                    return a * b;
                    break;
                }

                case '/':
                {
                    return a / b;
                    break;
                }
            }
    return 0;
}

int vfpp(char *fp, int *values)
{   
    int *vfp = NULL, *aux = NULL;
    int indexvfp = 0, size = CHUNK, E = 0;

    vfp = (int *)malloc(size * sizeof(int));

    if(vfp == NULL)
    {
        perror("not enough memory");
        exit(-1);
    }

    for(int indexfp = 0; indexfp < strlen(fp); indexfp ++)
    {
        if(size <= indexvfp)
        {
            size += CHUNK;
            aux = (int *)realloc(fp, size * sizeof(int));

            if(aux == NULL)
            {
                free(vfp);
                perror("not enough memory");
                exit(-1);
            }
            vfp = aux;
        }

        if(isalpha(fp[indexfp]))
        {
            vfp[indexvfp ++] = values[fp[indexfp] - 'a'];
        }
        else
        {
            E = calcul(vfp[indexvfp - 2], vfp[indexvfp - 1], fp[indexfp]);
            printf("%d %d\n", E, indexvfp);
            vfp[(-- indexvfp) - 1] = E;
        }
    }
    free(vfp);

    return E;
}

int *scanv(FILE *in)
{
    int *values = NULL, *aux = NULL;
    int indexv = 0, size = CHUNK;

    values = (int *)malloc(size * sizeof(int));

    if(values == NULL)
    {
        perror("not enough memory");
        exit(-1);
    }

    while((fscanf(in, "%d", &values[indexv ++])) != EOF)
    {
        if(size <= indexv)
        {
            size += CHUNK;
            aux = (int *)realloc(values, size * sizeof(int));

            if(aux == NULL)
            {
                free(values);
                perror("not enough memory");
                exit(-1);
            }
            values = aux;
        }
    }

    return values;
} 

int main(int argc, char **argv)
{
    char *fp = NULL;
    FILE *in = NULL, *out = NULL;
    int *values = NULL;
    int E = 0;

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

    fp = fpp(in);
    fprintf(out,"%s\n", fp);
    values = scanv(in);

    E = vfpp(fp, values);

    fprintf(out, "%d\n", E);
    free(values);
    free(fp);
    fclose(in);
    fclose(out);
    return 0;
}