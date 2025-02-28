<template>
    <div id="SnapShot-div">
        <h2 id="SnapShot-div-head"> Data Recorder </h2>
        <div class="container-fluid m-2 background-white border rounded table" id='snapshot-div'>
            <!-- <div>
            <InteractiveChart/>
        </div> -->
            <div class="row " id='table'>

                <table id="snapshot-table">
                    <thead class='table-head'>
                        <tr class='background-primary text-white' id="snapshot-table-thead">
                            <!-- <th v-for='heading in headings' :key="heading" scope="col">{{ heading }}</th> -->
                            <!-- <th scope="col">ID</th> -->
                            <th scope="col">Time(s)</th>
                            <th scope="col">T1(°C)</th>
                            <th scope="col">T2(°C)</th>
                            <th scope="col">T3(°C)</th>
                            <th scope="col">T4(°C)</th>
                            <th scope="col">T5(°C)</th>
                            <th scope="col">P1(bar)</th>
                            <th scope="col">P2(bar)</th>
                            <th scope="col">P3(bar)</th>
                            <th scope="col">F(L/h)</th>
                            <th scope="col">E(W)</th>
                            <th scope="col">TSA(°C)</th>
                            <th scope="col">PSA(mBar)</th>
                            <th scope="col">HSA(%rh)</th>
                        </tr>
                    </thead>
                    <tbody id="snapshot-table-tbody">


                        <tr v-for="row in getSnapData" id="snapshot-tr">
                            <!-- <td v-for='key in Object.keys(row)' :key="key">{{ row[key] }}</td> -->
                            <td>{{ row.t }}</td>
                            <td>{{ row.T1 }}</td>
                            <td>{{ row.T2 }}</td>
                            <td>{{ row.T3 }}</td>
                            <td>{{ row.T4 }}</td>
                            <td>{{ row.T5 }}</td>
                            <td>{{ row.P1 }}</td>
                            <td>{{ row.P2 }}</td>
                            <td>{{ row.P3 }}</td>
                            <td>{{ row.Flow }}</td>
                            <td>{{ row.Power }}</td>
                            <td>{{ row.TSA }}</td>
                            <td>{{ row.PSA }}</td>
                            <td>{{ row.HSA }}</td>
                        </tr>

                        <tr class='current' id='snapshot-table-current-row'>
                            <td>{{ currentTime }}</td>
                            <td>{{ GetCurrentTS1 }}</td>
                            <td>{{ GetCurrentTS2 }}</td>
                            <td>{{ GetCurrentTS3 }}</td>
                            <td>{{ GetCurrentTS4 }}</td>
                            <td>{{ GetCurrentTS5 }}</td>
                            <td>{{ GetCurrentPS1 }}</td>
                            <td>{{ GetCurrentPS2 }}</td>
                            <td>{{ GetCurrentPS3 }}</td>
                            <td>{{ GetCurrentFlow }}</td>
                            <td>{{ GetCurrentPower }}</td>
                            <td>{{ GetCurrentTSA }}</td>
                            <td>{{ GetCurrentPSA }}</td>
                            <td>{{ GetCurrentHSA }}</td>

                        </tr>
                    </tbody>

                    <!-- <div id='table-bottom'>
                        <div class='white-divider'>
                        </div>
                    </div> -->
                </table>
            </div>

            <div class='d-grid gap-2 d-sm-block'>
                <button id="snapshot-record-button" type='button' class="button-sm button-primary"
                    @click="snapshot(); scrollTo('table-bottom');">Record Data</button>
                <button id="reset_snaps-button" type='button' class="button-sm button-danger"
                    @click="toggleResetModal">Reset</button>
                <button id="download_snaps-button" type='button' class="button-sm button-secondary"
                    @click="outputToCSV">Download
                    Data</button>
                <!-- <button @click="setLocalStorage">localstoragetest</button> -->
                <!-- <button @click="getLocalStorage">getLocalStorage</button> -->
                <!-- <button @click="test()">test</button> -->
            </div>

            <div id="resetComfirmModal" v-if='showResetConfirmModal' class="modal modal-show" tabindex="-1"
                role="dialog">
                <div class="modal-dialog" role="document">
                    <div class="modal-content">
                        <div class="modal-header">
                            <h5 class="modal-title">Reset Data</h5>
                            <button id="resetComfirmModalButton" type="button" class="btn btn-close"
                                data-bs-dismiss="modal" aria-label="Close" @click='toggleResetModal'>

                            </button>
                        </div>
                        <div class="modal-body">
                            <p>Are you sure you want to Reset? This will clear all stored data.</p>
                        </div>
                        <div class="modal-footer">
                            <button id="resetSnapModalButton" type="button" class="button-sm button-danger"
                                @click="resetSnaps(); toggleResetModal();">Reset</button>
                            <button id="resetSnapModalCancelButton" type="button" class="button-sm button-primary"
                                data-dismiss="modal" data-bs-dismiss="modal" @click="toggleResetModal">Cancel</button>
                        </div>
                    </div>

                </div>
            </div>
        </div>
        <toolbar parentCanvasID="SnapShot-div" parentComponentName="SnapShot" parentDivID="SnapShot-div"
            :showDownload='false' :showPopupHelp="true" :showOptions="false" id="SnapShot_help">
            <template v-slot:popup id='SnapShot-popup'>
                <div class='row mb-2'>
                    <div class='col'>
                        <h3> Data Recorder </h3>
                        <p> Manually collect data in the current. Click ‘Record Data’ to save the current state. Each
                            click adds a new data set. Click ‘Download Data’ to save data as a .csv file. Click ‘Reset’
                            to clear recorded snapshots and reset the function.
                        </p>
                    </div>
                </div>
            </template>
        </toolbar>

    </div>
