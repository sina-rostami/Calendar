#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include<ctype.h>

typedef struct task Task;
typedef struct event Event;
typedef struct day Day;
struct task{
    char title[20];
    char description[50];
    int done;
    struct task *next;
    Day *day_for_move[5];
};
struct event{
    char title[20];
    char description[50];
    struct event *next;
    Day *day_for_move[5];
};
struct day{
    int day;
    char day_name[8];
    int month;
    Task *task;
    Event *event;
    Day *next;
    Day *prev;
};
void menu(Day *day);
void Calendar(Day *d);
void Search();
char *DayName(int n);
void DaysInitialize(Day day[]);
int get_ToDay();
void CraeteNewTask(Day *day);
void CraeteNewEvent(Day *day);
void PrintDay(Day *day);
int PrintEvents(Day *day);
int PrintTasks(Day *day);
void PrintEventOrTaskPage(Day *day, int type, Task *task, Event *event);
int DayNum(int month, int day);
void PrintTimedout(Day *d, Day day[]);
void SearchinTaskandEvent(Day day[],int type);
Day *GoToDay(Day d[]);
Day day[365];
Day *today;
int main(){
    
    DaysInitialize(day);
    today = &day[get_ToDay()-1];
    menu(today);
    return 0;
}
void menu(Day *day){
    int choose;
    system("clear");
    putchar(' ');
    for(int i = 0; i < 60; i++)
        printf("-");
    putchar('\n');
    putchar('|');
    printf("%25s%10s%25s"," ","Calendar", " ");
    putchar('|');
    putchar('\n');
    putchar('|');
    printf("%28s%5s%27s"," ","Menu", " ");
    putchar('|');
    putchar('\n');
    putchar('|');
    printf("%-60s", " ");
    putchar('|');
    putchar('\n');
    putchar('|');
    printf("    1.Go to Calendar%40s", " ");
    putchar('|');
    putchar('\n');
    putchar('|');
    printf("%-60s", " ");
    putchar('|');
    putchar('\n');
    putchar('|');
    printf("    2.Search%48s", " ");
    putchar('|');
    putchar('\n');
    putchar('|');
    printf("%-60s", " ");
    putchar('|');
    putchar('\n');
    putchar('|');
    printf("%-60s", "    3.Quit");
    putchar('|');
    putchar('\n');
    putchar('|');
    printf("%-60s", " ");
    putchar('|');
    putchar('\n');
    for(int i = 0; i < 31; i++)
        putchar('.'),putchar('_');
    putchar('\n');
    printf("Enter number of your choice and hit enter : \n");
    scanf("%d", &choose);
    switch (choose)
    {
    case 1:
        Calendar(day);
        break;
    case 2:
        Search();
        break;
    case 3:
        exit(0);
        break;
    default:
        break;
    }
}
void Calendar(Day *d){
    char choose[5];
    while(1){
        system("clear");
        PrintDay(d);
        scanf("%s", choose);
        if(!strcmp(choose , "n")){
            if(d == &day[364]){
                system("clear");
                PrintDay(d-=364);
            }
            else{
                system("clear");
                PrintDay(++d);
            }
        }
        else if(!strcmp(choose , "p")){
            if(d == &day[0]){
                system("clear");
                PrintDay(d+=364);
            }
            else{
                system("clear");
                PrintDay(--d);
            }
        } 
        else if(!strcmp(choose , "q"))//close prog
            return ;
        else if(!strcmp(choose , "m"))//go to menu
            menu(today);
        else if(!strcmp(choose , "1"))
            CraeteNewEvent(d);
        else if(!strcmp(choose , "2"))
            CraeteNewTask(d);
        else if(choose[0] == 'e' && isdigit(choose[1])){
            int num = atoi(&choose[1]);
            Event *temp = d->event;
            for(int i = 1; i < num;i++){
                temp = temp->next;
            }
            if(temp == NULL)
                    printf("Wrong!\n") ,sleep(2);
            else
                PrintEventOrTaskPage(d, 1, NULL, temp);
        }
        else if(choose[0] == 't' && isdigit(choose[1])){
            int num = atoi(&choose[1]);
            Task *temp = d->task;
            for(int i = 1; i < num;i++){
                temp = temp->next;
            }
            if(temp == NULL)
                    printf("Wrong!\n") ,sleep(2);
            else
                PrintEventOrTaskPage(d, 2, temp, NULL);
        }
    }
}
void Search(){
    int choose;
    system("clear");
    putchar(' ');
    for(int i = 0; i < 60; i++)
        printf("-");
    putchar('\n');
    printf("|%25s%10s%25s|\n"," ", "Search", " ");
    putchar(' ');
    for(int i = 0; i < 60; i++)
        putchar('=');
    putchar('\n');
    printf("|%60s|\n"," ");
    printf("|%-60s|\n"," 1.Go to Date");
    printf("|%60s|\n"," ");
    printf("|%-60s|\n"," 2.Search in Events");
    printf("|%60s|\n"," ");
    printf("|%-60s|\n"," 3.Search in Tasks");
    printf("|%60s|\n"," ");
    printf("|%-60s|\n"," 4.Search in Events and Tasks");
    printf("|%60s|\n"," ");
    printf("|%-60s|\n"," 5.Show timed out Tasks");
    printf("|%60s|\n"," ");
    printf("|%-60s|\n"," 0.Menu");
    printf("|%60s|\n"," ");
    for(int i = 0; i < 31; i++)
        putchar('.'),putchar('_');
    putchar('\n');
    printf("Enter number of your choice and hit enter key : \n");
    scanf("%d", &choose);
    switch (choose)
    {
    case 0:
        menu(today);
        break;
    case 1:
        GoToDay(day);
        break;
    case 2:
        SearchinTaskandEvent(day,1);
        break;
    case 3:
        SearchinTaskandEvent(day,2);
        break;
    case 4:
        SearchinTaskandEvent(day,3);
        break;        
    case 5:
        PrintTimedout(today , day);
        break;        
    default:
        break;
    }

}
void PrintDay(Day *day){
    time_t s, val = 1; 
    struct tm* current_time; 
    s = time(NULL);
    current_time = localtime(&s); 
    system("clear");
    putchar(' ');
    for(int i = 0; i < 52; i++)
        printf("-");
    printf("%02d:%02d:%02d", current_time->tm_hour, current_time->tm_min, current_time->tm_sec);
    putchar('\n'); 
    putchar('|');
    for(int i = 0; i < 22; i++)
        putchar(' ');
    printf("1398 / %02d / %02d", day->month, day->day);
    for(int i = 0; i < 24; i++)
        putchar(' ');
    putchar('|');
    putchar('\n');
    putchar('|');
    for(int i = 0; i < 25; i++)
        putchar(' ');
    printf("%8s", day->day_name);
    for(int i = 0; i < 27; i++)
        putchar(' ');
    putchar('|');
    putchar('\n');
    putchar(' ');
    for(int i = 0; i < 60; i++)
        putchar('=');
    putchar('\n');
    putchar('|');
    printf("Events : ");
    for(int i = 0; i < 51; i++)
        putchar(' ');
    putchar('|');
    putchar('\n');
    PrintEvents(day);
    putchar('|');
    printf("Tasks :  ");
    for(int i = 0; i < 51; i++)
        putchar(' ');
    putchar('|');
    putchar('\n');
    PrintTasks(day);
    for(int i = 0; i < 31; i++)
        putchar('.'),putchar('_');
    putchar('\n');
    printf("\n\t* Enter '1' to create new Event for this day\n");
    printf("\t* Enter '2' to create new Task for this day\n");
    printf("\t* Enter 'n' to go to next day(1398/%d/%d)\n", day->next->month, day->next->day);
    printf("\t* Enter 'p' to go to previous day(1398/%d/%d)\n", day->prev->month, day->prev->day);
    printf("\t* Enter 'e(n)' to go to n-th event page (e.g:e1)\n");
    printf("\t* Enter 't(n)' to go to n-th task page (e.g:t1)\n");
    printf("\t* Enter 'm' to return to the Menu\n");
}
int PrintEvents(Day *day){
    Event *temp = day->event;
    for(int i = 1; temp != NULL; i++){
        putchar('|');
        for(int i = 0; i < 4; i++)
            putchar(' ');
        printf("%2d-%-50s", i, temp->title);
        for(int i = 0; i < 3; i++)
            putchar(' ');
        putchar('|');
        putchar('\n');
        temp = temp -> next;
    }
}
int PrintTasks(Day *day){
    Task *temp = day->task;
    for(int i = 1; temp != NULL ; i++){
        putchar('|');
        for(int i = 0; i < 4; i++)
            putchar(' ');
        printf("%2d-%-50s", i, temp->title);
        for(int i = 0; i < 3; i++)
            putchar(' ');
        putchar('|');
        putchar('\n');
        temp = temp -> next;
    }
}
void PrintEventOrTaskPage(Day *day, int type, Task *task, Event *event){ // type : print EventPage(1) or TaskPage(2)
    system("clear");
    putchar(' ');
    for(int i = 0; i < 60; i++)
        printf("-");
    putchar('\n'); 
    putchar('|');
    for(int i = 0; i < 22; i++)
        putchar(' ');
    printf("1398 / %02d / %02d", day->month, day->day);
    for(int i = 0; i < 24; i++)
        putchar(' ');
    putchar('|');
    putchar('\n');
    putchar('|');
    for(int i = 0; i < 26; i++)
        putchar(' ');
    if(type == 1) printf("%7s", "Event");
    else if(type == 2) printf("%7s", "Task");
    for(int i = 0; i < 27; i++)
        putchar(' ');
    putchar('|');
    putchar('\n');
    putchar(' ');
    for(int i = 0; i < 60; i++)
        putchar('=');
    putchar('\n');
    putchar('|');
    printf("%-60s", " -Title :");
    putchar('|');
    putchar('\n');
    putchar('|');
    printf("%-60s", " ");
    putchar('|');
    putchar('\n');
    putchar('|');
    if(type == 1)
        printf("    *%-55s", event->title);
    else
        printf("    *%-55s", task->title);
    putchar('|');
    putchar('\n');
    putchar('|');
    printf("%-60s", " ");
    putchar('|');
    putchar('\n');
    putchar('|');
    printf("%-60s", " -Description :");
    putchar('|');
    putchar('\n');
    putchar('|');
    printf("%-60s", " ");
    putchar('|');
    putchar('\n');
    putchar('|');
    if(type == 1)
        printf("    *%-55s", event->description);
    else
        printf("    *%-55s", task->description);
    putchar('|');
    putchar('\n');
    putchar('|');
    printf("%-60s", " ");
    putchar('|');
    putchar('\n');
    putchar('|');
    printf("%-60s", " -Can Be Moved to :");
    putchar('|');
    putchar('\n');
    putchar('|');
    printf("%-60s", " ");
    putchar('|');
    putchar('\n');
    if(type == 1){
        for(int i = 0; i < 5, event->day_for_move[i] != NULL; i++){
            putchar('|');
            printf("    * 1398/%02d/%02d%44s", event->day_for_move[i]->month, event->day_for_move[i]->day, " ");
            putchar('|');
            putchar('\n');
        }
    }
    else {
        for(int i = 0; i < 5, task->day_for_move[i] != NULL; i++){
            putchar('|');
            printf("    * 1398/%02d/%02d%44s", task->day_for_move[i]->month, task->day_for_move[i]->day, " ");
            putchar('|');
            putchar('\n');
        }
    }
    putchar('|');
    printf("%-60s", " ");
    putchar('|');
    putchar('\n');
    if(type == 2){ //done
        putchar('|');
        printf("%-60s", " -Done?");
        putchar('|');
        putchar('\n');
        putchar('|');
        printf("%-60s", " ");
        putchar('|');
        putchar('\n');
        putchar('|');
            char done[4];
            if(task->done)
                strcpy(done, "YES");
            else 
                strcpy(done, "NO");
        printf("    *%-55s", done);
        putchar('|');
        putchar('\n');
    }
    putchar('|');
    printf("%-60s", " ");
    putchar('|');
    putchar('\n');
    for(int i = 0; i < 31; i++)
        putchar('.'),putchar('_');
    putchar('\n');
    printf("\n\t* Enter 'e' to edit\n");
    printf("\t* Enter 'b' to go back to the day\n");
    printf("\t* Enter 'm' to go back to the menu\n");
    if(type == 2)
        printf("\t* Enter 'd' to make task done!\n");
    char choose;
    scanf("%c", &choose);
    if(choose == 'b')
        return;
    else if(choose == 'm')
        menu(day);
    else{
        if(type == 1){
            if(choose == 'e'){
                printf("Enter new title for the event:\n");
                scanf("%20s", event->title);
                printf("Enter new description for the event:\n");
                scanf("%50s", event->description);
            }
            PrintEventOrTaskPage(day, 1, NULL,event);
        }
        else if(type == 2){
            if(choose == 'e'){
                printf("Enter new title for the task:\n");
                scanf("%20s", task->title);
                printf("Enter new description for the task:\n");
                scanf("%50s", task->description);
            }
            else if(choose == 'd'){
                task->done = 1-task->done;
            }
            PrintEventOrTaskPage(day, 2, task,NULL);
        }
    }
    
}
int get_ToDay(){
    time_t T= time(NULL);
    struct  tm tm = *localtime(&T);
    int day = tm.tm_mday;
    int month = tm.tm_mon+1;
    switch(month){
        case 1:
            if(day >= 1 && day <=20)
                day += 10, month = 10;
            else if(day > 20 && day <= 31)
                day -= 20, month = 11;
            break;
        case 2:
            if(day <= 19)
                day += 11, month = 11;
            else
                day -= 19, month = 12;
            break;
        case 3:
            if(day <= 19)
                day += 10, month = 12;
            break;
    }
    return DayNum(month, day);
}
void CraeteNewTask(Day *day){
    system("clear");
    Task *temp;
    temp = malloc(sizeof(Task));
    printf("Enter title of new Task for 1398 / %02d / %02d(maximum 20 character without spaces):\n", day->month, day->day);
    scanf("%20s", temp->title);
    printf("Enter description of new Task for 1398 / %02d / %02d(maximum 50 character without spaces):\n", day->month, day->day);
    scanf("%50s", temp->description);
    temp-> done = 0;
    temp-> next = NULL;
    if(day->task == NULL){
        day -> task = temp;
    }
    else {
        Task *prev;
        prev = day -> task;
        while(prev->next != NULL)
            prev = prev -> next;
        prev -> next = temp;
    }
    for(int i = 0; i < 5; i++)
        temp->day_for_move[i] = NULL;
    int n;
    printf("\nEnter number of days that you may change this Task's date with :\n");
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        Day *temp1 = malloc(sizeof(Day));
        system("clear");
        printf("\nEnter your date in (month day) format.(e.g: 10 13 is 13-th day of 10-th month)\n");
        scanf("%d %d", &temp1->month, &temp1->day);
        day->task->day_for_move[i] = temp1;
    }
}
void CraeteNewEvent(Day *day){
    system("clear");
    Event *temp;
    temp = malloc(sizeof(Event));
    printf("Enter title of new Event for 1398 / %02d / %02d(maximum 20 character)\n", day->month, day->day);
    scanf("%20s", temp->title);
    printf("Enter description of new Event for 1398 / %02d / %02d(maximum 50 character)\n", day->month, day->day);
    scanf("%50s", temp->description);
    temp-> next = NULL;
    if(day->event == NULL){
        day -> event = temp;
    }
    else {
        Event *prev;
        prev = day -> event;
        while(prev->next != NULL)
            prev = prev -> next;
        prev -> next = temp;
    }
    for(int i = 0; i < 5; i++)
        temp->day_for_move[i] = NULL;
    int n;
    printf("\nEnter number of days that you may change this Event's date with :\n");
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        Day *temp1 = malloc(sizeof(Day));
        system("clear");
        printf("\nEnter your date in (month day) format.(e.g: 10 13 is 13-th day of 10-th month)\n");
        scanf("%d %d", &temp1->month, &temp1->day);
        day->event->day_for_move[i] = temp1;
    }
    
}
void DaysInitialize(Day day[]){
    for(int i = 0; i < 365; i++){
        if(i == 364)
            day[i].next = &day[0];
        else
            day[i].next = &day[i+1];
        if(i == 0)
            day[i].prev = &day[364];
        else 
            day[i].prev = &day[i-1];
    }
    int cnt = 0;
    int month_days = 31;
    for(int i = 1; i <= 12; i++){
        if(i == 7)
            month_days = 30;
        else if(i == 12)
            month_days = 29;
        for(int j = 1; j <= month_days; j++){
            day[cnt].day = j;
            day[cnt].month = i;
            strcpy(day[cnt].day_name, DayName(cnt));
            day[cnt].event = NULL;
            day[cnt].task = NULL;
            cnt++;
        }
    }
}
char *DayName(int n){
    int temp = n%7;
    switch (temp)
    {
    case 0:
        return "5shanbe";
        break;
    case 1:
        return "Jome";
        break;
    case 2:
        return "shanbe";
        break;      
    case 3:
        return "1shanbe";
        break;      
    case 4:
        return "2shanbe";
        break;   
    case 5:
        return "3shanbe";
        break;   
    case 6:
        return "4shanbe";
        break;            
    }
}
int DayNum(int month, int day){
    int ans = 0;
    if(month <= 7){
        ans += (month - 1)*31;
        return ans+day;
    }
    else if(month > 7){
        ans += 186;
        month -= 7;
        ans += month*30;
        return ans+day;
    }
}
Day *GoToDay(Day d[]){
    int day_num,day_month;
    system("clear");
    printf("\nEnter your date in (month day) format.(e.g: 10 13 is 13-th day of 10-th month)\n");
    scanf("%d %d", &day_month, &day_num);
    Day *temp = &d[DayNum(day_month, day_num)-1];
    Calendar(temp);
    return temp;
}
void PrintTimedout(Day *d, Day day[]){
    int choose;
    system("clear");
    putchar(' ');
    for(int i = 0; i < 60; i++)
        printf("-");
    putchar('\n');
    printf("|%22s%16s%22s|\n"," ", "Timed out Tasks", " ");
    printf("|%60s|\n"," ");
    int cnt = 1;
    for(int i = 0; i < DayNum(d->month, d->day); i++){
        Task *temp = day[i].task;
        for( ; temp != NULL;){
            if(temp->done == 0){
                printf("|%d. 1398/%02d/%02d : %-44s|\n", cnt, day[i].month, day[i].day, temp->title);
            }
            temp = temp -> next;
        }
    }
    printf("|%60s|\n"," ");
    for(int i = 0; i < 31; i++)
        putchar('.'),putchar('_');
    putchar('\n');
    printf(" *press '0' to go back to the menu\n");
    scanf("%d", &choose);
    if(choose == 0)
        menu(d);
}
void SearchinTaskandEvent(Day day[],int type){ // 1: events |2: tasks| 3:both
    char title[20];
    int choose;
    system("clear");
    printf("Enter your search word (maximum 20 characters without spaces : \n");
    scanf("%s",title);
    system("clear");
    putchar(' ');
    for(int i = 0; i < 60; i++)
        printf("-");
    putchar('\n');
    printf("|%27s%6s%27s|\n"," ", "Tasks | Events", " ");
    printf("|%60s|\n"," ");
    int cnt = 1;
    for(int i = 0; i < 365; i++){
        Task *tempt = day[i].task;
        Event *tempe = day[i].event;
        if(type == 2 || type == 3){
            for( ; tempt != NULL; tempt = tempt -> next ){
                if(!strcmp(tempt->title, title)){
                    printf("|%02d. Task :  1398/%02d/%02d : %-35s|\n", cnt, day[i].month, day[i].day, tempt->title);
                    cnt++;
                }
            }
        }
        if(type == 1 || type == 3){
            for( ; tempe != NULL; tempe = tempe -> next ){
                if(!strcmp(tempe->title, title)){
                    printf("|%02d. Event :  1398/%02d/%02d : %-34s|\n", cnt, day[i].month, day[i].day, tempe->title);
                    cnt++;
                }
            }
        }
    }
    printf("|%60s|\n"," ");
    for(int i = 0; i < 31; i++)
        putchar('.'),putchar('_');
    putchar('\n');
    printf(" *press '0' to go back to the menu\n");
    scanf("%d", &choose);
    if(choose == 0)
        menu(today);
}