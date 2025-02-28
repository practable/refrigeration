//Vue3 update

<template>
    <div id='sessionTime'> Session ends in: {{current_time_left}}</div>
</template>

<script>

export default {

  name: 'Clock',
  data () {
    return {
        //current_time: '',           //in clock format
        current_time_left: '',      //in minutes and seconds
        interval_id: 0,
    }
  },
  components: {
    
  },
  computed:{
    //   sessionEndTime(){
    //       let date = new Date(this.$store.getters.getExpiryTime*1000);
    //       return this.getTime(date);
    //   }
  },
  watch:{
      
  },
  created(){
      
  },
  mounted(){
      this.interval_id = setInterval(() => {
          this.updateClock() 
      }, 1000);

  },
  methods: {
      addZeroes(value){
          if(value < 10){
              return "0" + value;
          } else {
              return value;
          }
      },
      updateClock(){
          //get the new date
          let date = new Date();
          //use this to get time in format hh:mm:ss
          //this.current_time = this.getTime(date);
          //get the time left to go in mm:ss
          this.current_time_left = this.getTimeLeft(date);
      },
      getTime(date){
          
          let hour = date.getHours();
          let min = date.getMinutes();
          let sec = date.getSeconds();

          hour = this.addZeroes(hour);
          min = this.addZeroes(min);
          sec = this.addZeroes(sec);

          return hour + ":" + min + ":" + sec;
      },
      getTimeLeft(date){
          let interval = this.$store.getters.getExpiryTime*1000 - date.getTime();       //in milliseconds
          let seconds = interval / 1000.0;
          let minutes = Math.floor(seconds/60);     //number of full minutes
          seconds = Math.floor(seconds % 60);               //remaining seconds

        //   minutes = this.addZeroes(minutes);
        //   seconds = this.addZeroes(seconds);

          if(interval > 0){
              return minutes + " min : " + seconds + " secs"; 
          } else {
            //   this.$store.dispatch('setSessionExpired', true);
              clearInterval(this.interval_id);
              return 'ENDED'
          }
          
      }
      
  }
}
</script>

<style scoped>
#sessionTime{
    font-style: italic;
    color: white;
}

</style>