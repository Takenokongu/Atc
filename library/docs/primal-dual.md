## 概要

最小費用流を最短路反復で解くアルゴリズム. 始点から終点までの重みの最短路を求め, そこに流せる限り流す. これを流したい分だけ流しきるまで繰り返す. 最短路の計算は, ポテンシャル $h$ を用いて負辺がないように変換して Dijkstra法 で求める.

## 使い方

* `PrimalDual(V)`: 頂点数 $v$ で初期化する.
* `add_edge(from, to, cap, cost)`: 頂点 `from` から `to` に容量 `cap`、コスト `cost` の有向辺を張る.
* `min_cost_flow(s, t, f)`: 頂点 `s` から `t` に流量 `f` の最小費用流を流し, そのコストを返す. 流せないとき $-1$ を返す.
* `output()`: 最小費用流を復元して出力する.

## 計算量

* $O(FE \log V)$

$F$: 流量, $V$: 頂点数, $E$: 辺の本数