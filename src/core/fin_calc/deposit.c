#include "deposit.h"

double find_payed_percents(double sum, int term, int is_year, double p,
                           int capitalization, int capfreq) {
  p /= 100;
  double payed_percents = 0;
  if (is_year) term *= 12;
  if (!capitalization) {
    payed_percents = sum * p * term / 12;
  } else {
    switch (capfreq) {
      case DAILY:
        payed_percents = sum * pow(1 + p / 365, term * 30) - sum;
        break;
      case MONTHLY:
        payed_percents = sum * pow(1 + p / 12, term) - sum;
        break;
      default:
        break;
    }
  }
  return payed_percents;
}

double find_tax(double sum, int term, int is_year, double p, int capitalization,
                int capfreq) {
  int tmpterm = term;
  double untaxed = KEYRATE * 1000000;
  if (is_year) tmpterm *= 12;
  double t =
      find_payed_percents(sum, term, is_year, p, capitalization, capfreq) -
      untaxed * tmpterm / 12;
  return t > 0 ? t * TAX : 0;
}

double find_total_dep(double sum, int term, int is_year, double p,
                      int capitalization, int capfreq) {
  return find_payed_percents(sum, term, is_year, p, capitalization, capfreq) +
         sum;
}