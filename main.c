#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <string.h>


typedef struct node_t
{
        int data;
        struct node_t *next;
}node;

void add_itm(node **head, node **last, int i)
{       
        *head = malloc(sizeof(node)); 
        (*head)->data = i;
        (*head)->next = NULL;
        *last = *head;
}

char* gbs(int a){
        char* str = malloc(sizeof(char) * 10);
        if (a == 0)
        {
                strcpy(str, "0");
                return str;
        }
        strcpy(str, "");
        int pos;
        for(pos = sizeof(int) * 8 -1; (a >> pos) == 0; pos--){}
        for(; pos>=0; pos--){
                int b = a >> pos;
                if (b == 1)
                {
                        strcat(str, "1");
                        a -= 1<<pos;
                }
                else
                {
                        strcat(str, "0");
                }
                
        }
        return str;
}

#define add_itm(item)\
if(head == NULL){add_itm(&head, &last, (item));}\
else{add_itm(&(last->next), &last, (item));}

#define CTRL(A) (A & 037)
#define DELL_KEY 127
#define ENTER_KEY 10

int main(int argc, char const *argv[])
{       
        initscr();
        noecho();
        raw();
        mvprintw(getmaxy(stdscr)-2,0, "Input binary number please...");
        mvprintw(getmaxy(stdscr)-1,0, "Ctrl+D or Enter to confirm; Ctrl+C to iterupt!");
        move(0, 0);
        refresh();
        node *head = NULL;
        node *last = head;
        int a = 0, c, count = 0;
        while (1)
        {       
                c = getch();
                // if (c != CTRL('c') & c != CTRL('d') 
                // & c != DELL_KEY & c != '1' & c != '0' 
                // & c != ' ' & c != ENTER_KEY)
                // {
                //         continue;
                // }
                if (c == CTRL('c'))
                {
                        endwin();
                        exit(1);
                }
                if (c == '1' | c == '0')
                {
                        addch(c);
                        refresh();
                        a<<=1;
                        a += (c == '1')? 1 : 0;
                }
                if (c == DELL_KEY) 
                {       
                        int x,y;
                        for (getyx(stdscr, y, x);;)
                        {
                                move(y,x-1);
                                break;
                        }
                        delch();
                        a >>= 1;
                        refresh();
                }
                
                if (c == ' ' | c == CTRL('d') | c == ENTER_KEY)
                {
                        addch(' ');
                        refresh();
                        add_itm(a);
                        a = 0;
                }
                if (c == CTRL('d') | c == ENTER_KEY)
                {
                        break;
                }
        }
        move(getmaxy(stdscr)-1,0);
        printw("Enter to exit; Ctrl+C to iterupt!");
        move(0,0);
        clrtoeol();
        printw("%8s,%8s", "bin", "dec");
        

        node *tmp = head;
        do
        {       printw("\n%8s%9d", gbs(tmp->data), tmp->data);
                tmp = tmp->next;
        }
        while(tmp != NULL); 
        refresh(); 
        for (c = getch(); c != CTRL('c') & c != ENTER_KEY; c = getch()){}  
        if (c == CTRL('c'))
        {       
                endwin();
                exit(1);
        }
        if (c == ENTER_KEY)
        {
                endwin();
                exit(0);
        }
        return 0;
}
