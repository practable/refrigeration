<template>
    <div id="Measured-data-input-and-feedback" class="border-dashed">
        <div class="row">
            <div class="col-lg-6">
                <h2>Measured Data Input</h2>
                <div class="table-responsive">
                    <table class="table">
                        <thead class="table-light">
                            <tr>
                                <th>Time(min)</th>
                                <th>T1(°C)</th>
                                <th>T2(°C)</th>
                                <th>T3(°C)</th>
                                <th>T4(°C)</th>
                                <th>T5(°C)</th>
                                <!-- <th>P1(bar)</th>
                                <th>P2(bar)</th>
                                <th>P3(bar)</th>
                                <th>F(L/h)</th>
                                <th>E(W)</th> -->
                            </tr>
                        </thead>
                        <tbody class="table-group-divider">
                            <tr>
                                <td><input type="number" name="" class="inputnumber" id="time" placeholder="0"
                                        value="30"></td>
                                <td><input type="number" name="" class="inputnumber" id="T1" placeholder="0" value="15">
                                </td>
                                <td><input type="number" name="" class="inputnumber" id="T2" placeholder="0" value="68">
                                </td>
                                <td><input type="number" name="" class="inputnumber" id="T3" placeholder="0" value="43">
                                </td>
                                <td><input type="number" name="" class="inputnumber" id="T4" placeholder="0"
                                        value="3.65"></td>
                                <td><input type="number" name="" class="inputnumber" id="T5" placeholder="0"
                                        value="2.82"></td>

                                <!-- <td><input type="number" name="" class="inputnumber" id="time" placeholder="0"></td>
                                <td><input type="number" name="" class="inputnumber" id="T1" placeholder="0"></td>
                                <td><input type="number" name="" class="inputnumber" id="T2" placeholder="0"></td>
                                <td><input type="number" name="" class="inputnumber" id="T3" placeholder="0"></td>
                                <td><input type="number" name="" class="inputnumber" id="T4" placeholder="0"></td>
                                <td><input type="number" name="" class="inputnumber" id="T5" placeholder="0"></td> -->

                            </tr>
                        </tbody>
                        <thead class="table-light">
                            <tr>
                                <!-- <th>T1(°C)</th>
                                <th>T2(°C)</th>
                                <th>T3(°C)</th>
                                <th>T4(°C)</th>
                                <th>T5(°C)</th> -->
                                <th>P1(bar)</th>
                                <th>P2(bar)</th>
                                <th>P3(bar)</th>
                                <th>F(L/h)</th>
                                <th>E(W)</th>
                                <th>Ambient Pressure(bar)</th>
                            </tr>
                        </thead>
                        <tbody class="table-group-divider">
                            <tr>
                                <!-- 
                                <td><input type="number" name="" class="inputnumber" id="P1" placeholder="0"></td>
                                <td><input type="number" name="" class="inputnumber" id="P2" placeholder="0"></td>
                                <td><input type="number" name="" class="inputnumber" id="P3" placeholder="0"></td>
                                <td><input type="number" name="" class="inputnumber" id="F" placeholder="0"></td>
                                <td><input type="number" name="" class="inputnumber" id="E" placeholder="0"></td>
                                <td><input type="number" name="" class="inputnumber" id="ASP" placeholder="0"></td> -->


                                <td><input type="number" name="" class="inputnumber" id="P1" placeholder="0"
                                        value="2.41"></td>
                                <td><input type="number" name="" class="inputnumber" id="P2" placeholder="0"
                                        value="10.18"></td>
                                <td><input type="number" name="" class="inputnumber" id="P3" placeholder="0"
                                        value="10.5"></td>
                                <td><input type="number" name="" class="inputnumber" id="F" placeholder="0"
                                        value="4.43"></td>
                                <td><input type="number" name="" class="inputnumber" id="E" placeholder="0" value="200">
                                </td>
                                <td><input type="number" name="" class="inputnumber" id="ASP" placeholder="0" value="1">
                                </td>
                            </tr>
                        </tbody>
                    </table>
                </div>
                <div class="row">
                    <div class="col-3">

                    </div>
                    <div class="col-3">
                        <button type="button" class="btn btn-primary"
                            @click="updateChart(); toggleMeasuredData()">Confirm</button>
                        <!-- <button type="button" class="btn btn-primary"
                            @click="GetDataformInput(); toggleMeasuredData()">Confirm</button> -->
                    </div>
                    <div class="col-3">
                        <button type="button" class="btn btn-primary" @click="reset()">Reset</button>
                    </div>
                    <div class="col-3">
                        <!-- <button @click="GetDataformInput()">test input data</button> -->
                    </div>
                </div>

            </div>
            <div class="col-lg-6">
                <h2>Measured Data Feedback</h2>
                <!-- <div v-if="this.GetMeasuerdDataFeedback" class="alert alert-danger" role="alert">
                    {{ this.GetMeasuerdDataFeedback }}
                </div> -->
                <div>
                  
                    <canvas id="MeasuredDataChart" width="450" height="200"></canvas>
                </div>
            </div>
        </div>
        <toolbar parentCanvasID="DataRecorder-div" parentComponentName="DataRecorder" parentDivID="DataRecorder-div"
            :showDownload='false' :showPopupHelp="true" :showOptions="false" id="DataRecorder_help">
            <template v-slot:popup id='DataRecorder-popup'>
                <div class='row mb-2'>
                    <div class='col'>
                        <h3> Measured Data Input (Students) and Measured Data Feedback </h3>
                        <p> In this component, users can get feedback about measured data from the experiment,
                            understand whether the data is good enough, and learn how to improve it. </p>
                        <p><b>Measured Data Input (Students):</b> Input the data that is obtained from the experiment
                            into the form, and then click the “Confirm” button to save data for submitting data to the
                            server and get feedback in the “Measured Data Feedback” component. The “Reset button” is
                            used to reset the value in the input form. The Nomenclature of the parameters is included in
                            Table.</p>
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
                                    <td>Ambient pressure</td>
                                    <td>Ambient pressure</td>
                                    <td>Bar</td>
                                </tr>
                            </tbody>
                        </table>
                        <p><b>Measured Data Feedback:</b> A feedback chart will be displayed after the user submits
                            input data in the “Measured Data Input” component. In the chart, the red line represents to
                            data quality curve, and the blue dot is the data that the user submitted. The orange area is
                            the best range area, which means the data falls in this area have better quality.</p>
                    </div>
                </div>
            </template>
        </toolbar>

    </div>

