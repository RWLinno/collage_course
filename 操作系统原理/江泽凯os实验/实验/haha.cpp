#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE    512        // 数据块的大小 
#define BLOCK_NUM     512        // 数据块的块数
#define INODE_NUM   32        // i节点的数目
#define FILENUM    8        // 打开文件表的数目

typedef struct
{
	char user_name[10]="Jiang";        // 用户名
} User;

// i节点(32B)
typedef struct
{
	short inum;          // 文件i节点号
	char  file_name[10]; // 文件名
	char  type;          // 文件类型
	char  user_name[10]; // 文件所有者
	short iparent;       // 父目录的i节点号 
	short length;        // 文件长度
	short address[2];    // 存放文件的地址        
} Inode;

// 打开文件表(16B)
typedef struct
{
	short inum;             // i节点号
	char  file_name[10]; // 文件名
	short mode;             // 读写模式(1:read, 2:write,
	//         3:read and write)
	short offset;        // 偏移量
} File_table;

int argc;        					// 命令的参数的个数
char *argv[5];        				// 命令的参数
int cur_dir;        				// 当前目录
char the_buffer[2*BLOCK_SIZE];    	// 缓冲区
User user;        					// 当前用户
char bitmap[BLOCK_NUM];    			// 位示图数组 
Inode inode_array[INODE_NUM];    	// i节点数组
File_table file_array[FILENUM];    	// 打开文件表数组
char image_name[10] = "hd.dat";    	// 文件系统名称
FILE *fp;                    		// 打开文件指针

//函数声明
void init(void);
int  analyse(char *);
void save_inode(int);
int get_BLOCK_NUM(void);
void read_blk(int);
void write_blk(int);
void release_blk(int);
void pathset();
void delet(int innum);
int  check(int i);
void help(void);
void cd(void);
void ls(void);
void mkdir(void);
void creat(void);
void open(void);
void read(void);
void write(void);
void close(void);
void del(void);
void command(void);
void rmdir();

//命令解析： 
int command_analyse(char *str)
{
	int i;
	char the_buffer[20];
	char *ptr_char;
	char *syscmd[]={"", "cd", "ls", "mkdir", "creat", "open", "read", "write", "close", "delete","rmdir"};	//, "logout", "clear","format","quit","rmdir"};
	argc = 0;
	for(i = 0, ptr_char = str; *ptr_char != '\0'; ptr_char++)
	{
		if(*ptr_char != ' ')
		{
			while(*ptr_char != ' ' && (*ptr_char != '\0'))
				the_buffer[i++] = *ptr_char++;
			argv[argc] = (char *)malloc(i+1);
			strncpy(argv[argc], the_buffer, i);
			argv[argc][i] = '\0';
			argc++;
			i = 0;
			if(*ptr_char == '\0')	break;
		}
	}
	if(argc != 0) 
	{
		for(i = 0; (i < 15) && strcmp(argv[0], syscmd[i]); i++);
			return i;
	}
	else return 15;
}

//文件创建/删除命令
void creat(void)
{
	int i;
	if(argc != 2)
	{
		printf("command creat must have one args. \n");
		return ;
	}
	for(i = 0; i < INODE_NUM; i++)
	{
		if((inode_array[i].inum > 0) && (inode_array[i].type == '-') && !strcmp(inode_array[i].file_name, argv[1]))
		{
			printf("The file has been exsited.\n");
			return ;
		}
	}
	for(i = 0; i < INODE_NUM; i++)
		if(inode_array[i].inum < 0) break;
	if(i == INODE_NUM)
	{
		printf("There is no else INode.\n");
		exit(-1);
	}
	inode_array[i].inum = i;
	strcpy(inode_array[i].file_name, argv[1]);
	inode_array[i].type = '-';
	strcpy(inode_array[i].user_name, user.user_name);
	inode_array[i].iparent = cur_dir;
	inode_array[i].length = 0;
	save_inode(i);
}
void delet(int innum)
{
	inode_array[innum].inum = -1;
	if(inode_array[innum].length >= 0)
	{
		release_blk(inode_array[innum].address[0]);
		if(inode_array[innum].length >= 512)
		release_blk(inode_array[innum].address[1]);
	}
	save_inode(innum);    
}
void del(void)
{
	int i,chk;
	if(argc != 2)
	{
		printf("Command delete must have one args. \n");
		return ;
	}
	for(i = 0; i < INODE_NUM; i++)
		if((inode_array[i].inum > 0) && (inode_array[i].type == '-') && !strcmp(inode_array[i].file_name, argv[1]))
			break;
	if(i == INODE_NUM)
	{
		printf("This file doesn't exist.\n");
		return ;
	}
	chk=check(i);
	if(chk!=1)  
	{
		printf("This file is not yours !\n");
		return ;  
	}
	delet(i);    
}

