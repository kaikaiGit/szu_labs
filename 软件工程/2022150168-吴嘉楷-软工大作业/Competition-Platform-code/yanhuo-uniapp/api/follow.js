import {
	request
} from '../utils/request.js'
import {
	appConfig
} from '../config/config.js'


export function followUser(data) {
	return request.post(`/platform/follow/followUser`, data)
}

export function clearFollow(data) {
	return request.post(`/platform/follow/clearFollow`, data)
}

export function isFollow(params) {
	return request.get(`/platform/follow/isFollow`, params)
}


export function getAllFriend(page, limit, params) {
	return request.get(`/platform/follow/getAllFriend/${page}/${limit}`, params)
}