function displayGames(category) {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "/games?category=" + category, true);
    xhr.onreadystatechange = function() {
        if (xhr.readyState == 4 && xhr.status == 200) {
            var games = JSON.parse(xhr.responseText);
            renderGames(games);
        }
    };
    xhr.send();
}

function renderGames(games) {
    var gameButtonsFrame = document.getElementById("gameButtonsFrame");
    gameButtonsFrame.innerHTML = "";
    games.forEach(function(game) {
        var button = document.createElement("button");
        button.textContent = game.name;
        button.className = "gameButton";
        button.onclick = function() {
            runCommand(game.command);
        };
        gameButtonsFrame.appendChild(button);
    });
}

function runCommand(command) {
    var xhr = new XMLHttpRequest();
    xhr.open("POST", "/run_command", true);
    xhr.setRequestHeader("Content-Type", "application/json");
    xhr.onreadystatechange = function() {
        if (xhr.readyState == 4 && xhr.status == 200) {
            console.log("Command executed successfully");
        }
    };
    xhr.send(JSON.stringify({ command: command }));
}
