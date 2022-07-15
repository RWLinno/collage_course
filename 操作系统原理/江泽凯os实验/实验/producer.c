#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "sem_com.h"
#include "shm_com.h"
 

#define IPC_KEY_PATH    "/"
#define SHM_KEY_PROJ    1
#define SEM_KEY_PROJ    2

int main()
{
    
    int shm_id[15],sem_id1,sem_id2,sem_id3;
    shm_buf *shmbuf[15];
    /*创建共享内存*/ 
    int i=0;
    for(i=0;i<10;i++)    
        if((shm_id[i] = shmget((ftok(IPC_KEY_PATH,i)),sizeof(shm_buf),IPC_CREAT|0666)) <0 )
        {
	    perror("shmget");
    	    exit(-1);
        }
    for(i=0;i<10;i++)
        printf("producer\'s shm_id:%d\n",shm_id[i]);
    /*创建信号量集合*/
    if((sem_id1 = semget(ftok(IPC_KEY_PATH,1),1,IPC_CREAT|0666)) < 0 )
    {
        perror("semget");
        exit(-1);
    }
    if((sem_id2 = semget(ftok(IPC_KEY_PATH,2),1,IPC_CREAT|0666)) < 0 )
    {
        perror("semget");
        exit(-1);
    }
    if((sem_id3 = semget(ftok(IPC_KEY_PATH,3),1,IPC_CREAT|0666)) < 0 )
    {
        perror("semget");
        exit(-1);
    }
    printf("producer\'s sem_id:%d\n",sem_id1);
    printf("producer\'s sem_id:%d\n",sem_id2);
    printf("producer\'s sem_id:%d\n",sem_id3);
    /*信号量初始值为1*/
    sem_init(sem_id1,1);   //互斥信号量
    sem_init(sem_id2,10);  //empty信号量
    sem_init(sem_id3,0);   //full信号量

    /*映射共享内存到当前进程*/
    for(i=0;i<10;i++)  
        if((shmbuf[i] = (shm_buf *)shmat(shm_id[i],NULL,0)) <0 )
        {
            perror("shmat");
            exit(-1);
        }
    printf("shared memory init  sucessful\n");

    /*向共享内存中写数据*/
    int cnt=0;
    while(1)
    {
        cnt=(cnt+1)%10;
	printf("Do you want to write?（1:Yes or 0:No）if you do, please Enter some text to shared memory\n");
	int op;
        scanf("%d",&op);
        // printf("%d", op);
	if(op==1)
	{
        // printf("and please Enter some text to shared memory\n");
        sem_p(sem_id1);
	sem_p(sem_id2);
        if (fgets(shmbuf[cnt]->buffer,SHM_BUFSIZE,stdin) ==NULL)
        {
            perror("fgets");
            sem_v(sem_id1);
            break;
        }
        shmbuf[cnt]->pid = getpid();
        sem_v(sem_id1);
        sem_v(sem_id3);
	}
	if(op==0)
	    break;
    }

    /*删除信号量集*/
    sem_delete(sem_id1);
    sem_delete(sem_id2);
    sem_delete(sem_id3);
    /*解除共享内存映射*/
    for(i=0;i<10;i++)
        if (shmdt(shmbuf[i]) < 0 ) 
        {
    	    perror("shmdt");
 	    exit(-1);
        }
    exit(0);
}


