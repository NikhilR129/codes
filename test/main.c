#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
char str[10]={0},final[10]={'0','1','2','3','4','5','6','7','8','\0'};
int hasharr[400000],k;
int parent[400000];

struct queue{
	char arr[100000][10];
	int head;
	int tail;
};
struct queue Q;

void cpystr(char array[]){
	int i;
	for(i=0;i<9;i++){
		Q.arr[Q.head][i]=array[i];
	}
	Q.arr[Q.head][i]='\0';
}

void enq(char array[]){
	cpystr(array);
	Q.head++;
}

void front(char array[]){
	int i;
	for(i=0;i<9;i++){
		array[i]=Q.arr[Q.tail][i];
	}
	array[9]='\0';
}

void deq(){
	Q.tail++;
}

int findzero(char array[]){
	int i;
	for(i=0;i<9;i++){
		if(array[i]=='0')
			break;
	}
	return i;
}

void swap(char array[],int i,int j){
	char temp;
	temp=array[i];
	array[i]=array[j];
	array[j]=temp;
}

void prinarray(){
	/*int i,j;
	for(i=0;i<=6;i+=3){
		for(j=0;j<=2;j++){
			printf("%c %c %c\n",Q.arr[Q.head-1][i+j]);
		}
	}
	printf("\n");*/
	printf("Queue head %d tail %d %s\n",Q.head,Q.tail,Q.arr[Q.head-1]);
}

int inssorted(int a){
	int i,j;
	for(i=0;i<k;i++){
		if(hasharr[i]>a)
			break;
	}
	for(j=k;j>i;j--)
		hasharr[j]=hasharr[j-1];
	hasharr[i]=a;
	k++;
	return i;
}

bool bin_search(int a){
	int l=0,u=k-1,mid;
	while(l<=u){
         mid=(l+u)/2;
         if(a==hasharr[mid]){
             return true;
         }
         else if(a<hasharr[mid]){
             u=mid-1;
         }
         else
             l=mid+1;
    }
    return false;
}

void solve(){
	char a[10],b[10];
	int i,j,g;
	enq(str);
	if(strcmp(str,final)==0){
		return;
	}
	//printf("String %s Number %d\n",a,atoi(a));
	//inssorted(atoi(a));
	prinarray();
	while(Q.head>Q.tail){
		front(a);
		deq();
		i=findzero(a);
		//printf("Head %d Tail %d\n i %d front of queue %s\n",Q.head,Q.tail,i,a);
		if(i!=0 && i!=3 && i!=6){
			swap(a,i-1,i);
			if(!bin_search(atoi(a))){
					enq(a);
				inssorted(atoi(a));
				prinarray();
				//printf("Hi\n");
				if(strcmp(a,final)==0){
					return;
				}
			}
			swap(a,i-1,i);
		}
		//printf("Head %d Tail %d\n i %d front of queue %s\n",Q.head,Q.tail,i,a);
		if(i!=2 && i!=5 && i!=8){
			swap(a,i+1,i);
			if(!bin_search(atoi(a))){
					enq(a);
				inssorted(atoi(a));
				prinarray();
				//printf("Hi\n");
				if(strcmp(a,final)==0){
					return;
				}
			}
			swap(a,i+1,i);
		}
		//printf("Head %d Tail %d\n i %d front of queue %s\n",Q.head,Q.tail,i,a);
		if(i!=0 && i!=1 && i!=2){
			swap(a,i-3,i);
			if(!bin_search(atoi(a))){
					enq(a);
				inssorted(atoi(a));
				prinarray();
				//printf("Hi\n");
				if(strcmp(a,final)==0){
					return;
				}
			}
			swap(a,i-3,i);
		}
		//printf("Head %d Tail %d\n i %d front of queue %s\n",Q.head,Q.tail,i,a);
		if(i!=6 && i!=7 && i!=8){
			swap(a,i+3,i);
			if(!bin_search(atoi(a))){
					enq(a);
				inssorted(atoi(a));
				prinarray();
				//printf("Hi\n");
				if(strcmp(a,final)==0){
					return;
				}
			}
			swap(a,i+3,i);
		}
		//printf("Head %d Tail %d\n i %d front of queue %s\n",Q.head,Q.tail,i,a);
		//printf("%s %s %s %s\n",Q.arr[Q.tail],Q.arr[Q.tail+1],Q.arr[Q.tail+2],Q.arr[Q.tail+3]);
		//break;
	}
}

int check(){
	int count=0,i,j;
	for(i=0;i<8;i++){
		for(j=i+1;j<=8;j++){
			if(str[i]!='0' && str[j]!='0' && str[j]<str[i])
				count++;
		}
	}
	printf("count %d\n",count);
	return count%2;
}


int main(){
    int i,t,n;
    FILE *F1;
    F1=fopen("init.txt","r");
    fscanf(F1,"%s",str);
    printf("%s\n",str);
    if(check()==0)
    	solve();
    else
    	printf("unsolvable\n");
    return 0;
}
