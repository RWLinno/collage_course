#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "sem_com.h"
#include "shm_com.h"
 

#define IPC_KEY_PATH    "/"
#define SHM_KEY_PROJ    1
#define SEM_KEY_PROJ    2

int main()
{
    
    int shm_id[15],sem_id1,sem_id2,sem_id3;
    shm_buf *shmbuf[15];
    /*获得共享内存*/
    int i=0;
    for(i=0;i<10;i++)    
        if((shm_id[i] = shmget((ftok(IPC_KEY_PATH,i)),sizeof(shm_buf),IPC_CREAT|0666)) <0 )
        {
	    perror("shmget");
    	    exit(-1);
        }    
    // if((shm_id = shmget(ftok(IPC_KEY_PATH,SHM_KEY_PROJ),sizeof(shm_buf),IPC_CREAT|0666)) <0 )
    // {
        // perror("shmget");
        // exit(-1);
    // }
    // printf("consumer\'s shm_id:%d\n",shm_id);

    /*获得信号量集合*/
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
    // if((sem_id = semget(ftok(IPC_KEY_PATH,SEM_KEY_PROJ),1,IPC_CREAT|0666)) < 0 )
    // {
        // perror("semget");
        // exit(-1);
    // }
    // printf("consumer\'s sem_id:%d\n",sem_id);
    /*映射共享内存到当前进程*/
    for(i=0;i<10;i++)  
        if((shmbuf[i] = (shm_buf *)shmat(shm_id[i],NULL,0)) <0 )
        {
            perror("shmat");
            exit(-1);
        }  
    // if((shmbuf = (shm_buf *)shmat(shm_id,NULL,0)) <0 )
    // {
       // perror("shmat");
    //     exit(-1);
    // }
    printf("shared memory init  sucessful\n");
    /*读取共享内存中数据*/
    int cnt=0;
    printf("Do you want to read?（1:Yes or 0:No）\n");
    int op;
    scanf("%d",&op);
    while(1)
    {
        cnt=(cnt+1)%10;
	// sleep(5); 
        sem_p(sem_id3);
        sem_p(sem_id1);
        printf("Data from shared memory : process[%d],%s \n",shmbuf[cnt]->pid,shmbuf[cnt]->buffer);
        /*读取数据后将共享内存清空*/
        if (strncmp(shmbuf[cnt]->buffer,"quit",4) == 0 )
        {
            break;
        }
        shmbuf[cnt]->pid = 0 ;
        memset(shmbuf[cnt]->buffer,0,SHM_BUFSIZE);
        sem_v(sem_id1);
        sem_v(sem_id2);
	printf("Do you want to read?（1:Yes or 0:No）\n");
        scanf("%d",&op);    
    }

    /*解除共享内存映射*/
    for(i=0;i<10;i++)
        if (shmdt(shmbuf[i]) < 0 ) 
        {
    	    perror("shmdt");
 	    exit(-1);
        }
    // if (shmdt(shmbuf) < 0 ) 
    // {
        // perror("shmdt");
        // exit(-1);
    // }
    /*删除共享内存*/
    for(i=0;i<10;i++)
        if(shmctl(shm_id[i],IPC_RMID,NULL) < 0 )
        {
            perror("shmctl_remove");
            exit(-1);
        }
    
    exit(0);
}


