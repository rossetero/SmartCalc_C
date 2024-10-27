#ifndef CREDIT_H
#define CREDIT_H
#include <math.h>
#include <time.h>

double find_diff_monthly_payment(double* s, double sd, double p, int is_year,
                                 int i);
double find_diff_overpayment(double s, int term, double p, int is_year);
double find_total_diff(double s, int term, double percent, int is_year);
double find_monthly_payment(double s, int term, double percent, int is_year);

double find_overpayment(double s, int term, double p, int is_year);

double find_total(double s, int term, double percent, int is_year);

#endif