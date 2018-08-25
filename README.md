# FIFO trial

## これは何

rubyでスタックを作る実装をbddで進める課題の練習

せっかくふるまいを定義したので、c拡張とpure rubyで同じものを作成し、ベンチマークをとった

課題については[bdd-stack](https://github.com/jiraffeinc/bdd-stack)を参照

## benchmark

```
$ ruby bench/bench.rb
```

| | user | system | total | real |
|:--- | :--- | :--- | :--- | :--- |
| FIFO (c ext) | 0.150330 | 0.002457 | 0.152787 | 0.153376 |
| FIFO (ruby) | 0.044496 | 0.001956 | 0.046452 | 0.046825 |


スピードはrubyの方が約４倍速かった。

ソースの行数はrubyの35行に対してcが90行。

rubyが圧倒的にコンパクト、しかも雑につくったcより全然速い。

## 結論

```
＿人人人人人人人人人人人人＿
＞　C Launguage is dead　＜
￣Y^Y^Y^Y^Y^Y^Y^Y^Y^Y^￣
```

## 敗因

* cからrubyオブジェクトを生成・操作しているだけなので、C言語の良さが全く生きない

* GCを全く考慮していない

* リストを持つのにクラスをつくるのではなく、素の構造体を使うと早くなる（ような気がする）

## 苦労したところ

* 頑張ってvimだけで開発してみたが開発時間と脳ミソの半分をvimに捧げることになった

* コンパイルが通るまで時間がかかった。`init_xxxx` の関数名と `extconf.rb` の指定の不一致（大文字・小文字の違い）でハマる

## 参考

たまたま取り組んでいた[神資料](https://github.com/ko1/rubyhackchallenge/blob/master/JA/3_practice.md)を盛大に読み返しました。
これがなかったら不可能でした。（心で合掌）

