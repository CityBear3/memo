#include <stdio.h>
#include <math.h>

typedef enum {
    false,
    true
}bool;

typedef struct {
    double x;
    double y;
}coordinates;

typedef struct {
    double p;
    double q;
}ver;

double gcd(double p, double q);

void input(coordinates* func);

double calc_a(coordinates* func_1, coordinates* func_2);

double calc_b(coordinates* func_1, double a);

bool integer_or_not(double number);

void a_rational_or_not(bool num_bool, coordinates* func_1, coordinates* func_2, ver* ver_a);

void b_rational_or_not(bool num_bool, coordinates* func_1, coordinates* func_2, ver* ver_b);

double calc_theta(double* a);

double calc_len(coordinates* func_1, coordinates* func_2);

void select_view(ver* ver_num, double* number, bool num_bool);

int main() {
    coordinates func_1, *f1;
    coordinates func_2, *f2;

    f1 = &func_1;
    f2 = &func_2;

    input(f1);
    input(f2);

    double a = calc_a(f1, f2);
    double b = calc_b(f1, a);

    bool a_bool = integer_or_not(a);
    bool b_bool = integer_or_not(b);
    
    ver ver_1, *ver_a;
    ver ver_2, *ver_b;

    ver_a = &ver_1;
    ver_b = &ver_2;

    a_rational_or_not(a_bool, f1, f2, ver_a);
    b_rational_or_not(b_bool, f1, f2, ver_b);

    double theta = calc_theta(&a);
    double len = calc_len(f1, f2);

    printf("a=");
    select_view(ver_a, &a, a_bool);

    printf("b=");
    select_view(ver_b, &b, b_bool);

    printf("theta=%lf\n", theta);
    printf("length=%lf\n", len);
}

double gcd(double p, double q) {
    if (q == 0) {
            return p;
    } else {
        return gcd(p, fmod(p, q));
    }    
}

void input(coordinates* func) {
    double x, y;
    char str[1000];
    fgets(str, sizeof(str), stdin);
    sscanf(str, "%lf %lf", &x, &y);

    func->x = x;
    func->y = y;
}

double calc_a(coordinates* func_1, coordinates* func_2) {
    double a = (func_1->y - func_2->y) / (func_1->x - func_2->x);
    return a;
}

double calc_b(coordinates* func_1, double a) {
    double b = (func_1->y - a * func_1->x);
    return b;
}

bool integer_or_not(double number) {
    if (fabs(number) - (int)number != 0) {
        return false;
    }else {
        return true;
    }
}

void a_rational_or_not(bool num_bool, coordinates* func_1, coordinates* func_2, ver* ver_a) {
    if (!num_bool) {
        ver_a->p = func_1->y - func_2->y;
        ver_a->q = func_1->x - func_2->x;

        double n = gcd(ver_a->p, ver_a->q);

        ver_a->p = ver_a->p / n;
        ver_a->q = ver_a->q / n;

        if (ver_a->p < 0 && ver_a->q < 0) {
            ver_a->p = fabs(ver_a->p);
            ver_a->q = fabs(ver_a->q);
        }
    }
}

void b_rational_or_not(bool num_bool, coordinates* func_1, coordinates* func_2, ver* ver_b) {
    if (!num_bool) {
        ver_b->p = (func_1->x * func_2->y) - (func_1->y * func_2->x);
        ver_b->q = func_1->x - func_2->x;

        double n = gcd(ver_b->p, ver_b->q);

        ver_b->p = ver_b->p / n;
        ver_b->q = ver_b->q / n;

        if (ver_b->p < 0 && ver_b->q < 0) {
            ver_b->p = fabs(ver_b->p);
            ver_b->q = fabs(ver_b->q);
        }
    }
}

double calc_theta(double* a) {
    double theta = atan(*a);
    return theta;
}

double calc_len(coordinates* func_1, coordinates* func_2) {
    double ver = pow((func_1->x - func_2->y), 2) + pow((func_1->y - func_2->y), 2);
    double len = sqrtl(ver);
    return len;
}

void select_view(ver* ver_num, double* number, bool num_bool) {
    if (num_bool) {
        int num = *number;
        printf("%d\n", num);
    }else if (!num_bool) {
        if (ver_num->p - (int)ver_num->q == 0) {
            if (ver_num->q - (int)ver_num->q == 0) {
                printf("%.0lf/%.0lf\n", ver_num->p, ver_num->q);
            }else {
                printf("%.0lf/%lf\n", ver_num->p, ver_num->q);
            }
        }else {
            if (ver_num->q - (int)ver_num->q == 0) {
                printf("%lf/%.0lf\n", ver_num->p, ver_num->q);
            }else {
                printf("%lf/%lf\n", ver_num->p, ver_num->q);
            }
        }
    }
}