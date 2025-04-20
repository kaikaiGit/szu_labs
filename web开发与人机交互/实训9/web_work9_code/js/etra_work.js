const box = document.querySelector(".content")
const text = document.querySelector(".banner p")

let list=[];
let sum =0;
function cal(n){
    let flag = true;
    for(let j=2;j<=n;j++){
        flag = true;
        for(let i=2;i<j;i++){
            if(j%i===0){
                flag = false;
                break;
            }
        }
        if(flag){
            list.push(j);
            sum++;
        }
    }
}
cal(100);

box.innerHTML =  list.join(" ")
text.innerHTML = `素数一共有：${sum}个`
