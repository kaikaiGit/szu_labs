<template>
	<tui-navigation-bar backgroundColor="#fff" :isFixed="false" :isOpacity="false">
		<view class="nav">
			<tui-icon name="arrowleft" size="30" @click="back"></tui-icon>
		</view>
	</tui-navigation-bar>
	<view class="container">
		<h1 style="text-align: center;">修改密码</h1>
		<view class="main" v-if="!check">
			<view class="center">
				<input placeholder="请输入手机号" class="info-input" v-model="value" />
				<view class="code">
					<input placeholder="验证码" class="info-input" v-model="code" />
					<tui-button type="white" width="200rpx" :link="true" height="60rpx" @click="getCode()"
						v-if="T">发送验证码</tui-button>
					<tui-tag type="white" v-else>{{ count }}</tui-tag>
				</view>
			</view>

			<view class="regist">
				<tui-button @click="next()" type="primary" shape="circle">下一步</tui-button>
			</view>
		</view>

		<view class="main" v-else>
			<input placeholder="输入密码" class="info-input" type="password" v-model="password" />
			<input placeholder="重新输入密码" class="info-input" type="password" v-model="checkPassword" />

			<view class="regist">
				<tui-button @click="updatePassword" type="primary" shape="circle">修改密码</tui-button>
			</view>
		</view>
	</view>
</template>

<script>
	import {
		sendDm,
		sendMsm,
		register,
		check,
		updatePassword
	} from "@/api/regist.js"
	import {
		isMobile,
		isEmail,
		validatorPassword
	} from '@/utils/validate.js'
	export default {
		data() {
			return {
				T: true,
				check: false,
				count: 0,
				userInfo: {},
				value: '',
				code: '',
				password: '',
				checkPassword: '',
			}
		},

		methods: {
			back() {
				uni.navigateBack({
					delta: 1
				})
			},

			getCode() {

				let isM = isMobile(this.value)
				let isE = isEmail(this.value)


				if (isM) {
					sendMsm(this.value).then(res => {
						uni.showToast({
							title: "发送成功"
						})
					})
				} else if (isE) {
					sendDm(this.value).then(res => {
						uni.showToast({
							title: "发送成功"
						})
					})
				} else {
					uni.showToast({
						title: "请输入正确手机号或邮箱"
					})
					return
				}

				this.T = false
				this.count = 60
				var times = setInterval(() => {
					this.count--; //递减
					if (this.count <= 1) {
						this.T = true
						clearInterval(times);
					}
				}, 1000)

			},

			next() {

				let isM = isMobile(this.value)
				let isE = isEmail(this.value)
				this.userInfo.code = this.code
				if (isM) {
					this.userInfo.phone = this.value
				} else if (isE) {
					this.userInfo.email = this.value
				}
				this.userInfo.type = 1

				check(this.userInfo).then(res => {
					if (res.data.res === 1) {
						this.check = true
					} else {
						uni.showToast({
							title: res.data.message
						})
					}
				})
			},

			updatePassword() {

				let pwd = validatorPassword(this.password)

				if (!pwd) {
					uni.showToast({
						title: "请输入8-20位由字母和数字组成的密码"
					})
					return
				}

				if (this.password !== this.checkPassword) {
					uni.showToast({
						title: "两次输入的密码不一致"
					})
					return
				}

				this.userInfo.password = this.password
				this.userInfo.checkPassword = this.checkPassword
				updatePassword(this.userInfo).then(res => {
					if (res.data) {
						uni.showToast({
							title: "修改成功"
						})
						setTimeout(() => {
							uni.reLaunch({
								url: "/pages/login/login"
							});
						}, 1000)
					}
				})
			}

		}
	}
</script>

<style scoped>
	@import url(./css/findPassword.css);
</style>