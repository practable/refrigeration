<template>
  <div id="submitComponentDiv" class="border-dashed">
    <!-- <p>{{ msg }}</p> -->
    <!-- <h2> Submit data to the server and get feedback </h2> -->
    <!-- <p>(Submit your data to compare the calculation difference with the results from CoolProp.)</p> -->
    <div id="submitComponent" class="row">
      <div id="submitComponentdiv1" class="col-lg-4">

      </div>
      <!-- <div class="col-lg-4">
        <button class="btn btn-primary" @click="SubmitMeasuredData"> Submit Measured Data</button>
      </div>
      <div class="col-lg-4">
        <button class="btn btn-primary" @click="SubmitCalculationData"> Submit Calculation Data</button>
      </div> -->
      <div id="submitComponentdiv2" class="col-lg-4">
        <!-- <button class="btn btn-primary" @click="submitStudentData();toggleSubmitData()"> Submit measured data and calculation data</button> -->
        <button id="submitToServer_button" class="btn btn-primary" :disabled="isDisabled"
          @click="submitStudentData(); toggleSubmitData(); handleClick();"> Submit Data for Comparison</button>
      </div>
      <div id="submitComponentdiv3" class="col-lg-4">

      </div>
    </div>
    <br>
    <toolbar parentCanvasID="submitComponent-div" parentComponentName="submitComponent" parentDivID="submitComponent-div"
      :showDownload='false' :showPopupHelp="true" :showOptions="false" id="submitComponent-help">
      <template v-slot:popup id='submitComponent-popup'>
        <div class='row mb-2'>
          <div class='col'>
            <h3> Submit Data to the Server and Get Feedback </h3>
            <p> Click the “Submit measured data and calculation data” button to submit the data saved in the above
              components to the server.</p>
          </div>
        </div>
      </template>
    </toolbar>

  </div>
</template>

<script>
import axios from 'axios';
import { mapGetters, mapActions } from 'vuex';
import Toolbar from './elements/Toolbar.vue';

