# ddbro-gw

## Build Setup

```bash
# install dependencies
$ npm install

# serve with hot reload at localhost:3000
$ npm run dev

# build for production and launch server
$ npm run build
$ npm run start

# generate static project
$ npm run generate

# 一旦 package.json 创建好， 可以通过以下 npm 命令将 nuxt 安装至项目中
npm install --save nuxt
```

资源目录
资源目录 assets 用于组织未编译的静态资源如 LESS、SASS 或 JavaScript。

关于 assets 目录的更多信息

组件目录
组件目录 components 

布局目录
布局目录 layouts 

中间件目录
middleware 

页面目录 pages 


插件目录 plugins 

静态文件目录 static

store 目录用于组织应用的 Vuex 状态树 文件。 N

nuxt.config.js 文件用于组织 Nuxt.js 应用的个性化配置，以便覆盖默认配置。

package.json 文件用于描述应用的依赖关系和对外暴露的脚本接口。

别名	目录
~ 或 @	srcDir
~~ 或 @@	rootDir
默认情况下，srcDir 和 rootDir 相同。


配置
Nuxt.js 默认的配置涵盖了大部分使用情形，可通过 nuxt.config.js 来覆盖默认的配置。

build
Nuxt.js 允许你在自动生成的 vendor.bundle.js 文件中添加一些模块，以减少应用 bundle 的体积。如果你的应用依赖第三方模块，这个配置项是十分实用的。

关于 build 配置项的详细文档

css
该配置项用于定义应用的全局（所有页面均需引用的）样式文件、模块或第三方库。

关于 css 配置项的详细文档

dev
该配置项用于配置 Nuxt.js 应用是开发还是生产模式。

关于 dev 配置项的详细文档

env
该配置项用于定义应用客户端和服务端的环境变量。

关于 env 配置项的详细文档

generate
该配置项用于定义每个动态路由的参数，Nuxt.js 依据这些路由配置生成对应目录结构的静态文件。

关于 generate 配置项的详细文档

head
该配置项用于配置应用默认的 meta 标签。

关于 head 配置项的详细文档

loading
该配置项用于个性化定制 Nuxt.js 使用的加载组件。

关于 loading 配置项的详细文档

modules
该配置项允许您将 Nuxt 模块添加到项目中。

关于 modules 配置项的详细文档

modulesDir
该配置项允许您定义Nuxt.js应用程序的node_modules文件夹。

关于 modulesDir 配置项的详细文档

plugins
该配置项用于配置那些需要在 根vue.js应用 实例化之前需要运行的 Javascript 插件。

关于 plugins 配置项的详细文档

rootDir
该配置项用于配置 Nuxt.js 应用的根目录。

关于 rootDir 配置项的详细文档

router
该配置项可用于覆盖 Nuxt.js 默认的 vue-router 配置。

关于 router 配置项的详细文档

server
此选项允许您配置 Nuxt.js 应用程序的服务器实例变量。

关于 server 配置项的详细文档

srcDir
该配置项用于配置应用的源码目录路径。

关于 srcDir 配置项的详细文档

dir
此选项允许您配置 Nuxt.js 应用程序的自定义目录。

Documentation about dir integration

transition
该配置项用于个性化配置应用过渡效果属性的默认值。

路由
Nuxt.js 依据 pages 目录结构自动生成 vue-router 模块的路由配置。

要在页面之间使用路由，我们建议使用<nuxt-link> 标签。

例如:

<template>
  <nuxt-link to="/">首页</nuxt-link>
</template>
基础路由
假设 pages 的目录结构如下：

pages/
--| user/
-----| index.vue
-----| one.vue
--| index.vue
那么，Nuxt.js 自动生成的路由配置如下：

router: {
  routes: [
    {
      name: 'index',
      path: '/',
      component: 'pages/index.vue'
    },
    {
      name: 'user',
      path: '/user',
      component: 'pages/user/index.vue'
    },
    {
      name: 'user-one',
      path: '/user/one',
      component: 'pages/user/one.vue'
    }
  ]
}
动态路由
在 Nuxt.js 里面定义带参数的动态路由，需要创建对应的以下划线作为前缀的 Vue 文件 或 目录。

以下目录结构：

pages/
--| _slug/
-----| comments.vue
-----| index.vue
--| users/
-----| _id.vue
--| index.vue
Nuxt.js 生成对应的路由配置表为：

router: {
  routes: [
    {
      name: 'index',
      path: '/',
      component: 'pages/index.vue'
    },
    {
      name: 'users-id',
      path: '/users/:id?',
      component: 'pages/users/_id.vue'
    },
    {
      name: 'slug',
      path: '/:slug',
      component: 'pages/_slug/index.vue'
    },
    {
      name: 'slug-comments',
      path: '/:slug/comments',
      component: 'pages/_slug/comments.vue'
    }
  ]
}
你会发现名称为 users-id 的路由路径带有 :id? 参数，表示该路由是可选的。如果你想将它设置为必选的路由，需要在 users/_id 目录内创建一个 index.vue 文件。

