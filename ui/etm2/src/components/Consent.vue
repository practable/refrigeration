//Should popup as a modal on App mount if no consent is stored in localStorage or if consent is false - giving students another chance to change their mind. 
// Updates the consent_given variable in logging.js store and saves to localStorage.
//When a choice is made a UUID is generated and stored in logging.js store
//This will make the App.vue component no longer render the consent modal.

<template>
<transition name='fade'>
    <div class="modal" id='consent-modal' tabindex="-1">
        <div class="modal-dialog">
          <div class="modal-content text-start">
            <div class="modal-header">
              <h5 class="modal-title">Research participation consent</h5>
              <!-- <button type="button" class="btn btn-close" aria-label="Close">
                
              </button> -->
            </div>
            <div class="modal-body">
              <div id='scroll-body'>
                <p> This remote laboratory is being used as part of a research study in the School of Engineering on how we can better design remote lab experiences for students.</p>
                <p> A lot of time and effort goes into developing these remote laboratories for your education, so we please ask that you participate in this study in order
                    to help out the researchers.
                </p>

                <h4>Collected Data</h4>
                <p>No personal data will be collected as part of this study. All data will be collected anonymously. Data is limited to your interaction with the remote lab UI and hardware.
                </p>
                <p>Please review the Participant Information Sheet for this study before giving your consent.</p>
                <p><a href='https://dev-static.practable.io/info/spinner-1.0/files/Project_Information_Sheet_RemoteLabs.pdf'>Participant Information Sheet</a></p>

                <h4>Interaction Data</h4>
                <div class='row'>
                  <div class='col-8'>
                    <p>I am happy for my interaction data (clicks, components used, input values) to be logged for hardware quality control and research purposes.</p>
                  </div>
                  <div class="form-check form-switch col-4">
                    <input class="form-check-input" type="checkbox" id="loggingConsentRadio" v-model='logging'>
                    <label class="form-check-label" for="loggingRadio">Consent</label>
                  </div>
                </div>

                <div class="modal-footer">
                    <button type="button" class="btn btn-primary" id='consent-yes-button' @click="consent">Confirm</button>
                </div>

              </div>
            </div>
            
          </div>
        </div>
      </div>
</transition>
</template>

<script>
import { mapGetters } from 'vuex';
export default {

  name: 'Consent',
  emits:['consentset'],
  data () {
    return {
        logging: false,
    }
  },
  components: {
    
  },
  computed:{
     ...mapGetters([
         'getUsesLocalStorage',
         'getExperiment',
         'getCourse'
     ])
  },
  watch:{
      
  },
  created(){
      
  },
  mounted(){
      

  },
  methods: {
      consent(){
          this.$store.dispatch('setLoggingConsent', this.logging);
          if(this.getUsesLocalStorage){
            let course = this.getCourse
            let exp = this.getExperiment
            const item = `consent-${exp}-${course}`
              window.localStorage.setItem(item, this.logging);
          }
          

          this.$emit('consentset');
          
      }
      
  }
}
</script>

<style scoped>
#consent-modal{
  display: block;
  
}

#scroll-body{
  max-height: 200px;
}

/* Important part */
.modal-dialog{
    overflow-y: initial !important
}
.modal-body{
    height: 80vh;
    overflow-y: auto;
}

</style>