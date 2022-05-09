#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct array_plus_len {
    int *a;
    int n;
} data;

typedef struct result {
    int count;
    float period;
} res;

struct res_collection {
    res *res_arr;
    int n;
};

data *gen_data(int n) {
    data *new_data = (data *)malloc(sizeof(data));
    if (new_data == NULL) exit(-2);
    srand(time(NULL));
    new_data->a = (int *)malloc(n*sizeof(int));
    if (new_data->a == NULL) exit(-2);
    for (int i = 0; i<n; i++) new_data->a[i] = rand();
    new_data->n = n;
    return new_data;
}

void del_data(data *old_data) {
    free(old_data->a);
    free(old_data);
}

void print_data(data *cur_data) {
    for (int i = 0; i<cur_data->n; i++) printf("%i ", cur_data->a[i]);
    putchar('\n');
}
void print_res_collection(struct res_collection *cur_res_col) {
    for (int i = 0; i<cur_res_col->n; i++) printf("%3i %10i %lf\n", i, cur_res_col->res_arr[i].count, cur_res_col->res_arr[i].period);
    putchar('\n');
}

#include "team_4_sorts.c"

void del_res_collection(struct res_collection *old_res_collection) {
    free(old_res_collection->res_arr);
    free(old_res_collection);
}

void del_step_arr(struct step_arr *old_step_arr){
    if (old_step_arr!=NULL) free(old_step_arr->s);
    free(old_step_arr);
}

double get_time(void (*func)(data*, struct step_arr*), data *cur_data, struct step_arr *cur_step_arr) {
    clock_t s = clock();
    func(cur_data, cur_step_arr);
    clock_t f = clock();
    double result = (double)(f-s) / CLOCKS_PER_SEC;
    return result;
}

int check_data(data *cur_data) {
    for (int i = 1; i<cur_data->n; i++) if (cur_data->a[i]<cur_data->a[i-1]) return -1;
    return 0;
}

int sortion_test(void (*func)(data*, struct step_arr*), struct step_arr *(*step_func)(data*), long long start, long long stop, long long step, int repeat, char* file_name) {
    struct res_collection *cur_res_col = (struct res_collection*)malloc(sizeof(struct res_collection));
    if (cur_res_col == NULL) exit(-2);
    cur_res_col->res_arr = (res*)malloc(((stop-start)/step+1)*sizeof(res));
    if (cur_res_col->res_arr == NULL) exit(-2);
    double cur_time;
    for (int r = 0; r<repeat; r++) {
        cur_res_col->n = 0;
        for (int i = start; i<=stop; i+=step) {
            data *cur_data = gen_data(i);
            struct step_arr *cur_step_arr = step_func(cur_data);
            cur_time = get_time(func, cur_data, cur_step_arr);
            if (check_data(cur_data)==-1) return -1;
            del_data(cur_data);
            del_step_arr(cur_step_arr);
            cur_res_col->res_arr[cur_res_col->n].count = i;
            cur_res_col->res_arr[cur_res_col->n].period *= r;
            cur_res_col->res_arr[cur_res_col->n].period += cur_time;
            cur_res_col->res_arr[cur_res_col->n].period /= (r+1);
            cur_res_col->n++;
        }
    }
    print_res_collection(cur_res_col);
    FILE *f_ptr;
    f_ptr = fopen(file_name, "w");
    for (int i = 0; i<cur_res_col->n; i++) {
        fprintf(f_ptr, "%i %lf\n", cur_res_col->res_arr[i].count, cur_res_col->res_arr[i].period);
    }
    fclose(f_ptr);
    del_res_collection(cur_res_col);
    return 0;
}

int main() {
    int res = 0;

    res += sortion_test(shell_sort, step_ciura, 0, 1000000, 10000, 1, "delete_this_7.txt");
    return res;
}
