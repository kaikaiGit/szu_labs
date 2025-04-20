const start = document.querySelector(".start");
const end = document.querySelector(".end");
const sum_text = document.querySelector(".sum");
const btn1 = document.querySelector(".btn1");
const btn2 = document.querySelector(".btn2");
btn1.addEventListener("click", function () {
let v1 = +start.value;
let v2 = +end.value;
function sum(n1,n2){
    let sum_v = 0;
    for (let i = n1; i <= n2; i++) {
    sum_v += i;
    }
    return sum_v;
}
function show(s){
    sum_text.value = s;
    alert("计算成功！结果将在确认后显示。\n计算结果将在6s后自动清空！");
}
if (v1 == 0 || v2 == 0) alert("数据不能为空 (自然数不支持0)！\n请您输入数据");
else if (v1 < 1) alert("起始值不能小于1！");
else if (v1 >= v2) alert("起始数必须小于终止数，请重新输入！");
else {
    let s = sum(v1,v2);
    show(s);
    setTimeout(function(){
        start.value = end.value = sum_text.value = null;
    },6000)
}
});
btn2.addEventListener("click", function () {
start.value = end.value = sum_text.value = null;
});