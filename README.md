# Atc
For Atcoder

# 解法が思いつかない時
- 解法が思いつかない時に見て考察に役立てる

## 発想
<details><summary>発想</summary><div>

- まず愚直に全探索を考える
    - その途中でDPなどの解法を思いつきやすくなったりする
- やることを分割する
- 何かを固定する
    - 固定するものが計算量につながることはよくある
    - 愚直は2^Nでも1つずつ固定していく解法はよくある
- 対称性を見出す
    - 2次元のものを1次元ずつ処理
- 不変量に注目
    - 将棋の角のように、x座標+y座標の偶奇が変わらないもの
    - 操作で何かを+1して何かを-1する、など合計がかわらないもの
    - 約数の交換で積が変わらないもの
- 操作系
    - 操作の順番を入れ替えても結果が変わらないか
    - 操作を逆順に考える
    - 操作結果の同値類を考える
        - 考えられる同値類の数が1e5付近までならメモ化やDPが使えるかも
- 数え上げ系
    - DPできないか考えてみる
    - いくつかの数列があり、平均が K となる組み合わせを求めるときは、
        - 「合計値が K × 個数」となる組み合わせ
        - 「元の値をすべて-K した数列で、合計値が 0」となる組み合わせ
        -  というように変更すると考えやすくなることがあります。
- 区間系
    - 左右両方から累積情報を前処理する
        - というかBITとかセグ木を使わない時は基本累積以外手はない
    - いもす法で区間和を求める方法もある
        - 座標圧縮することもありそう
    - 区間和に対応しているBITもあるらしい
    - 区間の削除、圧縮、合成をするときは区間DPが使えることも