//目录创建/删除命令 
void mkdir(void)
{
	int i;
	if(argc != 2)
	{
		printf("command mkdir must have two args. \n");
		return ;
	}

	for(i = 0; i < INODE_NUM; i++)
		if(inode_array[i].inum < 0) break;
	if(i == INODE_NUM)
	{
		printf("Inode is full.\n");
		exit(-1);
	}
	inode_array[i].inum = i;
	strcpy(inode_array[i].file_name, argv[1]);
	inode_array[i].type = 'd';
	strcpy(inode_array[i].user_name,user.user_name);
	inode_array[i].iparent = cur_dir;
	inode_array[i].length = 0;
	save_inode(i);
}

void rmdir()
{
	int i,j,t,flag=0;
	if(argc != 2)
	{
		printf("Command delete must have one args. \n");
		return ;
	}
	for(i = 0; i < INODE_NUM; i++)
	if((inode_array[i].inum > 0) && (inode_array[i].iparent == cur_dir) && (inode_array[i].type == 'd')&&(!strcmp(inode_array[i].file_name,argv[1])))
	{
		int chk=check(i);
		if(chk!=1)  
		{
			printf("This directory is not your !\n");
			return ;
		}
		else j=inode_array[i].inum;
		for(t=0;t<INODE_NUM;t++)
		{
			if((inode_array[t].inum>0)&&(inode_array[t].iparent==j)&&(inode_array[i].type == '-'))
				delet(t);
			else if((inode_array[t].inum>0)&&(inode_array[t].iparent==j)&&(inode_array[i].type == 'd'))
				delet(t);
		}
		if(t == INODE_NUM)
			delet(j);
	}
	if(i == INODE_NUM)
		delet(i);
	return;
}

//显示目录内容命令
void ls(void)
{
	int i;
	int dcount=0,fcount=0;
	short bcount=0;
	if(argc != 1)
	{
		printf("Command ls must have one args. \n");
		return ;
	}
	for(i = 0; i < INODE_NUM; i++)
		if((inode_array[i].inum> 0) && (inode_array[i].iparent == cur_dir))
		{
			if(inode_array[i].type == 'd' && check(i))
			{
				dcount++;
				printf("%-20s<DIR>\n", inode_array[i].file_name);
			}
			if(inode_array[i].type == '-' && check(i))
			{
				fcount++;
				bcount+=inode_array[i].length;
				printf("%-20s%12d bytes\n", inode_array[i].file_name,inode_array[i].length);
			}
		}
	printf("\n%d file(s)%11d bytes\n",fcount,bcount);
	printf("%d dir(s) %11d bytes FreeSpace\n",dcount,1024*1024-bcount);    
}
//文件打开/关闭open/ close
void open()
{
	int i, inum, mode, filenum,chk;
	if(argc != 2)
	{
		printf("command open must have one args. \n");
		return ;
	}
	for(i = 0; i < INODE_NUM; i++)
	if((inode_array[i].inum > 0) && (inode_array[i].type == '-') && !strcmp(inode_array[i].file_name,argv[1]))
		break;
	if(i == INODE_NUM)
	{
		printf("The file you want to open doesn't exsited.\n");
		return ;
	}
	inum = i;
	chk=check(i);
	if(chk!=1)  
	{
		printf("This file is not your !\n");
		return ;  
	}
	printf("Please enter the open mode:(1:only read, 2:only write, 3: read and write):");
	scanf("%d", &mode);
	gets(the_buffer);
	if((mode < 1) || (mode > 3))
	{
		printf("the number you entered is wrong.\n");
		return;
	}
	for(i = 0; i < FILENUM; i++)
		if(file_array[i].inum < 0) break;
	if(i == FILENUM) 
	{
		printf("The file table is full, please close some file.\n");
		return ;
	}
	filenum = i;
	file_array[filenum].inum = inum;
	strcpy(file_array[filenum].file_name, inode_array[inum].file_name);
	file_array[filenum].mode = mode;
	file_array[filenum].offset = 0;
	printf("Open file %s by ", file_array[filenum].file_name);
	if(mode == 1) printf("the file can be only read.\n");
	else if(mode == 2) printf("the file can be only written.\n");
	else printf("the file can be read and written.\n");
}

