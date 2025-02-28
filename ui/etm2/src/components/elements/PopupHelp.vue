//Vue3 update

<template>
<div :id='popup_help_id'>
    <button type='button' class='button-toolbar button-secondary' id='help-button' @click='toggleHelp' aria-label="popup help">
        <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-info-square" viewBox="0 0 16 16">
            <path d="M14 1a1 1 0 0 1 1 1v12a1 1 0 0 1-1 1H2a1 1 0 0 1-1-1V2a1 1 0 0 1 1-1h12zM2 0a2 2 0 0 0-2 2v12a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V2a2 2 0 0 0-2-2H2z"/>
            <path d="m8.93 6.588-2.29.287-.082.38.45.083c.294.07.352.176.288.469l-.738 3.468c-.194.897.105 1.319.808 1.319.545 0 1.178-.252 1.465-.598l.088-.416c-.2.176-.492.246-.686.246-.275 0-.375-.193-.304-.533L8.93 6.588zM9 4.5a1 1 0 1 1-2 0 1 1 0 0 1 2 0z"/>
        </svg>
    </button>

    <!-- Original div popup -->
    <!-- <transition name='fade'>
        <div v-if='popup_showing' id='popup-div'>
             <button type='button' :class="getDarkTheme ? 'btn-close' : 'btn-close btn-close-white'" id='close-button' @click='toggleHelp'></button>
            <slot id='popup-text'></slot>
        </div>
    </transition> -->


    <transition name='fade'>
        <div v-if='popup_showing' class="modal" id='modal-show' tabindex="-1">
            <div class="modal-dialog">
            <div class="modal-content" style="max-height: 600px;">
                <div class="modal-header">
                    <h5 class="modal-title">Help</h5>
                    <button type='button' :class="getDarkTheme ? 'btn-close' : 'btn-close btn-close-white'" id='close-button' @click='toggleHelp'></button>
                </div>
                <div class="modal-body">
                    <slot id='popup-text'></slot>

                </div>

                <div class="modal-footer">
                    <button type="button" class="btn btn-danger" @click="toggleHelp" id="help_close">Close</button>
                </div>
            </div>
            </div>
        </div>
        </transition>
</div>
</template>

<script>
import { mapGetters } from 'vuex';

export default {

  name: 'PopupHelp',
  props:{
      'parentDivID': String,
      'popup_help_id':String,
  },
  data () {
    return {
        popup_showing: false,
        // popupWidth: 50,
        // popupHeight: 50,
    }
  },
  components: {
    
  },
  created(){
      
  },
  mounted(){
      

  },
  computed:{
      ...mapGetters([
        'getDarkTheme'
      ])
  },
  watch:{
      
  },
  
  methods: {
      toggleHelp(){
          //this.setPopupWidth();
          //this.setPopupHeight();
          this.popup_showing = !this.popup_showing;
      },
    //   setPopupWidth(){
    //       let div = document.getElementById(this.parentDivID);
    //       if(div != null){
    //           this.popupWidth = div.clientWidth - 50;
    //       } 
    //   },
    //   setPopupHeight(){
    //       let div = document.getElementById(this.parentDivID);
    //       if(div != null){
    //           this.popupHeight = div.clientHeight - 50;
    //       } 
    //   }
     
      
  }
}
</script>

<style scoped>

/* #popup-div{
    position: fixed;
    top:50%;
    left:50%;
    transform:translate(-50%,-50%);
    width:50%;
    z-index: 998;
    background: var(--background-color-inverted);
    color: var(--text-color-inverted);
    opacity: 0.9;
    overflow: scroll;
    max-height: 50vh;
    padding: 10px;

} */

#close-button{
    position:absolute;
    right:10px;
}


#popup-text{
    z-index: 999;
}

.fade-enter-active,
.fade-leave-active {
  transition: opacity 0.5s ease;
}

.fade-enter-from,
.fade-leave-to {
  opacity: 0;
}


</style>