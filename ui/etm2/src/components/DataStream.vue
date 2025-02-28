<template>
	<div>
		<div><control-panel :url="url" /></div>
		<!-- <button @click="CheckURL()">Check Data URL</button> -->
	</div>
</template>

<script>

import axios from "axios";
import ControlPanel from "./ControlPanel.vue";


export default {
	name: "DataStream",
	components: {
		ControlPanel,


	},
	data() {
		return {
			stream: Object,
		}
	},
	computed: {
		urlOK() {
			return this.$store.getters.getDataURLObtained;
		},
		streamOK() {
			return this.$store.getters.getStream("data");

		},
		url() {
			return this.$store.getters.getDataURL;
		},
		version() {
			return this.$store.getters.getRemoteLabVersion;
		},
		dataRecorder() {
			return this.$store.getters.getIsDataRecorderOn;
		},
		tooltips() {
			return this.$store.getters.getDisableTooltips;
		}

	},
	mounted() {
		var _this = this;
		var reconnect = function () {
			console.log("RECONNECT EVENT");
			_this.getWebsocketConnection();
		};
		//make second and subsequent connections
		document.addEventListener("streams:dropped", reconnect);
		// reconnect();
	},
	methods: {
		getWebsocketConnection() {
			this.stream = this.$store.getters.getStream("data");
			var accessURL = this.stream.url;
			var token = this.stream.token;
			var store = this.$store;
			store.dispatch("deleteDataURL");		//NEWLY ADDED
			axios
				.post(accessURL, {}, { headers: { Authorization: token } })
				.then((response) => {
					store.dispatch("setDataURL", response.data.uri);
				})
				.catch((err) => console.log(err));
		},
		CheckURL() {
			console.log(this.$store.getters.getDataURL);
		}
	},

	watch: {
		streamOK: function (is) {
			if (is) {
				this.getWebsocketConnection();
			} else {
				console.log("no stream");
			}
		},
		// urlOK(is) {
		// 	if (is) {
		// 		console.log("get dataURL", this.urlOK, this.url);
		// 	}
		// },

	},

}


</script>

<style scoped></style>