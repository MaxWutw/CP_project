#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define LINE "----------------------------\n"
#define ASK "請輸入你的選擇: "

struct _ListHead {

    int32_t size;
    struct _ListNode *p_head;
};

struct _ListNode {

    int32_t mark;
    char info[1024];

    struct _ListNode *p_next1;
    struct _ListNode *p_next2;
    struct _ListNode *p_next3;
};

typedef struct _ListHead ListHead;
typedef struct _ListNode ListNode;

ListNode *find_mark(ListNode *node, int32_t mark) {
    if (node == NULL) {
        return NULL; // 未找到或已達列表結尾
    }
    if (node->mark == mark) {
        return node; // 找到目標
    }
    ListNode *found = find_mark(node->p_next1, mark);
    if (found != NULL) return found; // 在 p_next1 中找到
    found = find_mark(node->p_next2, mark);
    if (found != NULL) return found; // 在 p_next2 中找到
    return find_mark(node->p_next3, mark); // 返回 p_next3 的結果
}

int32_t add_script( ListNode *p_head , int32_t prev_mark , int32_t next_num , char *s , int32_t new_mark ) {

    ListNode *p_find = find_mark( p_head , prev_mark );
    ListNode *p_new = calloc( 1 , sizeof( ListNode ) );

    strcpy( p_new -> info , s );
    p_new -> mark = new_mark;
    p_new -> p_next1 = NULL;
    p_new -> p_next2 = NULL;
    p_new -> p_next3 = NULL;

    switch( next_num ) {
        case 1:
            p_find -> p_next1 = p_new;
            break;
        case 2:
            p_find -> p_next2 = p_new;
            break;
        case 3:
            p_find -> p_next3 = p_new;
            break;
        default:
            return -1;
            break;
    }

    return 0;
}

