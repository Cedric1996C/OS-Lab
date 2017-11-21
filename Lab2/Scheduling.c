#ifndef SCHEDULING
#define SCHEDULING
#include <stdio.h>
// #include <math.h>
#include <time.h>
#include <stdlib.h>

//head
#include "Scheduling.h"

int scheduling(int button[]);
double get_locate();
double get_door();
double get_speed();
//data_of_time
clock_t last_op=0;
const double freq=5.0;//set the freq of opration
int need_op();

//data_of_button
int floor_button[3][2];
int inner_order[3];
int inner_door_close;
int inner_door_open;
int button_aval=0;
void button_input(int button[]);
void button_output(int button[]);

//data_of_door
int door=0;//当前门的状态:closed-0-100-opened
const int door_max_speed=35;
const double door_close_delay=3.0;
double door_timer=0;//关门倒计时
clock_t last_time;
int door_lock=0;
int now_aim=0;//当前目标楼层
int next_door();
int open_door();//only called by next_door() in general
int close_door();//only called by next_door() in general

//data_of_location
int location=0;//当前位置:[0-100-200]
int speed=0;
const int max_speed=30;
int ori=0;//本次运行方向,0up,1down
int next_op();

int scheduling(int button[])
{
    /*if(need_op()==0)
    {
        return 0;//无操作
    }*/
    button_input(button);
    int flag=next_op();
    if(flag>0)
    {
        button_output(button);
        return flag;//成功的操作
    }
    return -1;//令人窒息的操作
}
double get_locate()
{
    return 1.0L*location/100;
}
double get_door()
{
    return 1.0L*door/100;
}
double get_speed()
{
    if(ori==1)
    {
        return -1.0L*freq*speed/100;
    }
    else
    {
        return 1.0L*freq*speed/100;
    }
}
int get_state()
{
    int flag=0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if(floor_button[i][j])
            {
                flag=1;
            }
        }
        if(inner_order[i])
        {
            flag=1;
        }
    }
    if(flag!=0||speed!=0)
    {
        if(ori==0)
            return 2;
        else
            return 0;
    }
    else
    {
        return 1;
    }
}
int next_op()
{
    if(next_door()!=0)
    {
        return 1;
    }
    if(ori==0)//电梯上行
    {
        int least_stop=(location+speed)/100;
        // printf("???%d\n",(location+speed)%100);
        if((location+speed)%100!=0)
            least_stop++;
        // printf("least_stop:%d  location:%d  speed:%d\n",least_stop,location,speed);
        now_aim=-1;
        for (int i = least_stop; i < 3; i++)
        {
            if(floor_button[i][0]||inner_order[i])
            {
                now_aim=i;
                break;
            }
        }
        // printf("%d!!!%d!!!%d\n",now_aim,location,speed);
        if(now_aim<0)//没有上行订单，检查接人订单
        {
            for (int i = 2; i > least_stop; i--)
            {
                if(floor_button[i][1])
                {
                    now_aim=i;
                    break;
                }
            }
        }
        if(now_aim<0&&location%100==0&&speed==0)//没有任何订单且停稳
        {
            ori=1;//改变look方向
            return 1;
        }
        if(now_aim<0)//没有订单但未停稳，设定目标为下一可停层
            now_aim=least_stop;
        int diff=100*now_aim-location;
        if(diff>2*speed+(int)(0.3*max_speed))
        {
            location+=speed;
            speed+=(int)(0.3*max_speed);
            if(speed>max_speed)
                speed=max_speed;
        }
        else
        {
            location+=speed;
            speed=(diff-speed)-(diff-speed)/2;
            if(location>now_aim*100)
            {
                location=now_aim*100;
                speed=0;
            }
        }
        return 1;
    }
    else//电梯下行
    {
        int least_stop=(location-speed)/100;
        // printf("least_stop:%d  location:%d  speed:%d\n",least_stop,location,speed);
        now_aim=-1;
        for (int i = least_stop; i >= 0; i--)
        {
            if(floor_button[i][1]||inner_order[i])
            {
                now_aim=i;
                break;
            }
        }
        // printf("%d!!!%d!!!%d\n",now_aim,location,speed);
        if(now_aim<0)//没有下行订单，检查接人订单
        {
            for (int i = 0; i < least_stop; i++)
            {
                if(floor_button[i][0])
                {
                    now_aim=i;
                    break;
                }
            }
        }
        if(now_aim<0&&location%100==0&&speed==0)//没有任何订单且停稳
        {
            ori=0;//改变look方向
            return 1;
        }
        if(now_aim<0)//没有订单但未停稳，设定目标为下一可停层
            now_aim=least_stop;
        int diff=location-100*now_aim;
        if(diff>2*speed+(int)(0.3*max_speed))
        {
            location-=speed;
            speed+=(int)(0.3*max_speed);
            if(speed>max_speed)
                speed=max_speed;
        }
        else
        {
            location-=speed;
            speed=(diff-speed)-(diff-speed)/2;
            if(location>now_aim*100)
            {
                location=now_aim*100;
                speed=0;
            }
        }
        return 1;
    }
}
int open_door()
{
    if(location%100!=0||speed!=0)
    {
        inner_door_open=0;
        inner_door_close=0;
        return 0;
    }
    else if(floor_button[location/100][ori]||inner_order[location/100]||inner_door_open)
    {
        door_lock=1;
        door_timer=door_close_delay;
        last_time=clock();
        floor_button[location/100][ori]=0;
        inner_order[location/100]=0;
        inner_door_open=0;
        return 1;
    }
    return 0;
}
int close_door()
{
    if(inner_door_close)
    {
        inner_door_close=0;
        door_timer=0;
        return 1;
    }
    return 0;
}
int next_door()
{
    close_door();
    open_door();
    if(door_lock==1)
    {
        door=door+door_max_speed;
        if(door>=100)
        {
            door=100;
            door_lock=0;
        }
    }
    else
    {
        if(door_timer<=0)
        {
            if(door==0)
            {
                return 0;//可行态
            }
            else
            {
                door-=door_max_speed;
                if(door<0)
                {
                    door=0;
                    door_lock=0;
                }
            }
        }
        else
        {
            //clock_t now=clock();
            //if(now>last_time)
            //{
            //door_timer-=1.0L*(now-last_time)/CLOCKS_PER_SEC;
            //}
            door_timer-=1.0;
        }
    }
    return 1;//忙
}
void button_input(int button[])
{
    floor_button[0][0]=button[FLOOR_1U]||button[FLOOR_1D];
    floor_button[0][1]=button[FLOOR_1D]||button[FLOOR_1U];
    floor_button[1][0]=button[FLOOR_2U];
    floor_button[1][1]=button[FLOOR_2D];
    floor_button[2][0]=button[FLOOR_3U]||button[FLOOR_3D];
    floor_button[2][1]=button[FLOOR_3D]||button[FLOOR_3U];
    inner_order[0]=button[INNER_1];
    inner_order[1]=button[INNER_2];
    inner_order[2]=button[INNER_3];
    inner_door_close=button[INNER_CLOSE];
    inner_door_open=button[INNER_OPEN];
    button_aval=1;
}
void button_output(int button[])
{
    if(button_aval==0)
        return;
    button_aval=0;
    button[FLOOR_1U]=floor_button[0][0]&&floor_button[0][1];
    button[FLOOR_1D]=floor_button[0][1]&&floor_button[0][0];
    button[FLOOR_2U]=floor_button[1][0];
    button[FLOOR_2D]=floor_button[1][1];
    button[FLOOR_3U]=floor_button[2][0]&&floor_button[2][1];
    button[FLOOR_3D]=floor_button[2][1]&&floor_button[2][0];
    button[INNER_1]=inner_order[0];
    button[INNER_2]=inner_order[1];
    button[INNER_3]=inner_order[2];
    button[INNER_CLOSE]=inner_door_close;
    button[INNER_OPEN]=inner_door_open;
}
int need_op()
{
    clock_t now=clock();
    if(1.0L/(now-last_op)*CLOCKS_PER_SEC<=freq||now<last_op)
    {
        last_op=now;
        return 1;
    }
    return 0;
}
#endif
/*int main()
{
    int test[11];
    srand(clock()*10000+clock());
    for (int i = 0; i < 11; i++)
    {
        test[i]=rand()%1000>500?1:0;
    }
    while(1)
    {
        int flag=scheduling(test);
        if (flag)
        {
            printf("%f\t%f\t%f\t%d\n",get_locate(),get_speed(),get_door(),get_state());
            for (int i = 0; i < 11; i++)
            {
                printf("%d ",test[i]);
            }
            printf("\n");
            // printf("%d %lf\n\n",ori,door_timer);
            if(rand()%1000>=980)
            {
                test[rand()%11]=1;
            }
        }
    }
    return 0;
}*/
