import {
	request
} from '../utils/request.js'
import {
	appConfig
} from '../config/config.js'


export function getCategory() {
	return request.get('/platform/category/getTreeCategory', null)
}


export function getImgListByCategory(page, limit, params) {
	return request.get(`/platform/category/getImgListByCategory/${page}/${limit}`, params)
}