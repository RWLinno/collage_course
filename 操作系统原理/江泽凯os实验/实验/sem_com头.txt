#ifndef _SEM_COM_H
#define _SEM_COM_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo * _buf;
};

/*  信号量初始化函数
 *  参数        sem_id  由KEY值得到的消耗量集ID
 *             init_value 信号量初始化值
 *  返回值      错误返回-1 成功返回0
 */
int sem_init(int sem_id,int init_value)
{
    union semun sem_union;
    sem_union.val = init_value;
    if (semctl(sem_id,0,SETVAL,sem_union) ==-1 )
    {
       
        return -1;
    }
    else 
        return 0;
}
/* 信号量集删除函数
 * 参数        sem_id 由KEY值得到的信号量集ID
 * 返回值       成功 0  失败-1
 */
int sem_delete(int sem_id)
{
  if(semctl(sem_id,0,IPC_RMID,NULL) < 0)
  {
      perror("semctl_delete");
      return(-1);
  }
  else 
    return 0;

}
/************************************
 * p操作函数
 * 参数         sem_id 由KEY值得到的信号量集ID
 * ***********************************/
int sem_p(int sem_id)
{
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = -1; /*-1代表P操作*/
    buf.sem_flg = SEM_UNDO; /*进程终止时，系统自动释放残余信号量*/
    if(semop(sem_id,&buf,1) < 0 )
    {
        perror("semop1");
        return -1;
    }
    return 0;
}

/*************************
 * V操作函数
 * 参数      sem_id 由KEY值得到的信号量集ID
 ************************/
int sem_v(int sem_id)
{
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = 1; /*-1代表P操作*/
    buf.sem_flg = SEM_UNDO; /*进程终止时，系统自动释放残余信号量*/
    if(semop(sem_id,&buf,1) < 0 )
    {
        perror("semop2");
        return -1;
    }
    return 0;
}

#endif
