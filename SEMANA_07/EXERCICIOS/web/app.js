const express = require('express')
const app = express()

const hostname = '127.0.0.1'
const port = process.env.PORT || 8080

const routes = require('./routes/routes.js')

app.use(routes)

app.use(express.json())

app.use(express.static('public'))

const server = app.listen(port, () => {
  console.log(`Servidor executando em http://${hostname}:${port}`)
})
