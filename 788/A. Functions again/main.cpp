//AC代码
#include <cstdio>
#define MAX 100003
#define ABS(x) ((x)>=0 ? (x) : -(x))
#define max(a, b) ((a)>(b) ? (a) : (b))

typedef long long LL;

int n;
LL a[MAX];
LL b[MAX];
LL d[MAX][2];

int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf("%lld", a + i);
		if(i > 0) {
			b[i - 1] = ABS(a[i] - a[i - 1]);
		}
	}
	d[0][0] = 0;
	d[0][1] = b[0];
	LL ans = b[0];
	for(int i = 1; i < n; i++) {
		if((i + 1) % 2) {
			d[i][0] = d[i - 1][0] - b[i];
			d[i][1] = max(d[i - 1][1] + b[i], b[i]);
			ans = max(ans, max(d[i][0], d[i][1]));
		}
		else {
			d[i][0] = max(d[i - 1][0] + b[i], b[i]);
			d[i][1] = d[i - 1][1] - b[i];
			ans = max(ans, max(d[i][0], d[i][1]));
		}
	}
	printf("%lld\n", ans);

	/*debug
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < 2; j++) {
			printf("%d %d %lld\n", i, j, d[i][j]);
		}
	}
	*/

	return 0;
}