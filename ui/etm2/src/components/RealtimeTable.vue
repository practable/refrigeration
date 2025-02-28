<template>
    <table id="realTimeTable" class="table table-bordered" style=" font-size:small;">
        <thead>
            <tr id="realTimeTable-thead">
                <th scope="col">T1(°C)</th>
                <th scope="col">T2(°C)</th>
                <th scope="col">T3(°C)</th>
                <th scope="col">T4(°C)</th>
                <th scope="col">T5(°C)</th>
                <th scope="col">P1(bar)</th>
                <th scope="col">P2(bar)</th>
                <!-- <th scope="col">P3(bar)</th>
                <th scope="col">F(L/h)</th>
                <th scope="col">E(W)</th>
                <th scope="col">TSA(°C)</th>
                <th scope="col">PSA(bar)</th>
                <th scope="col">HSA(%rh)</th> -->
            </tr>
        </thead>
        <tbody>
            <tr id="realTimeTable-tboday">
                <td>{{ T1 }}</td>
                <td>{{ T2 }}</td>
                <td>{{ T3 }}</td>
                <td>{{ T4 }}</td>
                <td>{{ T5 }}</td>
                <td>{{ P1 }}</td>
                <td>{{ P2 }}</td>
                <!-- <td>{{ P3 }}</td>
                <td>{{ F }}</td>
                <td>{{ E }}</td>
                <td>{{ TSA }}</td>
                <td>{{ PSA }}</td>
                <td>{{ HSA }}</td> -->
            </tr>
        </tbody>
        <thead>
            <tr id="realTimeTable-thead">
                <!-- <th scope="col">T1(°C)</th>
                <th scope="col">T2(°C)</th>
                <th scope="col">T3(°C)</th>
                <th scope="col">T4(°C)</th>
                <th scope="col">T5(°C)</th>
                <th scope="col">P1(bar)</th>
                <th scope="col">P2(bar)</th> -->
                <th scope="col">P3(bar)</th>
                <th scope="col">F(L/h)</th>
                <th scope="col">E(W)</th>
                <th scope="col">TSA(°C)</th>
                <th scope="col">PSA(mBar)</th>
                <th scope="col">HSA(%rh)</th>
                <th></th>
            </tr>
        </thead>
        <tbody>
            <tr id="realTimeTable-tboday">
                <!-- <td>{{ T1 }}</td>
                <td>{{ T2 }}</td>
                <td>{{ T3 }}</td>
                <td>{{ T4 }}</td>
                <td>{{ T5 }}</td>
                <td>{{ P1 }}</td>
                <td>{{ P2 }}</td> -->
                <td>{{ P3 }}</td>
                <td>{{ F }}</td>
                <td>{{ E }}</td>
                <td>{{ TSA }}</td>
                <td>{{ PSA }}</td>
                <td>{{ HSA }}</td>
                <td></td>
            </tr>
        </tbody>
    </table>

</template>

<script>
import { mapGetters } from 'vuex';


export default {
    name: "realtimetable",

    data() {
        return {


        }
    },
    mounted() {
       
    },
    watch() {
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
            
        ]),

        websockMsg() {
            // return websocketstore.getters.GETreceivedData;
            return this.$store.getters.GETreceivedData;
        },
        T1(){
            return this.GetCurrentTS1
        },
        T2(){
            return this.GetCurrentTS2
        },
        T3(){
            return this.GetCurrentTS3
        },
        T4(){
            return this.GetCurrentTS4
        },
        T5(){
            return this.GetCurrentTS5
        },
        P1(){
            return this.GetCurrentPS1
        },
        P2(){
            return this.GetCurrentPS2
        },
        P3(){
            return this.GetCurrentPS3
        },
        F(){
            return this.GetCurrentFlow
        },
        E(){
            return this.GetCurrentPower
        },
        TSA(){
            return this.GetCurrentTSA
        },
        PSA(){
            return this.GetCurrentPSA
        },
        HSA(){
            return this.GetCurrentHSA
        },
    },

    methods: {
     
      
    }


}
</script>