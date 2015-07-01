


/* 成绩查询系统*/
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
//# include <windows.h>

struct data 
{
    char subject[10];
    int score;
};
struct student
{
    char num[20];
    char name[20];
    struct data d[6];
    int totalscore;
    struct student *next;
};

struct student *creat_link(); 
void insert(struct student *,long);
struct student *creat_node();
void find();
void insert(struct student *,long);
void change(struct student *);
void writefile(struct student *);
struct student *readfile();
void student();
void teacher();
void administrator();
void add();
void ranking();
int loading();
void printchar(char, int, int);

void main()
{
    int i, t;
    struct student *head=NULL;
    printf("----***** 您正在使用的是成绩查询系统 *****----\n");
    printf("请输入您的身份\n");
    printf("1.学生\n");
    printf("2.教师\n");
    printf("3.管理员\n");
    scanf("%d",&i);
    switch(i)
    {
    case 1:/* 学生查询成绩*/
        {
           student();
           break;
        }
    case 2:/* 教师查询*/
        {
            teacher();
            break;
        }
    case 3:/* 管理员录入*/
        {
			t=loading();
			if(t==1)
			{
				administrator();
			}
			else
			{
				printf("密码错误您不能使用管理员\n");
			}
        }
    }

}
struct student *creat_link()
{
    struct student *head;
    head=(struct student *)malloc(sizeof(struct student));
    head->next=NULL;
    return (head);
}
struct student *creat_node()
{
    int i;
    struct student *p;
    p=(struct student *)malloc(sizeof(struct student));
    printf("请输入学生的学号,名字,成绩");
    scanf("%s",p->num);
    fflush(stdin);
    scanf("%s",p->name);
    //gets(p->name);
    fflush(stdin);
    p->totalscore=0;
    for(i=0;i<5;i++)
    {
        fflush(stdin);
        scanf("%s",p->d[i].subject);
        scanf("%d",&p->d[i].score);
        p->totalscore+=p->d[i].score;
    }
    return (p);


}
void insert(struct student *head,long n)
{
    int i=1;
    struct student *p;
    while(i<=n)
    {
        p=creat_node();
        if(head->next==NULL)
        {
            head->next=p;
            p->next=NULL;
        }
        else
        {
             p->next=head->next;
             head->next=p;
        }
        i++;
    }
}
void find()/*查找学生信息*/
{
    struct student *head=NULL,*p;
    char num[20];
	int i;
    head=readfile();
    p=head->next;
    printf("请输入您的学号:\n");
    scanf("%s",num);
    while(p!=NULL)
    {
        if(strcmp(p->num,num)==0);
    	{
            printf("%s\t%s\t",p->num,p->name);
            for(i=0;i<5;i++)
    		{
                printf("%s\t",p->d[i].subject);
                printf("%d\n",p->d[i].score);
    		}
            printf("%d\n",p->totalscore);
			ranking(p);
			break;
    	}
        p=p->next;
    }
	if(p==NULL)
	{
		printf("学号输入有误\n");
	}
}
void change(struct student * head)/*修改学生信息*/
{
    char num[20];
    int i;
    struct student *p;
    FILE *fp;
    printf("输入所要更改学生信息的学生学号\n");
    scanf("%s",num);
    p=head->next;
    while(p->next)
    {
        if(strcmp(p->num,num)==0)
        {
            
            if((fp=fopen("成绩管理系统.txt","at+"))==NULL)
                printf("can not open file!\n");
            else
            { 
                fprintf(fp,"%s %s",p->name,p->num);
                for(i=0;i<5;i++)
                {         
                    fprintf(fp,"%s %d",p->d[i].subject,p->d[i].score);
                }
                fclose(fp);
            }   	
        }
        p=p->next;
    } 
}
void writefile(struct student *head)
{
    FILE *fp;
    int i;
    struct student *p=head->next;
    if((fp=fopen("成绩管理系统.txt","w+"))==NULL)
        printf("can not open file!\n");
    else
    {
        while(p!=NULL)
        {
            fprintf(fp,"%s %s %d",p->name,p->num,p->totalscore);
            for(i=0;i<5;i++)
            {
                fprintf(fp,"%s %d",p->d[i].subject,p->d[i].score);
            }
            p=p->next;     
        }
        fclose(fp);
    }
}
struct student *readfile()
{
    int i;
    FILE *fp;
	struct student *head=(struct student *)malloc(sizeof(struct student));
    struct student *p=head;
    struct student *q;
	head->next=NULL;
    if((fp=fopen("成绩管理系统.txt","r"))==NULL)
    printf("can not open file!\n");
    else
    {
        while(!feof(fp))
    	{
            q=(struct student *)malloc(sizeof(struct student));
            fscanf(fp,"%s %s %d",q->name,q->num,&q->totalscore);
            for(i=0;i<5;i++)
            {
                fscanf(fp,"%s %d",q->d[i].subject,&q->d[i].score);
            }
            q->next=NULL;
            p->next=q;
        	p=q;
    	}
    }
	p->next=NULL;
	return head;
	fclose(fp);
    
}
void add()
{
    FILE *fp;
    struct student *head,*p,*q;
    int i;
    head=readfile();
    printf("请输入所要增添的学生信息\n");
    p=creat_node();
    q=head->next;
    while(1)
    {
        if(q->next->next==NULL)
        {
            q->next->next=p;
            p->next=NULL;
            break;
        }
    }
    if((fp=fopen("成绩管理系统.txt","at+"))==NULL)
        printf("can not open file!\n");
    else
    { 
        fprintf(fp,"%s %s",p->name,p->num);
        for(i=0;i<5;i++)
        {         
            fprintf(fp,"%s %d",p->d[i].subject,p->d[i].score);
        }
        fclose(fp);
    }   
}
void student()
{
	int j;
    system("cls");        
    printf("----***** 您当前的身份为学生 *****----\n");         
    printf("请输入您所要查询的内容：");
    printf("1.成绩\t");       
    printf("0.返回上一层\n");     
    scanf("%d",&j);        
    switch(j)
    {     
    case 1:       
        {     
            find();  
			system("pause");
			student();
			break;
        }      
    case 0:         
    	{
			main();
        }    
    }
}
void teacher()
{
	int t;
    struct student *head=NULL;
    system("cls");        
    printf("----***** 您当前的身份为管理员 *****----\n");
    printf("请输入您所要查询的内容:\n");
    printf("1.学生的成绩\n");
    printf("2.学生的排名\n");   
    printf("3.学生的偏科现象\n");
    printf("4.单科目成绩最高分与最低分\n");
    printf("0.返回\n");
    scanf("%d",&t); 
    switch(t)
    {
    case 1:	
        {		
            head=readfile();
			break;
    	}
	case 0:
		{
			main();
			break;
		}

    }
}
void administrator()
{
	int m;
    long n;
    struct student *head=NULL;
    system("cls");      
    printf("----***** 您当前的身份为管理员 *****----\n"); 
    printf("请输入您所要查询的内容:\n");
    printf("1.录入所有学生的成绩\n");
    printf("2.增添学生信息\n"); 
    printf("3.修改学生\n");
    printf("0.返回\n");
    scanf("%d",&m);
    switch(m) 
    {
    case 1:    
        {     
            printf("请输入学生的人数n:\n");        
            scanf("%ld",&n);       
            head=creat_link();       
            insert(head,n);       
            writefile(head);
			system("pause");
			administrator();
            break;
        }     
    case 2:     
    	{
            add();
			system("pause");
			administrator();
            break;
        }     
    case 3:        
        {    
            change(head); 
			system("pause");
			administrator();
            break;
        }   
    case 0:
    	{
            main();
            break;
    	}
    }      
}
void ranking(struct student *p)
{
	int cnt=1;
    struct student *head=NULL,*q;
    head=readfile();
    q=head->next;
	while(q->next!=NULL)
	{
		if(q->totalscore>p->totalscore)
		{
			cnt++;
		}
	}
	printf("\n该排名为%d",cnt);
}
int loading()
{
	int t;
	char key[5]="12345";
	char key1[5];
	printf("请输入密码:\n");
	scanf("%s",key1);
	if(strcmp(key,key1))
	{
		printf("登陆正确\n");
		t=1;
	}
	else
	{
		printf("密码错误\n");
		system("pause");
		loading();
	}
	printf("正在登陆");
	printchar('.',6,200);
	return t;     
}	
void printchar(char c,int n,int s)
{
    int i;
    for(i=0;i<n;i++)
    {
        printf("%c",c);
       // Sleep(s);
    }
}

