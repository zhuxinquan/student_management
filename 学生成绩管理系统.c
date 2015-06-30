#include<stdio.h>
#include<math.h>
#include"my_getch.h"
#include<string.h>
#include<stdlib.h>
#include"mystrcmp.h"
#include"inputkey_getch.h"
struct student
{
	char id[10];
	char name[20];
	int chinese;
	int math;
	int english;
	int physics;
	int chemistry;
	int biology;
	int sum;
	float average;
	struct student *next;
};

struct user
{
	char u[20];
	char k[20];
};

int c;      //消除缓存所用

typedef struct user us;
typedef struct student stu;
stu* _read();
stu* head;
void display_head();
stu* luru();
void save(stu*);
void insert(stu*);
void print_data(stu*);
void del(stu*);
void change(stu*);
void tongji(stu*);
stu* find(stu *);
void disp();
void sort();
void print_head();
void enter();
int login();
void enroll();



int main(void)
{
	stu* p;
	int i=0,t=0,n;		//n用来存储选择的项
    system("clear");
	enter();
	system("clear");
	head=_read();
	if(head->next==NULL)
	{
		printf("文件中无数据，请重新录入！");
		head=luru();
		save(head);
	}
	while(1)
	{
		system("clear");
		printf("\n");
		printf("\t\t           ---学生成绩管理系统---           \n");
	    printf("\t\t******************************************\n");
        printf("\t\t              1:增加学生信息                    \n");
        printf("\t\t              2:删除学生信息                    \n");
        printf("\t\t              3:查找学生信息                    \n");
        printf("\t\t              4:修改学生信息                    \n");
        printf("\t\t              5:统计学生信息                    \n");
        printf("\t\t              6:排序学生信息                    \n");
        printf("\t\t              7:显示学生信息                    \n");
        printf("\t\t              8:保存学生信息                    \n");
        printf("\t\t              9:读取学生信息                    \n"); 
        printf("\t\t              0:退出程序                        \n");
		printf("\t\t******************************************\n");
		printf("请选择(0～9):");
		scanf("%d",&n);
		switch(n)
		{
		case 1:
			system("clear");
			insert(head);
			break;
		case 2:
			system("clear");
			del(head);
			break;
		case 3:
			system("clear");
            p=find(head);
            if(!p)
            break;
            p=p->next;
            printf("\n你要查找的信息为：\n");
            print_head();
            print_data(p);
			printf("\n\n信息查找完成，按任意键返回....");
            getch1();
			mygetch();
			break;
		case 4:
			change(head);
			break;
		case 5:
			system("clear");
			tongji(head);
			break;
		case 6:
			system("clear");
			sort();
			break;
		case 7:
			system("clear");
			disp();
			break;
		case 8:
			system("clear");
			save(head);
			break;
		case 9:
			system("clear");
			head=_read();
			disp(head);
		}
		if(n==0)
			exit(0);
	}	
}

stu* _read()
{
	stu	*head,*tail;
	stu *p;
	FILE *fp;
	if((fp=fopen("s.txt","rt"))==NULL)
	{
		printf("\n\n\n...文件读取出错!任意键退出");
		mygetch();
		exit(1);
	}
	head=(stu *)malloc(sizeof(stu));
	head->next=NULL;
	tail=head;
	p=(stu *)malloc(sizeof(stu));
	while(fscanf(fp,"%s %s %d %d %d %d %d %d %d %f \n",p->id,p->name,&p->chinese,&p->math,&p->english,&p->physics,&p->chemistry,&p->biology,&p->sum,&p->average)!=EOF)	//未读到最后一个数据，则继续进行读取操作
	{
		tail->next=p;
		tail=p;
		p=(stu *)malloc(sizeof(stu));
	}
	tail->next=NULL;
	free(p);	//最后一个在循环内申请的内存不会被使用，再上一个已经到达文件尾返回EOF
	fclose(fp);
	//printf("学生信息文件读取完成！\n\n\n...按任意键返回！");
	//mygetch();
	return head;

}


