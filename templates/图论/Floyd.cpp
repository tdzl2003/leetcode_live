for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (minC[i][j] > minC[i][k] + minC[k][j])
                minC[i][j] = minC[i][k] + minC[k][j];