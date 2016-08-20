#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char animals[15][20]={
"ape",
"bear",
"cat",
"cow",
"deer",
"elephant",
"dog",
"eel",
"goat",
"hyena",
"jaguar",
"wolf",
"ant",
"hen",
"owl"
};
char colours[15][20]={
"black",
"blue",
"brown",
"grey",
"pink",
"red",
"green",
"white",
"yellow",
"orange",
"magenta",
"purple",
"violet",
"indigo",
"cyan"
};
char astronomy[15][20]={
"mercury",
"venus",
"earth",
"mars",
"jupiter",
"saturn",
"uranus",
"star",
"moon",
"meteor",
"nebula",
"galaxy",
"sun",
"blackhole",
"neptune"
};
char fruits[15][20]={
"apple",
"banana",
"grape",
"jackfruit",
"kiwi",
"lychee",
"mango",
"orange",
"plum",
"pineapple",
"raspberry",
"strawberry",
"starfruit",
"watermelon"
};

char grid[25][25];
int mask[25][25];
int check_horizontal(int r,int c,int ch,int index)
{
    int len,i;
    if(ch==1)
        len=strlen(animals[index]);
    else if(ch==2)
        len=strlen(colours[index]);
    else if(ch==3)
        len=strlen(astronomy[index]);
    else if(ch==4)
        len=strlen(fruits[index]);

        for(i=c;i<c+len;i++)
        {
           if(i>=20)
                return 0;
           if(mask[r][i]==1)
           {
               return 0;
           }
        }
            for(i=c;i<c+len;i++)
            {
                mask[r][i]=1;
               if(ch==1) grid[r][i]=animals[index][i-c];
                if(ch==2) grid[r][i]=colours[index][i-c];
                if(ch==3) grid[r][i]=astronomy[index][i-c];
                if(ch==4) grid[r][i]=fruits[index][i-c];
            }
            return 1;
    }
int check_vertical(int r,int c,int ch,int index)
{
    int len,i;
    if(ch==1)
        len=strlen(animals[index]);
    else if(ch==2)
        len=strlen(colours[index]);
    else if(ch==3)
        len=strlen(astronomy[index]);
    else if(ch==4)
        len=strlen(fruits[index]);

        for(i=r;i<r+len;i++)
        {
           if(i>=20)
                return 0;
           if(mask[i][c]==1)
           {
               return 0;
           }
        }
            for(i=r;i<r+len;i++)
            {
                mask[i][c]=1;
               if(ch==1) grid[i][c]=animals[index][i-r];
                if(ch==2) grid[i][c]=colours[index][i-r];
                if(ch==3) grid[i][c]=astronomy[index][i-r];
                if(ch==4) grid[i][c]=fruits[index][i-r];
            }
            return 1;
    }
int check_cross(int r,int c,int ch,int index)
{
    int len,i,j;
    if(ch==1)
        len=strlen(animals[index]);
    else if(ch==2)
        len=strlen(colours[index]);
    else if(ch==3)
        len=strlen(astronomy[index]);
    else if(ch==4)
        len=strlen(fruits[index]);

        for(i=r,j=c;i<r+len && j<c+len;i++,j++)
        {
           if(i>=20 || j>=20)
                return 0;
           if(mask[i][j]==1)
           {
               return 0;
           }
        }
            for(i=r,j=c;i<r+len && j<c+len;i++,j++)
            {
                mask[i][j]=1;
               if(ch==1) grid[i][j]=animals[index][i-r];
                if(ch==2) grid[i][j]=colours[index][i-r];
                if(ch==3) grid[i][j]=astronomy[index][i-r];
                if(ch==4) grid[i][j]=fruits[index][i-r];
            }
            return 1;
    }
int* generate_grid(int ch,int answer_matrix[])
{
    int i,r,c,j,count=0,count1=0,count2=0,count3=0,index,temp;
  /* initialize random seed: */
    srand (time(NULL));
    int hash[15];
    for(i=0;i<15;i++)
        hash[i]=-1;
    for(i=0;i<20;i++)
            for(j=0;j<20;j++)
            {
            temp = 25 + rand() / (RAND_MAX / (1 - 25+ 1) + 1);
            mask[i][j]=0;
            grid[i][j]=97+temp;
            }
  while(count<=8)
    {
        r = 20 + rand() / (RAND_MAX / (1 - 20 + 1) + 1);
        c = 20 + rand() / (RAND_MAX / (1 - 20 + 1) + 1);

        index = 14 + rand() / (RAND_MAX / (1 - 14 +1) + 1);
        if(hash[index]==-1 && check_horizontal(r,c,ch,index)==1)
            {
                answer_matrix[count]=index;
                hash[index]++;
                count++;
                 r = 20 + rand() / (RAND_MAX / (1 - 20 + 1) + 1);
                c = 20 + rand() / (RAND_MAX / (1 - 20 + 1) + 1);

                index = 14 + rand() / (RAND_MAX / (1 - 14 +1) + 1);
            }
            if(hash[index]==-1 && check_vertical(r,c,ch,index)==1)
            {
                answer_matrix[count]=index;
                count++;
                hash[index]++;
                 r = 20 + rand() / (RAND_MAX / (1 - 20 + 1) + 1);
                c = 20 + rand() / (RAND_MAX / (1 - 20 + 1) + 1);
                index = 14 + rand() / (RAND_MAX / (1 - 14 +1) + 1);
            }

        if(hash[index]==-1 && check_cross(r,c,ch,index)==1)
            {
                answer_matrix[count]=index;
                count++;
                hash[index]++;
            }

            //count=count1+count2+count3;
    }
    for(i=0;i<20;i++)
    {
        printf("  ");
        for(j=0;j<20;j++)
            printf("%c ",grid[i][j]);
        printf("\n");
    }

    return answer_matrix;
}

