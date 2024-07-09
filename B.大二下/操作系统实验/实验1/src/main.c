#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>

#define SEM_MUTEX 0
#define SEM_EMPTY 1
#define SEM_FULL 2

#define PRODUCER_NUM 3
#define CONSUMER_NUM 4
#define BUFFER_LEN 5

struct mybuffer
{
    char str[BUFFER_LEN];
    int head;
    int tail;
};

void P(int sem_id, int sem_num)
{
    struct sembuf sem_b;
    sem_b.sem_num = sem_num;
    sem_b.sem_op = -1;
    sem_b.sem_flg = SEM_UNDO;
    semop(sem_id, &sem_b, 1);
}

void V(int sem_id, int sem_num)
{
    struct sembuf sem_b;
    sem_b.sem_num = sem_num;
    sem_b.sem_op = 1;
    sem_b.sem_flg = SEM_UNDO;
    semop(sem_id, &sem_b, 1);
}

void producer(int sem_id, struct mybuffer *buf, int i)
{
    FILE *fp;
    char data[1024]; // 存储"data.txt"文件中的字符
    int index;       // 随机索引
    if ((fp = fopen("data.txt", "r")) == NULL)
    {
        printf("Can't open file data.txt\n");
        exit(1);
    }
    fgets(data, sizeof(data), fp); // 读取"data.txt"文件中的字符到data数组
    fclose(fp);
    srand(time(NULL) + i); // 初始化随机数生成器
    while (1)
    {
        index = rand() % 26; // 生成一个0到25的随机数
        P(sem_id, SEM_EMPTY);
        P(sem_id, SEM_MUTEX);
        sleep(3);
        buf->str[buf->tail] = data[index]; // 从data数组中随机取出一个字符
        buf->tail = (buf->tail + 1) % BUFFER_LEN;
        printf("Producer %d (PID: %d) put %c into buffer\n", i, getpid(), data[index]);
        printf("Buffer: ");
        for (int i = 0; i < BUFFER_LEN; i++)
        {
            if (buf->str[i] != '\0')
            {
                printf("%c ", buf->str[i]);
            }
        }
        printf("\n");
        printf("\n");
        V(sem_id, SEM_MUTEX);
        V(sem_id, SEM_FULL);
    }
    exit(0);
}
void consumer(int sem_id, struct mybuffer *buf, int i)
{
    char ch;
    while (1)
    {
        P(sem_id, SEM_FULL);
        P(sem_id, SEM_MUTEX);
        sleep(3);
        ch = buf->str[buf->head];
        buf->str[buf->head] = '\0'; // 清空取出字符的位置
        buf->head = (buf->head + 1) % BUFFER_LEN;
        printf("Consumer %d (PID: %d) get %c from buffer\n", i, getpid(), ch);
        printf("Buffer: ");
        for (int i = 0; i < BUFFER_LEN; i++)
        {
            if (buf->str[i] != '\0') // 如果字符不是'\0'，则打印
            {
                printf("%c ", buf->str[i]);
            }
        }
        printf("\n");
        printf("\n");

        V(sem_id, SEM_MUTEX);
        V(sem_id, SEM_EMPTY);
    }
}

int main()
{
    int sem_id = semget(IPC_PRIVATE, 3, IPC_CREAT | 0666);
    semctl(sem_id, SEM_MUTEX, SETVAL, 1);
    semctl(sem_id, SEM_EMPTY, SETVAL, BUFFER_LEN);
    semctl(sem_id, SEM_FULL, SETVAL, 0);

    int shm_id = shmget(IPC_PRIVATE, sizeof(struct mybuffer), IPC_CREAT | 0666);
    struct mybuffer *buf = shmat(shm_id, NULL, 0);
    buf->head = buf->tail = 0;

    for (int i = 0; i < PRODUCER_NUM; i++)
    {
        if (fork() == 0)
        {
            producer(sem_id, buf, i);
            exit(0);
        }
    }

    for (int i = 0; i < CONSUMER_NUM; i++)
    {
        if (fork() == 0)
        {
            consumer(sem_id, buf, i);
            exit(0);
        }
    }

    for (int i = 0; i < PRODUCER_NUM + CONSUMER_NUM; i++)
    {
        wait(NULL);
    }

    semctl(sem_id, 0, IPC_RMID, 0);
    shmctl(shm_id, IPC_RMID, 0);

    return 0;
}