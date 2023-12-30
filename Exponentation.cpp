// binary exponentation pow function
long long my_pow(long long x, long long n)
{
    long long res = 1;
    while (n > 0)
    {
        if(n & 1 == 1)
            res = res * x;
        x = x * x;
        n = n >> 1;
    }
    return res;
}

// matrix multiplication
vector<vector<long long>> matrix_multiplication(vector<vector<long long>> a, vector<vector<long long>> b, long long size) {
    vector<vector<long long>> res(size, vector<long long>(size, 0));
    for (int i = 0; i < size; i ++)
    {
        for (int j = 0; j < size; j ++)
        {
            res[i][j] = 0;
            for (int k = 0; k < size; k ++)
                res[i][j] += (a[i][k] * b[k][j]) % MAX;
                res[i][j] %= MAX;
        }
    }
    return res;
}

// matrix exponentation
vector<vector<long long>> matrix_exponentation(vector<vector<long long>> mat, long long n, long long size) {
    vector<vector<long long>> res(size, vector<ll>(size, 0));
    ll ind = 0;
    while(ind < size) {
        res[ind][ind] = 1;
        ind ++;
    }
    while (n > 0) {
        if (n & 1)
            res = matrix_multiplication(res, mat, size);
        mat = matrix_multiplication(mat, mat, size);
        n >>= 1;
    }
    return res;
}