int main() {

    ListNode story;
    
    strcpy( story.info , "請幫林小其選擇出生家庭\n\n1.富裕\n2.清寒\n3.單親\n" LINE ASK);
    story.mark = 0;
    story.p_next1 = NULL;
    story.p_next2 = NULL;
    story.p_next3 = NULL;

    add_script( &story , 0 , 1 , "他家境富裕，而他選擇\n\n1.每天玩樂\n2.認真讀書\n3.拿錢去把妹\n" LINE ASK , 1);
    add_script( &story , 0 , 2 , "他家境平困，但他選擇\n\n1.每天混\n2.認真讀書\n3.去把妹\n" LINE ASK , 2);
    add_script( &story , 0 , 3 , "他媽努力賺錢養他，而他選擇\n\n1.每天玩樂\n2.認真讀書\n3.拿錢去把妹\n" LINE ASK , 3);

    add_script( &story , 1 , 1 , "他父母病了，他選擇\n\n1.繼續玩樂\n2.在醫院陪著父母\n3.去尋找仙丹\n" LINE ASK , 4);
    add_script( &story , 1 , 2 , "他父母病了，他選擇\n\n1.繼續讀書\n2.在醫院陪著父母\n3.去尋找仙丹\n" LINE ASK , 5);
    add_script( &story , 1 , 3 , "他父母病了，他選擇\n\n1.繼續把妹\n2.在醫院陪著父母\n3.去尋找仙丹\n" LINE ASK , 6);

    add_script( &story , 2 , 1 , "他父母病了，他選擇\n\n1.繼續混\n2.在醫院陪著父母\n3.去尋找仙丹\n" LINE ASK , 7);
    add_script( &story , 2 , 2 , "他父母病了，他選擇\n\n1.繼續讀書\n2.在醫院陪著父母\n3.去尋找仙丹\n" LINE ASK , 8);
    add_script( &story , 2 , 3 , "他父母病了，他選擇\n\n1.繼續把妹\n2.在醫院陪著父母\n3.去尋找仙丹\n" LINE ASK , 9);

    add_script( &story , 3 , 1 , "他母親病了，他選擇\n\n1.繼續玩樂\n2.在醫院陪著父母\n3.去尋找仙丹\n" LINE ASK , 10);
    add_script( &story , 3 , 2 , "他母親病了，他選擇\n\n1.繼續讀書\n2.在醫院陪著父母\n3.去尋找仙丹\n" LINE ASK , 11);
    add_script( &story , 3 , 3 , "他母親病了，他選擇\n\n1.繼續把妹\n2.在醫院陪著父母\n3.去尋找仙丹\n" LINE ASK , 12);

    add_script( &story , 4 , 1 , "遊戲結束\n他父母死了，但他獲得一筆龐大的資產\n" , 13);
    add_script( &story , 4 , 2 , "遊戲結束\n感謝小其的陪伴，他父母病情好轉\n" , 14);
    add_script( &story , 4 , 3 , "遊戲結束\n小其沒找到仙丹，他父母死了\n" , 15);

    add_script( &story , 5 , 1 , "遊戲結束\n他父母死了，但他獲得一筆龐大的資產\n" , 13);
    add_script( &story , 5 , 2 , "遊戲結束\n感謝小其的陪伴，他父母病情好轉\n" , 14);
    add_script( &story , 5 , 3 , "遊戲結束\n小其沒找到仙丹，他父母死了\n" , 15);

    add_script( &story , 6 , 1 , "遊戲結束\n他父母死了，但他獲得一筆龐大的資產\n" , 13);
    add_script( &story , 6 , 2 , "遊戲結束\n感謝小其的陪伴，他父母病情好轉\n" , 14);
    add_script( &story , 6 , 3 , "遊戲結束\n小其沒找到仙丹，他父母死了\n" , 15);
    
    add_script( &story , 7 , 1 , "遊戲結束\n他用他讀書得到的獎學金幫父母付醫藥費，父母健康出院，謝謝小其\n" , 16);
    add_script( &story , 7 , 2 , "遊戲結束\n他們因為沒錢，小其眼睜睜看著父母離去...\n" , 17);
    add_script( &story , 7 , 3 , "遊戲結束\n小其沒找到仙丹，他父母死了\n" , 18);

    add_script( &story , 8 , 1 , "遊戲結束\n他用他讀書得到的獎學金幫父母付醫藥費，父母健康出院，謝謝小其\n" , 19);
    add_script( &story , 8 , 2 , "遊戲結束\n他們因為沒錢，小其眼睜睜看著父母離去...\n" , 20);
    add_script( &story , 8 , 3 , "遊戲結束\n小其沒找到仙丹，他父母死了\n" , 21);

    add_script( &story , 9 , 1 , "遊戲結束\n他用他讀書得到的獎學金幫父母付醫藥費，父母健康出院，謝謝小其\n" , 22);
    add_script( &story , 9 , 2 , "遊戲結束\n他們因為沒錢，小其眼睜睜看著父母離去...\n" , 23);
    add_script( &story , 9 , 3 , "遊戲結束\n小其沒找到仙丹，他父母死了\n" , 24);

    add_script( &story , 10 , 1 , "遊戲結束\n小其搞大了女生的肚子，父母直接氣死\n" , 25);
    add_script( &story , 10 , 2 , "遊戲結束\n他突然不理他的妹子，女方氣得拿刀砍他全家...\n" , 26);
    add_script( &story , 10 , 3 , "遊戲結束\n小其發現他女友其實是女巫的後裔，成功獲得姐要拯救父母\n" , 27);

    add_script( &story , 11 , 1 , "遊戲結束\n小其搞大了女生的肚子，父母直接氣死\n" , 28);
    add_script( &story , 11 , 2 , "遊戲結束\n他突然不理他的妹子，女方氣得拿刀砍他全家...\n" , 29);
    add_script( &story , 11 , 3 , "遊戲結束\n小其發現他女友其實是女巫的後裔，成功獲得姐要拯救父母\n" , 30);

    add_script( &story , 12 , 1 , "遊戲結束\n小其搞大了女生的肚子，父母直接氣死\n" , 31);
    add_script( &story , 12 , 2 , "遊戲結束\n他突然不理他的妹子，女方氣得拿刀砍他全家...\n" , 32);
    add_script( &story , 12 , 3 , "遊戲結束\n小其發現他女友其實是女巫的後裔，成功獲得姐要拯救父母\n" , 33);




    // 主程式

    ListNode *p_going = &story;
    int32_t choose = 0;
    system("clear");

    while(1) {

        puts( p_going -> info );

        if( p_going -> p_next1 == NULL && 
            p_going -> p_next2 == NULL &&
            p_going -> p_next3 == NULL    ) 
        {

            break;
        }

        choose = 0;

        scanf("%d", &choose);

        switch (choose) {
        case 1:
            p_going = p_going -> p_next1;
            break;
        case 2:
            p_going = p_going -> p_next2;
            break;
        case 3:
            p_going = p_going -> p_next3;
            break;
        default:
            printf("error\n");
            break;
        }

        system("clear");

    }

    return 0;
}
