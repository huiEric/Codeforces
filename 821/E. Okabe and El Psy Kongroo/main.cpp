#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef long long ll;
using namespace std;

const ll MAXK = 1e9 + 7;
typedef struct{
	ll m[17][17];
}Matrix;

Matrix A, d;

//维度可变的矩阵乘法
Matrix matrix_mul(Matrix A, Matrix B, int len) {
	Matrix C;
	memset(C.m, 0, sizeof(C.m));
	for(int i = 0; i < len; i++)
		for(int j = 0; j < len; j++) 
			for(int k = 0; k < len; k++) {
				C.m[i][j] += ((A.m[i][k] % MAXK) * (B.m[k][j] % MAXK)) % MAXK;
				C.m[i][j] %= MAXK;
			}
	return C;
}

Matrix matrix_quick_power(Matrix A, ll n, int len) {
	Matrix I, res;
	memset(I.m, 0, sizeof(I.m));
	//单位矩阵
	for(int j = 0; j < len; j++) 
		I.m[j][j] = 1;

	res = I;
	while(n) {
		if(n & 1) res = matrix_mul(res, A, len);
		A = matrix_mul(A, A, len);
		n /= 2;
	}
	return res;
}

int main() {
	int n; ll k;
	scanf("%d%lld", &n, &k);

	//初始化转移矩阵A和状态矩阵d
	memset(d.m, 0, sizeof(d.m));
	memset(A.m, 0, sizeof(A.m));
	d.m[0][0] = 1;
	for(int i = 0; i <= 15; i++)
		for(int j = i - 1; j <= i + 1; j++)
			if(j >= 0 && j <= 15)
				A.m[i][j] = 1;

	for(int i = 0; i < n; i++) {
		ll left, right; int y;
		scanf("%lld%lld%d", &left, &right, &y);
		if(right > k) right = k;
		Matrix temp = matrix_quick_power(A, right - left, y + 1);
		d = matrix_mul(d, temp, y + 1);	
		//清零无效状态
		for(int j = y + 1; j <= 15; j++) d.m[j][0] = 0;
	}

	printf("%lld\n", d.m[0][0]);
	return 0;
}