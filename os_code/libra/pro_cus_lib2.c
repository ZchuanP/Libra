#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_PRODUCT 50
char product[MAX_PRODUCT];
int empty=MAX_PRODUCT;
int full=0;
int in=0,out=0;
FILE *f;

pthread_mutex_t produce_lock=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t customer_lock=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t pro_cus_lock=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t pro_cus_lock1=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t produce_cond=PTHREAD_COND_INITIALIZER;
pthread_cond_t customer_cond=PTHREAD_COND_INITIALIZER;


void *produce(void* arg){
    while(1) {
        pthread_mutex_lock(&produce_lock);
        if (empty <= 0) {
            printf("%lld生产者等待\n",(long long)pthread_self());
            pthread_cond_wait(&produce_cond, &pro_cus_lock);
        } else {
            if (f == NULL) {
                printf("open file error!\n");
                exit(0);
            }
            char c = fgetc(f);
            product[in] = c;
            printf("%lld生产者生产了产品%c 1件\n", (long long)pthread_self(), c);
            in = (in + 1) % MAX_PRODUCT;
            sleep(1);
            pthread_mutex_lock(&pro_cus_lock1);
            full++;
            empty--;
            pthread_mutex_unlock(&pro_cus_lock1);
            pthread_cond_signal(&customer_cond);

        }
        pthread_mutex_unlock(&produce_lock);
    }
    return NULL;
}


void *customer(){
    while(1){
        pthread_mutex_lock(&customer_lock);
        if(full<=0){
            printf("%lld消费者等待\n",(long long)pthread_self());
            pthread_cond_wait(&customer_cond,&pro_cus_lock);
        }else{
            char c=product[out];
            printf("%lld消费者消耗了产品%c 1件\n",(long long )pthread_self(),c);
            out=(out+1)%MAX_PRODUCT;
            sleep(1);
            pthread_mutex_lock(&pro_cus_lock1);
            full--;
            empty++;
            pthread_mutex_unlock(&pro_cus_lock1);
            pthread_cond_signal(&produce_cond);

        }
        pthread_mutex_unlock(&customer_lock);
    }
    return NULL;
}


int main(){
    f=fopen("product.txt", "r");
    pthread_t tid1,tid2,tid3,tid4,tid5,tid6,tid7;
    pthread_create(&tid1,NULL,produce,NULL);
    pthread_create(&tid2,NULL,produce,NULL);
    pthread_create(&tid3,NULL,produce,NULL);
    pthread_create(&tid4,NULL,customer,NULL);
    pthread_create(&tid5,NULL,customer,NULL);
    pthread_create(&tid6,NULL,customer,NULL);
    pthread_create(&tid7,NULL,customer,NULL);

    pthread_join(tid1,NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);
    pthread_join(tid5, NULL);
    pthread_join(tid6, NULL);
    pthread_join(tid7, NULL);

    pthread_mutex_destroy(&produce_lock);
    pthread_mutex_destroy(&customer_lock);
    pthread_mutex_destroy(&pro_cus_lock);
    pthread_mutex_destroy(&pro_cus_lock1);
    fclose(f);

    return 0;
}
