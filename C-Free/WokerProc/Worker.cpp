#include "worker.h"


char filename[20]="";                          /*�ļ���*/
FILE *fp=NULL;               

int main(int argc,char **argv)                                 /*������*/
{
	int m;
	printf("��ӭʹ��ְ����Ϣ����ϵͳ: ");
	printf("\n\n��ӣ��밴1");
	printf("\n���ң��밴2");
	printf("\n�޸ģ��밴3");
	printf("\nɾ�����밴4");
	printf("\n������밴5");
	printf("\n�������밴6");
	printf("\n�˳����밴0\n"); 
	printf("���������ѡ��: ");                 /*�����ʾ��Ϣ*/
	scanf("%d",&m);
	while(m>0&&m<=6){
		//ʹ���ļ�����
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
		printf("\n\n��ӣ��밴1");
		printf("\n���ң��밴2");
		printf("\n�޸ģ��밴3");
		printf("\nɾ�����밴4");
		printf("\n������밴5");
		printf("\n�˳����밴0\n"); 
		printf("���ٴ��������ѡ��: ");  
		scanf("%d",&m);
	}
	if(0==m){
		printf("ѡ���˳�...\n");
	}else if(6<m){
		printf("��������ֲ���ѡ��Χ�ڣ��˳�...\n");
	}else
		printf("��������֣��˳�...\n");
	printf("���н���...\n");  
	return 1;
}

void append()
{
	worker one;
	char en[2];

	memset(en,'\0',sizeof(en));

	printf("\n�������ļ�����");
	scanf("%s",filename);                   /*����һ���ļ�������*/
	if((fp=fopen(filename,"at+"))==NULL)      /*���ļ���ʵ�����ļ���������*/
	{
		printf("\n�ļ����ܽ�����");
		return;
	}
	if(serachname(filename)){
		fprintf(fp,"%-15s|%-10s|%-10s|%-10s|%-10s|%-15s|%-10s|%-15s|%-50s\n","����","����","�Ա�","����","ѧ��","ְλ","����","�绰����","סַ");
	}
	printf("\n������ְ����Ϣ����0������: \n");

	while(strcmp(en,"0"))
	{
		printf("����: ");
		scanf("%s",one.name);
		printf("����: ");
		scanf("%s",one.num);
		printf("�Ա�: ");
		scanf("%s",one.sex);
		printf("����: ");
		scanf("%s",one.age);
		printf("ѧ��: ");
		scanf("%s",one.record);
		printf("ְλ: ");
		scanf("%s",one.position);
		printf("����: ");
		scanf("%s",one.wanges);
		printf("�绰: ");
		scanf("%s",one.tel);
		printf("סַ: ");
		scanf("%s",one.addr);                    /*���ְ���������Ϣ*/
		fprintf(fp,"%-15s|%-10s|%-10s|%-10s|%-10s|%-15s|%-10s|%-15s|%-50s\n",one.name,one.num,one.sex,one.age,one.record,one.position,one.wanges,one.tel,one.addr);

		printf("�Ƿ��������ְ����Ϣ: ");
		scanf("%s",en);
	}
	fclose(fp);                              /*�ر��ļ�*/
	printf("��ӽ���...\n");
}

void output()                            /*�������*/
{
	worker one;

	printf("\n�������ļ�����");
	scanf("%s",filename);

	if((fp=fopen(filename,"rb"))==NULL)        /*���ļ�*/
	{
		printf("\n���ܴ��ļ���");
		return;
	}

	printf("\n%20s\n","ְ����Ϣ����ϵͳ");/*���ļ���������*/
	while(!feof(fp))
	{
		fscanf(fp,"%s%s%s%s%s%s%s%s%s\n",one.name,one.num,one.sex,one.age,one.record,one.position,one.wanges,one.tel,one.addr);
		printf("%-15s%-10s%-10s%-10s%-10s%-15s%-10s%-15s%-50s\n",one.name,one.num,one.sex,one.age,one.record,one.position,one.wanges,one.tel,one.addr);
	}
	fclose(fp);/*�ر��ļ�*/
	printf("�������...\n");
}

void search()                     /*��ѯ����*/
{
	int k=0;
	char namekey[15];
	worker one,rel;
	printf("\n�������ļ�����");
	scanf("%s",filename);

	if((fp=fopen(filename,"rb"))==NULL)        /*���ļ�*/
	{
		printf("\n���ܴ��ļ���");
		return;
	}

	printf("\n��������Ҫ���ҵ�ְ������:");
	scanf("%s",namekey);

	while(!feof(fp))
	{
		fscanf(fp,"%s%s%s%s%s%s%s%s%s\n",one.name,one.num,one.sex,one.age,one.record,one.position,one.wanges,one.tel,one.addr);
		if(!strcmp(namekey,one.name))
		{
			printf("\n�Ѳ鵽����¼Ϊ��");
			printf("\n%-15s%-10s%-10s%-10s%-10s%-15s%-10s%-15s%-50s\n",one.name,one.num,one.sex,one.age,one.record,one.position,one.wanges,one.tel,one.addr);
			k=1;
		}
	}
	if(!k)
		printf("\n�Բ��𣬲��޴��ˣ�\n");
	fclose(fp);
	printf("��ѯ����...\n");
}

