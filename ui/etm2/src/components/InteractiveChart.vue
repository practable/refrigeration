<template>
    <div style="width: 200; height: 200;" id="InteractiveChart-div">
        <h2 id="interactiveChart-title"> Data Chart </h2>
        <canvas class="background-white" id="interactiveChart" width="600" height="400"
            style="background-color: white;"></canvas>

        <toolbar style="margin-top: 10px;" parentCanvasID="InteractiveChart-div" parentComponentName="InteractiveChart"
            parentDivID="InteractiveChart-div" :showDownload='false' :showPopupHelp="true" :showOptions="false"
            id="InteractiveChart_help">
            <template v-slot:popup id='InteractiveChart-popup'>
                <div class='row mb-2'>
                    <div class='col'>
                        <h3> Data Chart </h3>
                        <p> Visualize data in the table of Data Recorder. Click the label that includes the color bar
                            and
                            parameter name at the top of the chart (e.g. ‘(green bar) T1 data’) to hide/show the
                            corresponding data.</p>
                    </div>
                </div>
            </template>
        </toolbar>

    </div>

</template>

<script>

import Chart from 'chart.js/auto';
import 'chartjs-adapter-luxon';
import 'chartjs-plugin-streaming';
import 'luxon';
// import { shallowRef } from 'vue';
import Toolbar from './elements/Toolbar.vue';

import { mapGetters, mapActions } from 'vuex'

import Snapshot from './Snapshot.vue';


