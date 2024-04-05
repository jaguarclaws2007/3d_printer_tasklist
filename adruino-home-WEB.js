function openMenu(menu, replace = null, name, lastEdited, parentProject) {
	if(replace){
		parentProject = parentProject.split(' ');
		parentProject = parentProject[0] + ': ' + parentProject[1];

		alert("Details: \n"+parentProject+"\n\tName: " + name +"\n\tlast Edited: " + lastEdited);
	}
	menu.style.display = "block";
	document.addEventListener("click", closeMenu);
}

function closeMenu() {
	const menus = document.querySelectorAll(".menu");
	menus.forEach(menu => {
		menu.style.display = "none";
	});
	document.removeEventListener("click", closeMenu);
}

function deleteProject(projectId) {
	console.log("Deleting project with ID: " + projectId);

	const deleteData = new FormData();
	deleteData.append('projectName', 'placeholderN' + projectId);
	deleteData.append('projectId', projectId);
	deleteData.append('color', 'placeholderC' + projectId);
	deleteData.append('filePrintTime', 'placeholderT' + projectId);
	deleteData.append('otherInfo', 'placeholderO' + projectId);
	deleteData.append('filamentType', 'placeholderFT' + projectId);
	deleteData.append('lastEdited', 'never');


	fetch('/sendInfo', {
		method: 'POST',
		headers: {
			'Content-Type': 'application/x-www-form-urlencoded'
		},
		body: new URLSearchParams(deleteData)
	})
	.then(response => {
		if (!response.ok) {
			throw new Error('Network response was not ok');
		}
		return response.json();
	})
	.then(data => {
		console.log('Success:', data);
	})
	.catch(error => {
		console.error('Error:', error);
	});
}

function viewDetails(element, projectId) {
	console.log("Viewing details of project with ID: " + projectId);
	let name = element.parentNode.parentNode.dataset.name;
	let lastEdited = element.parentNode.parentNode.dataset.lastedited;
	let parentProject = element.parentNode.parentNode.querySelector('h3').innerHTML
	openMenu(element, true, name, lastEdited, parentProject);
}

const menuIcons = document.querySelectorAll(".menu-icon");
	menuIcons.forEach(icon => {
		icon.addEventListener("click", function(event) {
		event.stopPropagation();
		openMenu(event.target.nextElementSibling);
	});
});