</template>

<script>

import { mapGetters, mapActions, Store } from 'vuex'
import Toolbar from './elements/Toolbar.vue';
// import InteractiveChart from "./interactiveChart.vue"

export default {

    name: 'Snapshot',
    props: ['headings'],
    data() {
        return {
            // snaps: [],
            showResetConfirmModal: false,
            buttonValue: 0,
            currentTime: 0,


        }
    },
    components: {
        Toolbar,
        // InteractiveChart,
    },
    // created() {
    //     //beforeunload event and save data to local storage
    //     window.addEventListener("beforeunload", this.confirm_leaving);
    // },
    mounted() {
        this.currentTimeTable();
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
            'GetCurrentTSA',
            'GetCurrentPSA',
            'GetCurrentHSA',
            'GETCurrentDate',
            'getValuePost',
            'getSnapData',
            'getStartTime',
            'GETCurrentTime',
            'getLogUUID',
        ]),

    },
    methods: {
        ...mapActions([
            'addSnapData',
            'setValuePost',
            'deleteSnapData',
            'setCurrentTime',
        ]),
        snapshot() {
            this.setCurrentTime((Date.now() - this.getStartTime) / 1000);

            // this.snaps = this.getSnapData;
            this.buttonValue++;
            let snap_object = {
                date: this.GETCurrentDate, t: this.GETCurrentTime, T1: this.GetCurrentTS1, T2: this.GetCurrentTS2,
                T3: this.GetCurrentTS3, T4: this.GetCurrentTS4, T5: this.GetCurrentTS5,
                P1: this.GetCurrentPS1, P2: this.GetCurrentPS2, P3: this.GetCurrentPS3,
                Flow: this.GetCurrentFlow, Power: this.GetCurrentPower, TSA: this.GetCurrentTSA,
                PSA: this.GetCurrentPSA, HSA: this.GetCurrentHSA
            };
            console.log(snap_object);
            //gets added to the data for plotting
            this.addSnapData(snap_object);
            console.log(this.getSnapData);
            //gets added to the snaps list
            // this.snaps.push(snap_object);

            //button click value post
            this.setValuePost(this.buttonValue);
            console.log(this.getValuePost);
            console.log(this.buttonValue);

        },

        resetSnaps() {
            this.deleteSnapData();
            this.buttonValue = -1;
            this.setValuePost(this.buttonValue);
            console.log(this.getValuePost);
            console.log(this.getSnapData);
        },
        toggleResetModal() {
            this.showResetConfirmModal = !this.showResetConfirmModal;
        },
        scrollTo(id) {
            var element = document.getElementById(id);
            //let topPos = element.offsetTop;
            element.scrollIntoView(true);
            //document.getElementById('table').scrollTop = topPos;

        },
        outputToCSV() {
            let csv = '';
            let filename = '';
            let date = new Date();
            let data = this.getSnapData;
            let uuid = this.getLogUUID;

            filename = 'SNAPSHOTs_' + date.getDate().toString() + (date.getMonth() + 1).toString() + date.getFullYear().toString();
           
            csv = "UUID,"+uuid+"\n",

            csv += 'Date,Time,Snapshot Time/s,T1/C,T2/C,T3/C,T4/C,T5/C,P1/bar,P2/bar,P3/bar,Flowrate/(L/h),Power/W,TSA/C,PSA/hPa,HSA/%rh\n';

            data.forEach(function (d) {
                csv += d.date.toString();
                csv += ",";
                csv += d.t.toString();
                csv += ",";
                csv += d.T1.toString();
                csv += ',';
                csv += d.T2.toString();
                csv += ",";
                csv += d.T3.toString();
                csv += ",";
                csv += d.T4.toString();
                csv += ",";
                csv += d.T5.toString();
                csv += ",";
                csv += d.P1.toString();
                csv += ',';
                csv += d.P2.toString();
                csv += ",";
                csv += d.P3.toString();
                csv += ",";
                csv += d.Flow.toString();
                csv += ",";
                csv += d.Power.toString();
                csv += ",";
                csv += d.TSA.toString();
                csv += ",";
                csv += d.PSA.toString();
                csv += ",";
                csv += d.HSA.toString();
                csv += "\n";
            });

            filename += '.csv';

            let hiddenElement = document.createElement('a');
            hiddenElement.href = 'data:text/csv;charset=utf-8,' + encodeURI(csv);
            hiddenElement.target = '_blank';
            hiddenElement.download = filename;
            hiddenElement.click();
        },

        currentTimeTable() {

            setInterval(() => {
                this.currentTime = (Date.now() - this.getStartTime) / 1000;
            }, 1000);

        }

      
    }
}
</script>

<style scoped>
.current {
    border: thin;
    box-shadow: 0px 0px;
    color: green
}

.h-divider {
    margin-top: 5px;
    margin-bottom: 5px;
    height: 1px;
    width: 100%;
    border-top: 1px solid gray;
}

.v-divider {
    margin-left: 5px;
    margin-right: 5px;
    padding: 0px;
    width: 1px;
    height: 100%;
    border-right: 1px solid gray;
}

.modal-show {
    display: block;
}
</style>