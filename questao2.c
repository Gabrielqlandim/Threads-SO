#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutexBuffer;
pthread_cond_t condVazio;
pthread_cond_t condCheio;

typedef struct {
    int *buffer;
    int bufferSize;
    int in, out;
} BufferInfo;

void *produtor(void *args) {
    BufferInfo *info = (BufferInfo *) args;
    int item;

    while (1) {
        item = rand() % 100;
        
        pthread_mutex_lock(&mutexBuffer);  // bloqueia acesso ao buffer
        
        while ((info->in + 1) % info->bufferSize == info->out) {
            pthread_cond_wait(&condVazio, &mutexBuffer);  // sspera por espaço no buffer
        }

        // Adiciona item no buffer
        info->buffer[info->in] = item;
        info->in = (info->in + 1) % info->bufferSize;
        printf("Produtor produziu: %d\n", item);

        pthread_cond_signal(&condCheio);  // diz que há um item no buffer
        pthread_mutex_unlock(&mutexBuffer);  // desbloqueia o acesso ao buffer
        
        sleep(1);
    }

    return NULL;
}

void *consumidor(void *args) {
    BufferInfo *info = (BufferInfo *) args;
    int item;

    while (1) {
        pthread_mutex_lock(&mutexBuffer);  // bloqueia acesso ao buffer
        
        while (info->in == info->out) {
            pthread_cond_wait(&condCheio, &mutexBuffer);  // espera por um item no buffer
        }

        // Remove item do buffer
        item = info->buffer[info->out];
        info->out = (info->out + 1) % info->bufferSize;
        printf("Consumidor consumiu: %d\n", item);

        pthread_cond_signal(&condVazio);  // diz que há espaço vazio no buffer
        pthread_mutex_unlock(&mutexBuffer);  // desbloqueia o acesso ao buffer
        
        sleep(1);
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

    int buffer[bufferSize];
    BufferInfo info = {buffer, bufferSize, 0, 0};

    // inicia mutex e variáveis de condição
    pthread_mutex_init(&mutexBuffer, NULL);
    pthread_cond_init(&condVazio, NULL);
    pthread_cond_init(&condCheio, NULL);

    // cria threads dos produtores e consumidores
    pthread_t produtores[numProdutores], consumidores[numConsumidores];

    for (int i = 0; i < numProdutores; i++) {
        pthread_create(&produtores[i], NULL, produtor, &info);
    }
    for (int i = 0; i < numConsumidores; i++) {
        pthread_create(&consumidores[i], NULL, consumidor, &info);
    }

    for (int i = 0; i < numProdutores; i++) {
        pthread_join(produtores[i], NULL);
    }
    for (int i = 0; i < numConsumidores; i++) {
        pthread_join(consumidores[i], NULL);
    }

    return 0;
}
