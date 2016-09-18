# ENVIRONMENT
  Required environments
  ```bash
  $ node -v
  v4.5.0
  $ npm -v
  2.15.9
  ```

# HOW TO USE
1. Install modules with the npm
  Execute next commands at the server directory.
    ```bash
    npm install && cd node_modules/bootstrap && npm install
    ```

2. Ececute a node server
  Execute a next command at the server directory.
    ```bash
    npm start
    ```

3. Access to the node server from web browser
  Access to `http://localhost:3000`.

# HOW TO EDIT
  - static files:/public
  - views        :/routes /views and add next two codes at app.js
    ```javascript
    var routes = require('./routes/index');
    app.use('/', routes);
    ```