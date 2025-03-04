#include "dijkstra.h"
#include <assert.h>
#include <stdio.h>

int main(void) 
{
void *dijkstra = dijkstra_init();
assert(dijkstra);

int edges[23][3] = 
{{0, 1, 4},
{0, 3, 85},
{1, 0, 74},
{1, 2, 18},
{1, 4, 12},
{2, 1, 12},
{2, 5, 74},
{2, 9, 12},
{3, 4, 32},
{3, 6, 38},
{4, 3, 66},
{4, 5, 76},
{4, 7, 33},
{5, 9, 21},
{5, 8, 11},
{6, 7, 10},
{6, 3, 12},
{7, 6, 2},
{7, 8, 72},
{8, 7, 18},
{8, 5, 31},
{8, 9, 78},
{9, 5, 8}};
_Bool success = dijkstra_set_graph(23, edges, dijkstra);
assert(success);

success = dijkstra_solve(dijkstra, 0);
assert(success);

int solution[10][3];
success = dijkstra_get_solution(dijkstra, 10, solution);
assert(success);

for (int i = 0; i < 10; i++)
{
    printf("%d %d %d\n", solution[i][0], solution[i][1], solution[i][2]);
}

dijkstra_free(dijkstra);

return 0;
}
