<template>
    <div class="row" id="R134a-Chart">
        <h2 id="R134a-Chart-head">R134a p-h diagram</h2>
        <div class="col-12" id="R134aImageDiv">
            <!-- <img src="/images/ET-411C-Compression-refrigeration-system-gunt-206-foto_totale.jpg" alt=""> -->
            <img id="R134aImage" src="/images/R134a.png" alt="R134a p-H chart" >
            <!-- <CanvasDrawing /> -->
        </div>
        <toolbar parentCanvasID="R134aChart-div" parentComponentName="R134aChart" parentDivID="R134aChart-div"
            :showDownload='false' :showPopupHelp="true" :showOptions="false" id="R134aChart">
            <template v-slot:popup id='R134aChart-popup'>
                <div class='row mb-2'>
                    <div class='col'>
                        <h3> R134a p-h diagram </h3>
                        <p> Read the legend in the R134a p-h diagram to understand what the different colored lines mean.</p>

                    </div>
                </div>
            </template>
        </toolbar>
    </div>
</template>

<script>
import Toolbar from './elements/Toolbar.vue';
// import CanvasDrawing from "./CanvasDrawing.vue"
export default {

    name: "R134aChart",

    components: {
        // CanvasDrawing,
        Toolbar,
    },
    computed: {

    },
    watch: {

    },
    created() {

    },
    mounted() {

    },
};

</script>


<style>
#R134aImageDiv {
    display: inline;

}

#R134aImageDiv img {
    width: auto;
    height: auto;
    max-width: 100%;
    max-height: 100%;

}

/* #CanvasDrawing{
    width: auto;
    height: auto;
    max-width: 100%;
    max-height: 100%;
    position: relative;
    display: inline-block;
} */
</style>
