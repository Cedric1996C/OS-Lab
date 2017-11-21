#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
#include<semaphore.h>
#include<stdlib.h>
#include"Scheduling.h"

typedef struct threadinfo{
	pid_t *pdin;
	pid_t *pdout;
	sem_t sem0;
	sem_t sem1;
	char order[6];
	char state[5];
	int pidn;
}tinfo;	

void thread_fread(tinfo *info);
void thread_fwrite(tinfo *info);
void thread_fwrite_inelevator(tinfo *info);
int main(){
	pid_t pid[4];
	int ret[8];
	int pd[8][2];
	for(int i=0;i<8;i++){
                ret[i]=pipe(pd[i]);
                if(ret[i]<0){
                        printf("pipe create error!\n");
			return 0;
		}
	}


	if(pid[0]=fork()==0){

		tinfo info;
		sem_init(&info.sem0,0,1);
		sem_init(&info.sem1,0,0);
		info.pdin=pd[0];
		info.pdout=pd[4];
		info.state[0]='1';
		info.state[1]='1';
		info.pidn=0;
		pthread_t id[2];
		close(pd[0][1]);
		close(pd[4][0]);
		
		pthread_create(&id[0],NULL,(void*)thread_fread,(void*)&info);
		pthread_create(&id[1],NULL,(void*)thread_fwrite,(void*)&info);
		pthread_join(id[0],NULL);
		pthread_join(id[1],NULL);

		exit(0);
	}
	else{

		if(pid[1]=fork()==0){

			tinfo info;
			sem_init(&info.sem0,0,1);
			sem_init(&info.sem1,0,0);
			info.pdin=pd[1];
			info.pdout=pd[5];
			info.state[0]='1';
			info.state[1]='1';
			info.pidn=1;
			pthread_t id[2];
			close(pd[1][1]);
			close(pd[5][0]);

			pthread_create(&id[0],NULL,(void*)thread_fread,(void*)&info);
			pthread_create(&id[1],NULL,(void*)thread_fwrite,(void*)&info);
			pthread_join(id[0],NULL);
			pthread_join(id[1],NULL);

			exit(0);
		}
		else{

			if(pid[2]=fork()==0){

				tinfo info;
				sem_init(&info.sem0,0,1);
				sem_init(&info.sem1,0,0);
				info.pdin=pd[2];
				info.pdout=pd[6];
				info.state[0]='1';
				info.state[1]='1';
				info.pidn=2;
				pthread_t id[2];
				close(pd[2][1]);
				close(pd[6][0]);

				pthread_create(&id[0],NULL,(void*)thread_fread,(void*)&info);
				pthread_create(&id[1],NULL,(void*)thread_fwrite,(void*)&info);
				pthread_join(id[0],NULL);
				pthread_join(id[1],NULL);

				exit(0);
			}
	else{
				if(pid[3]=fork()==0){
                    tinfo info;
					int j;
					sem_init(&info.sem0,0,1);
					sem_init(&info.sem1,0,0);
					info.pdin=pd[3];
					info.pdout=pd[7];
                  for(j=0;j<5;j++){
				      info.state[j]='1';
				  }
				  info.pidn=3;
                pthread_t id[2];
				close(pd[3][1]);// only can read
				close(pd[7][0]);//only can write
	pthread_create(&id[0],NULL,(void*)thread_fread,(void *)&info);
	pthread_create(&id[1],NULL,(void*)thread_fwrite_inelevator,(void *)&info);
	                 pthread_join(id[0],NULL);
					 pthread_join(id[1],NULL);
					  exit(0);
				}
				else{
					int button[11];//按钮状态
					char order[12];//输入状态
					char state[5]={"1.01"};//前三位为电梯位置，后三位为电梯状态
					double double_state[2];//0为电梯位置，1为电梯状态

					for(int i=0;i<11;i++)button[i]=0;

					for(int i=0;i<4;i++){
						close(pd[i][0]);
						close(pd[i+4][1]);
					}
					while(1){
						for(int i=0;i<3;i++){
							//sleep(1);
							write(pd[i][1],state,4);	
							read(pd[i+4][0],order+2*i,2);
						}
						write(pd[3][1],state,4);	
						read(pd[7][0],order+6,6);
						//电梯内控制面板写完后注释

						for(int i=0;i<11;i++){
							if(order[i]=='1'){
								button[i]=(button[i]==1)?0:1;
							}
						}

						for(int i=0;i<11;i++)printf("%d",button[i]);
						printf("\n");
						/*double_state[0]=state[0]-'0'+(double)(state[2]-'0')/10;					
						double_state[1]=state[3]-'0';*/
						scheduling(button);
						double door=get_door();
						printf("%f\n",door);
						double_state[0]=get_locate()+1.0;
						double_state[1]=get_state();
						//电梯调度算法,参数为button[11](按钮状态)和double_state[2](电梯状态)

						
						state[0]=(int)(double_state[0])+'0';
						state[2]=(int)(double_state[0]*10)%10 +'0';
						state[3]=(int)(double_state[1])+'0';

						for(int i=0;i<11;i++)printf("%d",button[i]);
						printf("\n");
					}
					
					//printf("%s\n",strerror(errno));


				}
			}
		}
	}
}
void thread_fread(tinfo *info){
	tinfo *v=(tinfo*)info;
	while(1){
		
		sem_wait(&v->sem0);		
		read(v->pdin[0],v->state,4);
		if(v->pidn==0)printf("state:%s\n",v->state);		
		sem_post(&v->sem1);
	}
}
void thread_fwrite(tinfo *info){
	tinfo *v=(tinfo*)info;
	while(1){
	   
		  sem_wait(&v->sem1);
		 
		printf("floor%d operation:",v->pidn);
		scanf("%s",v->order);
		write(v->pdout[1],v->order,2);
		
		sem_post(&v->sem0);
		}      
}
void thread_fwrite_inelevator(tinfo *info){
    tinfo *v=(tinfo*)info;
	while(1){
	    sem_wait(&v->sem1);
		printf("Elevator interior%d opration:",v->pidn);
		scanf("%s",v->order);
		write(v->pdout[1],v->order,6);
	    sem_post(&v->sem0);
	}
}
