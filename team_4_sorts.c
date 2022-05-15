#include <stdlib.h>
#include <math.h>


struct step_arr {
    int *s;
    int len;
};

void classic_insertion_sort(data *cur_data, struct step_arr *cur_step_arr) {
    int x, i, j;
    for (i = 1; i<cur_data->n; i++) {
        x = cur_data->a[i];
        for (j=i-1; j>=0 && cur_data->a[j]>x; j--) cur_data->a[j+1] = cur_data->a[j];
        cur_data->a[j+1] = x;
    }
}

void watchdog_element_insertion_sort(data *cur_data, struct step_arr *cur_step_arr) {
    int x, i, j;
    int buf = cur_data->a[0];
    cur_data->a[0] = -1;
    for (i = 1; i<cur_data->n; i++) {
        x = cur_data->a[i];
        for (j=i-1; cur_data->a[j]>x; j--) cur_data->a[j+1] = cur_data->a[j];
        cur_data->a[j+1] = x;
    }
    for (j=1; j<cur_data->n && cur_data->a[j]<buf; j++) cur_data->a[j-1] = cur_data->a[j];
    cur_data->a[j-1] = buf;
}

int pos_binary_search(int a[], int n, int x){
    int lo = 0;
    int hi = n;
    int mid;
    while (lo<=hi) {
        mid = lo + (hi-lo)/2;
        if (x == a[mid]) return mid;
        else if (x<a[mid]) hi = mid-1;
        else if (x>a[mid]) lo = mid+1;
    }
    return lo;
}

void binary_search_insertion_sort(data* cur_data, struct step_arr *cur_step_arr){
    int x, i, j, pos;
    for (i = 1; i<cur_data->n; i++) {
        x = cur_data->a[i];
        pos = pos_binary_search(cur_data->a, i-1, x);
        for (j=i-1; j>=pos; j--) cur_data->a[j+1] = cur_data->a[j];
        cur_data->a[j+1] = x;
    }
}

void classic_shell_sort(data *cur_data, struct step_arr *cur_step_arr) {
    int s, x, i, j;
    for (s = cur_data->n/2; s>0; s/=2) {
        for (i = s; i<cur_data->n; i++) {
            x = cur_data->a[i];
            for (j=i-s; j>=0 && cur_data->a[j]>x; j-=s) cur_data->a[j+s] = cur_data->a[j];
            cur_data->a[j+s] = x;
        }
    }
}


struct step_arr *not_req(data *cur_data) {
    return NULL;
};

struct step_arr *step_shell(data *cur_data) {
    int n = cur_data->n;
    int s_max_len = 1;
    int cur_step;
    struct step_arr *cur_step_arr = (struct step_arr*)malloc(sizeof(struct step_arr));
    if (cur_step_arr == NULL) exit(-2);
    cur_step_arr->s = (int*)malloc(s_max_len*sizeof(int));
    if (cur_step_arr->s == NULL) exit(-2);
    for (cur_step_arr->len = 0; (cur_step = n/(int)pow((float)2, cur_step_arr->len+1))>0; cur_step_arr->len++) {
        if (cur_step_arr->len==s_max_len) cur_step_arr->s = (int*)realloc(cur_step_arr->s, (s_max_len*=2)*sizeof(int));
        cur_step_arr->s[cur_step_arr->len] = cur_step;
    }
    return cur_step_arr;
}


