<template>
	<div id="ControlPanel-div">
		<h2 id="controlPanel-head"> Experiment Control Panel and Schematic </h2>
		<div class='container-fluid m-2 background-white border rounded'>

			<div id="ControlPanel-PID">
				<PID />
			</div>
			<div id="ControlPanel-buttons" class="row">

				<div id="control-button-group" class="col-3 offset-2">
					<div  id="valve1-button-switch" class="form-check form-switch">
						<input id="valve1-button-input" class="form-check-input" type="checkbox" :checked="V1SwitchControllor"
							:disabled="V1SwitchDisabled" @click="valve1ColorChange()">
						<label id="valve1-button-label" class="form-check-label" :style="{ color: valve1Color }">V1 {{ V1state }}</label>
					</div>
					<!-- <div class="form-check form-switch">
						<input class="form-check-input" type="checkbox" :checked="V2SwitchControllor"
							:disabled="V2SwitchDisabled" @click="valve2ColorChange()">
						<label class="form-check-label" :style="{ color: valve2Color }">V2 {{ V2state }}</label>
					</div>
					<div class="form-check form-switch">
						<input class="form-check-input" type="checkbox" :checked="V3SwitchControllor"
							:disabled="V3SwitchDisabled" @click="valve3ColorChange()">
						<label class="form-check-label" :style="{ color: valve3Color }">V3 {{ V3state }}</label>
					</div>
					<div class="form-check form-switch">
						<input class="form-check-input" type="checkbox" :checked="V4SwitchControllor"
							:disabled="V4SwitchDisabled" @click="valve4ColorChange()">
						<label class="form-check-label" :style="{ color: valve4Color }">V4 {{ V4state }}</label>
					</div> -->
				</div>

				<div id="control-button-group" class="col-3">
					<div id="valve5-button-switch" class="form-check form-switch">
						<input id="valve5-button-input" class="form-check-input" type="checkbox" :checked="V5SwitchControllor"
							:disabled="V5SwitchDisabled" @click="valve5ColorChange()">
						<label id="valve5-button-label" class="form-check-label" :style="{ color: valve5Color }">V5 {{ V5state }}</label>
					</div>
					<div id="valve6-button-switch" class="form-check form-switch">
						<input id="valve6-button-input" class="form-check-input" type="checkbox" :checked="V6SwitchControllor"
							:disabled="V6SwitchDisabled" @click="valve6ColorChange()">
						<label id="valve6-button-label" class="form-check-label" :style="{ color: valve6Color }">V6 {{ V6state }}</label>
					</div>
					<!-- <div class="form-check form-switch">
						<input class="form-check-input" type="checkbox" :checked="V7SwitchControllor"
							:disabled="V7SwitchDisabled" @click="valve7ColorChange()">
						<label class="form-check-label" :style="{ color: valve7Color }"> V7 {{ V7state }}</label>
					</div> -->

				</div>


				<div id="control-button-group" class="col-3">
					<div id="fans-button-switch" class="form-check form-switch">
						<input id="fans-button-input" class="form-check-input" type="checkbox" :checked="W1SwitchControllor"
							:disabled="W1SwitchDisabled" @click="w1ColorChange()">
						<label id="fans-button-label" class="form-check-label" :style="{ color: w1color }"> Fans {{ W1state }} </label>
					</div>
					<div id="compressor-button-switch" class="form-check form-switch">
						<input id="compressor-button-input" class="form-check-input" type="checkbox" :checked="COMPSwitchControllor"
							:disabled="COMPSwitchDisabled" @click="compColorChange()">
						<label id="compressor-button-label" class="form-check-label" :style="{ color: compcolor }"> Compressor {{ COMPstate
							}}</label>
					</div>
					<div id="lights-button-switch" class="form-check form-switch">
						<input id="lights-button-input" class="form-check-input" type="checkbox" :checked="lightSwitchControllor"
							:disabled="lightSwitchDisabled" @click="lightColorChange()">
						<label id="lights-button-label" class="form-check-label" :style="{ color: lightcolor }"> Lights {{ lightstate }}</label>
					</div>
				</div>
			</div>
		</div>
		<toolbar parentCanvasID="ControlPanel-div" parentComponentName="ControlPanel" parentDivID="ControlPanel-div"
			:showDownload='false' :showPopupHelp="true" :showOptions="false" id="ControlPanel_help">
			<template v-slot:popup id='ControlPanel-popup'>
				<div class='row mb-2'>
					<div class='col'>
						<h3> Experiment Control Panel and Schematic </h3>
						<p> Control the experiment using the Control Panel and view the schematic diagram of the
							equipment. </p>
						<p> <b>Schematic:</b> The Nomenclature of the equipment is included in Table.</p>
						<table class="table">
							<thead>
								<tr>
									<th scope="col">#</th>
									<th scope="col">Symbol</th>
									<th scope="col">Definition</th>
									<th scope="col">Property</th>
								</tr>
							</thead>
							<tbody>
								<tr>
									<th scope="row">1</th>
									<td>V1</td>
									<td>Shut-off Valve Thermostatic Expansion Valve</td>
									<td>Control</td>
								</tr>
								<!-- <tr>
									<th scope="row">2</th>
									<td>V2</td>
									<td>Shut-off Valve Capillary Tube 1.5m</td>
									<td>Control</td>
								</tr>
								<tr>
									<th scope="row">3</th>
									<td>V3</td>
									<td>Shut-off Valve Capillary Tube 3m</td>
									<td>Control</td>
								</tr>
								<tr>
									<th scope="row">4</th>
									<td>V4</td>
									<td>Shut-off Valve Capillary Tube 6m</td>
									<td>Control</td>
								</tr> -->
								<tr>
									<th scope="row">2</th>
									<td>V5</td>
									<td>Shut-off Valve Receiver Outlet</td>
									<td>Control</td>
								</tr>
								<tr>
									<th scope="row">3</th>
									<td>V6</td>
									<td>Shut-off Valve Receiver Inlet</td>
									<td>Control</td>
								</tr>
								<!-- <tr>
									<th scope="row">7</th>
									<td>V7</td>
									<td>Shut-off Valve Receiver Bypass</td>
									<td>Control</td>
								</tr> -->
								<tr>
									<th scope="row">4</th>
									<td>T-01</td>
									<td>Compressor Inlet Temperature</td>
									<td>Monitor</td>
								</tr>
								<tr>
									<th scope="row">5</th>
									<td>T-02</td>
									<td>Compressor Outlet Temperature</td>
									<td>Monitor</td>
								</tr>
								<tr>
									<th scope="row">6</th>
									<td>T-03</td>
									<td>Condenser Outlet Temperature</td>
									<td>Monitor</td>
								</tr>
								<tr>
									<th scope="row">7</th>
									<td>T-04</td>
									<td>Evaporator Inlet Temperature</td>
									<td>Monitor</td>
								</tr>
								<tr>
									<th scope="row">8</th>
									<td>T-05</td>
									<td>Evaporator Outlet Temperature</td>
									<td>Monitor</td>
								</tr>
								<tr>
									<th scope="row">9</th>
									<td>P-01</td>
									<td>Evaporation Pressure</td>
									<td>Monitor</td>
								</tr>
								<tr>
									<th scope="row">10</th>
									<td>P-02</td>
									<td>Compressor Outlet Pressure</td>
									<td>Monitor</td>
								</tr>
								<tr>
									<th scope="row">11</th>
									<td>P-03</td>
									<td>Condensation Pressure</td>
									<td>Monitor</td>
								</tr>
								<tr>
									<th scope="row">12</th>
									<td>F</td>
									<td>Flowrate of Refrigerant</td>
									<td>Monitor</td>
								</tr>
								<tr>
									<th scope="row">13</th>
									<td>E</td>
									<td>Electric Power of Compressor</td>
									<td>Monitor</td>
								</tr>
							</tbody>
						</table>
						<p> The operation of the schematic is as follows:</p>
						<p>a. <b>Hover:</b> Hover the mouse pointer on the schematic symbols for 1 second to show the
							names of
							symbols.</p>
						<p>b. <b>Click: </b>To learn more about the kit in the real equipment, click on the symbol
							section
							(gray) in the schematic and a red blinking square will be displayed for the corresponding
							part in the equipment image.</p>

						<p><b>Control Panel: </b>The status of the control panel is included in Table C. </p>
						<table class="table">
							<thead>
								<tr>
									<th scope="col">#</th>
									<th scope="col">Status of valve</th>
									<th scope="col">Description</th>									
								</tr>
							</thead>
							<tbody>
								<tr>
									<th scope="row">1</th>
									<td>OFF</td>
									<td>The current state of the valve or switch is OFF</td>									
								</tr>
								<tr>
									<th scope="row">2</th>
									<td>ON</td>
									<td>The current state of the valve or switch is ON</td>									
								</tr>
								<tr>
									<th scope="row">3</th>
									<td>Opening/Turning on</td>
									<td>The current state of the valve or switch is Opening/Turning on, which may need 2-3 seconds.</td>									
								</tr>
								<tr>
									<th scope="row">4</th>
									<td>Closing/Turning off</td>
									<td>The current state of the valve or switch is Closing/Turning off, which may need 2-3 seconds.</td>									
								</tr>						
							</tbody>
						</table>
					</div>
				</div>
			</template>
		</toolbar>
	</div>
