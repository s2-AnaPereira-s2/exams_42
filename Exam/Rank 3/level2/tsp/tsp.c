#include <stdio.h>
#include <math.h>

typedef struct
{
    float x, y;
} Point;

float dist(Point a, Point b)
{
    return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

float path_len(Point *c, int *o, int n)
{
    float total = 0;
    for (int i = 0; i < n; i++)
        total += dist(c[o[i]], c[o[(i + 1) % n]]);
    return total;
}

void tsp(Point *c, int *o, int start, int n, float *min)
{
    if (start == n)
    {
        float d = path_len(c, o, n);
        if (d < *min)
            *min = d;
        return;
    }
    for (int i = start; i < n; i++)
    {
        int temp = o[start];
        o[start] = o[i];
        o[i] = temp;
        tsp(c, o, start + 1, n, min);
        temp = o[start];
        o[start] = o[i];
        o[i] = temp;
    }
}

int main()
{
    Point cities[11];
    int order[11];
    int n = 0;
    float x, y;
    while (fscanf(stdin, "%f, %f", &x, &y) == 2)
    {
        cities[n].x = x;
        cities[n].y = y;
        order[n] = n;
        n++;
    }
    float min_dist = 999999.0f;
    tsp(cities, order, 0, n, &min_dist);
    printf("%.2f\n", min_dist);
    return 0;
}
