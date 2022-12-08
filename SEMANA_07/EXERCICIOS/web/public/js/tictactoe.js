const resultDiv = document.getElementById('result')
const playAgainDiv = document.getElementById('play-again')

const winningScenarios = [
  [0, 1, 2],
  [3, 4, 5],
  [6, 7, 8],
  [0, 3, 6],
  [1, 4, 7],
  [2, 5, 8],
  [0, 4, 8],
  [2, 4, 6]
]

var boardSpaces = [0, 1, 2, 3, 4, 5, 6, 7, 8]

var playerX = []
var playerO = []

var currentPlayer = 1

function selectSpace(_element) {
  var position = Number(_element.id)

  if (boardSpaces.includes(position)) {
    if (currentPlayer) {
      _element.style.color = 'blue'
      _element.innerHTML += 'X'
      playerX.push(position)
    } else {
      _element.style.color = 'red'
      _element.innerHTML += 'O'
      playerO.push(position)
    }

    boardSpaces.splice(boardSpaces.indexOf(position), 1)
  }

  if (playerX.length + playerO.length > 4) {
    if (playerCheck(playerX)) {
      changeGameStatus(0, 'X')
    } else if (playerCheck(playerO)) {
      changeGameStatus(0, 'O')
    } else if (boardSpaces.length == 0) {
      changeGameStatus(1)
    }
  }

  console.log('Player X: ', playerX)
  console.log('Player O: ', playerO)
  console.log('Spaces Left: ', boardSpaces)

  currentPlayer = !currentPlayer
}

function playerCheck(_player) {
  const playerSpaces = _player

  for (var i = 0; i < winningScenarios.length; i++) {
    var checks = 0

    for (var j = 0; j < winningScenarios[i].length; j++) {
      if (playerSpaces.includes(winningScenarios[i][j])) {
        checks++
      }
    }

    if (checks > 2) {
      return true
    }
  }

  return false
}

function changeGameStatus(_status, _winner) {
  if (_status == 0) {
    if (_winner == 'X') {
      resultDiv.style.color = 'blue'
      postWinner(1)
    } else {
      resultDiv.style.color = 'red'
      postWinner(2)
    }
    resultDiv.innerHTML = `${_winner} WINS!`
    boardSpaces = []
  } else if (_status == 1) {
    resultDiv.style.color = 'yellow'
    resultDiv.innerHTML = 'TIE!'
    postWinner(3)
  } else {
    boardSpaces = [0, 1, 2, 3, 4, 5, 6, 7, 8]
    playerX = []
    playerO = []
    for (var i = 0; i < 9; i++) {
      document.getElementById(`${i}`).innerHTML = ''
    }
    resultDiv.innerHTML = ''
    postWinner(0)
  }
}

function postWinner(_winner) {
  let url = 'winner'

  let xhttp = new XMLHttpRequest()
  xhttp.open('post', url, false)
  xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded')

  var body = new URLSearchParams()
  body.append('winner', _winner)
  xhttp.send(body)

  let res = xhttp.response
  return res
}
