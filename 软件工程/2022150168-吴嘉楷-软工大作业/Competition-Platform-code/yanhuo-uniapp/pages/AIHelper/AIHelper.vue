<template>
	<view class="container" :style="{paddingTop: headerHeight+'px', paddingBottom: '158rpx'}">
		<!-- 头部栏 -->
		<view class="header">
			<tui-navigation-bar :style="{color: 'var(--my-font-color)'}" :isFixed="true" :isOpacity="true" @init="initHeader">
				<view class="flex-row" style="height: 100%;padding-inline: 20rpx;">
					<tui-icon name="arrowleft" size="25" color="var(--my-font-color)"></tui-icon>
					<view class="username">小智竞赛助手</view>
					<!-- 暂时不显示历史对话的图标 -->
					<tui-icon name="community" size="25" color="transparent"></tui-icon>
				</view>
			</tui-navigation-bar>
		</view>
		<!-- 中间对话聊天区域 -->
		<view class="content"  style="height: 100%">
			<!-- 热门竞赛榜单 -->
			<view class="contest_rankings" v-if="chatList.length === 1">
				<view class="title flex-row" style="font-size: 38rpx;">
					<span><b>热门竞赛</b></span>
					<span>{{currentDate}}</span>
				</view>
				
				<!-- 竞赛列表 -->
				<ul>
					<li v-for="(item,index) in contests" :key="index" @click="searchContest(item.name)">
						{{index+1}} &nbsp;{{item.name}}
					</li>
				</ul>
				
				<!-- 添加小智微信 -->
				<view class="flex-row" style="padding-top: 26rpx;">
					<image src="../../static/images/AIHelper/AI_logo.png" style="width: 100rpx;height: 104rpx;"></image>
					
					<view class="text" style="margin-right: 70rpx;font-size: 32rpx;line-height: 55rpx;">
						<view><b>添加小智微信</b></view>
						<view style="color: #777777;">订阅精选热点咨训</view>
					</view>
					
					<button class="add-btn" @click="switchModal">添加</button>
				</view>
				
				<!-- 弹出框 -->
				<tui-modal :show="modal" custom fadeIn maskClosable :cancel="switchModal">
					<view class="tui-modal-custom flex-column" style="gap:40rpx;font-size: 32rpx;font-weight: 600;">
						<view class="tui-modal-custom-text">扫描下方二维码码添加小智微信</view>
						
						<image src="../../static/images/AIHelper/WechatCode.jpg" class="tui-tips-img" style="height: 470rpx;width: 400rpx;"></image>
						<tui-button height="72rpx" :size="28" type="primary" shape="circle" @click="switchModal">确定</tui-button>
					</view>
				</tui-modal>
			</view>
			
			<scroll-view class="scroll-view" :scroll-y="true" :scroll-top="scrollTop" style="height: 97%;" v-else>
				<view class="scroll-view-content">
					<view class="oneChat" v-for="(item,index) in chatList" :key="index" :style="{'justify-content':item.role === 'user'?'flex-end':'start'}">
						<view class="user" v-if="item.role === 'user'">
							{{item.content}}
						</view>
						<view class="assistant-box" v-else>
							<view class="flex-row" style="justify-content: start;">
								<image src="../../static/images/AIHelper/xiaozhi-avator.png" mode="scaleToFill" style="width: 60rpx;height: 60rpx;"></image>
								&nbsp;
								<span>{{ item.role=== 'assistentThinking' ? '小智思考中...' : '小智' }}</span>
							</view>
							<view :class="item.role=== 'assistentThinking' ? 'loader' : 'assistent'">
								{{item.content}}
							</view>
						</view>
					</view>
				</view>
			</scroll-view>
		</view>
		<!-- 底部栏 -->
		<view class="bottom flex-row">
			<image src="../../static/images/AIHelper/voice-icon.png" mode="" style="width: 64rpx;height: 64rpx;" @click="parseVoice"></image>
			<input class="uni-input" v-model="message" confirm-type="send" placeholder="有什么问题尽管问我" style="flex:1;margin-inline: 20rpx;"/>
			<tui-icon name="send" size="64" unit="rpx" :color="message===''?'#aaa':'#1164F2cc'" @click="sendQuestion"></tui-icon>
		</view>
	</view>
</template>

<script setup>
import { ref, nextTick } from 'vue';
import { requestChatAPI } from '../../api/AIChat';

// 获取头部栏的高度
const headerHeight = ref(0);
const initHeader = (e) => {
	headerHeight.value = e.height; 
}

