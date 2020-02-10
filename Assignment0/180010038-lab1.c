#include<stdio.h>
int main(int argc, char*argv[])
{
  if(argc!=2)

  {

    printf("Only one at a time\n");

    return 0;

  }

  FILE *fp;
  FILE *fpo;

  fp= fopen(argv[1],"r");
  fpo= fopen("output.txt","w");
 
  if(fp==NULL)
  {
    printf("FAILED TO OPEN FILE\n");
    return 0;
  }

  int num;

  fscanf(fp,"%d",&num);

  int sum=0,count=0,min_no=num,max_no=num;

  while(!feof(fp))

  {

    //printf("%d\n",num);

    sum+=num;

    if(num>max_no)

    {

      max_no = num;

    }

    if(num<min_no)

    {

      min_no=num;

    }

    fscanf(fp,"%d",&num);

    count++;

  }

  double average = (double)sum/count;
  fprintf(fpo,"%d\n%d\n%d\n%d\n%.2f\n",count,min_no,max_no,sum,average);

return 0;
}
