//AC代码
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAX 1000
#define MAP(i) ((i)+1001)
#define ABS(x) ((x)>=0 ? (x) : -(x))

int n, k;
char s[MAX + 1];
int d[MAX + 1][2*MAX + 3];

void print(int n, int k) {
	char ans[MAX + 1];
	int j;
	if(d[n][MAP(k)]) j = k;
	else if(d[n][MAP(-k)]) j = -k;
	else {
		printf("NO\n");
		return;
	}
	ans[n] = '\0';
	for(int i = n - 1; i >= 0; i--) {
		if(ABS(j) < k && (s[i] == 'D' || (s[i] == '?' && d[i][MAP(j)]))) {
			ans[i] = 'D'; 
			continue;
		}
		else if(ABS(j + 1) < k && (s[i] == 'L' || (s[i] == '?' && d[i][MAP(j + 1)]))) {
			ans[i] = 'L'; 
			j++; 
			continue;
		}
		else if(ABS(j - 1) < k && (s[i] == 'W' || (s[i] == '?' && d[i][MAP(j - 1)]))) {
			ans[i] = 'W'; 
			j--; 
			continue;
		}
		else {
			printf("NO\n"); 
			return;
		}
	}
	printf("%s\n", ans);
}

int main() {	
	scanf("%d%d%s", &n, &k, s);

	memset(d, 0, sizeof(d));
	d[0][MAP(0)] = 1;
	
	for(int i = 0; i < n; i++) {
		for(int j = -k; j <= k; j++) {
			if(i != n-1) {
				if(j == -k || j == k) continue;
			}
			switch(s[i]) {
				case 'D' : d[i + 1][MAP(j)] = d[i][MAP(j)] ? 1 : 0;break;
				case 'L' : d[i + 1][MAP(j)] = d[i][MAP(j + 1)] ? 1 : 0;break;
				case 'W' : d[i + 1][MAP(j)] = d[i][MAP(j - 1)] ? 1 : 0; break;
				case '?' : d[i + 1][MAP(j)] = (d[i][MAP(j)] || d[i][MAP(j + 1)] || d[i][MAP(j - 1)]) ? 1 : 0;break;
			}
		}
	}
	print(n, k);

	/* debug
	printf("\n");
	for(int i = 0; i <= n; i++) {
		for(int j = -k; j <= k; j++) {
			if(d[i][MAP(j)]) {
				//printf("%d %d %d ", i, j, d[i][MAP(j)]);
				//print(i, ABS(j));
				//printf("\n");
			}
		}
	}
	*/

	return 0;  
}