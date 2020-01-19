/* SimplePageLoader */

    // Interpreter first checks loading state
    var isLoading = true,
        overlay = document.createElement("div");

    // A little bit of styling
    overlay.id = "before-content-overlay";
    overlay.style.background = "#ffffff";
    overlay.style.display = "block";
    overlay.style.position = "absolute";
    overlay.style.top = "0";
    overlay.style.bottom = "0";
    overlay.style.right = "0";
    overlay.style.left = "0";
    overlay.style.zIndex = "1000";

    // SVG Spinner
    overlay.innerHTML = "<svg class=\"lds-spinner\" width=\"64pxheight=\"64pxxmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" viewBox=\"0 0 100 100\" preserveAspectRatio=\"xMidYMid\" style=\"background: none;\"><g transform=\"rotate(0 50 50)\"><rect x=\"47\" y=\"24\" rx=\"9.4\" ry=\"4.8\" width=\"6\" height=\"12\" fill=\"#000000\"><animate attributeName=\"opacity\" values=\"1;0\" times=\"0;1\" dur=\"1s\" begin=\"-0.9166666666666666s\" repeatCount=\"indefinite\"></animate></rect></g><g transform=\"rotate(30 50 50)\"><rect x=\"47\" y=\"24\" rx=\"9.4\" ry=\"4.8\" width=\"6\" height=\"12\" fill=\"#000000\"><animate attributeName=\"opacity\" values=\"1;0\" times=\"0;1\" dur=\"1s\" begin=\"-0.8333333333333334s\" repeatCount=\"indefinite\"></animate></rect></g><g transform=\"rotate(60 50 50)\"><rect x=\"47\" y=\"24\" rx=\"9.4\" ry=\"4.8\" width=\"6\" height=\"12\" fill=\"#000000\"><animate attributeName=\"opacity\" values=\"1;0\" times=\"0;1\" dur=\"1s\" begin=\"-0.75s\" repeatCount=\"indefinite\"></animate></rect></g><g transform=\"rotate(90 50 50)\"><rect x=\"47\" y=\"24\" rx=\"9.4\" ry=\"4.8\" width=\"6\" height=\"12\" fill=\"#000000\"><animate attributeName=\"opacity\" values=\"1;0\" times=\"0;1\" dur=\"1s\" begin=\"-0.6666666666666666s\" repeatCount=\"indefinite\"></animate></rect></g><g transform=\"rotate(120 50 50)\"><rect x=\"47\" y=\"24\" rx=\"9.4\" ry=\"4.8\" width=\"6\" height=\"12\" fill=\"#000000\"><animate attributeName=\"opacity\" values=\"1;0\" times=\"0;1\" dur=\"1s\" begin=\"-0.5833333333333334s\" repeatCount=\"indefinite\"></animate></rect></g><g transform=\"rotate(150 50 50)\"><rect x=\"47\" y=\"24\" rx=\"9.4\" ry=\"4.8\" width=\"6\" height=\"12\" fill=\"#000000\"><animate attributeName=\"opacity\" values=\"1;0\" times=\"0;1\" dur=\"1s\" begin=\"-0.5s\" repeatCount=\"indefinite\"></animate></rect></g><g transform=\"rotate(180 50 50)\"><rect x=\"47\" y=\"24\" rx=\"9.4\" ry=\"4.8\" width=\"6\" height=\"12\" fill=\"#000000\"><animate attributeName=\"opacity\" values=\"1;0\" times=\"0;1\" dur=\"1s\" begin=\"-0.4166666666666667s\" repeatCount=\"indefinite\"></animate></rect></g><g transform=\"rotate(210 50 50)\"><rect x=\"47\" y=\"24\" rx=\"9.4\" ry=\"4.8\" width=\"6\" height=\"12\" fill=\"#000000\"><animate attributeName=\"opacity\" values=\"1;0\" times=\"0;1\" dur=\"1s\" begin=\"-0.3333333333333333s\" repeatCount=\"indefinite\"></animate></rect></g><g transform=\"rotate(240 50 50)\"><rect x=\"47\" y=\"24\" rx=\"9.4\" ry=\"4.8\" width=\"6\" height=\"12\" fill=\"#000000\"><animate attributeName=\"opacity\" values=\"1;0\" times=\"0;1\" dur=\"1s\" begin=\"-0.25s\" repeatCount=\"indefinite\"></animate></rect></g><g transform=\"rotate(270 50 50)\"><rect x=\"47\" y=\"24\" rx=\"9.4\" ry=\"4.8\" width=\"6\" height=\"12\" fill=\"#000000\"><animate attributeName=\"opacity\" values=\"1;0\" times=\"0;1\" dur=\"1s\" begin=\"-0.16666666666666666s\" repeatCount=\"indefinite\"></animate></rect></g><g transform=\"rotate(300 50 50)\"><rect x=\"47\" y=\"24\" rx=\"9.4\" ry=\"4.8\" width=\"6\" height=\"12\" fill=\"#000000\"><animate attributeName=\"opacity\" values=\"1;0\" times=\"0;1\" dur=\"1s\" begin=\"-0.08333333333333333s\" repeatCount=\"indefinite\"></animate></rect></g><g transform=\"rotate(330 50 50)\"><rect x=\"47\" y=\"24\" rx=\"9.4\" ry=\"4.8\" width=\"6\" height=\"12\" fill=\"#000000\"><animate attributeName=\"opacity\" values=\"1;0\" times=\"0;1\" dur=\"1s\" begin=\"0s\" repeatCount=\"indefinite\"></animate></rect></g></svg>";

    var spinner = overlay.childNodes[0];

    spinner.style.width = "64px";
    spinner.style.height = "64px";
    spinner.style.position = "absolute";
    spinner.style.left = spinner.style.top = "calc(50% - 32px)";

    // Once loaded
    window.onload = function() {
      isLoading = false;
      $('#flyInBox').removeClass('loading');
      $('#flyInBox').addClass('doneLoad');
      $('.h').addClass('round');
      start();

    	// Uncomment to test and comment/remove above statement
      // setTimeout(function() { isLoading = false }, 1000);
    };

    setInterval(function() {
      if (isLoading && !document.body.contains(overlay)) {
        document.body.appendChild(overlay);
      } else if (!isLoading && document.body.contains(overlay)) {
        // If loaded, overlay should disappear
        overlay.parentNode.removeChild(overlay);
      }
    }, 150);


  function start() {

  setTimeout( function() {
    var welcomeScrn = document.getElementById("flyInBox").style;
    var fadeId = setInterval(fadeAnim, 40);
    var opacityVal = 1.0;

    var hasScrolled = false;

    function fadeAnim() {

        if (opacityVal <= 0){
            clearInterval(fadeId);
            welcomeScrn.display = "none";
            document.body.style.overflowY = "scroll";
          }

      welcomeScrn.opacity = opacityVal;
      opacityVal -= 0.1;
    }

    $('body').scroll(function () {
        console.log($('body').scrollTop())
      if ($('body').scrollTop() > ($('#navigationMenu').height())-10) {
        $('#navigationMenu').addClass('stickyNav');
      }
      if ($('body').scrollTop() < ($('#navigationMenu').height())-10) {
        $('#navigationMenu').removeClass('stickyNav');
      }

      if ($('body').scrollTop()  > 580 && !hasScrolled) {
        fadeIn();
        hasScrolled = true;
      }
    });

  }, 3000);
}


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
