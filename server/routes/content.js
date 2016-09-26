var express = require('express');
var router = express.Router();

router.get('/', function(req, res, next) {
  res.render('content', { title: 'contents' });
});

module.exports = router;
