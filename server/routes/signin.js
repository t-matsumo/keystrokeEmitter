var express = require('express');
var router = express.Router();

router.get('/', function(req, res, next) {
  res.render('signin/signin', { title: 'Express' });
});

router.post('/', function(req, res, next) {
  if (false) {
    // res.render('サインイン後', { title: 'Express', error: true });
  } else {
    res.render('signin/signin', { title: 'Express', error: true });
  }
});

module.exports = router;
