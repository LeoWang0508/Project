const express = require('express');
const app = express();
const server = require('http').Server(app);
const io = require('socket.io')(server);

// 加入線上人數計數
let onlineCount = 0;

app.get('/*', (req, res) => {
    res.sendFile( __dirname + '/room.html');
});

io.on('connection', (socket) => {
    var url = socket.request.headers.referer;
    var splited = url.split('/');
    var roomID = splited[splited.length - 3];  // 獲取房間ID
    var player_num = splited[splited.length - 2];  // 第幾個使用者
    var player = splited[splited.length - 1];  // 使用者名稱
    var ID = roomID+"-"+player_num;
    var player1 = player.split('-')[0];
    var player2 = player.split('-')[1];

    // 有連線發生時增加人數
    onlineCount++;

    socket.join(ID);

    io.to(ID).emit("title", roomID);
    io.to(ID).emit("roomID", roomID);
    io.to(ID).emit("chatroom", roomID, player.split('-')[parseInt(player_num)-1]);
    io.to(ID).emit("board", roomID, player.split('-')[parseInt(player_num)-1]);
    io.to(ID).emit("player1", player1);
    io.to(ID).emit("player2", player2);
    if(player_num==="2"){
        io.to(roomID+"-1").emit("player2", player2);
        app.get('/*', (req, res) => {
            res.sendFile( __dirname + '/writeSQL.php?game='+game+'&player1='+player1+'&player2='+player2);
        });
    }

});

server.listen(4000, () => {
    console.log("Server Started. http://140.122.184.75:4000/#");
});


