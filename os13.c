#include<stdio.h>
int n;//Total no Processes.

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
	int priority;
	int wt;
	int tat;
	int st;
	int ft;
};
//declarating the queues with maximum 100 processes
struct info *q1[100];
struct info *q2[100];
struct info *q3[100];
int l=0;//length of q1.
int m=0;//length of q2.
int h=0;//length of q3.
int oready[100];//Ready Queue for MultiLevel
int orf=-1,orr=-1;
struct info hready[100];//Ready Queue for q1.
int hrf=-1,hrr=-1;
struct info mready[100];//Ready Queue For q2.
int mrf=-1,mrr=-1;
struct info lready[100];//Ready Queue For q3.
int lrf=-1,lrr=-1;
//mlq() pushes the processes int0 respective queue according to priorities.
void mlq(struct info p[])
{
	for(int i=0;i<n;i++)
	{
	if(p[i].priority>0&&p[i].priority<=10)
	{
		q1[l]=&p[i];
		l++;
	}
	else if(p[i].priority>10&&p[i].priority<=20)
	{
		q2[m]=&p[i];
		m++;
	}
	else
	{
		q3[h]=&p[i];
		h++;
	}

	}
}
//sort() sorts the process according arrival time and process id.
void sort(struct info *q[],int size)
{
	struct info temp;
	for(int i=0;i<size-1;i++)
	{
		for(int j=0;j<size-i-1;j++)
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
//orenq() pushes the queue number into queue
void orenq(int x)
{
	if(orr==100)
	{
		printf("over flow\n");
	}
	else if (orf == -1 && orr == -1)
	{
		orf++;
		orr++;
		oready[orr]=x;
	}
	else
	{
		orr++;
		oready[orr]=x;
	}
}
//ordq() removes the queue number from queue.
void ordq()
{
	if(orr==orf)
	{
		printf("\n");
	}
	else
	{
		orf++;
	}
}
//hrenq() will add process to hready q
void hrenq(struct info x)
{
	if(hrr==100)
	{
		printf("over flow\n");
	}
	else if (hrf == -1 && hrr == -1)
	{
		hrf++;
		hrr++;
		hready[hrr]=x;
	}
	else
	{
		hrr++;
		hready[hrr]=x;
	}

}
//hrdq removes the process from hready q.
void hrdq()
{
if(hrr==hrf)
	{
		printf("\n");
	}
	else
	{
		hrf++;
	}
}
//mrenq() adds process to mready q.
void mrenq(struct info x)
{
	if(mrr==100)
	{
		printf("over flow\n");
	}
	else if (mrf == -1 && mrr == -1)
	{
		mrf++;
		mrr++;
		mready[mrr]=x;
	}
	else
	{
		mrr++;
		mready[mrr]=x;
	}
}
//lrenq() adds process to lready q.
void lrenq(struct info x)
{
	if(lrr==100)
	{
		printf("over flow\n");
	}
	else if (lrf == -1 && lrr == -1)
	{
		lrf++;
		lrr++;
		lready[lrr]=x;
	}
	else
	{
		lrr++;
		lready[lrr]=x;
	}
}
//islempty() will check weather lready q empty or not.
int islempty()
{
	int s=0;
	for(int i=lrf;i<=lrr;i++)
	{
		if(lready[i].bt!=0)
			s=1;
	}
	if(s==0)
	{
		return 1;
	}
	else return 0;
		
}
//ismempty() will check weather mready q empty or not.
int ismempty()
{
	int s=0;
	for(int i=mrf;i<=mrr;i++)
	{
		if(mready[i].bt!=0)
			s=1;
	}
	if(s==0)
	{
		return 1;
	}
	else return 0;
}
//ishempty() will check weather hready q empty or not.
int ishempty()
{
	if(hrr==-1&&hrf==-1)
	{
		return 1;
	}
	else if(hrf>hrr)
	{
		return 1;
	}
	else return 0;
}
//isoempty() will check weather oready q empty or not.
int isoempty()
{
	if(orr=-1&&orf==-1)
	{
		return 1;
	}
	else if(orf>orr)
	{
		return 1;
	}
	else return 0;
}
//prior() will return the process index with high priority in mready q.
int prior()
{
	int index;
	int j=mrf;
	while(j<=mrr)
	{
		if(mready[j].bt!=0)
		{
			index=j;
			break;
		} 
		else
		{
			j++;
		}
			
	}
	for(int i=mrf;i<=mrr;i++)
	{
		if(mready[i].priority>mready[index].priority&&mready[i].bt!=0)
		{
			index=i;
		}		

	}
	return index;
}
//fcfs() will return the index of the process with least arrival time in lready q 
int fcfs()
{
	int index;
	int lat;
	int j=lrf;
	while(j<=lrr)
	{
		if(lready[j].bt!=0)
		{
			index=j;
			break;
		}
		else
			j++;
	}
	for(int i=lrf;i<=lrr;i++)
	{
		if(lready[i].at<lready[index].at&&lready[i].bt!=0)
		{
			index=i;
		}
	}
	return index;
}
//updates lready q with new arrived process.
void updatel(int x)
{
for(int i=0;i<l;i++)
{
if(q1[i]->at==x)
{
	lrenq(*q1[i]);
}
}
}
//updates mready q with new arrived process.
void updatem(int x)
{
	for(int i=0;i<l;i++)
	{
		if(q2[i]->at==x)
		{
			mrenq(*q2[i]);
		}
	}
}
//updates hready q with new arrived process.
void updateh(int x)
{
	for(int i=0;i<l;i++)
	{
		if(q3[i]->at==x)
		{
			hrenq(*q3[i]);
		}
	}
}
//minatl returns the index of process with least arrival time in lready q
int minatl()
{
	int index;
	int mint;
	int j=lrf;
	while(j<=lrr)
	{
		if(lready[j].bt!=0)
		{
			index=j;
			mint=lready[j].at;
			break;
		}	
		else j++;
	}
	for(int i=lrf;i<lrr;i++)
	{
		if(lready[i].at<mint&&lready[i].bt!=0)
		{
			index=i;
			mint=lready[i].at;
		}
	}
	return index;
}
//minatm returns the index of process with least arrival time in mready q
int minatm()
{
	int index;
	int mint;
	int j=mrf;
	while(j<=mrr)
	{
		if(mready[j].bt!=0)
		{
			index=j;
			mint=mready[j].at;
			break;
		}	
		else j++;
	}
	for(int i=mrf;i<mrr;i++)
	{
		if(mready[i].at<mint&&mready[i].bt!=0)
		{
			index=i;
			mint=mready[i].at;
		}
	}
	return index;
}
//minath returns the index of process with least arrival time in hready q
int minath()
{
	int index;
	int mint;
	int j=hrf;
	while(j<=hrr)
	{
		if(hready[j].bt!=0)
		{
			int index=j;
			mint=hready[j].at;
			break;
		}	
		else j++;
	}
	for(int i=hrf;i<hrr;i++)
	{
		if(hready[i].at<mint&&hready[i].bt!=0)
		{
			index=i;
			mint=hready[i].at;
		}
	}
	return mint;
}
//updates oready q
void updateo()
{
	if((orr-orf)!=2)
	{
		if((orr-orf)==0)
		{
			int temp=oready[orf];
			if(temp==1)
			{
				if(ismempty()||ishempty())
				{
					if(ismempty()&&ishempty());
					else if(ismempty())
						orenq(3);
					else orenq(2);
				}
				else
				{
					int x=minatm();
					int y=minath();
					if(mready[x].at<hready[y].at)
					{
						orenq(2);
						orenq(3);
					}			
					else if(mready[x].at>hready[y].at)
					{
						orenq(3);
						orenq(2);
					}
					else
					{
						if(mready[x].p_id<hready[y].p_id)
						{
							orenq(2);
							orenq(3);
						}
						else
						{
							orenq(3);
							orenq(2);
						}
					}
				}
			}
			else if(temp==2)
			{
			if(islempty()||ishempty())
				{
					if(islempty()&&ishempty());
					else if(islempty())
						orenq(1);
					else orenq(3);
				}
				else
				{
					int x=minatl();
					int y=minath();
					if(lready[x].at<hready[y].at)
					{
						orenq(1);
						orenq(3);
					}			
					else if(lready[x].at>hready[y].at)
					{
						orenq(3);
						orenq(1);
					}
					else
					{
						if(lready[x].p_id<hready[y].p_id)
						{
							orenq(1);
							orenq(3);
						}
						else
						{
							orenq(3);
							orenq(1);
						}
					}
				}	
			}
			else
			{
				if(islempty()||ismempty())
				{
					if(islempty()&&ismempty());
					else if(islempty())
						orenq(2);
					else orenq(1);
				}
				else
				{
					int x=minatl();
					int y=minatm();
					if(lready[x].at<mready[y].at)
					{
						orenq(1);
						orenq(2);
					}			
					else if(lready[x].at>mready[y].at)
					{
						orenq(2);
						orenq(1);
					}
					else
					{
						if(lready[x].p_id<mready[y].p_id)
						{
							orenq(1);
							orenq(2);
						}
						else
						{
							orenq(2);
							orenq(1);
						}
					}
				}
			}
			
		}
		else if((orf-orr)==1)
		{
			int x=6-(oready[orf]+oready[orf+1]);
			if(x==1)
			{
				if(!islempty())
					orenq(1);
			}
			else if(x==2)
			{
				if(!ismempty())
					orenq(2);
			}
			else
			{
				if(!ishempty())
					orenq(3);
			}
			
		}
	}
}
//WtTat() will Calculate and print the wt and tat of each process. 
void WtTat(int chart[],struct info p[],int tt)
{
	int pid;
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
}
//gantt() prepares gantt chart and prints
void gantt(struct info pc[])
{
	//calculate max size of gantt chart.
	int tt = 0;
    tt += pc[0].at + pc[0].bt;
	for (int i = 1; i < n; i++) 
	{
        if (tt < pc[i].at)
            tt = pc[i].at;
        
        tt += pc[i].bt;
    }
	int chart[tt];
	for(int i=0;i<tt;i++)
	{
		chart[i]=-1;
	}
	for(int i=0;i<l;i++)
	{
		if(q1[i]->at==0)
		{
			lrenq(*q1[i]);
		}
	}
	for(int i=0;i<m;i++)
	{
		if(q2[i]->at==0)
		{
			mrenq(*q2[i]);
		}
	}
	for(int i=0;i<h;i++)
	{
		if(q2[i]->at==0)
		{
			hrenq(*q3[i]);
		}
	}
	if(lready[0].at==0&&mready[0].at==0&&hready[0].at==0)
	{
		int min=1;
		if(mready[0].p_id<lready[0].p_id)
		{
			min=2;
		}
		if(hready[0].p_id<lready[0].p_id&&hready[0].p_id<mready[0].p_id)
		{
			min=3;
		}
		orenq(min);
		if(min==1)
		{
			if(mready[0].p_id<hready[0].p_id)
			{
				orenq(2);
				orenq(3);
			}
			else
			{
				orenq(3);
				orenq(2);
			}
		}
		else if(min==2)
		{
			if(lready[0].p_id<hready[0].p_id)
			{
				orenq(1);
				orenq(3);
			}
			else
			{
				orenq(3);
				orenq(1);
			}
		}
		else
		{
			if(lready[0].p_id<mready[0].p_id)
			{
				orenq(0);
				orenq(2);
			}
			else
			{
				orenq(2);
				orenq(0);
			}
			
		}
	}
	int oqt=0;
	int iqt=0;
	int uh=1;
	for(int i=0;i<tt;i++)
	{
		if(oready[orf]==1)
		{
			int findex=fcfs();
			chart[i]=lready[findex].p_id;
			lready[findex].bt--;
			oqt++;
		}
		else if(oready[orf]==2)
		{
			int pindex=prior();
			chart[i]=mready[pindex].p_id;
			mready[pindex].bt--;
			oqt++;
		}
		else if(oready[orf]==3)
		{
			chart[i]=hready[hrf].p_id;
			hready[hrf].bt--;
			oqt++;
			iqt++;
			if(hready[hrf].bt==0)
			{
				hrdq();
				iqt=0;
			}
			else if(iqt==4)
			{
				iqt=0;
				updateh(i+1);
				hrenq(hready[hrf]);
				hrdq();
				uh=0;
			}
		}
		updatel(i+1);
		updatem(i+1);
		if(uh!=0)
		{
			updateh(i+1);
		}
		else uh=1;
		updateo(); 
		if(1)
		{
			if(oready[orf]==1)
			{
				int c=islempty();
				if(c==1)
				{
					ordq();
					oqt=0;
				}
				else if(oqt==10)
				{
					oqt=0;
					orenq(1);
					ordq();
				}
			}
			else if(oready[orf]==2)
			{
				int c=ismempty();
				if(c==1)
				{
					ordq();
					oqt=0;
				}
				else if(oqt==10)
				{
					oqt=0;
					orenq(2);
					ordq();
				}
			}
			else
			{
				int c=ishempty();
				if(c==1)
				{
					ordq();
					oqt=0;
				}
				else if(oqt==10)
				{
					oqt=0;
					iqt=0;
					hrenq(hready[hrf]);
					hrdq();
					orenq(3);
					ordq();
				}
			}
	
		}
	}
	printf("Gantt Chart\n");
	for(int i=0;i<tt;i++)
	{
		printf("%d\t",chart[i]);
	}
	WtTat(chart,pc,tt);
}
int main()
{
	printf("Enter total no of processes\n");
	scanf("%d",&n);
	struct info p[n],pc[n];
	printf("Enter The processes one by one with pid followed by at,bt,priority\n");
	for(int i=0;i<n;i++)
	{
		scanf("%d%d%d%d",&p[i].p_id,&p[i].at,&p[i].bt,&p[i].priority);
	}
	struct info *pc1[n];
	for(int i=0;i<n;i++)
	{
		pc[i]=p[i];
		pc1[i]=&pc[i];
	}
	sort(pc1,n);
	mlq(p);
	sort(q1,l);
	sort(q2,m);
	sort(q3,h);
	gantt(pc);
	return 0;
}

