<div class="container">
  <h1>3D Printer Tasklist</h1>
  <p>If you are trying to use this for <span class="instructions">3D_Printer_Tasklist</span>, please go <a href="https://www.instructables.com/3D-Printer-Task-List/"> here</a> and follow the instructions.</p>
  <p>If you are trying to use this for your own use, you can use this code:</p>
  <div>
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
  <div><pre><code id="applet-code">javascript: const headerButton = document.createElement('button');headerButton.style.cssText = 'background: none; border: none; padding: 0; position: absolute; right: 10px;';headerButton.onclick = openPopup;const headerImg = document.createElement('img');headerImg.src = 'https://static.thenounproject.com/png/1433173-200.png';headerImg.width = '50';headerImg.height = '50';headerImg.alt = 'QR code Scanner';headerButton.appendChild(headerImg);const header = document.createElement('header');header.appendChild(headerButton);document.body.prepend(header);function openPopup() {	const popup = window.open('https://jaguarclaws2007.github.io/3d_printer_tasklist/scan_qr_code.html', 'QRScannerPopup', 'width=400,height=400');  window.addEventListener('message', function(event) {    popup.close();    console.log('Scanned QR Code: ' + event.data);    location.href = event.data;  })}</code></pre><div>
</div>
</body>