</template>

<script>
import PID from "./PID.vue"
// import dataTestStore from "../modules/ACON_dataTestStore"
//import Tooltip from "./Tooltip.vue";
import { mapGetters, mapMutations, mapActions } from 'vuex';
import Toolbar from './elements/Toolbar.vue';

export default {
	name: "ControlPanel",
	components: {
		//Tooltip,
		PID,
		Toolbar,

	},
	props: {
		url: String,
	},
	data() {
		return {
			dataSocket: null,
			// canvas: null,

			V1state: "OFF",
			V1SwitchControllor: false,
			V1SwitchDisabled: false,
			V1msg: "V1 error",

			V2state: "OFF",
			V2SwitchControllor: false,
			V2SwitchDisabled: false,
			V2msg: "V2 error",

			V3state: "OFF",
			V3SwitchControllor: false,
			V3SwitchDisabled: false,
			V3msg: "V3 error",

			V4state: "OFF",
			V4SwitchControllor: false,
			V4SwitchDisabled: false,
			V4msg: "V4 error",

			V5state: "OFF",
			V5SwitchControllor: false,
			V5SwitchDisabled: false,
			V5msg: "V5 error",

			V6state: "OFF",
			V6SwitchControllor: false,
			V6SwitchDisabled: false,
			V6msg: "V6 error",

			V7state: "OFF",
			V7SwitchControllor: false,
			V7SwitchDisabled: false,
			V7msg: "V7 error",

			W1state: "OFF",
			W1SwitchControllor: false,
			W1SwitchDisabled: false,
			W1msg: "Fans error",

			COMPstate: "OFF",
			COMPSwitchControllor: false,
			COMPSwitchDisabled: false,
			COMPmsg: "Fans error",

			lightstate: "OFF",
			lightSwitchControllor: false,
			lightSwitchDisabled: false,
			lightmsg: "Lights error",


		}
	},
	computed: {
		...mapGetters([
			'getDataURLObtained',
		]),
		valve1Color() {
			return this.$store.state.ui.v1color;
		},
		valve2Color() {
			return this.$store.state.ui.v2color;
		},
		valve3Color() {
			return this.$store.state.ui.v3color;
		},
		valve4Color() {
			return this.$store.state.ui.v4color;
		},
		valve5Color() {
			return this.$store.state.ui.v5color;
		},
		valve6Color() {
			return this.$store.state.ui.v6color;
		},
		valve7Color() {
			return this.$store.state.ui.v7color;
		},
		w1color() {
			return this.$store.state.ui.w1color;
		},
		compcolor() {
			return this.$store.state.ui.compcolor;
		},
		lightcolor() {
			return this.$store.state.ui.lightcolor;
		},




	},
	watch: {
		url() {
			try {
				if (this.getDataURLObtained) {//this.url != '' &&
					this.connect();
					// this.getInitialValveState();
				} else {
					console.log('disconnecting: ' + this.url);
				}

			} catch (e) {
				console.log(e);
			}


		},


	},
	created() {

		// window.addEventListener('beforeunload',this.getinitialstate);
	},
	mounted() {
		// var _this = this;
		// _this.getWebsocketConnection();

	},
	methods: {

		...mapActions([

			//set sensors value
			'setPS1_value',
			'setPS2_value',
			'setPS3_value',
			'setTS1_value',
			'setTS2_value',
			'setTS3_value',
			'setTS4_value',
			'setTS5_value',
			'setFlow_value',
			'setPower_value',
			'setTSA_value',
			'setPSA_value',
			'setHSA_value',

			// set controllers' value
			'setV1',
			'setV2',
			'setV3',
			'setV4',
			'setV5',
			'setV6',
			'setV7',
			// 'SETV8',
			'setW1',
			'setW2',
			'setComp',
			'setlight', //set light value

			'setCurrentDate',
			'setRecorderCurrentTime',

			//set the color and send command to server
			'setV1color',// set the color of the valve,setV1color(2)-waiting, setV1color(1)-on,setV1color(0)-off
			'SENDV1CONTROL',//send command to server,SENDV1CONTROL(1)-open,SENDV1CONTROL(1)-close
			'setV2color',
			'SENDV2CONTROL',
			'setV3color',
			'SENDV3CONTROL',
			'setV4color',
			'SENDV4CONTROL',
			'setV5color',
			'SENDV5CONTROL',
			'setV6color',
			'SENDV6CONTROL',
			'setV7color',
			'SENDV7CONTROL',
			'setW1color',
			'SENDW1CONTROL',
			// 'setW2color',
			'setCOMPcolor',
			'SENDCOMPCONTROL',
			'setlightcolor',
			'SENDLIGHTCONTROL',
		]),

		getinitialstate() {
			// get the initial state of controllers
			this.getInitialValve1State();
			this.getInitialValve2State();
			this.getInitialValve3State();
			this.getInitialValve4State();
			this.getInitialValve5State();
			this.getInitialValve6State();
			this.getInitialValve7State();
			this.getInitialFansState();
			this.getInitialCompState();
			this.getInitiallightState();
		},

		getInitialValve1State() {
			if (this.$store.state.command.V1 == 1) {
				this.setV1color(1);
				this.V1state = "ON";
				this.V1msg = "V1 already opended";
				console.log(this.V1msg);
				this.V1SwitchControllor = true;
			} else {
				this.V1SwitchDisabled = false;
				this.setV1color(0);
				this.V1state = "OFF";
				this.V1SwitchControllor = false;
			};

		},

		getInitialValve2State() {
			if (this.$store.state.command.V2 == 1) {
				this.setV2color(1);
				this.V2state = "ON";
				this.V2msg = "V2 already opended";
				console.log(this.V2msg);
				this.V2SwitchControllor = true;
			} else {
				this.V2SwitchDisabled = false;
				this.setV2color(0);
				this.V2state = "OFF";
				this.V2SwitchControllor = false;
			};

		},

		getInitialValve3State() {
			if (this.$store.state.command.V3 == 1) {
				this.setV3color(1);
				this.V3state = "ON";
				this.V3msg = "V3 already opended";
				console.log(this.V3msg);
				this.V3SwitchControllor = true;
			} else {
				this.V3SwitchDisabled = false;
				this.setV3color(0);
				this.V3state = "OFF";
				this.V3SwitchControllor = false;
			};

		},

		getInitialValve4State() {
			if (this.$store.state.command.V4 == 1) {
				this.setV4color(1);
				this.V4state = "ON";
				this.V4msg = "V4 already opended";
				console.log(this.V4msg);
				this.V4SwitchControllor = true;
			} else {
				this.V4SwitchDisabled = false;
				this.setV4color(0);
				this.V4state = "OFF";
				this.V4SwitchControllor = false;
			};

		},

		getInitialValve5State() {
			if (this.$store.state.command.V5 == 1) {
				this.setV5color(1);
				this.V5state = "ON";
				this.V5msg = "V5 already opended";
				console.log(this.V5msg);
				this.V5SwitchControllor = true;
			} else {
				this.V5SwitchDisabled = false;
				this.setV5color(0);
				this.V5state = "OFF";
				this.V5SwitchControllor = false;
			};

		},

		getInitialValve6State() {
			if (this.$store.state.command.V6 == 1) {
				this.setV6color(1);
				this.V6state = "ON";
				this.V6msg = "V6 already opended";
				console.log(this.V6msg);
				this.V6SwitchControllor = true;
			} else {
				this.V6SwitchDisabled = false;
				this.setV6color(0);
				this.V6state = "OFF";
				this.V6SwitchControllor = false;
			};

		},



		getInitialValve7State() {
			if (this.$store.state.command.V7 == 1) {
				this.setV7color(1);
				this.V7state = "ON";
				this.V7msg = "V7 already opended";
				console.log(this.V7msg);
				this.V7SwitchControllor = true;
			} else {
				this.setV7color(0);
				this.V7state = "OFF";
				this.V7SwitchControllor = false;
			};

		},

		getInitialFansState() {
			if (this.$store.state.command.W1 == 1) {
				this.setW1color(1);
				this.W1state = "ON";
				this.W1msg = "Fans turned on";
				console.log(this.W1msg);
				this.W1SwitchControllor = true;
			}
			else if (this.$store.state.command.W1 == 0) {
				this.setW1color(0);
				this.W1state = "OFF";
				this.W1SwitchControllor = false;
			}
		},

		getInitialCompState() {
			if (this.$store.state.command.Comp == 1) {
				this.setCOMPcolor(1);
				this.COMPstate = "ON";
				this.COMPmsg = "Compressor turned on";
				console.log(this.COMPmsg);
				this.COMPSwitchControllor = true;
			}
			else if (this.$store.state.command.Comp == 0) {
				this.setCOMPcolor(0);
				this.COMPstate = "OFF";
				this.COMPSwitchControllor = false;
			}
		},

		getInitiallightState() {
			if (this.$store.state.command.light == 1) {
				this.setlightcolor(1);
				this.lightstate = "ON";
				this.lightmsg = "Lights turned on";
				console.log(this.lightmsg);
				this.lightSwitchControllor = true;
			}
			else if (this.$store.state.command.light == 0) {
				this.setlightcolor(0);
				this.lightstate = "OFF";
				this.lightSwitchControllor = false;
			}
		},

		//send command first, and the state changes to opening. waith 1 -2 second, check the state again, if the state become opened, then UI change. otherwise, alert and UI keep original.
		valve1ColorChange() {

			if (this.V1SwitchControllor == false && this.$store.state.command.V1 == 0) {

				this.setV1color(2);
				this.V1state = "opening";
				this.SENDV1CONTROL(1);
				this.V1msg = "V1opening";
				console.log(this.V1msg);
				this.V1SwitchDisabled = true;

				setTimeout(() => {
					if (this.$store.state.command.V1 == 1) {
						this.V1SwitchDisabled = false;
						this.setV1color(1);
						this.V1state = "ON";
						this.V1msg = "V1opened";
						console.log(this.V1msg);
						this.V1SwitchControllor = true;
					}
					else if (this.$store.state.command.V1 == 0) {
						this.V1SwitchDisabled = false;
						this.setV1color(0);
						this.V1state = "OFF";
						this.V1msg = "V1_not_open_success";
						console.log(this.V1msg);
						this.V1SwitchControllor = false;
					}
				}, 5000);

			} else if (this.V1SwitchControllor == true && this.$store.state.command.V1 == 1) {

				this.setV1color(2);
				this.V1state = "closing";
				this.SENDV1CONTROL(0);
				this.V1msg = "V1closing";
				console.log(this.V1msg);
				this.V1SwitchDisabled = true;

				setTimeout(() => {
					if (this.$store.state.command.V1 == 0) {
						this.V1SwitchDisabled = false;
						this.setV1color(0);
						this.V1state = "OFF";
						this.V1msg = "V1closed";
						console.log(this.V1msg);
						this.V1SwitchControllor = false;
					}
					else if (this.$store.state.command.V1 == 1) {
						this.V1SwitchDisabled = false;
						this.setV1color(1);
						this.V1state = "ON";
						this.V1msg = "V1_not_close_success";
						console.log(this.V1msg);
						this.V1SwitchControllor = true;
					}
				}, 5000);

			} else {
				alert(this.V1msg);
				console.log("error:" + "V1 is" + this.V1state + "; its code is" + this.$store.state.command.V1 + ";" + "V2 is" + this.V2state + "; its code is" + this.$store.state.command.V2 + ";"
					+ "V3 is" + this.V3state + "; its code is" + this.$store.state.command.V3 + ";" + "V4 is" + this.V4state + "; its code is" + this.$store.state.command.V4 + ";" + "V5 is" + this.V5state + "; its code is" + this.$store.state.command.V5 + ";"
					+ "V6 is" + this.V6state + "; its code is" + this.$store.state.command.V6 + ";" + "V7 is" + this.V7state + "; its code is" + this.$store.state.command.V7 + ";");
			}
		},


		valve2ColorChange() {

			if (this.V2SwitchControllor == false && this.$store.state.command.V2 == 0) {

				this.setV2color(2);
				this.V2state = "opening";
				this.SENDV2CONTROL(1);
				this.V2msg = "V2opening";
				console.log(this.V2msg);
				this.V2SwitchDisabled = true;

				setTimeout(() => {
					if (this.$store.state.command.V2 == 1) {
						this.V2SwitchDisabled = false;
						this.setV2color(1);
						this.V2state = "ON";
						this.V2msg = "V2opened";
						console.log(this.V2msg);
						this.V2SwitchControllor = true;
					}
					else if (this.$store.state.command.V2 == 0) {
						this.V2SwitchDisabled = false;
						this.setV2color(0);
						this.V2state = "OFF";
						this.V2msg = "V2_not_open_success";
						console.log(this.V2msg);
						this.V2SwitchControllor = false;
					}
				}, 5000);

			} else if (this.V2SwitchControllor == true && this.$store.state.command.V2 == 1) {

				this.setV2color(2);
				this.V2state = "closing";
				this.SENDV2CONTROL(0);
				this.V2msg = "V2closing";
				console.log(this.V2msg);
				this.V2SwitchDisabled = true;

				setTimeout(() => {
					if (this.$store.state.command.V2 == 0) {
						this.V2SwitchDisabled = false;
						this.setV2color(0);
						this.V2state = "OFF";
						this.V2msg = "V2closed";
						console.log(this.V2msg);
						this.V2SwitchControllor = false;
					}
					else if (this.$store.state.command.V2 == 1) {
						this.V2SwitchDisabled = false;
						this.setV2color(1);
						this.V2state = "ON";
						this.V2msg = "V2_not_close_success";
						console.log(this.V2msg);
						this.V2SwitchControllor = true;
					}
				}, 5000);

			} else {
				alert(this.V2msg);
				console.log("error:" + "V1 is" + this.V1state + "; its code is" + this.$store.state.command.V1 + ";" + "V2 is" + this.V2state + "; its code is" + this.$store.state.command.V2 + ";"
					+ "V3 is" + this.V3state + "; its code is" + this.$store.state.command.V3 + ";" + "V4 is" + this.V4state + "; its code is" + this.$store.state.command.V4 + ";" + "V5 is" + this.V5state + "; its code is" + this.$store.state.command.V5 + ";"
					+ "V6 is" + this.V6state + "; its code is" + this.$store.state.command.V6 + ";" + "V7 is" + this.V7state + "; its code is" + this.$store.state.command.V7 + ";");
			}
		},


		valve3ColorChange() {

			if (this.V3SwitchControllor == false && this.$store.state.command.V3 == 0) {

				this.setV3color(2);
				this.V3state = "opening";
				this.SENDV3CONTROL(1);
				this.V3msg = "V3opening";
				console.log(this.V3msg);
				this.V3SwitchDisabled = true;

				setTimeout(() => {
					if (this.$store.state.command.V3 == 1) {
						this.V3SwitchDisabled = false;
						this.setV3color(1);
						this.V3state = "ON";
						this.V3msg = "V3opened";
						console.log(this.V3msg);
						this.V3SwitchControllor = true;
					}
					else if (this.$store.state.command.V3 == 0) {
						this.V3SwitchDisabled = false;
						this.setV3color(0);
						this.V3state = "OFF";
						this.V3msg = "V3_not_open_success";
						console.log(this.V3msg);
						this.V3SwitchControllor = false;
					}
				}, 5000);

			} else if (this.V3SwitchControllor == true && this.$store.state.command.V3 == 1) {

				this.setV3color(2);
				this.V3state = "closing";
				this.SENDV3CONTROL(0);
				this.V3msg = "V3closing";
				console.log(this.V3msg);
				this.V3SwitchDisabled = true;

				setTimeout(() => {
					if (this.$store.state.command.V3 == 0) {
						this.V3SwitchDisabled = false;
						this.setV3color(0);
						this.V3state = "OFF";
						this.V3msg = "V3closed";
						console.log(this.V3msg);
						this.V3SwitchControllor = false;
					}
					else if (this.$store.state.command.V3 == 1) {
						this.V3SwitchDisabled = false;
						this.setV3color(1);
						this.V3state = "ON";
						this.V3msg = "V3_not_close_success";
						console.log(this.V3msg);
						this.V3SwitchControllor = true;
					}
				}, 5000);

			} else {
				alert(this.V3msg);
				console.log("error:" + "V1 is" + this.V1state + "; its code is" + this.$store.state.command.V1 + ";" + "V2 is" + this.V2state + "; its code is" + this.$store.state.command.V2 + ";"
					+ "V3 is" + this.V3state + "; its code is" + this.$store.state.command.V3 + ";" + "V4 is" + this.V4state + "; its code is" + this.$store.state.command.V4 + ";" + "V5 is" + this.V5state + "; its code is" + this.$store.state.command.V5 + ";"
					+ "V6 is" + this.V6state + "; its code is" + this.$store.state.command.V6 + ";" + "V7 is" + this.V7state + "; its code is" + this.$store.state.command.V7 + ";");
			}
		},

		valve4ColorChange() {

			if (this.V4SwitchControllor == false && this.$store.state.command.V4 == 0) {

				this.setV4color(2);
				this.V4state = "opening";
				this.SENDV4CONTROL(1);
				this.V4msg = "V4opening";
				console.log(this.V4msg);
				this.V4SwitchDisabled = true;

				setTimeout(() => {
					if (this.$store.state.command.V4 == 1) {
						this.V4SwitchDisabled = false;
						this.setV4color(1);
						this.V4state = "ON";
						this.V4msg = "V4opened";
						console.log(this.V4msg);
						this.V4SwitchControllor = true;
					}
					else if (this.$store.state.command.V4 == 0) {
						this.V4SwitchDisabled = false;
						this.setV4color(0);
						this.V4state = "OFF";
						this.V4msg = "V4_not_open_success";
						console.log(this.V4msg);
						this.V4SwitchControllor = false;
					}
				}, 5000);

			} else if (this.V4SwitchControllor == true && this.$store.state.command.V4 == 1) {

				this.setV4color(2);
				this.V4state = "closing";
				this.SENDV4CONTROL(0);
				this.V4msg = "V4closing";
				console.log(this.V4msg);
				this.V4SwitchDisabled = true;

				setTimeout(() => {
					if (this.$store.state.command.V4 == 0) {
						this.V4SwitchDisabled = false;
						this.setV4color(0);
						this.V4state = "OFF";
						this.V4msg = "V4closed";
						console.log(this.V4msg);
						this.V4SwitchControllor = false;
					}
					else if (this.$store.state.command.V4 == 1) {
						this.V4SwitchDisabled = false;
						this.setV4color(1);
						this.V4state = "ON";
						this.V4msg = "V4_not_close_success";
						console.log(this.V4msg);
						this.V4SwitchControllor = true;
					}
				}, 5000);

			} else {
				alert(this.V4msg);
				console.log("error:" + "V1 is" + this.V1state + "; its code is" + this.$store.state.command.V1 + ";" + "V2 is" + this.V2state + "; its code is" + this.$store.state.command.V2 + ";"
					+ "V3 is" + this.V3state + "; its code is" + this.$store.state.command.V3 + ";" + "V4 is" + this.V4state + "; its code is" + this.$store.state.command.V4 + ";" + "V5 is" + this.V5state + "; its code is" + this.$store.state.command.V5 + ";"
					+ "V6 is" + this.V6state + "; its code is" + this.$store.state.command.V6 + ";" + "V7 is" + this.V7state + "; its code is" + this.$store.state.command.V7 + ";");
			}
		},


		valve5ColorChange() {

			if (this.V5SwitchControllor == false && this.$store.state.command.V5 == 0) {

				this.setV5color(2);
				this.V5state = "opening";
				this.SENDV5CONTROL(1);
				this.V5msg = "V5opening";
				console.log(this.V5msg);
				this.V5SwitchDisabled = true;

				setTimeout(() => {
					if (this.$store.state.command.V5 == 1) {
						this.V5SwitchDisabled = false;
						this.setV5color(1);
						this.V5state = "ON";
						this.V5msg = "V5opened";
						console.log(this.V5msg);
						this.V5SwitchControllor = true;
					}
					else if (this.$store.state.command.V5 == 0) {
						this.V5SwitchDisabled = false;
						this.setV5color(0);
						this.V5state = "OFF";
						this.V5msg = "V5_not_open_success";
						console.log(this.V5msg);
						this.V5SwitchControllor = false;
					}
				}, 5000);

			} else if (this.V5SwitchControllor == true && this.$store.state.command.V5 == 1) {

				this.setV5color(2);
				this.V5state = "closing";
				this.SENDV5CONTROL(0);
				this.V5msg = "V5closing";
				console.log(this.V5msg);
				this.V5SwitchDisabled = true;

				setTimeout(() => {
					if (this.$store.state.command.V5 == 0) {
						this.V5SwitchDisabled = false;
						this.setV5color(0);
						this.V5state = "OFF";
						this.V5msg = "V5closed";
						console.log(this.V5msg);
						this.V5SwitchControllor = false;
					}
					else if (this.$store.state.command.V5 == 1) {
						this.V5SwitchDisabled = false;
						this.setV5color(1);
						this.V5state = "ON";
						this.V5msg = "V5_not_close_success";
						console.log(this.V5msg);
						this.V5SwitchControllor = true;
					}
				}, 5000);

			} else {
				alert(this.V5msg);
				console.log("error:" + "V1 is" + this.V1state + "; its code is" + this.$store.state.command.V1 + ";" + "V2 is" + this.V2state + "; its code is" + this.$store.state.command.V2 + ";"
					+ "V3 is" + this.V3state + "; its code is" + this.$store.state.command.V3 + ";" + "V4 is" + this.V4state + "; its code is" + this.$store.state.command.V4 + ";" + "V5 is" + this.V5state + "; its code is" + this.$store.state.command.V5 + ";"
					+ "V6 is" + this.V6state + "; its code is" + this.$store.state.command.V6 + ";" + "V7 is" + this.V7state + "; its code is" + this.$store.state.command.V7 + ";");
			}
		},



		valve6ColorChange() {

			if (this.V6SwitchControllor == false && this.$store.state.command.V6 == 0) {

				this.setV6color(2);
				this.V6state = "opening";
				this.SENDV6CONTROL(1);
				this.V6msg = "V6opening";
				console.log(this.V6msg);
				this.V6SwitchDisabled = true;

				setTimeout(() => {
					if (this.$store.state.command.V6 == 1) {
						this.V6SwitchDisabled = false;
						this.setV6color(1);
						this.V6state = "ON";
						this.V6msg = "V6opened";
						console.log(this.V6msg);
						this.V6SwitchControllor = true;
					}
					else if (this.$store.state.command.V6 == 0) {
						this.V6SwitchDisabled = false;
						this.setV6color(0);
						this.V6state = "OFF";
						this.V6msg = "V6_not_open_success";
						console.log(this.V6msg);
						this.V6SwitchControllor = false;
					}
				}, 5000);

			} else if (this.V6SwitchControllor == true && this.$store.state.command.V6 == 1) {

				this.setV6color(2);
				this.V6state = "closing";
				this.SENDV6CONTROL(0);
				this.V6msg = "V6closing";
				console.log(this.V6msg);
				this.V6SwitchDisabled = true;

				setTimeout(() => {
					if (this.$store.state.command.V6 == 0) {
						this.V6SwitchDisabled = false;
						this.setV6color(0);
						this.V6state = "OFF";
						this.V6msg = "V6closed";
						console.log(this.V6msg);
						this.V6SwitchControllor = false;
					}
					else if (this.$store.state.command.V6 == 1) {
						this.V6SwitchDisabled = false;
						this.setV6color(1);
						this.V6state = "ON";
						this.V6msg = "V6_not_close_success";
						console.log(this.V6msg);
						this.V6SwitchControllor = true;
					}
				}, 5000);

			} else {
				alert(this.V6msg);
				console.log("error:" + "V1 is" + this.V1state + "; its code is" + this.$store.state.command.V1 + ";" + "V2 is" + this.V2state + "; its code is" + this.$store.state.command.V2 + ";"
					+ "V3 is" + this.V3state + "; its code is" + this.$store.state.command.V3 + ";" + "V4 is" + this.V4state + "; its code is" + this.$store.state.command.V4 + ";" + "V5 is" + this.V5state + "; its code is" + this.$store.state.command.V5 + ";"
					+ "V6 is" + this.V6state + "; its code is" + this.$store.state.command.V6 + ";" + "V7 is" + this.V7state + "; its code is" + this.$store.state.command.V7 + ";");
			}
		},



		valve7ColorChange() {

			if (this.V7SwitchControllor == false && this.$store.state.command.V7 == 0) {

				this.setV7color(2);
				this.V7state = "opening";
				this.SENDV7CONTROL(1);
				this.V7msg = "V7opening";
				console.log(this.V7msg);
				this.V7SwitchDisabled = true;

				setTimeout(() => {
					if (this.$store.state.command.V7 == 1) {
						this.V7SwitchDisabled = false;
						this.setV7color(1);
						this.V7state = "ON";
						this.V7msg = "V7opened";
						console.log(this.V7msg);
						this.V7SwitchControllor = true;
					}
					else if (this.$store.state.command.V7 == 0) {
						this.V7SwitchDisabled = false;
						this.setV7color(0);
						this.V7state = "OFF";
						this.V7msg = "V7_not_open_success";
						console.log(this.V7msg);
						this.V7SwitchControllor = false;
					}
				}, 5000);

			} else if (this.V7SwitchControllor == true && this.$store.state.command.V7 == 1) {

				this.setV7color(2);
				this.V7state = "closing";
				this.SENDV7CONTROL(0);
				this.V7msg = "V7closing";
				console.log(this.V7msg);
				this.V7SwitchDisabled = true;

				setTimeout(() => {
					if (this.$store.state.command.V7 == 0) {
						this.V7SwitchDisabled = false;
						this.setV7color(0);
						this.V7state = "OFF";
						this.V7msg = "V7closed";
						console.log(this.V7msg);
						this.V7SwitchControllor = false;
					}
					else if (this.$store.state.command.V7 == 1) {
						this.V7SwitchDisabled = false;
						this.setV7color(1);
						this.V7state = "ON";
						this.V7msg = "V7_not_close_success";
						console.log(this.V7msg);
						this.V7SwitchControllor = true;
					}
				}, 5000);

			} else {
				alert(this.V7msg);
				console.log("error:" + "V1 is" + this.V1state + "; its code is" + this.$store.state.command.V1 + ";" + "V2 is" + this.V2state + "; its code is" + this.$store.state.command.V2 + ";"
					+ "V3 is" + this.V3state + "; its code is" + this.$store.state.command.V3 + ";" + "V4 is" + this.V4state + "; its code is" + this.$store.state.command.V4 + ";" + "V5 is" + this.V5state + "; its code is" + this.$store.state.command.V5 + ";"
					+ "V6 is" + this.V6state + "; its code is" + this.$store.state.command.V6 + ";" + "V7 is" + this.V7state + "; its code is" + this.$store.state.command.V7 + ";");
			}
		},




		w1ColorChange() {

			if (this.W1SwitchControllor == false && this.$store.state.command.W1 == 0) {

				this.setW1color(2);
				this.W1state = "Turning on";
				this.SENDW1CONTROL(1);
				this.W1msg = "Fans turning on";
				console.log(this.W1msg);
				this.W1SwitchDisabled = true;

				setTimeout(() => {
					if (this.$store.state.command.W1 == 1) {
						this.W1SwitchDisabled = false;
						this.setW1color(1);
						this.W1state = "ON";
						this.W1msg = "Fans turned on";
						console.log(this.W1msg);
						this.W1SwitchControllor = true;
					}
					else if (this.$store.state.command.W1 == 0) {
						this.W1SwitchDisabled = false;
						this.setW1color(0);
						this.W1state = "OFF";
						this.W1msg = "Fans_not_turn_on_success";
						console.log(this.W1msg);
						this.W1SwitchControllor = false;
					}
				}, 5000);

			} else if (this.W1SwitchControllor == true && this.$store.state.command.W1 == 1) {

				this.setW1color(2);
				this.W1state = "Turning off";
				this.SENDW1CONTROL(0);
				this.W1msg = "Fans turning off";
				console.log(this.W1msg);
				this.W1SwitchDisabled = true;

				setTimeout(() => {
					if (this.$store.state.command.W1 == 0) {
						this.W1SwitchDisabled = false;
						this.setW1color(0);
						this.W1state = "OFF";
						this.W1msg = "Fans turning off";
						console.log(this.W1msg);
						this.W1SwitchControllor = false;
					}
					else if (this.$store.state.command.W1 == 1) {
						this.W1SwitchDisabled = false;
						this.setW1color(1);
						this.W1state = "ON";
						this.W1msg = "Fans_not_turn_off_success";
						console.log(this.W1msg);
						this.W1SwitchControllor = true;
					}
				}, 5000);

			} else {
				alert(this.W1msg + this.$store.state.command.W1 + this.W1SwitchControllor);
				console.log("error:" + "V1 is" + this.V1state + "; its code is" + this.$store.state.command.V1 + ";" + "V2 is" + this.V2state + "; its code is" + this.$store.state.command.V2 + ";"
					+ "V3 is" + this.V3state + "; its code is" + this.$store.state.command.V3 + ";" + "V4 is" + this.V4state + "; its code is" + this.$store.state.command.V4 + ";" + "V5 is" + this.V5state + "; its code is" + this.$store.state.command.V5 + ";"
					+ "V6 is" + this.V6state + "; its code is" + this.$store.state.command.V6 + ";" + "V7 is" + this.V7state + "; its code is" + this.$store.state.command.V7 + ";"
					+ "W1 is" + this.W1state + "; its code is" + this.$store.state.command.W1 + ";");
			}
		},




		compColorChange() {

			if (this.COMPSwitchControllor == false && this.$store.state.command.Comp == 0) {

				this.setCOMPcolor(2);
				this.COMPstate = "Turning on";
				this.SENDCOMPCONTROL(1);
				this.COMPmsg = "Compressor turning on";
				console.log(this.COMPmsg);
				this.COMPSwitchDisabled = true;

				setTimeout(() => {
					if (this.$store.state.command.Comp == 1) {
						this.COMPSwitchDisabled = false;
						this.setCOMPcolor(1);
						this.COMPstate = "ON";
						this.COMPmsg = "Compressor turned on";
						console.log(this.COMPmsg);
						this.COMPSwitchControllor = true;
					}
					else if (this.$store.state.command.Comp == 0) {
						this.COMPSwitchDisabled = false;
						this.setCOMPcolor(0);
						this.COMPstate = "OFF";
						this.COMPmsg = "Comperssor_not_turn_on_success";
						console.log(this.COMPmsg);
						this.COMPSwitchControllor = false;
					}
				}, 5000);

			} else if (this.COMPSwitchControllor == true && this.$store.state.command.Comp == 1) {

				this.setCOMPcolor(2);
				this.COMPstate = "Turning off";
				this.SENDCOMPCONTROL(0);
				this.COMPmsg = "Compressor turning off";
				console.log(this.COMPmsg);
				this.COMPSwitchDisabled = true;

				setTimeout(() => {
					if (this.$store.state.command.Comp == 0) {
						this.COMPSwitchDisabled = false;
						this.setCOMPcolor(0);
						this.COMPstate = "OFF";
						this.COMPmsg = "Compressor turned off";
						console.log(this.COMPmsg);
						this.COMPSwitchControllor = false;
					}
					else if (this.$store.state.command.Comp == 1) {
						this.COMPSwitchDisabled = false;
						this.setCOMPcolor(1);
						this.COMPstate = "ON";
						this.COMPmsg = "Compressor_not_turn_off_success";
						console.log(this.COMPmsg);
						this.COMPSwitchControllor = true;
					}
				}, 5000);

			} else {
				alert(this.COMPmsg + this.$store.state.command.Comp + this.COMPSwitchControllor);
				console.log("error:" + "V1 is" + this.V1state + "; its code is" + this.$store.state.command.V1 + ";" + "V2 is" + this.V2state + "; its code is" + this.$store.state.command.V2 + ";"
					+ "V3 is" + this.V3state + "; its code is" + this.$store.state.command.V3 + ";" + "V4 is" + this.V4state + "; its code is" + this.$store.state.command.V4 + ";" + "V5 is" + this.V5state + "; its code is" + this.$store.state.command.V5 + ";"
					+ "V6 is" + this.V6state + "; its code is" + this.$store.state.command.V6 + ";" + "V7 is" + this.V7state + "; its code is" + this.$store.state.command.V7 + ";"
					+ "W1 is" + this.W1state + "; its code is" + this.$store.state.command.W1 + ";");
			}
		},


		lightColorChange() {

			if (this.lightSwitchControllor == false && this.$store.state.command.light == 0) {

				this.setlightcolor(2);
				this.lightstate = "Turning on";
				this.SENDLIGHTCONTROL(1);
				this.lightmsg = "lights turning on";
				console.log(this.lightmsg);
				this.lightSwitchDisabled = true;

				setTimeout(() => {
					if (this.$store.state.command.light == 1) {
						this.lightSwitchDisabled = false;
						this.setlightcolor(1);
						this.lightstate = "ON";
						this.lightmsg = "lights Turned on";
						console.log(this.lightmsg);
						this.lightSwitchControllor = true;
					}
					else if (this.$store.state.command.light == 0) {
						this.lightSwitchDisabled = false;
						this.setlightcolor(0);
						this.lightstate = "OFF";
						this.lightmsg = "lights_not_turn_on_success";
						console.log(this.lightmsg);
						this.lightSwitchControllor = false;
					}
				}, 5000);

			} else if (this.lightSwitchControllor == true && this.$store.state.command.light == 1) {

				this.setlightcolor(2);
				this.lightstate = "Turning off";
				this.SENDLIGHTCONTROL(0);
				this.lightmsg = "lights turning off";
				console.log(this.lightmsg);
				this.lightSwitchDisabled = true;

				setTimeout(() => {
					if (this.$store.state.command.light == 0) {
						this.lightSwitchDisabled = false;
						this.setlightcolor(0);
						this.lightstate = "OFF";
						this.lightmsg = "lights Turned off";
						console.log(this.lightmsg);
						this.lightSwitchControllor = false;
					}
					else if (this.$store.state.command.light == 1) {
						this.lightSwitchDisabled = false;
						this.setlightcolor(1);
						this.lightstate = "ON";
						this.lightmsg = "lights_not_turn_off_success";
						console.log(this.lightmsg);
						this.lightSwitchControllor = true;
					}
				}, 5000);

			} else {
				alert(this.lightmsg + this.$store.state.command.light + this.lightSwitchControllor);
				console.log("error:" + "V1 is" + this.V1state + "; its code is" + this.$store.state.command.V1 + ";" + "V2 is" + this.V2state + "; its code is" + this.$store.state.command.V2 + ";"
					+ "V3 is" + this.V3state + "; its code is" + this.$store.state.command.V3 + ";" + "V4 is" + this.V4state + "; its code is" + this.$store.state.command.V4 + ";" + "V5 is" + this.V5state + "; its code is" + this.$store.state.command.V5 + ";"
					+ "V6 is" + this.V6state + "; its code is" + this.$store.state.command.V6 + ";" + "V7 is" + this.V7state + "; its code is" + this.$store.state.command.V7 + ";"
					+ "W1 is" + this.W1state + "; its code is" + this.$store.state.command.W1 + ";");
			}
		},



		connect() {

			let _this = this;

			this.dataSocket = new WebSocket(this.url);
			//console.log(this.dataSocket);
			this.$store.dispatch('setDataSocket', this.dataSocket);


			let debug = false;


			this.dataSocket.onopen = () => {
				//dataOpen = true; 
				console.log("Websocket Openned")

			};


			this.dataSocket.onmessage = (event) => {
				//console.log(event.data);
				// console.log(JSON.parse(event.data));

				try {
					//delay of timestamp from device and UI

					var obj = JSON.parse(event.data);

					var msgTime = obj.timestamp;
					// Measured data from refrigeration
					var PS1 = obj.sensors.pressure.PS1;
					var PS2 = obj.sensors.pressure.PS2;
					var PS3 = obj.sensors.pressure.PS3;
					var TS1 = obj.sensors.temperature.TS1;
					var TS2 = obj.sensors.temperature.TS2;
					var TS3 = obj.sensors.temperature.TS3;
					var TS4 = obj.sensors.temperature.TS4;
					var TS5 = obj.sensors.temperature.TS5;
					var flow = obj.sensors.misc.flow;
					var power = obj.sensors.misc.power;
					var TSA = obj.sensors.misc.TSA;
					var PSA = obj.sensors.misc.PSA;
					var HSA = obj.sensors.misc.HSA;

					//controller data from refrigeration
					var V1 = obj.valves.V1;
					var V2 = obj.valves.V2;
					var V3 = obj.valves.V3;
					var V4 = obj.valves.V4;
					var V5 = obj.valves.V5;
					var V6 = obj.valves.V6;
					var V7 = obj.valves.V7;
					// var V8 = obj.valves.V8;
					var W1 = obj.relays.W1; //fan1
					var W2 = obj.relays.W2; //fan2
					var comp = obj.relays.comp; //compressor
					var lights = obj.relays.lights; //light


					//set the experimental measured value in store
					this.setPS1_value(PS1);
					this.setPS2_value(PS2);
					this.setPS3_value(PS3);
					this.setTS1_value(TS1);
					this.setTS2_value(TS2);
					this.setTS3_value(TS3);
					this.setTS4_value(TS4);
					this.setTS5_value(TS5);
					this.setFlow_value(flow);
					this.setPower_value(power);
					this.setTSA_value(TSA);
					this.setPSA_value(PSA);
					this.setHSA_value(HSA);
					// console.log(this.$store.state.rawData.PS1_value)


					//dispatch controllers value in store: rawdatastore_controllers
					this.setV1(V1);
					this.setV2(V2);
					this.setV3(V3);
					this.setV4(V4);
					this.setV5(V5);
					this.setV6(V6);
					this.setV7(V7);
					// this.setV8(V8);
					this.setW1(W1);
					this.setW2(W2);
					this.setComp(comp);
					this.setlight(lights);
					this.setRecorderCurrentTime(msgTime);//msgtime is start from restart of equipment, so in this experiment this time will not be recorded
					this.setCurrentDate(new Date().toLocaleString());

					// get the initial state of controllers
					this.getinitialstate();

				} catch (e) {
					if (debug) {
						console.log(e)
					}
				}

			};



			window.addEventListener('keydown', this.hotkey, false);
			//window.addEventListener('pagehide', this.free);				//closing window
			// window.addEventListener('beforeunload', this.free);			//refreshing page, changing URL


		},

	},
}