stu* luru()
{
    int c;
	char m='y';	//用来判断循环条件是否继续录入成绩
	stu* p1,*p2,*head;		//此head变量将屏蔽全局变量head
	head=(stu*)malloc(sizeof(stu));
	p1=head;
	printf("请录入数据：\n");
	while(m=='y')
	{
		do{c = fgetc(stdin);}while(c!=10&&c!=EOF);		//清空输入缓存区
		p2=(stu*)malloc(sizeof(stu));
		printf("请输入学生学号：");
		do{c = fgetc(stdin);}while(c!=10&&c!=EOF);
        scanf("%s",p2->id);
		printf("请输入姓名：");
		scanf("%s",p2->name);
		printf("请输入语文成绩：");
		scanf("%d",&p2->chinese);
		printf("请输入数学成绩：");
		scanf("%d",&p2->math);
		printf("请输入英语成绩：");
		scanf("%d",&p2->english);
		printf("请输入物理成绩：");
		scanf("%d",&p2->physics);
		printf("请输入化学成绩：");
		scanf("%d",&p2->chemistry);
		printf("请输入生物成绩：");
		scanf("%d",&p2->biology);
		p2->sum=p2->chinese+p2->math+p2->english+p2->physics+p2->chemistry+p2->biology;
		p2->average=(float)((p2->sum)/6.0);
		p1->next=p2;		//此节点第一个内存数据域为空！！
		p1=p2;
		do{c = fgetc(stdin);}while(c!=10&&c!=EOF);
		printf("是否继续录入？(y/n)");
		scanf("%c",&m);
	}
	p1->next=NULL;
	return head;
}

void save(stu* head)
{
	stu *p;
	FILE *fp;
	fp=fopen("s.txt","wt");				//以at形式打开，只能在尾部添加
	if(fp==NULL)
	{
		printf("文件打开失败！\n\n\n...任意键退出!");
		mygetch();
		exit(1);
	}
	for(p=head->next;p!=NULL;p=p->next)
		fprintf(fp,"%s %s %d %d %d %d %d %d %d %f \n",p->id,p->name,p->chinese,p->math,p->english,p->physics,p->chemistry,p->biology,p->sum,p->average);
	printf("文件保存成功！\n\n\n...按任意键返回！");
	mygetch();
	fclose(fp);
}

void insert(stu* head)		//增加学生信息，即插入
{
    int c;
	stu *p1,*p2;
	p1=head;
	while(p1->next)
		p1=p1->next;
	p2=(stu*)malloc(sizeof(stu));
	printf("请输入学生学号：");
	do{c = fgetc(stdin);}while(c!=10&&c!=EOF);
	scanf("%s",p2->id);
	printf("请输入姓名：");
	scanf("%s",p2->name);
	printf("请输入语文成绩：");
	scanf("%d",&p2->chinese);
	printf("请输入数学成绩：");
	scanf("%d",&p2->math);
	printf("请输入英语成绩：");
	scanf("%d",&p2->english);
	printf("请输入物理成绩：");
	scanf("%d",&p2->physics);
	printf("请输入化学成绩：");
	scanf("%d",&p2->chemistry);
	printf("请输入生物成绩：");
	scanf("%d",&p2->biology);
	p2->sum=p2->chinese+p2->math+p2->english+p2->physics+p2->chemistry+p2->biology;
	p2->average=(float)((p2->sum)/6.0);
	p1->next=p2;
	p2->next=NULL;
	save(head);
    getchar();
}

void disp()			//显示学生信息
{
	stu* p;
    int c;
	p=head->next;
	if(!p)
	{
		printf("\n...无学生信息!");
		mygetch();
		return ;
	}
	print_head();
	while(p)
	{
		print_data(p);
		p=p->next;
	}
	printf("\n\n\n...按任意键返回！！");
	do{c = fgetc(stdin);}while(c!=10&&c!=EOF);
	getchar();
	return ;
}
void print_head()		//显示表头
{
	printf("\n				学生信息\n");
	printf("学号\t  |姓名         |语文 |数学 |英语 |物理 |化学 |生物 |总分  |平均分\n\n");
	//printf("--------------------------------------------------------------------------\n");
}

void print_data(stu *p)		//输出数据函数
{
	printf("%-10s|%-10s   | %-4d| %-4d| %-4d| %-4d| %-4d| %-4d| %-4d |%-.2f\n",p->id,p->name,p->chinese,p->math,p->english,p->physics,p->chemistry,p->biology,p->sum,p->average);
}

