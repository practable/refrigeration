<template>
    <div id="P&ID">
        <!-- test svg dispaly  -->
        <PID_SVG style="background-color: white; width: 100%;" id="Schematic Figure" alt="Experiment Schematic Figure"/>
    </div>
    <!-- <div>
        <InteractiveChart/> auto; height: auto; max-width: 100%; max-height:
    </div> -->

    
</template>

<script>
//svgfiller has error for this project, and maybe because of the version problem. https://github.com/biigpongsatorn/vue-svg-filler/issues/36
// import Svgfiller from "vue-svg-filler"

import PID_SVG from "./PID_SVG.vue"
// import InteractiveChart from "./interactiveChart.vue"


export default {
    name: "PID",
    components: {
        // Svgfiller,
        PID_SVG,
        // InteractiveChart,
        
},
    data() {
        return {
            
    }
},
    methods: {
    
},
}


</script>
