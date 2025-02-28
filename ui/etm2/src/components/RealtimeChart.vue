<template>
    <div id="RealtimeChart-div">
        <h2> Real-Time Line Chart </h2>
        <div id="smoothie-chart-container" style="position: relative;">
            <canvas id="smoothie-chart" style="width:100%;height:100%"></canvas>
        </div>
        <div id="legend" style="max-width: 100%; width: auto;resize: both;overflow: auto;">
            <svg id="legend-title" height="30" width="80">
                <text x="0" y="18" fill="rgb(0, 0, 0)">Legend:</text>
            </svg>
            <svg id="legend-content" height="60" width="550">
                <line x1="0" y1="5" x2="50" y2="5" style="stroke:rgb(0, 255, 0);stroke-width:3" />
                <text x="0" y="25" fill="rgb(0, 255, 0)" font-style="italic">T1(°C)</text>
                <line x1="70" y1="5" x2="120" y2="5" style="stroke:rgb(255, 0, 255);stroke-width:3" />
                <text x="70" y="25" fill="rgb(255, 0, 255)" font-style="italic">T2(°C)</text>
                <line x1="140" y1="5" x2="190" y2="5" style="stroke:rgb(255, 0, 0);stroke-width:3" />
                <text x="140" y="25" fill="rgb(255, 0, 0)" font-style="italic">T3(°C)</text>
                <line x1="210" y1="5" x2="260" y2="5" style="stroke:rgb(0, 0, 255);stroke-width:3" />
                <text x="210" y="25" fill="rgb(0, 0, 255)" font-style="italic">T4(°C)</text>
                <line x1="280" y1="5" x2="330" y2="5" style="stroke:rgb(210, 210, 0);stroke-width:3" />
                <text x="280" y="25" fill="rgb(210, 210, 0)" font-style="italic">T5(°C)</text>
                <line x1="350" y1="5" x2="400" y2="5" style="stroke:rgb(0, 255, 255);stroke-width:3" />
                <text x="350" y="25" fill="rgb(0, 255, 255)" font-style="italic">P1(bar)</text>
                <line x1="420" y1="5" x2="470" y2="5" style="stroke:rgb(141, 14, 14);stroke-width:3" />
                <text x="420" y="25" fill="rgb(141, 14, 14)" font-style="italic">P2(bar)</text>
                <line x1="490" y1="5" x2="540" y2="5" style="stroke:rgb(14, 14, 141);stroke-width:3" />
                <text x="490" y="25" fill="rgb(14, 14, 141)" font-style="italic">P3(bar)</text>
                <line x1="0" y1="35" x2="50" y2="35" style="stroke:rgb(0, 178, 148);stroke-width:3" />
                <text x="0" y="55" fill="rgb(0, 178, 148)" font-style="italic">F(L/h)</text>
                <!-- <line x1="70" y1="35" x2="120" y2="35" style="stroke:rgb(255, 140, 0);stroke-width:3" /> 
                <text x="70" y="55" fill="rgb(255, 140, 0)" font-style="italic">E(W)</text> -->
            </svg>
        </div>
        <toolbar parentCanvasID="RealtimeChart-div" parentComponentName="RealtimeChart" parentDivID="RealtimeChart-div"
            :showDownload='false' :showPopupHelp="true" :showOptions="false" id="RealtimeChart_help">
            <template v-slot:popup id='RealtimeChart-popup'>
                <div class='row mb-2'>
                    <div class='col'>
                        <h3> Real-Time Line Chart </h3>
                        <p> Monitor parameter changes in real-time on a line chart. Hover over the chart to see current
                            values. The Nomenclature of the parameters is as follows:</p>
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

    <!-- <div class="col-12 background-white" id="realTimeTable" style="margin-top: 10px;">
        <realtimetable />
    </div> -->
</template>


<script>

import { mapActions, mapGetters } from 'vuex'

import { SmoothieChart } from 'smoothie';
import { TimeSeries } from 'smoothie';
import realtimetable from './RealtimeTable.vue';
import Toolbar from './elements/Toolbar.vue';