</template>

<script>
import Chart from 'chart.js/auto';
import annotationPlugin from 'chartjs-plugin-annotation';
import 'chartjs-plugin-streaming';
// import 'chartjs-adapter-luxon';
// import 'luxon';
import { mapGetters, mapActions } from 'vuex';
import Toolbar from './elements/Toolbar.vue';

export default {
    name: "MeasuredDataFeedback",
    props: {

    },
    components: {
        Toolbar,

    },
    data() {
        this.MeasuredDataChart = null
        return {
            DataQualityDataset: [],
            updateFlag: false,
            // inputTime: 0,
        }
    },
    mounted() {
        this.createChart();

    },
    computed: {
        ...mapGetters([
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
            'GetMeasuerdDataFeedback',
            'GetMeasuerdDataConfirmed',
            
        ])
    },
    methods: {
        ...mapActions([
            'SetMeasuredTime',
            'SetT1',
            'SetT2',
            'SetT3',
            'SetT4',
            'SetT5',
            'SetP1',
            'SetP2',
            'SetP3',
            'SetE',
            'SetF',
            'SetASP',
            'SetMeasuerdDataConfirmed'

        ]),

        toggleMeasuredData() {
            const newState = true; // Example: Set the boolean value dynamically
            this.$emit('updateMeasuredData', newState); // Emit event with the new boolean state
        },



        GetDataformInput() {

            this.SetMeasuredTime(document.getElementById('time').value);
            this.SetT1(document.getElementById('T1').value);
            this.SetT2(document.getElementById('T2').value);
            this.SetT3(document.getElementById('T3').value);
            this.SetT4(document.getElementById('T4').value);
            this.SetT5(document.getElementById('T5').value);
            this.SetP1(document.getElementById('P1').value);
            this.SetP2(document.getElementById('P2').value);
            this.SetP3(document.getElementById('P3').value);
            this.SetE(document.getElementById('E').value);
            this.SetF(document.getElementById('F').value);
            this.SetASP(document.getElementById('ASP').value);
            this.SetMeasuerdDataConfirmed(1);
            // console.log(this.GetMeasuredTime, this.GetT1, this.GetT2,this.GetT3,this.GetT4,this.GetT5,this.GetP1,this.GetP2,this.GetP3,this.GetE,this.GetF,this.GetASP);
        },

        //quality curve data 
        QualityDataset() {
            for (let i = 0; i < 70; i++) {
                this.DataQualityDataset.push({
                    x: i,
                    y: 1 - Math.exp(-i * 0.1)
                })
            };

        },

        //init chart
        createChart() {
            Chart.register(annotationPlugin);
            // Initialize Chart.js
            var ctx = document.getElementById('MeasuredDataChart').getContext('2d');
            this.MeasuredDataChart = new Chart(ctx, {
                type: 'line',
                data: {
                    labels: [], // Fixed x-axis labels
                    datasets: [{
                        label: 'Data Quality Curve',
                        backgroundColor: 'rgb(255, 0, 0)',
                        borderColor: 'rgb(255, 0, 0)',
                        borderWidth: 1,
                        data: [],  // Initialize with empty data
                        pointRadius: 0,
                        // hidden: () => this.updateAction(),
                    },

                    {
                        label: 'Your Data',
                        backgroundColor: 'rgb(0, 0, 255)',
                        borderColor: 'rgb(0, 0, 255)',
                        borderWidth: 1,
                        data: [],
                        pointRadius: 8,
                        pointStyle: 'rectRot',
                    },],
                },
                options: {
                    responsive: true,
                    scales: {
                        x: {
                            type: 'linear', // Fixed x-axis scale
                            position: 'bottom', // Position x-axis at the bottom
                            ticks: {
                                stepSize: 5, // Step size for x-axis
                                min: 0,      // Minimum value for x-axis
                                max: 500,      // Maximum value for x-axis
                            },
                            title: {
                                display: true,
                                text: 'Time/min'
                            }
                        },
                        y: {
                            ticks: {
                                display: false
                            },
                            scaleLabel: {
                                display: true,
                                labelString: 'Value',
                            },
                            title: {
                                display: true,
                                text: 'Data Quality'
                            }
                        }
                    },
                    plugins: {
                        annotation: {
                            annotations: {
                                box1: {
                                    type: 'box',
                                    xMin: 20,
                                    xMax: 45,
                                    yMin: 0,
                                    yMax: 1.6,
                                    backgroundColor: 'rgba(255,165,0, 0.25)',
                                    borderColor: 'rgba(255,165,0, 0.25)',
                                    display: () => this.updateAction(),
                                    drawTime: 'afterDraw',
                                },
                                label1: {
                                    display: () => this.updateAction(),
                                    type: 'label',
                                    xValue: 33,
                                    yValue: 0.3,
                                    backgroundColor: 'rgba(245,245,245)',
                                    content: ['Best Range'],
                                    font: {
                                        size: 18
                                    }
                                }
                            }
                        }
                    },

                },
            });
        },

        //update function for display the element in the chart
        updateAction() {
            return this.updateFlag;
        },

        // update the elements and the curve in the chart
        updateChart() {
            this.GetDataformInput();
            // this.inputTime = document.getElementById('time').value;
            if (this.MeasuredDataChart.data.datasets[0].data.length == 0 && this.GetMeasuredTime != '' && this.DataQualityDataset.length == 0) {
                //update the quality line in the chart and show the best range annotation
                this.updateFlag = true;
                this.QualityDataset();
                this.MeasuredDataChart.data.datasets[0].data = this.DataQualityDataset;

                //update the data input
                // let inputTime = document.getElementById('time').value;
                let qualityCalculation = 1 - Math.exp(-this.GetMeasuredTime * 0.1);
                this.MeasuredDataChart.data.datasets[1].data.push({
                    x: this.GetMeasuredTime,
                    y: qualityCalculation,
                }),
                    this.MeasuredDataChart.update();

            } else if (this.GetMeasuredTime == '') {
                alert("Please input measured data!")

            }
            else {
                this.updateFlag = true;
                this.MeasuredDataChart.data.datasets[0].data = this.DataQualityDataset;
                //update the data input 
                this.GetMeasuredTime = document.getElementById('time').value;
                let qualityCalculation = 1 - Math.exp(-this.GetMeasuredTime * 0.1);
                this.MeasuredDataChart.data.datasets[1].data = [];
                this.MeasuredDataChart.data.datasets[1].data.push({
                    x: this.GetMeasuredTime,
                    y: qualityCalculation,
                }),
                    this.MeasuredDataChart.update();
            }

        },

        ClearformInput() {
            document.getElementById('time').value = 0;
            document.getElementById('T1').value = 0;
            document.getElementById('T2').value = 0;
            document.getElementById('T3').value = 0;
            document.getElementById('T4').value = 0;
            document.getElementById('T5').value = 0;
            document.getElementById('P1').value = 0;
            document.getElementById('P2').value = 0;
            document.getElementById('P3').value = 0;
            document.getElementById('E').value = 0;
            document.getElementById('F').value = 0;
            document.getElementById('ASP').value = 0;
            // console.log(this.GetMeasuredTime, this.GetT1, this.GetT2,this.GetT3,this.GetT4,this.GetT5,this.GetP1,this.GetP2,this.GetP3,this.GetE,this.GetF,this.GetASP);
        },

        //clear and reset the data in the input form and chart
        reset() {
            this.updateFlag = false;
            this.MeasuredDataChart.data.datasets[0].data = [];
            this.MeasuredDataChart.data.datasets[1].data = [];
            this.MeasuredDataChart.update();
            this.ClearformInput();
            this.GetDataformInput();
            this.SetMeasuerdDataConfirmed(0);
            console.log(this.GetMeasuredTime);

        },


    },


};
</script>

<style>
.inputnumber {
    width: 70px;
}
</style>