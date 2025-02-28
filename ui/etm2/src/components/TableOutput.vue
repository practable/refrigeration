<template>
    <div id="TableOutput-div">
        <button id="recordTableUpdate" class="button-sm button-secondary" @click="updateTable()"> Update Table </button>
        <div class='container-fluid m-2 background-white border rounded table'>
            <div class="row ">
                <!-- <input type="text" id="search" v-on:keyup="search" v-model="search_field" placeholder="Search the table..."> -->
                <table>
                    <thead class='table-head'>
                        <tr class='background-primary text-white'>
                            <!-- <th scope="col">ID</th> -->
                            <th scope="col">RecordingTime(s)</th>
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
                            <th scope="col">PSA(hPa)</th>
                            <th scope="col">HSA(%rh)</th>
                        </tr>
                    </thead>
                    <!-- <tr v-for="row in tableData" :id="row.id" :key="row.id"
                    v-bind:class="[row.id == selected_row_id ? 'selected-row' : '']" @click="changeSelected(row.id)">
                    <td>{{ row.t.toFixed(2) }}</td>
                    <td>{{ row.theta.toFixed(2) }}</td>
                    <td>{{ row.omega.toFixed(2) }}</td>
                </tr> -->
                    <tbody>
                        <tr v-for="row in tableData" :id="row.id" :key="row.id"
                            v-bind:class="[row.id == selected_row_id ? 'selected-row' : '']"
                            @click="changeSelected(row.id)">
                            <!-- <td>{{ row.id + 1 }}</td> -->
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
                            <!-- <td>{{ T3 }}</td>
                    <td>{{ T4 }}</td>
                    <td>{{ T5 }}</td>
                    <td>{{ P1 }}</td>
                    <td>{{ P2 }}</td>
                    <td>{{ P3 }}</td>
                    <td>{{ F }}</td>
                    <td>{{ E }}</td> -->
                        </tr>
                    </tbody>
                </table>

            </div>

        </div>
        <toolbar parentCanvasID="TableOutput-div" parentComponentName="TableOutput" parentDivID="TableOutput-div"
            :showDownload='false' :showPopupHelp="true" :showOptions="false" id="TableOutput_help">
            <template v-slot:popup id='TableOutput-popup'>
                <div class='row mb-2'>
                    <div class='col'>
                        <h3> Data Recorder Table </h3>
                        <p> Click “Update Table” to refresh data from the Data Recorder.</p>
                    </div>
                </div>
            </template>
        </toolbar>
    </div>
</template>

<script>

import { mapGetters } from 'vuex';
import Toolbar from './elements/Toolbar.vue';


export default {
    name: 'TableOutput',
    components: {

        Toolbar,

    },
    props: [
        'selected_point'
    ],
    data() {
        return {
            tableData: [],
            searchData: [],
            search_field: "",
            selected_row_id: "0",
        }
    },
    methods: {
        updateTable() {

            this.tableData = [...this.getData];     //get a clone of the data, not set tableData to the getData getter
            // console.log(this.tableData);
        },
        search() {
            if (this.search_field == "") {
                this.searchData = Array.from(this.tableData);
            } else {
                this.searchData = [];
                let d;
                let string_data_row;
                // Loop through all tableData, create a string of all elements in the table row, search if the current search_field text is contained and set hidden appropriately.
                for (let i = 0; i < this.tableData.length; i++) {
                    d = this.tableData[i];
                    string_data_row = d.id + d.mass + d.name + d.reclat + d.reclong + d.recclass;

                    if (string_data_row.toUpperCase().indexOf(this.search_field.toUpperCase()) > -1) {
                        this.searchData.push(d);
                    } else {
                        //tr[i].style.display = "none";
                    }

                }
            }

        },
        changeSelected(id) {
            this.selected_row_id = id;
            //the selected row will be covered by the sticky table heading, so scroll to the element below
            let scroll_id = id - 1;
            var elmnt = document.getElementById(scroll_id);
            elmnt.scrollIntoView();
        }
    },
    computed: {
        ...mapGetters([
            'getIsRecording',
            'getData',
        ])
    },
    watch: {
        //to clear data table on reset.
        getData(data) {
            if (data.length == 0) {
                this.updateTable();
            }
        },
        //to update table once recording complete
        getIsRecording(now, prev) {
            if (!now && prev) {
                this.updateTable();
            }
        },
        selected_point(id) {
            this.changeSelected(id);
        }
    },
    mounted() {
        this.updateTable();
    },
    created() {

    }
}
</script>

<style scoped>
.selected-row {
    background-color: red;
    color: white;
}
</style>
