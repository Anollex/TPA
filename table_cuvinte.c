#include<stdio.h>
#include<stdlib.h>
#include<string.h>



int main()
{
    char tabela[MAX][MAX], cuvant[MAX+1];
    int left, right, up, down; 
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; J++)
        {
            if(cuvant[0] == tabela[i][j])
            {
                up = 1; down = 1; right = 1; left = 1;
                for(int k = 1; k < strlen(cuvant); k++)
                {
                    if(cuvant[k] != tabela[i - k][j])
                    {
                        down = 0;
                    }

                    if(cuvant[k] != tabela[i + k][j])
                    {
                        up = 0;
                    }

                    if(cuvant[k] != tabela[i][j - k])
                    {
                        left = 0;
                    }

                    if(cuvant[k] != tabela[i][j + k])
                    {
                        right = 0;
                    }
                }

                if(1 == )
                {
                    printf()
                }
            }
        }
    }
}