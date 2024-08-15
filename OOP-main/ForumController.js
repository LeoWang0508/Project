const post = document.getElementById("post")
post.addEventListener('click', function(){
    window.location.href='./post.php';
})

const get_forum = document.getElementById("get_forum")
get_forum.addEventListener('click', function(){
    window.location.href='./get_forum.php';
})

const change_view_forum_detail = document.getElementById("forum_detail")
change_view_forum_detail.addEventListener('click', function(){
    window.location.href='./forum_detail.php';
})