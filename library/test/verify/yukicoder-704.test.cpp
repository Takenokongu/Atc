#define PROBLEM "https://yukicoder.me/problems/no/704"

#include "../../template/template.cpp"

#include "../../dp/online-offline-dp.cpp"

int main() {
  int n;
  cin >> n;
  vector< int > a(n), x(n), y(n);
  for(int i = 0; i < n; i++) cin >> a[i];
  for(int i = 0; i < n; i++) cin >> x[i];
  for(int i = 0; i < n; i++) cin >> y[i];
  function< int64_t(int, int) > dist = [&](int i, int j) {
    assert(0 <= i && i < j && j <= n);
    int s = abs(a[j - 1] - x[i]);
    int t = abs(y[i]);
    return s + t;
  };
  cout << online_offline_dp(n, dist).back() << endl;
}
