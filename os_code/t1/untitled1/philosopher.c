#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

struct meal{
    pthread_mutex_t chopsticks_left;
    pthread_mutex_t chopsticks_right;
};
extern void METEX(struct meal* meal, pthread_mutex_t left, pthread_mutex_t right)
{
    meal->chopsticks_left=left;
    meal->chopsticks_right=right;
}


void* philosopher1(void* arg) {
    struct meal* meal1 = (struct meal *)arg;
    int num=0;
    while(num<30) {
        printf("哲学家1第%d次思考1秒\n",num);
        sleep(0.1);
        while(person_have >= 4) {
            int i=0;
            if(i==0) {
                printf("哲学家1避免死锁，不拿筷子\n");
                i++;
            }
        }
        pthread_mutex_trylock(&meal1->chopsticks_left);

        pthread_mutex_trylock(&meal1->chopsticks_right);

        //int meal_time=rand()%5+3;
        //printf("哲学家1第%d次进餐%d秒\n",num, meal_time);
        //sleep(meal_time);
        printf("哲学家1第%d次进餐1秒\n",num);
        sleep(1);

        pthread_mutex_unlock(&meal1->chopsticks_right);
        pthread_mutex_unlock(&meal1->chopsticks_left);
        num++;
    }
    return NULL;
}

void* philosopher2(void* arg) {
    struct meal* meal2 = (struct meal *)arg;
    int num=0;
    while(num<30) {
        printf("哲学家2第%d次思考1秒\n",num);
        sleep(0.1);
        while(person_have >= 4) {
            int i=0;
            if(i==0) {
                printf("哲学家2避免死锁，不拿筷子\n");
                i++;
            }
        }
        pthread_mutex_trylock(&meal2->person_lock);
        person_have++;
        pthread_mutex_unlock(&meal2->person_lock);

        pthread_mutex_trylock(&meal2->chopsticks_left);
        pthread_mutex_trylock(&meal2->chopsticks_right);

//        int meal_time=rand()%5+3;
//        printf("哲学家2第%d次进餐%d秒\n",num, meal_time);
//        sleep(meal_time);
        printf("哲学家2第%d次进餐1秒\n",num);
        sleep(1);

        pthread_mutex_unlock(&meal2->chopsticks_right);
        pthread_mutex_unlock(&meal2->chopsticks_left);
        pthread_mutex_trylock(&meal2->person_lock);
        person_have--;
        pthread_mutex_unlock(&meal2->person_lock);
        num++;
    }
    return NULL;
}

void* philosopher3(void* arg) {
    struct meal* meal3 = (struct meal *)arg;
    int num=0;
    while(num<30) {
        printf("哲学家3第%d次思考1秒\n",num);
        sleep(0.1);
        while(person_have >= 4) {
            int i=0;
            if(i==0) {
                printf("哲学家3避免死锁，不拿筷子\n");
                i++;
            }
        }

        pthread_mutex_trylock(&meal3->person_lock);
        person_have++;
        pthread_mutex_unlock(&meal3->person_lock);

        pthread_mutex_trylock(&meal3->chopsticks_left);
        pthread_mutex_trylock(&meal3->chopsticks_right);

//        int meal_time=rand()%5+3;
//        printf("哲学家3第%d次进餐%d秒\n",num, meal_time);
//        sleep(meal_time);
        printf("哲学家3第%d次进餐1秒\n",num);
        sleep(1);

        pthread_mutex_unlock(&meal3->chopsticks_right);
        pthread_mutex_unlock(&meal3->chopsticks_left);
        pthread_mutex_trylock(&meal3->person_lock);
        person_have--;
        pthread_mutex_unlock(&meal3->person_lock);
        num++;
    }
    return NULL;
}

