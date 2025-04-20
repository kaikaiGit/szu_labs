const btn = document.querySelector(".check ")
const modal = document.querySelector(".modal")
const text = document.querySelector(".modal-body input")

const names = document.querySelector("form input")
btn.addEventListener("click",
function(){
    if(text.value==''){
        alert("请输入你的姓名！");
    }
    else {
        names.value = text.value;
        text.value='';
        alert(`你的姓名是：${names.value}`);
        $("#exampleModal").modal('hide');
    }

})


