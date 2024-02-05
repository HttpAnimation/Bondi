fetch('https://raw.githubusercontent.com/HttpAnimation/Bondi/stable/Installing.md')
.then(response => response.text())
.then(data => {
  document.querySelector('md-block').innerHTML = data;
})
.catch(error => console.error('Erorr getting the mark down file:', error));