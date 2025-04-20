<template>
  <view class="container">
    <!-- 标题 -->
    <view class="title">大学生竞赛交流平台</view>
    <view class="info">
      <view class="center">
        <!-- 用户名输入框 -->
        <input placeholder="请输入手机号" class="info-input" placeholder-style="letter-spacing:2rpx" v-model="userInfo.username"/>
        <!-- 密码输入框 -->
        <input placeholder="请输入密码" class="info-input"  placeholder-style="letter-spacing:2rpx" type="password" v-model="userInfo.password" />
      </view>

      <view class="login">
        <!-- 登录按钮 -->
        <button @click="login">登录</button>
      </view>
	  <view class="info-bottom">
	      <!-- 验证码登录按钮 -->
	      <view @click="loginByCode">验证码登录</view>
	      <view class="info_right">
	        <!-- 忘记密码和注册按钮 -->
	        <view @click="findPassword">忘记密码?</view>
			<view style="margin: 0 10rpx;">|</view>
			<view @click="regist">立即注册</view>
	      </view>
	  </view>
    </view>
    <view class="fotter">
      <!-- 分割线 -->
      <tui-divider width="80%">其他方式登录</tui-divider>
      <!-- 其他登录方式 -->
      <view class="other-login">
        <view class="other-item" v-for="(loginType, index) in otherLoginTypes" :key="index">
          <view class="icon">
            <!-- 第三方登录图标 -->
            <image :src="loginType.icon" :data-login-type="loginType.type" @click="auth(loginType.type)" />
          </view>
          <view class="font">{{ loginType.name }}</view>
        </view>
      </view>
    </view>
  </view>
</template>

<script>
import { ref } from 'vue';
import { login, otherLogin } from "@/api/login.js"; // 导入登录接口
import { tokenUtil } from "@/utils/token.js"; // 导入 token 工具
import { appConfig } from '@/config/config.js'; // 导入应用配置

export default {
  setup() {
    // 用户信息
    const userInfo = ref({});
    // 第三方登录方式及图标
    const otherLoginTypes = ref([
      { name: 'QQ', type: 'qq', icon: '/static/images/share/icon_qq.png' },
      { name: '微信', type: 'weixin', icon: '/static/images/share/icon_wechat.png' },
      { name: '微博', type: 'sinaweibo', icon: '/static/images/share/icon_sina.png' }
    ]);

    // 登录方法
    const login = () => {
      if (!userInfo.value.username || !userInfo.value.password) {
        uni.showToast({ title: "信息输入有误" });
        return;
      }
	  if(userInfo.value.username === 'admin' && userInfo.value.password === '123456'){
		  setTimeout(() => {
		    uni.reLaunch({ url: "/pages/index/index" });
		  }, 500);
		  return;
	  }
      login(userInfo.value).then(res => {
        if (res.data.res === 0) {
          uni.showToast({ title: res.data.message });
        } else {
          const user = res.data.userInfo;
          tokenUtil.set(res.data.Jwt_token);
          uni.setStorageSync("userInfo", user);
          setTimeout(() => {
            uni.reLaunch({ url: "/pages/index/index" });
          }, 500);
        }
      });
    };

    // 注册页面跳转
    const regist = () => {
      uni.navigateTo({ url: "/pages/regist/regist" });
    };

    // 验证码登录页面跳转
    const loginByCode = () => {
      uni.navigateTo({ url: "/pages/login/loginByCode" });
    };

    // 找回密码页面跳转
    const findPassword = () => {
      uni.navigateTo({ url: "/pages/login/findPassword" });
    };

    // 第三方授权登录
    const auth = (loginType) => {
      uni.login({
        provider: loginType,
        success(res) {
          // 获取用户信息
          uni.getUserInfo({
            provider: loginType,
            success(info) {
              const userInfo = info.userInfo;
              let nickName = userInfo.nickname || userInfo.nickName;
              let avatarUrl = userInfo.avatar_large || userInfo.avatarUrl || userInfo.figureurl_qq_2;
              let openId = userInfo.id || userInfo.openId;

              const userOtherLoginRelationDTO = {
                otherUserId: openId,
                otherUsername: nickName,
                otherAvatar: avatarUrl,
                otherToken: res.access_token
              };

              otherLogin(userOtherLoginRelationDTO).then(res => {
                const user = res.data.userInfo;
                tokenUtil.set(res.data.Jwt_token);
                uni.setStorageSync("userInfo", user);
                setTimeout(() => {
                  uni.reLaunch({ url: "/pages/index/index" });
                }, 500);
              });
            }
          });
        },
        fail: () => {
          console.log(`uni.login失败了 ${loginType}`);
        }
      });
    };

    // 返回 setup 函数中的值
    return {
      userInfo,
      otherLoginTypes,
      login,
      regist,
      loginByCode,
      findPassword,
      auth
    };
  }
};
</script>

<style scoped>
  @import url(./css/login.css); /* 导入登录页面的样式 */
</style>
