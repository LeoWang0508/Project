const express = require('express');
const app = express();
const server = require('http').Server(app);
const io = require('socket.io')(server);

// 加入線上人數計數
let onlineCount = 0;

app.get('/*', (req, res) => {
    res.sendFile( __dirname + '/chatroom.html');
});

io.on('connection', (socket) => {
    var url = socket.request.headers.referer;
    var splited = url.split('/');
    var roomID = splited[splited.length - 2];  // 獲取房間ID
    var username = splited[splited.length - 1]; //使用者名稱
    // 有連線發生時增加人數
    onlineCount++;

    socket.join(roomID);
    // 發送人數給網頁
    io.emit("online", onlineCount);
    io.to(roomID).emit("name", username);

    socket.on("greet", () => {
        socket.emit("greet", onlineCount);
    });

    socket.on("send", (msg) => {
        // 如果 msg 內容鍵值小於 2 等於是訊息傳送不完全
        // 因此我們直接 return ，終止函式執行。
        if (Object.keys(msg).length < 2) return;

        // 廣播訊息到聊天室
        
        io.to(roomID).emit("msg", msg);
        //console.log(msg);
    });

    socket.on('disconnect', () => {
        // 有人離線了，扣人
        onlineCount = (onlineCount < 0) ? 0 : onlineCount-=1;
        io.to(roomID).emit("online", onlineCount);
    });
});

server.listen(3000, () => {
    console.log("Server Started. http://140.122.184.75:3000/#");
});

