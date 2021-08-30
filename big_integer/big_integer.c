#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define N 10000000

const int bs = 1000000000;
int size_num1, size_num2, sign, num1[N], num2[N], tmp_zero1[N] = { 1, 0 }, tmp_zero2[N] = { 1, 0 };
int num1_cpy[N], num_sum[N], ans_fac[N] = { 1,1 }, array1[N] = { 1,1 }, array1_2[2] = { 1,1 };
long long ans[N];
char sign1 = '+', sign2 = '+';

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

void scan_sign() {
    printf("Please, choose set of signs for your numbers:\n1: + +\n2: + -\n3: - +\n4: - -\n");
    scanf("%d", &sign);
    if (sign == 2) sign2 = '-';
    if (sign == 3) sign1 = '-';
    if (sign == 4) {
        sign1 = '-';
        sign2 = '-';
    }
}
int cmp_big(int first[], int second[]) {
    if (first[0] == second[0] && first[first[0]] == second[second[0]]) return 0;
    if (first[0] == second[0] && first[first[0]] > second[second[0]]) return 1;
    if (first[0] == second[0] && first[first[0]] < second[second[0]])  return -1;
    if (first[0] > second[0]) return 1;
    if (second[0] > first[0]) return -1;
    printf("ERROR_");
    return 0;
}

void num_scan(char str_num[1001], int num[N], int* len) {
    scanf("%s", str_num);
    *len = strlen(str_num);
    num[0] = ((*len) - 1) / 9 + 1;
    for (int i = 1; i <= num[0]; ++i) {
        for (int j = 9; j >= 1; --j) {
            int point = (*len) - (i - 1) * 9 - j;
            if (point >= 0) {
                num[i] = num[i] * 10 + (str_num[point] - 48);
            }
        }
    }

}

void num_print(int num[]) {
    printf("%d", num[num[0]]);
    for (int i = num[0] - 1; i > 0; --i)
        printf("%.9d", num[i]);
}

void addition(int first[], int second[]) {
    if (first[0] < second[0])
        first[0] = second[0];
    int move = 0;
    for (int i = 1; i <= first[0]; ++i) {
        first[i] += second[i] + move;
        if (first[i] >= bs) {
            move = 1;
            first[i] -= bs;
        }
        else
            move = 0;
    }
    if (move) {
        first[0]++;
        first[first[0]] = 1;
    }
}

void subtract(int first[], int second[]) {
    int move = 0;
    for (int i = 1; i <= first[0]; ++i) {
        first[i] -= second[i] + move;
        if (first[i] < 0) {
            move = 1;
            first[i] += bs;
        }
        else
            move = 0;
    }
    while (first[0] > 1 && first[first[0]] == 0) {
        first[0]--;
    }
}

void multiplication(int first[], int second[]) {
    memset(ans, 0, (first[0] + second[0] + 1) * 8);
    for (int i = 1; i <= first[0]; ++i) {
        long long move = 0;
        for (int j = 1; j <= second[0] || move > 0; ++j) {
            ans[i + j - 1] += (long long)first[i] * (long long)second[j] + move;
            move = (long long)ans[i + j - 1] / (long long)bs;
            ans[i + j - 1] -= (long long)move * (long long)bs;

        }
    }
    ans[0] = first[0] + second[0];
    for (int i = 0; i <= ans[0]; ++i) first[i] = ans[i];
    while (first[0] > 1 && first[first[0]] == 0) {
        first[0]--;
    }
}

void power(int first[], int second[]) {
    memset(num1_cpy, 0, sizeof(num1_cpy));
    memccpy(num1_cpy, first, -1, sizeof(int) * N);
    subtract(second, array1);
    while (second[1] != 0) {
        subtract(second, array1);
        multiplication(first, num1_cpy);
    }
}

void factorial(int first[]) {
    while (array1[first[0]] != first[first[0]]) {
        addition(array1, array1_2);
        multiplication(ans_fac, array1);
    }
    memmove(first, ans_fac, sizeof(ans_fac));

}

void sum(int first[], int second[]) {
    memmove(num_sum, first, sizeof(num1));
    while (first[first[0]] != second[second[0]] || first[0] != second[0]) {
        addition(first, array1);
        addition(num_sum, first);
    }
    memmove(first, num_sum, sizeof(num_sum));
}

