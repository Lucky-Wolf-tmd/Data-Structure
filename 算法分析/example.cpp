/* O(N^3)矩阵乘法 */
/*
* Standard matrix multiplication
* Arrays start at 0.
* Assumes a and b are square.
*/
matrix<int> operator*(const matrix<int>& a, const matrix<int>& b) {
	int n = a.numrows();
	matrix<int>c(n, n);

	int i;
	for (i = 0; i < n; i++)//Initialization
		for (int j = 0; j < n; j++)c[i][j] = 0;

	for (i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				c[i][j] += a[i][k] * b[k][j];
	return c;
}

/*斐波那契低效算法*/
/* Compute Fibonacci numbers */
int fib(int n) {
	if (n <= 1) return 1;
	else return fib(n - 1) + fib(n - 2);
}

//斐波那契线性算法
/* Compute Fibonacci numbers */
int fibonacci(int n) {
	if (n <= 1) return 1;
	int last = 1;
	int nexttoLast = 1;
	int answer = 1;
	for (int i = 2; i <= n; i++) {
		answer = last + nexttoLast;
		nexttoLast = last;
		last = answer;
	}
	return answer;
}

double eval_r(int n) {
	if (n == 0)return 1.0;
	else {
		double sum = 0.0;
		for (int i = 0; i < n; i++) sum += eval_r(i);
		return 2.0 * sum / n + n;
	}
}

double eval_l(int n)
{
	vector<double>c(n + 1);
	c[0] = 1.0;
	for (int i = 1; i <= n; i++) {
		double sum = 0.0;
		for (int j = 0; j < i; j++) sum += c[j];
		c[i] = 2.0 * sum / i + i;
	}
	return c[n];
}

/*找出矩阵乘法的最优顺序的程序*/
/*
* Compute optimal ordering of matrix multiplication
* c contains the number of rows in matrix 1.
* c[0] is the number of rows in matrix 1.
* The minimum number of multiplications is left in m[l][n].
* Actual ordering is computed via another procedure using lastChange.
* m and lastChange are indexed starting at 1,instead of 0.
* Note:Entries below main diagonals of m and lastChange
* are meaningless and uninitialized 
*/
void optMatrix(const vector<int>& c,
	matrix<long>& m, matrix<int>& lastChange) {
	int n = c.size() - 1;

	for (int left = 1; left <= n; left++) m[left][left] = 0;
	for(int k =1;k<n;k++) //k is right - left
		for (int left = 1; left <= n - k; left++)
		{
			//for each position
			int right = left + k;
			m[left][right] = INFINITY;
			for (int i = left; i < right; i++)
			{
				long thisCost = m[left][i] + m[i + 1][right]
					+ c[left - 1] * c[i] * c[right];
				if (thisCost < m[left][right])//Update min
				{
					m[left][right] = thisCost;
					lastChange[left][right] = i;
				}
			}
		}
}

/*
* Compute all-shortest paths.
* a contains the adjacency matrix with
* a[i][i] presumed to be zero.
* d contains the values of the shortest path.
* Vertices are numberd starting at 0; all arrays
* have equal dimension. A negative value.
* Actual path can be computed using path[][].
*/
const int NOT_A_VERTEX = -1;
void allPairs(const matrix<int>& a, matrix<int>& d, matrix<int>& path) {
	int n = a.numrows();
	//Initialize d and path
	for (int i = 0; i < n; j++)
		for (int j = 0; j < n; j++)
		{
			d[i][j] = a[i][j];
			path[i][j] = NOT_A_VERTEX;
		}
	for(int k  = 0;k<n;k++)
		//Condisder each vertex as an intermediate
		for(int i =0;i<n;i++)
			for(int j = 0;j<n;j++)
			if (d[i][k] + d[k][j] < d[i][j])
			{
				//update shortest path
				d[i][j] = d[i][k] + d[k][j];
				path[i][j] = k;
			}
}

/*
随机数生成器
*/

//线性同余算法
// x[i+1]=A*x[i] mod M  x[0]为种子