import {
	request
} from '../utils/request.js'
import {
	appConfig
} from '../config/config.js'


export function sendDm(data) {
	return request.post(`/util/dm/sendDm`, data)
}

export function sendMsm(data) {
	return request.post(`/util/msm/sendMsm`, data)
}

export function register(data) {
	return request.post(`/auth/register`, data)
}

export function check(data) {
	return request.post(`/auth/check`, data)
}

export function updatePassword(data) {
	return request.post(`/auth/updatePassword`, data)
}

export function isRegist(data) {
	return request.post(`/auth/isRegist`, data)
}