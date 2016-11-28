#include "worker.h"


char filename[20]="";                          /*文件名*/
FILE *fp=NULL;               

int main(int argc,char **argv)                                 /*主函数*/
{
	int m;
	printf("欢迎使用职工信息管理系统: ");
	printf("\n\n添加，请按1");
	printf("\n查找，请按2");
	printf("\n修改，请按3");
	printf("\n删除，请按4");
	printf("\n输出，请按5");
	printf("\n其他，请按6");
	printf("\n退出，请按0\n"); 
	printf("请输入你的选择: ");                 /*输出提示信息*/
	scanf("%d",&m);
	while(m>0&&m<=6){
		//使用文件处理
		switch(m)
		{
		case 1: append();
			break;
		case 2: search();
			break;
		case 3: modify();
			break;
		case 4: delwork();
			break;
		case 5: output();
			break;
		case 6: else_test();
			break;
		}
		printf("\n\n添加，请按1");
		printf("\n查找，请按2");
		printf("\n修改，请按3");
		printf("\n删除，请按4");
		printf("\n输出，请按5");
		printf("\n退出，请按0\n"); 
		printf("请再次输入你的选择: ");  
		scanf("%d",&m);
	}
	if(0==m){
		printf("选择退出...\n");
	}else if(6<m){
		printf("输入的数字不在选择范围内，退出...\n");
	}else
		printf("输入非数字，退出...\n");
	printf("运行结束...\n");  
	return 1;
}

void append()
{
	worker one;
	char en[2];

	memset(en,'\0',sizeof(en));

	printf("\n请输入文件名：");
	scanf("%s",filename);                   /*创建一个文件的名字*/
	if((fp=fopen(filename,"at+"))==NULL)      /*打开文件，实现向文件输入数据*/
	{
		printf("\n文件不能建立！");
		return;
	}
	if(serachname(filename)){
		fprintf(fp,"%-15s|%-10s|%-10s|%-10s|%-10s|%-15s|%-10s|%-15s|%-50s\n","姓名","工号","性别","年龄","学历","职位","工资","电话号码","住址");
	}
	printf("\n请输入职工信息（以0结束）: \n");

	while(strcmp(en,"0"))
	{
		printf("姓名: ");
		scanf("%s",one.name);
		printf("工号: ");
		scanf("%s",one.num);
		printf("性别: ");
		scanf("%s",one.sex);
		printf("年龄: ");
		scanf("%s",one.age);
		printf("学历: ");
		scanf("%s",one.record);
		printf("职位: ");
		scanf("%s",one.position);
		printf("工资: ");
		scanf("%s",one.wanges);
		printf("电话: ");
		scanf("%s",one.tel);
		printf("住址: ");
		scanf("%s",one.addr);                    /*输出职工的相关信息*/
		fprintf(fp,"%-15s|%-10s|%-10s|%-10s|%-10s|%-15s|%-10s|%-15s|%-50s\n",one.name,one.num,one.sex,one.age,one.record,one.position,one.wanges,one.tel,one.addr);

		printf("是否继续输入职工信息: ");
		scanf("%s",en);
	}
	fclose(fp);                              /*关闭文件*/
	printf("添加结束...\n");
}

void output()                            /*输出函数*/
{
	worker one;

	printf("\n请输入文件名：");
	scanf("%s",filename);

	if((fp=fopen(filename,"rb"))==NULL)        /*打开文件*/
	{
		printf("\n不能打开文件！");
		return;
	}

	printf("\n%20s\n","职工信息管理系统");/*向文件输入数据*/
	while(!feof(fp))
	{
		fscanf(fp,"%s%s%s%s%s%s%s%s%s\n",one.name,one.num,one.sex,one.age,one.record,one.position,one.wanges,one.tel,one.addr);
		printf("%-15s%-10s%-10s%-10s%-10s%-15s%-10s%-15s%-50s\n",one.name,one.num,one.sex,one.age,one.record,one.position,one.wanges,one.tel,one.addr);
	}
	fclose(fp);/*关闭文件*/
	printf("输出结束...\n");
}

