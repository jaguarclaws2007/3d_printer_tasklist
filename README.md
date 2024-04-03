<style>
  body {
    font-family: Arial, sans-serif;
    margin: 0;
    padding: 0;
    background-color: #f4f4f4;
  }
  .container {
    max-width: 800px;
    margin: 50px auto;
    padding: 20px;
    background-color: #fff;
    border-radius: 8px;
    box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
    position: relative; /* Added for positioning the toolbar */
  }
  .instructions {
    color: green;
  }
  code {
    display: inherit;
    overflow: auto;
    background-color: black;
    color: white;
    padding: 10px;
  }
  pre{
	margin-top: 0px;
  }
  .toolbar {
	display: inherit;
	width: inherit;
  }
  .copy-icon {
    cursor: pointer;
  }
</style>
</head>
<body>

<div class="container">
  <h1>3D Printer Tasklist</h1>
  <p>If you are trying to use this for <span class="instructions">3D_Printer_Tasklist</span>, please go <a href="https://www.instructables.com/3D-Printer-Task-List/"> here</a> and follow the instructions.</p>
  <p>If you are trying to use this for your own use, you can use this code:</p>
  <div>
		<div class="toolbar">
			<img src="https://img.icons8.com/material-outlined/24/000000/copy--v1.png" class="copy-icon" alt="Copy" id="Copy-code" title="Copy Code">
		</div>
	  <pre>
		  <code id="code">window.onload = function(){
	const headerButton = document.createElement('button');
	headerButton.style.cssText = 'background: none; border: none; padding: 0; position: absolute; right: 10px;';
	headerButton.onclick = openPopup;
	const headerImg = document.createElement('img');
	headerImg.src = 'https://static.thenounproject.com/png/1433173-200.png';
	headerImg.width = '50';
	headerImg.height = '50';
	headerImg.alt = 'QR code Scanner';
	headerButton.appendChild(headerImg);
	const header = document.createElement('header');
	header.appendChild(headerButton);document.body.prepend(header);
}

function openPopup() {	
	const popup = window.open('https://jaguarclaws2007.github.io/3d_printer_tasklist/scan_qr_code.html', 'QRScannerPopup', 'width=400,height=400');  
	window.addEventListener('message', function(event) {
		popup.close();    
		console.log('Scanned QR Code: ' + event.data);    
		location.href = event.data;  
	})
}
		  </code>
	  </pre>
  </div>
  <p>Here is an applet version</p>
  <div>
	<div class="toolbar">
		<img src="https://img.icons8.com/material-outlined/24/000000/copy--v1.png" class="copy-icon" alt="Copy" id="Copy-applet" title="Copy Applet">
	</div>
	<pre>
		<code id="applet-code">javascript: const headerButton = document.createElement('button');headerButton.style.cssText = 'background: none; border: none; padding: 0; position: absolute; right: 10px;';headerButton.onclick = openPopup;const headerImg = document.createElement('img');headerImg.src = 'https://static.thenounproject.com/png/1433173-200.png';headerImg.width = '50';headerImg.height = '50';headerImg.alt = 'QR code Scanner';headerButton.appendChild(headerImg);const header = document.createElement('header');header.appendChild(headerButton);document.body.prepend(header);function openPopup() {	const popup = window.open('https://jaguarclaws2007.github.io/3d_printer_tasklist/scan_qr_code.html', 'QRScannerPopup', 'width=400,height=400');  window.addEventListener('message', function(event) {    popup.close();    console.log('Scanned QR Code: ' + event.data);    location.href = event.data;  })}
		</code>
	</pre>
  <div>
</div>

<script>
document.addEventListener("DOMContentLoaded", function() {
  const copy_code = document.getElementById("Copy-code");
  const copy_applet = document.getElementById("Copy-applet");
  
  const applet = document.getElementById('applet-code');
  const code = document.getElementById('code');

  copy_code.addEventListener("click", function() {
    const codetoCopy = code.innerText.trim();
    copyToClipboard(codetoCopy);
    alert("Code copied to clipboard!");
  });
  
  copy_applet.addEventListener("click", function() {
    const codetoCopy = applet.innerText.trim();
    copyToClipboard(codetoCopy);
    alert("Code copied to clipboard!");
  });

  function copyToClipboard(text) {
    const textarea = document.createElement("textarea");
    textarea.value = text;
    document.body.appendChild(textarea);
    textarea.select();
    document.execCommand("copy");
    document.body.removeChild(textarea);
  }
});
</script>

</body>
</html>
