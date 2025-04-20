import {
	request
} from '../utils/request.js'
import {
	appConfig
} from '../config/config.js'


export function getAllSearchRecord(params) {
	return request.get('/platform/searchRecord/getAllSearchRecord', params)
}

export function addSearchRecord(data) {
	return request.post('/platform/searchRecord/addSearchRecord', data)
}

export function deleteSearchRecord(uid, data) {
	return request.post('/platform/searchRecord/deleteSearchRecord?uid=' + uid, data)
}