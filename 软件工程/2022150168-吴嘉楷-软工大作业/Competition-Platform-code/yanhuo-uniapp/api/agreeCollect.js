import {
	request
} from '../utils/request.js'
import {
	appConfig
} from '../config/config.js'


export function agree(data) {
	return request.post('/platform/agreeCollect/agree', data)
}

export function cancelAgree(data) {
	return request.post('/platform/agreeCollect/cancelAgree', data)
}


export function isAgree(data) {
	return request.post('/platform/agreeCollect/isAgree', data)
}


export function getAllAgreeAndCollection(page, limit, params) {
	return request.get(`/platform/agreeCollect/getAllAgreeAndCollection/${page}/${limit}`, params)
}

export function getAllCollection(page, limit, params) {
	return request.get(`/platform/agreeCollect/getAllCollection/${page}/${limit}`, params)
}


export function collection(data) {
	return request.post('/platform/agreeCollect/collection', data)
}

export function cancelCollection(data) {
	return request.post('/platform/agreeCollect/cancelCollection', data)
}