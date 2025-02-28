<template>
    <div id="dataCompare">
        <div class="row">
            <div id="phChartDiv" class="col-lg-6">
                <div class="border-dashed">
                    <h2 id="phChartDivHead"> p-h Chart </h2>
                    <!-- <h2> p-h Chart for Enthalpy Value (CoolProp library)</h2> -->
                    <!-- <p>The system data calculation is from CoolProp library: </p>  -->
                    <!-- <a href="http://www.coolprop.org/general_information.html" target="_blank">The automated data
                        calculation is from CoolProp library</a>
                    <br>
                    <a href="http://www.coolprop.org/fluid_properties/fluids/R134a.html" target="_blank">R134a
                        properties from CoolProp</a> -->
                    <!-- <p>R134a properties from CoolProp: http://www.coolprop.org/fluid_properties/fluids/R134a.html</p> -->

                    <!-- <div class="row" id="buttongroup">
                        <div class="col-lg-3">
                            <button type="button" class="col-12 btn btn-primary" @click="pencil()">Pencil
                            </button>
                        </div>
                        <div class="col-lg-3">
                            <button type="button" class="col-12 btn btn-primary" @click="straightLineDrawing()">Straight
                                line </button>
                        </div>
                        <div class="col-lg-3">
                            <button type="button" class="col-12 btn btn-primary" @click="clearLine()">Clear</button>
                        </div>
                    </div> -->
                    <br>
                    <br>
                    <div id="phChart_coolprop_div" class="image-container">
                        <!-- <img :src="GetImgData" alt=""> -->
                        <div id="phChart_coolprop" v-if="Getimg_data">
                            <img :src="'data:image/png;base64,' + Getimg_data" alt="Image">
                        </div>
                        <div id="phChart_coolprop_div_errorMessage" v-else>
                            <div :class="this.GetFeedbackMessageClass">
                                <!-- <strong>Info!</strong> Please submit your data to get the results. -->
                                {{ this.GetErrorMessage }}
                            </div>
                        </div>
                        <!-- <u v-else> Please submit your data to get the results </u> -->
                    </div>
                    <toolbar parentCanvasID="phChart-div" parentComponentName="phChartDiv" parentDivID="phChart-div"
                        :showDownload='false' :showPopupHelp="true" :showOptions="false" id="phChart_help">
                        <template v-slot:popup id='phChart-popup'>
                            <div class='row mb-2'>
                                <div class='col'>
                                    <h3> P-h Chart for Enthalpy Value (CoolProp Library) </h3>
                                    <p> After submitting data to the server, a p-h chart for enthalpy values plotted by
                                        the server will be posted back and displayed in this component. The results of
                                        this chart and calculation are based on the CoolProp library, the link to
                                        CoolProp is <u>http://www.coolprop.org/general_information.html</u> , and the
                                        link to
                                        R134a properties from CoolProp is
                                        <u>http://www.coolprop.org/fluid_properties/fluids/R134a.html</u>.
                                    </p>
                                </div>
                            </div>
                        </template>
                    </toolbar>
                </div>
            </div>
            <div id="CalcComparsionDiv" class="col-lg-6">
                <div class="border-dashed">
                    <h2 id="CalcComparsionDivHead"> Calculation Comparsion </h2>
                    <!-- <h2> Automated Calculation Comparsion (CoolProp and Student) </h2> -->
                    <div id="CalcComparsionTableDiv" class="table-responsive">
                        <table id="CalcComparsionTable" class="table">
                            <thead id="CalcComparsionTableDivHead" class="table-light">
                                <tr class="table-dark">
                                    <th colspan="5">Enthalpy Value</th>
                                </tr>
                                <tr>

                                    <th>H1 Difference (%)</th>
                                    <th>H2 Difference (%)</th>
                                    <th>H3 Difference (%)</th>
                                    <th>H4 Difference (%)</th>
                                    <!-- <th>H5(KJ/Kg)</th> -->

                                </tr>
                            </thead>
                            <tbody id="CalcComparsionTableBody" class="table-group-border">
                                <tr>
                                    <td>{{ this.GetH1_Dev }}</td>
                                    <td>{{ this.GetH2_Dev }}</td>
                                    <td>{{ this.GetH3_Dev }}</td>
                                    <td>{{ this.GetH4_Dev }}</td>
                                    <!-- <td>{{ this.GetH5_Dev }}</td> -->
                                </tr>
                            </tbody>
                        </table>
                        <table id="CalcComparsionTable" class="table">
                            <thead id="CalcComparsionTableDivHead" class="table-light">
                                <tr class="table-dark">
                                    <th colspan="3">Parameters Calculation</th>
                                </tr>
                                <tr>
                                    <th>Mass flowrate Difference (m, %)</th>
                                    <th>Refrigeration capacity Difference (QL, %)</th>
                                    <th>Condensation capacity Difference (QH, %)</th>

                                </tr>
                            </thead>
                            <tbody id="CalcComparsionTableBody" class="table-group-border">
                                <tr>

                                    <td>{{ this.Getm_Dev }}</td>
                                    <td>{{ this.GetQL_Dev }}</td>
                                    <td>{{ this.GetQH_Dev }}</td>

                                </tr>
                            </tbody>
                            <thead id="CalcComparsionTableDivHead" class="table-light">
                                <tr>
                                    <th>Compressor work Difference (W, %)</th>
                                    <th>Coefficient of performance Difference (COP, %)</th>
                                    <!-- <th>Compressor compression ratio η</th> -->
                                </tr>
                            </thead>
                            <tbody id="CalcComparsionTableDivBody" class="table-group-border">
                                <tr>
                                    <td>{{ this.GetW_Dev }}</td>
                                    <td>{{ this.GetCOP_Dev }}</td>
                                    <!-- <td>{{ this.Getn_Dev }}</td> -->

                                </tr>
                            </tbody>
                        </table>
                        <table id="CalcComparsionTable" class="table">
                            <thead id="CalcComparsionTableDivHead" class="table-light">
                                <tr class="table-dark">
                                    <th colspan="5">Saturated Vapor or Liquid Value</th>
                                </tr>
                                <tr>

                                    <th>Saturated Temperature(°C) under P1</th>
                                    <th>Saturated Temperature(°C) under P2</th>
                                    <th>Saturated Pressure(bar) under T3</th>
                                    <th>Saturated Pressure(bar) under T4</th>
                                </tr>
                            </thead>
                            <tbody id="CalcComparsionTableDivBody" class="table-group-border">
                                <tr>
                                    <td>{{ this.GetSaturT_P1 }}</td>
                                    <td>{{ this.GetSaturT_P2 }}</td>
                                    <td>{{ this.GetSaturP_T3 }}</td>
                                    <td>{{ this.GetSaturP_T5 }}</td>
                                    <!-- <td>{{ (this.GetSaturT_P1).toFixed(2) }}</td>
                                    <td>{{ (this.GetSaturT_P2).toFixed(2) }}</td>
                                    <td>{{ (this.GetSaturP_T3 / 100000).toFixed(2) }}</td>
                                    <td>{{ (this.GetSaturP_T5 / 100000).toFixed(2) }}</td> -->
                                </tr>
                            </tbody>
                        </table>
                        <!-- <button @click="test">{{ GetImgData }}</button> -->
                    </div>
                    <toolbar parentCanvasID="CalcComparsion-div" parentComponentName="CalcComparsionDiv"
                        parentDivID="CalcComparsion-div" :showDownload='false' :showPopupHelp="true"
                        :showOptions="false" id="CalcComparsion_help">
                        <template v-slot:popup id='CalcComparsion-popup'>
                            <div class='row mb-2'>
                                <div class='col'>
                                    <h3> Automated Calculation Comparison </h3>
                                    <p> The comparison of the user’s calculation (from the <b>Calculation results
                                            (Students)</b> component) and the calculation from the server (based on
                                        CoolProp and
                                        the <b>Measured Data Input (Students)</b> component) will be displayed in this
                                        component. So that users can learn the deviation percentage between their
                                        calculations and CoolProp calculations and consider how to improve the
                                        calculation. </p>
                                </div>
                            </div>
                        </template>
                    </toolbar>
                </div>
            </div>
        </div>

    </div>