void del(stu* head)			//删除单条数据函数
{
    int c;
	char m;
	stu* p=NULL;
	stu* pr=NULL;
	pr=find(head);
	if(pr==NULL)
		return ;
	p=pr->next;
	printf("你要删除的学生信息为:\n");
	print_head();
	print_data(p);
	printf("\n!!!是否确认删除!!!y/n");
	do{c = fgetc(stdin);}while(c!=10&&c!=EOF);
	scanf("%c",&m);
	if(m=='y')
	{
		pr->next=p->next;
		free(p);
		printf("删除成功!");
		save(head);
		return ;
	}
	else
	{
		printf("删除取消!\n\n\n...任意键返回！！");
		return ;
	}

}
void change(stu *head)
{
    int c;
	char m;
	stu* p;
	p=find(head);
    p=p->next;
	printf("你要修改的学生信息为：\n");
	print_head();
	print_data(p);
	printf("确认修改？y/n");
	do{c = fgetc(stdin);}while(c!=10&&c!=EOF);
    scanf("%c",&m);
	if(m=='y')
	{
        printf("请输入学号：");
        scanf("%s",p->id);
		printf("请输入姓名：");
		scanf("%s",p->name);
		printf("请输入语文成绩：");
		scanf("%d",&p->chinese);
		printf("请输入数学成绩：");
		scanf("%d",&p->math);
		printf("请输入英语成绩：");
		scanf("%d",&p->english);
		printf("请输入物理成绩：");
		scanf("%d",&p->physics);
		printf("请输入化学成绩：");
		scanf("%d",&p->chemistry);
		printf("请输入生物成绩：");
		scanf("%d",&p->biology);
		p->sum=p->chinese+p->math+p->english+p->physics+p->chemistry+p->biology;
		p->average=(float)((p->sum)/6.0);
		printf("修改成功!\n\n\n...任意键返回！！");
		save(head);
		return ;
	}
	else
	{
		printf("修改取消!\n\n\n...任意键返回！！");
		return ;
	}

}
void tongji(stu *head)
{
	int count=0;
	int a,c;			//a中存储要统计的分界点数据
	int s;			//s为要统计的科目选择
	stu *p;
	printf("要统计的项目是:\n");
	printf("1.语文  2.数学  3.英语  4.物理  5.化学  6.生物  7.总分  8.平均分\n");
	printf("请选择数字(1—8):");
	scanf("%d",&s);
	printf("请输入要统计的数据范围  如：+80(80分以上)或-80(80分以下)  :");
	do{c = fgetc(stdin);}while(c!=10&&c!=EOF);
	scanf("%d",&a);
	switch(s)
	{
	case 1:
		if(a>0)
		{
			printf("\n语文%d分(含%d分)以上是：\n\n",a,a);
			for(p=head->next;;p=p->next)
			{
				if(p->chinese>=a)
				{
					if(count==0)
						print_head();
					print_data(p);
					count++;
				}
				if(p->next==NULL)
					break; 
			}
			printf("\n总计有%d个!",count);
		}
		else
		{
			printf("语文%d分(不含%d分)以下的是：\n",abs(a),abs(a));
			for(p=head->next;;p=p->next)
			{
				if(p->chinese<abs(a))
				{
					if(count==0)
						print_head();
					print_data(p);
					count++;
				}
				if(p->next==NULL)
					break; 
			}
			printf("\n\n总计有%d个!",count);
		}
		break;
	case 2:
		if(a>0)
		{
			printf("\n数学%d分(含%d分)以上是：\n\n",a,a);
			for(p=head->next;;p=p->next)
			{
				if(p->math>=a)
				{
					if(count==0)
						print_head();
					print_data(p);
					count++;
				}
				if(p->next==NULL)
					break; 
			}
			printf("\n总计有%d个!",count);
		}
		else
		{
			printf("数学%d分(不含%d分)以下的是：\n",abs(a),abs(a));
			for(p=head->next;;p=p->next)
			{
				if(p->math<abs(a))
				{
					if(count==0)
						print_head();
					print_data(p);
					count++;
				}
				if(p->next==NULL)
					break; 
			}
			printf("\n\n总计有%d个!",count);
		}
		break;
	case 3:
		if(a>0)
		{
			printf("\n英语%d分(含%d分)以上是：\n\n",a,a);
			for(p=head->next;;p=p->next)
			{
				if(p->english>=a)
				{
					if(count==0)
						print_head();
					print_data(p);
					count++;
				}
				if(p->next==NULL)
					break; 
			}
			printf("\n总计有%d个!",count);
		}
		else
		{
			printf("英语%d分(不含%d分)以下的是：\n",abs(a),abs(a));
			for(p=head->next;;p=p->next)
			{
				if(p->english<abs(a))
				{
					if(count==0)
						print_head();
					print_data(p);
					count++;
				}
				if(p->next==NULL)
					break; 
			}
			printf("\n\n总计有%d个!",count);
		}
		break;
	case 4:
		if(a>0)
		{
			printf("\n物理%d分(含%d分)以上是：\n\n",a,a);
			for(p=head->next;;p=p->next)
			{
				if(p->physics>=a)
				{
					if(count==0)
						print_head();
					print_data(p);
					count++;
				}
				if(p->next==NULL)
					break; 
			}
			printf("\n总计有%d个!",count);
		}
		else
		{
			printf("\n物理%d分(不含%d分)以下的是：\n",abs(a),abs(a));
			for(p=head->next;;p=p->next)
			{
				if(p->physics<abs(a))
				{
					if(count==0)
						print_head();
					print_data(p);
					count++;
				}
				if(p->next==NULL)
					break; 
			}
			printf("\n\n总计有%d个!",count);
		}
		break;
	case 5:
		if(a>0)
		{
			printf("\n化学%d分(含%d分)以上是：\n\n",a,a);
			for(p=head->next;;p=p->next)
			{
				if(p->chemistry>=a)
				{
					if(count==0)
						print_head();
					print_data(p);
					count++;
				}
				if(p->next==NULL)
					break; 
			}
			printf("\n总计有%d个!",count);
		}
		else
		{
			printf("\n化学%d分(不含%d分)以下的是：\n",abs(a),abs(a));
			for(p=head->next;;p=p->next)
			{
				if(p->chemistry<abs(a))
				{
					if(count==0)
						print_head();
					print_data(p);
					count++;
				}
				if(p->next==NULL)
					break; 
			}
			printf("\n\n总计有%d个!",count);
		}
		break;
	case 6:
		if(a>0)
		{
			printf("\n生物%d分(含%d分)以上是：\n\n",a,a);
			for(p=head->next;;p=p->next)
			{
				if(p->biology>=a)
				{
					if(count==0)
						print_head();
					print_data(p);
					count++;
				}
				if(p->next==NULL)
					break; 
			}
			printf("\n总计有%d个!",count);
		}
		else
		{
			printf("\n生物%d分(不含%d分)以下的是：\n",abs(a),abs(a));
			for(p=head->next;;p=p->next)
			{
				if(p->biology<abs(a))
				{
					if(count==0)
						print_head();
					print_data(p);
					count++;
				}
				if(p->next==NULL)
					break; 
			}
			printf("\n\n总计有%d个!",count);
		}
		break;
	case 7:
		if(a>0)
		{
			printf("\n总分%d分(含%d分)以上是：\n\n",a,a);
			for(p=head->next;;p=p->next)
			{
				if(p->sum>=a)
				{
					if(count==0)
						print_head();
					print_data(p);
					count++;
				}
				if(p->next==NULL)
					break; 
			}
			printf("\n总计有%d个!",count);
		}
		else
		{
			printf("\n总分%d分(不含%d分)以下的是：\n",abs(a),abs(a));
			for(p=head->next;;p=p->next)
			{
				if(p->sum<abs(a))
				{
					if(count==0)
						print_head();
					print_data(p);
					count++;
				}
				if(p->next==NULL)
					break; 
			}
			printf("\n\n总计有%d个!",count);
		}
		break;
	case 8:
		if(a>0)
		{
			printf("\n平均分%d分(含%d分)以上是：\n\n",a,a);
			for(p=head->next;;p=p->next)
			{
				if(p->average>=(float)a)
				{
					if(count==0)
						print_head();
					print_data(p);
					count++;
				}
				if(p->next==NULL)
					break; 
			}
			printf("\n总计有%d个!",count);
		}
		else
		{
			printf("\n平均分%d分(不含%d分)以下的是：\n",abs(a),abs(a));
			for(p=head->next;;p=p->next)
			{
				if(p->average<(float)abs(a))
				{
					if(count==0)
						print_head();
					print_data(p);
					count++;
				}
				if(p->next==NULL)
					break; 
			}
			printf("\n\n总计有%d个!",count);
		}
		break;
	}
	printf("\n\n\n...按任意键返回!");
    do{c = fgetc(stdin);}while(c!=10&&c!=EOF);
	mygetch();
}
stu* find(stu *head)					//返回所找数据的 ！！！前一个指针
{
	stu* p=NULL;
	stu* t=NULL;
	char id[10];
	char name[20];
	int select,c;
	int re,i,j,k,re1;
	while(1)
	{
		printf("\n\n请选择查找学生方式:\n");
		printf("\n  1.学号查找\t\t\t  2.姓名查找\n\n  3.学号+姓名\t\t\t  4.学号模糊查找\n\n  5.姓名模糊查找\t\t  6.取消查找\n\n 请选择：");
		scanf("%d",&select);
		switch(select)
		{
		case 1:
			printf("\n请输入学生学号：");
			do{c = fgetc(stdin);}while(c!=10&&c!=EOF);
			scanf("%s",id);
			for(p=head;;p=p->next)
			{
				if(!strcmp(p->next->id,id))
				{
					return p;
					break;
				}
				else if(!(p->next->next))
				{
					printf("\n该学生不存在!!!\n\n..");
					mygetch();
					break;
				}
			}
			break;
		case 2:
			printf("\n请输入学生姓名：");
			do{c = fgetc(stdin);}while(c!=10&&c!=EOF);
			scanf("%s",name);
			for(p=head;;p=p->next)
			{
				if(!strcmp(p->next->name,name))
				{
					return p;
					break;
				}
				else if(!(p->next->next))
				{
					printf("\n该学生不存在!!!\n\n..");
					mygetch();
					break;
				}
			}
			break;
		case 3:
			printf("\n请输入学生学号：");
			do{c = fgetc(stdin);}while(c!=10&&c!=EOF);
			scanf("%s",id);
			printf("\n请输入学生姓名：");
			do{c = fgetc(stdin);}while(c!=10&&c!=EOF);
			scanf("%s",name);
			for(p=head;;p=p->next)
			{
				if(!(strcmp(p->next->name,name)||strcmp(p->next->id,id)))
				{
					return p;
					break;
				}
				else if(!(p->next->next))
				{
					printf("\n该学生不存在!!!\n\n..");
					mygetch();
					break;
				}
			}
		case 4:
			while(1)
			{
				printf("\n请输入学生学号：");
				do{c = fgetc(stdin);}while(c!=10&&c!=EOF);
				scanf("%s",id);
				if(strlen(id)==0)
					continue;
				p=head;
				t=head->next;
                re1=0;
				for(p=head;;p=p->next)
				{
                    re=0;
                    i=strlen(p->next->id);
                    j=strlen(id);
                    for(k=0;k<i;k++)
                    {
                        if((p->next->id[k])==id[re])
                        {
                            re++;
                        }
                    }
                    if(re1<re)
                    {
                        re1=re;
                        t=p;
                    }
                    if(!(p->next->next))
                    {
                        return t;
                    }
				}
			}
			break;
		case 5:
			while(1)
			{
				printf("\n请输入学生姓名：");
				do{c = fgetc(stdin);}while(c!=10&&c!=EOF);
                scanf("%s",name);
				if(strlen(name)==0)
					continue;
				p=head;
				t=head->next;
                re1=0;
				for(p=head;;p=p->next)
				{
                    re=0;
                    i=strlen(p->next->name);
                    j=strlen(name);
                    for(k=0;k<i;k++)
                    {
                        
                        if((p->next->name[k])==name[re])
                        {
                            re++;
                        }
                    }
                    if(re1<re)
                    {
                        re1=re;
                        t=p;
                    }
                    if(!(p->next->next))
                    {
                        return t;
                    }
				}
			}
			break;
		case 6:
			return NULL;
			break;
		default:
			continue;
		}
	}
}
void sort()			//学生排序
{

	stu* p=NULL;
	stu* p1=NULL;
	int x;
	stu* r;
	stu* t;
	int score;
	printf("按什么排序？\n");
	printf("1.语文  2.数学  3.英语  4.物理  5.化学  6.生物  7.总分\n");
	printf("请选择数字(1—7):");
	scanf("%d",&x);	
	t=(stu*)malloc(sizeof(stu));
	switch(x)
	{
	case 1:
		for(p=head->next;;p=p->next)
		{
			
			score=p->chinese;
			for(p1=p->next;;p1=p1->next)
			{
			
				if(score<p1->chinese)	
				{
					score=p1->chinese;
					*t=*p1;
					*p1=*p;
					*p=*t;
					r=p->next;
					p->next=p1->next;
					p1->next=r;
				}
				if(!p1->next)
					break;
			}

			if(p->next->next==NULL)
				break;
		}
		free(t);
		disp();
		save(head);
		break;
	case 2:
		for(p=head->next;;p=p->next)
		{
			score=p->math;
			for(p1=p->next;;p1=p1->next)
			{
			
				if(score<p1->math)	
				{
					score=p1->math;
					*t=*p1;
					*p1=*p;
					*p=*t;
					r=p->next;
					p->next=p1->next;
					p1->next=r;
				}
				if(!p1->next)
					break;
			}
	
			if(p->next->next==NULL)
				break;
		}
		free(t);
		disp();
		save(head);
		break;
	case 3:
		for(p=head->next;;p=p->next)
		{
			score=p->english;
			for(p1=p->next;;p1=p1->next)
			{
			
				if(score<p1->english)	
				{
					score=p1->english;
					*t=*p1;
					*p1=*p;
					*p=*t;
					r=p->next;
					p->next=p1->next;
					p1->next=r;
				}
				if(!p1->next)
					break;
			}
	
			if(p->next->next==NULL)
				break;
		}
		free(t);
		disp();
		save(head);
		break;
	case 4:
		for(p=head->next;;p=p->next)
		{
			
			score=p->physics;
			for(p1=p->next;;p1=p1->next)
			{
			
				if(score<p1->physics)	
				{
					score=p1->physics;
					*t=*p1;
					*p1=*p;
					*p=*t;
					r=p->next;
					p->next=p1->next;
					p1->next=r;
				}
				if(!p1->next)
					break;
			}
	
			if(p->next->next==NULL)
				break;
		}
		free(t);
		disp();
		save(head);
		break;
	case 5:
		for(p=head->next;;p=p->next)
		{
			
			score=p->chemistry;
			for(p1=p->next;;p1=p1->next)
			{
			
				if(score<p1->chemistry)	
				{
					score=p1->chemistry;
					*t=*p1;
					*p1=*p;
					*p=*t;
					r=p->next;
					p->next=p1->next;
					p1->next=r;
				}
				if(!p1->next)
					break;
			}
	
			if(p->next->next==NULL)
				break;
		}
		free(t);
		disp();
		save(head);
		break;
	case 6:
		for(p=head->next;;p=p->next)
		{
			
			score=p->biology;
			for(p1=p->next;;p1=p1->next)
			{
			
				if(score<p1->biology)	
				{
					score=p1->biology;
					*t=*p1;
					*p1=*p;
					*p=*t;
					r=p->next;
					p->next=p1->next;
					p1->next=r;
				}
				if(!p1->next)
					break;
			}
	
			if(p->next->next==NULL)
				break;
		}
		free(t);
		disp();
		save(head);
		break;
	case 7:
		for(p=head->next;;p=p->next)
		{
			
			score=p->sum;
			for(p1=p->next;;p1=p1->next)
			{
				if(score<p1->sum)	
				{
					score=p1->sum;
					*t=*p1;
					*p1=*p;
					*p=*t;
					r=p->next;
					p->next=p1->next;
					p1->next=r;
				}
				if(!p1->next)
					break;
			}
	
			if(p->next->next==NULL)
				break;
		}
		free(t);
		disp();
		save(head);
		break;
	}
	mygetch();
}



