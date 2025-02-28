<template>

<div id="videoElement2" v-if='getSessionExpired' class='row'>
  <div class='col-12'>
        <img id='session-end-image' src='https://app.practable.io/ed0/static/images/common/thank-you-screen.svg' alt='session ended'>
    </div>
</div>
<div v-else>
  <div class='row'>
      <div class='col-12'>
        <canvas id="video-canvas2"></canvas>
        <toolbar parentCanvasID="video-canvas2" parentComponentName="webcam" parentDivID='video-element' :showDownload='true' :showPopupHelp='false' :showOptions="false"></toolbar>
      </div>
      
    </div>
</div>    
    
    
    <!-- <div id='videoWrapper'></div> -->
</template>

<script>
import JSMpeg from "@cycjimmy/jsmpeg-player";
import { mapGetters } from 'vuex';
import Toolbar from './elements/Toolbar.vue';

export default {
  name: "VideoElement2",
  props: ["url"],
  data(){
        return{
          player: null,
        }
    },
    components:{
      Toolbar,
    },
    computed:{
      ...mapGetters([
        'getSessionExpired'
      ]),
    },
    watch:{
        url(){
            let canvas = document.getElementById("video-canvas2");
            this.player = new JSMpeg.Player(this.url, {canvas: canvas, preserveDrawingBuffer: true});
            // let url = this.$store.getters.getVideoURL;
            // this.player = new JSMpeg.VideoElement("#videoWrapper", url, {
            //     autoplay: true,
            //     chunkSize: 10 * 1024 * 1024,
            // });
        }
    },
    created(){
  
    },
  mounted() {
    //only for debugging
    //let canvas = document.getElementById("video-canvas");
		//let playerUrl = 'wss://video.practable.io:443/out/dpr/video0';		//for robot arm
		//let playerUrl = 'wss://video.practable.io:443/out/dpr/video1';		//for variable governor
		//let playerUrl = 'wss://video.practable.io:443/out/dpr/video2';		//for spinner
		
    // new JSMpeg.Player(playerUrl, {canvas: canvas});
    
      //let canvas = document.getElementById("video-canvas");
      
      //this.player = new JSMpeg.Player(this.url, {canvas: canvas});
    // this.player = new JSMpeg.VideoElement("#videoWrapper", this.url, {
    //   autoplay: true,
    //   chunkSize: 10 * 1024 * 1024,
    // });
  },

};


</script>

<style>
    #video-canvas2 {
      width: 100%;
      /* height: 100%; */
    }

    #session-end-image {
      width: 100%;
      /* height: 100%; */
    }
</style>