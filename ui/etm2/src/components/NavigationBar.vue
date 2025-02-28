<template>
  <nav
    :class="getDarkTheme ? 'navbar navbar-light fixed-top navbar-expand-lg navbar-background' : 'navbar navbar-dark fixed-top navbar-expand-lg  navbar-background'"
    id='navbar'>
    <div id="navbar-container" class="container-fluid">
      <div id="navbar-brand" class="navbar-brand">
        <img id="navbar-experiment-name" src="/images/practable-icon.png" width="30" height="30"
          alt="practable.io logo">
        Remote Lab: Compression Refrigeration
      </div>
      <button id="navbar-toggler" class="navbar-toggler" type="button" data-bs-toggle="collapse"
        data-bs-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false"
        aria-label="Toggle navigation">
        <span class="navbar-toggler-icon"></span>
      </button>

      <div class="collapse navbar-collapse" id="navbarSupportedContent">
        <ul class="navbar-nav me-auto">
          <li class="nav-item dropdown">
            <a class="nav-link dropdown-toggle" href="#" id="navbarDropdown" role="button" data-bs-toggle="dropdown"
              aria-expanded="false">
              Menu
            </a>
            <ul class="dropdown-menu" aria-labelledby="navbarDropdown">
              <li id="nav-stopwatch"><a class="dropdown-item" href="#"
                  @click='toggleComponent("stopwatch")'>Stopwatch</a></li>
              <li id="nav-r134aDiagram"><a class="dropdown-item" href="#" @click='toggleComponent("R134aChart")'>R134a
                  p-h Diagram</a></li>
              <!-- <li><a class="dropdown-item" href="#" @click='toggleComponent("snapshot")'>Snapshot</a></li> -->
            </ul>
          </li>
          <li id="session-time" class="nav-item">
            <clock class='nav-link' />
          </li>
        </ul>

        <ul class="navbar-nav dropstart">

          <li class="nav-item me-1" id="uuid">
            <div id="UUID" class='nav-link'>
              UUID: {{ getLogUUID }}
            </div>

          </li>

          <!-- <li class="nav-item me-1" id="chatbox">
            <chat />
          </li> -->

          <li class="nav-item me-1">
            <toolbar parentCanvasID="" parentDivID="navbar" parentComponentName="navbar" :showDownload="false"
              :showOptions="false" :showPopupHelp="true" id="navbar_help">
              <template v-slot:popup id="nav-help-pop">
                <h2>UUID</h2>
                <p>{{ getLogUUID }}</p>

                <h2>User Interface</h2>
                <p>
                  • Operation: Use the mouse for clicking and the keyboard for input to interact with the UI.
                </p>
                <p>
                  • Components: The UI is divided into components within dotted areas. Click the ‘i’ information box at
                  the bottom of each component for details.
                </p>
                <p>
                  • Session Ended: The session will end automatically when time runs out. Book a new session to continue
                  the experiment.
                </p>
                <p></p>

                <h2>Chat Box</h2>
                <p>Powered by Chat GPT 4 Turbo, it helps with experiment operations, theories, and UI queries. Click the
                  widget, type your message/query, and press 'Enter' to chat. Click ‘Full Window’ to enlarge the Chat
                  Box.</p>
                <p></p>


                <h2>Experiment Operation</h2>
                <p>Preparation: Read the experiment manual and plan your approach (e.g. using the factorial design
                  method).</p>
                <p>Execution: Use the ‘Experiment Control Panel and Schematic’ to manage equipment and run your
                  experiment.</p>
                <p></p>

                <h2>Data Collection and Download</h2>
                <p>Use the ‘Data Recorder’ (record data manually). Click the ‘Download Data’ button in the Data Recorder
                  component to save the data as a .csv file to the local computer for analysis.</p>
                <p></p>

                <h2>Data Analysis</h2>
                <p>Analysis can be performed in the Data Analysis Dashboard (access through the booking page) or outside
                  of the UI using the downloaded .csv file. Possible analysis tools include Excel and MATLAB. In the
                  meantime, the Chat Box can assist with any issues encountered during analysis.</p>
              </template>
            </toolbar>
          </li>

          <!-- <li class="nav-item me-1">
            <button type='button' class='button-toolbar button-secondary' id='toggle-theme-button'
              aria-label='toggle dark theme' @click='toggleTheme' :disabled="disableThemeButton">
              <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor"
                class="bi bi-circle-half" viewBox="0 0 16 16">
                <path d="M8 15A7 7 0 1 0 8 1zm0 1A8 8 0 1 1 8 0a8 8 0 0 1 0 16" />
              </svg>
            </button>
          </li> -->

        </ul>

      </div>
    </div>
  </nav>

</template>

<script>

import Toolbar from './elements/Toolbar.vue';
import Clock from "./Clock.vue";
import { mapGetters } from 'vuex';
import Chat from './Chat.vue'

export default {

  name: 'NavigationBar',
  emits: ['togglestopwatch', 'toggleR134aChart', 'toggleSnapshot'],
  data() {
    return {

    }
  },
  components: {
    Clock,
    Toolbar,
    Chat,
  },
  computed: {
    ...mapGetters([
      'getIsLoggingOn',
      'getLogUUID'
    ])
  },
  methods: {
    addTool(tool) {
      this.toggleComponent('workspace');
      setTimeout(() => { this.$emit('add' + tool) }, 100);  //give the workspace time to initialise and then send tool event

    },
    toggleComponent(component) {
      this.$emit('toggle' + component);
    },
    clearWorkspace() {
      this.$emit('clearworkspace');
    }
  }
}
</script>

<style scoped></style>