</template>

<script>
import { mapGetters } from 'vuex';
import Toolbar from './elements/Toolbar.vue';

export default {
    name: "DataCompare",
    props: {

    },
    components: {
        Toolbar,

    },
    data() {
        return {
            // getImgData: null,
            feedbackMessageClass: "",
        };
    },
    mounted() {


    },

    computed: {
        ...mapGetters([
            //get deviation data from the store 
            'GetH1_Dev',
            'GetH2_Dev',
            'GetH3_Dev',
            'GetH4_Dev',
            'GetH5_Dev',
            'Getm_Dev',
            'GetQL_Dev',
            'GetQH_Dev',
            'GetW_Dev',
            'GetCOP_Dev',
            'Getn_Dev',
            'GetSaturT_P1',
            'GetSaturT_P2',
            'GetSaturP_T3',
            'GetSaturP_T5',
            //get img_data from the store
            'Getimg_data',
            'GetErrorMessage',
            'GetFeedbackMessageClass',
        ]),

        // GetImgData() {
        //     if (this.Getimg_data != null) {
        //         return "data:image/png;base64," + this.Getimg_data
        //     }
        //     else {
        //         // return "/practable-icon.png"
        //         return "./images/practable-icon.png"
        //     }
        // },
    },
    watch: {

    },
    methods: {
        // test() {
        //     console.log(this.Getimg_data);
        //     console.log(this.imgData);
        // },


    },

};
</script>

<style>
.image-container {
    display: inline-block;
    width: 100%;
    height: 100%;
    position: relative;
    min-height: 80vh;

}


.image-container img {

    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    position: absolute;

}
</style>