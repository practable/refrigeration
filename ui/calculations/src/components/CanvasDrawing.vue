<template>
    <div id="ethalpyPlot" class="border-dashed">
        <div id='canvasPlot-div'>
            <!-- <div class="row">
            <div class="col-lg-6"> -->
            <h2> p-h Chart for Enthalpy Value (Student)</h2>
            <p>Please reload the canvas if you change the browser window size.</p>
            <div id='canvasPlot'>
                <div id="canvasButtonGroup" class="btn-group" role="group"
                    aria-label="Button group with nested dropdown">

                    <button id="cancelCanvasFullScreen_button" v-if="fullScreenWatch" type="button"
                        class="btn btn-primary" @click="cancelFullScreen()">Cancel Full
                        Screen</button>
                    <button id="canvasFullScreen_button" v-else type="button" class="btn btn-primary"
                        @click="fullScreen()">Full
                        Screen</button>
                    <button id="canvasReloadCanvas_button" type="button" class="btn btn-primary"
                        @click="setupCanvas()">Reload Canvas</button>
                    <button id="canvasClearLine_button" type="button" class="btn btn-primary" @click="clearLine()">Clear
                        Canvas</button>
                    <div id="canvasLineGroup_buttonGroup" class="btn-group" role="group">
                        <button id="canvasLineGroup_buttonDropdown" type="button"
                            class="btn btn-primary dropdown-toggle" data-bs-toggle="dropdown" aria-haspopup="true"
                            aria-expanded="false">
                            Plot Line
                        </button>
                        <ul id="canvasLineGroup_buttonDropdownMenu" class="dropdown-menu">
                            <!-- <li><input id="canvasLineGroup_pencil_button" type="button" class="dropdown-item"
                                    @click="plotLineHandle(pencil)" value="Pencil" /></li>
                            <li><input id="canvasLineGroup_straightLine_button" type="button" class="dropdown-item"
                                    @click="plotLineHandle(straightLineDrawing)" value="Straight line" /></li> -->
                            <a id="canvasLineGroup_pencil_button" type="button" class="dropdown-item"
                                @click="pencil()">Pencil</a>
                            <a id="canvasLineGroup_straightLine_button" type="button" class="dropdown-item"
                                @click="straightLineDrawing()">straightLineDrawing</a>
                        </ul>
                    </div>
                    <button id="canvasEraser" class="btn btn-primary" @click="eraser()">Eraser</button>
                    <button id="canvasDownloadCanvas_button" @click="downloadCanvas()" class="btn btn-primary">Download
                        Plotting</button>
                    <span id="canvasFullScreen_info" v-if="fullScreenWatch" style="color: white;">Please reload the
                        canvas if you are using full screen. Attention: Reload Canvas will clear the plotting on the
                        current canvas. </span>
                    <span style="color: red;">{{ message }}</span>
                </div>
                <div id="phChartParent" class="image-container">
                    <canvas id="phChartCanvas" ref="canvas" @mousedown="startDrawing" @mouseup="endDrawing"
                        @mousemove="drawLine"></canvas>
                </div>
            </div>

        </div>
        <toolbar parentCanvasID="canvasPlot-div" parentComponentName="canvasPlot" parentDivID="canvasPlot-div"
            :showDownload='false' :showPopupHelp="true" :showOptions="false" id="canvasPlot_help">
            <template v-slot:popup id='canvasPlot-popup'>
                <div class='row mb-2'>
                    <div class='col'>
                        <h3> P-h Chart for Enthalpy Value </h3>
                        <p> The p-h chart diagram from R134a is included in this component, users can plot lines on the
                            chart and get the enthalpy value according to the data from the experiment. The Nomenclature
                            of the p-h diagram is included in Table. </p>
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
                                    <td>p</td>
                                    <td>Pressure (Y-axis)</td>
                                    <td>bar</td>
                                </tr>
                                <tr>
                                    <th scope="row">2</th>
                                    <td>h</td>
                                    <td>Enthalpy (X-axis)</td>
                                    <td>kJ/kg</td>
                                </tr>
                                <tr>
                                    <th scope="row">3</th>
                                    <td>T</td>
                                    <td>Temperature (blue line)</td>
                                    <td>℃</td>
                                </tr>
                                <tr>
                                    <th scope="row">4</th>
                                    <td>s</td>
                                    <td>Entropy (red line)</td>
                                    <td>kJ/(K·kg)</td>
                                </tr>
                                <tr>
                                    <th scope="row">5</th>
                                    <td>v</td>
                                    <td>Volume (green line)</td>
                                    <td>m3/kg</td>
                                </tr>
                                <tr>
                                    <th scope="row">6</th>
                                    <td>Quality</td>
                                    <td>Quality (black line)</td>
                                    <td>-</td>
                                </tr>
                            </tbody>
                        </table>
                        <p>The operation of the this component is as follows:</p>
                        <p><b>Full Screen: </b>Full screen the diagram.</p>
                        <p><b>Reload Canvas: </b>
                            Please reload the canvas if you are using full screen or changing size of
                            page.
                            <b>Attention: Reload Canvas will clear the plotting on the current canvas.</b> If you don't
                            want the current canvas to be clear, you can change the canvas back to previous size and
                            continue plotting.
                        </p>
                        <p><b>Plot Line:</b> Choose the types of lines for plotting. Choose “Pencil” to draw or make
                            notes on the canvas, and choose “Straight line” to plot a straight line on the canvas.</p>
                    </div>
                </div>
            </template>
        </toolbar>
    </div>

