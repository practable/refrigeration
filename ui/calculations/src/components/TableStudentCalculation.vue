<template>
    <div id="studentCalculationDiv" class="border-dashed">
        <!-- <div class="row">
            <div class="col-lg-6"> -->
        <h2 id="studentCalculationDivHead"> Calculation Results (Student) </h2>
        <div id="studentCalculationTableDiv" class="table-responsive">
            <table id="studentCalculationTable" class="table">
                <thead id="studentCalculationTableHead" class="table-light">
                    <tr class="table-dark">
                        <th colspan="5">Enthalpy Value</th>
                    </tr>
                    <tr>

                        <th>H1(KJ/Kg)</th>
                        <th>H2(KJ/Kg)</th>
                        <th>H3(KJ/Kg)</th>
                        <th>H4(KJ/Kg)</th>
                        <!-- <th>H5(KJ/Kg)</th> -->

                    </tr>
                </thead>
                <tbody id="studentCalculationTableBody" class="table-group-bordered">
                    <tr>
                        <!-- <td><input type="text" name="" class="inputnumber" id="H1" placeholder="0" v-model="numberValue"
                                @input="validateNumberInput"  @keypress="onlyAllowNumbers"></td> -->
                        <!-- <td><input type="number" name="" class="inputnumber" id="H1" placeholder="0" value="400" @change="inputValueOnchange()"></td>
                        <td><input type="number" name="" class="inputnumber" id="H2" placeholder="0" value="400" @change="inputValueOnchange()"></td>
                        <td><input type="number" name="" class="inputnumber" id="H3" placeholder="0" value="200" @change="inputValueOnchange()"></td>
                        <td><input type="number" name="" class="inputnumber" id="H4" placeholder="0" value="200" @change="inputValueOnchange()"></td> -->
                        <!-- <td><input type="number" name="" class="inputnumber" id="H5" placeholder="0" value="400" @change="inputValueOnchange()"></td> -->
                        
                        <td><input type="number" name="" class="inputnumber" id="H1" placeholder="0" @change="inputValueOnchange()"></td>
                        <td><input type="number" name="" class="inputnumber" id="H2" placeholder="0" @change="inputValueOnchange()"></td>
                        <td><input type="number" name="" class="inputnumber" id="H3" placeholder="0" @change="inputValueOnchange()"></td>
                        <td><input type="number" name="" class="inputnumber" id="H4" placeholder="0" @change="inputValueOnchange()"></td>
                        <!-- <td><input type="number" name="" class="inputnumber" id="H5" placeholder="0" @change="inputValueOnchange()"></td> -->
                    </tr>
                </tbody>
            </table>
            <table id="studentCalculationTable" class="table">
                <thead id="studentCalculationTableHead" class="table-light">
                    <tr class="table-dark">
                        <th colspan="3">Parameters Calculation</th>
                    </tr>
                    <tr>
                        <th>Mass flowrate, m(Kg/s)</th>
                        <th>Refrigeration capacity, QL(W)</th>
                        <th>Condensation capacity, QH(W)</th>
                        <!-- <th>Compressor work</th>
                            <th>Coefficient of performance </th>
                            <th>Compressor compression ratio</th> -->
                    </tr>
                </thead>
                <tbody id="studentCalculationTableBody" class="table-group-bordered">
                    <tr>

                        <td><input type="number" name="" class="inputnumber" id="m" placeholder="0" @change="inputValueOnchange()"></td>
                        <td><input type="number" name="" class="inputnumber" id="QL" placeholder="0" @change="inputValueOnchange()"></td>
                        <td><input type="number" name="" class="inputnumber" id="QH" placeholder="0" @change="inputValueOnchange()"></td>

                        <!-- <td><input type="number" name="" class="inputnumber" id="m" placeholder="0" value="0.01" @change="inputValueOnchange()"></td>
                        <td><input type="number" name="" class="inputnumber" id="QL" placeholder="0" value="60" @change="inputValueOnchange()"></td>
                        <td><input type="number" name="" class="inputnumber" id="QH" placeholder="0" value="50" @change="inputValueOnchange()"></td> -->


                    </tr>
                </tbody>
                <thead id="studentCalculationTableHead" class="table-light">
                    <tr>
                        <th>Compressor work, W(W)</th>
                        <th>Coefficient of performance, COP</th>
                        <!-- <th>Compressor compression ratio η</th> -->
                    </tr>
                </thead>
                <tbody id="studentCalculationTableBody" class="table-group-bordered">
                    <tr>
                        <td><input type="number" name="" class="inputnumber" id="W" placeholder="0" @change="inputValueOnchange()"></td>
                        <td><input type="number" name="" class="inputnumber" id="COP" placeholder="0" @change="inputValueOnchange()"></td>
                        <!-- <td><input type="number" name="" class="inputnumber" id="n" placeholder="0" @change="inputValueOnchange()"></td> -->

                        <!-- <td><input type="number" name="" class="inputnumber" id="W" placeholder="0" value="250" @change="inputValueOnchange()"></td>
                        <td><input type="number" name="" class="inputnumber" id="COP" placeholder="0" value="5" @change="inputValueOnchange()"></td> -->
                        <!-- <td><input type="number" name="" class="inputnumber" id="n" placeholder="0" value="5" @change="inputValueOnchange()"></td> -->

                    </tr>
                </tbody>
            </table>

        </div>
        <div id="studentCalculationsubmitButtonDiv" class="row">
            <div class="col-3">

            </div>
            <div class="col-3">
                <button id="studentCalculationConfirm_button" :class="confirmButtionClass" @click="GetDataformInput(); toggleCalculatedData()">Confirm</button>
            </div>
            <div class="col-3">
                <button id="studentCalculationReset_button" class="btn btn-primary" @click="reset">Reset</button>
            </div>
        </div>
        <div class="col-3">

        </div>
        <toolbar parentCanvasID="studentCalculation-div" parentComponentName="studentCalculationDiv" parentDivID="studentCalculation-div"
            :showDownload='false' :showPopupHelp="true" :showOptions="false" id="studentCalculation-help">
            <template v-slot:popup id='studentCalculation-popup'>
                <div class='row mb-2'>
                    <div class='col'>
                        <h3> Calculation results (Students) </h3>
                        <p> the user needs to complete the calculation and input the results in the form. After
                            that, click the “Confirm” button to save data for submitting data to the server. The “Reset
                            button” is used to reset the value in the input form. The nomenclature of parameters and
                            units are included in Table. </p>
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
                                    <td>H1</td>
                                    <td>Enthalpy of saturated vapor</td>
                                    <td>kJ/kg</td>
                                </tr>
                                <tr>
                                    <th scope="row">2</th>
                                    <td>H2</td>
                                    <td>Enthalpy of superheated vapor</td>
                                    <td>kJ/kg</td>
                                </tr>
                                <tr>
                                    <th scope="row">3</th>
                                    <td>H3</td>
                                    <td>Enthalpy of saturated liquid</td>
                                    <td>kJ/kg</td>
                                </tr>
                                <tr>
                                    <th scope="row">4</th>
                                    <td>H4</td>
                                    <td>Enthalpy of liquid and vapor at T4</td>
                                    <td>kJ/kg</td>
                                </tr>
                                <!-- <tr>
                                    <th scope="row">5</th>
                                    <td>H5</td>
                                    <td>Enthalpy of liquid and vapor at T5</td>
                                    <td>kJ/kg</td>
                                </tr> -->
                                <tr>
                                    <th scope="row">5</th>
                                    <td>m</td>
                                    <td>Mass flowrate</td>
                                    <td>kg/s</td>
                                </tr>
                                <tr>
                                    <th scope="row">6</th>
                                    <td>QL</td>
                                    <td>Refrigeration capacity</td>
                                    <td>W</td>
                                </tr>
                                <tr>
                                    <th scope="row">7</th>
                                    <td>QH</td>
                                    <td>Condensation capacity</td>
                                    <td>W</td>
                                </tr>
                                <tr>
                                    <th scope="row">8</th>
                                    <td>W</td>
                                    <td>Compressor work</td>
                                    <td>W</td>
                                </tr>
                                <tr>
                                    <th scope="row">9</th>
                                    <td>COP</td>
                                    <td>Coefficient of performance</td>
                                    <td>-</td>
                                </tr>
                                <!-- <tr>
                                    <th scope="row">7</th>
                                    <td>n</td>
                                    <td>Compressor compression ratio</td>
                                    <td>-</td>
                                </tr> -->
                            </tbody>
                        </table>
                    </div>
                </div>
            </template>
        </toolbar>
    </div>


    <!-- </div>
    </div> -->


