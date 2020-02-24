#include <string.h>
#include <stdio.h>
#include "f.h"
#define LEN 1234
#define ERROR_OPEN_A -1
#define ERROR_OPEN_B -2
#define ERROR_READ_A -3
#define ERROR_WRITE_B -4
#define SUCCESS 0
int f(const char *a, const char *b, const char *s, const char *r)
{
	FILE *in, *out;
	char buf[LEN];
	char *key;
	int i, l = strlen(s);
	int count = 0;
	if(!(in=fopen(a,"r")))
		return ERROR_OPEN_A;
	if(!(out=fopen(b,"w")))
	{
		fclose(in);
		return ERROR_OPEN_B;
	}
	while(fgets(buf,LEN,in))
	{
		if(strstr(buf,s))
		{
			
			key = strstr(buf,s);
			i = 0;
			while(buf[i])
			{

				if(buf[i]=='\n')
				{
					buf[i] = 0;
					fprintf(out,"\n");
					break;
				}
				if((buf+i)!=key)
				{
					fprintf(out,"%c",buf[i]);
				}
				if((buf+i)==key)
				{
					fprintf(out,"%s",r);
					key = strstr(buf+i+l,s);
					i = i+l-1;
					
				}
				i++;
			}
			count++;
		}
		else
			fprintf(out,"%s", buf);
	}
	if(!feof(in))
	{
		fclose(in);
		fclose(out);
		return ERROR_READ_A;
	}
	fclose(in);
	fclose(out);
	return count;
}