void enter()
{
	int n=0;
	int s;
	while(1)
	{
		printf("\n\n\t\t    ************学生管理系统***********");
		printf("\n\n\t\t\t1.登陆\t2.注册\n\n\t\t\t请选择：");
		scanf("%d",&s);
		if(s==1)
		{
			if(1==login())			//登陆返回1用户未找到
			{
				continue;
			}
			else
				return;
		}
		else
		{	
			enroll();	//注册
			break;
		}
	}
}


int login()				//登陆
{
	char u[20];
	char k[20];
	us p;
	int fc,i,n = 0;
	FILE *fp;
	printf("\n\t\t\t请输入用户名：");
	scanf("%s",u);
	if((fp=fopen("user.txt","rt"))==NULL)		
	{
		printf("\n\n\n...用户文件读取出错!任意键退出");
		mygetch();
		exit(1);
	}
	while(1)
	{	
		fc=fscanf(fp,"%s %s\n",p.u,p.k);
		for(i=0;i<(int)strlen(p.k);i++)
		{
			p.k[i]=p.k[i]-20;
		}
		while(1)
		{
			if(!strcmp(p.u,u))
			{
                do{c = fgetc(stdin);}while(c!=10&&c!=EOF);
				printf("\n\t\t\t请输入密码：");
				n++;
				/*do{c = fgetc(stdin);}while(c!=10&&c!=EOF);
				for(i=0;i<10;i++)			//此循环用来显示密文密码
				{
                    printf("...");
                    do{c = fgetc(stdin);}while(c!=10&&c!=EOF);
					k[i]=mygetch();
					if((k[i]!=10)&&(k[i]!=13))
						printf("*");
					else
						break;
				}
                k[i]='\0';*/
                inputkey(k);
                // scanf("%s",k);
				if(strcmp(p.k,k))
				{
					if(n>2)
					{
						printf("\n\t\t密码输入错误三次！！！\n\n\n");
						exit(0);
					}
					printf("\n\t\t密码输入错误！！请重新输入...");
					continue;
				}
				else
					return 0;
			}
			else
				break;
		}
		if(fc==EOF)
		{
			printf("\n\t\t\t用户未找到....\n");
			fclose(fp);
			return 1;
		}	
	}
	
}