</script>

<style scoped>
#smoothie-chart {
	width: 100%;
	height: 120px;
}

.slidecontainer {
	width: 100%;
	/* Width of the outside container */
}

.slider {
	/* -webkit-appearance: none; */
	width: 100%;
	height: 15px;
	border-radius: 5px;
	background: #d3d3d3;
	outline: none;
	opacity: 0.7;
	-webkit-transition: .2s;
	transition: opacity .2s;
	cursor: pointer;
}

.slider::-webkit-slider-thumb {
	-webkit-appearance: none;
	appearance: none;
	width: 25px;
	height: 25px;
	border-radius: 50%;
	background: #1433BA;
	/* Persian Blue */
	cursor: grab;
}

.slider::-moz-range-thumb {
	width: 25px;
	height: 25px;
	border-radius: 50%;
	background: #1433BA;
	/* Persian Blue */
	cursor: grab;
}

/* Mouse-over effects */
.slider:hover {
	opacity: 1;
	/* Fully shown on mouse-over */
}

.column {
	float: left;
	width: 50%;
}


.sliderlabel {
	text-align: left;
}

.column1-4 {
	float: left;
	width: 30%;
}

.column2-4 {
	float: left;
	width: 40%;
}

.column3-4 {
	float: left;
	width: 75%;
}

.column1-3 {
	float: left;
	width: 33.3%;
}

.column2-3 {
	float: left;
	width: 66.6%;
}

.row {
	margin-top: 12px;
}

/* Clear floats after the columns */
.row:after {
	content: "";
	display: table;
	clear: both;
}
</style>