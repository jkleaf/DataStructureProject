#include <stdio.h>
#include <windows.h>
void color(short x)    
{  
    if(x>=0 && x<=15)  
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);       
    else
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);  
}  
void drawMenu1(){ 
	color(15);printf("                                 ～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～ ·～\n");
	color(15);printf("                                 ～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～ ·～\n");
	color(15);printf("                                 **                                                                                                                                                               **\n");
	color(15);printf("                                 **                ");color(12);printf("   ***************                                                                                           ***************                   ");color(15);printf("**\n");
	color(15);printf("                                 **                ");color(12);printf("  **      *      **                                                                                         **      *      **                  ");color(15);printf("**\n");
	color(15);printf("                                 **                ");color(12);printf("   **    ***    **                                                                                           **    ***    **                   ");color(15);printf("**\n");																						
	color(15);printf("                                 **                ");color(12);printf("  **      *      **                                                                                         **      *      **                  ");color(15);printf("**\n");
	color(15);printf("                                 **                ");color(12);printf(" **   *********   **                                                                                       **   *********   **                 ");color(15);printf("**\n");
	color(15);printf("                                 **                ");color(12);printf("********  *  ********                  ");color(11);printf("－－－－－－－－－－－－－－－－－－－－－－－－ ");color(12);printf("                  ********  *  ********                ");color(15);printf("**\n");
	color(15);printf("                                 **                ");color(12);printf("        * * *                          ");color(11);printf("|             您已进入选择菜单                  |");color(12);printf("                          * * *                        ");color(15);printf("**\n");
	color(15);printf("                                 **                ");color(12);printf("         * *                           ");color(11);printf("|                                               |");color(12);printf("                           * *                         ");color(15);printf("**\n");
	color(15);printf("                                 **                ");color(12);printf("          *                            ");color(11);printf("| 0.修改商品售价			          |");color(12);printf("                            *                          ");color(15);printf("**\n");
	color(15);printf("                                 **                ");color(10);printf("         ***                           ");color(11);printf("|                                               |");color(10);printf("                           ***                         ");color(15);printf("**\n");
	color(15);printf("                                 **                ");color(10);printf("      ********                         ");color(11);printf("|                                               |");color(10);printf("                         ********                      ");color(15);printf("**\n");
 	color(15);printf("                                 **                ");color(10);printf("    ************                       ");color(11);printf("| 1：输入商品销售数据(利用商品编码进行选择)     |");color(10);printf("   	                  ************                    ");color(15);printf("**\n");
	color(15);printf("                                 **                ");color(10);printf("  ****************                     ");color(11);printf("|                                               |");color(10);printf("                     ****************                  ");color(15);printf("**\n");
	color(15);printf("                                 **                ");color(10);printf("********************                   ");color(11);printf("|                                               |");color(10);printf("                   ********************                ");color(15);printf("**\n");
	color(15);printf("                                 **              ");color(10);printf("************************                 ");color(11);printf("| 2：输入商品销售数据(利用商品名称进行选择)     |");color(10);printf("                 ************************              ");color(15);printf("**\n");
	color(15);printf("                                 **            ");color(10);printf("****************************               ");color(11);printf("|                                               |");color(10);printf("               ****************************            ");color(15);printf("**\n");
	color(15);printf("                                 **                ");color(10);printf("        ******                         ");color(11);printf("|                                               |");color(10);printf("                         ******                        ");color(15);printf("**\n");
	color(15);printf("                                 **                ");color(10);printf("        ******                         ");color(11);printf("| 3：增添或删除商品信息                         |");color(10);printf("                         ******                        ");color(15);printf("**\n");
	color(15);printf("                                 **           ");color(10);printf("********************************            ");color(11);printf("|                                               |");color(10);printf("             *******************************           ");color(15);printf("**\n");
	color(15);printf("                                 **         ");color(10);printf("************************************          ");color(11);printf("|                                               |");color(10);printf("          ************************************         ");color(15);printf("**\n");
	color(15);printf("                                 **       ");color(10);printf("****************************************        ");color(11);printf("| 4：计算销售总额及库存                         |");color(10);printf("        ****************************************       ");color(15);printf("**\n");
	color(15);printf("                                 **     ");color(10);printf("********************************************      ");color(11);printf("|                                               |");color(10);printf("      ********************************************     ");color(15);printf("**\n");
	color(15);printf("                                 **                ");color(10);printf("        ******                         ");color(11);printf("|                                               |");color(10);printf("                         ******                        ");color(15);printf("**\n");
	color(15);printf("                                 **                ");color(10);printf("        ******                         ");color(11);printf("| 5：输出商品列表信息                           |");color(10);printf("                         ******                        ");color(15);printf("**\n");
	color(15);printf("                                 **                ");color(10);printf("        ******                         ");color(11);printf("|                                               |");color(10);printf("                         ******                        ");color(15);printf("**\n");
	color(15);printf("                                 **                ");color(10);printf("        ******                         ");color(11);printf("|                                               |");color(10);printf("                         ******                        ");color(15);printf("**\n");
	color(15);printf("                                 **           ");color(10);printf("********************************            ");color(11);printf("| 6：查找销售商品销售情况                       |");color(10);printf("             ********************************          ");color(15);printf("**\n");
	color(15);printf("                                 **         ");color(10);printf("************************************          ");color(11);printf("|                                               |");color(10);printf("           ************************************        ");color(15);printf("**\n");
	color(15);printf("                                 **       ");color(10);printf("****************************************        ");color(11);printf("|                                               |");color(10);printf("         ****************************************      ");color(15);printf("**\n");
	color(15);printf("                                 **     ");color(10);printf("********************************************      ");color(11);printf("| 7：清屏                                       |");color(10);printf("      ********************************************     ");color(15);printf("**\n");
	color(15);printf("                                 **   ");color(10);printf("************************************************    ");color(11);printf("|                                               |");color(10);printf("    ************************************************   ");color(15);printf("**\n");
	color(15);printf("                                 ** ");color(10);printf("****************************************************  ");color(11);printf("|                                               |");color(10);printf("  **************************************************** ");color(15);printf("**\n");
	color(15);printf("                                 **                ");color(10);printf("        ******                         ");color(11);printf("| 8：退出程序                                   |");color(10);printf("                         ******                        ");color(15);printf("**\n");
	color(15);printf("                                 **                ");color(10);printf("        ******                         ");color(11);printf("|                                               |");color(10);printf("                         ******                        ");color(15);printf("**\n");
	color(15);printf("                                 **                ");color(10);printf("        ******                         ");color(11);printf("|                                               |");color(10);printf("                         ******                        ");color(15);printf("**\n");
	color(15);printf("                                 **                ");color(10);printf("        ******                         ");color(11);printf("| 9：清除内部数据                               |");color(10);printf("                         ******                        ");color(15);printf("**\n");
	color(15);printf("                                 **                ");color(10);printf("        ******                         ");color(11);printf("－－－－－－－－－－－－－－－－－－－－－－－－ ");color(10);printf("                         ******                        ");color(15);printf("**\n");
	color(15);printf("                                 **                ");color(10);printf("        ******                                                                                             ");color(10);printf("      ");color(10);printf("******                        ");color(15);printf("**\n");
	color(15);printf("                                 **                ");color(10);printf("        ******                                                                                             ");color(10);printf("      ");color(10);printf("******                        ");color(15);printf("**\n");
	color(15);printf("                                 **                ");color(10);printf("        ******                                                                                             ");color(10);printf("      ");color(10);printf("******                        ");color(15);printf("**\n");
	color(15);printf("                                 **                ");color(10);printf("        ******                                                                                             ");color(10);printf("      ");color(10);printf("******                        ");color(15);printf("**\n");
	color(15);printf("                                 **                ");color(10);printf("        ******                                                                                             ");color(10);printf("      ");color(10);printf("******                        ");color(15);printf("**\n");
	color(15);printf("                                 **                ");color(10);printf("        ******                                                                                             ");color(10);printf("      ");color(10);printf("******                        ");color(15);printf("**\n");
	color(15);printf("                                 **                ");color(10);printf("        ******                                                                                             ");color(10);printf("      ");color(10);printf("******                        ");color(15);printf("**\n");
	color(15);printf("                                 **                ");color(10);printf("        ******                                                                                             ");color(10);printf("      ");color(10);printf("******                        ");color(15);printf("**\n");
	color(15);printf("                                 ～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～ \n");
	color(15);printf("                                 ～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～·～ \n");
	color(16);
}
void drawMenu2()
{
	color(11);printf("                                                                                        －－－－－－－－－－－－－－－－－－－－－－－－ \n");
color(11);printf("                                                                                        |             您已进入选择菜单                  |\n");
color(11);printf("                                                                                        |                                               |\n");
color(11);printf("                                                                                        | 0.修改商品售价			        |\n");
color(11);printf("                                                                                        |                                               |\n");
color(11);printf("                                                                                        |                                               |\n");
color(11);printf("                                                                                        | 1：输入商品销售数据(利用商品编码进行选择)     |\n");
color(11);printf("                                                                                        |                                               |\n");
color(11);printf("                                                                                        |                                               |\n");
color(11);printf("                                                                                        | 2：输入商品销售数据(利用商品名称进行选择)     |\n");
color(11);printf("                                                                                        |                                               |\n");
color(11);printf("                                                                                        |                                               |\n");
color(11);printf("                                                                                        | 3：增添或删除商品信息                         |\n");
color(11);printf("                                                                                        |                                               |\n");
color(11);printf("                                                                                        |                                               |\n");
color(11);printf("                                                                                        | 4：计算销售总额及库存                         |\n");
color(11);printf("                                                                                        |                                               |\n");
color(11);printf("                                                                                        |                                               |\n");
color(11);printf("                                                                                        | 5：输出商品列表信息                           |\n");
color(11);printf("                                                                                        |                                               |\n");
color(11);printf("                                                                                        |                                               |\n");
color(11);printf("                                                                                        | 6：查找销售商品销售情况                       |\n");
color(11);printf("                                                                                        |                                               |\n");
color(11);printf("                                                                                        |                                               |\n");
color(11);printf("                                                                                        | 7：清屏                                       |\n");
color(11);printf("                                                                                        |                                               |\n");
color(11);printf("                                                                                        |                                               |\n");
color(11);printf("                                                                                        | 8：退出程序                                   |\n");
color(11);printf("                                                                                        |                                               |\n");
color(11);printf("                                                                                        |                                               |\n");
color(11);printf("                                                                                        | 9：清除内部数据                               |\n");
color(11);printf("                                                                                        －－－－－－－－－－－－－－－－－－－－－－－－ \n");color(15);
}
