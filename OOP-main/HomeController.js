const change_view_home = document.getElementById("home")
change_view_home.addEventListener('click', function(){
    window.location.href='./Home.php';
})

const change_view_lobby = document.getElementById("lobby")
change_view_lobby.addEventListener('click', function(){
    window.location.href='./Lobby.php';
})

const change_view_forum = document.getElementById("forum")
change_view_forum.addEventListener('click', function(){
    window.location.href='./Forum.php';
})

const change_view_history = document.getElementById("history")
change_view_history.addEventListener('click', function(){
    window.location.href='./History.php';
})

const changeRoom = document.getElementById("changeRoom")
changeRoom.addEventListener('click', function(){
    window.location.href='./changeRoomController.php';
})