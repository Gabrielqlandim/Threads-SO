#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>


pthread_mutex_t mudar;
sem_t vazio;
sem_t cheio;

typedef struct Infos{
    int *buffer;
    int buffer_sizer;
    int in, out;
}Infos;

void *produtores(void *args){
    Infos *infos = (Infos*)args;
    int item;
    while(1){
        item = rand()%100;
        sem_wait(&vazio);
        pthread_mutex_lock(&mudar);

        infos->buffer[infos->in] = item;
        infos->in = (infos->in + 1) %infos->buffer_sizer;
        printf("Produtor produziu: %d\n", item);

        pthread_mutex_unlock(&mudar);
        sem_post(&cheio);
        sleep(2);
    }
    return NULL;
}


void *consumidores(void *args){
    Infos *infos = (Infos*)args;
    int item;
    while(1){
        sem_wait(&cheio);
        pthread_mutex_lock(&mudar);

        item = infos->buffer[infos->out];
        infos->out = (infos->out + 1) %infos->buffer_sizer;
        printf("Consumidor consumiu: %d\n", item);

        pthread_mutex_unlock(&mudar);
        sem_post(&vazio);
        sleep(2);
    }
    return NULL;
}
int main(void){
    int buffer_sizer, num_produtor, num_consumidor;
    
    printf("Digite o tamanho do buffer: ");
    scanf("%d", &buffer_sizer);

    printf("Digite o numero de produtores: ");
    scanf("%d", &num_produtor);

    printf("Digite o numero de consumidores: ");
    scanf("%d", &num_consumidor);

    int buffer[buffer_sizer];
    Infos infos = {buffer, buffer_sizer, 0, 0};

    sem_init(&vazio, 0, buffer_sizer);
    sem_init(&cheio,0,0);
    pthread_mutex_init(&mudar, NULL);

    pthread_t produtoresT[num_produtor], consumidoresT[num_consumidor];
    
    for(int i=0;i<num_produtor;i++){
        pthread_create(&produtoresT[i], NULL, produtores, &infos);
    }
    for(int i=0;i<num_consumidor;i++){
        pthread_create(&consumidoresT[i], NULL, consumidores, &infos);
    }
    for(int i=0;i<num_produtor;i++){
        pthread_join(produtoresT[i], NULL);
    }
    for(int i=0;i<num_consumidor; i++){
        pthread_join(consumidoresT[i], NULL);

    }

    sem_destroy(&vazio);
    sem_destroy(&cheio);
    pthread_mutex_destroy(&mudar);

    return 0;

}

