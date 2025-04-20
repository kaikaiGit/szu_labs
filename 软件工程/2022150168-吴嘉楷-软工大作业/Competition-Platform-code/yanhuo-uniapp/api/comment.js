import {
	request
} from '../utils/request.js'
import {
	appConfig
} from '../config/config.js'

export function addComment(data) {
	return request.post('/platform/comment/addComment', data)
}

export function getAllTwoCommentByOneId(page, limit, params) {
	return request.get(`/platform/comment/getAllTwoCommentByOneId/${page}/${limit}`, params)
}


export function getAllOneCommentByImgId(page, limit, params) {
	return request.get(`/platform/comment/getAllOneCommentByImgId/${page}/${limit}`, params)
}

export function getAllTwoComment(params) {
	return request.get(`/platform/comment/getAllTwoComment`, params)
}


export function getAllReplyComment(page, limit, params) {
	return request.get(`/platform/comment/getAllReplyComment/${page}/${limit}`, params)
}


export function getComment(params) {
	return request.get(`/platform/comment/getComment`, params)
}

export function scrollComment(params) {
	return request.get(`/platform/comment/scrollComment`, params)
}


export function getAllTrendCommentByImage(page, limit, params) {
	return request.get(`/platform/comment/getAllTrendCommentByImage/${page}/${limit}`, params)
}

export function getAllComment(page, limit, params) {
	return request.get(`/platform/comment/getAllComment/${page}/${limit}`, params)
}

export function delComment(params) {
	return request.get(`/platform/comment/delComment`, params)
}