：API Configuration generate

警告：generate 命令会忽略动态路由: API Configuration generate

路由参数校验
Nuxt.js 可以让你在动态路由组件中定义参数校验方法。

举个例子： pages/users/_id.vue

export default {
  validate({ params }) {
    // 必须是number类型
    return /^\d+$/.test(params.id)
  }
}
如果校验方法返回的值不为 true或Promise中 resolve 解析为false或抛出 Error ， Nuxt.js 将自动加载显示 404 错误页面或 500 错误页面。

想了解关于路由参数校验的信息，请参考 页面校验 API。

嵌套路由
你可以通过 vue-router 的子路由创建 Nuxt.js 应用的嵌套路由。

创建内嵌子路由，你需要添加一个 Vue 文件，同时添加一个与该文件同名的目录用来存放子视图组件。

Warning: 别忘了在父组件(.vue文件) 内增加 <nuxt-child/> 用于显示子视图内容。

假设文件结构如：

pages/
--| users/
-----| _id.vue
-----| index.vue
--| users.vue
Nuxt.js 自动生成的路由配置如下：

router: {
  routes: [
    {
      path: '/users',
      component: 'pages/users.vue',
      children: [
        {
          path: '',
          component: 'pages/users/index.vue',
          name: 'users'
        },
        {
          path: ':id',
          component: 'pages/users/_id.vue',
          name: 'users-id'
        }
      ]
    }
  ]
}
动态嵌套路由
这个应用场景比较少见，但是 Nuxt.js 仍然支持：在动态路由下配置动态子路由。

假设文件结构如下：

pages/
--| _category/
-----| _subCategory/
--------| _id.vue
--------| index.vue
-----| _subCategory.vue
-----| index.vue
--| _category.vue
--| index.vue
Nuxt.js 自动生成的路由配置如下：

router: {
  routes: [
    {
      path: '/',
      component: 'pages/index.vue',
      name: 'index'
    },
    {
      path: '/:category',
      component: 'pages/_category.vue',
      children: [
        {
          path: '',
          component: 'pages/_category/index.vue',
          name: 'category'
        },
        {
          path: ':subCategory',
          component: 'pages/_category/_subCategory.vue',
          children: [
            {
              path: '',
              component: 'pages/_category/_subCategory/index.vue',
              name: 'category-subCategory'
            },
            {
              path: ':id',
              component: 'pages/_category/_subCategory/_id.vue',
              name: 'category-subCategory-id'
            }
          ]
        }
      ]
    }
  ]
}
未知嵌套深度的动态嵌套路由
如果您不知道 URL 结构的深度，您可以使用_.vue动态匹配嵌套路径。这将处理与更具体请求不匹配的情况。

文件结构:

pages/
--| people/
-----| _id.vue
-----| index.vue
--| _.vue
--| index.vue
将处理这样的请求：

Path	File
/	index.vue
/people	people/index.vue
/people/123	people/_id.vue
/about	_.vue
/about/careers	_.vue
/about/careers/chicago	_.vue
Note: 处理 404 页面，现在符合_.vue页面的逻辑。 有关 404 重定向的更多信息，请点击此处.

命名视图
要渲染命名视图，您可以在布局(layout) / 页面(page)中使用 <nuxt name="top"/> 或 <nuxt-child name="top"/> 组件。要指定页面的命名视图，我们需要在nuxt.config.js文件中扩展路由器配置：

export default {
  router: {
    extendRoutes(routes, resolve) {
      const index = routes.findIndex(route => route.name === 'main')
      routes[index] = {
        ...routes[index],
        components: {
          default: routes[index].component,
          top: resolve(__dirname, 'components/mainTop.vue')
        },
        chunkNames: {
          top: 'components/mainTop'
        }
      }
    }
  }
}
它需要使用两个属性 components 和 chunkNames 扩展路由。此配置示例中的命名视图名称为 top 。看一个例子:命名视图 例子。

SPA fallback
您也可以为动态路由启用SPA fallback。在使用mode:'spa'模式下，Nuxt.js 将输出一个与index.html相同的额外文件。如果没有文件匹配，大多数静态托管服务可以配置为使用 SPA 模板。生成文件不包含头信息或任何 HTML，但它仍将解析并加载 API 中的数据。

我们在nuxt.config.js文件中启用它：

export default {
  generate: {
    fallback: true, // if you want to use '404.html'
    fallback: 'my-fallback/file.html' // if your hosting needs a custom location
  }
}
在 Surge 上实现
Surge 可以处理200.html 和 404.html，generate.fallback默认设置为200.html，因此无需更改它。