void search()                     /*查询函数*/
{
	int k=0;
	char namekey[15];
	worker one,rel;
	printf("\n请输入文件名：");
	scanf("%s",filename);

	if((fp=fopen(filename,"rb"))==NULL)        /*打开文件*/
	{
		printf("\n不能打开文件！");
		return;
	}

	printf("\n请输入您要查找的职工姓名:");
	scanf("%s",namekey);

	while(!feof(fp))
	{
		fscanf(fp,"%s%s%s%s%s%s%s%s%s\n",one.name,one.num,one.sex,one.age,one.record,one.position,one.wanges,one.tel,one.addr);
		if(!strcmp(namekey,one.name))
		{
			printf("\n已查到，记录为：");
			printf("\n%-15s%-10s%-10s%-10s%-10s%-15s%-10s%-15s%-50s\n",one.name,one.num,one.sex,one.age,one.record,one.position,one.wanges,one.tel,one.addr);
			k=1;
		}
	}
	if(!k)
		printf("\n对不起，查无此人！\n");
	fclose(fp);
	printf("查询结束...\n");
}

void modify()                          /*修改函数*/
{
	int k=0;
	long offset;
	char namekey[15];
	char numid[10];
	struct staff one;
	printf("\n请输入文件名：");
	scanf("%s",filename);

	if((fp=fopen(filename,"r+"))==NULL)        /*打开文件*/
	{
		printf("\n不能打开文件！");
		return;
	}
	printf("\n请输入您要查找的职工姓名:");
	scanf("%s",namekey);
	while(!feof(fp))
	{
		offset=ftell(fp);                     /*查找信息*/
		fscanf(fp,"%s%s%s%s%s%s%s%s%s\n",one.name,one.num,one.sex,one.age,one.record,one.position,one.wanges,one.tel,one.addr);
		if(!strcmp(namekey,one.name))
		{
			k=1;
		}
	}
	if(k)
	{
		printf("\n已查到，记录为：");
		printf("\n%-15s%-10s%-10s%-10s%-10s%-15s%-10s%-15s%-50s\n",one.name,one.num,one.sex,one.age,one.record,one.position,one.wanges,one.tel,one.addr);
		printf("\n请输入信息(按照姓名、工号、性别、年龄、学历、职位、工资、电话、地址的顺序输入,输入一个回车一次)：");
		scanf("%s%s%s%s%s%s%s%s%s",one.name,one.num,one.sex,one.age,one.record,one.position,one.wanges,one.tel,one.addr);
		fseek(fp,offset,SEEK_SET);
		printf("%ld",ftell(fp));
		fprintf(fp,"%-15s|%-10s|%-10s|%-10s|%-10s|%-15s|%-10s|%-15s|%-50s\n",one.name,one.num,one.sex,one.age,one.record,one.position,one.wanges,one.tel,one.addr);
	}
	else
		printf("\n对不起，查无此人,无法进行修改。\n");
	fclose(fp);                            /*文件关闭*/

	printf("修改结束...\n");
}

void delwork()                          /*删除函数*/
{
	int m,k=0;
	long offset1;
	char namekey[15];
	struct staff one;
	
	printf("\n请输入文件名：");
	scanf("%s",filename);

	if((fp=fopen(filename,"r+"))==NULL)        /*打开文件*/
	{
		printf("\n不能打开文件！");
		return;
	}

	printf("\n请输入您要查找的职工姓名:");
	scanf("%s",namekey);

	while(!feof(fp))
	{
		offset1=ftell(fp);               /*查询文件中相关的信息*/
		fscanf(fp,"%s%s%s%s%s%s%s%s%s\n",one.name,one.num,one.sex,one.age,one.record,one.position,one.wanges,one.tel,one.addr);
		if(!strcmp(namekey,one.name))
		{
			k=1;
		}
	}
	if(k)
	{
		printf("\n已查到，记录为");
		printf("\n%-15s%-10s%-10s%-10s%-10s%-15s%-10s%-15s%-50s\n",one.name,one.num,one.sex,one.age,one.record,one.position,one.wanges,one.tel,one.addr);
		printf("\n确实要删除,按1；不删除，按0：");
		scanf("%d",&m);
		if(m)
		{
			fseek(fp,offset1,SEEK_SET);
			fprintf(fp,"%-15s%-10s%-10s%-10s%-10s%-15s%-10s%-15s%-50s\n","","","","","","","","","");
		}
	}
	else
		printf("\n对不起，查无此人。\n");
	fclose(fp);                       /*关闭文件*/

	printf("删除结束...\n");
}


int serachname(char filename[20]){
	long offset;
	FILE *fp=NULL;
	struct staff one;
	if((fp=fopen(filename,"r+"))==NULL){
		printf("新创建文件...\n");
		return -1;
	}
	while(!feof(fp)){
		offset=ftell(fp);
		fscanf(fp,"%s%s%s%s%s%s%s%s%s\n",one.name,one.num,one.sex,one.age,one.record,one.position,one.wanges,one.tel,one.addr);
		if(strcmp(one.name,"姓名")){
			return 0;
		}
	}
	fclose(fp);
	return 1;
}