</template>

<script>
import { mapGetters, mapActions } from 'vuex';
import Toolbar from './elements/Toolbar.vue';

export default {
    name: "TableStudentCalculation",
    props: {

    },
    components: {
        Toolbar,

    },
    data() {
        return {
            // numberValue: "250",
            confirmButtionClass : "btn btn-primary",

        };
    },
    mounted() {


    },
    watch:{
        // watch on GetCalcuDataConfirmed to change the color to corresponding state
        GetCalcuDataConfirmed(newValue){
            if(newValue == 1){
                this.confirmButtionClass = "btn btn-success"
            }else {
                this.confirmButtionClass = "btn btn-primary"
            }
        }
        
    },
    computed: {
        ...mapGetters([
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
            'GetCalcuDataConfirmed',
        ])
    },

    methods: {
        ...mapActions([
            'SetH1',
            'SetH2',
            'SetH3',
            'SetH4',
            'SetH5',
            'Setm',
            'SetQL',
            'SetQH',
            'SetW',
            'SetCOP',
            'Setn',
            'SetCalcuDataConfirmed',
        ]),


        //  // validate number input: Firefox allows non-numeric characters in <input type="number"> fields, even though it prevents non-numeric values from being submitted. To fully prevent users from entering letters, you can use the @keypress event to block non-numeric characters before they are typed.
        // change <input type="number"> to <input type="text">  add <v-model="numberValue" @input="validateNumberInput"  @keypress="onlyAllowNumbers"> as well to every input box

        // validateNumberInput(event) {
        //     let value = event.target.value;

        //     // Allow only numbers and a single decimal point
        //     value = value.replace(/[^0-9.]/g, '');

        //     // Ensure only one decimal point is allowed
        //     const dotCount = (value.match(/\./g) || []).length;
        //     if (dotCount > 1) {
        //         value = value.slice(0, value.lastIndexOf('.')); // Remove extra decimal
        //     }

        //     // Update the Vue model
        //     this.numberValue = value;
        // },


        // onlyAllowNumbers(event) {
        //     const char = event.key;

        //     // Allow numbers and a single decimal point
        //     if (!/[\d.]/.test(char)) {
        //         event.preventDefault();
        //     }

        //     // Prevent multiple decimal points
        //     if (char === '.' && this.numberValue.includes('.')) {
        //         event.preventDefault();
        //     }
        // },


        inputValueOnchange(){
            this.SetCalcuDataConfirmed(0);
            // console.log(this. GetCalcuDataConfirmed)

        },



        toggleCalculatedData() {
            const newState = true; // Example: Set the boolean value dynamically
            this.$emit('updateCalculatedData', newState); // Emit event with the new boolean state
        },

        GetDataformInput() {
            this.SetH1(document.getElementById('H1').value);
            this.SetH2(document.getElementById('H2').value);
            this.SetH3(document.getElementById('H3').value);
            this.SetH4(document.getElementById('H4').value);
            // this.SetH5(document.getElementById('H5').value);
            this.Setm(document.getElementById('m').value);
            this.SetQL(document.getElementById('QL').value);
            this.SetQH(document.getElementById('QH').value);
            this.SetW(document.getElementById('W').value);
            this.SetCOP(document.getElementById('COP').value);
            // this.Setn(document.getElementById('n').value);
            this.SetCalcuDataConfirmed(1);
            // console.log(this.GetH1, this.GetH2,this.GetH3,this.GetH4,this.GetH5,
            // this.Getm,this.GetQL,this.GetQH,this.GetW,this.GetCOP,this.Getn);
        },

        ClearformInput() {
            document.getElementById('H1').value = 0;
            document.getElementById('H2').value = 0;
            document.getElementById('H3').value = 0;
            document.getElementById('H4').value = 0;
            document.getElementById('H5').value = 0;
            document.getElementById('m').value = 0;
            document.getElementById('QL').value = 0;
            document.getElementById('QH').value = 0;
            document.getElementById('W').value = 0;
            document.getElementById('COP').value = 0;
            document.getElementById('n').value = 0;
        },

        //clear and reset the data in the input form and chart
        reset() {
            this.ClearformInput();
            this.GetDataformInput();
            this.SetCalcuDataConfirmed(0);

        },


    },

};
</script>

<style></style>