import ConvertUtil from '@/uni_modules/evan-emoji/utils/convert.js';
const install = (app) => {
	uni.$evanEmoji = {
		util: {
			convert: ConvertUtil
		}
	};
	app.config.globalProperties.$evanEmoji = {
		util: {
			convert: ConvertUtil
		}
	};
}

export default {
	install
}

