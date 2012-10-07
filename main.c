#include<stdio.h>
#include<stdlib.h>

//read input from file, represent each line as a seperate string


int input(char s[][20])
{
	int i=0,j=0;
	char c;
	FILE *ptr=fopen("input.txt","r");
	printf("File input is \n");
	while(fscanf(ptr,"%c",&c)!=EOF)
	{
		if(c=='\n'||c=='\t')
		{
			s[i][j]=0;
			i++;
			j=0;
		}
		else
		{
			s[i][j]=c;
			j++;
		}
		fflush(stdin);
		fflush(stdout);
	}
	s[i][j]=0;
	fclose(ptr);
	for(j=0;j<i;j++)
		printf("%s\n",s[j]);
	for(j=0;j<50;j++)
		printf("_");
	return i;
}

//check whether a variable/terminal is already in list or not
int isin(char c,char a[],int count)
{
	int i;
	for(i=0;i<count;i++)
	{
		if(a[i]==c)
			return 1;
	}
	return 0;
}

//seperate variables and terminals from input
void decode(char s[][20],char v[],char t[],int count,int *vcount,int *tcount)
{
	int i,j,v_count=0,t_count=0;
	printf("\nAnalysing input.....\n");
	for(i=0;i<count;i++)
	{
		for(j=0;s[i][j]!=0;j++)
		{
			if(s[i][j]>='A'&&s[i][j]<='Z')
			{
				/*int k,flag=0;
				for(k=0;k<v_count;k++)
				{
					if(v[k]==s[i][j])
					{
						flag=1;
						break;
					}
				}*/
				if(!isin(s[i][j],v,v_count))
				{
					v[v_count]=s[i][j];
					v_count++;
				}
			}
			else if(s[i][j]>='a'&&s[i][j]<='z')
			{
				/*int k,flag=0;
				for(k=0;k<t_count;k++)
				{
					if(v[k]==s[i][j])
					{
						flag=1;
						break;
					}
				}*/
				if(!isin(s[i][j],t,t_count))
				{
				
					t[t_count]=s[i][j];
					t_count++;
				}
			}
		}
	}
	*vcount=v_count;
	*tcount=t_count;
	printf("Analysis completed.\n");
	for(i=0;i<50;i++)
		printf("_");
	printf("\nVariables {");
	for(i=0;i<v_count;i++)
	{
		printf("%c",v[i]);
		if(i!=v_count-1)
			printf(",");
	}
	printf("}\nTerminals  {");
	for(i=0;i<t_count;i++)
	{
		printf("%c",t[i]);
		if(i!=t_count-1)
			printf(",");
	}
	printf("}\n");
	for(i=0;i<50;i++)
		printf("_");
}
//Return index of a character in an array
int getindex(char v[],int v_count,char e)
{
	int i;
	for(i=0;i<v_count;i++)
	{
		if(v[i]==e)
			return i;
	}
	return 0;
}
//Convert production statement to integer representation. Each variable and terminal
//will be represented by their index in respective arrays
int transform(char s[][20],int si[][20],int count,char e[],int limit)
{
	int i,j,k=0,l=0;
	for(i=0;i<count;i++)
	{
		for(j=0;s[i][j]!=0;j++)
		{
			if(s[i][j]>='A'&&s[i][j]<='Z')
			{
				si[k][l]=getindex(e,limit,s[i][j]);
				l++;
			}
			else if(s[i][j]>='a'&&s[i][j]<='z')
			{
				si[k][l]=getindex(e,limit,s[i][j]);
				l++;
			}
			else if(s[i][j]=='|')
			{
				si[k][l]=-1;
				k++;
				l=0;
				si[k][l]=si[k-1][l];
				l++;
			}
			//i++;
		}
		si[k][l]=-1;
		k++;
		l=0;
		//printf("%d ",k);
	}
	//printf("test %d ",k);
	printf("\nProductions in seperated form");
	for(i=0;i<k;i++)
	{
		printf("\n%c->",e[si[i][0]]);
		for(j=1;si[i][j]!=-1;j++)
		{
			printf("%c",e[si[i][j]]);
		}
	}
	printf("\n");
	return k;
}
//combine variables and terminals into single array
char *combine(char v[],int vc,char t[],int tc)
{
	int i=0;
	int j=0;
	char *e;
	e=(char *)malloc(sizeof(char)*40);
	for(i=0;i<vc;i++,j++)
		e[j]=v[i];
	for(i=0;i<tc;i++,j++)
		e[j]=t[i];
	return e;
}
void finalize(int si[][20],int np,char e[],int limit)
{
	char c[40],v[20];
	int l[np],vc;
	int i,j,k,r,t=0;
	for(i=0;i<limit;i++)
	{
		if(e[i]>='a'&&e[i]<='z')
		{
			c[t]=e[i];
			t++;
		}
	}
	for(i=0;i<np;i++)
		l[i]=0;
	do
	{
		r=0;
		
		for(i=0;i<np;i++)
		{
			int flag=1;
			for(j=1;si[i][j]!=-1;j++)
			{
				if(!isin(e[si[i][j]],c,t))
				{
					flag=0;
					break;
				}
			}
			if(flag)
			{
				l[i]=1;
				if(!isin(e[si[i][0]],c,t))
				{
					c[t]=e[si[i][0]];
				//l[i]=1;
					t++;
					r++;	
				}
			}
		}

	}while(r>0);
	for(i=0;i<50;i++)
		printf("_");
	printf("\n\nP' is ");
	//printf("%d ",np);
	for(i=0;i<np;i++)
	{
		if(l[i]==1)
		{
			printf("\n%c->",e[si[i][0]]);
			for(j=1;si[i][j]!=-1;j++)
			{
				printf("%c",e[si[i][j]]);
			}
		}
	}	
	//Finding V'
	j=0;
	for(i=0;i<np;i++)
	{
		if(l[i]==1&&!isin(e[si[i][0]],v,i+1))
		{
			v[j]=e[si[i][0]];
			j++;
		}
	}
	printf("\nV' is {");
	for(i=0;i<j;i++)
	{
		printf("%c",v[i]);
		if(i!=j-1)
			printf(",");
	}
	printf("}\n");
}			
			
		
									
int main()
{
	char s[20][20],v[20],t[20],*e;
	int v_count,t_count,si[20][20];
	int count,i,np;
	//read input from file , consider each line as a string
	count=input(s);
	
	//seperate variables and terminals from input
	decode(s,v,t,count,&v_count,&t_count);
	//combine variables and terminals to single array
	e=combine(v,v_count,t,t_count);
	//transform productions into integer representation. ie each variable and terminal
	//is represented by their index in varibale and terminal array

	np=transform(s,si,count,e,(t_count+v_count));
	
	//Analise and display result
	finalize(si,np,e,(t_count+v_count));
	free(e);
	
	return 0;
}
