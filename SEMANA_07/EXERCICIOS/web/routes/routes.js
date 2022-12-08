const express = require('express')
const router = express.Router()

const fs = require('fs')
const status = require('../status.json')

const bodyParser = require('body-parser')
const urlencodedParser = bodyParser.urlencoded({ extended: false })

// WINNER
router.get('/winner', (req, res) => {
  res.statusCode = 200
  res.setHeader('Access-Control-Allow-Origin', '*')

  var data = status.winner

  res.json(data)
})

router.post('/winner', urlencodedParser, (req, res) => {
  res.statusCode = 200
  res.setHeader('Access-Control-Allow-Origin', '*')

  status.winner = Number(req.body.winner)

  let data = JSON.stringify(status)

  fs.writeFile('status.json', data, err => {
    if (err) throw err
    console.log('Winner updated: ', status.winner)
  })

  res.json(status)
})

module.exports = router
