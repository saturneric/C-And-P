//
//  main.c
//  C&P
//
//  Created by Eric on 16-3-25.
//  Copyright (c) 2016年 Bakantu Eric. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Keyboard.h"
//#include "C&P.h"


double peo = 1000;
double tax = 0.2,i_peo = 0,get_peo = 0,e_peo = 1,get_total_peo = 0,t_tax = 0,soc_total = 0;
double e_max_peo = 1;
double res_total = 0, res_increase = 0;

int p_offical = 2, e_offical = 0, a_offical = 0;
double px_offical = 0.2, ex_offical = 0.2, ax_offical = 0.1;
double tax_max = 0, army_max = 0;

double out_country = 0,in_country = 0,at_country = 0;
double pi_offical = 20, ei_offical = 25, ai_offical = 30,soldier = 0.8;
double ec_offical = 500, ac_offical = 500;
double army;

int count = 1;

int main(int argc, const char * argv[]) {
    srand((unsigned int)time(NULL));
    peo = rand()%900+100;
    res_total = (rand() % 990000) + 10000;
    res_increase = 1000000000 / res_total;
    while(1){
        if(kbhit()){
            char input = readch();
            switch (input) {
                case 'w':
                     if (tax < tax_max) tax += 0.1;
                    break;
                case 's':
                    tax -= 0.1;
                    break;
                case 'e': p_offical +=1;
                    break;
                case 'd': p_offical -=1;
                    break;
                case 'r': e_offical +=1;
                    break;
                case 'f': e_offical -=1;
                    break;
                case 't': a_offical +=1;
                    break;
                case 'g': a_offical -=1;
                    break;
                case 'y':if ((army < a_offical * ac_offical)) {army +=100;
                    peo -= 100;}
                    break;
                case 'h':if (army - 100 > 0) {army -=100;
                    peo += 100;}
                    break;
                case 'x':
                    at_country += soc_total *0.6;
                    soc_total = soc_total * 0.4;
                    break;
                default:
                    break;
            }
        }
        if ((res_total+ res_increase) - (e_peo * peo) > 0){
            get_peo = e_peo *(1 - tax);
            get_total_peo = get_peo * peo;
            //PEOPLE INCREASE
            i_peo = (pow(2, 1 - tax) -1.25)/100;
            //PEOPLE GET RESOURCE
            e_peo = e_max_peo * (pow(2, 1 - tax) -1);
            //RESOURCE
            res_total -= e_peo * peo;
            res_total += res_increase;

        }
        else{
            res_total = 0;
            get_total_peo = res_increase;
            i_peo = -0.025;
        }
        t_tax = get_total_peo * tax;
        
        soc_total += get_total_peo;
        
        printf("回合: %d\n",count++);
        //LAND
        printf("领土信息: \n");
        printf("劳动力: %.0f\n税率: %lf\n生产力: %lf\n人民总所得: %lf\n人口增长率: %lf\n社会财富: %lf\n \n"\
               ,peo,tax,e_peo,get_total_peo,i_peo,soc_total);
        printf("总资源: %lf\n资源增加: %lf\n领土税收: %lf \n \n",res_total,res_increase,t_tax);
        printf("政治官员: %d\n经济官员: %d\n军事官员: %d \n \n",p_offical,e_offical,a_offical);
        if((e_offical * ec_offical) < peo) t_tax = e_offical * ec_offical * get_peo * tax;
        tax_max = (double) p_offical /10;
        army_max = (double)p_offical /10;
        printf("实际税收: %.2lf\n最高税率: %.2lf%%\n最高征兵率: %.2lf%%\n \n",t_tax,tax_max*100,army_max*100);

        
        //COUNTRY
        printf("国家信息: \n");
        in_country = (1 - ex_offical)*t_tax;
        out_country = ((a_offical * ai_offical) + (army * soldier * (1+ax_offical))) + (e_offical * ei_offical);
        out_country = out_country + (p_offical * pi_offical);
        if (p_offical > 0) out_country *= 1 + px_offical;
        at_country += in_country - out_country;
        printf("国库储量: %lf\n财政收入: %lf\n财政支出: %lf \n \n",at_country,in_country,out_country);
        printf("军队: %lf\n军费: %lf\n \n",army,army * soldier);

        
        
        peo = peo * (1 + i_peo);
        usleep(200000);
    }
    return 0;
}