int main() {
    char str_num1[1001], str_num2[1001];

    int op, check;
    printf("Input number of mathematical symbol (1 = '+', 2 = '-', 3 = '*', 4 = '^', 5 = '!', 6 = 'sum[a, b]'):\n");
    scanf("%d", &op);
    if (op == 1) {
        scan_sign();
        printf("Input numbers:\n");
        num_scan(str_num1, num1, &size_num1);
        num_scan(str_num2, num2, &size_num2);
        int check = cmp_big(num1, num2);
        if (sign1 == '+' && sign2 == '+') {
            addition(num1, num2);
            num_print(num1);
        }
        else if (sign1 == '+' && sign2 == '-') {
            if (check >= 0) {
                subtract(num1, num2);
                num_print(num1);
            }
            else if (check < 0) {
                subtract(num2, num1);
                printf("-");
                num_print(num2);
            }
        }
        else if (sign1 == '-' && sign2 == '+') {
            int check = cmp_big(num1, num2);
            if (check > 0) {
                subtract(num1, num2);
                printf("-");
                num_print(num1);
            }
            else if (check <= 0) {
                subtract(num2, num1);
                num_print(num2);
            }
        }
        else if (sign1 == '-' && sign2 == '-') {
            addition(num1, num2);
            printf("-");
            num_print(num1);
        }
        else printf("ERROR");
    }
    if (op == 2) {
        scan_sign();
        printf("Input numbers:\n");
        num_scan(str_num1, num1, &size_num1);
        num_scan(str_num2, num2, &size_num2);
        int check = cmp_big(num1, num2);
        if (sign1 == '+' && sign2 == '+') {
            if (check >= 0) {
                subtract(num1, num2);
                num_print(num1);
            }
            else if (check < 0) {
                subtract(num2, num1);
                printf("-");
                num_print(num2);
            }
        }
        else if (sign1 == '+' && sign2 == '-') {
            addition(num1, num2);
            num_print(num1);
        }
        else if (sign1 == '-' && sign2 == '+') {
            addition(num1, num2);
            printf("-");
            num_print(num1);

        }
        else if (sign1 == '-' && sign2 == '-') {
            if (check > 0) {
                subtract(num1, num2);
                printf("-");
                num_print(num1);
            }
            else if (check <= 0) {
                subtract(num2, num1);
                num_print(num2);
            }
        }
        else printf("ERROR");
    }
    if (op == 3) {
        scan_sign();
        printf("Input numbers:\n");
        num_scan(str_num1, num1, &size_num1);
        num_scan(str_num2, num2, &size_num2);
        int check = cmp_big(num1, num2);
        if (sign1 == sign2) {
            if (check) {
                multiplication(num1, num2);
                num_print(num1);
            }
            else {
                multiplication(num2, num1);
                num_print(num2);
            }
        }
        else {
            if (check) {
                multiplication(num1, num2);
                num_print(num1);
            }
            else {
                multiplication(num2, num1);
                printf("-");
                num_print(num2);
            }
        }
    }
    if (op == 4) {
        printf("Input numbers without signs:\n");
        num_scan(str_num1, num1, &size_num1);
        num_scan(str_num2, num2, &size_num2);
        power(num1, num2);
        num_print(num1);
    }
    if (op == 5) {
        printf("Input number without sign:\n");
        num_scan(str_num1, num1, &size_num1);
        factorial(num1);
        num_print(num1);
    }
    if (op == 6) {
        printf("Please, choose set of signs for your numbers:\n1: + +\n2: - +\n3: - -\n");
        scanf("%d", &sign);
        if (sign == 2) sign1 = '-';
        if (sign == 3) {
            sign1 = '-';
            sign2 = '-';
        }
        printf("Input numbers:\n");
        num_scan(str_num1, num1, &size_num1);
        num_scan(str_num2, num2, &size_num2);
        if (sign1 == '-' && sign2 == '+') {
            sum(tmp_zero1, num1);
            sum(tmp_zero2, num2);
            int check = cmp_big(tmp_zero1, tmp_zero2);
            if (check == 0) {
                printf("0");
            }
            else if (check > 0) {
                subtract(tmp_zero1, tmp_zero2);
                printf("-");
                num_print(tmp_zero1);
            }
            else if (check < 0) {
                subtract(tmp_zero2, tmp_zero1);
                num_print(tmp_zero2);
            }
        }
        else if (sign1 == '-' && sign2 == '-') {
            sum(num2, num1);
            printf("-");
            num_print(num2);
        }
        else if (sign1 == '+' && sign2 == '+') {
            sum(num1, num2);
            num_print(num1);
        }
    }
    return 0;
}