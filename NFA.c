#include <stdio.h>
#include <string.h>

#define MAX_STATES 50

int eps[MAX_STATES][MAX_STATES];

// helper to parse "q<number>"
static int parse_state(const char* tok) {
	int idx = -1;
	if (sscanf(tok, "q%d", &idx) == 1) return idx;
	if (sscanf(tok, "Q%d", &idx) == 1) return idx;
	return -1;
}

void dfs(int n, int u, int vis[]) {
	int v;
	for (v = 0; v < n; v++) {
		if (eps[u][v] && !vis[v]) {
			vis[v] = 1;
			dfs(n, v, vis);
		}
	}
}

int main() {
	// clear eps
	for (int i = 0; i < MAX_STATES; i++)
		for (int j = 0; j < MAX_STATES; j++)
			eps[i][j] = 0;

	int m;
	printf("Enter number of transitions: ");
	if (scanf("%d", &m) != 1 || m < 0) return 0;

	char a[32], b[32], c[32];
	int max_state = -1;

	printf("Enter each transition as: qX sym qY (e.g., q0 0 q0 or q0 e q1)\n");
	for (int i = 0; i < m; i++) {
		if (scanf("%31s %31s %31s", a, b, c) != 3) continue;
		int from = parse_state(a);
		int to   = parse_state(c);
		if (from < 0 || to < 0 || from >= MAX_STATES || to >= MAX_STATES) continue;
		if (b[0] == 'e' || b[0] == 'E') eps[from][to] = 1;
		if (from > max_state) max_state = from;
		if (to > max_state) max_state = to;
	}

	if (max_state < 0) return 0;

	int n = max_state + 1;
	int vis[MAX_STATES];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) vis[j] = 0;
		vis[i] = 1;
		dfs(n, i, vis);

		printf("E-closure(q%d) = {", i);
		int first = 1;
		for (int j = 0; j < n; j++) {
			if (vis[j]) {
				if (!first) printf(", ");
				printf("q%d", j);
				first = 0;
			}
		}
		printf("}\n");
	}
	return 0;
}