void close(void)
{
	int i;
	if(argc != 2)
	{
		printf("Command close must have one args. \n");
		return ;
	}
	for(i = 0; i < FILENUM; i++)
		if((file_array[i].inum > 0) && !strcmp(file_array[i].file_name, argv[1]))
			break;
	if(i == FILENUM)
	{
		printf("This file doesn't be opened.\n");
		return ;
	}
	else 
	{
		file_array[i].inum = -1;
		printf("Close %s successful!\n", argv[1]);
	}
}

//文件读/写 read/write
void read()
{
	int i, start=0, num, inum;
	if(argc != 2)
	{
		printf("command read must have one args. \n");
		return;
	}
	for(i = 0; i < FILENUM; i++)
		if((file_array[i].inum > 0) && !strcmp(file_array[i].file_name,argv[1]))
			break;
	if(i == FILENUM)
	{
		printf("Open %s first.\n", argv[1]);
		return ;
	}
	else if(file_array[i].mode == 2)
	{
		printf("Can't read %s.\n", argv[1]);
		return ;
	}
	inum = file_array[i].inum;
	if(inode_array[inum].length > 0)
	{
		gets(the_buffer);
		read_blk(inum);    
		for(i = 0; the_buffer[i] != '\0'; i++)
			printf("%c", the_buffer[i]);
		printf("\n");
	}
}
void write()
{
	int i, inum, length=0;
	if(argc != 2)
	{
		printf("Command write must have one args. \n");
		return ;
	}
	for(i = 0; i < FILENUM; i++)
		if((file_array[i].inum>0)&&!strcmp(file_array[i].file_name,argv[1]))
			break;
	if(i == FILENUM)
	{
		printf("Open %s first.\n", argv[1]);
		return ;
	}
	else if(file_array[i].mode == 1)
	{
		printf("Can't write %s.\n", argv[1]);
		return ;
	}
	inum = file_array[i].inum;
	printf("The length of %s:%d\n", inode_array[inum].file_name, inode_array[inum].length);
	if(inode_array[inum].length == 0)
	{
		printf("The length you want to write(0-1024):");
		scanf("%d", &length);
		gets(the_buffer);
		if((length < 0) && (length >1024))
		{
			printf("Input wrong.\n");
			return ;
		}
		inode_array[inum].length = length;
		inode_array[inum].address[0] = get_BLOCK_NUM();
		if(length > 512)
			inode_array[inum].address[1] = get_BLOCK_NUM();
		save_inode(inum);
		printf("Input the data(Enter to end):\n");
		gets(the_buffer);
		write_blk(inum);
	}
	else
		printf("This file can't be written.\n");
}

//切换当前目录
void cd(void)
{
	int i;
	if(argc != 2)
	{
		printf("Command cd must have two args. \n");
		return ;
	}
	if(!strcmp(argv[1], ".."))
		cur_dir = inode_array[cur_dir].iparent;
	else
	{
		// 遍历i节点数组
		for(i = 0; i < INODE_NUM; i++)
		if((inode_array[i].inum>0)&&(inode_array[i].type=='d')&&(inode_array[i].iparent==cur_dir)&&!strcmp(inode_array[i].file_name,argv[1])&&check(i))
			break;
		if(i == INODE_NUM) 
			printf("This directory isn't exsited.\n");
		else
			cur_dir = i;
	}
}

void init(void)
{
	int   i;
	if((fp = fopen(image_name, "r+b")) == NULL)
	{
		printf("Can't open file %s.\n", image_name);
		exit(-1);
	}
	for(i = 0; i < BLOCK_NUM; i++)
		bitmap[i] = fgetc(fp);
	for(i = 0; i < INODE_NUM; i++)
		fread(&inode_array[i], sizeof(Inode), 1, fp);
	cur_dir = 0;
	for(i = 0; i < FILENUM; i++)
		file_array[i].inum = -1;
}

void save_inode(int num)
{
	if((fp=fopen(image_name, "r+b")) == NULL)
	{
		printf("Can't open file %s\n", image_name);
		exit(-1);
	}
	fseek(fp, 512+num*sizeof(Inode), SEEK_SET);
	fwrite(&inode_array[num], sizeof(Inode), 1, fp);
	fclose(fp);
}

