#include<stdio.h>
#define MAXSIZE 30
typedef struct good{
	int n;           //商品编号
	char name[20];   //名称
	char model[10] ; //型号
	int  c;          //类别
	double price;    //价格
	int num;         //库存数量
	
}good;

static int last;

void init(){
	last=0;
}
void setUp(good *g){        //信息录入

	int a;
	int i;
	int j;
	init();
	printf("请输入要录入的信息数量：");
	scanf("%d",&a);
	for(i=0;i<a;i++){
wen:	printf("输入第%d个商品信息\n",i+1);
		printf("输入编号：");
		scanf("%d",&g[i].n);
		for(j=0;j<i;j++)
		{
			if(g[i].n==g[j].n )
			{
				printf("编号重复，请重新输入\n");
				goto wen;
			}
		}
		printf("输入商品名称:");
		scanf("%s",g[i].name);
		printf("输入型号:");
		scanf("%s",g[i].model);
		printf("输入类别：");
		scanf("%d",&g[i].c);
		printf("输入价格:");
		scanf("%lf",&g[i].price );
		printf("输入库存数量：");
		scanf("%d",&g[i].num);
		last++;
	}
}

void insert(good *g)     //添加商品信息
{
	int a;
	int k;
	int j;
	int i;
	printf("请输入要添加的商品数量：");
	scanf("%d",&a);
	for(k=0;k<a;k++)
	{
		i=last;
		wen:	printf("输入第%d个商品信息\n",i+1);
		printf("输入编号：");
		scanf("%d",&g[i].n);
		for(j=0;j<i;j++)
		{
			if(g[i].n==g[j].n )
			{
				printf("编号重复，请重新输入\n");
				goto wen;
			}
		}
		printf("输入商品名称:");
		scanf("%s",g[i].name);
		printf("输入型号:");
		scanf("%s",g[i].model);
		printf("输入类别：");
		scanf("%d",&g[i].c);
		printf("输入价格:");
		scanf("%lf",&g[i].price );
		printf("输入库存数量：");
		scanf("%d",&g[i].num);
		last++;
	}
}

void change(good *g)   //修改商品信息
{
	int a;
	int k;
	int j;
	printf("输入要修改的商品编号：");
	scanf("%d",&a);
	for(k=0;k<last;k++)
	{
		if(g[k].n==a)
		{
           wen:	printf("请重新输入编号：");
			scanf("%d",&g[k].n);
			for(j=0;j<k;j++)
			{
				if(g[k].n==g[j].n )
					goto wen;
			}
			printf("请输入名称");
			scanf("%s",g[k].name);
			printf("请输入型号：");
			scanf("%s",g[k].model);
			printf("请输入类别:");
			scanf("%d",&g[k].c );
			printf("请输入价格：");
			scanf("%lf",&g[k].price );
			printf("请输入库存数量：");
			scanf("%d",&g[k].num );
		}
	}
}

void save(good *g){       //保存
	FILE *fp;
	int i;
	if((fp=fopen("good.dat","wb"))==NULL)
	{
		printf("cannot open file\n");
		return ;
	}
	for(i=0;i<last;i++){
		if(fwrite(&g[i],sizeof(good),1,fp)!=1)
			printf("file write error\n");
	}
	
	fclose(fp);
	fp=fopen("last.dat","wb");
	fprintf(fp,"%d",last);
	fclose(fp);
	printf("保存成功!");
}

void read(good *g)    //读取
{
	FILE *fp;
	int i;
	if((fp=fopen("good.dat","rb"))==NULL)
	{
		printf("cannot open file\n");
		exit(0);
	}
	for(i=0;i<last;i++)
	{
		if((fread(&g[i],sizeof(good),1,fp))!=1)
		{
			printf("file read error\n");
		    return ;
		}
	}
	fclose(fp);
	if((fp=fopen("last.dat","rb"))==NULL)
	{
		printf("cannot open “last.data”");
		return ;
	}
	fscanf(fp,"%d",&last);
	fclose(fp);
	printf("读取成功!");
}

void scan(good *g){     //浏览商品信息
	int a;
	int i;
	printf("输入要浏览的商品类别：");
	scanf("%d",&a);
	printf("编号\t名称\t型号\t类别\t价格\t库存数量\n");
    for(i=0;i<last;i++)
	{
		if(g[i].c ==a ){
			printf("%d\t%s\t%s\t%d\t%lf\t%d",g[i].n,g[i].name,g[i].model,g[i].c,g[i].price,g[i].num);
		}
		printf("\n");
	}
}

void show(){       //功能提示
	printf("\n欢迎使用商品信息管理系统\n");
	printf("========================\n");
	printf("1 信息录入\n");
	printf("2 商品浏览\n");
	printf("3 商品添加\n");
	printf("4 商品修改\n");
	printf("5 保存\n");
	printf("6 读取\n");
	printf("0 退出\n");
}

main(){
	good g[MAXSIZE],*p;
	int flag;
	init();
	p=g;
	do
	{
		show();
		printf("输入要完成的功能序号：");
	    scanf("%d",&flag);
	
	    switch(flag){
       	case 1: setUp(p);break;
	    case 2: scan(p);break;
		case 3: insert(p);break;
		case 4: change(p);break;
		case 5: save(p);break;
		case 6: read(p);break;
		}
	}while(flag);
	printf("%d",last);
}


