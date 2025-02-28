<template>
  <router-view />
  <div id="app" class='container-fluid-sm m-0 background-white'>

    <navigation-bar @save="saveDataToLocalStorage" @toggleconsent="showConsentModal = true" />
    
    <div id="measuredDataInput&feedback-div">
      <MeasuredDataFeedback @updateMeasuredData="measuredDataInput = $event" />
    </div>

    <div v-if="measuredDataInput" class="row" id="calculatedDataInput&chart-div">
      <div class="col-lg-6">
        <CanvasDrawing />
      </div>
      <div class="col-lg-6">
        <TableStudentCalculation @updateCalculatedData="calculatedDataInput = $event" />
      </div>
      <div v-if="calculatedDataInput" id="dataSubmit-div">
        <ping @updateSubmitData="dataSubmit = $event" />
      </div>
    </div>
    <div v-if="dataSubmit" id="dataCompare-div">
      <DataCompare />
    </div>


  </div>
  
</template>

<script>
import CanvasDrawing from './components/CanvasDrawing.vue'
import NavigationBar from './components/NavigationBar.vue'
// import Consent from './components/Consent.vue'
import MeasuredDataFeedback from './components/MeasuredDataFeedback.vue'
import TableStudentCalculation from './components/TableStudentCalculation.vue'
import DataCompare from './components/DataCompare.vue'
import { RouterView } from 'vue-router'
import ping from './components/ping.vue'
import { mapGetters } from 'vuex'



export default {
  name: 'App',
  components: {
    NavigationBar,
    // Consent,
    CanvasDrawing,
    MeasuredDataFeedback,
    TableStudentCalculation,
    DataCompare,
    ping,
 
  },
  data() {
    return {
      // showConsentModal: false,
      measuredDataInput: false,
      calculatedDataInput: false,
      dataSubmit: false,
    }
  },
  computed: {
    ...mapGetters([
      'getCourse',
      'getLogUUID',
      'getUsesLocalStorage',
    ])
  },
  created() {
    this.$store.dispatch('setUsesLocalStorage', this.hasStorage());
    //check if user has a UUID generated already and whether they have consented to take part in the study
    console.log('created');
    // console.log(localStorage);
  },
  mounted() {
    this.updateUUID();
  },
  watch: {
    // getCourse() {
    //   console.log('updating UUID')
    //   this.updateUUID();
    //   // this.checkConsent();
    // }
  },
  methods: {
    //  closeConsentModal(){
    //   this.showConsentModal =false;
    //  },
    updateUUID() {
      let stored_uuid;

      if (this.getUsesLocalStorage) {
        stored_uuid = window.localStorage.getItem('userName');
      } else {
        stored_uuid = null;
      }
      // console.log(stored_uuid);

      if (stored_uuid) {
        this.$store.dispatch('setUUID', stored_uuid);
      } else {
        this.$store.dispatch('setUUID', 'NA');
      }

      // console.log(this.getLogUUID);
    },


    hasStorage() {
      try {
        window.localStorage.setItem('test', 'storage');
        window.localStorage.removeItem('test');
        return true;
      } catch (exception) {
        return false;
      }
    },
  }
}

</script>



<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
</style>
<!-- 
<style scoped></style> -->
