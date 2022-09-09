// MATEMATICA DISCRETA 2 2022.1
// LUCAS GOMES CALDAS 212005426
// RAFAEL XAVIER CANABRAVA 200026551
// CASO DE TESTE 
// 3
// 2 1 5
// 3 2 7
// 5 7 11

#include <stdio.h>
#include <stdlib.h>

int *mdc_n, *mdc_p, *solucao, *solucao_aux, *coe_aux;

int MDC(int a, int b)
{
    int resto;
    do
    {
        resto = a % b;

        a = b;
        b = resto;

    } while (resto != 0);

    return a;
}

void calculaMDC_N(int *num, int k)
{
    int x = 0;
    for (int i = 0; i < k; i++)
    {
        for (int j = 1; j <= k / 2 + 1; j++)
        {
            if (i != j && i <= j)
            {
                mdc_n[x] = MDC(num[i], num[j]);
                x++;
            }
        }
    }
}

void calculaMDC_PARTICULAR(int *a, int *b, int k)
{
    for (int i = 0; i < k; i++)
    {
        mdc_p[i] = MDC(a[i], b[i]);
        // printf("mdc(%d, %d) = %d\n", a[i], b[i], mdc_p[i]);
    }
}

void teoremaCHINES(int *a, int *b, int *n, int k)
{
    // solucao numerica para cada congruencia linear
    int c, x = 1;
    for (int i = 0; i < k; i++) 
    {
        while (x++)
        {
            c = (a[i] * x - b[i]) % n[i];
            if (c == 0)
                break;
        }
        solucao[i] = x;
        x = 1;
    }

    // coefiente auxiliar
    int n_aux = 1;
    for (int i = 0; i < k; i++) 
    {
        for (int j = 0; j < k; j++) 
        {
            n_aux *= n[j];
            // printf("n_aux[%d] = %d\n", j, n_aux);
        }
        coe_aux[i] =  n_aux/n[i];
        n_aux = 1;
    }

    // solucao auxiliar
    x = 1;
    for (int i = 0; i < k; i++) 
    {
        while (x++)
        {
            c = (coe_aux[i] * x - 1) % n[i];
            if (c == 0)
                break;
        }
        solucao_aux[i] = x;
        // printf("solucao_aux[%d] = %d\n", i, solucao_aux[i]);
        x = 1;
    }

    // solucao geral do teorema Chines do Resto
    int s = 0; 
    for (int i = 0; i < k; i++) 
    {
        s += solucao[i]*coe_aux[i]*solucao_aux[i];
    }
    // printf("s = %d\n", s);

    // produto dos modulos
    int prod_modulos = 1;
    for (int i = 0; i < k; i++)
    {
        prod_modulos *= n[i];
    }
    // printf("prod_modulos = %d\n", prod_modulos);

    int solucao_geral = s % prod_modulos;
    printf("\nLogo, a solucao geral do sistema => %d(mod%d)\n", solucao_geral, prod_modulos);
    
}

int main(void)
{
    // aix = bi(modn)
    int k;
    scanf("%d", &k);

    int a[k], b[k], n[k];
    for (int i = 0; i < k; i++)
    {
        scanf("%d %d %d", &a[i], &b[i], &n[i]);
    }


    mdc_n = malloc(sizeof(int)*k);
    calculaMDC_N(n, k);

    mdc_p = malloc(sizeof(int)*k);
    calculaMDC_PARTICULAR(a, n, k);

    for (int i = 0; i < k; i++) 
    {
        if (mdc_n[i] != 1 || mdc_p[i] != 1) 
        {
            printf("OOOPAA, Sistema sem solucao amigao\n");
            return 0;
        }
    }

    solucao = malloc(sizeof(int)*k);
    coe_aux = malloc(sizeof(int)*k);
    solucao_aux = malloc(sizeof(int)*k);
    teoremaCHINES(a, b, n, k);

    free(mdc_n);
    free(mdc_p);
    free(solucao);
    free(coe_aux);
    free(solucao_aux);

    return 0;
}