int get_BLOCK_NUM(void)
{
	int i;
	for(i = 0; i < BLOCK_NUM; i++)
		if(bitmap[i] == '0') break;
	// 未找到空闲数据块
	if(i == BLOCK_NUM)
	{
		printf("Data area is full.\n");
		exit(-1);
	}
	bitmap[i] = '1';
	if((fp=fopen(image_name, "r+b")) == NULL)
	{
		printf("Can't open file %s\n", image_name);
		exit(-1);
	}
	fseek(fp, i, SEEK_SET);
	fputc('1', fp);
	fclose(fp);
	return i;
}

void read_blk(int num)
{
	int  i, len;
	char ch;
	int  add0, add1;
	len = inode_array[num].length;
	add0 = inode_array[num].address[0];
	if(len > 512)
		add1 = inode_array[num].address[1];
	if((fp = fopen(image_name, "r+b")) == NULL)
	{
		printf("Can't open file %s.\n", image_name);
		exit(-1);
	}
	fseek(fp, 1536+add0*BLOCK_SIZE, SEEK_SET);
	ch = fgetc(fp);
	for(i=0; (i < len) && (ch != '\0') && (i < 512); i++)
	{
		the_buffer[i] = ch;
		ch = fgetc(fp);
	}
	if(i >= 512)
	{
		fseek(fp, 1536+add1*BLOCK_SIZE, SEEK_SET);
		ch = fgetc(fp);
		for(; (i < len) && (ch != '\0'); i++)
		{
			the_buffer[i] = ch;
			ch = fgetc(fp);    
		}
	}
	the_buffer[i] = '\0';
	fclose(fp);
}

void write_blk(int num)
{
	int  i, len;
	int  add0, add1;
	add0 = inode_array[num].address[0];
	len  = inode_array[num].length;
	if((fp = fopen(image_name, "r+b")) == NULL)
	{
		printf("Can't open file %s.\n", image_name);
		exit(-1);
	}
	fseek(fp, 1536+add0*BLOCK_SIZE, SEEK_SET);
	for(i=0; (i<len)&&(the_buffer[i]!='\0')&&(i < 512); i++)
	fputc(the_buffer[i], fp);
	if(i == 512)
	{
		add1 = inode_array[num].address[1];
		fseek(fp, 1536+add1*BLOCK_SIZE, SEEK_SET);
		for(; (i < len) && (the_buffer[i] != '\0'); i++)
		fputc(the_buffer[i], fp);
	}
	fputc('\0', fp);
	fclose(fp);
}

void release_blk(int num)
{
	FILE *fp;
	if((fp=fopen(image_name, "r+b")) == NULL)
	{
		printf("Can't open file %s\n", image_name);
		exit(-1);
	}
	bitmap[num] = '0';
	fseek(fp, num, SEEK_SET);
	fputc('0', fp);
	fclose(fp);
}

void pathset()
{
	char path[50];
	int m,n;
	if(inode_array[cur_dir].inum == 0)
	strcpy(path,user.user_name);
	else
	{
		strcpy(path,user.user_name);
		m=0;
		n=cur_dir;
		while(m != cur_dir)
		{
			while(inode_array[n].iparent != m)
			{
				n = inode_array[n].iparent;
			}
			strcat(path,"/");
			strcat(path,inode_array[n].file_name);
			m = n;
			n = cur_dir;
		}
	}
	printf("[%s]@",path);
}

int check(int i)
{
	int j;
	char *uuser,*fuser;
	uuser=user.user_name;
	fuser=inode_array[i].user_name;
	j=strcmp(fuser,uuser);
	if(j==0)  return 1;
	else      return 0;
}

void errcmd()
{
	printf("This command is not allowed\n");
}

void command(void)
{
	char cmd[100];
	system("cls");
	do
	{
		pathset();
		gets(cmd);
		switch(command_analyse(cmd))
		{
			case 1: 
				cd(); 
				break;
			case 2: 
				printf("The files in this directory are:\n"); 
			    ls(); 
			    break;
			case 3: 
			    mkdir(); 
			    printf("\nYou have made the directory successfully\n");
			    break;
			case 4: 
			    creat(); 
			    printf("\nYou have created the file successfully\n");
			    break;
			case 5: 
			    open(); 
			    break;
			case 6: 
			    read(); 
			    break;
			case 7: 
			    write(); 
			    break;
			case 8: 
			    close(); 
			    break;
			case 9: 
			    del(); 
			    printf("\nYou have deleted the file successfully\n");
			    break;
            case 10: 
				rmdir();
				printf("\nYou have removed the directory successfully\n");
				break;
			case 11:
			    errcmd();
				break;
			default:
				break;
		}
	}while(1);
}

int main(void)
{
	init();
	command();
	return 0;
}
