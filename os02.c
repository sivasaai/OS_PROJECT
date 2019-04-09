#include<stdio.h>
int n;//Total no of processes
/*Struct contains details of a process.
p_id=process id.
at=arrival time.
bt=burst time.
wt=waiting time.
tat=turn arround time.
st=start time.
qn=tells us that to which queue it belongs.
*/
struct info
{
	int p_id;
	int at;
	int bt;
	int wt;
	int tat;
	int st;
	int ft;
};
struct info readyq[100];//ready queue,front,rear.
int rqr=-1,rqf=-1;
//renq() will add the process to readyq
void renq(struct info x)
{
if(rqr==100)
	{
		printf("over flow\n");
	}
	else if (rqf == -1 && rqr == -1)
	{
		rqf++;
		rqr++;
		readyq[rqr]=x;
	}
	else
	{
		rqr++;
		readyq[rqr]=x;
	}
}
//rdq() will remove process from readyq
void rdq()
{
if(rqr==rqf)
	{
		printf("Under Flow\n");
	}
	else
	{
		rqf++;
	}
}
//sort() will sort the queue according to arrival time and process id.
void sort(struct info *q[])
{
	struct info temp;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n-i-1;j++)
		{
			if(q[j]->at>q[j+1]->at)
			{
				temp=*q[j];
				*q[j]=*q[j+1];
				*q[j+1]=temp;
			}
			else if(q[j]->at==q[j+1]->at)
			{
				if(q[j]->p_id>q[j+1]->p_id)
				{
					temp=*q[j];
					*q[j]=*q[j+1];
					*q[j+1]=temp;
				}
			}
		}
	}
}
//updateq() will check for the processes arrived and adds them to readyq 
void updateq(struct info p[],int x)
{
    for(int j=0;j<n;j++)
    {
        if(p[j].at==x)
        {
            renq(p[j]);
        }
    }
}
//lrtf() returns the index of process with longest burst time left.
int lrtf()
{
	int index;
	int j=rqf;
	while(j<=rqr)
	{
		if(readyq[j].bt!=0)
		{
			index=j;
			break;
		}
		else
			j++;
	}
	for(int i=rqf;i<=rqr;i++)
	{
		if(readyq[i].bt>readyq[index].bt&&readyq[i].bt!=0)
		{
			index=i;
		}
	}
	return index;
}
//WtTat will calculates and prints the wt and tat of each process and average of wt and average of tat.
void WtTat(int chart[],struct info p[],int tt)
{
	int pid;
    int swt=0;
    int stat=0;
    float avgwt,awgwt;
	for(int i=0;i<n;i++)
	{
		int l;
		pid=p[i].p_id;
		for(int j=tt-1;j>=0;j--)
		{
			if(chart[j]==pid)
			{
				l=j+1;
				break;
			}
		}
		p[i].tat=l-p[i].at;
		p[i].wt=p[i].tat-p[i].bt;
	}
	printf("\n\n");
	for(int i=0;i<n;i++)
	{
		printf("pid:%d\t",p[i].p_id);
		printf("Waiting Time:%d\t",p[i].wt);
		printf("Turn Around Time:%d\t",p[i].tat);
		printf("\n\n");
	}
    for(int i=0;i<n;i++)
    {
        swt=swt+p[i].wt;
        stat=swt+p[i].tat;
    }
    avgwt=swt/n;
    avgwt=stat/n;
}
//gantt() will prepares the gant chart and prints.
void gantt(struct info p[])
{
	//calculating the size of gantt chart.
    int tt = 0;
    tt += p[0].at + p[0].bt;
	for (int i = 1; i < n; i++) 
	{
        if (tt < p[i].at)
            tt = p[i].at;
        
        tt += p[i].bt;
    }
    printf("Gantt Chart:\n");
	int chart[tt];
    for(int j=0;j<tt;j++)
        chart[tt]=-1;
    for(int j=0;j<n;j++)
    {
        if(p[j].at==0)
        {
            renq(p[j]);
        }
    }
    int qt1=0;
    int qt2=0;
    int uh=1;
	//follows round robin with quantum 6 for first 24 seconds.
    for(int j=0;j<24;j++)
    {
        chart[j]=readyq[rqf].p_id;
        readyq[rqf].bt--;
        qt1++;
        updateq(p,j+1);
        if(readyq[rqf].bt==0)
        {
            rdq();
            qt1=0;
        }
        else if(qt1==6)
        {
            renq(readyq[rqf]);
            rdq();
            qt1=0;
        }
    }
	//follows Round Robin with quantum 10 for next 40 seconds.
    for(int j=24;j<64;j++)
    {
        chart[j]=readyq[rqf].p_id;
        readyq[rqf].bt--;
        qt2++;
        updateq(p,j+1);
        if(readyq[rqf].bt==0)
        {
            rdq();
            qt2=0;
        }
        else if(qt2==10)
        {
            renq(readyq[rqf]);
            rdq();
            qt2=0;
        }
    }
	//follows LRTF for the rest.
    for(int j=64;j<tt;j++)
    {
        int lindex=lrtf();
        chart[j]=readyq[lindex].p_id;
        readyq[lindex].bt--;
    }
	//printing the gantt chart
    for(int i=0;i<tt;i++)
	{
		printf("%d\t",chart[i]);
	}
    WtTat(chart,p,tt);    //for printing Wt and Tat.
}
int main()
{
    printf("Enter the total number of processes\n");
    scanf("%d",&n);
    struct info p[n],pc[n],*pc1[n];
	printf("Enter The processes one by one with pid followed by at,bt\n");
    for(int i=0;i<n;i++)
    {
    	scanf("%d%d%d",&p[i].p_id,&p[i].at,&p[i].bt); 
    }
    for(int i=0;i<n;i++)
	{
		pc[i]=p[i];
        pc1[i]=&pc[i];
	}
    sort(pc1);
    gantt(pc);
    return 0;
}
