#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

pthread_mutex_t mutexBuffer;
sem_t slotsVazios;
sem_t slotsCheios;

typedef struct {
    int *buffer;
    int bufferSize;
    int in, out;
} BufferInfo;

void *produtor(void *args) {
    BufferInfo *info = (BufferInfo *) args;
    int item;

    while (1) {
        item = rand() % 100;  // produz um item aleatório
        sem_wait(&slotsVazios);  // verifica se tem espaço
        pthread_mutex_lock(&mutexBuffer);  // bloqueia entrada

        // adiciona item no buffer
        info->buffer[info->in] = item;
        info->in = (info->in + 1) % info->bufferSize;
        printf("Produtor produziu: %d\n", item);

        pthread_mutex_unlock(&mutexBuffer);  // desbloqueia entrada
        sem_post(&slotsCheios);  // mostra que tem mais de 1 item no buffer
        sleep(1);  // sleep
    }

    return NULL;
}

void *consumidor(void *args) {
    BufferInfo *info = (BufferInfo *) args;
    int item;

    while (1) {
        sem_wait(&slotsCheios);  // verifica se tem espaço
        pthread_mutex_lock(&mutexBuffer);   // bloqueia entrada

        // remove o item do buffer
        item = info->buffer[info->out];
        info->out = (info->out + 1) % info->bufferSize;
        printf("Consumidor consumiu: %d\n", item);

        pthread_mutex_unlock(&mutexBuffer); // desbloqueia entrada
        sem_post(&slotsVazios);  // mostra que tem mais de 1 espaço vazio no buffer
        sleep(1);  // sleep
    }

    return NULL;
}

int main() {
    int bufferSize, numProdutores, numConsumidores;

    printf("Digite o tamanho do buffer: ");
    scanf("%d", &bufferSize);
    printf("Digite o número de produtores: ");
    scanf("%d", &numProdutores);
    printf("Digite o número de consumidores: ");
    scanf("%d", &numConsumidores);

    // Inicia o buffer
    int buffer[bufferSize];
    BufferInfo info = {buffer, bufferSize, 0, 0};

    // Inicializa os semáforos e mutex
    sem_init(&slotsVazios, 0, bufferSize);  
    sem_init(&slotsCheios, 0, 0);  
    pthread_mutex_init(&mutexBuffer, NULL);

    // cria os threads dos produtores e consumidores
    pthread_t produtores[numProdutores], consumidores[numConsumidores];

    for (int i = 0; i < numProdutores; i++) {
        pthread_create(&produtores[i], NULL, produtor, &info);
    }
    for (int i = 0; i < numConsumidores; i++) {
        pthread_create(&consumidores[i], NULL, consumidor, &info);
    }

    // Aguarda o término das threads (teoricamente nunca termina, pois é um loop infinito)
    for (int i = 0; i < numProdutores; i++) {
        pthread_join(produtores[i], NULL);
    }
    for (int i = 0; i < numConsumidores; i++) {
        pthread_join(consumidores[i], NULL);
    }

    return 0;
}