struct step_arr *step_frank_and_lazarus(data *cur_data) {
    int n = cur_data->n;
    int s_max_len = 1;
    int cur_step;
    struct step_arr *cur_step_arr = (struct step_arr*)malloc(sizeof(struct step_arr));
    if (cur_step_arr == NULL) exit(-2);
    cur_step_arr->s = (int*)malloc(s_max_len*sizeof(int));
    if (cur_step_arr->s == NULL) exit(-2);
    for (cur_step_arr->len = 0; (cur_step = 2*(n/(int)pow((float)2, cur_step_arr->len+2))+1)>1; cur_step_arr->len++) {
        if (cur_step_arr->len==s_max_len) cur_step_arr->s = (int*)realloc(cur_step_arr->s, (s_max_len*=2)*sizeof(int));
        cur_step_arr->s[cur_step_arr->len] = cur_step;
    }
    if (cur_step_arr->len==s_max_len) cur_step_arr->s = (int*)realloc(cur_step_arr->s, (s_max_len+=1)*sizeof(int));
    cur_step_arr->s[cur_step_arr->len] = 1;
    cur_step_arr->len++;
    return cur_step_arr;
}

void reverse_arr(int *a, int n) {
    int i, buf;
    for (int i = 0; i<n/2; i++){
        buf = a[i];
        a[i] = a[n-i-1];
        a[n-i-1] = buf;
    }
}

struct step_arr *step_hibbard(data *cur_data) {
    int n = cur_data->n;
    int s_max_len = 1;
    int cur_step;
    struct step_arr *cur_step_arr = (struct step_arr*)malloc(sizeof(struct step_arr));
    if (cur_step_arr == NULL) exit(-2);
    cur_step_arr->s = (int*)malloc(s_max_len*sizeof(int));
    if (cur_step_arr->s == NULL) exit(-2);
    for (cur_step_arr->len = 0; (cur_step = (int)pow((float)2, cur_step_arr->len+1)-1)<n; cur_step_arr->len++) {
        if (cur_step_arr->len==s_max_len) cur_step_arr->s = (int*)realloc(cur_step_arr->s, (s_max_len*=2)*sizeof(int));
        cur_step_arr->s[cur_step_arr->len] = cur_step;
    }
    reverse_arr(cur_step_arr->s, cur_step_arr->len);
    return cur_step_arr;
}

struct step_arr *step_papernov_and_stasivich(data *cur_data) {
    int n = cur_data->n;
    int s_max_len = 1;
    int cur_step;
    struct step_arr *cur_step_arr = (struct step_arr*)malloc(sizeof(struct step_arr));
    if (cur_step_arr == NULL) exit(-2);
    cur_step_arr->s = (int*)malloc(s_max_len*sizeof(int));
    if (cur_step_arr->s == NULL) exit(-2);
    cur_step_arr->s[0] = 1;
    for (cur_step_arr->len = 1; (cur_step = (int)pow((float)2, cur_step_arr->len)+1)<n; cur_step_arr->len++) {
        if (cur_step_arr->len==s_max_len) cur_step_arr->s = (int*)realloc(cur_step_arr->s, (s_max_len*=2)*sizeof(int));
        cur_step_arr->s[cur_step_arr->len] = cur_step;
    }
    reverse_arr(cur_step_arr->s, cur_step_arr->len);
    return cur_step_arr;
}


struct step_arr *step_pratt(data *cur_data) {
    int n = cur_data->n;
    int s_max_len = 1;
    int cur_step;
    int p, q;
    struct step_arr *cur_step_arr = (struct step_arr*)malloc(sizeof(struct step_arr));
    if (cur_step_arr == NULL) exit(-2);
    cur_step_arr->s = (int*)malloc(s_max_len*sizeof(int));
    if (cur_step_arr->s == NULL) exit(-2);
    cur_step_arr->len = 0;
    for (p=0; (int)pow((float)2, p) < n; p++) {
        for (q=0; (int)pow((float)3, q) < n; q++) {
            if ((cur_step = (int)pow((float)2, p)*(int)pow((float)3, q))<n && cur_step>0) {
                if (cur_step_arr->len==s_max_len) cur_step_arr->s = (int*)realloc(cur_step_arr->s, (s_max_len*=2)*sizeof(int));
                cur_step_arr->s[cur_step_arr->len] = cur_step;
                cur_step_arr->len++;
            }
        }
    }
    int x, i, j;
    for (i = 1; i<cur_step_arr->len; i++) {
        x = cur_step_arr->s[i];
        for (j=i-1; j>=0 && cur_step_arr->s[j]>x; j--) cur_step_arr->s[j+1] = cur_step_arr->s[j];
        cur_step_arr->s[j+1] = x;
    }
    reverse_arr(cur_step_arr->s, cur_step_arr->len);
    return cur_step_arr;
}

