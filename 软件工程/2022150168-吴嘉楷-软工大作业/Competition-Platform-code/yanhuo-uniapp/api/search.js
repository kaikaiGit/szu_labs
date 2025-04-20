import {
	request
} from '../utils/request.js'
import {
	appConfig
} from '../config/config.js'


export function esSearch(page, limit, data) {
	return request.post(`/search/imgDetailSearch/esSearch/${page}/${limit}`, data)
}


export function addSearchRecordData(parmas) {
	return request.get(`/search/searchRecord/addSearchRecordData`, parmas)
}


export function esSearchRecord(parmas) {
	return request.get(`/search/searchRecord/esSearchRecord`, parmas)
}