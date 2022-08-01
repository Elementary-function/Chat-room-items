/*
 * is_login.c
 *
 *  Created on: 2011-7-27
 *      Author: 
 */ 

#include "../../include/myhead.h" 

/*函数作用：检测用户是否登录了
 *输入：登录链表头指针first，需要检测的用户名username
 *输出：
 *返回值: 已登录返回1，没有登录返回0
 */
int is_login(LNode * first, char *username)
{
    LNode *p = first->next;
    while (p != NULL)
    {
        if (strcmp(username, p->user) == 0)
            return 1;
        p = p->next;
    }
    return 0;
}