int main()
{
    int ch,i,j,answer_matrix[6];
    char name[50];
    printf("  Heyy there!! Please tell your name first--> ");
    scanf("%[^\n]",name);
    printf("\n\n  Hi %s !! Glad to have you here !! Please follow the Rules and the Menu below carefully\n\n",name);
   /* FILE *fp1,*fp2;
    char a[50];
    fp1=fopen("file.txt","r");
    fp2=fopen("colours.txt","w");
    while(fscanf(fp1,"%s\n",a)!=EOF)
        fprintf(fp2,"\"%s\"\,\n",a);
        */
        printf("  Rules->\n  *******\n  1.  You can choose one of the topics from the menu below\n\n");
        printf("  2.  You have to find 6 names of the selected topic\n\n");
        printf("  3.  You have 8 attempts in total\n\n              **GOOD LUCK**\n\n");

    while(1)
    {
        int count,corr_answers;
        char ans[20];
        printf("  MENU\n  *****\n  1.  Animals\n\n  2.  Colors\n\n  3.  Fruits\n\n  4.  Exit\n\n");
        printf("  Please enter your choice: [1/2/3/4] ");
        scanf("%d",&ch);
        if(ch==1)
        {
        count=0; corr_answers=0;
        int *answer=generate_grid(ch,answer_matrix);
        printf("\n\n  Enter your answers!!\n\n");
        while(count!=8)
        {
            int flag=0;
            printf(">>");
            scanf("%s",ans);
            count++;
            for(i=0;i<6;i++)
            {
                if(strcmp(animals[answer[i]],ans)==0)
                {
                corr_answers++;
                printf("  Correct\n");
                flag=1;
                }
            }
            if(flag==0)
                printf("  That's not what exactly I was looking for!!\n");
            if(corr_answers==6)
            {
                printf("\n\ncongrats!! You nailed it!!\n\n");
                break;
            }
            if(count==8)
            {
                printf("\n\nSorry!! Game over!! Try again!! Your score is %d\n\n",corr_answers);
            }

        }
        }
        else if(ch==2)
        {
        count=0; corr_answers=0;
        int *answer=generate_grid(ch,answer_matrix);
        printf("\n\n  Enter your answers!!\n");
        while(count!=8)
        {
            int flag=0;
            printf(">>");
            scanf("%s",ans);
            count++;
            for(i=0;i<6;i++)
            {
                if(strcmp(colours[answer[i]],ans)==0)
                {
                corr_answers++;
                printf("  Correct\n");
                flag=1;
                }
            }
            if(flag==0)
                printf("  That's not what exactly I was looking for!!\n");
            if(corr_answers==6)
            {
                printf("\n\n  congrats!! You nailed it!!\n\n");
                break;
            }
            if(count==8)
            {
                printf("\n\n  Sorry!! Game over!! Try again!! Your score is %d\n\n",corr_answers);
            }

        }
        }
        else if(ch==3)
        {
        count=0; corr_answers=0;
        int *answer=generate_grid(ch,answer_matrix);
        printf("\n\n  Enter your answers!!\n");
        while(count!=8)
        {
            int flag=0;
            printf(">>");
            scanf("%s",ans);
            count++;
            for(i=0;i<6;i++)
            {
                if(strcmp(fruits[answer[i]],ans)==0)
                {
                corr_answers++;
                printf("  Correct\n");
                flag=1;
                }
            }
            if(flag==0)
                printf("  That's not what exactly I was looking for!!\n");
            if(corr_answers==6)
            {
                printf("\n\n  congrats!! You nailed it!!\n\n");
                break;
            }
            if(count==8)
            {
                printf("\n\n  Sorry!! Game over!! Try again!! Your score is %d\n\n",corr_answers);
            }

        }
        }
    else if(ch==4)
            return 0;
    else
        printf("\n\n  Wrong option selected..Please try again\n\n");
        }
    return 0;
}
