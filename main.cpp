#include <stdio.h>
#include <stdlib.h>

int g_ans_buf[20];

int * g_ans = g_ans_buf + 10;
int g_idx = 2;


int g_acts[20];

enum
{
    ACT_ERR,
    ACT_PASS,
    ACT_0,
    ACT_1,
    ACT_IF_B,
    ACT_IF_0,
    ACT_IF_1,
    ACT_LEFT,
    ACT_RIGHT
};


int action(int t_next, int f_next, int act)
{
    switch (act)
    {
        case ACT_ERR:
            fprintf(stderr, "act err\n");
            exit(-1);
        case ACT_0:
            g_ans[g_idx] = 0;
            return t_next;
        case ACT_1:
            g_ans[g_idx] = 1;
            return t_next;
        case ACT_IF_B:
            return  (g_ans[g_idx] == -1)?
                t_next: f_next;
        case ACT_IF_0:
            return  (g_ans[g_idx] == 0)?
                t_next: f_next;
        case ACT_IF_1:
            return  (g_ans[g_idx] == 1)?
                t_next: f_next;
        case ACT_LEFT:
            --g_idx;
            return  t_next;
        case ACT_RIGHT:
            ++g_idx;
            return  t_next;
        case ACT_PASS:
            return  t_next;
        default:
            fprintf(stderr, "-error act = %d\n", act);
            exit(0);
    }


}


int Next(int n)
{
    const int col_n = 5;

    int nt = (n <= col_n)? n + col_n: n - col_n;

    /* printf("n = %d, act=%d, nt = %d, g_idx = %d\n" */
    /*         ,n */
    /*         , g_acts[n] */
    /*         , nt */
    /*         , g_idx */
    /*         ); */

    if (n == 1)
        return action(nt, n+1, g_acts[n]);

    if (n == 4)
        return action(nt, n+1, g_acts[n]);

    if (n == 5)
        return action(1, nt, g_acts[n]);

    if (n == 10)
        return action(5, 100, g_acts[n]);


    return action(n+1, nt, g_acts[n]);
}

void initAction(void)
{
    int i;

    for (i = 0; i < 20; ++i)
        g_acts[i] = ACT_ERR;

    g_acts[1 ] = ACT_PASS;
    g_acts[2 ] = ACT_RIGHT;
    g_acts[3 ] = ACT_PASS;
    g_acts[4 ] = ACT_PASS;
    g_acts[5 ] = ACT_PASS;
    g_acts[6 ] = ACT_0;
    g_acts[7 ] = ACT_LEFT;
    g_acts[8 ] = ACT_1;
    g_acts[9 ] = ACT_LEFT;
    g_acts[10] = ACT_PASS;
    g_acts[11] = ACT_PASS;
    g_acts[12] = ACT_0;
    g_acts[13] = ACT_RIGHT;
    g_acts[14] = ACT_PASS;
    g_acts[15] = ACT_0;
    g_acts[16] = ACT_PASS;

    g_idx = 2;

    for (i = 0; i < 20; ++i)
        g_ans_buf[i] = -1;
}

int gogo(void)
{
    int i;

    g_ans[0] = 0;
    g_ans[1] = 0;
    g_ans[2] = 0;
    g_ans[3] = 0;
    g_ans[4] = 1;

    int ret = 1;
    int times = 0;

    while (1)
    {
        ++times;
        ret = Next(ret);
        if (ret > 50)
            break;

        if (times == 100)
        {
            printf("XXXXX\n");
            return -1;
        }
    }

    for (i = -10; i < 10; ++i)
    {
        if (g_ans[i] == -1)
            printf("X ");
        else
            printf("%d ", g_ans[i]);
    }
    printf("\n");

    return 0;
}

int main(int argc, const char * argv[])
{
    int act_set1[3] = {ACT_IF_B, ACT_IF_0, ACT_IF_1};

    int i, j, k, l,m, n;
    for (i = 0; i < 3; ++i)
    for (j = 0; j < 3; ++j)
    for (k = 0; k < 3; ++k)
    /* for (l = 0; l < 3; ++l) */
    /* for (m = 0; m < 3; ++m) */
    /* for (n = 0; n < 3; ++n) */
    {
        initAction();

        g_acts[1] = act_set1[i];
        g_acts[4] = act_set1[j];
        g_acts[10] = act_set1[k];
        /* g_acts[11] = act_set1[l]; */
        /* g_acts[14] = act_set1[m]; */
        /* g_acts[16] = act_set1[n]; */
        printf(">%d, %d, %d\n", i, j, k);
        gogo();
    }


    return 0;
}
