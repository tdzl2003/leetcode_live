vector<mint> fac(n + 1), ifac(n + 1);
fac[0] = 1;
for (int i = 1; i <= n; i++) {
    fac[i] = fac[i - 1] * i;
}
ifac[n] = fac[n].inv();
for (int i = n; i >= 1; i--) {
    ifac[i - 1] = ifac[i] * i;
}