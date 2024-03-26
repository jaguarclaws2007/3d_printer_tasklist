void handleInfo() {
  if (server.hasArg("projectName") && server.hasArg("projectId") && server.hasArg("color") && server.hasArg("filePrintTime") && server.hasArg("otherInfo") && server.hasArg("filamentType")) {
    int projectNum = server.arg("projectId").toInt();

    projectName[projectNum] = server.arg("projectName");
    filePrintTime[projectNum] = server.arg("filePrintTime") + " ";
    otherInfo[projectNum] = server.arg("otherInfo") + " ";
    filamentType[projectNum] = server.arg("filamentType") + " ";

    if (server.hasArg("otherColor")) {
      color[projectNum] = server.arg("otherColor") + " ";
    } else {
      color[projectNum] = server.arg("color") + " ";
    }

    String response = "Ok <a href='/'>Home</a>";
    server.send(200, "text/html", response);
  } else {
    String response = "Ok <a href='/'>Home</a>";
    server.send(200, "text/html", "No Params");
  }
}



void handleSetInfoProject() {
  if (server.hasArg("project")) {
    String projectNumber = server.arg("project");

    String html = "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Project Information Form</title><style>body {font-family: Arial, sans-serif;background-color: #f0f0f0;margin: 0;padding: 0;display: flex;justify-content: center;align-items: center;height: 100vh;}.container {background-color: #fff;padding: 30px;border-radius: 10px;box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.1);}form {max-width: 400px;margin: auto;}label {display: block;margin-bottom: 10px;font-weight: bold;}input[type=\"text\"],select {width: 100%;padding: 10px;border: 1px solid #ccc;border-radius: 5px;margin-bottom: 20px;box-sizing: border-box;}textarea {width: 100%;padding: 10px;border: 1px solid #ccc;border-radius: 5px;margin-bottom: 20px;box-sizing: border-box;resize: vertical;height: 100px;}small {font-size: 0.8em;color: #888;}button {background-color: #32326b;color: white;padding: 15px 20px;border: none;border-radius: 5px;cursor: pointer;font-size: 16px;}button:hover {background-color: #7b7bd4;}.other-color {display: none;}</style></head><body><div class=\"container\"><h2>Project Information</h2><form action=\"/sendInfo\" method=\"POST\" onsubmit=\"return validateForm()\"><label for=\"projectName\">Project Name:</label><input type=\"text\" id=\"projectName\" name=\"projectName\" required><input type=\"hidden\" id=\"projectId\" name=\"projectId\" value=" + projectNumber + " required><label for=\"color\">Color:</label><select id=\"color\" name=\"color\" onchange=\"showOtherColorInput(this.value)\" required><option value=\"null\">...</option><option value=\"any color\">Any Color</option><option value=\"white\">White</option><option value=\"black\">Black</option><option value=\"red\">Red</option><option value=\"orange\">Orange</option><option value=\"yellow\">Yellow</option><option value=\"blue\">Blue</option><option value=\"green\">Green</option><option value=\"purple\">Purple</option><option value=\"brown\">Brown</option><option value=\"grey\">Grey</option><option value=\"other\">Other</option></select><div id=\"otherColorInputDiv\" class=\"other-color\"><label for=\"otherColor\">Other Color:</label><input type=\"hidden\" id=\"otherColor\" > </div><label for=\"filePrintTime\">File Print Time <small>(from slicer)</small>:</label><input type=\"text\" id=\"filePrintTime\" name=\"filePrintTime\" required><label for=\"filamentType\">Filament Type:</label><input type=\"text\" id=\"filamentType\" name=\"filamentType\" required><label for=\"otherInfo\">Other Info:</label><textarea id=\"otherInfo\" name=\"otherInfo\" maxlength=\"320\" placeholder=\"Max 320 characters\"></textarea><button type=\"submit\">Submit</button></form></div><script>function showOtherColorInput(value) {var otherColorInputDiv = document.getElementById('otherColorInputDiv');var otherColorInput = document.getElementById('otherColor');if (value === 'other') {otherColorInputDiv.style.display = 'block';otherColorInput.setAttribute('name', 'otherColor');otherColorInput.setAttribute('required', '');otherColorInput.type = 'text';} else {otherColorInputDiv.style.display = 'none';otherColorInput.removeAttribute('required');otherColorInput.removeAttribute('name');otherColorInput.type = 'hidden';}}function validateForm(){var otherColorInput = document.getElementById('otherColorInput');if (value === '...') {alert(\"Please Enter Color\");}}</script><script>window.onload = function(){const headerButton = document.createElement('button');headerButton.style.cssText = 'background: none; border: none; padding: 0; position: absolute; right: 10px;';headerButton.onclick = openPopup;const headerImg = document.createElement('img');headerImg.src = 'https://static.thenounproject.com/png/1433173-200.png';headerImg.width = '50';headerImg.height = '50';headerImg.alt = 'QR code Scanner';headerButton.appendChild(headerImg);const header = document.createElement('header');header.appendChild(headerButton);document.body.prepend(header);function openPopup() {  const popup = window.open('https://jaguarclaws2007.github.io/3d_printer_tasklist/scan_qr_code.html', 'QRScannerPopup', 'width=400,height=400');  window.addEventListener('message', function(event) {    popup.close();    console.log('Scanned QR Code: ' + event.data);    location.href = event.data;  });}}</script></body></html>";
    server.send(200, "text/html", html);
  } else {
    server.sendHeader("Location", "/", true);
    server.send(302, "text/plain", "Error \n Redirecting...");
  }
}



