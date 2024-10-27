#include "credit.h"

int is_leap_year(int x) { return x % 400 == 0 || (x % 4 == 0 && x % 100 != 0); }

double find_diff_monthly_payment(double* s, double sd, double p, int is_year,
                                 int i) {
  int cntyears = 0;
  int days_in_mon = 0;
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  int cmon = tm.tm_mon + 1 + i;
  if (cmon > 12) {
    cntyears = cmon / 12;
    cmon -= 12 * cntyears;
  }
  int cyear = tm.tm_year + 1900 + cntyears;
  switch (cmon) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
    case 0:
      days_in_mon = 31;
      break;
    case 2:
      days_in_mon = 28 + is_leap_year(cyear);
      break;
    default:
      days_in_mon = 30;
      break;
  }
  p /= 100;
  double sp = (*s) * p * days_in_mon / (365 + is_leap_year(cyear));
  if (is_year) sd /= 12;
  *s -= sd;
  return sd + sp;
}

double find_total_diff(double s, int term, double p, int is_year) {
  double t = 0;
  double tmps = s;
  int tmpterm = term;
  if (is_year) tmpterm *= 12;
  for (int i = 0; i < tmpterm; i++) {
    t += find_diff_monthly_payment(&tmps, s / term, p, is_year, i);
  }
  return t;
}

double find_diff_overpayment(double s, int term, double p, int is_year) {
  return find_total_diff(s, term, p, is_year) - s;
}

double find_monthly_payment(double s, int term, double p, int is_year) {
  p /= 100;
  if (is_year) term *= 12;
  return s * p / 12 * pow(1 + p / 12, term) / (pow(1 + p / 12, term) - 1);
}

double find_total(double s, int term, double p, int is_year) {
  int tmpterm = term;
  if (is_year) tmpterm *= 12;
  return find_monthly_payment(s, term, p, is_year) * tmpterm;
}

double find_overpayment(double s, int term, double p, int is_year) {
  return find_total(s, term, p, is_year) - s;
}
