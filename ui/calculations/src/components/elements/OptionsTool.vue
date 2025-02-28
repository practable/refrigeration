//Vue3 update

<template>
<div id='options-button'>
    <button type='button' class='button-toolbar button-secondary' id='help-button' @click='toggleHelp' aria-label="component options">
        <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-gear" viewBox="0 0 16 16">
                <path d="M8 4.754a3.246 3.246 0 1 0 0 6.492 3.246 3.246 0 0 0 0-6.492zM5.754 8a2.246 2.246 0 1 1 4.492 0 2.246 2.246 0 0 1-4.492 0z"/>
                <path d="M9.796 1.343c-.527-1.79-3.065-1.79-3.592 0l-.094.319a.873.873 0 0 1-1.255.52l-.292-.16c-1.64-.892-3.433.902-2.54 2.541l.159.292a.873.873 0 0 1-.52 1.255l-.319.094c-1.79.527-1.79 3.065 0 3.592l.319.094a.873.873 0 0 1 .52 1.255l-.16.292c-.892 1.64.901 3.434 2.541 2.54l.292-.159a.873.873 0 0 1 1.255.52l.094.319c.527 1.79 3.065 1.79 3.592 0l.094-.319a.873.873 0 0 1 1.255-.52l.292.16c1.64.893 3.434-.902 2.54-2.541l-.159-.292a.873.873 0 0 1 .52-1.255l.319-.094c1.79-.527 1.79-3.065 0-3.592l-.319-.094a.873.873 0 0 1-.52-1.255l.16-.292c.893-1.64-.902-3.433-2.541-2.54l-.292.159a.873.873 0 0 1-1.255-.52l-.094-.319zm-2.633.283c.246-.835 1.428-.835 1.674 0l.094.319a1.873 1.873 0 0 0 2.693 1.115l.291-.16c.764-.415 1.6.42 1.184 1.185l-.159.292a1.873 1.873 0 0 0 1.116 2.692l.318.094c.835.246.835 1.428 0 1.674l-.319.094a1.873 1.873 0 0 0-1.115 2.693l.16.291c.415.764-.42 1.6-1.185 1.184l-.291-.159a1.873 1.873 0 0 0-2.693 1.116l-.094.318c-.246.835-1.428.835-1.674 0l-.094-.319a1.873 1.873 0 0 0-2.692-1.115l-.292.16c-.764.415-1.6-.42-1.184-1.185l.159-.291A1.873 1.873 0 0 0 1.945 8.93l-.319-.094c-.835-.246-.835-1.428 0-1.674l.319-.094A1.873 1.873 0 0 0 3.06 4.377l-.16-.292c-.415-.764.42-1.6 1.185-1.184l.292.159a1.873 1.873 0 0 0 2.692-1.115l.094-.319z"/>
        </svg>
    </button>

    <!-- <transition name='fade'>
        <div v-if='popup_showing' id='popup-div'>
             <button type='button' class='btn-close btn-close-white' id='close-button' @click='toggleHelp'></button>
            <slot id='popup-text'></slot>
        </div>
    </transition> -->

    <transition name='fade'>
        <div v-if='popup_showing' class="modal" id='modal-show' tabindex="-1">
            <div class="modal-dialog">
            <div class="modal-content">
                <div class="modal-header">
                    <h5 class="modal-title">Options</h5>
                    <button type='button' :class="getDarkTheme ? 'btn-close' : 'btn-close btn-close-white'" id='close-button' @click='toggleHelp'></button>
                </div>
                <div class="modal-body">
                    <slot id='popup-text'></slot>

                </div>

                <div class="modal-footer">
                    <button type="button" class="btn btn-danger" @click="toggleHelp">Close</button>
                </div>
            </div>
            </div>
        </div>
        </transition>
    
    
</div>
</template>

<script>

export default {

  name: 'OptionsTool',
  props:{
      
  },
  data () {
    return {
        popup_showing: false,
        popupWidth: 50,
        popupHeight: 50,
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
      toggleHelp(){
        //   this.setPopupWidth();
        //   this.setPopupHeight();
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


#popup-div{
    position: fixed;
    top:50%;
    left:50%;
    transform:translate(-50%,-50%);
    width:25%;
    border: 5px solid #000000;
    z-index: 998;
    background-color: rgba(0,0,0,0.8);
    color: white;
    overflow: scroll;
    max-height: 50vh;

}

#close-button{
    position:absolute;
    right:0px;
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