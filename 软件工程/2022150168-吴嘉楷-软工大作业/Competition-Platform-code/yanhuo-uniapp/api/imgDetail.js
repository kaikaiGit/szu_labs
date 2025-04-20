import {
	request
} from '../utils/request.js'
import {
	appConfig
} from '../config/config.js'


export function publish(data) {
	return request.post('/platform/imgDetail/publish', data)
}

export function updateStatus(data) {
	return request.post('/platform/imgDetail/updateStatus', data)
}


export function getAllImgByAlbum(page, limit, params) {
	return request.get(`/platform/imgDetail/getAllImgByAlbum/${page}/${limit}`, params)
}


export function getOne(params) {
	return request.get(`/platform/imgDetail/getOne`, params)
}


export function getPage(page, limit, params) {
	return request.get(`/platform/imgDetail/getPage/${page}/${limit}`, params)
}

export function getRecommend(page, limit, params) {
	return request.get(`/recommend/newRecommend/RecommendToUserByCF/${page}/${limit}`, params)
}

export function deleteImgs(data, uid) {
	return request.post( `/platform/imgDetail/deleteImgs/${uid}`, data)
}

export function getHot(page, limit) {
	return request.get(`/platform/imgDetail/getHot/${page}/${limit}`, null)
}

export function updateImgDetail(data) {
	return request.post('/platform/imgDetail/updateImgDetail', data)
}

export function addMQTask(data) {
	return request.post('/platform/imgDetail/addMQTask', data)
}