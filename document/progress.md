# やったこと
- npn init を用いてpackage.jsonを作成
- expressのgeneratorでできるディレクトリ構造を参考にテンプレートを作成
(view engine はejsを使用するように変更)
- node_modules内のbootstrapディテクトリ内でnpm install

# いじるところ
  静的ファイル：public内
  routes内
  views内
  app.js内に2行を追加
    var routes = require('./routes/index');
    app.use('/', routes);