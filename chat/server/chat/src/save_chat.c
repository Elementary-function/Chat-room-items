/*
 *  save_chat.c
 *
 *  Created on: 2011-7-27
 *      Author: 
 */ 

#include "../../include/myhead.h" 

/*函数作用：服务器端保存用户聊天信息
 *输入：客户端聊天信息字符串buffer
 *输出：保存聊天记录在history文件中
 *返回值: 成功返回0
 */
int Save_data(char *buffer)
{
    FILE *fp;
    fp = fopen("history.txt", "a+"); /* 聊天日志保存在当前目录下的history.txt文件中 */
    strcat(buffer, "\n");
    fwrite(buffer, strlen(buffer), 1, fp);
    fclose(fp);
    bzero(buffer, strlen(buffer));
    return 0;
}
