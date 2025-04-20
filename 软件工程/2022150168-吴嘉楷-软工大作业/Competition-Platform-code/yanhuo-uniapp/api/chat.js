import {
	request
} from '../utils/request.js'
import {
	appConfig
} from '../config/config.js'


export function getZimToken(params) {
	return request.get('/platform/chat/getZimToken', params)
}


export function getChatUserList(params) {
	return request.get('/platform/chat/getChatUserList', params)
}

export function addChatRecord(data) {
	return request.post('/platform/chat/addChatRecord', data)
}


export function getChatRecord(page, limit, params) {
	return request.get(`/platform/chat/getChatRecord/${page}/${limit}`, params)
}

export function updateRecordCount(params) {
	return request.get(`/platform/chat/updateRecordCount`, params)
}

export function deleteRecord(params) {
	return request.get(`/platform/chat/deleteRecord`, params)
}