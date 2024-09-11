<template>
  <!-- <Tutorial/> -->
<div>

  <div id="head_main">
      <div class="header_bar">
        <div class="logo">
          <a href="https://ddbro.com">
            <img src="img/logo.png" />
          </a>
        </div>
        <div class="main_tab">
          <ul class="hidden-on-small">
            <li>首页</li>
            <li>产品</li>
            <li>项目定制</li>
            <li>业务演示</li>
            <li>行业案例</li>
            <li>资源中心</li>
            <li>关于恒歌</li>
          </ul>
        </div>
        <div class="login">
          <div class="btn_user">
            <a href="javascript:;" id="mylogin" class="tc_btn" name="tc_login"
              >登录</a
            >
            <i>|</i>
            <a href="javascript:;" class="tc_btn" name="tc_register">注册</a>
          </div>
        </div>
      </div>
    </div>
  <section id="banner">
      <div clas="swiper-container">
        <div class="swiper-wrapper">
          <div class="slide-inner">
            <video width="100%" height="100%" autoplay="" loop="" muted="" preload="none">
              <source src="https://video2024.oss-cn-beijing.aliyuncs.com/44444.mp4">
              <!-- <source src="https://video2024.oss-cn-beijing.aliyuncs.com/669b47a70165274.mp4"> -->
            </video>
          </div>
        </div>
      </div>
    </section>
</div>





</template>

<script lang="ts">
import Vue from 'vue'
import 'static/css/base.css';
import 'static/css/global.css';
import 'static/css/index.css';
export default Vue.extend({
  name: 'IndexPage'
  
})
</script>
<style>
  .red {
    color: red;
  }
</style>