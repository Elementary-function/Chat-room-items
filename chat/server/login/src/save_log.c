/*
 * save_log.c
 *
 *  Created on: 2011-7-27
 *      Author: 
 */ 

#include "../../include/myhead.h" 

/*函数作用：服务器端记录用户登录星系
 *输入：登录信息字符串log
 *输出：保存在dialog文件
 *返回值: 成功返回0
 */
int Save_log(char *log)
{
    FILE *fp;
    fp = fopen("dialog.txt", "a+"); /* 登录日志保存在当前目录下的dialog.txt文件中 */
    fwrite(log, strlen(log), 1, fp);
    fclose(fp);
    bzero(log, strlen(log));
    return 0;
}
 
