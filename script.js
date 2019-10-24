window.onload = setTimeout(function () {

  var welcomeScrn = document.getElementById("flyInBox").style;
  var fadeId = setInterval(fadeAnim, 40);
  var opacityVal = 1.0;

  $("#scrollPsAbout").one("mouseover", fadeIn);

  function fadeAnim() {

      if (opacityVal <= 0){
          clearInterval(fadeId);
          welcomeScrn.display = "none";
          document.body.style.overflowY = "scroll";
        }

    welcomeScrn.opacity = opacityVal;
    opacityVal -= 0.1;
  }

}, 2000);

function fadeIn() {

  var adrianCol = document.getElementById("a2").style;
  var adrianBW = document.getElementById("a1").style;
  var fadeIn = setInterval(fadeCol, 100);
  var opcValCol = 0.0;
  var opcValBW = 1.0;

  function fadeCol() {
      if (opcValCol >= 0.8) {
        adrianBW.opacity = opcValBW;
        opcValBW -= 0.1;
        if (opcValBW <= 0) {
          animDone = true;
          clearInterval(fadeIn);
        }
      }
      adrianCol.opacity = opcValCol;
      opcValCol += 0.1;
    }

}
