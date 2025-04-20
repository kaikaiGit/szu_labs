import {
	request
} from '../utils/request.js'
import {
	appConfig
} from '../config/config.js'


export function saveTag(tagInfo) {
	return request.post('/platform/tag/saveTag', tagInfo)
}


export function getAllTag(params) {
	return request.get('/platform/tag/getAllTag', params)
}


export function getImgListByTagId(page, limit, params) {
	return request.get(`/platform/tag/getImgListByTagId/${page}/${limit}`, params)
}


export function getOneTag(params) {
	return request.get('/platform/tag/getOneTag', params)
}