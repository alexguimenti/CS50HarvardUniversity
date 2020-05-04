const player1 = "X";
const player2 = "O";
var playTime = player1;
var gameOver = false;

updateDisplay();
startSpaces();

function updateDisplay() {
  if (gameOver) {return;}

  if (playTime == player1) {
    var player = document.querySelector("#display img");
    player.setAttribute("src", "images/x.png");
  }

  else {
    var player = document.querySelector("#display img");
    player.setAttribute("src", "images/o.png");
    }
}

function startSpaces() {
  var div = document.querySelectorAll(".space");
  for (let i = 0; i < div.length; i++) {
    div[i].addEventListener("click", function() {
      if (gameOver) {return;}

      if(this.getElementsByTagName("img").length == 0){

        if (playTime == player1){
          this.innerHTML = "<img src='images/x.png'>";
          this.setAttribute("play", player1);
          playTime = player2;
        }

        else {
          this.innerHTML = "<img src='images/o.png'>";
          this.setAttribute("play", player2);
          playTime = player1;
        }
      updateDisplay();
      winnerCheck();
      }
    })
  }
}

async function winnerCheck(){

  var winner = "";

  var a1 = document.querySelector("#a1").getAttribute("play");
  var a2 = document.querySelector("#a2").getAttribute("play");
  var a3 = document.querySelector("#a3").getAttribute("play");

  var b1 = document.querySelector("#b1").getAttribute("play");
  var b2 = document.querySelector("#b2").getAttribute("play");
  var b3 = document.querySelector("#b3").getAttribute("play");

  var c1 = document.querySelector("#c1").getAttribute("play");
  var c2 = document.querySelector("#c2").getAttribute("play");
  var c3 = document.querySelector("#c3").getAttribute("play");

  if ((a1 == b1 && a1 == c1 && a1 != "") || (a1 == a2 && a1 == a3 && a1 != "") || (a1 == b2 && a1 == c3 && a1 != "")){
    winner = a1;
  }

  else if ((b2 == b1 && b2 == b3 && b2 != "") || (b2 == a2 && b2 == c2 && b2 != "") || (b2 == a3 && b2 == c1 && c1 != "")){
    winner = b2;
  }

  else if ((c3 == c2 && c3 == c1 && c3 != "") || (c3 == a3 && c3 == b3 && c3 != "")){
    winner = c3;
  }

  else if (a1 != "" && b1 != "" && c1 != "" && a2 != "" && b2 != "" && c2 != "" && a3 != "" && b3 != "" && c3 != "") {
    gameOver = true;

    await sleep(50);
    alert("Velha!");
  }

  if (winner != "") {
    gameOver = true;

    await sleep(50);
    setTimeout(function(){ 
        alert("The winner is: " + winner); }, 700);
  }
}

function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

function newGame(){
  var div = document.querySelectorAll(".space");
  for (let i = 0; i < div.length; i++) {
      div[i].innerHTML = "";
      div[i].setAttribute("play", "");
      updateDisplay();
      startSpaces();
      gameOver = false;
  }
}