export default {
    name: "RealtimeChart",
    components: {
        realtimetable,
        Toolbar,

    },

    computed: {
        ...mapGetters([
            'GetCurrentTS1',
            'GetCurrentTS2',
            'GetCurrentTS3',
            'GetCurrentTS4',
            'GetCurrentTS5',
            'GetCurrentPS1',
            'GetCurrentPS2',
            'GetCurrentPS3',
            'GetCurrentFlow',
            'GetCurrentPower',
            "GETCurrentTime",
        ]),

    },
    mounted() {
        setTimeout(() => {
            this.plotChart();
        }, 1000);

    },
    methods: {
        timePlot() {
            return this.GETCurrentTime;
        },

        plotChart() {
            var smoothie = new SmoothieChart({ responsive: true, millisPerPixel: 70, grid: { fillStyle: '#ffffff', strokeStyle: '#c9c9c9', millisPerLine: 2000, verticalSections: 3, lineWidth: 1 }, labels: { fillStyle: '#000000' }, tooltip: true, tooltipLine: { strokeStyle: '#bbbbbb' }, timestampFormatter: SmoothieChart.timeFormatter });
            smoothie.streamTo(document.getElementById("smoothie-chart"));

            // Data
            var line1 = new TimeSeries();
            var line2 = new TimeSeries();
            var line3 = new TimeSeries();
            var line4 = new TimeSeries();
            var line5 = new TimeSeries();
            var line6 = new TimeSeries();
            var line7 = new TimeSeries();
            var line8 = new TimeSeries();
            var line9 = new TimeSeries();
            // var line10 = new TimeSeries();

            // console.log(this.GETCurrentTime)
            // console.log(this.GetCurrentTS1);
            // line1.append(this.GETCurrentTime, 0.3);

            // Add a random value to each line every second
            setInterval(() => {
                line1.append(Date.now(), this.GetCurrentTS1);
                // console.log("servertime"+this.GETCurrentTime);
                // console.log("UItime"+ Date.now());
                // console.log(this.GETCurrentTime-Date.now())
                // console.log(this.GetCurrentTS1);
                //this.test();
                line2.append(Date.now(), this.GetCurrentTS2);
                line3.append(Date.now(), this.GetCurrentTS3);
                line4.append(Date.now(), this.GetCurrentTS4);
                line5.append(Date.now(), this.GetCurrentTS5);
                line6.append(Date.now(), this.GetCurrentPS1);
                line7.append(Date.now(), this.GetCurrentPS2);
                line8.append(Date.now(), this.GetCurrentPS3);
                line9.append(Date.now(), this.GetCurrentFlow);
                // line10.append(Date.now(), this.GetCurrentPower);
            }, 1000);

            // Add to SmoothieChart
            smoothie.addTimeSeries(line1, { strokeStyle: 'rgb(0, 255, 0)', lineWidth: 1.2, interpolation: 'linear' });
            smoothie.addTimeSeries(line2, { strokeStyle: 'rgb(255, 0, 255)', lineWidth: 1.2, interpolation: 'linear' });
            smoothie.addTimeSeries(line3, { strokeStyle: 'rgb(255, 0, 0)', lineWidth: 1.2, interpolation: 'linear' });
            smoothie.addTimeSeries(line4, { strokeStyle: 'rgb(0, 0, 255)', lineWidth: 1.2, interpolation: 'linear' });
            smoothie.addTimeSeries(line5, { strokeStyle: 'rgb(210, 210, 0)', lineWidth: 1.2, interpolation: 'linear' });
            smoothie.addTimeSeries(line6, { strokeStyle: 'rgb(0, 255, 255)', lineWidth: 1.2, interpolation: 'linear' });
            smoothie.addTimeSeries(line7, { strokeStyle: 'rgb(141, 14, 14)', lineWidth: 1.2, interpolation: 'linear' });
            smoothie.addTimeSeries(line8, { strokeStyle: 'rgb(14, 14, 141)', lineWidth: 1.2, interpolation: 'linear' });
            smoothie.addTimeSeries(line9, { strokeStyle: 'rgb(0, 178, 148)', lineWidth: 1.2, interpolation: 'linear' });
            // smoothie.addTimeSeries(line10, { strokeStyle: 'rgb(255, 140, 0)', lineWidth: 1.2, interpolation:'linear' });

            // add some delay
            // smoothie.streamTo(document.getElementById("smoothie-chart"), 1000 /*delay*/);
        }
    },

    watch: {


    }
}


</script>

<style>
div.smoothie-chart-tooltip {
    background: #444;
    padding: 1em;
    margin-top: 20px;
    font-family: consolas;
    color: white;
    font-size: 15px;
    pointer-events: none;
}

#legend {
    background: #ffffff;
    border-color: black;
    height: 60px;
    width: 640px;
    margin: auto;

}
</style>