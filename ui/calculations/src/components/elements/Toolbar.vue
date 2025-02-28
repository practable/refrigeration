//Vue3 update

<template>
    <div>

        <download-image-button v-if='showDownload' :parentComponentName="getParentComponentName" :parentCanvasID="getCanvasID"/>
       
        <popup-help v-if='showPopupHelp' :parentDivID="getParentDivID" :id="id" popup_help_id = "popup_help"> 
                <slot name='popup' :id="slotID"></slot> 
        </popup-help>
        
        <options-tool v-if='showOptions'>
            <slot name='options'></slot>
        </options-tool>
    </div>
</template>

<script>

import DownloadImageButton from './DownloadImageButton.vue';
import PopupHelp from './PopupHelp.vue';
import OptionsTool from './OptionsTool.vue';

export default {

  name: 'Toolbar',
  props:{
      'parentComponentName': String, 
      'parentCanvasID': String,
      'parentDivID': String,
      'showDownload': Boolean,
      'showPopupHelp': Boolean,
      'showOptions': Boolean,
      'id':String,
      'slotID':String,
  },
  data () {
    return {
   
    }
  },
  components: {
    DownloadImageButton,
    PopupHelp,
    OptionsTool
  },
  created(){
      
  },
  mounted(){
      

  },
  computed:{
      getParentComponentName(){
          return this.parentComponentName;
      },
      getCanvasID(){
          return this.parentCanvasID;
      },
      getParentDivID(){
          return this.parentDivID;
      }
      
  },
  watch:{
      
  },
  methods: {
      
      
  }
}
</script>

<style scoped>


</style>