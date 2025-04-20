import {
  __commonJS
} from "./chunk-Y2F7D3TJ.js";

// C:/Users/24312/Desktop/软件工程/大作业/Competition-Platform/yanhuo-uniapp/node_modules/plus-websocket/out/index.js
var require_out = __commonJS({
  "C:/Users/24312/Desktop/软件工程/大作业/Competition-Platform/yanhuo-uniapp/node_modules/plus-websocket/out/index.js"(exports) {
    !function(e, n) {
      for (var t in n)
        e[t] = n[t];
    }(exports, function(e) {
      var n = {};
      function t(o) {
        if (n[o])
          return n[o].exports;
        var r = n[o] = { i: o, l: false, exports: {} };
        return e[o].call(r.exports, r, r.exports, t), r.l = true, r.exports;
      }
      return t.m = e, t.c = n, t.d = function(e2, n2, o) {
        t.o(e2, n2) || Object.defineProperty(e2, n2, { enumerable: true, get: o });
      }, t.r = function(e2) {
        "undefined" != typeof Symbol && Symbol.toStringTag && Object.defineProperty(e2, Symbol.toStringTag, { value: "Module" }), Object.defineProperty(e2, "__esModule", { value: true });
      }, t.t = function(e2, n2) {
        if (1 & n2 && (e2 = t(e2)), 8 & n2)
          return e2;
        if (4 & n2 && "object" == typeof e2 && e2 && e2.__esModule)
          return e2;
        var o = /* @__PURE__ */ Object.create(null);
        if (t.r(o), Object.defineProperty(o, "default", { enumerable: true, value: e2 }), 2 & n2 && "string" != typeof e2)
          for (var r in e2)
            t.d(o, r, (function(n3) {
              return e2[n3];
            }).bind(null, r));
        return o;
      }, t.n = function(e2) {
        var n2 = e2 && e2.__esModule ? function() {
          return e2.default;
        } : function() {
          return e2;
        };
        return t.d(n2, "a", n2), n2;
      }, t.o = function(e2, n2) {
        return Object.prototype.hasOwnProperty.call(e2, n2);
      }, t.p = "", t(t.s = 1);
    }([function(e, n, t) {
      "use strict";
      function o(e2) {
        return (o = "function" == typeof Symbol && "symbol" == typeof Symbol.iterator ? function(e3) {
          return typeof e3;
        } : function(e3) {
          return e3 && "function" == typeof Symbol && e3.constructor === Symbol && e3 !== Symbol.prototype ? "symbol" : typeof e3;
        })(e2);
      }
      function r(e2, n2, t2) {
        n2 ? n2.errMsg || (n2.errMsg = "callback:ok") : "object" === o(t2) ? (t2 || (t2 = { errMsg: "callback:fail" }), t2.errMsg || (t2.errMsg = t2.message || "callback:fail")) : t2 = { errMsg: "callback:fail " + String(t2) }, e2 && "function" == typeof e2.success && n2 && e2.success(n2), t2 && console.warn("Callback Fail:", t2), e2 && "function" == typeof e2.fail && t2 && e2.fail(t2), e2 && "function" == typeof e2.complete && e2.complete(n2 || t2);
      }
      Object.defineProperty(n, "__esModule", { value: true }), n.getCallback = n.callback = n.plusReady = n.isApp = n.isWeex = n.isWeb = n.isPlus = void 0, n.isPlus = "object" === ("undefined" == typeof navigator ? "undefined" : o(navigator)) && !!navigator.userAgent.match(/Html5Plus/i), n.isWeb = "object" === ("undefined" == typeof document ? "undefined" : o(document)) && !n.isPlus, n.isWeex = "object" === ("undefined" == typeof weex ? "undefined" : o(weex)), n.isApp = n.isPlus || n.isWeex, n.plusReady = function(e2) {
        "object" === ("undefined" == typeof plus ? "undefined" : o(plus)) ? e2() : n.isApp && window.addEventListener("plusready", e2, false);
      }, n.callback = r, n.getCallback = function() {
        return r;
      };
    }, function(e, n, t) {
      "use strict";
      Object.defineProperty(n, "__esModule", { value: true });
      var o = t(2);
      Object.defineProperty(n, "connectSocket", { enumerable: true, get: function() {
        return o.connectSocket;
      } }), Object.defineProperty(n, "onSocketOpen", { enumerable: true, get: function() {
        return o.onSocketOpen;
      } }), Object.defineProperty(n, "onSocketError", { enumerable: true, get: function() {
        return o.onSocketError;
      } }), Object.defineProperty(n, "sendSocketMessage", { enumerable: true, get: function() {
        return o.sendSocketMessage;
      } }), Object.defineProperty(n, "onSocketMessage", { enumerable: true, get: function() {
        return o.onSocketMessage;
      } }), Object.defineProperty(n, "closeSocket", { enumerable: true, get: function() {
        return o.closeSocket;
      } }), Object.defineProperty(n, "onSocketClose", { enumerable: true, get: function() {
        return o.onSocketClose;
      } });
    }, function(e, n, t) {
      "use strict";
      Object.defineProperty(n, "__esModule", { value: true }), n.onSocketClose = n.closeSocket = n.onSocketMessage = n.sendSocketMessage = n.onSocketError = n.onSocketOpen = n.connectSocket = void 0;
      var o = t(3), r = null, a = {};
      function c(e2, n2) {
        r ? r[e2](n2) : a[e2] = n2;
      }
      n.connectSocket = function(e2) {
        e2 = e2 || {};
        var n2 = new o.SocketTask(e2);
        function t2() {
          r = null;
        }
        if (n2.onClose(t2), n2.onError(t2), !r)
          for (var c2 in r = n2, a)
            a.hasOwnProperty(c2) && n2[c2](a[c2]);
        return r = r || n2, n2;
      }, n.onSocketOpen = function(e2) {
        c("onOpen", e2);
      }, n.onSocketError = function(e2) {
        c("onError", e2);
      }, n.sendSocketMessage = function(e2) {
        r && r.send(e2);
      }, n.onSocketMessage = function(e2) {
        c("onMessage", e2);
      }, n.closeSocket = function(e2) {
        r && r.close(e2);
      }, n.onSocketClose = function(e2) {
        c("onClose", e2);
      };
    }, function(e, n, t) {
      "use strict";
      function o(e2) {
        return (o = "function" == typeof Symbol && "symbol" == typeof Symbol.iterator ? function(e3) {
          return typeof e3;
        } : function(e3) {
          return e3 && "function" == typeof Symbol && e3.constructor === Symbol && e3 !== Symbol.prototype ? "symbol" : typeof e3;
        })(e2);
      }
      function r(e2, n2) {
        for (var t2 = 0; t2 < n2.length; t2++) {
          var r2 = n2[t2];
          r2.enumerable = r2.enumerable || false, r2.configurable = true, "value" in r2 && (r2.writable = true), Object.defineProperty(e2, (a2 = r2.key, c2 = void 0, c2 = function(e3, n3) {
            if ("object" !== o(e3) || null === e3)
              return e3;
            var t3 = e3[Symbol.toPrimitive];
            if (void 0 !== t3) {
              var r3 = t3.call(e3, n3 || "default");
              if ("object" !== o(r3))
                return r3;
              throw new TypeError("@@toPrimitive must return a primitive value.");
            }
            return ("string" === n3 ? String : Number)(e3);
          }(a2, "string"), "symbol" === o(c2) ? c2 : String(c2)), r2);
        }
        var a2, c2;
      }
      var a = this && this.__createBinding || (Object.create ? function(e2, n2, t2, o2) {
        void 0 === o2 && (o2 = t2), Object.defineProperty(e2, o2, { enumerable: true, get: function() {
          return n2[t2];
        } });
      } : function(e2, n2, t2, o2) {
        void 0 === o2 && (o2 = t2), e2[o2] = n2[t2];
      }), c = this && this.__setModuleDefault || (Object.create ? function(e2, n2) {
        Object.defineProperty(e2, "default", { enumerable: true, value: n2 });
      } : function(e2, n2) {
        e2.default = n2;
      }), i = this && this.__importStar || function(e2) {
        if (e2 && e2.__esModule)
          return e2;
        var n2 = {};
        if (null != e2)
          for (var t2 in e2)
            "default" !== t2 && Object.hasOwnProperty.call(e2, t2) && a(n2, e2, t2);
        return c(n2, e2), n2;
      }, s = this && this.__importDefault || function(e2) {
        return e2 && e2.__esModule ? e2 : { default: e2 };
      };
      Object.defineProperty(n, "__esModule", { value: true }), n.SocketTask = void 0;
      var l, u, d = i(t(4)), f = t(0), b = s(t(5)), p = {}, y = t(6), v = false, k = [];
      var h = function() {
        function e2(n3) {
          !function(e3, n4) {
            if (!(e3 instanceof n4))
              throw new TypeError("Cannot call a class as a function");
          }(this, e2), this.id = Date.now().toString(), this.eval("connect", n3);
        }
        var n2, o2, a2;
        return n2 = e2, (o2 = [{ key: "send", value: function(e3) {
          e3.data && "string" != typeof e3.data && (e3.data = [b.default.encode(e3.data)]), this.eval("send", e3);
        } }, { key: "close", value: function(e3) {
          this.eval("close", e3);
        } }, { key: "onOpen", value: function(e3) {
          this.on("open", e3);
        } }, { key: "onClose", value: function(e3) {
          this.on("close", e3);
        } }, { key: "onError", value: function(e3) {
          this.on("error", e3);
        } }, { key: "onMessage", value: function(e3) {
          this.on("message", function(n3) {
            n3 = (n3 = n3.data) && "string" != typeof n3 ? b.default.decode(n3[0]) : n3, e3({ data: n3 });
          });
        } }, { key: "eval", value: function(e3, n3) {
          var o3 = "callback".concat(Date.now()), r2 = f.isWeb ? window : p;
          r2[o3] = function(e4) {
            delete r2[o3], e4 ? f.callback(n3, {}, e4) : f.callback(n3, {});
          };
          var a3 = "window.__webSocket&&__webSocket.".concat(e3, "(").concat(this.id, ",").concat(JSON.stringify(n3), ",'").concat(o3, "')");
          f.isWeb ? (l || (window.eval(y), l = true), window.eval(a3)) : f.plusReady(function() {
            !function(e4) {
              var n4 = plus.webview.getWebviewById("__websocket__");
              if (!n4) {
                var o4 = t(7);
                (n4 = plus.webview.create("http://www.dcloud.io", "__websocket__", { kernel: "WKWebview", render: "always", plusrequire: "none" })).overrideUrlLoading({ match: ".*data.*" }, function(e5) {
                  var t2 = e5.url, o5 = t2.match(/\?(\S+)=(\S+)/);
                  if (o5) {
                    var r3 = o5[1], a4 = JSON.parse(decodeURIComponent(o5[2]));
                    "event" === r3 ? d.emit(a4.type, a4.data) : "callback" === r3 && p[a4.callbackName](a4.error);
                  } else
                    !v && "number" != typeof u && t2.indexOf("load") >= 0 ? u = setInterval(function() {
                      n4.evalJS(y);
                    }, 16) : !v && t2.indexOf("ready") >= 0 && (clearInterval(u), v = true, k.forEach(function(e6) {
                      e6(n4);
                    }), k = []);
                }), n4.loadData(o4, { baseURL: "http://websocket.websocket" });
              }
              v ? e4(n4) : k.push(e4);
            }(function(e4) {
              e4.evalJS(a3);
            });
          });
        } }, { key: "on", value: function(e3, n3) {
          d.on("websocket".concat(e3).concat(this.id), function(e4) {
            n3(e4.detail);
          });
        } }]) && r(n2.prototype, o2), a2 && r(n2, a2), Object.defineProperty(n2, "prototype", { writable: false }), e2;
      }();
      n.SocketTask = h;
    }, function(e, n, t) {
      "use strict";
      Object.defineProperty(n, "__esModule", { value: true }), n.emit = n.off = n.on = void 0;
      var o = t(0), r = {};
      n.on = function(e2, n2) {
        o.isWeb ? window.addEventListener(e2, n2, false) : (r[e2] = r[e2] || [], r[e2].push(n2));
      }, n.off = function(e2, n2) {
        if (o.isWeb)
          window.removeEventListener(e2, n2, false);
        else {
          var t2 = r[e2];
          t2 && t2.splice(t2.indexOf(n2), 1);
        }
      }, n.emit = function(e2, n2) {
        if (o.isWeb)
          document.dispatchEvent(new CustomEvent(e2, { detail: n2, bubbles: true }));
        else {
          var t2 = r[e2];
          t2 && t2.forEach(function(e3) {
            e3({ detail: n2 });
          });
        }
      };
    }, function(e, n, t) {
      "use strict";
      Object.defineProperty(n, "__esModule", { value: true });
      var o = { chars: "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/", lookup: null, encode: function(e2) {
        var n2, t2 = this.chars, o2 = new Uint8Array(e2), r = o2.length, a = "";
        for (n2 = 0; n2 < r; n2 += 3)
          a += t2[o2[n2] >> 2], a += t2[(3 & o2[n2]) << 4 | o2[n2 + 1] >> 4], a += t2[(15 & o2[n2 + 1]) << 2 | o2[n2 + 2] >> 6], a += t2[63 & o2[n2 + 2]];
        return r % 3 == 2 ? a = a.substring(0, a.length - 1) + "=" : r % 3 == 1 && (a = a.substring(0, a.length - 2) + "=="), a;
      }, decode: function(e2) {
        var n2 = this.chars, t2 = this.lookup;
        if (!t2) {
          t2 = this.lookup = new Uint8Array(256);
          for (var o2 = 0; o2 < n2.length; o2++)
            t2[n2.charCodeAt(o2)] = o2;
        }
        var r, a, c, i, s = 0.75 * e2.length, l = e2.length, u = 0;
        "=" === e2[e2.length - 1] && (s--, "=" === e2[e2.length - 2] && s--);
        var d = new ArrayBuffer(s), f = new Uint8Array(d);
        for (o2 = 0; o2 < l; o2 += 4)
          r = t2[e2.charCodeAt(o2)], a = t2[e2.charCodeAt(o2 + 1)], c = t2[e2.charCodeAt(o2 + 2)], i = t2[e2.charCodeAt(o2 + 3)], f[u++] = r << 2 | a >> 4, f[u++] = (15 & a) << 4 | c >> 2, f[u++] = (3 & c) << 6 | 63 & i;
        return d;
      } };
      n.default = o;
    }, function(e, n) {
      e.exports = "(function () {\n    if (window.__webSocket) {\n        return\n    }\n    var isPlus = typeof navigator === 'object' && !!navigator.userAgent.match(/Html5Plus/i)\n    if (isPlus) {\n        location.href = 'http://data?ready'\n    }\n    // 自定义事件\n    var $event = {\n        emit (type, data) {\n            if (!isPlus) {\n                document.dispatchEvent(new CustomEvent(type, {\n                    detail: data,\n                    bubbles: true\n                }))\n                return\n            }\n            location.href = 'http://data?event=' + encodeURIComponent(JSON.stringify({\n                type,\n                data\n            }))\n        }\n    }\n    var Base64 = {\n        chars: \"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/\",\n        lookup: null,\n        encode: function (arraybuffer) {\n            var chars = this.chars;\n            var bytes = new Uint8Array(arraybuffer),\n                i, len = bytes.length, base64 = \"\";\n\n            for (i = 0; i < len; i += 3) {\n                base64 += chars[bytes[i] >> 2];\n                base64 += chars[((bytes[i] & 3) << 4) | (bytes[i + 1] >> 4)];\n                base64 += chars[((bytes[i + 1] & 15) << 2) | (bytes[i + 2] >> 6)];\n                base64 += chars[bytes[i + 2] & 63];\n            }\n\n            if ((len % 3) === 2) {\n                base64 = base64.substring(0, base64.length - 1) + \"=\";\n            } else if (len % 3 === 1) {\n                base64 = base64.substring(0, base64.length - 2) + \"==\";\n            }\n\n            return base64;\n        },\n        decode: function (base64) {\n            var chars = this.chars;\n            var lookup = this.lookup\n            if (!lookup) {\n                lookup = this.lookup = new Uint8Array(256);\n                for (var i = 0; i < chars.length; i++) {\n                    lookup[chars.charCodeAt(i)] = i;\n                }\n            }\n            var bufferLength = base64.length * 0.75,\n                len = base64.length, p = 0,\n                encoded1, encoded2, encoded3, encoded4;\n\n            if (base64[base64.length - 1] === \"=\") {\n                bufferLength--;\n                if (base64[base64.length - 2] === \"=\") {\n                    bufferLength--;\n                }\n            }\n\n            var arraybuffer = new ArrayBuffer(bufferLength),\n                bytes = new Uint8Array(arraybuffer);\n\n            for (i = 0; i < len; i += 4) {\n                encoded1 = lookup[base64.charCodeAt(i)];\n                encoded2 = lookup[base64.charCodeAt(i + 1)];\n                encoded3 = lookup[base64.charCodeAt(i + 2)];\n                encoded4 = lookup[base64.charCodeAt(i + 3)];\n\n                bytes[p++] = (encoded1 << 2) | (encoded2 >> 4);\n                bytes[p++] = ((encoded2 & 15) << 4) | (encoded3 >> 2);\n                bytes[p++] = ((encoded3 & 3) << 6) | (encoded4 & 63);\n            }\n\n            return arraybuffer;\n        }\n    }\n\n    window.__webSocket = {\n        webSockets: {},\n        connect (id, data, callbackName) {\n            var url = data.url\n            var header = data.header// 未支持\n            var method = data.method// 未支持\n            var protocols = data.protocols || []\n            var webSocket\n            try {\n                webSocket = this.webSockets[id] = new WebSocket(url, protocols)\n                webSocket.binaryType = 'arraybuffer'\n            } catch (error) {\n                this.callback(callbackName, error)\n                return\n            }\n            this.callback(callbackName)\n            if (webSocket) {\n                webSocket.addEventListener('open', () => {\n                    $event.emit(`websocketopen${id}`, {})\n                })\n                webSocket.addEventListener('message', ({ data }) => {\n                    $event.emit(`websocketmessage${id}`, {\n                        data: data && typeof data !== 'string' ? [Base64.encode(data)] : data\n                    })\n                })\n                webSocket.addEventListener('error', () => {\n                    $event.emit(`websocketerror${id}`, {})\n                })\n                webSocket.addEventListener('close', (event) => {\n                    $event.emit(`websocketclose${id}`, {\n                        code: event.code,\n                        reason: event.reason\n                    })\n                })\n            }\n        },\n        send (id, data = {}, callbackName) {\n            data = data.data\n            data = data && typeof data !== 'string' ? Base64.decode(data[0]) : data\n            try {\n                this.webSockets[id].send(data)\n            } catch (error) {\n                this.callback(callbackName, error)\n                return\n            }\n            this.callback(callbackName)\n        },\n        close (id, data = {}, callbackName) {\n            var options = []\n            options.push(data.code || 1000)\n            if (typeof data.reason === 'string') {\n                options.push(data.reason)\n            }\n            try {\n                this.webSockets[id].close(...options)\n            } catch (error) {\n                this.callback(callbackName, error)\n                return\n            }\n            this.callback(callbackName)\n        },\n        callback (callbackName, error) {\n            if (isPlus) {\n                location.href = 'http://data?callback=' + encodeURIComponent(JSON.stringify({\n                    callbackName,\n                    error\n                }))\n            } else {\n                var js = `window.${callbackName}&&window.${callbackName}('${error || ''}')`\n                window[callbackName] && window[callbackName](error | '')\n                window.eval(js)\n            }\n        }\n    }\n})()";
    }, function(e, n) {
      e.exports = '<!doctype html> <html lang=en> <head> <meta charset=UTF-8> <title>WebSocket</title> </head> <body> <script>location.href="http://data/load"<\/script> </body> </html>';
    }]));
  }
});
export default require_out();
//# sourceMappingURL=plus-websocket.js.map
