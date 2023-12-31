## 迷いの森
**[作成者]** 

前匠人　マエタクト

**[制作期間]** 

2023年　8月29日～9月29日

**[修正期間]** 

12月4日、7日

### 開発環境
使用言語：C++

使用ツール：DXLib

### ゲームの内容
製作途中ですが、ダンジョンRPGを制作しているところです。プレイヤーは、マス上のフィールドを動くことができ、
フィールドのどこかにある出口を見つけ、脱出するゲームとなっています。
プレイヤーが行動すると敵が行動し、プレイヤーの操作ターンに戻り、その繰り返しをするシステムになっています。

まだ実装途中ですが、マップのランダム生成や敵の攻撃、メッセージログなどを今後出していきたいと思っています。

### 操作方法
WASDキー：上下左右移動

Zキー：1ターン進める

SPACEキー：攻撃

（実装途中で分かりにくいですが、プレイヤーの上下左右方向にいる場合、3回当てると倒せます。）

ESCキー：メニュー表示

矢印キー：メニュー選択

### 制作目的
このゲームを制作した目的は、二次元配列の勉強やターンの制御をしたいと思い制作しました。
マップ上での、地形データやプレイヤー、敵の位置情報などをどのように配列で管理するのか、
またプレイヤーが行動するまでは敵は待機し、プレイヤーが行動したら敵も同時に行動して行動終了したら
また待機するといったターンの制御を勉強したいと思い、制作しました。

### 工夫した部分

・プレイヤーや敵の移動の仕方が瞬間移動にならないように徐々に移動させるように工夫しました。

・画面の切り替え時に徐々に暗くするフェード演出を付けたり、クリア時の切り替えには画面の黒色ではなく白色でフェード演出をして、
クリアしたように見せる工夫をしました。

・敵の行動方法が、向いている方向にまっすぐ進み、壁にぶつかったらランダムで向きを変えるといった、敵の行動方法を工夫しました。

・メニュー画面の表示の仕方で、なるべくコードの処理が複雑にならないようにシンプルに書くことや、
のちにメニューを追加するときコードを変更しやすいように、工夫しました。

・プレイシーンでの、プレイヤーや敵の行動シーケンスなど、コードの構造が複雑にならないように各シーケンスを
関数化して、シンプルに書くように工夫しました。

### Gameフォルダ以外にあるコードについて
自分が書いたコードはGameフォルダにあるもののみです。それ以外は、専門学校の講師が作成したコードとなっております。

### 使用素材

イラストAC

https://www.ac-illust.com/main/detail.php?id=2173013&word=%E3%83%AC%E3%83%88%E3%83%ADRPG%E3%82%B2%E3%83%BC%E3%83%A0%E9%A2%A8%E3%82%A6%E3%82%A3%E3%83%B3%E3%83%89%E3%82%A6+

ひみつ

http://uros.web.fc2.com/frame.html

ぴぽや倉庫

https://pipoya.net/sozai/assets/charachip/character-chip-1/

Musmus

https://musmus.main.jp/music_game.html

無料効果音で遊ぼう！

https://taira-komori.jpn.org/freesound.html

画像、音楽ファイルなどの素材の二次配布不可。

