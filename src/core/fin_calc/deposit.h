#ifndef DEPOSIT_H
#define DEPOSIT_H
#define TAX 0.13
#define KEYRATE 0.16

#define DAILY 1
#define MONTHLY 2
#include <math.h>
double find_payed_percents(double sum, int term, int is_year, double p,
                           int capitalization, int capfreq);
double find_total_dep(double sum, int term, int is_year, double p,
                      int capitalization, int capfreq);
double find_tax(double sum, int term, int is_year, double p, int capitalization,
                int capfreq);
#endif