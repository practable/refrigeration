<template>

  <nav class="navbar fixed-top navbar-expand-lg navbar-dark background-primary justify-content-between">
    <div class="container-fluid">
      <img src="/images/practable-icon.png" width="30" height="30" alt="">
      <a class="navbar-brand" href="#">Calculation App: Compression Refrigeration </a>
      <!-- <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarSupportedContent"
      aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
      <span class="navbar-toggler-icon"></span>
    </button> -->

      <div class="collapse navbar-collapse" id="navbarSupportedContent">
        <ul class="navbar-nav me-auto mb-2 mb-lg-0">
          <!-- Placeholder for left-aligned nav items -->
        </ul>
        <ul class="navbar-nav ms-auto">
          <li class="nav-item me-1" id="uuid">
            <a class="nav-link" id="UUID">
              UUID: {{ getLogUUID }}
            </a>
          </li>

          <li class="nav-item me-1">
            <toolbar parentCanvasID="" parentDivID="navbar" parentComponentName="navbar" :showDownload="false"
              :showOptions="false" :showPopupHelp="true" id="navbar_help">
              <template v-slot:popup id="nav-help-pop">
                <h2>UUID</h2>
                <p>{{ getLogUUID }}</p>

                <h2>User Interface</h2>
                <p>
                  • <b>Operation:</b> Use the mouse for clicking and the keyboard for input to interact with the UI.
                </p>
                <p>
                  • <b>Components:</b> The UI is divided into components within dotted areas. Click the ‘i’ information
                  box at
                  the bottom of each component for details.
                </p>
                <p></p>

                <h2>Dashboard Usage Procedure</h2>
                <p>1. Input the measured data that you got from experiment in the "Measured Data Input" component. Click
                  "Confirm" to save the data for submitting to the server and receive the feedback from "Measured Data Feedback"
                  component. </p>
                <p>2. Plot and obtain the enthalpy value from the 'p-H Chart for Enthalpy Value (Student)' component, and
                  calculate the related parameters. Enter the enthalpy and parameter values in the 'Calculation Results
                  (Student)' component. Click the 'Confirm' button to save the data for submitting to the server.
                </p>
                <p>3. Click the button 'Submit Data for Comparison' to submit saved data to the server.
                </p>
                <p>4. Get the reference p-h diagram and calculation comparison from the server.</p>
                <p>
                  5. The enthalpy value plotting and parameter calculation can be done multiple times for a better outcome.
                </p>

                <h2>Experiment Data Collection and Download</h2>
                <p>Experiment data is collected from the <u>“Remote Lab: Compression Refrigeration”</u> experiment. The
                  experiment can be found on the same booking page, please collect the data from the remote experiment
                  first and then do this data analysis.</p>
                <p></p>

                <h2>Vapor Compression Cycle</h2>
                <p>The vapor compression cycle of the experiment is as Figure 1.</p>
                <img src="/images/vaporCompressionCycle.png" alt="">
                <p>Figure 1 (a) A basic vapor-compression refrigeration system, (b) its T–s diagram, and (c) its log P–h
                  diagram.</p>


              </template>
            </toolbar>
          </li>
        </ul>
      </div>
    </div>
  </nav>


</template>

<script>

import Toolbar from './elements/Toolbar.vue';
import { mapActions, mapGetters } from 'vuex';

export default {

  name: 'NavigationBar',
  components: {
    Toolbar,

  },
  props: {

  },
  emits: [

  ],
  data() {
    return {

    }
  },
  computed: {
    ...mapGetters([
      'getLogUUID',

    ]),

  },
  methods: {

  }
}
</script>

<style scoped></style>