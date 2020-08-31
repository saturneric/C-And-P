//
//  C&P.h
//  C&P
//
//  Created by Eric on 16-3-26.
//  Copyright (c) 2016年 Bakantu Eric. All rights reserved.
//

#ifndef C_P_C_P_h
#define C_P_C_P_h

#define LandMax 10
#define CountryMax 2

struct land{
    double people, tax_percent, efficiency, social_wealth;
    double resource_total, resource_add;
    int politics_official ,emconomy_official;
    int belong;
};

struct country{
    double income, outcome, at_storage;
    double phide_offical, ehide_offical, mhide_offical;
    double pi_offical, ei_offical, mi_offical;
    double pc_offical, ec_offical, mc_offical;
    int military_official;
    int soldiers;
    double soldier_pay;
    double efficiency_max;
};

struct land lands[LandMax];
struct country countries[CountryMax];
char USER_CONTROL = 0;
int USER_SEE = -1;

void init(void){
    int i;
    srand((unsigned int)time(NULL));
    for (i = 0; i < LandMax; i++){
        lands[i].people = rand()%900+100;
        lands[i].resource_total = (rand() % 990000) + 10000;
        lands[i].resource_add = 1000000000 / lands[i].resource_total;
        lands[i].social_wealth = 0;
        lands[i].politics_official = 0;
        lands[i].emconomy_official = 0;
        lands[i].tax_percent = 0;
        lands[i].belong = -1;
    }
    for (i = 0; i < CountryMax; i++){
        countries[i].income = 0;
        countries[i].outcome = 0;
        countries[i].at_storage = 0;
        countries[i].phide_offical = 0.2;
        countries[i].ehide_offical = 0.2;
        countries[i].mhide_offical = 0.2;
        countries[i].ec_offical = 500;
        countries[i].mc_offical = 500;
        countries[i].military_official = 0;
        countries[i].soldiers = 0;
        countries[i].soldier_pay = 0.8;
        countries[i].efficiency_max = 1;
        
        USER_SEE = rand()%LandMax;
        lands[USER_SEE].belong = i;
    }
}

void game_engine(void){
    if((kbhit()) && (lands[USER_SEE].belong == USER_CONTROL)){
        char input = readch();
        switch (input) {
            case 'w':
                if (lands[USER_SEE].tax_percent < (double)(lands[USER_SEE].politics_official/10)) lands[USER_SEE].tax_percent += 0.1;
                break;
            case 's':
                if (lands[USER_SEE].tax_percent > 0) lands[USER_SEE].tax_percent -= 0.1;
                break;
            case 'e': lands[USER_SEE].politics_official += 1;
                break;
            case 'd': if (lands[USER_SEE].politics_official > 0) lands[USER_SEE].politics_official -= 1;
                break;
            case 'r': lands[USER_SEE].emconomy_official += 1;
                break;
            case 'f': if (lands[USER_SEE].emconomy_official > 0) lands[USER_SEE].emconomy_official -= 1;
                break;
            case 't': countries[USER_SEE].military_official += 1;
                break;
            case 'g': if (countries[USER_SEE].military_official > 0) countries[USER_SEE].military_official -= 1;                break;
            case 'y':if ((countries[lands[USER_SEE].belong].soldiers <= countries[lands[USER_SEE].belong].military_official) && ((100/lands[USER_SEE].people) < (double)(lands[USER_SEE].politics_official / 10))) {
                countries[lands[USER_SEE].belong].soldiers += 100;
                lands[USER_SEE].people -= 100;
                }
                break;
            case 'h':if (countries[lands[USER_SEE].belong].soldiers > 0) {
                countries[lands[USER_SEE].belong].soldiers -= 100;
                lands[USER_SEE].people += 100;
                }
                break;
                
            default:
                break;
        }
    }
    
    int i,get_total_peo,increase_peo,t_tax;
    for(i = 0; i < LandMax; i++){
        if ((lands[i].resource_total+ lands[i].resource_add) - (lands[i].people * lands[i].efficiency) > 0){
            //EFFICIENCY
            if (lands[i].belong != -1) lands[i].efficiency = countries[lands[i].belong].efficiency_max * (pow(2, 1 - lands[i].tax_percent) -1);
            else lands[i].efficiency = 1;
            get_total_peo = lands[i].efficiency * lands[i].people;
            //PEOPLE INCREASE
            increase_peo = (pow(2, 1 - lands[i].tax_percent) -1.25)/100;
            //RESOURCE
            lands[i].resource_total -= lands[i].people * lands[i].efficiency;
            lands[i].resource_total += lands[i].resource_add;
            
        }
        else{
            lands[i].resource_total = 0;
            get_total_peo = lands[i].resource_add;
            increase_peo = -0.025;
        }
        t_tax = get_total_peo * lands[i].tax_percent;
        lands[i].social_wealth += get_total_peo;
        if (lands[i].belong != -1){
            if((lands[i].emconomy_official * countries[lands[i].belong].ec_offical * lands[i].people * lands[i].efficiency * lands[i].tax_percent) < t_tax) t_tax = lands[i].emconomy_official * countries[lands[i].belong].ec_offical * lands[i].people * lands[i].efficiency * lands[i].tax_percent;
            countries[lands[i].belong].income = (1 - ex_offical)*t_tax;
            countries[lands[i].belong].outcome = ((a_offical * ai_offical) + (army * soldier * (1+ax_offical))) + (e_offical * ei_offical);
            countries[lands[i].belong].outcome = out_country + (p_offical * pi_offical);
            if (p_offical > 0) countries[lands[i].belong].outcome *= 1 + px_offical;
            at_country += in_country - out_country;
        }
    }

}


#endif
