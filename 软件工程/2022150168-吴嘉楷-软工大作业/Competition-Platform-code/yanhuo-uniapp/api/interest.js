import {
	request
} from '../utils/request.js'
import {
	appConfig
} from '../config/config.js'


export function getAllFollowTrends(page, limit, params) {
	return request.get(`/platform/follow/getAllFollowTrends/${page}/${limit}`, params)
}