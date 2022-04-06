#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct word0
{
	char tu[50];
};

struct word1
{
	int col;
	char wor[25];
};

struct word2
{
	char wor[25];
	int times;
};



void delete(char wor[])
{
    int i;
    i=strlen(wor);
    if(isalpha(wor[i-1])==0)wor[i-1]='\0';
}

int open1(FILE *f,struct word1 str1[])
{
	int m=0;
	char c;
	char string[25];
	int i,line=1,end_sen=0;
	int k;

    while(!feof(f))
        {	
            i=0;k=0;
            do{
            c=fgetc(f);
            if(c=='.') end_sen=1;	
            if((c>='a' && c<='z') || (c>='A' && c<='Z') || c=='-')
            {
            if (end_sen==1 && c>='A' && c<='Z') 
            {k=1; end_sen=0;}
            string[i]=c;
            i++;
            }
            else
            {
            string[i]='\0';
            if(c=='\n') line++;	
            break;
            }
            }while(1);

	        if(strlen(string)>1)
            {
                if(!(k!=1 && string[0] >='A' && string[0]<='Z'))
                {
                    if(string[0]>='A'&& string[0]<='Z') string[0]+=32;
                    delete(string);
                    strcpy(str1[m].wor,string);
                    str1[m].col=line;
                    m++;
                }
            }
        }
	return m;
	}


int open2(FILE *f,struct word0 str2[])
{
	char buff[10];
	int n=0,i;
	char c;
	while(!feof(f))
	{	i=0;
	do{
		c=fgetc(f);
		if((c>='a' && c<='z') || (c>='A' && c<='Z'))
		{
		buff[i]=c;
		i++;
		}
		else
		{
		buff[i]='\0';
		break;
		}
	}while(1);
		if(strlen(buff)>0)
		{
		delete(buff);
		strcpy(str2[n].tu,buff);
		n++;
		}
	}
	return n;
}

int compare(struct word1 str1[],struct word1 str3[],struct word0 str2[],int m, int n)
{
int i,j,k=0;
int x;
int h=0;
for(i=0;i<m;i++)
{	
    x=1;
	for(j=0;j<n;j++)
	{
		if(strcmp(str2[j].tu,str1[i].wor)==0)
		{x=0;break;}
	}
	if(x==1)
	{
        strcpy(str3[h].wor,str1[i].wor);
			str3[h].col=str1[i].col;
			h++;
    }
	
}
return h;
}

void sorting(struct word1 str1[], int n)
{

	int i,j;
	struct word1 tmp;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(strcmp(str1[i].wor,str1[j].wor)<0)
			{
				tmp=str1[i];
				str1[i]=str1[j];
				str1[j]=tmp;
			}
		}
	}
}



int final(struct word2 str4[],struct word1 str3[],int m)
{
	int i,j;
	int k=1,h=0;

	for (i = 0; i < m; i++)
	{
			if(strcmp(str3[i].wor,str3[i+1].wor)==0)
			{
				k++;
			}
			else
			{
			strcpy(str4[h].wor,str3[i].wor);
			str4[h].times=k;
			h++;
			k=1;
			}
	}
	return h;
}


void result(struct word2 str4[],struct word1 str3[],int m, int n)
{
	int i,j;
	int flag[100];
	for(i=0;i<m;i++)
	{	
		printf("%-20s%d",str4[i].wor,str4[i].times);
		for(j=0;j<n;j++)
		{ 
			if(strcmp(str4[i].wor,str3[j].wor)==0) 
			{
				printf(", %d", str3[j].col);
			}
		}
		printf("\n");
	}
}

int main()
{
	FILE *f1,*f2;
	struct word1 str1[200];
	struct word0 str2[80];
	struct word1 str3[200];
	struct word2 str4[200];
	int i,m,h,n,tong;
	int j,k=0,flag;

	f1=fopen("vanban.txt","r");
	f2=fopen("stopw.txt","r");
	if(f1==NULL || f2==NULL) 
	{
		printf("File does not exist\n");
	}
	h=open2(f2,str2);
	m=open1(f1,str1);
	j=compare(str1,str3,str2,m,h);
	sorting(str3,j);
	tong=final(str4,str3,j);
	result(str4,str3,tong,j);
	return 0;
}