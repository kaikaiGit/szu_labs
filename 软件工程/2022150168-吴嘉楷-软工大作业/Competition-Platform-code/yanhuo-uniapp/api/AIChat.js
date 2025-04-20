const url = "https://spark-api-open.xf-yun.com/v1/chat/completions";
const data = {
    model: "generalv3.5", // 指定请求的模型
    messages: [
        {
            role: "system",
            content: "你是一位知识渊博的竞赛助手。你擅长搜索各类竞赛的信息，包括竞赛网站、竞赛简介、涉及的知识点，然后用一段话的形式进行回答。你每次回答的最后一句话都是竞赛的网址url，且从不分点罗列。"
        },
        {
            role: "user",
            content: "你是谁"
        }
    ],
    top_k: 6, // 高随机性
    stream: false, // 是否为流式
};
const headers = {
    "Authorization": "Bearer EkbffLpOqxJDlYJgJNuc:SvPAVlfLVpihmXGVgwts", // Bearer+自己的APIPassword
    "Content-Type": "application/json"
};

// 将 uni.request 封装为返回 Promise 的函数
export function requestChatAPI(question) {
	data.messages[1].content = question;	//设置用户的问题
	
    return new Promise((resolve, reject) => {
        uni.request({
            url: url,
            method: "POST",
            header: headers,
            data: data,
            success: (res) => {
                if (res.statusCode === 200) {
                    resolve(res.data); // 请求成功时解析数据
                } else {
                    reject(`HTTP error! status: ${res.statusCode}`); // 请求失败时抛出错误
                }
            },
            fail: (error) => {
                reject(error); // 请求失败时抛出错误
            }
        });
    });
}