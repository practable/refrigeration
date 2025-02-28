<template>
  <div v-if="isVisible" class="modal-overlay" @click.self="close" >
    <div class="modal-content_confirm">
      <button id="sessionCloseButton" type="button" class="btn-close" aria-label="Close" @click="close"></button>
      <slot></slot>
    </div>
  </div>
</template>

<script>
import { mapGetters } from 'vuex';

export default {

  name: 'popConfirm',
  props: {
    //   'parentDivID': String
    isVisible: {
      type: Boolean,
      default: false,
    },
  },
  data() {
    return {
      // popup_showing: false,

    }
  },
  components: {

  },
  created() {

  },
  mounted() {


  },
  computed: {
    ...mapGetters([
      // 'getDarkTheme'
    ])
  },
  watch: {

  },

  methods: {
    //   toggleHelp(){
    //       this.popup_showing = !this.popup_showing;
    //   },
    close() {
      this.$emit('close');
    },



  }
}
</script>

<style>
.modal-overlay {
  position: fixed;
  top: 50%;
  left: 50%;
  background: var(--text-color);
  display: flex;
  align-items: center;
  justify-content: center;
}

.modal-content_confirm {
  background: var(--background-color-inverted);
  padding: 20px;
  border-radius: 8px;
}

#sessionCloseButton {
background-color: var(--text-color-inverted);
position: relative;
float: right
}

</style>