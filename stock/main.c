/*
 * 使用：
 * cd stock
 * gcc -O3 main.c ../pearson.c
 * ./a.out
 */
#include <stdio.h>
#include <stdlib.h>
#include "../pearson.h"

int main() {
    FILE *fp;
    double a;
    double *dataArray;
    int total = 0;
    fp = fopen("data.csv", "r");
    if (NULL == fp) {
        printf("文件打开失败\n");
        return 0;
    }
    while (0 == feof(fp)) {
        if (fscanf(fp, "%lf", &a) <= 0) {
            break;
        }
        total++;
    }
    printf("数据总数：%d\n", total);
    fseek(fp, 0, SEEK_SET);
    dataArray = (double*)calloc(total, sizeof (double));
    for (int i = 0; i < total; i++) {
        if (fscanf(fp, "%lf", &(dataArray[i])) <= 0) {
            printf("读取数据失败\n");
        }
    }
    fclose(fp);
    int newTotal = total / 2;
    int xTotal = 2 * newTotal - 2;
    //for (int j = 0; j < xTotal; j++) {
    //    printf("%d,%d\n", dataArray[j + 1] - dataArray[j] > 0 ? 1 : 0, dataArray[j + 2] - dataArray[j + 1] > 0 ? 1 : 0);
    //}

    struct pear_data *pear_data;
    double seq;
    char *x;
    char *y;
    x = (char*)calloc(xTotal, sizeof (char));
    y = (char*)calloc(xTotal, sizeof (char));
    for (int j = 0; j < xTotal; j++) {
        x[j] = dataArray[j + 1] - dataArray[j] > 0 ? 1 : 0;
        y[j] = dataArray[j + 2] - dataArray[j + 1] > 0 ? 1 : 0;
        // 即使这里不引入随机，相关性还是很大
        if (abs(dataArray[j + 1] - dataArray[j]) < 0.00001) {
            x[j] = rand();
        }
        if (abs(dataArray[j + 2] - dataArray[j + 1]) < 0.00001) {
            y[j] = rand();
        }
    }
    pear_data = pear_create_from_chars_reffer(xTotal, x, y);
    seq = pear_get_chi_square(pear_data);
    printf("Seq=%lf\n", seq);
    printf("Believe=%lf\n", pear_believe(seq));
    pear_free(pear_data);
    free(x);
    free(y);
    free(dataArray);
    return 0;
}
