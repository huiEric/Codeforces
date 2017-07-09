#include <cstdio>
#include <cstring>
#include <algorithm>

//#define MAXN 1e5
using namespace std;

const int MAXN = 1e5;

int main() {
	static char s[MAXN + 2], t[MAXN + 2];
	scanf("%s%s", s+1, t+1);
	int n = strlen(s + 1), m = strlen(t + 1);

	//对照P213理解
	/* ch(i,c)记录t的前i个字符加上字母表的第c个字符后能匹配到t的前几个字符
	   0 <= i <= m;
	*/
	/* fail(i)是失配函数，
	   记录状态i失配后应转移到的新状态。
	   0 <= i <= m;
 	*/
	static int ch[MAXN + 1][26], fail[MAXN + 1];

	//t的前i-1个字符加上第i个字符能匹配到t的前i个字符
	for(int i = 1; i <= m; i++) ch[i - 1][t[i] - 'a'] = i;

	//KMP算法计算t的前i-1个字符加上任意字符能匹配到t的前多少个字符
	//t[0]，t[1]不匹配，回到t[0]进行匹配
	fail[0] = 0; fail[1] = 0; 
	//若t[i + 1]失配
	for(int i = 1; i <= m; i++) {
		if(i < m) {
			//沿着失配线倒回去，直到t的开头，或者匹配为止
			int j = fail[i];
			while(j && t[i + 1] != t[j + 1]) j = fail[j];
			//若匹配，则从匹配的下一个位置开始匹配；
			//若为t开始位置，则从t开始位置重新匹配
			//printf("%c %c\n", t[i + 1], t[j + 1]);
			fail[i + 1] = (t[i + 1] == t[j + 1] ? (j + 1) : 0);
		}

		for(int k = 0; k < 26; k++) {
			//如果加的字符不是t[i]，亦即失配
			if(!ch[i][k]) {
				//沿着失配线倒回去，得到最大匹配长度
				ch[i][k] = ch[fail[i]][k];
			}
		}
	}

	/*
	printf("\n%s\n", "fail:");
	for(int i = 0; i <= m; i++) printf("%d %d\n", i, fail[i]);

	printf("\n%s\n", "ch:");
	for(int i = 0; i <= m; i++)
		for(int j = 0; j < 26; j++)
			printf("%d %d %d\n", i, j, ch[i][j]);
	*/

	/* 
	   d(i,j)为s的前i个字符，
	   在其后缀匹配到t前缀的最大长度为j的情况下，
	   对t的最大匹配次数。
	   0 <= i <= n;
	   0 <= j <= m;
	*/
	int d[n + 1][m + 1];
	//无效值设为-1
	memset(d, -1, sizeof(d));
	//s的前0个字符，其后缀只能匹配到t的长度为0的前缀，其他值无意义
	d[0][0] = 0;
	/* 计算d(i+1,ch(j,c))
	   即s的前i个字符，
	   在后缀能匹配到j个字符的情况下，
	   接上s[i]或任意字符c(?时)，最多能匹配t几次。
	   注意，此时后缀匹配t前缀的长度变为ch(j,c)。
	   d(i+1,ch(j,c)) = max{d(i+1,ch(j,c)), d(i,j)+(ch(j,c)==m)}
	*/
	for(int i = 0; i < n; i++) 
		for(int j = 0; j <= m; j++) {
			//d(i,ch(j,_))无意义，则d(i+1,ch(j,_))无意义
			if(d[i][j] == -1) continue;
			//c为s的下一个字符
			for(int c = (s[i + 1] == '?' ? 0 : (s[i + 1] - 'a')); c < (s[i + 1] == '?' ? 26 : (s[i + 1] - 'a' + 1)); c++) {
				//ch(j,c)会多次重复出现，所以d(i+1,ch(j,c))值会多次改变
				d[i + 1][ch[j][c]] = max(d[i + 1][ch[j][c]], d[i][j] + (ch[j][c] == m));
				//if(i == 2 && j == 0) printf("\n%d %d %d\n\n", c, d[i][j], ch[j][c]);
			}
		}

	/*
	printf("\n%s\n", "d:");
	for(int i = 0; i <= n; i++) {
		for(int j = 0; j <= m; j++) {
			printf("%d %d %d\n", i, j, d[i][j]);
		}
	}
	*/

	int ans = 0;
	/* s的前n个字符，
       在其后缀匹配的t前缀长度任意的情况下，
       求最大值。
    */
	for(int i = 0; i <= m; i++) {
		//printf("%d\n", d[n][i]);
		ans = max(ans, d[n][i]);
	}
	printf("%d\n", ans);
	//system("pause");
	return 0;
}