void handleRoot() {
  String html = "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Projects</title><style>body {font-family: Arial, sans-serif;background-color: #f0f0f0;margin: 0;padding: 20px;}.container {display: flex;flex-wrap: wrap;justify-content: flex-start;max-width: 800px;margin: 0 auto;align-content: center;flex-direction: row;align-items: center;}.Project {width: calc(10% - 20px);margin-bottom: 20px;padding: 20px;background-color: #fff;border-radius: 10px;box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.1);text-align: center;transition: all 0.3s ease;}.Project:hover {transform: translateY(-5px);box-shadow: 0px 5px 15px rgba(0, 0, 0, 0.1);}.Project h3 {margin-bottom: 10px;color: #333;}.Project a {color: #007bff;text-decoration: none;}.Project a:hover {text-decoration: underline;}</style></head><body><div class=\"container\"><div class=\"Project\"><h3>Project 0</h3><a href=\"/setInfo?project=0\">Open Link</a></div><div class=\"Project\"><h3>Project 1</h3><a href=\"/setInfo?project=1\">Open Link</a></div><div class=\"Project\"><h3>Project 2</h3><a href=\"/setInfo?project=2\">Open Link</a></div><div class=\"Project\"><h3>Project 3</h3><a href=\"/setInfo?project=3\">Open Link</a></div><div class=\"Project\"><h3>Project 4</h3><a href=\"/setInfo?project=4\">Open Link</a></div><div class=\"Project\"><h3>Project 5</h3><a href=\"/setInfo?project=5\">Open Link</a></div><div class=\"Project\"><h3>Project 6</h3><a href=\"/setInfo?project=6\">Open Link</a></div><div class=\"Project\"><h3>Project 7</h3><a href=\"/setInfo?project=7\">Open Link</a></div><div class=\"Project\"><h3>Project 8</h3><a href=\"/setInfo?project=8\">Open Link</a></div><div class=\"Project\"><h3>Project 9</h3><a href=\"/setInfo?project=9\">Open Link</a></div></div><script>window.onload = function(){const headerButton = document.createElement('button');headerButton.style.cssText = 'background: none; border: none; padding: 0; position: absolute; right: 10px;';headerButton.onclick = openPopup;const headerImg = document.createElement('img');headerImg.src = 'https://static.thenounproject.com/png/1433173-200.png';headerImg.width = '50';headerImg.height = '50';headerImg.alt = 'QR code Scanner';headerButton.appendChild(headerImg);const header = document.createElement('header');header.appendChild(headerButton);document.body.prepend(header);function openPopup() {  const popup = window.open('https://jaguarclaws2007.github.io/3d_printer_tasklist/scan_qr_code.html', 'QRScannerPopup', 'width=400,height=400');  window.addEventListener('message', function(event) {    popup.close();    console.log('Scanned QR Code: ' + event.data);    location.href = event.data;  });}}</script></body></html>";
  server.send(200, "text/html", html);
}

