extern int scheduling(int button[]);
extern double get_locate();//用于得到当前层数：0-1-2
extern double get_door();//用于得到当前门的状态，1-完全开启，0-完全关闭
extern double get_speed();//用于得到当前轿厢的速度，向上为正,层/秒
extern int get_state();//得到当前状态：0-下行,不论速度，1-无请求-静止，2-上行，不论速度
#ifndef BUTTON_SYM
#define BUTTON_SYM
#define FLOOR_1U 0
#define FLOOR_1D 1
#define FLOOR_2U 2
#define FLOOR_2D 3
#define FLOOR_3U 4
#define FLOOR_3D 5
#define INNER_1 6
#define INNER_2 7
#define INNER_3 8
#define INNER_CLOSE 9
#define INNER_OPEN 10
#endif