void modify()                          /*�޸ĺ���*/
{
	int k=0;
	long offset;
	char namekey[15];
	char numid[10];
	struct staff one;
	printf("\n�������ļ�����");
	scanf("%s",filename);

	if((fp=fopen(filename,"r+"))==NULL)        /*���ļ�*/
	{
		printf("\n���ܴ��ļ���");
		return;
	}
	printf("\n��������Ҫ���ҵ�ְ������:");
	scanf("%s",namekey);
	while(!feof(fp))
	{
		offset=ftell(fp);                     /*������Ϣ*/
		fscanf(fp,"%s%s%s%s%s%s%s%s%s\n",one.name,one.num,one.sex,one.age,one.record,one.position,one.wanges,one.tel,one.addr);
		if(!strcmp(namekey,one.name))
		{
			k=1;
		}
	}
	if(k)
	{
		printf("\n�Ѳ鵽����¼Ϊ��");
		printf("\n%-15s%-10s%-10s%-10s%-10s%-15s%-10s%-15s%-50s\n",one.name,one.num,one.sex,one.age,one.record,one.position,one.wanges,one.tel,one.addr);
		printf("\n��������Ϣ(�������������š��Ա����䡢ѧ����ְλ�����ʡ��绰����ַ��˳������,����һ���س�һ��)��");
		scanf("%s%s%s%s%s%s%s%s%s",one.name,one.num,one.sex,one.age,one.record,one.position,one.wanges,one.tel,one.addr);
		fseek(fp,offset,SEEK_SET);
		printf("%ld",ftell(fp));
		fprintf(fp,"%-15s|%-10s|%-10s|%-10s|%-10s|%-15s|%-10s|%-15s|%-50s\n",one.name,one.num,one.sex,one.age,one.record,one.position,one.wanges,one.tel,one.addr);
	}
	else
		printf("\n�Բ��𣬲��޴���,�޷������޸ġ�\n");
	fclose(fp);                            /*�ļ��ر�*/

	printf("�޸Ľ���...\n");
}

void delwork()                          /*ɾ������*/
{
	int m,k=0;
	long offset1;
	char namekey[15];
	struct staff one;
	
	printf("\n�������ļ�����");
	scanf("%s",filename);

	if((fp=fopen(filename,"r+"))==NULL)        /*���ļ�*/
	{
		printf("\n���ܴ��ļ���");
		return;
	}

	printf("\n��������Ҫ���ҵ�ְ������:");
	scanf("%s",namekey);

	while(!feof(fp))
	{
		offset1=ftell(fp);               /*��ѯ�ļ�����ص���Ϣ*/
		fscanf(fp,"%s%s%s%s%s%s%s%s%s\n",one.name,one.num,one.sex,one.age,one.record,one.position,one.wanges,one.tel,one.addr);
		if(!strcmp(namekey,one.name))
		{
			k=1;
		}
	}
	if(k)
	{
		printf("\n�Ѳ鵽����¼Ϊ");
		printf("\n%-15s%-10s%-10s%-10s%-10s%-15s%-10s%-15s%-50s\n",one.name,one.num,one.sex,one.age,one.record,one.position,one.wanges,one.tel,one.addr);
		printf("\nȷʵҪɾ��,��1����ɾ������0��");
		scanf("%d",&m);
		if(m)
		{
			fseek(fp,offset1,SEEK_SET);
			fprintf(fp,"%-15s%-10s%-10s%-10s%-10s%-15s%-10s%-15s%-50s\n","","","","","","","","","");
		}
	}
	else
		printf("\n�Բ��𣬲��޴��ˡ�\n");
	fclose(fp);                       /*�ر��ļ�*/

	printf("ɾ������...\n");
}


int serachname(char filename[20]){
	long offset;
	FILE *fp=NULL;
	struct staff one;
	if((fp=fopen(filename,"r+"))==NULL){
		printf("�´����ļ�...\n");
		return -1;
	}
	while(!feof(fp)){
		offset=ftell(fp);
		fscanf(fp,"%s%s%s%s%s%s%s%s%s\n",one.name,one.num,one.sex,one.age,one.record,one.position,one.wanges,one.tel,one.addr);
		if(strcmp(one.name,"����")){
			return 0;
		}
	}
	fclose(fp);
	return 1;
}