</template>

<script>

import Toolbar from './elements/Toolbar.vue';
import axios from 'axios';
import { DateTime } from 'luxon';
import { mapGetters } from 'vuex';
// import bootstrap from 'bootstrap';

export default {
    name: "CanvasDrawing",
    props: {

    },
    data() {
        return {
            drawing: false,
            startX: 0,
            startY: 0,
            canvas: null,
            ctx: null,
            rect: null,
            straightLine: false,
            lines: [],
            mouseX: 0,
            mouseY: 0,
            pencilPath: [],
            line: [],
            loaded: false,
            message: '',
            canvasData: {}, //save plotting and canvas 
            fullScreenWatch: false,
            erasing: false,

        };
    },
    components: {
        Toolbar,

    },
    computed: {
        ...mapGetters([
            'getLogUUID',
        ])
    },
    mounted() {
        this.setupCanvas(); // load initial canvas according to page
        window.addEventListener("scroll", this.updateCanvasRect);
        window.addEventListener("resize", this.updateCanvasRect);
        window.addEventListener("keydown", this.handleKeyPress);
        // window.removeEventListener("keydown", this.handleDKey);
    },
    beforeDestroy() {
        window.removeEventListener("scroll", this.updateCanvasRect);
        window.removeEventListener("resize", this.updateCanvasRect);
        window.addEventListener("keydown", this.handleKeyPress);
        // window.removeEventListener("keydown", this.handleDKey);
    },
    methods: {

        handleKeyPress(event) {
            if (event.key === "Escape") {
                // if (this.straightLine && this.lines.length > 0) {
                //     this.lines.pop();
                //     this.clearAndRedraw();
                // }
                if (this.fullScreenWatch) {
                    this.cancelFullScreen();
                }
            }
        },

        // handleDKey(event) {
        //     if (event.key === "d" || event.key === "D") {
        //         event.preventDefault();
        //         if (this.straightLine && this.lines.length > 0) {
        //             this.lines.pop();
        //             this.clearAndRedraw();
        //         }
        //     }
        // },

        focusToCanvas() {
            // window.location.hash = '#parent';
            // this.$refs.canvas.scrollIntoView();
            this.$refs.canvas.scrollIntoView({ behavior: "smooth", block: "center" });
        },


        fullScreen() {
            var el = document.getElementById("canvasPlot");
            if (el.requestFullscreen) {
                el.requestFullscreen();
                this.fullScreenWatch = true;
            } else if (el.webkitRequestFullscreen) { // Safari
                el.webkitRequestFullscreen();
                this.fullScreenWatch = true;
            } else if (el.mozRequestFullScreen) { // Firefox
                el.mozRequestFullScreen();
                this.fullScreenWatch = true;
            }
        },
        cancelFullScreen() {

            if (document.exitFullscreen) {
                document.exitFullscreen();
                this.fullScreenWatch = false;
                this.focusToCanvas();
            } else if (document.webkitExitFullscreen) { // Safari
                document.webkitExitFullscreen();
                this.fullScreenWatch = false;
                this.focusToCanvas();
            } else if (document.mozCancelFullScreen) { // Firefox
                document.mozCancelFullScreen();
                this.fullScreenWatch = false;
                this.focusToCanvas();
            }

        },

        // fullScreen() {
        //     var el = document.getElementById("canvasPlot");
        //     if (el.webkitRequestFullScreen) {
        //         el.webkitRequestFullScreen();
        //     }
        //     else {
        //         el.mozRequestFullScreen();
        //     };
        // },

        updateCanvasRect() {
            if (this.canvas) {
                this.rect = this.canvas.getBoundingClientRect();
            }

        },

        setupCanvas() {

            this.canvas = this.$refs.canvas;
            this.ctx = this.$refs.canvas.getContext('2d');
            // const canvas = this.$refs.canvas;
            const parent = document.getElementById('phChartParent');
            // canvas.width = parent.offsetWidth;
            // canvas.height = parent.offsetHeight;
            // this.canvas.width = this.canvas.offsetWidth;
            // this.canvas.height = this.canvas.offsetHeight;
            // this.rect = this.$refs.canvas.getBoundingClientRect();

            // Resize canvas based on parent container
            this.canvas.width = parent.clientWidth;
            this.canvas.height = parent.clientHeight;
            this.rect = this.canvas.getBoundingClientRect();

            // Compute scale factors for future coordinate adjustments
            this.scaleX = this.canvas.width / 2339;
            this.scaleY = this.canvas.height / 1653; // original image width * height = 2339*1653

            this.lines = [];
            this.pencilPath = [];
            this.drawing = false;
            this.loaded = true;
            this.message = '';

            // Redraw lines after resizing
            this.clearAndRedraw();

        },

        // drawing lines function
        startDrawing(e) {
            if (this.loaded == true) {
                this.drawing = true;
                this.startX = e.clientX - this.rect.left;
                this.startY = e.clientY - this.rect.top;
                this.drawLine(e);
                // console.log("start drawing")
            } else {
                // alert('Please load canvas before plotting')
                this.message = 'Please load canvas before plotting.';
            }

        },
        endDrawing() {
            this.drawing = false;
            // this.$refs.canvas.getContext('2d').beginPath();
            if (this.straightLine == false) {
                //console.log(this.pencilPath);
                var line = this.line;
                this.pencilPath.push({ line });
                // console.log(this.pencilPath);
                this.line = [];
                this.ctx.beginPath();

            } else {
                this.lines.push({
                    startX: this.startX,
                    startY: this.startY,
                    endX: this.mouseX,
                    endY: this.mouseY
                });

                // this.clearAndRedraw();
                this.ctx.beginPath();
                this.saveCanvasData();
            }


        },
        drawLine(e) {
            if (!this.drawing) return;
            this.mouseX = e.clientX - this.rect.left;
            this.mouseY = e.clientY - this.rect.top;

            if (this.erasing) {
                this.ctx.clearRect(this.mouseX - 5, this.mouseY - 5, 10, 10);

                // Remove erased pencil strokes from stored data
                // this.pencilPath = this.pencilPath.filter(point =>
                //     Math.abs(point.x - this.mouseX) > 5 || Math.abs(point.y - this.mouseY) > 5
                // );
                // this.pencilPath = this.pencilPath.filter(line => !this.isPointNearLine(line, this.mouseX, this.mouseY));

                // //remove the points on line 
                // this.pencilPath = this.pencilPath.map(segment => ({
                //     line: segment.line.filter(point =>
                //         Math.abs(point.x - this.mouseX) > 5 || Math.abs(point.y - this.mouseY) > 5
                //     )
                // })).filter(segment => segment.line.length > 0);

                // remove entire line object in the pencil path rather then points in it
                this.pencilPath = this.pencilPath.filter(segment =>
                    !segment.line.some(point =>
                        Math.sqrt((point.x - this.mouseX) ** 2 + (point.y - this.mouseY) ** 2) < 5
                    )
                );

                // Remove erased straight lines
                this.lines = this.lines.filter(line => !this.isPointNearLine_straight(line, this.mouseX, this.mouseY));

                this.clearAndRedraw(); // Redraw remaining strokes and lines
                return;
            }


            if (!this.straightLine) {
                // Pencil drawing logic
                this.ctx.lineWidth = 2.5;
                this.ctx.strokeStyle = '#FFAC1C';
                this.ctx.lineTo(this.mouseX, this.mouseY);
                this.ctx.stroke();
                this.ctx.beginPath();
                this.ctx.moveTo(this.mouseX, this.mouseY);
                this.line.push({ x: this.mouseX, y: this.mouseY });
            } else {
                // Straight line drawing logic
                this.ctx.lineWidth = 2.5;
                this.clearAndRedraw();
                this.ctx.strokeStyle = "darkred";
                this.ctx.lineWidth = 3;
                this.ctx.beginPath();
                this.ctx.moveTo(this.startX, this.startY);
                this.ctx.lineTo(this.mouseX, this.mouseY);
                this.ctx.stroke();
            }
        },

        //straight line filter
        isPointNearLine_straight(line, x, y) {
            const tolerance = 10;
            const dx = line.endX - line.startX;
            const dy = line.endY - line.startY;
            const lineLength = Math.sqrt(dx * dx + dy * dy);

            const dotProduct = ((x - line.startX) * dx + (y - line.startY) * dy) / lineLength;
            const closestX = line.startX + dotProduct * (dx / lineLength);
            const closestY = line.startY + dotProduct * (dy / lineLength);

            const distance = Math.sqrt(Math.pow(closestX - x, 2) + Math.pow(closestY - y, 2));
            return distance < tolerance;
        },

        //pencil line filter
        isPointNearLine_pencil(line, x, y) {
            const tolerance = 10;
            const dx = line.endX - line.startX;
            const dy = line.endY - line.startY;
            const lineLength = Math.sqrt(dx * dx + dy * dy);

            const dotProduct = ((x - line.startX) * dx + (y - line.startY) * dy) / lineLength;
            const closestX = line.startX + dotProduct * (dx / lineLength);
            const closestY = line.startY + dotProduct * (dy / lineLength);

            const distance = Math.sqrt(Math.pow(closestX - x, 2) + Math.pow(closestY - y, 2));
            return distance < tolerance;
        },



        clearLine() {
            this.drawing = false;
            this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
            this.lines = [];
            this.pencilPath = [];
            console.log("clear");
            this.savedLines = [];
        },


        //Clear and redraw the canvas
        clearAndRedraw() {
            this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);

            // Redraw stored straight lines
            this.lines.forEach(line => {
                this.ctx.beginPath();
                this.ctx.moveTo(line.startX, line.startY);
                this.ctx.lineTo(line.endX, line.endY);
                this.ctx.strokeStyle = "darkred";
                this.ctx.lineWidth = 3;
                this.ctx.stroke();
            });

            // Redraw stored pencil strokes
            this.pencilPath.forEach(line => {
                for (let i = 1; i < line.line.length; i++) {
                    this.ctx.beginPath();
                    this.ctx.lineWidth = 2;
                    this.ctx.strokeStyle = '#FFAC1C';
                    this.ctx.moveTo(line.line[i - 1].x, line.line[i - 1].y);
                    this.ctx.lineTo(line.line[i].x, line.line[i].y);
                    this.ctx.stroke();
                };
            });
            // this.ctx.beginPath();
            // if (this.pencilPath.length > 0) {
            //     this.ctx.beginPath();
            //     this.ctx.moveTo(this.pencilPath[0].x, this.pencilPath[0].y);
            //     for (let i = 1; i < this.line.length; i++) {
            //         this.ctx.lineTo(this.pencilPath[i].x, this.pencilPath[i].y);
            //     }
            //     this.ctx.strokeStyle = '#FFAC1C';
            //     this.ctx.lineWidth = 2.5;
            //     this.ctx.stroke();
            // }
        },

        pencil() {
            this.straightLine = false;
            this.erasing = false;
        },

        straightLineDrawing() {
            this.straightLine = true;
            this.erasing = false;
        },

        eraser() {
            this.erasing = true;
            this.straightLine = false;
        },


        // SAVE CANVAS DATA
        saveCanvasData() {
            this.canvasData = {
                time: new Date().getTime(),
                canvasWidth: this.canvas.width,
                canvasHeight: this.canvas.height,
                straightLines: this.lines,
                // pencilPaths: this.pencilPath
            };
            this.postChartPlot(this.canvasData);
            // console.log("Canvas Data Saved:", JSON.stringify(this.canvasData, null, 2));
        },

        // EXPORT TO JSON
        exportCanvasData() {
            const dataStr = JSON.stringify(this.canvasData, null, 2);
            const blob = new Blob([dataStr], { type: "application/json" });
            const link = document.createElement("a");
            link.href = URL.createObjectURL(blob);
            link.download = "canvas_data.json";
            link.click();
        },

        // IMPORT FROM JSON
        // importCanvasData(jsonData) {
        //     this.canvasData = JSON.parse(jsonData);
        //     this.canvas.width = this.canvasData.canvasWidth;
        //     this.canvas.height = this.canvasData.canvasHeight;
        //     this.lines = this.canvasData.straightLines || [];
        //     this.pencilPath = this.canvasData.pencilPaths || [];
        //     this.clearAndRedraw();
        // },


        downloadCanvas() {

            // Increase for higher resolution 
            const scaleFactor = 2;

            const tempCanvas = document.createElement("canvas");
            const tempCtx = tempCanvas.getContext("2d");

            const uuid = this.getLogUUID;

            tempCanvas.width = this.canvas.width * scaleFactor;
            tempCanvas.height = this.canvas.height * scaleFactor;

            // Load the background image
            const bgImage = new Image();
            bgImage.src = './images/Chart-p-h-R134a-1.png';
            bgImage.onload = () => {
                // Scale everything for high resolution
                tempCtx.scale(scaleFactor, scaleFactor);
                tempCtx.drawImage(bgImage, 0, 0, this.canvas.width, this.canvas.height);
                tempCtx.drawImage(this.canvas, 0, 0, this.canvas.width, this.canvas.height);
                tempCtx.setTransform(1, 0, 0, 1, 0, 0);

                // Add UUID text at the bottom
                tempCtx.font = "30px Arial";
                tempCtx.fillStyle = "black";
                tempCtx.textAlign = "center";
                tempCtx.fillText(`UUID: ${uuid}`, this.canvas.width, 70);

                // Convert to image and download
                const image = tempCanvas.toDataURL("image/png", 1.0);
                const link = document.createElement("a");
                link.href = image;
                link.download = "phChart_plot.png";
                link.click();
            };
        },

        // post the phChart plot data to server
        postChartPlot(payload) {
            const path = `https://app.practable.io/ed-log-dev/analytics/enthalpy/api/v1/enthalpyChartPlot?username=${this.getLogUUID}&hardware=calculator&course=etm2`;

            // const path = 'http://127.0.0.1:5000/enthalpyChartPlot?username=test&hardware=fridge&course=fridge';
            // const path = 'http://127.0.0.1:5000/feedback';
            axios.post(path, payload, {
                // headers: {
                //     'Content-Type': 'application/json',
                //     'Authorization': 'Basic ' + this.la_auth
                // }
            }).then((res) => {
                this.msg = res.data;
            })
                .catch((error) => {
                    console.log(error);
                });
        },

    },
    //https://stackoverflow.com/questions/49885020/drawing-a-straight-line-using-mouse-events-on-canvas-in-javascript
};
</script>

<style>
.image-container {
    display: inline-block;
    width: 100%;
    /* height: 500px; */
    position: relative;
    min-height: 80vh;

}

.image-container canvas {
    background: url(../assets/Chart-p-h-R134a-1.png);
    background-size: 100% 100%;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    position: absolute;

}
</style>