void enroll()				//注册
{
	int i;
	char u[20];
	char k[20];
	char k1[20];
	FILE *fp;
		if((fp=fopen("user.txt","at"))==NULL)
		{
			printf("\n\t\t文件打开失败！\n\n任意键退出...");
			mygetch();
			exit(0);
		}
		printf("\n\t\t\t请输入用户名：");
		do{c = fgetc(stdin);}while(c!=10&&c!=EOF);
		scanf("%s",u);
		while(1)
		{
			printf("\n\t\t\t请输入密码：");
			do{c = fgetc(stdin);}while(c!=10&&c!=EOF);
			/*for(i=0;i<20;i++)			//此循环用来显示密文密码
			{
				do{c = fgetc(stdin);}while(c!=10&&c!=EOF);
				k[i]=mygetch();
				if(k[i]!='\r')
					printf("*");
				else
					break;
			}
			k[i]='\0';*/
            //scanf("%s",k);
            inputkey(k);
			printf("\n\t\t\t请再次输入密码：");
			/*for(i=0;i<20;i++)			
			{
				k1[i]=mygetch();
				if(k1[i]!='\r')
					printf("*");
				else
					break;
			}
			k1[i]='\0';*/
            //scanf("%s",k1);
            inputkey(k1);
			if(strcmp(k,k1))
			{
				printf("\n\t\t\t两次输入密码不相同，请重新设定\n");
				continue;
			}
			else
				break;
		}
		for(i=0;i<(int)strlen(k);i++)
		{
			k[i]=k[i]+20;
		}
		if(fprintf(fp,"%s %s\n",u,k)==EOF)
		{
			printf("\n\t\t用户文件写入出错！\n\n\n按任意键退出....");
			mygetch();
			exit(0);
		}
		printf("\n\t\t\t注册完成，请重新登陆...");
		fclose(fp);
		mygetch();
		enter();
}