export default {
  name: 'enthalpy',
  data() {
    return {
      msg: 'Hello!',
      H3: 0,
      H4: 0,
      isDisabled: false,
    };
  },
  components: {
    Toolbar,

  },
  created() {
    // this.getMessage();
  },
  computed: {
    ...mapGetters([
      //get measured data from store
      'GetMeasuredTime',
      'GetT1',
      'GetT2',
      'GetT3',
      'GetT4',
      'GetT5',
      'GetP1',
      'GetP2',
      'GetP3',
      'GetE',
      'GetF',
      'GetASP',
      //get student calculation data from store
      'GetH1',
      'GetH2',
      'GetH3',
      'GetH4',
      'GetH5',
      'Getm',
      'GetQL',
      'GetQH',
      'GetW',
      'GetCOP',
      'Getn',

      'GetMeasuerdDataConfirmed',
      'GetCalcuDataConfirmed',
      'getLogUUID',

      'GetMeasuerdDataFeedback',
    ])
  },
  methods: {
    ...mapActions([
      //get deviation data and set them in the store 
      'SetH1_Dev',
      'SetH2_Dev',
      'SetH3_Dev',
      'SetH4_Dev',
      'SetH5_Dev',
      'Setm_Dev',
      'SetQL_Dev',
      'SetQH_Dev',
      'SetW_Dev',
      'SetCOP_Dev',
      'Setn_Dev',
      //get saturated data and set them in the store
      'SetSaturT_P1',
      'SetSaturT_P2',
      'SetSaturP_T3',
      'SetSaturP_T5',
      //get img_data from server and set it in the store
      'Setimg_data',
      'SetMeasuerdDataFeedback',
    ]),

    toggleSubmitData() {
      const newState = true; // Example: Set the boolean value dynamically
      this.$emit('updateSubmitData', newState); // Emit event with the new boolean state
    },

    handleClick() {
      this.isDisabled = true;
      setTimeout(() => {
        this.isDisabled = false;
      }, 5000);
    },

    // getMessage() {
    //   const path = 'http://127.0.0.1:5000/enthalpy?username=test&hardware=fridge';
    //   // const path = `https://app.practable.io/ed-log-dev/analytics/enthalpy/api/v1/enthalpy?username=${this.getLogUUID}&hardware=fridge&course=fridge`;
    //   //  // the error catched in the .catch part
    //   axios.get(path)
    //     .then(response => {
    //       this.response = response.data;
    //       // here, you might have logic to handle specific error types
    //       if (this.response.response === 'ERROR') {
    //         this.error = this.response.message;
    //       }
    //     })
    //     .catch(error => {
    //       // this catches network/axios errors, not server-parsed error responses
    //       console.error('There was an error!', error);
    //     });

    //   // axios.get(path)
    //   //   .catch(function (error) {
    //   //     if (error.response) {
    //   //       // The request was made and the server responded with a status code
    //   //       // that falls out of the range of 2xx
    //   //       console.log(error.response.data);
    //   //       console.log(error.response.status);
    //   //       console.log(error.response.headers);
    //   //     } else if (error.request) {
    //   //       // The request was made but no response was received
    //   //       // `error.request` is an instance of XMLHttpRequest in the browser and an instance of
    //   //       // http.ClientRequest in node.js
    //   //       console.log(error.request);
    //   //     } else {
    //   //       // Something happened in setting up the request that triggered an Error
    //   //       console.log('Error', error.message);
    //   //     }
    //   //     console.log(error.config);
    //   //   });

    // },

    postMessage(payload) {
      // const path = 'http://127.0.0.1:5000/enthalpy?username=test&hardware=fridge&course=fridge';
      const path = `https://app.practable.io/ed-log-dev/analytics/enthalpy/api/v1/enthalpy?username=${this.getLogUUID}&hardware=calculator&course=etm2`;
      axios.post(path, payload)
        .then((res) => {
          // this.msg = res.data;
          if (res.data.response == "EXPECTED_ERROR") {
            this.$store.dispatch('SetMeasuerdDataFeedback',res.data.message);
            console.log(this.GetMeasuerdDataFeedback);
          } else {
            this.$store.dispatch('SetH1_Dev', res.data.Parameters_DeviationCaculation.H1_Dev);
            this.$store.dispatch('SetH2_Dev', res.data.Parameters_DeviationCaculation.H2_Dev);
            this.$store.dispatch('SetH3_Dev', res.data.Parameters_DeviationCaculation.H3_Dev);
            this.$store.dispatch('SetH4_Dev', res.data.Parameters_DeviationCaculation.H4_Dev);
            this.$store.dispatch('SetH5_Dev', res.data.Parameters_DeviationCaculation.H5_Dev);
            this.$store.dispatch('Setm_Dev', res.data.Parameters_DeviationCaculation.m_Dev);
            this.$store.dispatch('SetQL_Dev', res.data.Parameters_DeviationCaculation.QL_Dev);
            this.$store.dispatch('SetQH_Dev', res.data.Parameters_DeviationCaculation.QH_Dev);
            this.$store.dispatch('SetW_Dev', res.data.Parameters_DeviationCaculation.W_Dev);
            this.$store.dispatch('SetCOP_Dev', res.data.Parameters_DeviationCaculation.COP_Dev);
            this.$store.dispatch('Setn_Dev', res.data.Parameters_DeviationCaculation.n_Dev);
            this.$store.dispatch('SetSaturT_P1', (res.data.Parameters_SaturatedValue.SaturT_P1).toFixed(2) );
            this.$store.dispatch('SetSaturT_P2', (res.data.Parameters_SaturatedValue.SaturT_P2).toFixed(2) );
            this.$store.dispatch('SetSaturP_T3', ((res.data.Parameters_SaturatedValue.SaturP_T3)/ 100000).toFixed(2));
            this.$store.dispatch('SetSaturP_T5', ((res.data.Parameters_SaturatedValue.SaturP_T5)/ 100000).toFixed(2));
            this.$store.dispatch('Setimg_data', res.data.img_data);

          }


        })
        .catch((error) => {

          console.log(error);
          if (error.status == 400) {
            alert("MESSAGE: " + error.response.data.message );
          }
        });
    },


    SubmitMeasuredData() {
      // if (this.H3 != ''&&this.H4 != '') {
      const payload = {
        'MeasuredTime': Number(this.GetMeasuredTime),
        'T1': Number(this.GetT1),
        'T2': Number(this.GetT2),
        'T3': Number(this.GetT3),
        'T4': Number(this.GetT4),
        'T5': Number(this.GetT5),
        'P1': Number(this.GetP1),
        'P2': Number(this.GetP2),
        'P3': Number(this.GetP3),
        'E': Number(this.GetE),
        'F': Number(this.GetF),
        'ASP': Number(this.GetASP),
        'dataType': 'Measured',
      };
      this.postMessage(payload);
      console.log(payload);
      // }
    },

    SubmitCalculationData() {
      const payload = {
        'H1': Number(this.GetH1),
        'H2': Number(this.GetH2),
        'H3': Number(this.GetH3),
        'H4': Number(this.GetH4),
        'H5': Number(this.GetH5),
        'm': Number(this.Getm),
        'QL': Number(this.GetQL),
        'QH': Number(this.GetQH),
        'W': Number(this.GetW),
        'COP': Number(this.GetCOP),
        'n': Number(this.Getn),
        'dataType': 'Calculation',
      };
      this.postMessage(payload);
      console.log(payload);
    },

    submitStudentData() {

      const payload = {

        'MeasuredTime': Number(this.GetMeasuredTime),
        'T1': Number(this.GetT1),
        'T2': Number(this.GetT2),
        'T3': Number(this.GetT3),
        'T4': Number(this.GetT4),
        'T5': Number(this.GetT5),
        'P1': Number(this.GetP1),
        'P2': Number(this.GetP2),
        'P3': Number(this.GetP3),
        'E': Number(this.GetE),
        'F': Number(this.GetF),
        'ASP': Number(this.GetASP),

        'H1': Number(this.GetH1),
        'H2': Number(this.GetH2),
        'H3': Number(this.GetH3),
        'H4': Number(this.GetH4),
        'H5': Number(this.GetH5),
        'm': Number(this.Getm),
        'QL': Number(this.GetQL),
        'QH': Number(this.GetQH),
        'W': Number(this.GetW),
        'COP': Number(this.GetCOP),
        'n': Number(this.Getn),
        'dataType': 'MeasuredandCalculation',
      };

      // add error if not confirm data 
      if (this.GetMeasuerdDataConfirmed == 1 && this.GetCalcuDataConfirmed == 1) {
        this.postMessage(payload);
      }
      else if (this.GetMeasuerdDataConfirmed == 0 && this.GetCalcuDataConfirmed == 1) {
        alert("Please confirm the measured you entered, and press the Confirm button in the Measured Data Input component.")
      }
      else if (this.GetCalcuDataConfirmed = 0 && this.GetMeasuerdDataConfirmed == 0) {
        alert("Please confirm the calculated data you entered, and press the Confirm button in the Calculation Results(Student) component. ")
      } else {
        alert("Please confirm the measured and calculated data you entered, and press the Confirm button in both components.")
      }

      console.log(payload);
    }
  }
};
</script>