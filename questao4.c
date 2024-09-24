#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_rwlock_t rwlock;
int escritor = 0;

void *leitores(void *args)
{   
    int *id = (int *)args;
    free(args);
    for (int i = 0; i < 5000; i++)
    {
        
        printf("Leitor %d esta lendo\n", *id);
        sleep(2);
    }
    
    return NULL;
}


void *escritores(void *args)
{
    int *id = (int *)args;
    free(args);
    for(int i=0; i<5000; i++){
        pthread_rwlock_wdlock(&rwlock);
        escritor++;
        printf("Escritor %d esta escrevendo\n", *id);
        pthread_rwlock_unlock(&rwlock);
        sleep(2);
    }
    
    return NULL;
}


int main(void)
{

    int num_leitor, num_escritor;
    printf("Digite o numero de leitores: ");
    scanf("%d", &num_leitor);

    printf("Digite o numero de escitores: ");
    scanf("%d", &num_escritor);

    pthread_rwlock_init(&rwlock, NULL);
    pthread_t threads1_leitores[num_leitor];
    pthread_t threads2_escritores[num_escritor];

    for (int i = 0; i < num_leitor; i++)
    {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&threads1_leitores[i], NULL, leitores, id);
    }

    for (int i = 0; i < num_escritor; i++)
    {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&threads2_escritores[i], NULL, escritores, id);
    }

    for (int i = 0; i < num_leitor; i++)
    {
        pthread_join(threads1_leitores[i], NULL);
    }

    for (int i = 0; i < num_escritor; i++)
    {
        pthread_join(threads2_escritores[i], NULL);
    }
    return 0;
}