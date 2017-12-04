#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
int linenum;
void doubleword(char*,FILE*);
int getword(FILE*,char*,int);
int main(int argc,char* argv[])
{
    FILE *fp;
    for(int i=1;i<argc;i++)
    {
        if((fp=fopen(argv[i],"r"))==NULL)
        {
            fprintf(stderr,"%s can't open '%s'(%s)",argv[0],argv[i],strerror(errno));
            return EXIT_FAILURE;
        }
        else
        {
            doubleword(argv[i],fp);
            fclose(fp);
        }
    }
    if(argc==1)
        doubleword(NULL,stdin);
    return EXIT_SUCCESS;
}
void doubleword(char *name,FILE *fp)
{
    char prev[128],word[128];
    prev[0]='\0';
    linenum=1;
    while(getword(fp,word,sizeof(word)))
    {
        if(isalpha(word[0])&&strcmp(word,prev)==0)
        {
            if(name)
                printf("%s:",name);
            printf("%d: %s\n",linenum,word);
        }
        strcpy(prev,word);
    }
}
int getword(FILE *fp,char *buf,int size)
{
    int c;
    for(c=getc(fp);c!=EOF&&isspace(c);c=getc(fp))
        if(c=='\n')
            linenum++;
    int i=0;
    for(;c!=EOF&&!isspace(c);c=getc(fp))
    {
        if(i<size-1)
            buf[i++]=tolower(c);
    }
    if(i<size)
        buf[i]='\0';
    if(c!=EOF)
        ungetc(c,fp);//eg:push back the new line;
    return buf[0]!='\0';
}