- 不偏ゲームはGrundy数を考える
    - [Grundy数](https://algo-logic.info/combinatorial-games/)
    - Nimにおいて山が一つでコインが一つという状態の勝敗から考え始め、頑張って一般化して法則を導き出す、部分ゲームを考えるのは大事
- 二分探索
    - f(x)=yが単調増加ならyを決め打ちして二分探索に持っていける
- 余事象
    - 全体の場合の数から余事象の数を引く
- K番目の数を求める
    - 要素の値が小さければBITなどで出せる
    - 二分探索もよく使う
- xorを桁ごとに考える
    - xor が「繰り上がりのない足し算」ということは、ある桁がどんな数であっても、xorをして他の桁に影響を与えることがありません。
    - 故に、xor を何度も使用する問題には「桁ごとにxorを計算して最後にまとめる」という手法が使えることがあります。特定の桁において、xorをする数それぞれで1が出現する回数が偶数なら最終的な答えは0、奇数なら1になります。
- マンハッタン距離
    - 45度回転させる
- 差の最小化は中央値を使うのがよい
- グラフ
    - エッジケースの考え方
        - パスグラフ（直線上に繋げたグラフ）
        - スターグラフ（一つの頂点から、他のすべての頂点に1つずつ辺が出ているグラフ）
        - 完全グラフ（任意の２頂点間に辺があるグラフ）
        - 完全二部グラフ（二部グラフのうち、可能な限り辺をつないだもの）
パスグラフに少し辺を足したグラフ
- 何らかの最大化
    - 二分探索
    - 選択肢が少ないほうから見て貪欲法
- 積の総和は和の積になる、数学ゲー
- かっこ列は"("で+1、")"で-1と考える
    - 最後に0になる
    - 途中でマイナスにならない
- 選ぶ要素の間隔をK開けて、K=1~nを求めるなど
    - 調和級数をうまいことやると1個あたりO(logN)で求められるらしい
    
</div></details>

## Nの制約からアルゴリズムを予想する
<details><summary>Nの制約からアルゴリズムを予想する</summary><div>

### N=8
- 順列全探索 O(N*N!)

### N=10~20
- bit全探索 O(2^N)
- 包除原理とかも
- bitDP O(2^N*N^2)

### N=30~40
- 半分全列挙 O(N*2^(N/2))

### N=50
- 4重ループ O(N^4)

### N=300~500
- 3重ループ O(N^3)

### N=1000
- 2重ループと二分探索など O(N^2logN)

### N=3000
- 2重ループ O(N^2)

### N=10^5
- ソートなど O(NlogN)

---

### N=10^9~10^18
- Ai=1e9のときは座標圧縮など

### N>10^18
- 桁ごとに考える

---

### 小さいmodがある場合
- modワールドを考える

### 意味深な定数
- 2種類の状態、じゃんけん、4等分、10進法の最後の桁などなど定数を見いだせるもの

</div></details>

## DPについて
<details><summary>DPについて</summary><div>

- 動的計画法のこと。ナップサックや部分和問題を解ける
- ちなみに部分和問題で和がX以上などの条件になる場合はmin(dp[X], dp[i+Ai])みたいになる
- うまいこと漸化式を立てることによって計算量O(N)で解けるようにするのが基本
- [drkenさんの記事](https://qiita.com/drken/items/a5e6fe22863b7992efdb)

### ナップサック問題
- dp[i個目の品物][重さがwを超えない]
    - i番目までの品物の中から重さがwを超えないように選んだ時の価値の総和の最大値
- 品物の個数をi、重さをw、価値の総和をvalueで持っている
- 半分全列挙とも組み合わせられそう

### 部分和問題
- 数字を何個か選んで総和をXにすることができるか
    - dp[0]=1で始め、dp[i]にboolを入れていく
    - 計算量はO(N*X)
- 多次元になることもある

### 部分和数え上げ問題
- 部分和の答えが何通りあるか
    - dp[0]=1で始め、dp[i]に整数を入れていく。添え字の大きいほうから処理するとバグらない

### 最小個数部分和問題
- 部分和を作れる最小個数を求める
    - valueに今までに使った個数を入れるとうまくいく

### 最長共通部分列 (LCS) 問題
- 2次元DPの一種
    - sの部分文字列とtの部分文字列で等しいもののうち最長のもの
    - O(|s|*|t|)

### 最小コスト弾性マッチング問題
- これもDPの一種

### レーベンシュタイン距離 (diffコマンド)
- これも
- リンク先にコードあり

### 発電計画問題
正の整数 T が与えられ、t=0,...,T−1t=0,...,T−1 のそれぞれについて時刻 [t,t+1][t,t+1] の間に発電装置をオンにするかオフにするかを決める必要がある。発電計画においてオンになっている区間が [l0,r0][l0,r0], [l1,r1][l1,r1], ..., [lk−1,rk−1][lk−1,rk−1] (0≤l0<r0<l1<r1<⋯<lk−1<rk−1≤T)(0≤l0<r0<l1<r1<⋯<lk−1<rk−1≤T) であった場合の利得は、各 i,ji,j (0≤i<j≤T)(0≤i<j≤T) に対して定義された値 g[i][j]g[i][j] を用いて、g[l0][r0]+g[l1][r1]+⋯+g[lk−1][rk−1]g[l0][r0]+g[l1][r1]+⋯+g[lk−1][rk−1] で与えられる。発電計画を最適化して得られる利得の最大値を求めよ。

### 分かち書き
- 文章を単語ごとに区切る作業

### 区間 DP
- 行列積問題
- 最適二分探索木問題
- randomized quicksort における swap 回数の期待値 (SRM486 DIV1 Medium QuickSort)
- iwi問題 (TDPC I - イゥイ)
- 回文の何か
- 四則とか
- (余裕あったら) Monge性とか

### bit DP
- 巡回セールスマン問題
- 完全マッチングの数え上げ問題
- トポロジカルソートの数え上げ問題 (ABC 041 D 徒競走)
- タイル色塗り (SRM532 DIV2 Hard DengklekPaintingSquares)
- 数え上げお姉さん問題

</div></details>

## BIT（Binary Indexed Tree）
<details><summary>BIT（Binary Indexed Tree）</summary><div>

### https://algo-logic.info/binary-indexed-tree/
- 1点加算 O(logN)
- 区間加算（RAQ: Range Add Query） O(logN)
- BIT上での二分探索 O(logN)
- 転倒数 O(NlogN)
- w番目に小さい要素を取得 O(logN)
- 2次元のBITも考えられる

</div></details>

## テンプレ
<details><summary>テンプレ</summary><div>

</div></details>