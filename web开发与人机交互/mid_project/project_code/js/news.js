const news_list = document.querySelectorAll(".new_box .new");
news_href = ["https://www.toutiao.com/article/7292974004938342921/",
            "https://www.toutiao.com/article/7307564762882654758/",
            "https://www.toutiao.com/article/7294256695495557667/",
            "https://www.toutiao.com/article/7287782533629018678/"
            ];
for(let i=0; i < news_list.length; i++){
    news_list[i].addEventListener("click",
    function(){
        window.open(news_href[i]);
        console.log(i);
    })
}
        