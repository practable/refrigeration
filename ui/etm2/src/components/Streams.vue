<template>
  <div>

</div>
</template> 

<script>

import dayjs from "dayjs";

export default {
  name: "Streams",
  components: {

  },
  data(){
    return{
      connectionChecker: null,
    }
  },
  computed: {

    getSessionExpired(){
      return this.$store.getters.getSessionExpired;
    },
    decodedStreams() {
      return this.$store.getters.getStreams;
    },
    streamsObtained() {
      return this.$store.getters.getStreamsObtained;
    },
    videoStream() {
      return this.$store.getters.getStream("video");
    },
    videoAltStream() {
      return this.$store.getters.getStream("video-alt");
    },
    dataStream() {
      return this.$store.getters.getStream("data");
    },
  },
  created(){
      
    },
  mounted() {
    if (this.streamsObtained) {
      return;
    }
    try {
      let query = new URLSearchParams(window.location.search);
      //add the streams data to the store
      let streams = query.get('streams');
      let decodedStreams = JSON.parse(decodeURIComponent(String(streams)));
      let lh = query.get('lh');
      console.log(lh);
      
      this.$store.dispatch("setStreams", decodedStreams);
      //add expiry time data to store
      let expire_time = query.get('exp');
      this.$store.dispatch('setExpiryTime', expire_time);

      //Search for the course query parameter
      // If it doesn't exist then don't set null or '', just leave the default course set in the logging.js store - probably engdes1 for now
      let course = query.get('course');
      if(course != null){
        this.$store.dispatch('setCourse', course);
      }

    } catch (e) {
      console.log("error decoding streams");
      this.$store.dispatch("deleteStreams");
      
    }


    //reconnection code
    var _this = this;
    var cvb = function () {
      _this.$store.dispatch("setLastVideoWrite", dayjs().valueOf()); //milliseconds
    };

    document.addEventListener("jsmpeg:write", function () {
      cvb();
    });

    var wd = function(){
       var lc = _this.$store.getters.getLastVideoCheck;
      var lw = _this.$store.getters.getLastVideoWrite;

      var dropped = function () {
        
        _this.$store.dispatch("setConnectionIsDropped", true);
        _this.$store.dispatch("setConnectionDroppedAt", dayjs().unix()); //seconds
        var reconnectEvent = new Event("streams:dropped");
        document.dispatchEvent(reconnectEvent);
      };

      if (lc > lw) {
        // no write since last check
        if (_this.$store.getters.getConnectionIsDropped) {
          var when = _this.$store.getters.getConnectionDroppedAt;
          var since = dayjs().unix() - when;
          if (since > 10) {
          
            dropped();
          }
          return;
        }
        dropped();
      } else {
        //connection OK
        _this.$store.dispatch("setLastVideoCheck", dayjs().valueOf()); //milliseconds
        _this.$store.dispatch("setConnectionIsDropped", false);
      }

    };

    this.connectionChecker = setInterval(wd, 1000);

  },
  methods:{
    
  },
  watch: {
    getSessionExpired(expired){
      if(expired){
        clearInterval(this.connectionChecker);
      }
    }
  },
};

</script>