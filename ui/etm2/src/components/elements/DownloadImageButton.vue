//Vue3 update

<template>

    <button type='button' class='button-toolbar button-secondary' id='download-button' @click='downloadImage' aria-label="download image">
        <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-download" viewBox="0 0 16 16">
            <path d="M.5 9.9a.5.5 0 0 1 .5.5v2.5a1 1 0 0 0 1 1h12a1 1 0 0 0 1-1v-2.5a.5.5 0 0 1 1 0v2.5a2 2 0 0 1-2 2H2a2 2 0 0 1-2-2v-2.5a.5.5 0 0 1 .5-.5z"/>
            <path d="M7.646 11.854a.5.5 0 0 0 .708 0l3-3a.5.5 0 0 0-.708-.708L8.5 10.293V1.5a.5.5 0 0 0-1 0v8.793L5.354 8.146a.5.5 0 1 0-.708.708l3 3z"/>
        </svg>
    </button>

</template>

<script>

export default {

  name: 'DownloadImageButton',
  props:{
      'parentComponentName': String, 
      'parentCanvasID': String
  },
  data () {
    return {
   
    }
  },
  components: {
    
  },
  created(){
      
  },
  mounted(){
      

  },
  computed:{
      
  },
  watch:{
      
  },
  
  methods: {
      downloadImage(){
            let canvas = document.getElementById(this.parentCanvasID);
            let image = canvas.toDataURL("image/png")
            let link = document.createElement('a');
            let date = new Date();
            link.download = this.parentComponentName + date.getHours() + "_" + date.getMinutes() + ".png";
            link.href = image;
            link.click();
            link.remove();
        }
      
  }
}
</script>

<style scoped>
/* #download-button{
    max-height:40px;
    max-width:40px;
    padding: 0px;
} */

</style>