export default {
    name: "InteractiveChart",
    emits: ['updateChartData'],
    components: {
        Snapshot,
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
            'GETCurrentTime',
            // 'getChart',
            'getValuePost',
            'getSnapData',
            'getStartTime',
            'GETCurrentTime',


        ]),

    },
    created() {
        //beforeunload event and save data to local storage
        window.addEventListener("beforeunload", this.confirm_leaving);
    },
    data() {
        // the chart need to be out side of return{ }, otherwise has the bug "Uncaught RangeError: Maximum call stack size exceeded"
        this.interactiveChart = null
        // this.datasetTS1 = [],
        //     this.datasetTS2 = [],
        //     this.datasetTS3 = [],
        //     this.datasetTS4 = [],
        //     this.datasetTS5 = [],
        //     this.datasetPS1 = [],
        //     this.datasetPS2 = [],
        //     this.datasetPS3 = [],
        //     this.datasetFlow = [],
        //     this.datasetPower = []
        // this.local = 0
        return {
            // startTime: 0,
            datasetTS1: [],
            datasetTS2: [],
            datasetTS3: [],
            datasetTS4: [],
            datasetTS5: [],
            datasetPS1: [],
            datasetPS2: [],
            datasetPS3: [],
            datasetFlow: [],
            datasetPower: [],
            // local: 0, 
            // valuePost: 0,
        }
    },
    mounted() {
        this.createChart();
        this.LocalStorageCheck();
        //add data according to the valuePost from Snapshot
        this.$watch('getValuePost', function (val) {
            this.updateChartData();
            val = this.getValuePost;
            if (val == -1) {
                this.clearChartData();
                this. removeLocalStorageData();
            }
            // console.log(this.valuePost);
        })

        // this.updateChart();
        // this.updateChartBySnapshot();
    },

    methods: {
        ...mapActions([
            // 'setChart',
            'addLocalSnapData',
            'addSnapData',
            'setStartTime',
            'setCurrentTime',
        ]),

        createChart() {
            //test 
            this.setStartTime(Date.now());
            // this.startTime = Date.now();
            // console.log(this.startTime);

            // Initialize Chart.js
            var ctx = document.getElementById('interactiveChart').getContext('2d');
            this.interactiveChart = new Chart(ctx, {
                type: 'line',
                data: {
                    labels: [], // Fixed x-axis labels
                    datasets: [{
                        label: 'T1 Data',
                        backgroundColor: 'rgb(0, 255, 0)',
                        borderColor: 'rgb(0, 255, 0)',
                        borderWidth: 1,
                        data: []  // Initialize with empty data
                    },
                    {
                        label: 'T2 Data',
                        backgroundColor: 'rgb(255, 0, 255)',
                        borderColor: 'rgb(255, 0, 255)',
                        borderWidth: 1,
                        data: []  // Initialize with empty data
                    },
                    {
                        label: 'T3 Data',
                        backgroundColor: 'rgb(255, 0, 0)',
                        borderColor: 'rgb(255, 0, 0)',
                        borderWidth: 1,
                        data: []  // Initialize with empty data
                    },
                    {
                        label: 'T4 Data',
                        backgroundColor: 'rgb(0, 0, 255)',
                        borderColor: 'rgb(0, 0, 255)',
                        borderWidth: 1,
                        data: []  // Initialize with empty data
                    },
                    {
                        label: 'T5 Data',
                        backgroundColor: 'rgb(210, 210, 0)',
                        borderColor: 'rgb(210, 210, 0)',
                        borderWidth: 1,
                        data: []  // Initialize with empty data
                    },
                    {
                        label: 'P1 Data',
                        backgroundColor: 'rgb(0, 255, 255)',
                        borderColor: 'rgb(0, 255, 255)',
                        borderWidth: 1,
                        data: []  // Initialize with empty data
                    },
                    {
                        label: 'P2 Data',
                        backgroundColor: 'rgb(141, 14, 14)',
                        borderColor: 'rgb(141, 14, 14)',
                        borderWidth: 1,
                        data: []  // Initialize with empty data
                    },
                    {
                        label: 'P3 Data',
                        backgroundColor: 'rgb(14, 14, 141)',
                        borderColor: 'rgb(14, 14, 141)',
                        borderWidth: 1,
                        data: []  // Initialize with empty data
                    },
                    {
                        label: 'Flow Data',
                        backgroundColor: 'rgb(0, 178, 148)',
                        borderColor: 'rgb(0, 178, 148)',
                        borderWidth: 1,
                        data: []  // Initialize with empty data
                    },
                    {
                        label: 'Power Data',
                        backgroundColor: 'rgb(255, 140, 0)',
                        borderColor: 'rgb(255, 140, 0)',
                        borderWidth: 1,
                        data: []  // Initialize with empty data
                    },
                    ]
                },
                options: {
                    scales: {
                        x: {
                            type: 'linear', // Fixed x-axis scale
                            position: 'bottom', // Position x-axis at the bottom
                            ticks: {
                                stepSize: 10, // Step size for x-axis
                                min: 0,      // Minimum value for x-axis
                                max: 500,      // Maximum value for x-axis
                            },
                            title: {
                                display: true,
                                text: 'time/s'
                            }
                        },
                        // x: {
                        //     type: 'linear',
                        //     realtime: {
                        //         duration: 20000, // Data will be removed after 20 seconds
                        //         refresh: 1000, // Refresh data every 1 second
                        //         delay: 1000, // Delay of 1 second
                        //         pause: false, // No pause
                        //         ttl: undefined, // Time-to-live (in ms) for data point, undefined means data points do not expire
                        //     }
                        // },
                        y: {
                            scaleLabel: {
                                display: true,
                                labelString: 'Value'
                            }
                        }
                    }
                }
            });
        },

        //update dataset for chart input
        updatDataset() {
         
            this.datasetTS1.push({
                x: this.GETCurrentTime,
                y: this.GetCurrentTS1,
            });
            this.datasetTS2.push({
                x: this.GETCurrentTime,
                y: this.GetCurrentTS2,
            });
            this.datasetTS3.push({
                x: this.GETCurrentTime,
                y: this.GetCurrentTS3,
            });
            this.datasetTS4.push({
                x: this.GETCurrentTime,
                y: this.GetCurrentTS4,
            });
            this.datasetTS5.push({
                x: this.GETCurrentTime,
                y: this.GetCurrentTS5,
            });
            this.datasetPS1.push({
                x: this.GETCurrentTime,
                y: this.GetCurrentPS1,
            });
            this.datasetPS2.push({
                x: this.GETCurrentTime,
                y: this.GetCurrentPS2,
            });
            this.datasetPS3.push({
                x: this.GETCurrentTime,
                y: this.GetCurrentPS3,
            });
            this.datasetFlow.push({
                x: this.GETCurrentTime,
                y: this.GetCurrentFlow,
            });
            this.datasetPower.push({
                x: this.GETCurrentTime,
                y: this.GetCurrentPower,
            });
        },

        //feed the dataset into chart 
        updateChartData() {

            // if (this.local == 0) {
            this.updatDataset();
            // this.interactiveChart.data.datasets.data.push(this.dataset[this.dataset.length - 1]);
            // update chart :https://www.chartjs.org/docs/latest/developers/updates.html
            // console.log(this.interactiveChart.data.datasets);
            // this.interactiveChart.data.datasets.forEach((dataset) => {
            //     dataset.data.push(this.dataset[this.dataset.length - 1]);
            //    console.log(this.interactiveChart.data.datasets);
            //    console.log(this.interactiveChart.data.datasets.data);
            // });
            // console.log(this.interactiveChart);

            this.interactiveChart.data.datasets[0].data.push(this.datasetTS1[this.datasetTS1.length - 1]);
            this.interactiveChart.data.datasets[1].data.push(this.datasetTS2[this.datasetTS2.length - 1]);
            this.interactiveChart.data.datasets[2].data.push(this.datasetTS3[this.datasetTS3.length - 1]);
            this.interactiveChart.data.datasets[3].data.push(this.datasetTS4[this.datasetTS4.length - 1]);
            this.interactiveChart.data.datasets[4].data.push(this.datasetTS5[this.datasetTS5.length - 1]);
            this.interactiveChart.data.datasets[5].data.push(this.datasetPS1[this.datasetPS1.length - 1]);
            this.interactiveChart.data.datasets[6].data.push(this.datasetPS2[this.datasetPS2.length - 1]);
            this.interactiveChart.data.datasets[7].data.push(this.datasetPS3[this.datasetPS3.length - 1]);
            this.interactiveChart.data.datasets[8].data.push(this.datasetFlow[this.datasetFlow.length - 1]);
            this.interactiveChart.data.datasets[9].data.push(this.datasetPower[this.datasetPower.length - 1]);

            // console.log(this.interactiveChart.data.datasets);
            // console.log(this.dataset.length);

            // Update the chart
            this.interactiveChart.update();
            console.log(this.datasetTS1);
            // } else if (this.local == 1) {


        },

        //updata chart data per second
        updateChart() {
            setInterval(this.updateChartData, 1000);
        },


        // test(){
        //     this.valuePost++;
        // },

        //remove one data in the chart
        removeChartData() {
            this.interactiveChart.data.datasets.forEach((dataset) => {
                dataset.data.pop();
            })

            this.interactiveChart.update();
        },

        //remove All data in the chart
        clearChartData() {
            //clear the dataset in the chart
            this.interactiveChart.data.datasets.forEach((dataset) => {
                dataset.data = [];
            })
            this.interactiveChart.update();
            //clear the dataset as well
            // this.dataset = [];
            console.log(this.datasetTS1);
            this.datasetTS1 = [];
            this.datasetTS2 = [];
            this.datasetTS3 = [];
            this.datasetTS4 = [];
            this.datasetTS5 = [];
            this.datasetPS1 = [];
            this.datasetPS2 = [];
            this.datasetPS3 = [];
            this.datasetFlow = [];
            this.datasetPower = [];

        },


        removeLocalStorageData() {
            localStorage.removeItem('datasetTS1');
            localStorage.removeItem('datasetTS2');
            localStorage.removeItem('datasetTS3');
            localStorage.removeItem('datasetTS4');
            localStorage.removeItem('datasetTS5');
            localStorage.removeItem('datasetPS1');
            localStorage.removeItem('datasetPS2');
            localStorage.removeItem('datasetPS3');
            localStorage.removeItem('datasetFlow');
            localStorage.removeItem('datasetPower');
            localStorage.removeItem('snapsData');
            localStorage.removeItem('starttime');
        },

        setLocalStorage() {

            localStorage.setItem('datasetTS1', JSON.stringify(this.datasetTS1));
            localStorage.setItem('datasetTS2', JSON.stringify(this.datasetTS2));
            localStorage.setItem('datasetTS3', JSON.stringify(this.datasetTS3));
            localStorage.setItem('datasetTS4', JSON.stringify(this.datasetTS4));
            localStorage.setItem('datasetTS5', JSON.stringify(this.datasetTS5));
            localStorage.setItem('datasetPS1', JSON.stringify(this.datasetPS1));
            localStorage.setItem('datasetPS2', JSON.stringify(this.datasetPS2));
            localStorage.setItem('datasetPS3', JSON.stringify(this.datasetPS3));
            localStorage.setItem('datasetFlow', JSON.stringify(this.datasetFlow));
            localStorage.setItem('datasetPower', JSON.stringify(this.datasetPower));
            localStorage.setItem('snapsData', JSON.stringify(this.getSnapData));
            localStorage.setItem('starttime', JSON.stringify(this.getStartTime));

        },
        getLocalStorage() {
            if (localStorage.getItem('datasetTS1') == null) {
                console.log("There is no data in the localStorage")
            } else {
                const TS1Local = JSON.parse(localStorage.getItem('datasetTS1'));
                const TS2Local = JSON.parse(localStorage.getItem('datasetTS2'));
                const TS3Local = JSON.parse(localStorage.getItem('datasetTS3'));
                const TS4Local = JSON.parse(localStorage.getItem('datasetTS4'));
                const TS5Local = JSON.parse(localStorage.getItem('datasetTS5'));
                const PS1Local = JSON.parse(localStorage.getItem('datasetPS1'));
                const PS2Local = JSON.parse(localStorage.getItem('datasetPS2'));
                const PS3Local = JSON.parse(localStorage.getItem('datasetPS3'));
                const FlowLocal = JSON.parse(localStorage.getItem('datasetFlow'));
                const PowerLocal = JSON.parse(localStorage.getItem('datasetPower'));
                const startTime = JSON.parse(localStorage.getItem('starttime'));

                this.interactiveChart.data.datasets[0].data = TS1Local;
                this.interactiveChart.data.datasets[1].data = TS2Local;
                this.interactiveChart.data.datasets[2].data = TS3Local;
                this.interactiveChart.data.datasets[3].data = TS4Local;
                this.interactiveChart.data.datasets[4].data = TS5Local;
                this.interactiveChart.data.datasets[5].data = PS1Local;
                this.interactiveChart.data.datasets[6].data = PS2Local;
                this.interactiveChart.data.datasets[7].data = PS3Local;
                this.interactiveChart.data.datasets[8].data = FlowLocal;
                this.interactiveChart.data.datasets[9].data = PowerLocal;

                this.interactiveChart.update();

                this.setStartTime(startTime);

                this.addLocalSnapData(JSON.parse(localStorage.getItem('snapsData')));
                // console.log(this.getSnapData);

                // console.log("TS1Local" + TS1Local + "datasetTS1" + this.datasetTS1);

                this.datasetTS1 = [...TS1Local];
                this.datasetTS2 = [...TS2Local];
                this.datasetTS3 = [...TS3Local];
                this.datasetTS4 = [...TS4Local];
                this.datasetTS5 = [...TS5Local];
                this.datasetPS1 = [...PS1Local];
                this.datasetPS2 = [...PS2Local];
                this.datasetPS3 = [...PS3Local];
                this.datasetFlow = [...FlowLocal];
                this.datasetPower = [...PowerLocal];
            }


        },

        confirm_leaving(evt) {
            if (this.snaps != []) {
                const unsaved_changes_warning = "You have unsaved changes. Are you sure you wish to leave?";
                evt.returnValue = unsaved_changes_warning;
                this.setLocalStorage();
                // Snapshot.methods.setLocalStorage();
                return unsaved_changes_warning;
            };
        },


        LocalStorageCheck() {

            if (localStorage.getItem('datasetTS1') == null || JSON.parse(localStorage.getItem('datasetTS1')).length == 0) {
                console.log(localStorage.getItem('datasetTS1'));
            } else {
                console.log(typeof (localStorage.getItem('datasetTS1')) + localStorage.getItem('datasetTS1'));
                var con;
                con = confirm("You have saved data, Would you like to load it ?")
                if (con == true) {
                    this.getLocalStorage();
                } else {
                    this. removeLocalStorageData();
                }
            }

        }
    }
}




</script>
