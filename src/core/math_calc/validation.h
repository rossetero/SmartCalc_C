#ifndef VALIDATION_H
#define VALIDATION_H

#define VALID 1
#define INVALID 0
int is_valid(char* exp);
int is_oper(char ch);
int is_mod(char* exp, int i);
int is_sin(char* exp, int i);
int is_cos(char* exp, int i);
int is_tan(char* exp, int i);
int is_log(char* exp, int i);
int is_asin(char* exp, int i);
int is_acos(char* exp, int i);
int is_atan(char* exp, int i);
int is_sqrt(char* exp, int i);
int is_ln(char* exp, int i);
int validate_all_numbers(char* exp);
int validate_all_opers(char* exp);
int validate_all_mods(char* exp);
int validate_bkts(char* exp);
int validate_all_sins(char* exp);
int validate_all_coses(char* exp);
int validate_all_tans(char* exp);
int validate_all_logs(char* exp);
int validate_all_asins(char* exp);
int validate_all_acoses(char* exp);
int validate_all_atans(char* exp);
int validate_all_sqrts(char* exp);
int validate_all_lns(char* exp);
#endif