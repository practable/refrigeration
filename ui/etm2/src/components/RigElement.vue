<template>
  <div class="row" id="RigElement-div">
    <h2 id="RigElement-div-head"> Real Equipment and Real-Time Table </h2>
    <div class="col-12 background-white" id="rigImage" >
      <!-- <div v-for="(position, index) in highlightedPositions" :key="index" class="highlight"
        :style="{ left: position.x, top: position.y }"></div> -->
      <!-- <img src="/images/ET-411C-Compression-refrigeration-system-gunt-206-foto_totale.jpg" alt=""> -->
      <img src="/images/ET-411C-Compression-refrigeration-system2.jpg" id="mainFigImage"
        alt="ET-411C-Compression-refrigeration-system">
      <!-- <button >{{ highlightedPositions }}</button> -->
      <div class="col-12 background-white" id="realTimeTable" style="margin-top: 10px;">
        <realtimetable />
      </div>
    </div>

    <toolbar parentCanvasID="RealtimeChart-div" parentComponentName="RealtimeChart" parentDivID="RealtimeChart-div"
      :showDownload='false' :showPopupHelp="true" :showOptions="false" id="RealtimeChart_help">
      <template v-slot:popup id='RealtimeChart-popup'>
        <div class='row mb-2'>
          <div class='col'>
            <h3> Real Equipment and Real-Time Table </h3>
            <p> <b>Real Equipment Image:</b> A static image of the real equipment. Corresponding to the components in the
              schematic, to learn more about the kit in the device, click on the symbol section (gray) in the schematic
              and a red blinking square will be displayed for the corresponding part in the equipment image. </p>
            <p> <b>Real-Time Table: </b> Monitor parameter changes in real-time on a table. The Nomenclature of the parameters is included in the table. </p>
            <table class="table">
              <thead>
                <tr>
                  <th scope="col">#</th>
                  <th scope="col">Symbol</th>
                  <th scope="col">Definition</th>
                  <th scope="col">Units</th>
                </tr>
              </thead>
              <tbody>
                <tr>
                  <th scope="row">1</th>
                  <td>T1</td>
                  <td>Compressor Inlet Temperature</td>
                  <td>℃</td>
                </tr>
                <tr>
                  <th scope="row">2</th>
                  <td>T2</td>
                  <td>Compressor Outlet Temperature</td>
                  <td>℃</td>
                </tr>
                <tr>
                  <th scope="row">3</th>
                  <td>T3</td>
                  <td>Condenser Outlet Temperature</td>
                  <td>℃</td>
                </tr>
                <tr>
                  <th scope="row">4</th>
                  <td>T4</td>
                  <td>Evaporator Inlet Temperature</td>
                  <td>℃</td>
                </tr>
                <tr>
                  <th scope="row">5</th>
                  <td>T5</td>
                  <td>Evaporator Outlet Temperature</td>
                  <td>℃</td>
                </tr>
                <tr>
                  <th scope="row">6</th>
                  <td>P1</td>
                  <td>Evaporation Pressure</td>
                  <td>Bar</td>
                </tr>
                <tr>
                  <th scope="row">7</th>
                  <td>P2</td>
                  <td>Compressor Outlet Pressure</td>
                  <td>Bar</td>
                </tr>
                <tr>
                  <th scope="row">8</th>
                  <td>P3</td>
                  <td>Condensation Pressure</td>
                  <td>Bar</td>
                </tr>
                <tr>
                  <th scope="row">9</th>
                  <td>F</td>
                  <td>Flowrate of Refrigerant</td>
                  <td>L/h</td>
                </tr>
                <tr>
                  <th scope="row">10</th>
                  <td>E</td>
                  <td>Electric Power of Compressor</td>
                  <td>W</td>
                </tr>
                <tr>
                  <th scope="row">11</th>
                  <td>TSA</td>
                  <td>Ambient temperature</td>
                  <td>℃</td>
                </tr>
                <tr>
                  <th scope="row">12</th>
                  <td>PSA</td>
                  <td>Ambient pressure</td>
                  <td>mBar</td>
                </tr>
                <tr>
                  <th scope="row">13</th>
                  <td>HSA</td>
                  <td>Ambient humidity</td>
                  <td>%rh</td>
                </tr>
              </tbody>
            </table>
          </div>
        </div>
      </template>
    </toolbar>
  </div>
</template>

<script>
import realtimetable from "./RealtimeTable.vue";
import Toolbar from './elements/Toolbar.vue';

export default {

  name: "RigElement",

  data() {
    return {
      // xPercentage: 0.2,
      // yPercentage: 0.3,
    }
  },
  components: {
    realtimetable,
    Toolbar,


  },
  computed: {
    // highlightedPositions: {
    //   get() {
    //     return this.$store.state.ui.highlightedPositions;
    //   },
    //   set() {

    //   }

    // },


  },
  watch: {
  },
  created() {

  },
  mounted() {

  },
  methods: {

    // setposition() {
    //   // console.log(this.highlightedPositions.xPercentage);
    //   this.xPercentage = this.highlightedPositions.xPercentage;
    //   this.yPercentage = this.highlightedPositions.yPercentage;
    //   // console.log(this.xPercentage)
    //   this.highlightPosition(this.xPercentage, this.yPercentage);
    // },

    highlightPosition(xPercentage, yPercentage, highlightwidth, highlightheight) {
      // Get the image element
      var image = document.getElementById('mainFigImage');

      // Calculate the position based on percentages
      var x = xPercentage * image.width;
      var y = yPercentage * image.height;

      // Create a div element for the highlight
      var highlightDiv = document.createElement('div');
      highlightDiv.id = "highlightDiv";
      highlightDiv.classList.add('highlight');

      // Set position and size of the highlight
      highlightDiv.style.left = x + 'px';
      highlightDiv.style.top = y + 'px';
      highlightDiv.style.width = highlightwidth; // Initial width as a percentage
      highlightDiv.style.height = highlightheight; // Initial height as a percentage


      // Append the highlight div to the image container
      image.parentNode.appendChild(highlightDiv);

      window.addEventListener('resize', function () {
        var imageRect = image.getBoundingClientRect();

        var newX = xPercentage * imageRect.width;
        var newY = yPercentage * imageRect.height;

        highlightDiv.style.left = newX + 'px';
        highlightDiv.style.top = newY + 'px';
        highlightDiv.style.width = highlightwidth; // Adjust highlight width as a percentage
        highlightDiv.style.height = highlightheight; // Adjust highlight height as a percentage
      });

    },

    removeHighlightPosition() {
      document.getElementById('mainFigImage').parentNode.removeChild(highlightDiv);
    },


  }
}


</script>


<style>
#rigImage {
  display: inline;
  position: relative;
  width: 100%;
  /* max-width: 800px; */
  /* Adjust max-width as needed */
}

#rigImage img {
  width: 100%;
  /* width: auto;
  height: auto;
  max-width: 100%;
  max-height: 100%; */
}

/* CSS for highlighting */

.highlight {
  border: 5px solid red;
  box-sizing: border-box;
  position: absolute;
  animation: twinkling 1s infinite alternate;
  /* Twinkling effect animation */
  width: 5%;
  /* Initial width as a percentage */
  height: 5%;
  /* Initial height as a percentage */
}

@keyframes twinkling {
  0% {
    opacity: 1;
  }

  100% {
    opacity: 0.5;
  }
}
</style>