<template>
    <div id="MeasuredDataInputandFeedback" class="border-dashed">
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
                            </tr>
                        </thead>
                        <tbody class="table-group-divider">
                            <tr>
                                <!-- <td><input type="number" name="" class="inputnumber" id="time" placeholder="0"
                                        value="30" @change="inputValueOnChange()"></td>
                                <td><input type="number" name="" class="inputnumber" id="T1" placeholder="0" value="15"
                                        @change="inputValueOnChange()">
                                </td>
                                <td><input type="number" name="" class="inputnumber" id="T2" placeholder="0" value="68"
                                        @change="inputValueOnChange()">
                                </td>
                                <td><input type="number" name="" class="inputnumber" id="T3" placeholder="0" value="43"
                                        @change="inputValueOnChange()">
                                </td>
                                <td><input type="number" name="" class="inputnumber" id="T4" placeholder="0"
                                        value="3.65" @change="inputValueOnChange()"></td>
                                <td><input type="number" name="" class="inputnumber" id="T5" placeholder="0"
                                        value="2.82" @change="inputValueOnChange()"></td> -->

                                <td><input type="number" name="" class="inputnumber" id="time" placeholder="0"
                                        @change="inputValueOnChange()"></td>
                                <td><input type="number" name="" class="inputnumber" id="T1" placeholder="0"
                                        @change="inputValueOnChange()"></td>
                                <td><input type="number" name="" class="inputnumber" id="T2" placeholder="0"
                                        @change="inputValueOnChange()"></td>
                                <td><input type="number" name="" class="inputnumber" id="T3" placeholder="0"
                                        @change="inputValueOnChange()"></td>
                                <td><input type="number" name="" class="inputnumber" id="T4" placeholder="0"
                                        @change="inputValueOnChange()"></td>
                                <td><input type="number" name="" class="inputnumber" id="T5" placeholder="0"
                                        @change="inputValueOnChange()"></td>

                            </tr>
                        </tbody>
                        <thead class="table-light">
                            <tr>
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

                                <td><input type="number" name="" class="inputnumber" id="P1" placeholder="0"
                                        @change="inputValueOnChange()"></td>
                                <td><input type="number" name="" class="inputnumber" id="P2" placeholder="0"
                                        @change="inputValueOnChange()"></td>
                                <td><input type="number" name="" class="inputnumber" id="P3" placeholder="0"
                                        @change="inputValueOnChange()"></td>
                                <td><input type="number" name="" class="inputnumber" id="F" placeholder="0"
                                        @change="inputValueOnChange()"></td>
                                <td><input type="number" name="" class="inputnumber" id="E" placeholder="0"
                                        @change="inputValueOnChange()"></td>
                                <td><input type="number" name="" class="inputnumber" id="ASP" placeholder="0"
                                        @change="inputValueOnChange()"></td>


                                <!-- <td><input type="number" name="" class="inputnumber" id="P1" placeholder="0"
                                        value="2.41" @change="inputValueOnChange()"></td>
                                <td><input type="number" name="" class="inputnumber" id="P2" placeholder="0"
                                        value="10.18" @change="inputValueOnChange()"></td>
                                <td><input type="number" name="" class="inputnumber" id="P3" placeholder="0"
                                        value="10.5" @change="inputValueOnChange()"></td>
                                <td><input type="number" name="" class="inputnumber" id="F" placeholder="0" value="4.43"
                                        @change="inputValueOnChange()"></td>
                                <td><input type="number" name="" class="inputnumber" id="E" placeholder="0" value="200"
                                        @change="inputValueOnChange()">
                                </td>
                                <td><input type="number" name="" class="inputnumber" id="ASP" placeholder="0" value="1"
                                        @change="inputValueOnChange()">
                                </td> -->
                            </tr>
                        </tbody>
                    </table>
                </div>
                <div class="row">
                    <div class="col-3">

                    </div>
                    <div class="col-3">
                        <button id="measureddata_ConfirmButton" type="button" :class="confirmButtonClass"
                            @click="measuredDataFeedback(); toggleMeasuredData()">Confirm</button>
                    </div>
                    <div class="col-3">
                        <button id="measuredData_ResetButton" type="button" class="btn btn-primary"
                            @click="reset()">Reset</button>
                    </div>
                    <div class="col-3">
                        <!-- <button @click="GetDataformInput()">test input data</button> -->
                    </div>
                </div>

            </div>
            <div id="MeasuredDataFeedback_div" class="col-lg-6">
                <h2>Measured Data Feedback</h2>
                <div v-if="this.errorMessage" :class="feedbackMessageClass" role="alert">
                    {{ this.errorMessage }}
                </div>
            </div>
        </div>
        <toolbar parentCanvasID="MeasuredDataInputandFeedback-div" parentComponentName="MeasuredDataInputandFeedback"
            parentDivID="MeasuredDataInputandFeedback-div" :showDownload='false' :showPopupHelp="true"
            :showOptions="false" id="MeasuredDataInputandFeedback">
            <template v-slot:popup id='MeasuredDataInputandFeedback-popup'>
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
                        <p><b>Measured Data Feedback:</b> A feedback will be displayed after the user submits input data
                            in the “Measured Data Input” component. </p>
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

import { checkParametersSystemCalculation } from '../modules/parameterValidation'

export default {
    name: "MeasuredDataFeedback",
    props: {

    },
    components: {
        Toolbar,

    },
    data() {
        return {
            confirmButtonClass: "btn btn-primary",
            errorMessage: '',
            feedbackMessageClass: ""
        }
    },
    mounted() {

    },
    watch: {
        GetMeasuerdDataConfirmed(newValue) {
            if (newValue == 1) {
                this.confirmButtonClass = "btn btn-success";
            } else {
                this.confirmButtonClass = "btn btn-primary";
                // console.log("input value has been changed");
            }
        },
        errorMessage(newValue) {
            if (newValue == "All parameters are valid!") {
                this.feedbackMessageClass = "alert alert-success";
                this.SetFeedbackMessageClass(this.feedbackMessageClass);
            } else {
                this.feedbackMessageClass = "alert alert-danger";
                this.SetFeedbackMessageClass(this.feedbackMessageClass);
            }
        }

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
            'SetMeasuerdDataConfirmed',
            'SetErrorMessage',
            'SetFeedbackMessageClass',

        ]),

        toggleMeasuredData() {
            const newState = true; // Example: Set the boolean value dynamically
            this.$emit('updateMeasuredData', newState); // Emit event with the new boolean state
        },

        inputValueOnChange() {
            this.SetMeasuerdDataConfirmed(0);
            // console.log(this.GetMeasuerdDataConfirmed);
        },

        validateData(parameters) {
            try {
                checkParametersSystemCalculation(parameters);
                this.errorMessage = "All parameters are valid!";
                this.SetErrorMessage(this.errorMessage);

            } catch (error) {
                this.errorMessage = error.message;
                this.SetErrorMessage(this.errorMessage);

            }
        },

        measuredDataFeedback() {
            var MeasuredInput;
            this.GetDataformInput();
            MeasuredInput = {
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
            };
            this.validateData(MeasuredInput);
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
            // this.updateFlag = false;
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