struct step_arr *step_knuth(data *cur_data) {
    int n = cur_data->n;
    int s_max_len = 1;
    int cur_step;
    struct step_arr *cur_step_arr = (struct step_arr*)malloc(sizeof(struct step_arr));
    if (cur_step_arr == NULL) exit(-2);
    cur_step_arr->s = (int*)malloc(s_max_len*sizeof(int));
    if (cur_step_arr->s == NULL) exit(-2);
    for (cur_step_arr->len = 0; (cur_step = ((int)pow((float)3, cur_step_arr->len+1)-1)/2)<ceil((double)n/2); cur_step_arr->len++) {
        if (cur_step_arr->len==s_max_len) cur_step_arr->s = (int*)realloc(cur_step_arr->s, (s_max_len*=2)*sizeof(int));
        cur_step_arr->s[cur_step_arr->len] = cur_step;
    }
    reverse_arr(cur_step_arr->s, cur_step_arr->len);
    return cur_step_arr;
}

struct step_arr *step_sedgewick_1(data *cur_data) {
    int n = cur_data->n;
    int s_max_len = 1;
    int cur_step;
    struct step_arr *cur_step_arr = (struct step_arr*)malloc(sizeof(struct step_arr));
    if (cur_step_arr == NULL) exit(-2);
    cur_step_arr->s = (int*)malloc(s_max_len*sizeof(int));
    if (cur_step_arr->s == NULL) exit(-2);
    cur_step_arr->s[0] = 1;
    for (cur_step_arr->len = 1; (cur_step = (int)pow((float)4, cur_step_arr->len)+3*((int)pow((float)2, cur_step_arr->len-1))+1)<n; cur_step_arr->len++) {
        if (cur_step_arr->len==s_max_len) cur_step_arr->s = (int*)realloc(cur_step_arr->s, (s_max_len*=2)*sizeof(int));
        cur_step_arr->s[cur_step_arr->len] = cur_step;
    }
    reverse_arr(cur_step_arr->s, cur_step_arr->len);
    return cur_step_arr;
}

struct step_arr *step_sedgewick_2(data *cur_data) {
    int n = cur_data->n;
    int s_max_len = 1;
    int cur_step;
    struct step_arr *cur_step_arr = (struct step_arr*)malloc(sizeof(struct step_arr));
    if (cur_step_arr == NULL) exit(-2);
    cur_step_arr->s = (int*)malloc(s_max_len*sizeof(int));
    if (cur_step_arr->s == NULL) exit(-2);
    for (cur_step_arr->len = 0; (cur_step = cur_step_arr->len%2==0 ? (9*(int)pow((float)2, cur_step_arr->len)-9*(int)pow((float)2, cur_step_arr->len/2)+1) :\
        (8*(int)pow((float)2, cur_step_arr->len)-6*(int)pow((float)2, (cur_step_arr->len+1)/2)+1))<n; cur_step_arr->len++) {
        if (cur_step_arr->len==s_max_len) cur_step_arr->s = (int*)realloc(cur_step_arr->s, (s_max_len*=2)*sizeof(int));
        cur_step_arr->s[cur_step_arr->len] = cur_step;
    }
    reverse_arr(cur_step_arr->s, cur_step_arr->len);
    return cur_step_arr;
}

