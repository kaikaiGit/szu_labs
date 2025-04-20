import {
	request
} from '../utils/request.js'
import {
	appConfig
} from '../config/config.js'


export function getMe(params) {
	return request.get('/manage/user/getOne', params)
}


export function getTrendByUser(page, limit, params) {
	return request.get(`/platform/user/getTrendByUser/${page}/${limit}`, params)
}

export function getUserInfo(params) {
	return request.get(`/platform/user/getUserInfo`, params)
}


export function updateUser(data) {
	return request.post('/platform/user/updateUser', data)
}

export function searchUser(page, limit, params) {
	return request.get(`/platform/user/searchUser/${page}/${limit}`, params)
}

export function searchUserByUsername(params) {
	return request.get('/platform/user/searchUserByUsername', params)
}

export function getUserRecord(params) {
	return request.get(`/platform/user/getUserRecord`, params)
}

export function clearUserRecord(params) {
	return request.get(`/platform/user/clearUserRecord`, params)
}