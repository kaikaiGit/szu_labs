import App from './App'
import GoEasy from '@/node_modules/GOEASY-IM/js_sdk/goeasy-2.8.3.esm.min.js'
import EvanEmoji from '@/uni_modules/evan-emoji/utils/index.js'
import { appConfig } from '@/config/config.js'
import { createSSRApp } from 'vue'

// Vue 3 setup
export function createApp() {
  const app = createSSRApp(App)

  app.use(EvanEmoji);

  const goEasy = GoEasy.getInstance({
      host: 'hangzhou.goeasy.io',
      appkey: appConfig.ImKey,
      modules: ['im'],
      allowNotification: true
  });

  goEasy.im.on(GoEasy.IM_EVENT.CONVERSATIONS_UPDATED, setUnreadNumber);

  function setUnreadNumber(content) {
      let unreadTotal = content.unreadTotal;
      uni.setStorageSync("unreadTotal", unreadTotal);
      // Other tab bar badge logic here
  }

  goEasy.onClickNotification((message) => {
      let currentUrl;
      const routes = getCurrentPages();

      if (routes && routes.length) {
          const curRoute = routes[routes.length - 1].route;
          const curParam = routes[routes.length - 1].options;
          currentUrl = '/' + curRoute + `?to=${curParam.to}`;
      }

      let newUrl;
      switch (message.toType) {
          case GoEasy.IM_SCENE.PRIVATE:
              newUrl = '/pages/message/privateChat/privateChat?to=' + message.senderId;
              break;
          case GoEasy.IM_SCENE.GROUP:
              newUrl = '/pages/groupChat?to=' + message.groupId;
              break;
      }

      if (currentUrl !== newUrl) {
          uni.navigateTo({
              url: newUrl,
          });
      }
  });
  
  app.config.globalProperties.GoEasy = GoEasy
  app.config.globalProperties.goEasy = goEasy

  return { app }
}
