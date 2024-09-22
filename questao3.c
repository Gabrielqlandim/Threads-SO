#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *escritor(void *arg);
void *leitor(void *arg);

sem_t area;
sem_t cont;
sem_t escritorLock;

int leitores = 0;
int escritores = 0;


int main(void) {

  sem_init(&area, 0, 1);
  sem_init(&cont, 0, 1);
  sem_init(&escritorLock, 0, 1);

  int num_produtor, num_consumidor;

  printf("Digite o numero de produtores: ");
  scanf("%d", &num_produtor);

  printf("Digite o numero de consumidores: ");
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

  sem_destroy(&area);
  sem_destroy(&cont);
  sem_destroy(&escritorLock);

  return 0;
}

void *escritor(void *arg) {

  int escritorAtual = *((int *)arg);
  free(arg);

  while (1) {

    sem_wait(&escritorLock);
    
    escritores++;
    
    if(escritores == 1){
      sem_wait(&area);
    }
    
    sem_post(&escritorLock);

    printf("Escritor %d esta escrevendo...%d\n", escritorAtual, escritores);
    sleep(1);
    

    sem_wait(&escritorLock);  
    escritores--;
    if (escritores == 0){
      sem_post(&area);
    }
    sem_post(&escritorLock);

    sleep(1);
    
  }
}

void *leitor(void *arg) {

  int leitorAtual = *((int *)arg);
  free(arg);

  while (1) {
    
    sem_wait(&cont);

    while (escritores > 0){
      sem_post(&cont);
      sleep(1);
      sem_wait(&cont);
    }
    
    leitores++;

    if (leitores == 1) {
      sem_wait(&area);
    }

    sem_post(&cont);

    printf("Leitor %d lendo...%d\n", leitorAtual, leitores);
    sleep(1);

    sem_wait(&cont);

    leitores--;

    if (leitores == 0) {
      sem_post(&area);
    }

    sem_post(&cont);
    sleep(1);
  }
}