struct step_arr *step_gonnet_and_baeza_yates(data *cur_data) {
    int n = cur_data->n;
    int s_max_len = 1;
    int cur_step;
    struct step_arr *cur_step_arr = (struct step_arr*)malloc(sizeof(struct step_arr));
    if (cur_step_arr == NULL) exit(-2);
    cur_step_arr->s = (int*)malloc(s_max_len*sizeof(int));
    if (cur_step_arr->s == NULL) exit(-2);
    cur_step_arr->s[0] = (5*n-1)/11;
    for (cur_step_arr->len = 1; (cur_step = (5*cur_step_arr->s[cur_step_arr->len-1]-1)/11) > 1; cur_step_arr->len++) {
        if (cur_step_arr->len==s_max_len) cur_step_arr->s = (int*)realloc(cur_step_arr->s, (s_max_len*=2)*sizeof(int));
        cur_step_arr->s[cur_step_arr->len] = cur_step;
    }
    if (cur_step_arr->len==s_max_len) cur_step_arr->s = (int*)realloc(cur_step_arr->s, (s_max_len+=1)*sizeof(int));
    cur_step_arr->s[cur_step_arr->len] = 1;
    cur_step_arr->len++;
    return cur_step_arr;
}

struct step_arr *step_tokuda(data *cur_data) {
    int n = cur_data->n;
    int s_max_len = 1;
    int cur_step;
    struct step_arr *cur_step_arr = (struct step_arr*)malloc(sizeof(struct step_arr));
    if (cur_step_arr == NULL) exit(-2);
    cur_step_arr->s = (int*)malloc(s_max_len*sizeof(int));
    if (cur_step_arr->s == NULL) exit(-2);
    for (cur_step_arr->len = 0; (cur_step = ceil((9*pow((double)9/(double)4, cur_step_arr->len)-4)/5))<n; cur_step_arr->len++) {
        if (cur_step_arr->len==s_max_len) cur_step_arr->s = (int*)realloc(cur_step_arr->s, (s_max_len*=2)*sizeof(int));
        cur_step_arr->s[cur_step_arr->len] = cur_step;
    }
    reverse_arr(cur_step_arr->s, cur_step_arr->len);
    return cur_step_arr;
}

struct step_arr *step_ciura(data *cur_data) {
    int n = cur_data->n;
    int s_max_len = 9;
    int cur_step;
    struct step_arr *cur_step_arr = (struct step_arr*)malloc(sizeof(struct step_arr));
    if (cur_step_arr == NULL) exit(-2);
    cur_step_arr->s = (int*)malloc(s_max_len*sizeof(int));
    if (cur_step_arr->s == NULL) exit(-2);
    cur_step_arr->s[0] = 1;
    cur_step_arr->s[1] = 4;
    cur_step_arr->s[2] = 10;
    cur_step_arr->s[3] = 23;
    cur_step_arr->s[4] = 57;
    cur_step_arr->s[5] = 132;
    cur_step_arr->s[6] = 301;
    cur_step_arr->s[7] = 701;
    cur_step_arr->s[8] = 1750;
    for (cur_step_arr->len = 9; (cur_step = floor(((double)9/(double)4)*cur_step_arr->s[cur_step_arr->len-1])) < n; cur_step_arr->len++) {
        if (cur_step_arr->len==s_max_len) cur_step_arr->s = (int*)realloc(cur_step_arr->s, (s_max_len*=2)*sizeof(int));
        cur_step_arr->s[cur_step_arr->len] = cur_step;
    }
    reverse_arr(cur_step_arr->s, cur_step_arr->len);
    return cur_step_arr;
}


void shell_sort(data *cur_data, struct step_arr *cur_step_arr) {
    int s_i, x, i, j;
    for (s_i = 0; s_i<cur_step_arr->len; s_i++) {
        for (i = cur_step_arr->s[s_i]; i<cur_data->n; i++) {
            x = cur_data->a[i];
            for (j=i-cur_step_arr->s[s_i]; j>=0 && cur_data->a[j]>x; j-=cur_step_arr->s[s_i]) cur_data->a[j+cur_step_arr->s[s_i]] = cur_data->a[j];
            cur_data->a[j+cur_step_arr->s[s_i]] = x;
        }
    }
}