// 定义一个响应式变量来存储日期
const currentDate = ref('');
// 获取当前日期
const getDate = () => {
  const today = new Date();
  const month = String(today.getMonth() + 1).padStart(2, '0'); // 月份补零
  const date = String(today.getDate()).padStart(2, '0'); // 日期补零
  currentDate.value = `${month}.${date}`;
};
// 调用函数初始化日期
getDate();

// 热门竞赛列表
const contests = ref([
	{
		name: "互联网＋大学生创新创业大赛"
	},
	{
		name: "中国大学生计算机设计大赛"
	},
	{
		name: "第十六届蓝桥杯软件赛"
	},
	{
		name: "大学生服务外包创新创业大赛"
	},
])

//用户点击热门竞赛列表
const searchContest = (contest) => {
	message.value = contest;
	sendQuestion();
}

//语音输入相关
const parseVoice = () => {
	uni.showToast({
		title: '此功能暂未完善',
		icon: 'error'
	});
}

//输入框内容
const message = ref("");
//对话列表
const chatList = ref([{role: "assistent", content: "Hello，我是小智，很高兴遇见您！您可以向我询问关于竞赛的任何事情，小智一定会绞尽脑汁地帮助你的！"}]);
//用户发送问题内容，调用AI接口
const sendQuestion = () => {
	chatList.value.push({role: "user", content: message.value});
	chatList.value.push({role: "assistentThinking", content: ""});
	scrollToButtom();
		
	// 使用 Promise 调用接口
	requestChatAPI(message.value)
	    .then(result => {
			chatList.value.pop();
	        chatList.value.push({role: "assistent", content: result.choices[0].message.content});
			scrollToButtom();
	    })
	    .catch(error => {
	        console.error("Error:", error); // 处理错误
	    });
	message.value = "";
}

const scrollTop = ref(0);
//滚动到底部
const scrollToButtom = () => {
	// 使用 nextTick 等待视图更新
	nextTick(() => {
		// 设置 scroll-top 为最大高度，滚动到底部
		const scrollView = uni.createSelectorQuery().select('.scroll-view-content');
		scrollView.boundingClientRect(rect => {
		  scrollTop.value = rect.height; // 设置 scroll-top 为内容的最大高度
		}).exec();
	});
}

//用户点击添加小智微信的交互
const modal = ref(false);
const switchModal = () => {
	modal.value = !modal.value;
}

</script>

<style scoped lang="scss">
@import url("../../uni.scss");

ul, li {
  margin: 0; /* 清除默认外边距 */
  padding: 0; /* 清除默认内边距 */
  list-style: none; /* 去掉列表项前面的默认小圆点 */
}

.container {
	background-color: #EDEDED;
	height: 100vh;
	box-sizing: border-box;
	color: var(--my-font-color);
	font-size: var(--my-font-size);
}     

.content {
	padding-block: 30rpx;
	
	.contest_rankings {
		background-color: #fff;
		border-radius: 30rpx;
		padding: 26rpx;
		margin-inline: 24rpx;
		box-shadow: 0 2rpx 12rpx 0 #0000001a;
		ul {
			margin-top: 10rpx;
			font-size: 35rpx;
			li {
				line-height: 100rpx;
				border-bottom: 2rpx solid #BBBBBB;
			}
		}
		
		.add-btn {
			background-color: var(--my-blue-color);
			color: #fff;
			font-weight: 600;
			height: 82rpx;
			width: 140rpx;
			line-height: 82rpx;
			border-radius: 16rpx;
			margin: 0;
		}
	}
	
	.oneChat {
		display: flex;
		margin: 30rpx;
		font-size: 30rpx;
		letter-spacing: 0.1em;
		line-height: 1.5em;
		
		.user {
			background-color: var(--my-blue-color);
			color: #fff;
			border-radius: 30rpx 30rpx 0 30rpx;
			padding: 25rpx;
		}
		
		.assistent {
			margin-top: 10rpx;
			background-color: #fff;
			border-radius:  0 30rpx 30rpx 30rpx;
			padding: 25rpx;
		}
	}
}

.bottom {
	position: fixed;
	bottom: 24rpx;
	left: 24rpx;
	right: 24rpx;
	height: 110rpx;
	padding-inline: 30rpx;
	border-radius: 64rpx;
	background-color: #fff;
}

/* HTML: <div class="loader"></div> */
.loader {
  width: 330rpx;
  height: 40rpx;
  margin-top: 10rpx;
  border-radius: 40rpx;
  color: #514b82;
  border: 4rpx solid;
  position: relative;
}
.loader::before {
  content: "";
  position: absolute;
  margin: 2px;
  inset: 0 100% 0 0;
  border-radius: inherit;
  background: currentColor;
  animation: l6 2s infinite;
}
@keyframes l6 {
    100% {inset:0}
}
</style>
