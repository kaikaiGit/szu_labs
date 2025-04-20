const usn = document.querySelector(".username")
const psw = document.querySelector(".password")
const bt = document.querySelector(".btn-primary")

bt.addEventListener("click",
function(){
    let flag = false;
    for(let i=0;i<psw.value.length;i++){
        if(psw.value[i]>='a'&&psw.value[i]<='z'||psw.value[i]>='A'&&psw.value[i]<='Z'){
            flag=true;
            break;
        }
    }
    if(usn.value=='')alert("用户名不能为空！")
    else if(psw.value.length<8)alert("密码长度必须大于等于8，请重输！")
    else if(!flag)alert("密码中必须包含至少一个字母，请重输！")
    else{
        alert("验证通过！")
        usn.value = psw.value ="";
    }
})