void* philosopher4(void* arg) {
    struct meal* meal4 = (struct meal *)arg;
    int num=0;
    while(num<30) {
        printf("哲学家4第%d次思考1秒\n",num);
        sleep(0.1);
        while(person_have >= 4) {
            int i=0;
            if(i==0) {
                printf("哲学家4避免死锁，不拿筷子\n");
                i++;
            }
        }
        pthread_mutex_trylock(&meal4->person_lock);
        person_have++;
        pthread_mutex_unlock(&meal4->person_lock);
        pthread_mutex_trylock(&meal4->chopsticks_left);

        pthread_mutex_trylock(&meal4->chopsticks_right);

//        int meal_time=rand()%5+3;
//        printf("哲学家4第%d次进餐%d秒\n",num, meal_time);
//        sleep(meal_time);
        printf("哲学家4第%d次进餐1秒\n",num);
        sleep(1);

        pthread_mutex_unlock(&meal4->chopsticks_right);
        pthread_mutex_unlock(&meal4->chopsticks_left);
        pthread_mutex_trylock(&meal4->person_lock);
        person_have--;
        pthread_mutex_unlock(&meal4->person_lock);
        num++;
    }
    return NULL;
}

void* philosopher5(void* arg) {
    struct meal* meal5 = (struct meal *)arg;
    int num=0;
    while(num<30) {
        printf("哲学家5第%d次思考1秒\n",num);
        sleep(0.1);
        while(person_have >= 4) {
            int i=0;
            if(i==0) {
                printf("哲学家5避免死锁，不拿筷子\n");
                i++;
            }
        }
        pthread_mutex_trylock(&meal5->person_lock);
        person_have++;
        pthread_mutex_unlock(&meal5->person_lock);
        pthread_mutex_trylock(&meal5->chopsticks_left);

        pthread_mutex_trylock(&meal5->chopsticks_right);

//        int meal_time=rand()%5+3;
//        printf("哲学家5第%d次进餐%d秒\n",num, meal_time);
//        sleep(meal_time);
        printf("哲学家5第%d次进餐1秒\n",num);
        sleep(1);

        pthread_mutex_unlock(&meal5->chopsticks_right);
        pthread_mutex_unlock(&meal5->chopsticks_left);
        pthread_mutex_trylock(&meal5->person_lock);
        person_have--;
        pthread_mutex_unlock(&meal5->person_lock);
        num++;
    }
    return NULL;
}


int main() {
    pthread_mutex_t chopsticks1;
    pthread_mutex_t chopsticks2;
    pthread_mutex_t chopsticks3;
    pthread_mutex_t chopsticks4;
    pthread_mutex_t chopsticks5;

    pthread_mutex_init(&chopsticks1, NULL);
    pthread_mutex_init(&chopsticks1, NULL);
    pthread_mutex_init(&chopsticks2, NULL);
    pthread_mutex_init(&chopsticks3, NULL);
    pthread_mutex_init(&chopsticks4, NULL);
    pthread_mutex_init(&chopsticks5, NULL);
    struct meal* meal1=(struct meal *)malloc(sizeof(struct meal));
    struct meal* meal2=(struct meal *)malloc(sizeof(struct meal));
    struct meal* meal3=(struct meal *)malloc(sizeof(struct meal));
    struct meal* meal4=(struct meal *)malloc(sizeof(struct meal));
    struct meal* meal5=(struct meal *)malloc(sizeof(struct meal));
    METEX(meal1,chopsticks1,chopsticks2,person_lock);
    METEX(meal2,chopsticks2,chopsticks3,person_lock);
    METEX(meal3,chopsticks3,chopsticks4,person_lock);
    METEX(meal4,chopsticks4,chopsticks5,person_lock);
    METEX(meal5,chopsticks5,chopsticks1,person_lock);
    pthread_t tid1, tid2, tid3, tid4, tid5;

    pthread_create(&tid1, NULL, (void*)philosopher1, (void*)meal1);
    pthread_create(&tid2, NULL, (void*)philosopher2, (void*)meal2);
    pthread_create(&tid3, NULL, (void*)philosopher3, (void*)meal3);
    pthread_create(&tid4, NULL, (void*)philosopher4, (void*)meal4);
    pthread_create(&tid5, NULL, (void*)philosopher5, (void*)meal5);

    // 该调用等待标识的进程终止。
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);
    pthread_join(tid5, NULL);

    free(meal1);
    free(meal2);
    free(meal3);
    free(meal4);
    free(meal5);

    pthread_mutex_destroy(&chopsticks1);
    pthread_mutex_destroy(&chopsticks2);
    pthread_mutex_destroy(&chopsticks3);
    pthread_mutex_destroy(&chopsticks4);
    pthread_mutex_destroy(&chopsticks5);

    return 0;
}
