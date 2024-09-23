#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *escritor(void *arg);
void *leitor(void *arg);

sem_t mutex;

int leitores = 0;
int escritores = 0;


int main(void) {

  sem_init(&mutex, 0, 1);

  int num_produtor, num_consumidor;

  printf("Digite o numero de leitores: ");
  scanf("%d", &num_produtor);

  printf("Digite o numero de escitores: ");
  scanf("%d", &num_consumidor);

  pthread_t threads1_id[num_produtor];
  pthread_t threads2_id[num_consumidor];

  for (int i = 0; i < num_produtor; i++) {
    int *id = malloc(sizeof(int));
    *id = i + 1;
    pthread_create(&threads1_id[i], NULL, escritor, id);
  }

  for (int i = 0; i < num_consumidor; i++) {
    int *id = malloc(sizeof(int));
    *id = i + 1;
    pthread_create(&threads2_id[i], NULL, leitor, id);
  }

  for (int i = 0; i < num_produtor; i++) {
    pthread_join(threads1_id[i], NULL);
  }

  for (int i = 0; i < num_consumidor; i++) {
    pthread_join(threads2_id[i], NULL);
  }

  sem_destroy(&mutex);

  return 0;
}

void *escritor(void *arg) {

  int escritorAtual = *((int *)arg);
  free(arg);

  for (int i=0; i<5000; i++) {
    
    sem_wait(&mutex);
    escritores++;
    
    printf("Escritor %d escrevendo...%d\n", escritorAtual, escritores);
    sleep(1);
    
    escritores--;
    
    sem_post(&mutex);
    sleep(1);
    
  }
}

void *leitor(void *arg) {

  int leitorAtual = *((int *)arg);
  free(arg);

  for (int i=0; i<5000; i++) {

    sem_wait(&mutex);
    
    if (escritores > 0){
      sem_post(&mutex);
    }
    leitores++;

    printf("Leitor %d lendo...%d\n", leitorAtual, leitores);
    sleep(1);

    leitores--;
    sem_post(&mutex);
    sleep(1);

  }
}