void handleQrCode() {
  if (show == "home") {
    server.sendHeader("Location", "/", true);
    server.send(302, "text/plain", "Error \n Redirecting...");
  } else {
    server.sendHeader("Location", "/showInfo?id=" + show, true);
    server.send(302, "text/plain", "Redirecting...");
  }
}

void handleShowInfo() {
  if (server.hasArg("id")) {
    String projectNum = server.arg("id");

    String stOtherInfo = otherInfo[projectNum.toInt()];
    String stColor = color[projectNum.toInt()];
    String stFilePrintTime = filePrintTime[projectNum.toInt()];
    String stProjectName = projectName[projectNum.toInt()];
    String stfilamentType = filamentType[projectNum.toInt()];

    String html = "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Project Information Form</title><style>body {font-family: Arial, sans-serif;background-color: #f0f0f0;margin: 0;padding: 0;display: flex;justify-content: center;align-items: center;height: 100vh;}.container {background-color: #fff;padding: 30px;border-radius: 10px;box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.1);}form {max-width: 400px;margin: auto;}p {display: block;margin-bottom: 10px;font-weight: bold;}label {display: block;margin-bottom: 10px;font-weight: bold;}input[type=\"text\"],select {width: 100%;padding: 10px;border: 1px solid #ccc;border-radius: 5px;margin-bottom: 20px;box-sizing: border-box;}textarea {width: 100%;padding: 10px;border: 1px solid #ccc;border-radius: 5px;margin-bottom: 20px;box-sizing: border-box;resize: vertical;height: 100px;}small {font-size: 0.8em;color: #888;}button {background-color: #32326b;color: white;padding: 15px 20px;border: none;border-radius: 5px;cursor: pointer;font-size: 16px;}button:hover {background-color: #7b7bd4;}.other-color {display: none;}</style></head><body><div class=\"container\"><h2>Project Information</h2><p>Project Name: <span>" + stProjectName + "</span></p><p>Color: <span>" + stColor + "</span></p><p>File Print Time <small>(from slicer)</small>: <span>" + stFilePrintTime + "</span></p><p>Filament Type: <span>"+ stfilamentType +"</span></p><label for=\"otherInfo\">Other Info:</label><textarea id=\"otherInfo\" name=\"otherInfo\" placeholder=\"\" readonly>" + stOtherInfo + "</textarea></div><script>window.onload = function(){const headerButton = document.createElement('button');headerButton.style.cssText = 'background: none; border: none; padding: 0; position: absolute; right: 10px;';headerButton.onclick = openPopup;const headerImg = document.createElement('img');headerImg.src = 'https://static.thenounproject.com/png/1433173-200.png';headerImg.width = '50';headerImg.height = '50';headerImg.alt = 'QR code Scanner';headerButton.appendChild(headerImg);const header = document.createElement('header');header.appendChild(headerButton);document.body.prepend(header);function openPopup() {  const popup = window.open('https://jaguarclaws2007.github.io/3d_printer_tasklist/scan_qr_code.html', 'QRScannerPopup', 'width=400,height=400');  window.addEventListener('message', function(event) {    popup.close();    console.log('Scanned QR Code: ' + event.data);    location.href = event.data;  });}}</script></body></html>";
    server.send(200, "text/html", html);
  } else {
    server.sendHeader("Location", "/", true);
    server.send(302, "text/plain", "Error \n Redirecting...");
  }
}