在 GitHub Pages 和 Netlify 上实现
GitHub Pages 和 Netlify 自动识别 404.html文件，所以我们需要做的就是将 generate.fallback 设置为 true！

在 Firebase Hosting 上实现
要在 Firebase Hosting 上使用，请将 generate.fallback 配置为 true 并使用以下配置 (more info)：

{
  "hosting": {
    "public": "dist",
    "ignore": ["firebase.json", "**/.*", "**/node_modules/**"],
    "rewrites": [
      {
        "source": "**",
        "destination": "/404.html"
      }
    ]
  }
}
过渡动效
Nuxt.js 使用 Vue.js 的<transition>组件来实现路由切换时的过渡动效。

全局过渡动效设置
提示 :Nuxt.js 默认使用的过渡效果名称为 page

如果想让每一个页面的切换都有淡出 (fade) 效果，我们需要创建一个所有路由共用的 CSS 文件。所以我们可以在 assets/ 目录下创建这个文件：

在全局样式文件 assets/main.css 里添加一下样式：

.page-enter-active,
.page-leave-active {
  transition: opacity 0.5s;
}
.page-enter,
.page-leave-active {
  opacity: 0;
}
然后添加到 nuxt.config.js 文件中：

module.exports = {
  css: ['assets/main.css']
}
关于过渡效果 transition 属性配置的更多信息可参看 页面过渡效果 API。

页面过渡动效设置
如果想给某个页面自定义过渡特效的话，只要在该页面组件中配置 transition 字段即可：

在全局样式 assets/main.css 中添加一下内容：

.test-enter-active,
.test-leave-active {
  transition: opacity 0.5s;
}
.test-enter,
.test-leave-active {
  opacity: 0;
}
然后我们将页面组件中的 transition 属性的值设置为 test 即可：

export default {
  transition: 'test'
}
关于过渡效果 transition 属性配置的更多信息可参看 页面过渡效果 API。

中间件
中间件允许您定义一个自定义函数运行在一个页面或一组页面渲染之前。

每一个中间件应放置在 middleware/ 目录。文件名的名称将成为中间件名称 (middleware/auth.js将成为 auth 中间件)。

一个中间件接收 context 作为第一个参数：

export default function (context) {
  context.userAgent = process.server
    ? context.req.headers['user-agent']
    : navigator.userAgent
}
中间件执行流程顺序：

nuxt.config.js
匹配布局
匹配页面
中间件可以异步执行,只需要返回一个 Promise 或使用第 2 个 callback 作为第一个参数：

middleware/stats.js

import axios from 'axios'

export default function ({ route }) {
  return axios.post('http://my-stats-api.com', {
    url: route.fullPath
  })
}
然后在你的 nuxt.config.js 、 layouts 或者 pages 中使用中间件:

nuxt.config.js

module.exports = {
  router: {
    middleware: 'stats'
  }
}
现在，stats 中间件将在每个路由改变时被调用。

您也可以将 middleware 添加到指定的布局或者页面:

pages/index.vue 或者 layouts/default.vue

export default {
  middleware: 'stats'
}
如果你想看到一个使用中间件的真实例子，请参阅在 GitHub 上的example-auth0。



HTML 头部
Nuxt.js 使用了 vue-meta 更新应用的 头部标签(Head) and html 属性。

Nuxt.js 使用以下参数配置 vue-meta:

{
  keyName: 'head', // 设置 meta 信息的组件对象的字段，vue-meta 会根据这 key 值获取 meta 信息
  attribute: 'n-head', // vue-meta 在监听标签时所添加的属性名
  ssrAttribute: 'n-head-ssr', // 让 vue-meta 获知 meta 信息已完成服务端渲染的属性名
  tagIDKeyName: 'hid' // 让 vue-meta 用来决定是否覆盖还是追加 tag 的属性名
}
默认 Meta 标签
Nuxt.js 允许你在 nuxt.config.js 里定义应用所需的所有默认 meta 标签，在 head 字段里配置就可以了：

注意: Nuxt.js 使用 hid 而不是默认值 vmid 识别元素key

一个使用自定义 viewport 和 谷歌字体 的配置示例：

head: {
  meta: [
    { charset: 'utf-8' },
    { name: 'viewport', content: 'width=device-width, initial-scale=1' }
  ],
  link: [
    { rel: 'stylesheet', href: 'https://fonts.googleapis.com/css?family=Roboto' }
  ]
}
想了解 head 变量的所有可选项的话，请查阅 vue-meta 使用文档。

关于 Nuxt.js 应用 HTML 头部配置的更多信息，请参考 HTML 头部配置 API。

个性化特定页面的 Meta 标签 