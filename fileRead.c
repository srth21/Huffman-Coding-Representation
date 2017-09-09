#include<stdio.h>
#include<stdlib.h>


int returnSize()
{
  int freq[54];
  int j;
  for(j=0;j<54;j++)
  {
    freq[j]=0;
  }


  char alpha[54];
  char ch='a';
  int i=0;
  for(;i<52;i++)
  {
    alpha[i]=ch;
    if(ch=='z')
      ch='A';
    else
      ch++;
  }
  alpha[52]=' ';
  alpha[53]='.';



  char code;
  for(i=0;i<54;i++)
  {
    FILE *f=fopen("test.txt","r");
    char ch1=alpha[i];

    while((code = fgetc(f)) != EOF) {
           if (code == ch1) {
               freq[i]++;
           }
  }
  fclose(f);
  }

  int size=0;
  for(i=0;i<54;i++)
  {
    if(freq[i]!=0)
    {
      size++;

    }
  }
  int *freqNew;
  char *alphaNew;
  freqNew=(int *)malloc(sizeof(int)*size);
  alphaNew=(char *)malloc(sizeof(char)*size);
  int range=0;
  for(i=0;i<54;i++)
  {
    if(freq[i]!=0)
    {
      alphaNew[range]=alpha[i];
      freqNew[range]=freq[i];
      range++;
    }
  }
  printf("Character->Frequency\n");
for(i=0;i<range;i++)
{
  printf("%c->%d\n",alphaNew[i],freqNew[i]);
}
printf("\n");
return range;
}

int* returnFreqArray()
{
  int freq[54];
  int j;
  for(j=0;j<54;j++)
  {
    freq[j]=0;
  }
  int *freqNew;
  char *alphaNew;

  char alpha[54];
  char ch='a';
  int i=0;
  for(;i<52;i++)
  {
    alpha[i]=ch;
    if(ch=='z')
      ch='A';
    else
      ch++;
  }
  alpha[52]=' ';
  alpha[53]='.';

  char code;
  for(i=0;i<54;i++)
  {
    FILE *f=fopen("test.txt","r");
    char ch1=alpha[i];

    while((code = fgetc(f)) != EOF) {
           if (code == ch1) {
               freq[i]++;
           }
  }
  fclose(f);
  }

  int size=0;
  for(i=0;i<54;i++)
  {
    if(freq[i]!=0)
    {
      size++;

    }
  }
  freqNew=(int *)malloc(sizeof(int)*size);
  alphaNew=(char *)malloc(sizeof(char)*size);
  int range=0;
  for(i=0;i<54;i++)
  {
    if(freq[i]!=0)
    {
      alphaNew[range]=alpha[i];
      freqNew[range]=freq[i];
      range++;
    }
  }
return freqNew;
}

char* returnAlphaArray()
{
  int freq[54];
  int j;
  for(j=0;j<54;j++)
  {
    freq[j]=0;
  }


  char alpha[54];
  char ch='a';
  int i=0;
  for(;i<52;i++)
  {
    alpha[i]=ch;
    if(ch=='z')
      ch='A';
    else
      ch++;
  }
  alpha[52]=' ';
  alpha[53]='.';
  int *freqNew;
  char *alphaNew;
  char code;
  for(i=0;i<54;i++)
  {
    FILE *f=fopen("test.txt","r");
    char ch1=alpha[i];

    while((code = fgetc(f)) != EOF) {
           if (code == ch1) {
               freq[i]++;
           }
  }
  fclose(f);
  }

  int size=0;
  for(i=0;i<54;i++)
  {
    if(freq[i]!=0)
    {
      size++;

    }
  }
  freqNew=(int *)malloc(sizeof(int)*size);
  alphaNew=(char *)malloc(sizeof(char)*size);
  int range=0;
  for(i=0;i<54;i++)
  {
    if(freq[i]!=0)
    {
      alphaNew[range]=alpha[i];
      freqNew[range]=freq[i];
      range++;
    }
  }

return alphaNew;
}
